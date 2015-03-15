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

#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>
#include <assert.h>

#include "glyph_string_renderer.h"

GlyphStringRenderer::GlyphStringRenderer(const GlyphString *glyphString,
                                         int penWidth, const QFont &font,
                                         quint32 flags, QColor levelArrowColor,
                                         QColor runArrowColor)
    : mGlyphString(glyphString), mPenWidth(penWidth),
      mFont(font), mFlags(flags), mLevelArrowColor(levelArrowColor),
      mRunArrowColor(runArrowColor)
{
    layout();
}

void GlyphStringRenderer::reset(const GlyphString *glyphString,
                                int penWidth, const QFont &font,
                                quint32 flags, QColor levelArrowColor,
                                QColor runArrowColor)
{
    mGlyphString = glyphString;
    mPenWidth = penWidth;
    mFont = font;
    mFlags = flags;
    mLevelArrowColor = levelArrowColor;
    mRunArrowColor = runArrowColor;
    layout();
}

QRectF GlyphStringRenderer::boundingRect() const
{
    return mBoundingRect;
}

void GlyphStringRenderer::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *,
                                QWidget *)
{
    for (int i = 0; i < mArrows.size(); ++i)
        mArrows[i].paint(painter);

    for (int i = 0; i < mImageIndices.size(); ++i) {
        const QImage &image = mGlyphString->image(mImageIndices[i]);
        QPoint &p = mImagePositions[i];
        painter->drawImage(p.x(), p.y(), image);
    }
}

void GlyphStringRenderer::layout()
{
    int width = 0;
    int height = 0;
    int lineHeight = 0;
    int x = 0;
    int y = 0;

    prepareGeometryChange();
    clear();

    if (mGlyphString->state() < GlyphString::LaidOut)
        return;

    for (int i = 0; i < mGlyphString->lineInfos().size(); ++i) {
        width = qMax(width, mGlyphString->lineInfos()[i].width);
        lineHeight = qMax(lineHeight, mGlyphString->lineInfos()[i].height);
        height += mGlyphString->lineInfos()[i].height;
    }
    width += 10 * mPenWidth;

    QString paragraphText = mGlyphString->paragraphType() == FRIBIDI_PAR_RTL ?
        QString("Paragraph base direction: RTL"):
        QString("Paragraph base direction: LTR");
    QFontMetrics fontMetrics(mFont);
    width = qMax(width, fontMetrics.width(paragraphText + QString("****")));

    Arrow paragraphArrow;
    if (mGlyphString->paragraphType() == FRIBIDI_PAR_RTL)
        paragraphArrow.init(mFont, paragraphText, mPenWidth,
                            mPenWidth / 2, width - mPenWidth / 2, y, true);
    else
        paragraphArrow.init(mFont, paragraphText, mPenWidth,
                            mPenWidth / 2, width - mPenWidth / 2, y, false);

    if (mFlags & ParagraphArrow) {
        mArrows.push_back(paragraphArrow);
        y += paragraphArrow.height();
    }

    for (int i = 0; i < mGlyphString->lineInfos().size(); ++i) {
        const LineInfo &lineInfo = mGlyphString->lineInfos()[i];
        int levelArrowY = y;
        if (mFlags & LevelArrows)
            y += paragraphArrow.height();
        int runArrowY = y;
        if (mFlags & RunArrows)
            y += paragraphArrow.height();

        y += lineInfo.ascent;
        x = (width - lineInfo.width) / 2;
        x -= lineInfo.left;

        int offset = mGlyphString->reorderedIndex(lineInfo.startOffset);

        int lastRun = mGlyphString->run(offset);
        int lastRunX = x;
        int lastLevel = mGlyphString->level(offset);
        int lastLevelX = x;
        bool lastRunRTL = mGlyphString->runInfos()[lastRun]
                .direction == HB_DIRECTION_RTL;
        bool lastLevelRTL = lastLevel & 1;

        for (int j = lineInfo.startOffset; j < lineInfo.endOffset; ++j) {
            offset = mGlyphString->reorderedIndex(j);
            const Geometry &geometry = mGlyphString->geometry(offset);
            QPoint p;
            p.setX(x + geometry.left + geometry.xOffset);
            p.setY(y - geometry.top - geometry.yOffset);

            if ((mFlags & RunArrows) && (lastRun != mGlyphString->run(offset))) {
                mArrows.push_back(Arrow(mFont, QString("%1").arg(lastRun), mPenWidth,
                    lastRunX, x, runArrowY, lastRunRTL, mRunArrowColor));
                lastRun = mGlyphString->run(offset);
                lastRunX = x;
                lastRunRTL = mGlyphString->runInfos()[lastRun]
                        .direction == HB_DIRECTION_RTL;
            }

            if ((mFlags & LevelArrows)
                    && (lastLevel != mGlyphString->level(offset)))
            {
                mArrows.push_back(Arrow(mFont, QString("%1").arg(lastLevel), mPenWidth,
                         lastLevelX, x, levelArrowY, lastLevelRTL, mLevelArrowColor));
                lastLevel = mGlyphString->level(offset);
                lastLevelX = x;
                lastLevelRTL = lastLevel & 1;
            }

            assert(p.x() >= 0);
            assert(p.x() + mGlyphString->image(offset).width() <= width);
            mImagePositions.push_back(p);
            mImageIndices.push_back(offset);
            x += geometry.xAdvance;
        }

        if (mFlags & RunArrows) {
            mArrows.push_back(Arrow(mFont, QString("%1").arg(lastRun), mPenWidth,
                lastRunX, x, runArrowY, lastRunRTL, mRunArrowColor));
        }

        if (mFlags & LevelArrows) {
            mArrows.push_back(Arrow(mFont, QString("%1").arg(lastLevel), mPenWidth,
                lastLevelX, x, levelArrowY, lastLevelRTL, mLevelArrowColor));
        }

        y -= lineInfo.ascent;
        y += lineHeight;
    }

    mBoundingRect = QRectF(0, 0, width, y);
    update();
}

void GlyphStringRenderer::clear()
{
    mArrows.clear();
    mImagePositions.clear();
    mImageIndices.clear();
}

void GlyphStringRenderer::setGlyphString(const GlyphString *glyphString)
{
    mGlyphString = glyphString;
    layout();
}

void GlyphStringRenderer::setLevelArrowColor(QColor color)
{
    mLevelArrowColor = color;
    layout();
}

void GlyphStringRenderer::setRunArrowColor(QColor color)
{
    mRunArrowColor = color;
    layout();
}

void GlyphStringRenderer::setRendererFlags(quint32 flags)
{
    mFlags = flags;
    layout();
}

void GlyphStringRenderer::setPenWidth(int width)
{
    mPenWidth = width;
    layout();
}
