/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/c/gr4d_backendsurfacemutablestate.h"
#include "src/c/sk4d_mapping.h"

gr_backendsurfacemutablestate_t* gr4d_backendsurfacemutablestate_create(gr_vk_imagelayout_t image_layout, uint32_t queue_family_index) {
    SK4D_ONLY_VULKAN(auto r = sk_make_sp<skgpu::MutableTextureState>(skgpu::MutableTextureStates::MakeVulkan(AsVkImageLayout(image_layout), queue_family_index));)
    return SK4D_ONLY_VULKAN(ToGrBackendSurfaceMutableState(r.release()), nullptr);
}

void gr4d_backendsurfacemutablestate_destroy(gr_backendsurfacemutablestate_t* self) {
    SK4D_ONLY_VULKAN(AsGrBackendSurfaceMutableState(self)->unref();)
}
