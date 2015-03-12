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

#include <assert.h>

#include "glyph_string.h"

QString scriptShortText(hb_script_t script)
{
    char buffer[5] = {0};
    hb_tag_to_string(script, buffer);
    return QString(buffer);
}

QString scriptLongText(hb_script_t script)
{
    switch (script) {
    case HB_SCRIPT_COMMON: return QString("HB_SCRIPT_COMMON");
    case HB_SCRIPT_INHERITED: return QString("HB_SCRIPT_INHERITED");
    case HB_SCRIPT_UNKNOWN: return QString("HB_SCRIPT_UNKNOWN");
    case HB_SCRIPT_ARABIC: return QString("HB_SCRIPT_ARABIC");
    case HB_SCRIPT_ARMENIAN: return QString("HB_SCRIPT_ARMENIAN");
    case HB_SCRIPT_BENGALI: return QString("HB_SCRIPT_BENGALI");
    case HB_SCRIPT_CYRILLIC: return QString("HB_SCRIPT_CYRILLIC");
    case HB_SCRIPT_DEVANAGARI: return QString("HB_SCRIPT_DEVANAGARI");
    case HB_SCRIPT_GEORGIAN: return QString("HB_SCRIPT_GEORGIAN");
    case HB_SCRIPT_GREEK: return QString("HB_SCRIPT_GREEK");
    case HB_SCRIPT_GUJARATI: return QString("HB_SCRIPT_GUJARATI");
    case HB_SCRIPT_GURMUKHI: return QString("HB_SCRIPT_GURMUKHI");
    case HB_SCRIPT_HANGUL: return QString("HB_SCRIPT_HANGUL");
    case HB_SCRIPT_HAN: return QString("HB_SCRIPT_HAN");
    case HB_SCRIPT_HEBREW: return QString("HB_SCRIPT_HEBREW");
    case HB_SCRIPT_HIRAGANA: return QString("HB_SCRIPT_HIRAGANA");
    case HB_SCRIPT_KANNADA: return QString("HB_SCRIPT_KANNADA");
    case HB_SCRIPT_KATAKANA: return QString("HB_SCRIPT_KATAKANA");
    case HB_SCRIPT_LAO: return QString("HB_SCRIPT_LAO");
    case HB_SCRIPT_LATIN: return QString("HB_SCRIPT_LATIN");
    case HB_SCRIPT_MALAYALAM: return QString("HB_SCRIPT_MALAYALAM");
    case HB_SCRIPT_ORIYA: return QString("HB_SCRIPT_ORIYA");
    case HB_SCRIPT_TAMIL: return QString("HB_SCRIPT_TAMIL");
    case HB_SCRIPT_TELUGU: return QString("HB_SCRIPT_TELUGU");
    case HB_SCRIPT_THAI: return QString("HB_SCRIPT_THAI");
    case HB_SCRIPT_TIBETAN: return QString("HB_SCRIPT_TIBETAN");
    case HB_SCRIPT_BOPOMOFO: return QString("HB_SCRIPT_BOPOMOFO");
    case HB_SCRIPT_BRAILLE: return QString("HB_SCRIPT_BRAILLE");
    case HB_SCRIPT_CANADIAN_SYLLABICS: return QString("HB_SCRIPT_CANADIAN_SYLLABICS");
    case HB_SCRIPT_CHEROKEE: return QString("HB_SCRIPT_CHEROKEE");
    case HB_SCRIPT_ETHIOPIC: return QString("HB_SCRIPT_ETHIOPIC");
    case HB_SCRIPT_KHMER: return QString("HB_SCRIPT_KHMER");
    case HB_SCRIPT_MONGOLIAN: return QString("HB_SCRIPT_MONGOLIAN");
    case HB_SCRIPT_MYANMAR: return QString("HB_SCRIPT_MYANMAR");
    case HB_SCRIPT_OGHAM: return QString("HB_SCRIPT_OGHAM");
    case HB_SCRIPT_RUNIC: return QString("HB_SCRIPT_RUNIC");
    case HB_SCRIPT_SINHALA: return QString("HB_SCRIPT_SINHALA");
    case HB_SCRIPT_SYRIAC: return QString("HB_SCRIPT_SYRIAC");
    case HB_SCRIPT_THAANA: return QString("HB_SCRIPT_THAANA");
    case HB_SCRIPT_YI: return QString("HB_SCRIPT_YI");
    //case HB_SCRIPT_DESERT: return QString("HB_SCRIPT_DESERT");
    case HB_SCRIPT_GOTHIC: return QString("HB_SCRIPT_GOTHIC");
    case HB_SCRIPT_OLD_ITALIC: return QString("HB_SCRIPT_OLD_ITALIC");
    case HB_SCRIPT_BUHID: return QString("HB_SCRIPT_BUHID");
    case HB_SCRIPT_HANUNOO: return QString("HB_SCRIPT_HANUNOO");
    case HB_SCRIPT_TAGALOG: return QString("HB_SCRIPT_TAGALOG");
    case HB_SCRIPT_TAGBANWA: return QString("HB_SCRIPT_TAGBANWA");
    case HB_SCRIPT_CYPRIOT: return QString("HB_SCRIPT_CYPRIOT");
    case HB_SCRIPT_LIMBU: return QString("HB_SCRIPT_LIMBU");
    case HB_SCRIPT_LINEAR_B: return QString("HB_SCRIPT_LINEAR_B");
    case HB_SCRIPT_OSMANYA: return QString("HB_SCRIPT_OSMANYA");
    case HB_SCRIPT_SHAVIAN: return QString("HB_SCRIPT_SHAVIAN");
    case HB_SCRIPT_TAI_LE: return QString("HB_SCRIPT_TAI_LE");
    case HB_SCRIPT_UGARITIC: return QString("HB_SCRIPT_UGARITIC");
    case HB_SCRIPT_BUGINESE: return QString("HB_SCRIPT_BUGINESE");
    case HB_SCRIPT_COPTIC: return QString("HB_SCRIPT_COPTIC");
    case HB_SCRIPT_GLAGOLITIC: return QString("HB_SCRIPT_GLAGOLITIC");
    case HB_SCRIPT_KHAROSHTHI: return QString("HB_SCRIPT_KHAROSHTHI");
    case HB_SCRIPT_NEW_TAI_LUE: return QString("HB_SCRIPT_NEW_TAI_LUE");
    case HB_SCRIPT_OLD_PERSIAN: return QString("HB_SCRIPT_OLD_PERSIAN");
    case HB_SCRIPT_SYLOTI_NAGRI: return QString("HB_SCRIPT_SYLOTI_NAGRI");
    case HB_SCRIPT_TIFINAGH: return QString("HB_SCRIPT_TIFINAGH");
    case HB_SCRIPT_BALINESE: return QString("HB_SCRIPT_BALINESE");
    case HB_SCRIPT_CUNEIFORM: return QString("HB_SCRIPT_CUNEIFORM");
    case HB_SCRIPT_NKO: return QString("HB_SCRIPT_NKO");
    case HB_SCRIPT_PHAGS_PA: return QString("HB_SCRIPT_PHAGS_PA");
    case HB_SCRIPT_PHOENICIAN: return QString("HB_SCRIPT_PHOENICIAN");
    case HB_SCRIPT_CARIAN: return QString("HB_SCRIPT_CARIAN");
    case HB_SCRIPT_CHAM: return QString("HB_SCRIPT_CHAM");
    case HB_SCRIPT_KAYAH_LI: return QString("HB_SCRIPT_KAYAH_LI");
    case HB_SCRIPT_LEPCHA: return QString("HB_SCRIPT_LEPCHA");
    case HB_SCRIPT_LYCIAN: return QString("HB_SCRIPT_LYCIAN");
    case HB_SCRIPT_LYDIAN: return QString("HB_SCRIPT_LYDIAN");
    case HB_SCRIPT_OL_CHIKI: return QString("HB_SCRIPT_OL_CHIKI");
    case HB_SCRIPT_REJANG: return QString("HB_SCRIPT_REJANG");
    case HB_SCRIPT_SAURASHTRA: return QString("HB_SCRIPT_SAURASHTRA");
    case HB_SCRIPT_SUNDANESE: return QString("HB_SCRIPT_SUNDANESE");
    case HB_SCRIPT_VAI: return QString("HB_SCRIPT_VAI");
    case HB_SCRIPT_AVESTAN: return QString("HB_SCRIPT_AVESTAN");
    case HB_SCRIPT_BAMUM: return QString("HB_SCRIPT_BAMUM");
    case HB_SCRIPT_EGYPTIAN_HIEROGLYPHS: return QString("HB_SCRIPT_EGYPTIAN_HIEROGLYPHS");
    case HB_SCRIPT_IMPERIAL_ARAMAIC: return QString("HB_SCRIPT_IMPERIAL_ARAMAIC");
    case HB_SCRIPT_INSCRIPTIONAL_PAHLAVI: return QString("HB_SCRIPT_INSCRIPTIONAL_PAHLAVI");
    case HB_SCRIPT_INSCRIPTIONAL_PARTHIAN: return QString("HB_SCRIPT_INSCRIPTIONAL_PARTHIAN");
    case HB_SCRIPT_JAVANESE: return QString("HB_SCRIPT_JAVANESE");
    case HB_SCRIPT_KAITHI: return QString("HB_SCRIPT_KAITHI");
    case HB_SCRIPT_LISU: return QString("HB_SCRIPT_LISU");
    case HB_SCRIPT_MEETEI_MAYEK: return QString("HB_SCRIPT_MEETEI_MAYEK");
    case HB_SCRIPT_OLD_SOUTH_ARABIAN: return QString("HB_SCRIPT_OLD_SOUTH_ARABIAN");
    case HB_SCRIPT_OLD_TURKIC: return QString("HB_SCRIPT_OLD_TURKIC");
    case HB_SCRIPT_SAMARITAN: return QString("HB_SCRIPT_SAMARITAN");
    case HB_SCRIPT_TAI_THAM: return QString("HB_SCRIPT_TAI_THAM");
    case HB_SCRIPT_TAI_VIET: return QString("HB_SCRIPT_TAI_VIET");
    case HB_SCRIPT_BATAK: return QString("HB_SCRIPT_BATAK");
    case HB_SCRIPT_BRAHMI: return QString("HB_SCRIPT_BRAHMI");
    case HB_SCRIPT_MANDAIC: return QString("HB_SCRIPT_MANDAIC");
    case HB_SCRIPT_CHAKMA: return QString("HB_SCRIPT_CHAKMA");
    case HB_SCRIPT_MEROITIC_CURSIVE: return QString("HB_SCRIPT_MEROITIC_CURSIVE");
    case HB_SCRIPT_MEROITIC_HIEROGLYPHS: return QString("HB_SCRIPT_MEROITIC_HIEROGLYPHS");
    case HB_SCRIPT_MIAO: return QString("HB_SCRIPT_MIAO");
    case HB_SCRIPT_SHARADA: return QString("HB_SCRIPT_SHARADA");
    case HB_SCRIPT_SORA_SOMPENG: return QString("HB_SCRIPT_SORA_SOMPENG");
    case HB_SCRIPT_TAKRI: return QString("HB_SCRIPT_TAKRI");
    //case HB_SCRIPT_BASSA_VAH: return QString("HB_SCRIPT_BASSA_VAH");
    //case HB_SCRIPT_CAUCASIAN_ALBANIAN: return QString("HB_SCRIPT_CAUCASIAN_ALBANIAN");
    //case HB_SCRIPT_DUPLOYAN: return QString("HB_SCRIPT_DUPLOYAN");
    //case HB_SCRIPT_ELBASAN: return QString("HB_SCRIPT_ELBASAN");
    //case HB_SCRIPT_GRANTHA: return QString("HB_SCRIPT_GRANTHA");
    //case HB_SCRIPT_KHOJKI: return QString("HB_SCRIPT_KHOJKI");
    //case HB_SCRIPT_KHUDAWADI: return QString("HB_SCRIPT_KHUDAWADI");
    //case HB_SCRIPT_LINEAR_A: return QString("HB_SCRIPT_LINEAR_A");
    //case HB_SCRIPT_MAHAJANI: return QString("HB_SCRIPT_MAHAJANI");
    //case HB_SCRIPT_MANICHAEAN: return QString("HB_SCRIPT_MANICHAEAN");
    //case HB_SCRIPT_MENDE_KIKAKUI: return QString("HB_SCRIPT_MENDE_KIKAKUI");
    //case HB_SCRIPT_MODI: return QString("HB_SCRIPT_MODI");
    //case HB_SCRIPT_MRO: return QString("HB_SCRIPT_MRO");
    //case HB_SCRIPT_NABATAEAN: return QString("HB_SCRIPT_NABATAEAN");
    //case HB_SCRIPT_OLD_NORTH_ARABIAN: return QString("HB_SCRIPT_OLD_NORTH_ARABIAN");
    //case HB_SCRIPT_OLD_PERMIC: return QString("HB_SCRIPT_OLD_PERMIC");
    //case HB_SCRIPT_PAHAWH_HMONG: return QString("HB_SCRIPT_PAHAWH_HMONG");
    //case HB_SCRIPT_PALMYRENE: return QString("HB_SCRIPT_PALMYRENE");
    //case HB_SCRIPT_PAU_CIN_HAU: return QString("HB_SCRIPT_PAU_CIN_HAU");
    //case HB_SCRIPT_PSALTER_PAHLAVI: return QString("HB_SCRIPT_PSALTER_PAHLAVI");
    //case HB_SCRIPT_SIDDHAM: return QString("HB_SCRIPT_SIDDHAM");
    //case HB_SCRIPT_TIRHUTA: return QString("HB_SCRIPT_TIRHUTA");
    //case HB_SCRIPT_WARANG_CITI: return QString("HB_SCRIPT_WARANG_CITI");
    case HB_SCRIPT_INVALID: return QString("HB_SCRIPT_INVALID");
    default: return QString("HB_SCRIPT_INVALID");
    }
}

