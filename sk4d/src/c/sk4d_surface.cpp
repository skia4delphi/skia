/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <memory>

#include "include/c/sk4d_surface.h"
#include "src/c/sk4d_mapping.h"

void sk4d_surface_draw(sk_surface_t* self, sk_canvas_t* canvas, float x, float y, sk_paint_t* paint) {
    AsSurface(self)->draw(AsCanvas(canvas), x, y, AsPaint(paint));
}

// DEPRECATED
void sk4d_surface_flush(sk_surface_t* self) {
    SK4D_ONLY_GPU(
        auto direct = AsSurface(self)->recordingContext()->asDirectContext();
        if (direct)
        direct->flush(AsSurface(self));)
}

// DEPRECATED
void sk4d_surface_flush_and_submit(sk_surface_t* self, gr_backendsemaphore_t* semaphores[], int32_t count, const gr_backendsurfacemutablestate_t* new_state, bool sync_cpu) {
    SK4D_ONLY_GPU(
        auto direct = AsSurface(self)->recordingContext()->asDirectContext();
        if (direct) {
            GrFlushInfo info;
            std::vector<GrBackendSemaphore> vector;
            vector.reserve(count);
            for (size_t i = 0; i < count; i++)
                vector.emplace_back(*AsGrBackendSemaphore(semaphores[i]));
            info.fNumSemaphores = count;
            info.fSignalSemaphores = vector.data();

          direct->flush(AsSurface(self), info, AsGrBackendSurfaceMutableState(new_state));
          direct->submit(AsGrSyncCpu(sync_cpu));
        })
}

sk_canvas_t* sk4d_surface_get_canvas(sk_surface_t* self) {
    return ToCanvas(AsSurface(self)->getCanvas());
}

void sk4d_surface_get_props(const sk_surface_t* self, sk_surfaceprops_t* result) {
    *result = ToSurfaceProps(AsSurface(self)->props());
}

sk_surface_t* sk4d_surface_make_from_mtk_view(gr_directcontext_t* context, gr_mtl_handle_t view, gr_surfaceorigin_t origin, int32_t sample_count, sk_colortype_t color_type, sk_colorspace_t* color_space, const sk_surfaceprops_t* props) {
    SK4D_ONLY_METAL(
        SkSurfaceProps surface_props;
        if (props)
            SkSurfaceProps surface_props = AsSurfaceProps(props);)
    return SK4D_ONLY_METAL(ToSurface(SkSurfaces::WrapMTKView(AsGrDirectContext(context), view, AsGrSurfaceOrigin(origin), sample_count, AsColorType(color_type), sk_ref_sp(AsColorSpace(color_space)), (props) ? &surface_props : nullptr).release()), nullptr);
}

sk_surface_t* sk4d_surface_make_from_render_target(gr_directcontext_t* context, const gr_backendrendertarget_t* render_target, gr_surfaceorigin_t origin, sk_colortype_t color_type, sk_colorspace_t* color_space, const sk_surfaceprops_t* props) {
    SK4D_ONLY_GPU(
        SkSurfaceProps surface_props;
        if (props)
            SkSurfaceProps surface_props = AsSurfaceProps(props);)
    return SK4D_ONLY_GPU(ToSurface(SkSurfaces::WrapBackendRenderTarget(AsGrDirectContext(context), AsGrBackendRenderTarget(*render_target), AsGrSurfaceOrigin(origin), AsColorType(color_type), sk_ref_sp(AsColorSpace(color_space)), (props) ? &surface_props : nullptr).release()), nullptr);
}

