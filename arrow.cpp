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

#include "arrow.h"

const float Arrow::Sin45 = 0.707106781f;
const float Arrow::Cos45 = 0.707106781f;

Arrow::Arrow() : mPenWidth(0), mArrowSize(0), mHeight(0),
                 mX1(0), mX2(0), mY(0), mRtl(false)
{
}

Arrow::Arrow(const QFont &font, const QString &text, int penWidth,
             int x1, int x2, int y, bool rtl, QColor color)
{
    init(font, text, penWidth, x1, x2, y, rtl, color);
}

void Arrow::init(const QFont &font, const QString &text, int penWidth,
                 int x1, int x2, int y, bool rtl, QColor color)
{
    mFont = font;
    mText = text;
    mPenWidth = penWidth;
    if (x2 - x1 >= 2 * penWidth) {
        x1 += penWidth;
        x2 -= penWidth;
    }
    mY = y;
    mColor = color;

    mArrowSize = 2 * mPenWidth;
    QFontMetrics fontMetrics(mFont);

    mHeight = mArrowSize > fontMetrics.height() ?
        2 * mPenWidth + 2 * mArrowSize:
        2 * mPenWidth + fontMetrics.height() + mArrowSize;

    mY = mY + mHeight / 2;
    QPoint p1;
    QPoint p2;
    if (rtl) {
        mX1 = x2;
        mX2 = x1;
        p1.setX(mX2 + (mArrowSize * Cos45));
        p1.setY(mY + (mArrowSize * Sin45));
        p2.setX(mX2 + (mArrowSize * Cos45));
        p2.setY(mY - (mArrowSize * Sin45));
    } else {
        mX1 = x1;
        mX2 = x2;
        p1.setX(mX2 - (mArrowSize * Cos45));
        p1.setY(mY + (mArrowSize * Sin45));
        p2.setX(mX2 - (mArrowSize * Cos45));
        p2.setY(mY - (mArrowSize * Sin45));
    }
    mLine = QLine(mX1, mY, mX2, mY);

    mArrowHead << QPoint(mX2, mY) << p1 << p2;
    mTextPosition.setX(mX1 + (mX2 - mX1 - fontMetrics.width(text)) / 2);
    mTextPosition.setY(mY - mPenWidth);
}

void Arrow::paint(QPainter *painter)
{
    QPen pen;
    pen.setWidth(mPenWidth);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(mColor);

    painter->save();

    painter->setPen(pen);
    painter->setBrush(mColor);
    painter->setFont(mFont);

    painter->drawLine(mLine);
    painter->drawPolygon(mArrowHead);
    painter->drawText(mTextPosition.x(), mTextPosition.y(), mText);

    painter->restore();
}