QString charTypeShortText(FriBidiCharType charType)
{
    switch (charType) {
    case FRIBIDI_TYPE_LTR: return QString("LTR");
    case FRIBIDI_TYPE_RTL: return QString("RTL");
    case FRIBIDI_TYPE_AL: return QString("AL");
    case FRIBIDI_TYPE_EN: return QString("EN");
    case FRIBIDI_TYPE_AN: return QString("AN");
    case FRIBIDI_TYPE_ES: return QString("ES");
    case FRIBIDI_TYPE_ET: return QString("ET");
    case FRIBIDI_TYPE_CS: return QString("CS");
    case FRIBIDI_TYPE_NSM: return QString("NSM");
    case FRIBIDI_TYPE_BN: return QString("BN");
    case FRIBIDI_TYPE_BS: return QString("BS");
    case FRIBIDI_TYPE_SS: return QString("SS");
    case FRIBIDI_TYPE_WS: return QString("WS");
    case FRIBIDI_TYPE_ON: return QString("ON");
    case FRIBIDI_TYPE_LRE: return QString("LRE");
    case FRIBIDI_TYPE_RLE: return QString("RLE");
    case FRIBIDI_TYPE_LRO: return QString("LRO");
    case FRIBIDI_TYPE_RLO: return QString("RLO");
    case FRIBIDI_TYPE_PDF: return QString("PDF");
    }
    return QString();
}

