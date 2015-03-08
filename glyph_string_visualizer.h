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

class GlyphStringVisualizer : public QGraphicsItem
{
public:
    enum VisualizerFlags
    {
        LineArrows = 1 << 0,
        LevelArrows = 1 << 1,
        RunArrows = 1 << 2,
        CodePoints = 1 << 3,
        GlyphIndices = 1 << 4,
        CharTypes = 1 << 5,
        Scripts = 1 << 6,
        Geometries = 1 << 7,
        Indices = 1 << 8,
        ReorderedIndices = 1 << 9
    };

    GlyphStringVisualizer(const GlyphString *glyphString, int characterSize,
                          int penWidth, const QFont &font, quint32 flags);
    void reset(const GlyphString *glyphString, int characterSize,
               int penWidth, const QFont &font, quint32 flags);
    void clear();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void layout();
    void addTextItem(const QFontMetrics &fontMetrics, int x, int y,
                     int totalWidth, int totalHeight, const QString &text,
                     const QString &toolTip = QString());
    void setGlyphString(const GlyphString *glyphString);
    void setPenWidth(int penWidth);
    void setVisualizerFlags(quint32 flags);

protected:
    const GlyphString *mGlyphString;
    int mCharacterSize;
    int mPenWidth;
    QFont mFont;
    quint32 mFlags;
    QRectF mBoundingRect;

    QVector<Arrow> mArrows;
    QVector<QPoint> mImagePositions;
    QVector<QRect> mCells;
};
