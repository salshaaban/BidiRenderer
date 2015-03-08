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

#pragma once

#include <qglobal.h>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets/QGraphicsItem>
#else
#include <QtGui/QGraphicsItem>
#endif

#include <QtCore/QVector>
#include <QtGui/QFont>

#include "glyph_string.h"
#include "arrow.h"

class GlyphStringRenderer : public QGraphicsItem
{
public:
    enum RendererFlags
    {
        ParagraphArrow = 1 << 0,
        LevelArrows = 1 << 1,
        RunArrows = 1 << 2
    };

    GlyphStringRenderer(const GlyphString *glyphString, int penWidth,
                        const QFont &font, quint32 flags,
                        QColor levelArrowColor = Qt::black,
                        QColor runArrowColor = Qt::black);
    void reset(const GlyphString *glyphString, int penWidth,
               const QFont &font, quint32 flags,
               QColor levelArrowColor = Qt::black,
               QColor runArrowColor = Qt::black);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void layout();
    void clear();
    void setGlyphString(const GlyphString *glyphString);
    void setLevelArrowColor(QColor color);
    void setRunArrowColor(QColor color);
    void setRendererFlags(quint32 flags);
    void setPenWidth(int width);

protected:
    const GlyphString *mGlyphString;
    int mPenWidth;
    QFont mFont;
    quint32 mFlags;
    QRectF mBoundingRect;
    QColor mLevelArrowColor;
    QColor mRunArrowColor;

    QVector<Arrow> mArrows;
    QVector<QPoint> mImagePositions;
    QVector<int> mImageIndices;
};