QString charTypeLongText(FriBidiCharType charType)
{
    switch (charType) {
    case FRIBIDI_TYPE_LTR: return QString("Left-to-Right Letter");
    case FRIBIDI_TYPE_RTL: return QString("Right-to-Left Letter");
    case FRIBIDI_TYPE_AL: return QString("Arabic Letter");
    case FRIBIDI_TYPE_EN: return QString("European Numeral");
    case FRIBIDI_TYPE_AN: return QString("Arabic Numeral");
    case FRIBIDI_TYPE_ES: return QString("European Number Separator");
    case FRIBIDI_TYPE_ET: return QString("European Number Terminator");
    case FRIBIDI_TYPE_CS: return QString("Common Separator");
    case FRIBIDI_TYPE_NSM: return QString("Non Spacing Mark");
    case FRIBIDI_TYPE_BN: return QString("Boundary Neutral");
    case FRIBIDI_TYPE_BS: return QString("Block Separator");
    case FRIBIDI_TYPE_SS: return QString("Segment Separator");
    case FRIBIDI_TYPE_WS: return QString("White Space");
    case FRIBIDI_TYPE_ON: return QString("Other Neutral");
    case FRIBIDI_TYPE_LRE: return QString("Left-to-Right Embedding");
    case FRIBIDI_TYPE_RLE: return QString("Right-to-Left Embedding");
    case FRIBIDI_TYPE_LRO: return QString("Left-to-Right Override");
    case FRIBIDI_TYPE_RLO: return QString("Right-to-Left Override");
    case FRIBIDI_TYPE_PDF: return QString("Pop Directional Flag");
    }
    return QString();
}

