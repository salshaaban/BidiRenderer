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

#include <QtGui/QFont>
#include <QtCore/QString>
#include <QtCore/QLine>
#include <QtGui/QPolygon>
#include <QtGui/QColor>

class QPainter;

class Arrow
{
public:
    static const float Sin45;
    static const float Cos45;

    Arrow();
    Arrow(const QFont &font, const QString &text,
          int penWidth, int x1, int x2, int y, bool rtl, QColor color = Qt::black);
    void init(const QFont &font, const QString &text,
              int penWidth, int x1, int x2, int y, bool rtl, QColor color = Qt::black);
    void paint(QPainter *painter);
    int height() const { return mHeight; }

protected:
    QFont mFont;
    QString mText;
    QPoint mTextPosition;
    int mPenWidth;
    int mArrowSize;
    int mHeight;
    int mX1;
    int mX2;
    int mY;
    bool mRtl;
    QLine mLine;
    QPolygon mArrowHead;
    QColor mColor;
};
