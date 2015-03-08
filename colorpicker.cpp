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

#include "colorpicker.h"

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets/QColorDialog>
#else
#include <QtGui/QColorDialog>
#endif

ColorPicker::ColorPicker(QWidget *parent) : QLabel(parent), mColor(Qt::black)
{
    updateStyleSheet();
}

ColorPicker::~ColorPicker()
{

}

void ColorPicker::mouseReleaseEvent(QMouseEvent *)
{
    QColor color = QColorDialog::getColor(mColor, this);
    if (color.isValid()) {
        mColor = color;
        updateStyleSheet();
    }
}

void ColorPicker::updateStyleSheet()
{
    QString styleSheetText = QString("background-color: rgb(%1, %2, %3)")
            .arg(mColor.red()).arg(mColor.green()).arg(mColor.blue());
    setStyleSheet(styleSheetText);
    emit colorChanged(mColor);
}

void ColorPicker::setColor(QColor color)
{
    mColor = color;
    updateStyleSheet();
}

QColor ColorPicker::color() const
{
    return mColor;
}