GlyphString::GlyphString() :
    mCodePoints(0), mGlyphIndices(0), mImages(0), mGeometries(0),
    mRuns(0), mLines(0), mScripts(0), mTypes(0), mLevels(0), mMap(0),
    mState(Invalid)
{
}

GlyphString::~GlyphString()
{
    delete[] mMap;
    delete[] mLevels;
    delete[] mTypes;
    delete[] mScripts;
    delete[] mLines;
    delete[] mRuns;
    delete[] mGeometries;
    delete[] mImages;
    delete[] mGlyphIndices;
    delete[] mCodePoints;
}

bool GlyphString::init(quint32 *codePoints, int size, FT_Face face,
                       QColor faceColor, FriBidiParType parType, int maxWidth)
{
    if (size <= 0) return false;

    mCodePoints = new quint32[size];
    memset(mCodePoints, 0, size * sizeof(*mCodePoints));

    mGlyphIndices = new int[size];
    memset(mGlyphIndices, 0, size * sizeof(*mGlyphIndices));

    mImages = new QImage[size];
    mGeometries = new Geometry[size];

    mRuns = new int[size];
    memset(mRuns, 0, size * sizeof(*mRuns));

    mLines = new int[size];
    memset(mLines, 0, size * sizeof(*mLines));

    mScripts = new hb_script_t[size];
    memset(mScripts, 0, size * sizeof(*mScripts));

    mTypes = new FriBidiCharType[size];
    memset(mTypes, 0, size * sizeof(*mTypes));

    mLevels = new FriBidiLevel[size];
    memset(mLevels, 0, size * sizeof(*mLevels));

    mMap = new FriBidiStrIndex[size];
    memset(mMap, 0, size * sizeof(*mMap));

    memcpy(mCodePoints, codePoints, size * sizeof(*codePoints));
    mSize = size;
    mFace = face;
    mFaceColor = faceColor;
    mMaxWidth = maxWidth;
    mParType = parType;

    loadGlyphImages();

    mState = Initialized;
    return true;
}

