/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <string_view>
#include <vector>
#include <utility>

#include "include/c/sk4d_imagefilter.h"
#include "src/c/sk4d_mapping.h"

bool sk4d_imagefilter_can_compute_fast_bounds(const sk_imagefilter_t* self) {
    return AsImageFilter(self)->canComputeFastBounds();
}

void sk4d_imagefilter_compute_fast_bounds(const sk_imagefilter_t* self, const sk_rect_t* bounds, sk_rect_t* result) {
    *result = ToRect(AsImageFilter(self)->computeFastBounds(AsRect(*bounds)));
}

sk_imagefilter_t* sk4d_imagefilter_make_arithmetic(float k1, float k2, float k3, float k4, bool enforce_premultiplied_color, sk_imagefilter_t* background, sk_imagefilter_t* foreground, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::Arithmetic(k1, k2, k3, k4, enforce_premultiplied_color, sk_ref_sp(AsImageFilter(background)), sk_ref_sp(AsImageFilter(foreground)), AsRect(crop_rect)).release());
}

static sk_sp<SkImageFilter> MakeAlphaThresholdReplacement(const SkRegion& region, SkScalar innerMin, SkScalar outerMax, sk_sp<SkImageFilter> input,const SkImageFilters::CropRect& cropRect = {}) {
    SkPictureRecorder recorder;
    SkCanvas* canvas = recorder.beginRecording(region.getBounds().width(), region.getBounds().height());

    SkPaint paint;
    paint.setColor(SK_ColorWHITE); 
    paint.setStyle(SkPaint::kFill_Style);

    for (SkRegion::Iterator it(region); !it.done(); it.next()) {
        canvas->drawRect(SkRect::Make(it.rect()), paint);
    }
    
    sk_sp<SkPicture> picture = recorder.finishRecordingAsPicture();
    sk_sp<SkImageFilter> regionFilter = SkImageFilters::Picture(picture);

    return SkImageFilters::Blend(SkBlendMode::kSrcIn, std::move(input), std::move(regionFilter), cropRect);
}