sk_surface_t* sk4d_surface_make_from_texture(gr_directcontext_t* context, const gr_backendtexture_t* texture, gr_surfaceorigin_t origin, int32_t sample_count, sk_colortype_t color_type, sk_colorspace_t* color_space, const sk_surfaceprops_t* props) {
    SK4D_ONLY_GPU(
        SkSurfaceProps surface_props;
        if (props)
            SkSurfaceProps surface_props = AsSurfaceProps(props);)
    return SK4D_ONLY_GPU(ToSurface(SkSurfaces::WrapBackendTexture(AsGrDirectContext(context), AsGrBackendTexture(*texture), AsGrSurfaceOrigin(origin), sample_count, AsColorType(color_type), sk_ref_sp(AsColorSpace(color_space)), (props) ? &surface_props : nullptr).release()), nullptr);
}

sk_image_t* sk4d_surface_make_image_snapshot(sk_surface_t* self) {
    return ToImage(AsSurface(self)->makeImageSnapshot().release());
}

sk_image_t* sk4d_surface_make_image_snapshot2(sk_surface_t* self, const sk_irect_t* bounds) {
    return ToImage(AsSurface(self)->makeImageSnapshot(AsIRect(*bounds)).release());
}

sk_surface_t* sk4d_surface_make_raster(const sk_imageinfo_t* image_info, size_t row_bytes, const sk_surfaceprops_t* props) {
    SkSurfaceProps surface_props;
    if (props)
        SkSurfaceProps surface_props = AsSurfaceProps(props);
    return ToSurface(SkSurfaces::Raster(AsImageInfo(image_info), row_bytes, (props) ? &surface_props : nullptr).release());
}

sk_surface_t* sk4d_surface_make_raster_direct(const sk_pixmap_t* pixmap, sk_surface_raster_release_proc proc, void* proc_context, const sk_surfaceprops_t* props) {
    SkSurfaceProps surface_props;
    if (props)
        SkSurfaceProps surface_props = AsSurfaceProps(props);
    return ToSurface(SkSurfaces::WrapPixels(AsPixmap(pixmap)->info(), AsPixmap(pixmap)->writable_addr(), AsPixmap(pixmap)->rowBytes(), proc, proc_context, (props) ? &surface_props : nullptr, true).release());
}

sk_surface_t* sk4d_surface_make_render_target(gr_directcontext_t* context, bool is_budgeted, const sk_imageinfo_t *image_info, int32_t sample_count, gr_surfaceorigin_t origin, const sk_surfaceprops_t* props, bool should_create_with_mips) {
    SK4D_ONLY_GPU(
        SkSurfaceProps surface_props;
        if (props)
            SkSurfaceProps surface_props = AsSurfaceProps(props);)
    return SK4D_ONLY_GPU(ToSurface(SkSurfaces::RenderTarget(AsGrDirectContext(context), AsBudgeted(is_budgeted), AsImageInfo(image_info), sample_count, AsGrSurfaceOrigin(origin), (props) ? &surface_props : nullptr, should_create_with_mips).release()), nullptr);
}

sk_pixmap_t* sk4d_surface_peek_pixels(sk_surface_t* self) {
    auto r = std::make_unique<SkPixmap>();
    return AsSurface(self)->peekPixels(r.get()) ? ToPixmap(r.release()) : nullptr;
}

bool sk4d_surface_read_pixels(sk_surface_t* self, const sk_pixmap_t* dest, int32_t src_x, int32_t src_y) {
    return AsSurface(self)->readPixels(AsPixmap(*dest), src_x, src_y);
}

void sk4d_surface_wait(sk_surface_t* self, const gr_backendsemaphore_t* semaphores[], int32_t count) {
    SK4D_ONLY_GPU(
        GrFlushInfo info;
        std::vector<GrBackendSemaphore> vector;
        vector.reserve(count);
        for (size_t i = 0; i < count; i++)
            vector.emplace_back(*AsGrBackendSemaphore(semaphores[i]));
        AsSurface(self)->wait(count, vector.data());)
}

void sk4d_surface_write_pixels(sk_surface_t* self, const sk_pixmap_t* src, int32_t dest_x, int32_t dest_y) {
    AsSurface(self)->writePixels(AsPixmap(*src), dest_x, dest_y);
}