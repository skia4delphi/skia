/*
 * Copyright (c) 2011-2026 Google LLC.
 * Copyright (c) 2021-2026 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/c/sk4d_shader.h"
#include "src/c/sk4d_mapping.h"

#include <vector>

namespace {

std::vector<SkColor4f> ToGradientColors(const sk_color_t colors[], int32_t count) {
    std::vector<SkColor4f> result;
    if (count > 0) {
        result.reserve(count);
        for (int32_t i = 0; i < count; ++i) {
            result.push_back(SkColor4f::FromColor(colors[i]));
        }
    }
    return result;
}

SkGradient ToGradient(const SkColor4f colors[],
                      sk_sp<SkColorSpace> color_space,
                      const float positions[],
                      int32_t count,
                      SkTileMode tile_mode) {
    const size_t safe_count = count > 0 ? static_cast<size_t>(count) : 0;
    return SkGradient(
            SkGradient::Colors(SkSpan<const SkColor4f>(colors, safe_count),
                               SkSpan<const float>(positions, positions ? safe_count : 0),
                               tile_mode,
                               std::move(color_space)),
            SkGradient::Interpolation::FromFlags(0));
}

}  // namespace

sk_shader_t* sk4d_shader_make_blend(sk_blendmode_t mode, sk_shader_t* dest, sk_shader_t* src) {
    return ToShader(SkShaders::Blend(AsBlendMode(mode), sk_ref_sp(AsShader(dest)), sk_ref_sp(AsShader(src))).release());
}

sk_shader_t* sk4d_shader_make_color(sk_color_t color) {
    return ToShader(SkShaders::Color(color).release());
}

sk_shader_t* sk4d_shader_make_color2(const sk_color4f_t* color, sk_colorspace_t* color_space) {
    return ToShader(SkShaders::Color(AsColor4f(*color), sk_ref_sp(AsColorSpace(color_space))).release());
}

sk_shader_t* sk4d_shader_make_empty(void) {
    return ToShader(SkShaders::Empty().release());
}

sk_shader_t* sk4d_shader_make_gradient_linear(const sk_point_t points[2], const sk_color_t colors[], const float positions[], int32_t count, sk_tilemode_t tile_mode, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto converted_colors = ToGradientColors(colors, count);
    const auto gradient = ToGradient(converted_colors.data(), nullptr, positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::LinearGradient(AsPoint(points), gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_gradient_linear2(const sk_point_t points[2], const sk_color4f_t colors[], sk_colorspace_t* color_space, const float positions[], int32_t count, sk_tilemode_t tile_mode, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto gradient = ToGradient(AsColor4f(colors), sk_ref_sp(AsColorSpace(color_space)), positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::LinearGradient(AsPoint(points), gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_gradient_radial(const sk_point_t* center, float radius, const sk_color_t colors[], const float positions[], int32_t count, sk_tilemode_t tile_mode, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto converted_colors = ToGradientColors(colors, count);
    const auto gradient = ToGradient(converted_colors.data(), nullptr, positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::RadialGradient(AsPoint(*center), radius, gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_gradient_radial2(const sk_point_t* center, float radius, const sk_color4f_t colors[], sk_colorspace_t* color_space, const float positions[], int32_t count, sk_tilemode_t tile_mode, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto gradient = ToGradient(AsColor4f(colors), sk_ref_sp(AsColorSpace(color_space)), positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::RadialGradient(AsPoint(*center), radius, gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_gradient_sweep(float center_x, float center_y, const sk_color_t colors[], const float positions[], int32_t count, sk_tilemode_t tile_mode, float start_angle, float end_angle, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto converted_colors = ToGradientColors(colors, count);
    const auto gradient = ToGradient(converted_colors.data(), nullptr, positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::SweepGradient({center_x, center_y}, start_angle, end_angle, gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_gradient_sweep2(float center_x, float center_y, const sk_color4f_t colors[], sk_colorspace_t* color_space, const float positions[], int32_t count, sk_tilemode_t tile_mode, float start_angle, float end_angle, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto gradient = ToGradient(AsColor4f(colors), sk_ref_sp(AsColorSpace(color_space)), positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::SweepGradient({center_x, center_y}, start_angle, end_angle, gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_gradient_two_point_conical(const sk_point_t* start, float start_radius, const sk_point_t* end, float end_radius, const sk_color_t colors[], const float positions[], int32_t count, sk_tilemode_t tile_mode, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto converted_colors = ToGradientColors(colors, count);
    const auto gradient = ToGradient(converted_colors.data(), nullptr, positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::TwoPointConicalGradient(AsPoint(*start), start_radius, AsPoint(*end), end_radius, gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_gradient_two_point_conical2(const sk_point_t* start, float start_radius, const sk_point_t* end, float end_radius, const sk_color4f_t colors[], sk_colorspace_t* color_space, const float positions[], int32_t count, sk_tilemode_t tile_mode, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    const auto gradient = ToGradient(AsColor4f(colors), sk_ref_sp(AsColorSpace(color_space)), positions, count, AsTileMode(tile_mode));
    return ToShader(SkShaders::TwoPointConicalGradient(AsPoint(*start), start_radius, AsPoint(*end), end_radius, gradient, (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_shader_make_perlin_noise_fractal_noise(float base_frequency_x, float base_frequency_y, int32_t num_octaves, float seed, const sk_isize_t* tile_size) {
    return ToShader(SkShaders::MakeFractalNoise(base_frequency_x, base_frequency_y, num_octaves, seed, AsISize(tile_size)).release());
}

sk_shader_t* sk4d_shader_make_perlin_noise_turbulence(float base_frequency_x, float base_frequency_y, int32_t num_octaves, float seed, const sk_isize_t* tile_size) {
    return ToShader(SkShaders::MakeTurbulence(base_frequency_x, base_frequency_y,  num_octaves,  seed,  AsISize(tile_size)).release());
}

sk_shader_t* sk4d_shader_make_with_color_filter(const sk_shader_t* self, sk_colorfilter_t* color_filter) {
    return ToShader(AsShader(self)->makeWithColorFilter(sk_ref_sp(AsColorFilter(color_filter))).release());
}

sk_shader_t* sk4d_shader_make_with_local_matrix(const sk_shader_t* self, const sk_matrix_t* local_matrix) {
    return ToShader(AsShader(self)->makeWithLocalMatrix(AsMatrix(local_matrix)).release());
}