// DEPRECATED
sk_imagefilter_t* sk4d_imagefilter_make_alpha_threshold(const sk_region_t* region, float inner_min, float outer_max, sk_imagefilter_t* input) {
    return ToImageFilter(MakeAlphaThresholdReplacement(AsRegion(*region), inner_min, outer_max, sk_ref_sp(AsImageFilter(input))).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_blend(sk_blendmode_t mode, sk_imagefilter_t* background, sk_imagefilter_t* foreground, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::Blend(AsBlendMode(mode), sk_ref_sp(AsImageFilter(background)), sk_ref_sp(AsImageFilter(foreground)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_blur(float sigma_x, float sigma_y, sk_tilemode_t tile_mode, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::Blur(sigma_x, sigma_y, AsTileMode(tile_mode), sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_colorfilter(sk_colorfilter_t* color_filter, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::ColorFilter(sk_ref_sp(AsColorFilter(color_filter)), sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_compose(sk_imagefilter_t* inner, sk_imagefilter_t* outer) {
    return ToImageFilter(SkImageFilters::Compose(sk_ref_sp(AsImageFilter(inner)), sk_ref_sp(AsImageFilter(outer))).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_dilate(float radius_x, float radius_y, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::Dilate(radius_x, radius_y, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_displacement_map(sk_colorchannel_t x_channel_selector, sk_colorchannel_t y_channel_selector, float scale, sk_imagefilter_t* displacement, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::DisplacementMap(AsColorChannel(x_channel_selector), AsColorChannel(y_channel_selector), scale,  sk_ref_sp(AsImageFilter(displacement)), sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release()); 
}

sk_imagefilter_t* sk4d_imagefilter_make_distant_lit_diffuse(const sk_point3_t* direction, sk_color_t light_color, float surface_scale, float kd, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::DistantLitDiffuse(AsPoint3(*direction), light_color, surface_scale, kd, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_distant_lit_specular(const sk_point3_t* direction, sk_color_t light_color, float surface_scale, float ks, float shininess, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::DistantLitSpecular(AsPoint3(*direction), light_color, surface_scale, ks, shininess, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_drop_shadow(float dx, float dy, float sigma_x, float sigma_y, sk_color_t color, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::DropShadow(dx, dy, sigma_x, sigma_y, color, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release()); 
}

sk_imagefilter_t* sk4d_imagefilter_make_drop_shadow_only(float dx, float dy, float sigma_x, float sigma_y, sk_color_t color, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::DropShadowOnly(dx, dy, sigma_x, sigma_y, color, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_erode(float radius_x, float radius_y, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::Erode(radius_x, radius_y, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_image(sk_image_t* image, const sk_rect_t* src, const sk_rect_t* dest, const sk_samplingoptions_t* sampling) {
    return ToImageFilter(SkImageFilters::Image(sk_ref_sp(AsImage(image)), AsRect(*src), AsRect(*dest), AsSamplingOptions(*sampling)).release());
}

static sk_sp<SkImageFilter> MakeMagnifier(const SkRect& srcRect, SkScalar inset, sk_sp<SkImageFilter> input, const SkImageFilters::CropRect& cropRect = {}) {
    SkScalar zoomAmount = 2.0f;
    SkSamplingOptions sampling(SkFilterMode::kLinear, SkMipmapMode::kNone);
    return SkImageFilters::Magnifier(srcRect, zoomAmount, inset, sampling, std::move(input), cropRect);
}

// DEPRECATED
// TODO: Add overloading with new parameters.
sk_imagefilter_t* sk4d_imagefilter_make_magnifier(const sk_rect_t* src, float inset, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(MakeMagnifier(AsRect(*src), inset, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_matrix_convolution(const sk_isize_t* kernel_size, const float* kernel, float gain, float bias, const sk_ipoint_t* kernel_offset, sk_tilemode_t tile_mode, bool convolve_alpha, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::MatrixConvolution(AsISize(*kernel_size), kernel, gain, bias, AsIPoint(*kernel_offset), AsTileMode(tile_mode), convolve_alpha, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release()); 
}

sk_imagefilter_t* sk4d_imagefilter_make_matrix_transform(const sk_matrix_t* matrix, const sk_samplingoptions_t* sampling, sk_imagefilter_t* input) {
    return ToImageFilter(SkImageFilters::MatrixTransform(AsMatrix(matrix), AsSamplingOptions(*sampling), sk_ref_sp(AsImageFilter(input))).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_merge(const sk_imagefilter_t* filters[], int32_t count, const sk_rect_t* crop_rect) {
    std::vector<sk_sp<SkImageFilter>> vector;
    vector.reserve(count);
    for (int32_t i = 0; i < count; i++)
        vector.emplace_back(sk_ref_sp(AsImageFilter(filters[i])));
    return ToImageFilter(SkImageFilters::Merge(vector.data(), count, AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_offset(float dx, float dy, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::Offset(dx, dy, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_picture(sk_picture_t* picture, const sk_rect_t* crop_rect) {
    if (!crop_rect)
        return ToImageFilter(SkImageFilters::Picture(sk_ref_sp(AsPicture(picture))).release());
    else
        return ToImageFilter(SkImageFilters::Picture(sk_ref_sp(AsPicture(picture)), AsRect(*crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_point_lit_diffuse(const sk_point3_t* location, sk_color_t light_color, float surface_scale, float kd, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::PointLitDiffuse(AsPoint3(*location), light_color, surface_scale, kd, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_point_lit_specular(const sk_point3_t* location, sk_color_t light_color, float surface_scale, float ks, float shininess, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::PointLitSpecular(AsPoint3(*location), light_color, surface_scale, ks, shininess, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_runtime_shader(const sk_runtimeshaderbuilder_t* effect_builder, const char child[], sk_imagefilter_t* input) {
    return ToImageFilter(SkImageFilters::RuntimeShader(AsRuntimeShaderBuilder(*effect_builder), child, sk_ref_sp(AsImageFilter(input))).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_runtime_shader2(const sk_runtimeshaderbuilder_t* effect_builder, const char* children[], sk_imagefilter_t* inputs[], int32_t count) {
    std::vector<std::string_view> vector;
    std::vector<sk_sp<SkImageFilter>> filters;
    vector.reserve(count);
    filters.reserve(count);
    for (int32_t i = 0; i < count; i++) {
        vector.emplace_back(children[i]);
        filters.emplace_back(sk_ref_sp(AsImageFilter(inputs[i])));
    }
    return ToImageFilter(SkImageFilters::RuntimeShader(AsRuntimeShaderBuilder(*effect_builder), vector.data(), filters.data(), count).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_shader(sk_shader_t* shader, bool dither, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::Shader(sk_ref_sp(AsShader(shader)), AsImageFiltersDither(dither), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_spot_lit_diffuse(const sk_point3_t* location, const sk_point3_t* target, float falloff_exponent, float cutoff_angle, sk_color_t light_color, float surface_scale, float kd, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::SpotLitDiffuse(AsPoint3(*location), AsPoint3(*target), falloff_exponent, cutoff_angle, light_color, surface_scale, kd, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_spot_lit_specular(const sk_point3_t* location, const sk_point3_t* target, float falloff_exponent, float cutoff_angle, sk_color_t light_color, float surface_scale, float ks, float shininess, sk_imagefilter_t* input, const sk_rect_t* crop_rect) {
    return ToImageFilter(SkImageFilters::SpotLitSpecular(AsPoint3(*location), AsPoint3(*target), falloff_exponent, cutoff_angle, light_color, surface_scale, ks, shininess, sk_ref_sp(AsImageFilter(input)), AsRect(crop_rect)).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_tile(const sk_rect_t* src, const sk_rect_t* dest, sk_imagefilter_t* input) {
    return ToImageFilter(SkImageFilters::Tile(AsRect(*src), AsRect(*dest), sk_ref_sp(AsImageFilter(input))).release());
}

sk_imagefilter_t* sk4d_imagefilter_make_with_local_matrix(const sk_imagefilter_t* self, const sk_matrix_t* local_matrix) {
    return ToImageFilter(AsImageFilter(self)->makeWithLocalMatrix(AsMatrix(local_matrix)).release());
}