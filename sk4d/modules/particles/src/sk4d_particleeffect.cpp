/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

// DEPRECATED: The particles module in Skia has been completely removed in the
// latest versions.

#include "modules/particles/include/sk4d_particleeffect.h"

void sk4d_particleeffect_get_position(const sk_particleeffect_t* self, sk_point_t* result) {
    (void)self;
    (void)result;
}

float sk4d_particleeffect_get_rate(const sk_particleeffect_t* self) {
    (void)self;
    return 0;
}

void sk4d_particleeffect_get_uniform(const sk_particleeffect_t* self, size_t index, sk_particleuniform_t* result) {
    (void)self;
    (void)index;
    (void)result;
}

size_t sk4d_particleeffect_get_uniform_count(const sk_particleeffect_t* self) {
    (void)self;
    return 0;
}

float* sk4d_particleeffect_get_uniform_data(sk_particleeffect_t* self) {
    (void)self;
    return nullptr;
}

int32_t sk4d_particleeffect_get_uniform_data_count(const sk_particleeffect_t* self) {
    (void)self;
    return 0;
}

sk_string_t* sk4d_particleeffect_get_uniform_name(const sk_particleeffect_t* self, size_t index) {
    (void)self;
    (void)index;
    return nullptr;
}

void sk4d_particleeffect_init(void) {
}

sk_particleeffect_t* sk4d_particleeffect_make_from_file(const char file_name[]) {
    (void)file_name;
    return nullptr;
}

sk_particleeffect_t* sk4d_particleeffect_make_from_stream(sk_stream_t* stream, sk_resourceprovider_t* resource_provider) {
    (void)stream;
    (void)resource_provider;
    return nullptr;
}

void sk4d_particleeffect_render(sk_particleeffect_t* self, sk_canvas_t* canvas) {
    (void)self;
    (void)canvas;
}

void sk4d_particleeffect_set_position(sk_particleeffect_t* self, const sk_point_t* value) {
    (void)self;
    (void)value;
}

void sk4d_particleeffect_set_rate(sk_particleeffect_t* self, float value) {
    (void)self;
    (void)value;
}

bool sk4d_particleeffect_set_uniform(sk_particleeffect_t* self, const char name[], const float data[], int32_t count) {
    (void)self;
    (void)name;
    (void)data;
    (void)count;
    return false;
}

void sk4d_particleeffect_start(sk_particleeffect_t* self, double now, bool looping) {
    (void)self;
    (void)now;
    (void)looping;
}

void sk4d_particleeffect_update(sk_particleeffect_t* self, double now) {
    (void)self;
    (void)now;
}
