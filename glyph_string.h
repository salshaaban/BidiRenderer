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

#include <QtGui/QImage>
#include <QtCore/QVector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <fribidi.h>

#include <hb.h>
#include <hb-ft.h>

#include <assert.h>

struct Geometry
{
    int left;
    int top;
    int xOffset;
    int yOffset;
    int xAdvance;
    int yAdvance;

    Geometry() : left(0), top(0), xOffset(0), yOffset(0),
                 xAdvance(0), yAdvance(0)
    {
    }
};

struct LineInfo
{
    int startOffset;
    int endOffset;
    int width;
    int height;
    int ascent;
    int descent;
    int left;

    LineInfo() : startOffset(0), endOffset(0), width(0), height(0),
                 ascent(0), descent(0), left(0)
    {
    }
};

struct RunInfo
{
    int startOffset;
    int endOffset;
    hb_buffer_t *buffer;
    hb_direction_t direction;
    hb_script_t script;
    unsigned int glyphCount;
    hb_glyph_info_t *glyphInfos;
    hb_glyph_position_t *glyphPositions;

    RunInfo() : startOffset(0), endOffset(0), buffer(0),
                glyphCount(0), glyphInfos(0), glyphPositions(0)
    {
    }
};

class GlyphString
{
public:
    enum State
    {
        Invalid = 0,
        Initialized = 1,
        Analyzed = 2,
        Shaped = 3,
        LaidOut = 4
    };

    GlyphString();
    ~GlyphString();
    bool init(quint32 *codePoints, int size, FT_Face face,
             FriBidiParType parType, int maxWidth);
    bool analyze(bool resolveScripts = true, bool breakOnLevelChange = false);
    bool shapeHarfBuzz();
    bool shapeFriBidi(bool removeInvisibleCharacters = true);
    bool reorderLine(int startOffset, int endOffset);
    bool layout();
    LineInfo newLine(int startOffset, int endOffset, int lineNo);
    void clearGlyph(int index);
    bool loadGlyphImages(bool useGlyphIndices = false, bool keepXAdvance = false);

    const QVector<LineInfo> & lineInfos() const { return mLineInfos; }
    const QVector<RunInfo> & runInfos() const { return mRunInfos; }
    int size() const { return mSize; }

    quint32 codePoint(int index) const
    {
        assert(index >= 0 && index < mSize);
        return mCodePoints[index];
    }

    int glyphIndex(int index) const
    {
        assert(index >= 0 && index < mSize);
        return mGlyphIndices[index];
    }

    const QImage & image(int index) const
    {
        assert(index >= 0 && index < mSize);
        return mImages[index];
    }

    const Geometry & geometry(int index) const
    {
        assert(index >= 0 && index < mSize);
        return mGeometries[index];
    }

    FriBidiLevel level(int index) const
    {
        if (mState < Analyzed)
            return 0;
        assert(index >= 0 && index < mSize);
        return mLevels[index];
    }

    int run(int index) const
    {
        if (mState < Analyzed)
            return 0;
        assert(index >= 0 && index < mSize);
        return mRuns[index];
    }

    int line(int index) const
    {
        if (mState < LaidOut)
            return 0;
        assert(index >= 0 && index < mSize);
        return mLines[index];
    }

    void setMaxWidth(int maxWidth)
    {
        mMaxWidth = maxWidth;
        layout();
    }

    QString scriptShortText(int index) const;
    QString scriptLongText(int index) const;
    QString charTypeShortText(int index) const;
    QString charTypeLongText(int index) const;

    FriBidiStrIndex reorderedIndex(int index) const
    {
        assert(index >= 0 && index < mSize);
        return mMap[index];
    }

    FriBidiParType paragraphType() const
    {
        return mParType;
    }

    int state() const
    {
        return mState;
    }

protected:
    FT_Face mFace;
    QVector<LineInfo> mLineInfos;
    QVector<RunInfo> mRunInfos;
    int mSize;
    quint32 *mCodePoints;
    int *mGlyphIndices;
    QImage *mImages;
    Geometry *mGeometries;
    int *mRuns;
    int *mLines;
    int mMaxWidth;
    hb_script_t *mScripts;
    FriBidiCharType *mTypes;
    FriBidiLevel *mLevels;
    FriBidiStrIndex *mMap;
    FriBidiParType mParType;
    int mState;

private:
    GlyphString(const GlyphString &);
    GlyphString & operator=(const GlyphString &);
};
