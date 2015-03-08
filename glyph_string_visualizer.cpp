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

#include "glyph_string_visualizer.h"

#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets/QGraphicsSimpleTextItem>
#else
#include <QtGui/QGraphicsSimpleTextItem>
#endif

GlyphStringVisualizer::GlyphStringVisualizer(const GlyphString *glyphString,
                                             int characterSize,
                                             int penWidth, const QFont &font,
                                             quint32 flags)
    : mGlyphString(glyphString), mCharacterSize(characterSize),
      mPenWidth(penWidth), mFont(font), mFlags(flags)
{
    layout();
}

void GlyphStringVisualizer::reset(const GlyphString *glyphString, int characterSize,
                                  int penWidth, const QFont &font, quint32 flags)
{
    mGlyphString = glyphString;
    mCharacterSize = characterSize;
    mPenWidth = penWidth;
    mFont = font;
    mFlags = flags;

    layout();
}

void GlyphStringVisualizer::setGlyphString(const GlyphString *glyphString)
{
    mGlyphString = glyphString;
    layout();
}

void GlyphStringVisualizer::setPenWidth(int penWidth)
{
    mPenWidth = penWidth;
    layout();
}

void GlyphStringVisualizer::setVisualizerFlags(quint32 flags)
{
    mFlags = flags;
    layout();
}

void GlyphStringVisualizer::clear()
{
    mCells.clear();
    mArrows.clear();
    mImagePositions.clear();

    QList<QGraphicsItem *> children = childItems();
    for (int i = children.size() - 1; i >= 0; --i)
        delete children[i];
}

QRectF GlyphStringVisualizer::boundingRect() const
{
    return mBoundingRect;
}

void GlyphStringVisualizer::paint(QPainter *painter,
                                  const QStyleOptionGraphicsItem *,
                                  QWidget *)
{

    QPen pen;
    pen.setWidth(mPenWidth);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    for (int i = 0; i < mCells.size(); ++i)
        painter->drawRect(mCells[i]);

    for (int i = 0; i < mArrows.size(); ++i)
        mArrows[i].paint(painter);

    for (int i = 0; i < mImagePositions.size(); ++i)
        painter->drawImage(mImagePositions[i].x(), mImagePositions[i].y(),
                           mGlyphString->image(i));

}

