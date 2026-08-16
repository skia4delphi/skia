/*
 * Copyright (c) 2011-2026 Google LLC.
 * Copyright (c) 2021-2026 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <algorithm>
#include <memory>

#include "include/c/sk4d_font.h"
#include "src/c/sk4d_mapping.h"

sk_font_t* sk4d_font_create(sk_typeface_t* typeface, float size, float sx, float kx) {
    return ToFont(new SkFont(typeface ? sk_ref_sp(AsTypeface(typeface)) : Sk4DComp::MakeDefaultTypeface(), size, sx, kx));
}

sk_font_t* sk4d_font_create2(const sk_font_t* font) {
    return ToFont(new SkFont(AsFont(*font)));
}

void sk4d_font_destroy(sk_font_t* self) {
    delete AsFont(self);
}

bool sk4d_font_get_baseline_snap(const sk_font_t* self) {
    return AsFont(self)->isBaselineSnap();
}

sk_fontedging_t sk4d_font_get_edging(const sk_font_t* self) {
    return ToFontEdging(AsFont(self)->getEdging());
}

bool sk4d_font_get_embedded_bitmaps(const sk_font_t* self) {
    return AsFont(self)->isEmbeddedBitmaps();
}

bool sk4d_font_get_embolden(const sk_font_t* self) {
    return AsFont(self)->isEmbolden();
}

bool sk4d_font_get_force_auto_hinting(const sk_font_t* self) {
    return AsFont(self)->isForceAutoHinting();
}

int32_t sk4d_font_get_glyphs(const sk_font_t* self, const void* text, size_t size, sk_textencoding_t encoding, sk_glyphid_t result[], int32_t max_count) {
    const size_t safe_count = max_count > 0 ? static_cast<size_t>(max_count) : 0;
    return static_cast<int32_t>(AsFont(self)->textToGlyphs(
            text, size, AsTextEncoding(encoding), SkSpan<SkGlyphID>(result, safe_count)));
}

int32_t sk4d_font_get_glyphs_count(const sk_font_t* self, const void* text, size_t size, sk_textencoding_t encoding) {
    return AsFont(self)->countText(text, size, AsTextEncoding(encoding));
}

sk_fonthinting_t sk4d_font_get_hinting(const sk_font_t* self) {
    return ToFontHinting(AsFont(self)->getHinting());
}

void sk4d_font_get_horizontal_positions(const sk_font_t* self, const sk_glyphid_t glyphs[], int32_t count, float result[], float origin) {
    const size_t safe_count = count > 0 ? static_cast<size_t>(count) : 0;
    AsFont(self)->getXPos(SkSpan<const SkGlyphID>(glyphs, safe_count),
                          SkSpan<SkScalar>(result, safe_count), origin);
}

size_t sk4d_font_get_intercepts(const sk_font_t* self, const sk_glyphid_t glyphs[], int32_t count, const sk_point_t positions[], const float bounds[2], float result[], const sk_paint_t* paint) {
    const size_t safe_count = count > 0 ? static_cast<size_t>(count) : 0;
    auto intercepts = AsFont(self)->getIntercepts(
            SkSpan<const SkGlyphID>(glyphs, safe_count),
            SkSpan<const SkPoint>(AsPoint(positions), safe_count),
            bounds[0], bounds[1], AsPaint(paint));
    if (result)
        std::copy(intercepts.begin(), intercepts.end(), result);
    return intercepts.size();
}

bool sk4d_font_get_linear_metrics(const sk_font_t* self) {
    return AsFont(self)->isLinearMetrics();
}

float sk4d_font_get_metrics(const sk_font_t* self, sk_fontmetrics_t* metrics) {
    return AsFont(self)->getMetrics(AsFontMetrics(metrics));
}

sk_path_t* sk4d_font_get_path(const sk_font_t* self, sk_glyphid_t glyph) {
    auto r = AsFont(self)->getPath(glyph);
    return r ? ToPath(new SkPath(std::move(*r))) : nullptr;
}

void sk4d_font_get_paths(const sk_font_t* self, const sk_glyphid_t glyphs[], int32_t count, sk_font_path_proc proc, void* proc_context) {
    struct Rec {
        void*             fContext;
        sk_font_path_proc fProc;
    } rec = { proc_context, proc };

    const size_t safe_count = count > 0 ? static_cast<size_t>(count) : 0;
    AsFont(self)->getPaths(SkSpan<const SkGlyphID>(glyphs, safe_count),
        [](const SkPath* path, const SkMatrix& matrix, void* ctx) {
            Rec*        rec = reinterpret_cast<Rec*>(ctx);
            sk_matrix_t m   = ToMatrix(matrix);
            rec->fProc(ToPath(path), &m, rec->fContext);
        },
        &rec);
}

void sk4d_font_get_positions(const sk_font_t* self, const sk_glyphid_t glyphs[], int32_t count, sk_point_t result[], const sk_point_t* origin) {
    const size_t safe_count = count > 0 ? static_cast<size_t>(count) : 0;
    AsFont(self)->getPos(SkSpan<const SkGlyphID>(glyphs, safe_count),
                         SkSpan<SkPoint>(AsPoint(result), safe_count), *AsPoint(origin));
}

float sk4d_font_get_scale_x(const sk_font_t* self) {
    return AsFont(self)->getScaleX();
}

float sk4d_font_get_size(const sk_font_t* self) {
    return AsFont(self)->getSize();
}

float sk4d_font_get_skew_x(const sk_font_t* self) {
    return AsFont(self)->getSkewX();
}

bool sk4d_font_get_subpixel(const sk_font_t* self) {
    return AsFont(self)->isSubpixel();
}

sk_typeface_t* sk4d_font_get_typeface(const sk_font_t* self) {
    return ToTypeface(AsFont(self)->refTypeface().release());
}

sk_typeface_t* sk4d_font_get_typeface_or_default(const sk_font_t* self) {
    auto r = AsFont(self)->refTypeface();
    if (!r)
      r = Sk4DComp::MakeDefaultTypeface();
    return ToTypeface(r.release());
}

void sk4d_font_get_widths_bounds(const sk_font_t* self, const sk_glyphid_t glyphs[], int32_t count, float widths[], sk_rect_t bounds[], const sk_paint_t* paint) {
    const size_t safe_count = count > 0 ? static_cast<size_t>(count) : 0;
    AsFont(self)->getWidthsBounds(
            SkSpan<const SkGlyphID>(glyphs, safe_count),
            SkSpan<SkScalar>(widths, widths ? safe_count : 0),
            SkSpan<SkRect>(AsRect(bounds), bounds ? safe_count : 0), AsPaint(paint));
}

bool sk4d_font_is_equal(const sk_font_t* self, const sk_font_t* font) {
    return AsFont(*self) == AsFont(*font);
}

float sk4d_font_measure_text(const sk_font_t* self, const void* text, size_t size, sk_textencoding_t encoding, sk_rect_t* bounds, const sk_paint_t* paint) {
    return AsFont(self)->measureText(text, size, AsTextEncoding(encoding), AsRect(bounds), AsPaint(paint));
}

void sk4d_font_set_baseline_snap(sk_font_t* self, bool value) {
    AsFont(self)->setBaselineSnap(value);
}

void sk4d_font_set_edging(sk_font_t* self, sk_fontedging_t value) {
    AsFont(self)->setEdging(AsFontEdging(value));
}

void sk4d_font_set_embedded_bitmaps(sk_font_t* self, bool value) {
    AsFont(self)->setEmbeddedBitmaps(value);
}

void sk4d_font_set_embolden(sk_font_t* self, bool value) {
    AsFont(self)->setEmbolden(value);
}

void sk4d_font_set_force_auto_hinting(sk_font_t* self, bool value) {
    AsFont(self)->setForceAutoHinting(value);
}

void sk4d_font_set_hinting(sk_font_t* self, sk_fonthinting_t value) {
    AsFont(self)->setHinting(AsFontHinting(value));
}

void sk4d_font_set_linear_metrics(sk_font_t* self, bool value) {
    AsFont(self)->setLinearMetrics(value);
}

void sk4d_font_set_scale_x(sk_font_t* self, float value) {
    AsFont(self)->setScaleX(value);
}

void sk4d_font_set_size(sk_font_t* self, float value) {
    AsFont(self)->setSize(value);
}

void sk4d_font_set_skew_x(sk_font_t* self, float value) {
    AsFont(self)->setSkewX(value);
}

void sk4d_font_set_subpixel(sk_font_t* self, bool value) {
    AsFont(self)->setSubpixel(value);
}

void sk4d_font_set_typeface(sk_font_t* self, sk_typeface_t* typeface) {
    AsFont(self)->setTypeface(sk_ref_sp(AsTypeface(typeface)));
}

sk_glyphid_t sk4d_font_unichar_to_glyph(const sk_font_t* self, sk_unichar_t unichar) {
    return AsFont(self)->unicharToGlyph(unichar);
}

void sk4d_font_unichars_to_glyphs(const sk_font_t* self, const sk_unichar_t unichars[], int32_t count, sk_glyphid_t result[]) {
    const size_t safe_count = count > 0 ? static_cast<size_t>(count) : 0;
    AsFont(self)->unicharsToGlyphs(SkSpan<const SkUnichar>(unichars, safe_count),
                                   SkSpan<SkGlyphID>(result, safe_count));
}