bool GlyphString::analyze(bool resolveScripts, bool breakOnLevelChange)
{
    if (mState != Initialized)
        return false;

    fribidi_get_bidi_types(mCodePoints, mSize, mTypes);
    fribidi_get_par_embedding_levels(mTypes, mSize, &mParType, mLevels);

    hb_unicode_funcs_t *ufuncs = hb_unicode_funcs_get_default();
    for (int i = 0; i < mSize; ++i)
        mScripts[i] = hb_unicode_script(ufuncs, mCodePoints[i]);

    if (resolveScripts) {
        hb_script_t lastScriptValue;
        int lastScriptIndex = -1;
        int lastSetIndex = -1;

        for (int i = 0; i < mSize; ++i) {
            if (mScripts[i] == HB_SCRIPT_COMMON || mScripts[i] == HB_SCRIPT_INHERITED) {
                if (lastScriptIndex != -1) {
                    mScripts[i] = lastScriptValue;
                    lastSetIndex = i;
                }
            } else {
                for (int j = lastSetIndex + 1; j < i; ++j)
                    mScripts[j] = mScripts[i];
                lastScriptValue = mScripts[i];
                lastScriptIndex = i;
                lastSetIndex = i;
            }
        }
    }

    int runID = 0;
    hb_script_t lastScript = mScripts[0];
    int lastLevel = mLevels[0];
    int lastRunStart = 0;
    for (int i = 0; i <= mSize; ++i) {
        if (i == mSize || mScripts[i] != lastScript ||
                (breakOnLevelChange && mLevels[i] != lastLevel))
        {
            ++runID;
            RunInfo run;
            run.startOffset = lastRunStart;
            run.endOffset = i;
            run.script = lastScript;
            run.direction = lastLevel & 1 ? HB_DIRECTION_RTL : HB_DIRECTION_LTR;
            mRunInfos.push_back(run);
            if (i < mSize) {
                lastScript = mScripts[i];
                lastLevel = mLevels[i];
                lastRunStart = i;
            } else {
                break;
            }
        }
        mRuns[i] = runID;
    }

    mState = Analyzed;
    return true;
}

