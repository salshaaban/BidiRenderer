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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qglobal.h>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#else
#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>
#endif

#include "glyph_string.h"
#include "glyph_string_visualizer.h"
#include "glyph_string_renderer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void render();
    void setVisualizerFlags();
    void setRendererFlags();
    void setRendererLevelColor(QColor color);
    void setRendererRunColor(QColor color);
    void setFontPath();
    void setFontFile(const QString &fontFile);
    void setMaxLineWidth(int width);
    void setFontSize(int size);
    void setPenWidth(int width);

protected:
    static const int messageTimeout = 5000;
    bool loadSamples();
    bool listFonts();
    quint32 visualizerFlags();
    quint32 rendererFlags();

    QGraphicsScene *mGraphicsScene;
    QString mFontPath;
    bool mFreeTypeInitialized;
    bool mRendering;
    FT_Library mLibrary;
    FT_Face mFace;
    FT_Face mResourceFace;
    QByteArray mResourceFaceData;
    int mFontSize;
    int mPenWidth;
    GlyphString *mRawGlyphString;
    GlyphString *mShapedGlyphString;
    GlyphStringVisualizer *mRawVisualizer;
    GlyphStringVisualizer *mShapedVisualizer;
    GlyphStringRenderer *mShapedRenderer;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
