/*
 * Copyright (c) 2015, Salah-Eddin Shaban <salshaaban@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QTextCodec>
#include <QtCore/QDirIterator>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>
#else
#include <QtGui/QLineEdit>
#include <QtGui/QFileDialog>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), mGraphicsScene(0), mFontPath("fonts/"),
    mFreeTypeInitialized(false), mRendering(false),
    mLibrary(0), mFace(0), mResourceFace(0), mRawGlyphString(0),
    mShapedGlyphString(0), mRawVisualizer(0), mShapedVisualizer(0),
    mShapedRenderer(0), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BidiRenderer");
    statusBar();

    loadSamples();
    ui->fontPathLE->setText(mFontPath);
    listFonts();

    ui->levelsColorPickerLabel->setColor(Qt::blue);
    mFontSize = ui->fontSizeSB->value();
    mPenWidth = ui->penWidthSB->value();
    ui->lineWidthSlider->setRange(mFontSize * 4, mFontSize * 40);
    ui->lineWidthSlider->setValue(mFontSize * 40);

    if (FT_Init_FreeType(&mLibrary)) {
        statusBar()->showMessage("Error initializing FreeType", messageTimeout);
        return;
    }
    mFreeTypeInitialized = true;

    QFile fontFile(":/files/fonts/DejaVuSans.ttf");
    if (fontFile.open(QIODevice::ReadOnly))
        mResourceFaceData = fontFile.readAll();

    if (FT_New_Memory_Face(mLibrary,
                           reinterpret_cast<const FT_Byte*>(mResourceFaceData.constData()),
                           fontFile.size(), 0, &mResourceFace))
    {
        statusBar()->showMessage("Error loading DejaVuSans.ttf", messageTimeout);
    }
    else
    {
        if (FT_Set_Pixel_Sizes(mResourceFace, 0, mFontSize)) {
            statusBar()->showMessage("Error setting font pixel size", messageTimeout);
            FT_Done_Face(mResourceFace);
            mResourceFace = 0;
        } else {
            mFace = mResourceFace;
        }
    }


    mGraphicsScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(mGraphicsScene);

    connect(ui->actionE_xit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Panel, SIGNAL(toggled(bool)),
            ui->dockWidget, SLOT(setVisible(bool)));
    connect(ui->dockWidget, SIGNAL(visibilityChanged(bool)),
            ui->action_Panel, SLOT(setChecked(bool)));
    connect(ui->textCombo->lineEdit(), SIGNAL(returnPressed()),
            ui->renderButton, SLOT(animateClick()));
    connect(ui->renderButton, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->rtlRB, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->ltrRB, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->autoRB, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->resolveScriptsCB, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->breakRunsCB, SIGNAL(clicked()), this, SLOT(render()));

    connect(ui->linesCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->levelsCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->runsCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->codePointsCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->glyphIndicesCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->charTypesCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->scriptsCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->geometriesCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->indicesCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));
    connect(ui->reorderedIndicesCB, SIGNAL(clicked()), this, SLOT(setVisualizerFlags()));

    connect(ui->paragraphCB, SIGNAL(clicked()), this, SLOT(setRendererFlags()));
    connect(ui->levelsGB, SIGNAL(clicked()), this, SLOT(setRendererFlags()));
    connect(ui->runsGB, SIGNAL(clicked()), this, SLOT(setRendererFlags()));
    connect(ui->levelsColorPickerLabel, SIGNAL(colorChanged(QColor)),
            this, SLOT(setRendererLevelColor(QColor)));
    connect(ui->runsColorPickerLabel, SIGNAL(colorChanged(QColor)),
            this, SLOT(setRendererRunColor(QColor)));

    connect(ui->shapeHarfBuzzRB, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->shapeFriBidiRB, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->removeZeroWidthCB, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->shapeFriBidiRB, SIGNAL(toggled(bool)),
            ui->removeZeroWidthCB, SLOT(setEnabled(bool)));

    connect(ui->fontPathButton, SIGNAL(clicked()), this, SLOT(setFontPath()));
    connect(ui->fontsCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setFontFile(QString)));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)),
            ui->graphicsView, SLOT(setScale(int)));
    connect(ui->graphicsView, SIGNAL(scaleChanged(int)),
            ui->zoomSlider, SLOT(setValue(int)));
    connect(ui->lineWidthSlider, SIGNAL(valueChanged(int)),
            this, SLOT(setMaxLineWidth(int)));
    connect(ui->fontSizeSB, SIGNAL(valueChanged(int)),
            this, SLOT(setFontSize(int)));
    connect(ui->fontColorPickerLabel, SIGNAL(colorChanged(QColor)),
            this, SLOT(render()));
    connect(ui->penWidthSB, SIGNAL(valueChanged(int)),
            this, SLOT(setPenWidth(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mGraphicsScene;
    delete mRawGlyphString;
    delete mShapedGlyphString;

    if (mFace && (mFace != mResourceFace)) {
        FT_Done_Face(mFace);
        FT_Done_Face(mResourceFace);
    } else {
        FT_Done_Face(mResourceFace);
    }

    if (mLibrary)
        FT_Done_FreeType(mLibrary);
}

void MainWindow::render()
{
    if (!mFreeTypeInitialized) {
        statusBar()->showMessage("FreeType has not been initialized", messageTimeout);
        return;
    }
    if (!mFace) {
        statusBar()->showMessage("No font selected", messageTimeout);
        return;
    }
    if (ui->textCombo->lineEdit()->text().isEmpty())
        return;

    QTextCodec *codec = QTextCodec::codecForName("UTF-32");
    QByteArray byteArray = codec->fromUnicode(ui->textCombo->lineEdit()->text());

    QFont font("Arial");
    font.setPixelSize(mFontSize / 4);

    delete mRawGlyphString;
    mRawGlyphString = 0;
    delete mShapedGlyphString;
    mShapedGlyphString = 0;

    FriBidiParType parType;
    if (ui->rtlRB->isChecked())
        parType = FRIBIDI_PAR_RTL;
    else if (ui->ltrRB->isChecked())
        parType = FRIBIDI_PAR_LTR;
    else
        parType = FRIBIDI_PAR_ON;

    mRawGlyphString = new GlyphString();
    mRawGlyphString->init(((quint32*) byteArray.constData()) + 1,
                          ui->textCombo->lineEdit()->text().size(),
                          mFace, ui->fontColorPickerLabel->color(),
                          parType, ui->lineWidthSlider->value());
    mShapedGlyphString = new GlyphString();
    mShapedGlyphString->init(((quint32*) byteArray.constData()) + 1,
                             ui->textCombo->lineEdit()->text().size(),
                             mFace, ui->fontColorPickerLabel->color(),
                             parType, ui->lineWidthSlider->value());
    mRawGlyphString->analyze(ui->resolveScriptsCB->isChecked(),
                             ui->breakRunsCB->isChecked());
    mShapedGlyphString->analyze(ui->resolveScriptsCB->isChecked(),
                                ui->breakRunsCB->isChecked());

    if (ui->shapeHarfBuzzRB->isChecked())
        mShapedGlyphString->shapeHarfBuzz();
    else
        mShapedGlyphString->shapeFriBidi(ui->removeZeroWidthCB->isChecked());
    mShapedGlyphString->layout();

    quint32 vFlags = visualizerFlags();
    quint32 rFlags = rendererFlags();

    if (mRendering) {
        mRawVisualizer->reset(mRawGlyphString, mFontSize, mPenWidth,
                              font, vFlags);
        mShapedVisualizer->reset(mShapedGlyphString, mFontSize, mPenWidth,
                                 font, vFlags);
        mShapedRenderer->reset(mShapedGlyphString, mPenWidth,
                               font, rFlags, ui->levelsColorPickerLabel->color(),
                               ui->runsColorPickerLabel->color());

    } else {
        mRawVisualizer = new GlyphStringVisualizer(mRawGlyphString, mFontSize,
                                                   mPenWidth, font, vFlags);
        mShapedVisualizer = new GlyphStringVisualizer(mShapedGlyphString, mFontSize,
                                                      mPenWidth, font, vFlags);
        mShapedRenderer = new GlyphStringRenderer(mShapedGlyphString, mPenWidth,
                                font, rFlags, ui->levelsColorPickerLabel->color(),
                                ui->runsColorPickerLabel->color());

        mRawVisualizer->setFlags(QGraphicsItem::ItemIsSelectable |
                                 QGraphicsItem::ItemIsMovable);
        mShapedVisualizer->setFlags(QGraphicsItem::ItemIsSelectable |
                                    QGraphicsItem::ItemIsMovable);
        mShapedRenderer->setFlags(QGraphicsItem::ItemIsSelectable |
                                  QGraphicsItem::ItemIsMovable);

        mShapedVisualizer->setPos(0, 2 * mRawVisualizer->boundingRect().height());
        mShapedRenderer->setPos(0, 2 * mRawVisualizer->boundingRect().height()
                                 + 2 * mShapedVisualizer->boundingRect().height());

        mGraphicsScene->addItem(mRawVisualizer);
        mGraphicsScene->addItem(mShapedVisualizer);
        mGraphicsScene->addItem(mShapedRenderer);

        mRendering = true;
    }

    update();
}

void MainWindow::setVisualizerFlags()
{
    if (!mRendering)
        return;
    mRawVisualizer->setVisualizerFlags(visualizerFlags());
    mShapedVisualizer->setVisualizerFlags(visualizerFlags());
}

void MainWindow::setRendererFlags()
{
    if (!mRendering)
        return;
    mShapedRenderer->setRendererFlags(rendererFlags());
}

void MainWindow::setRendererLevelColor(QColor color)
{
    if (!mRendering)
        return;
    mShapedRenderer->setLevelArrowColor(color);
}

void MainWindow::setRendererRunColor(QColor color)
{
    if (!mRendering)
        return;
    mShapedRenderer->setRunArrowColor(color);
}

void MainWindow::setFontPath()
{
    QString path = QFileDialog::getExistingDirectory(this,
        "Set fonts directory", mFontPath,
        QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);
    if (path.isEmpty())
        return;
    mFontPath = path;
    ui->fontPathLE->setText(path);
    listFonts();
}

void MainWindow::setFontFile(const QString &fontFile)
{
    if (fontFile.isEmpty())
        return;

    FT_Face newFace;
    if (FT_New_Face(mLibrary, fontFile.toStdString().c_str(), 0, &newFace)) {
        statusBar()->showMessage(QString("Error loading %1")
                                 .arg(fontFile), messageTimeout);
        return;
    }
    if (FT_Set_Pixel_Sizes(newFace, 0, mFontSize)) {
        statusBar()->showMessage(QString("Error setting font size"),
                                 messageTimeout);
        FT_Done_Face(newFace);
        return;
    }
    if (mFace != mResourceFace)
        FT_Done_Face(mFace);
    mFace = newFace;
    render();
}

void MainWindow::setMaxLineWidth(int width)
{
    mShapedGlyphString->setMaxWidth(width);
    mShapedVisualizer->layout();
    mShapedRenderer->layout();
}

void MainWindow::setFontSize(int size)
{
    if (FT_Set_Pixel_Sizes(mFace, 0, size)) {
        statusBar()->showMessage("Error setting font size");
        return;
    }
    mFontSize = size;
    ui->lineWidthSlider->setRange(size * 4, size * 40);
    ui->penWidthSB->setMaximum(size / 10);
    render();
}

void MainWindow::setPenWidth(int width)
{
    mPenWidth = width;
    mRawVisualizer->setPenWidth(width);
    mShapedVisualizer->setPenWidth(width);
    mShapedRenderer->setPenWidth(width);
}

bool MainWindow::loadSamples()
{
    QFile file(":/files/samples.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");

    while(!textStream.atEnd()) {
        QString line = textStream.readLine();
        ui->textCombo->insertItem(ui->textCombo->count(), line);
    }
    return true;
}

bool MainWindow::listFonts()
{
    ui->fontsCombo->clear();
    QStringList nameFilters;
    nameFilters << "*.ttf";
    QDirIterator it(mFontPath, nameFilters, QDir::NoFilter, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        ui->fontsCombo->insertItem(ui->fontsCombo->count(), it.next());
    }
    return true;
}

quint32 MainWindow::visualizerFlags()
{
    quint32 flags = 0;

    if (ui->linesCB->isChecked())
        flags |= GlyphStringVisualizer::LineArrows;
    if (ui->levelsCB->isChecked())
        flags |= GlyphStringVisualizer::LevelArrows;
    if (ui->runsCB->isChecked())
        flags |= GlyphStringVisualizer::RunArrows;
    if (ui->codePointsCB->isChecked())
        flags |= GlyphStringVisualizer::CodePoints;
    if (ui->glyphIndicesCB->isChecked())
        flags |= GlyphStringVisualizer::GlyphIndices;
    if (ui->charTypesCB->isChecked())
        flags |= GlyphStringVisualizer::CharTypes;
    if (ui->scriptsCB->isChecked())
        flags |= GlyphStringVisualizer::Scripts;
    if (ui->geometriesCB->isChecked())
        flags |= GlyphStringVisualizer::Geometries;
    if (ui->indicesCB->isChecked())
        flags |= GlyphStringVisualizer::Indices;
    if (ui->reorderedIndicesCB->isChecked())
        flags |= GlyphStringVisualizer::ReorderedIndices;

    return flags;
}

quint32 MainWindow::rendererFlags()
{
    quint32 flags = 0;
    if (ui->paragraphCB->isChecked())
        flags |= GlyphStringRenderer::ParagraphArrow;
    if (ui->levelsGB->isChecked())
        flags |= GlyphStringRenderer::LevelArrows;
    if (ui->runsGB->isChecked())
        flags |= GlyphStringRenderer::RunArrows;
    return flags;
}
