/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/c/gr4d_backendsurface.h"
#include "src/c/sk4d_mapping.h"

gr_backendrendertarget_t* gr4d_backendrendertarget_create_gl(int32_t width, int32_t height, int32_t sample_count, int32_t stencil_bits, const gr_gl_framebufferinfo_t* framebuffer_info) {
    return SK4D_ONLY_GL(ToGrBackendRenderTarget(new GrBackendRenderTarget(GrBackendRenderTargets::MakeGL(width, height, sample_count, stencil_bits, AsGrGLFramebufferInfo(framebuffer_info)))), nullptr);
}

gr_backendrendertarget_t* gr4d_backendrendertarget_create_mtl(int32_t width, int32_t height, const gr_mtl_textureinfo_t* texture_info) {
    return SK4D_ONLY_METAL(ToGrBackendRenderTarget(new GrBackendRenderTarget(GrBackendRenderTargets::MakeMtl(width, height, AsGrMtlTextureInfo(texture_info)))), nullptr);
}

gr_backendrendertarget_t* gr4d_backendrendertarget_create_vk(int32_t width, int32_t height, const gr_vk_imageinfo_t* image_info) {
    return SK4D_ONLY_VULKAN(ToGrBackendRenderTarget(new GrBackendRenderTarget(GrBackendRenderTargets::MakeVk(width, height, AsGrVkImageInfo(image_info)))), nullptr);
}

void gr4d_backendrendertarget_destroy(gr_backendrendertarget_t* self) {
    SK4D_ONLY_GPU(delete AsGrBackendRenderTarget(self);)
}

gr_backendapi_t gr4d_backendrendertarget_get_backend_api(const gr_backendrendertarget_t* self) {
    return SK4D_ONLY_GPU(ToGrBackendAPI(AsGrBackendRenderTarget(self)->backend()), (gr_backendapi_t)0);
}

int32_t gr4d_backendrendertarget_get_height(const gr_backendrendertarget_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendRenderTarget(self)->height(), 0);
}

int32_t gr4d_backendrendertarget_get_sample_count(const gr_backendrendertarget_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendRenderTarget(self)->sampleCnt(), 0);
}

int32_t gr4d_backendrendertarget_get_stencil_bits(const gr_backendrendertarget_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendRenderTarget(self)->stencilBits(), 0);
}

int32_t gr4d_backendrendertarget_get_width(const gr_backendrendertarget_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendRenderTarget(self)->width(), 0);
}

bool gr4d_backendrendertarget_is_valid(const gr_backendrendertarget_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendRenderTarget(self)->isValid(), false);
}

gr_backendtexture_t* gr4d_backendtexture_create_gl(int32_t width, int32_t height, bool is_mipmapped, const gr_gl_textureinfo_t* texture_info) {
    return SK4D_ONLY_GL(ToGrBackendTexture(new GrBackendTexture(GrBackendTextures::MakeGL(width, height, AsGrMipmapped(is_mipmapped), AsGrGLTextureInfo(texture_info)))), nullptr);
}

gr_backendtexture_t* gr4d_backendtexture_create_mtl(int32_t width, int32_t height, bool is_mipmapped, const gr_mtl_textureinfo_t* texture_info) {
    return SK4D_ONLY_METAL(ToGrBackendTexture(new GrBackendTexture(GrBackendTextures::MakeMtl(width, height, AsGrMipmapped(is_mipmapped), AsGrMtlTextureInfo(texture_info)))), nullptr);
}

gr_backendtexture_t* gr4d_backendtexture_create_vk(int32_t width, int32_t height, const gr_vk_imageinfo_t* image_info) {
    return SK4D_ONLY_VULKAN(ToGrBackendTexture(new GrBackendTexture(GrBackendTextures::MakeVk(width, height, AsGrVkImageInfo(image_info)))), nullptr);
}

void gr4d_backendtexture_destroy(gr_backendtexture_t* self) {
    SK4D_ONLY_GPU(delete AsGrBackendTexture(self);)
}

gr_backendapi_t gr4d_backendtexture_get_backend_api(const gr_backendtexture_t* self) {
    return SK4D_ONLY_GPU(ToGrBackendAPI(AsGrBackendTexture(self)->backend()), (gr_backendapi_t)0);
}

bool gr4d_backendtexture_get_gl_framebuffer_info(const gr_backendtexture_t* self, gr_gl_textureinfo_t* texture_info) {
    GrGLTextureInfo info;
    if (SK4D_ONLY_GL(GrBackendTextures::GetGLTextureInfo(*AsGrBackendTexture(self), &info), false)) {
      *texture_info = ToGrGLTextureInfo(info);
      return true;
    }
    return false;
}

int32_t gr4d_backendtexture_get_height(const gr_backendtexture_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendTexture(self)->height(), 0);
}

int32_t gr4d_backendtexture_get_width(const gr_backendtexture_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendTexture(self)->width(), 0);
}

bool gr4d_backendtexture_has_mipmaps(const gr_backendtexture_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendTexture(self)->hasMipmaps(), false);
}

bool gr4d_backendtexture_is_valid(const gr_backendtexture_t* self) {
    return SK4D_ONLY_GPU(AsGrBackendTexture(self)->isValid(), false);
}