void GlyphStringVisualizer::layout()
{
    prepareGeometryChange();
    clear();

    if (mGlyphString->state() == GlyphString::Invalid)
        return;

    QFontMetrics fontMetrics(mFont);
    int fontHeight = fontMetrics.height();
    int cellWidth = mCharacterSize + mPenWidth;
    int cellHeight = mCharacterSize + 2 * mPenWidth;
    int margin = fontMetrics.width("Make the margin big enough");
    int x = 0;
    int y = 0;
    Arrow tempArrow(mFont, "text", mPenWidth, 0, 1000, 0, false);

    int lineArrowY = y;
    int arrowHeight = qMax(tempArrow.height(), fontHeight);
    if (mFlags & LineArrows) y += arrowHeight;

    int levelArrowY = y;
    if (mFlags & LevelArrows) y += arrowHeight;

    int runArrowY = y;
    if (mFlags & RunArrows) y += arrowHeight;

    int cellsY = y;
    y += cellHeight;

    int codePointsY = y;
    if (mFlags & CodePoints) y += fontHeight;

    int glyphIndicesY = y;
    if (mFlags & GlyphIndices) y += fontHeight;

    int charTypesY = y;
    if (mFlags & CharTypes) y += fontHeight;

    int scriptsY = y;
    if (mFlags & Scripts) y += fontHeight;

    int leftsY = 0, topsY = 0, xOffsetsY = 0,
        yOffsetsY = 0, xAdvancesY = 0, yAdvancesY = 0;

    if (mFlags & Geometries) {
        leftsY = y;
        y += fontHeight;

        topsY = y;
        y += fontHeight;

        xOffsetsY = y;
        y += fontHeight;

        yOffsetsY = y;
        y += fontHeight;

        xAdvancesY = y;
        y += fontHeight;

        yAdvancesY = y;
        y += fontHeight;
    }

    int indicesY = y;
    if (mFlags & Indices) y += fontHeight;

    int reorderedIndicesY = y;
    if (mFlags & ReorderedIndices) y += fontHeight;

    // Lay out the margin
    if (mFlags & LineArrows)
        addTextItem(fontMetrics, 0, lineArrowY, margin, arrowHeight, "Lines:");
    if (mFlags & LevelArrows)
        addTextItem(fontMetrics, 0, levelArrowY, margin, arrowHeight, "Levels:");
    if (mFlags & RunArrows)
        addTextItem(fontMetrics, 0, runArrowY, margin, arrowHeight, "Runs:");
    addTextItem(fontMetrics, 0, cellsY, margin, cellHeight,
                "Glyphs:");
    if (mFlags & CodePoints)
        addTextItem(fontMetrics, 0, codePointsY, margin, fontHeight, "Code Point:");
    if (mFlags & GlyphIndices)
        addTextItem(fontMetrics, 0, glyphIndicesY, margin, fontHeight, "Glyph Index:");
    if (mFlags & CharTypes)
        addTextItem(fontMetrics, 0, charTypesY, margin, fontHeight, "Bidi Char Type:");
    if (mFlags & Scripts)
        addTextItem(fontMetrics, 0, scriptsY, margin, fontHeight, "Script:");
    if (mFlags & Geometries) {
        addTextItem(fontMetrics, 0, leftsY, margin, fontHeight, "Left:");
        addTextItem(fontMetrics, 0, topsY, margin, fontHeight, "Top:");
        addTextItem(fontMetrics, 0, xOffsetsY, margin, fontHeight, "X Offset:");
        addTextItem(fontMetrics, 0, yOffsetsY, margin, fontHeight, "Y Offset:");
        addTextItem(fontMetrics, 0, xAdvancesY, margin, fontHeight, "X Advance:");
        addTextItem(fontMetrics, 0, yAdvancesY, margin, fontHeight, "Y Advance:");
    }
    if (mFlags & Indices)
        addTextItem(fontMetrics, 0, indicesY, margin, fontHeight, "Index:");
    if (mFlags & ReorderedIndices)
        addTextItem(fontMetrics, 0, reorderedIndicesY, margin, fontHeight, "Reordered Index:");

    int height = y;
    x = margin + mPenWidth / 2;
    y = cellsY + mPenWidth / 2;

    int lastRun = mGlyphString->run(0);
    int lastRunStart = 0;
    int lastLevel = mGlyphString->level(0);
    int lastLevelStart = 0;
    int lastLine = mGlyphString->line(0);
    int lastLineStart = 0;

    for (int i = 0; i <= mGlyphString->size(); ++i) {
        int currentX = x + i * cellWidth;
        if ((mFlags & RunArrows) && (i == mGlyphString->size()
             || mGlyphString->run(i) != lastRun))
        {
            QString arrowText = QString("%1").arg(lastRun);
            Arrow arrow(mFont, arrowText, mPenWidth,
                        x + lastRunStart * cellWidth,
                        x + i * cellWidth, runArrowY, false);
            mArrows.push_back(arrow);
            if ( i < mGlyphString->size() ) {
                lastRun = mGlyphString->run(i);
                lastRunStart = i;
            }
        }

        if ((mFlags & LevelArrows) && (i == mGlyphString->size()
             || mGlyphString->level(i) != lastLevel))
        {
            QString arrowText = QString("%1").arg(lastLevel);
            Arrow arrow(mFont, arrowText, mPenWidth,
                        x + lastLevelStart * cellWidth,
                        x + i * cellWidth, levelArrowY, false);
            mArrows.push_back(arrow);
            if ( i < mGlyphString->size() ) {
                lastLevel = mGlyphString->level(i);
                lastLevelStart = i;
            }
        }

        if ((mFlags & LineArrows) && (i == mGlyphString->size()
             || mGlyphString->line(i) != lastLine))
        {
            if ( lastLine != -1 ) {
                QString arrowText = QString("%1").arg(lastLine);
                Arrow arrow(mFont, arrowText, mPenWidth,
                            x + lastLineStart * cellWidth,
                            x + i * cellWidth, lineArrowY, false);
                mArrows.push_back(arrow);
            }
            if ( i < mGlyphString->size() ) {
                lastLine = mGlyphString->line(i);
                lastLineStart = i;
            }
        }

        if ( i == mGlyphString->size() )
            break;

        QRect cell(currentX, y, cellWidth, cellWidth);
        mCells.push_back(cell);

        int imageX = currentX
            + (cellWidth - mGlyphString->image(i).width()) / 2;
        int imageY = y
            + (cellWidth - mGlyphString->image(i).height()) / 2;
        mImagePositions.push_back(QPoint(imageX, imageY));

        QString text;
        QString toolTip;

        if (mFlags & CodePoints) {
            text = text.sprintf("0x%04x", mGlyphString->codePoint(i));
            addTextItem(fontMetrics, currentX, codePointsY,
                        cellWidth, fontHeight, text);
        }
        if (mFlags & GlyphIndices) {
            text = QString("%1").arg(mGlyphString->glyphIndex(i));
            addTextItem(fontMetrics, currentX, glyphIndicesY,
                        cellWidth, fontHeight, text);
        }
        if (mFlags & CharTypes) {
            text = mGlyphString->charTypeShortText(i);
            toolTip = mGlyphString->charTypeLongText(i);
            addTextItem(fontMetrics, currentX, charTypesY,
                        cellWidth, fontHeight, text, toolTip);
        }
        if (mFlags & Scripts) {
            text = mGlyphString->scriptShortText(i);
            toolTip = mGlyphString->scriptLongText(i);
            addTextItem(fontMetrics, currentX, scriptsY,
                        cellWidth, fontHeight, text, toolTip);
        }
        if (mFlags & Geometries) {
            text = QString("%1").arg(mGlyphString->geometry(i).left);
            addTextItem(fontMetrics, currentX, leftsY,
                        cellWidth, fontHeight, text);
            text = QString("%1").arg(mGlyphString->geometry(i).top);
            addTextItem(fontMetrics, currentX, topsY,
                        cellWidth, fontHeight, text);
            text = QString("%1").arg(mGlyphString->geometry(i).xOffset);
            addTextItem(fontMetrics, currentX, xOffsetsY,
                        cellWidth, fontHeight, text);
            text = QString("%1").arg(mGlyphString->geometry(i).yOffset);
            addTextItem(fontMetrics, currentX, yOffsetsY,
                        cellWidth, fontHeight, text);
            text = QString("%1").arg(mGlyphString->geometry(i).xAdvance);
            addTextItem(fontMetrics, currentX, xAdvancesY,
                        cellWidth, fontHeight, text);
            text = QString("%1").arg(mGlyphString->geometry(i).yAdvance);
            addTextItem(fontMetrics, currentX, yAdvancesY,
                        cellWidth, fontHeight, text);
        }
        if (mFlags & Indices) {
            text = QString("%1").arg(i);
            addTextItem(fontMetrics, currentX, indicesY,
                        cellWidth, fontHeight, text);
        }
        if (mFlags & ReorderedIndices) {
            text = QString("%1").arg(mGlyphString->reorderedIndex(i));
            addTextItem(fontMetrics, currentX, reorderedIndicesY,
                        cellWidth, fontHeight, text);
        }
    }

    mBoundingRect = QRectF(0, 0, margin + mGlyphString->size() * cellWidth
                           + mPenWidth,
                           height);
    update();

}

void GlyphStringVisualizer::addTextItem(const QFontMetrics &fontMetrics,
                                        int x, int y,
                                        int totalWidth, int totalHeight,
                                        const QString &text,
                                        const QString &toolTip)
{
    QGraphicsSimpleTextItem *item;
    int textWidth = fontMetrics.width(text);

    item = new QGraphicsSimpleTextItem(this);
    item->setFont(mFont);
    item->setText(text);
    if (!toolTip.isEmpty())
        item->setToolTip(toolTip);
    item->setPos(x + (totalWidth - textWidth) / 2,
                 y + (totalHeight - fontMetrics.height()) / 2);
}
