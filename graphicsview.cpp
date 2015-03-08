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

#include <QtGui/QWheelEvent>

#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent), mScale(1.0)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setDragMode(ScrollHandDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    if (event->delta() > 0)
        mScale *= 1.15;
    else
        mScale /= 1.15;

    mScale = qMax(0.01, qMin(mScale, 3.0));
    setScale(mScale);
}

void GraphicsView::setScale(int scale)
{
    if (mScale * 1000 == scale)
        return;
    setScale(static_cast<qreal>(scale) / 1000);
}

void GraphicsView::setScale(qreal scale)
{
    mScale = scale;
    QTransform transform;
    setTransform(transform.scale(mScale, mScale));
    emit scaleChanged(scale * 1000);
}