bool GlyphString::shapeHarfBuzz()
{
    if (mState != Analyzed)
        return false;

    hb_font_t *hb_font = hb_ft_font_create(mFace, NULL);
    int totalGlyphs = 0;

    for (int i = 0; i < mRunInfos.size(); ++i) {
        RunInfo &runInfo = mRunInfos[i];
        runInfo.buffer = hb_buffer_create();
        hb_buffer_set_direction(runInfo.buffer, runInfo.direction);
        hb_buffer_set_script(runInfo.buffer, runInfo.script);
        hb_buffer_add_utf32(runInfo.buffer, mCodePoints + runInfo.startOffset,
                            runInfo.endOffset - runInfo.startOffset, 0,
                            runInfo.endOffset - runInfo.startOffset);
        hb_shape(hb_font, runInfo.buffer, NULL, 0);

        runInfo.glyphInfos = hb_buffer_get_glyph_infos(runInfo.buffer,
                                 &runInfo.glyphCount);
        runInfo.glyphPositions = hb_buffer_get_glyph_positions(runInfo.buffer,
                                     &runInfo.glyphCount);
        totalGlyphs += runInfo.glyphCount;
    }

    quint32 *newCodePoints = new quint32[totalGlyphs];
    memset(newCodePoints, 0, totalGlyphs * sizeof(*newCodePoints));

    int *newGlyphIndices = new int[totalGlyphs];
    memset(newGlyphIndices, 0, totalGlyphs * sizeof(*newGlyphIndices));

    QImage *newImages = new QImage[totalGlyphs];
    Geometry *newGeometries = new Geometry[totalGlyphs];

    int *newRuns = new int[totalGlyphs];
    memset(newRuns, 0, totalGlyphs * sizeof(*newRuns));

    int *newLines = new int[totalGlyphs];
    memset(newLines, 0, totalGlyphs * sizeof(*newLines));

    hb_script_t *newScripts = new hb_script_t[totalGlyphs];
    memset(newScripts, 0, totalGlyphs * sizeof(*newScripts));

    FriBidiCharType *newTypes = new FriBidiCharType[totalGlyphs];
    memset(newTypes, 0, totalGlyphs * sizeof(*newTypes));

    FriBidiLevel *newLevels = new FriBidiLevel[totalGlyphs];
    memset(newLevels, 0, totalGlyphs * sizeof(*newLevels));

    FriBidiStrIndex *newMap = new FriBidiStrIndex[totalGlyphs];
    memset(newMap, 0, totalGlyphs * sizeof(*newMap));

    int index = 0;
    for (int i = 0; i < mRunInfos.size(); ++i) {
        RunInfo &runInfo = mRunInfos[i];
        hb_glyph_info_t *glyphInfos = runInfo.glyphInfos;
        hb_glyph_position_t *glyphPositions = runInfo.glyphPositions;
        for (unsigned int j = 0; j < runInfo.glyphCount; ++j) {
            int runIndex = runInfo.direction == HB_DIRECTION_LTR ?
                j : runInfo.glyphCount - 1 - j;
            int sourceIndex = glyphInfos[runIndex].cluster
                + runInfo.startOffset;
            //newCodePoints[index] = mCodePoints[sourceIndex];
            newGlyphIndices[index] = glyphInfos[runIndex].codepoint;
            newRuns[index] = mRuns[sourceIndex];
            newScripts[index] = mScripts[sourceIndex];
            newTypes[index] = mTypes[sourceIndex];
            newLevels[index] = mLevels[sourceIndex];
            newGeometries[index].xOffset = glyphPositions[runIndex].x_offset / 64;
            newGeometries[index].yOffset = glyphPositions[runIndex].y_offset / 64;
            newGeometries[index].xAdvance = glyphPositions[runIndex].x_advance / 64;
            newGeometries[index].yAdvance = glyphPositions[runIndex].y_advance / 64;
            ++index;
        }
    }

    delete[] mCodePoints;
    delete[] mGlyphIndices;
    delete[] mImages;
    delete[] mGeometries;
    delete[] mRuns;
    delete[] mLines;
    delete[] mScripts;
    delete[] mTypes;
    delete[] mLevels;
    delete[] mMap;

    mCodePoints = newCodePoints;
    mGlyphIndices = newGlyphIndices;
    mImages = newImages;
    mGeometries = newGeometries;
    mRuns = newRuns;
    mLines = newLines;
    mScripts = newScripts;
    mTypes = newTypes;
    mLevels = newLevels;
    mMap = newMap;
    mSize = totalGlyphs;

    loadGlyphImages(true, true);

    hb_font_destroy(hb_font);
    for (int i = 0; i < mRunInfos.size(); ++i) {
        hb_buffer_destroy(mRunInfos[i].buffer);
        mRunInfos[i].buffer = 0;
        mRunInfos[i].glyphInfos = 0;
        mRunInfos[i].glyphPositions = 0;
        mRunInfos[i].glyphCount = 0;
    }

    mState = Shaped;
    return true;
}

bool GlyphString::shapeFriBidi(bool removeInvisibleCharacters)
{
    if (mState != Analyzed)
        return false;

    FriBidiJoiningType *joiningTypes = new FriBidiJoiningType[mSize];
    fribidi_get_joining_types(mCodePoints, mSize, joiningTypes);
    fribidi_join_arabic(mTypes, mSize, mLevels, joiningTypes);
    fribidi_shape_arabic(FRIBIDI_FLAG_SHAPE_MIRRORING |
                         FRIBIDI_FLAG_SHAPE_ARAB_PRES |
                         FRIBIDI_FLAG_SHAPE_ARAB_LIGA,
                         mLevels, mSize, joiningTypes, mCodePoints);
    delete[] joiningTypes;
    loadGlyphImages();

    if (removeInvisibleCharacters) {
        for (int i = 0; i < mSize; ++i) {
            if (mCodePoints[i] == 0xfeff
                || mCodePoints[i] == 0x061c
                || (mCodePoints[i] >= 0x202a && mCodePoints[i] <= 0x202e)
                || (mCodePoints[i] >= 0x2060 && mCodePoints[i] <= 0x2069)
                || (mCodePoints[i] >= 0x200b && mCodePoints[i] <= 0x200f))
                clearGlyph(i);
        }
    }

    mState = Shaped;
    return true;
}

bool GlyphString::reorderLine(int startOffset, int endOffset)
{
    int length = endOffset - startOffset;
    fribidi_reorder_line(0, mTypes + startOffset, length, 0, mParType,
                         mLevels + startOffset, 0, mMap + startOffset);
    return true;
}

bool GlyphString::layout()
{
    if (mState == Invalid)
        return false;

    for (int i = 0; i < mSize; ++i) {
        mMap[i] = i;
        mLines[i] = -1;
    }

    mLineInfos.clear();

    int lineNo = 0;
    int width = 0;
    int lineStart = 0;
    int lastSpace = -1;

    for (int i = 0; i <= mSize; ++i) {
        if (i == mSize) {
            mLineInfos.push_back(newLine(lineStart, i, lineNo++));
            break;
        }
        //if (mCodePoints[i] == ' ') {
        if (mTypes[i] == FRIBIDI_TYPE_WS) {
            if (lineStart == i) {
                lineStart = i + 1;
                continue;
            } else if (lastSpace == i - 1) {
                clearGlyph(i - 1);
                lastSpace = i;
                continue;
            }
            lastSpace = i;
        }
        width += mGeometries[i].xAdvance;
        if (mMaxWidth < width) {
            if (lineStart == i - 1) {
                return false;
            }
            if (lastSpace > lineStart) {
                mLineInfos.push_back(newLine(lineStart, lastSpace, lineNo++));
                width = 0;
                lineStart = lastSpace + 1;
                continue;
            } else {
                mLineInfos.push_back(newLine(lineStart, i, lineNo++));
                width = 0;
                lineStart = i;
                continue;
            }
        }
    }

    mState = LaidOut;
    return true;
}

LineInfo GlyphString::newLine(int startOffset, int endOffset, int lineNo)
{
    LineInfo lineInfo;
    lineInfo.startOffset = startOffset;
    lineInfo.endOffset = endOffset;
    reorderLine(startOffset, endOffset);

    int left = 0;
    int right = 0;
    int x = 0;
    for (int i = startOffset; i < endOffset; ++i) {
        int index = reorderedIndex(i);
        mLines[index] = lineNo;
        left = qMin(left, x + mGeometries[index].left + mGeometries[index].xOffset);
        right = qMax(right, x + mGeometries[index].left
                     + mGeometries[index].xOffset + mImages[index].width());
        x += mGeometries[index].xAdvance;
        int top = mGeometries[index].top + mGeometries[index].yOffset;
        int bottom = top - mImages[index].height();
        lineInfo.ascent = qMax(lineInfo.ascent, top);
        lineInfo.descent = qMin(lineInfo.descent, bottom);
    }
    right = qMax(right, x);
    lineInfo.width = right - left;
    lineInfo.left = left;
    lineInfo.height = lineInfo.ascent - lineInfo.descent;
    return lineInfo;
}

void GlyphString::clearGlyph(int index)
{
    mImages[index] = QImage();
    mGeometries[index] = Geometry();
}

bool GlyphString::loadGlyphImages(bool useGlyphIndices, bool keepXAdvance)
{

    for (int i = 0; i < mSize; ++i) {
        int glyphIndex;
        if (useGlyphIndices)
            glyphIndex = mGlyphIndices[i];
        else
            glyphIndex = FT_Get_Char_Index(mFace, mCodePoints[i]);

        if (FT_Load_Glyph(mFace, glyphIndex, 0))
            continue;
        if (FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL))
            continue;

        FT_Bitmap bmp = mFace->glyph->bitmap;

        mGlyphIndices[i] = glyphIndex;
        mGeometries[i].top = mFace->glyph->bitmap_top;
        mGeometries[i].left = mFace->glyph->bitmap_left;
        if (!keepXAdvance)
            mGeometries[i].xAdvance = mFace->glyph->advance.x / 64;

        mImages[i] = QImage(bmp.width, bmp.rows, QImage::Format_ARGB32);

        for (int ii = 0; ii < bmp.width; ++ii)
        {
            for (int jj = 0; jj < bmp.rows; ++jj)
                mImages[i].setPixel(ii, jj, qRgba(mFaceColor.red(),
                                                  mFaceColor.green(),
                                                  mFaceColor.blue(),
                                                  bmp.buffer[jj * bmp.pitch + ii]));
        }

    }

    return true;
}

QString GlyphString::scriptShortText(int index) const
{
    assert(index >= 0 && index < mSize);
    return ::scriptShortText(mScripts[index]);
}

QString GlyphString::scriptLongText(int index) const
{
    assert(index >= 0 && index < mSize);
    return ::scriptLongText(mScripts[index]);
}

QString GlyphString::charTypeShortText(int index) const
{
    assert(index >= 0 && index < mSize);
    return ::charTypeShortText(mTypes[index]);
}

QString GlyphString::charTypeLongText(int index) const
{
    assert(index >= 0 && index < mSize);
    return ::charTypeLongText(mTypes[index]);
}
