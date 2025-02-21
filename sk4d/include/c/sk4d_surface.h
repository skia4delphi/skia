/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef sk4d_surface_DEFINED
#define sk4d_surface_DEFINED

#include "include/c/sk4d_types.h"

SK4D_C_PLUS_PLUS_BEGIN_GUARD

SK4D_API void sk4d_surface_draw(sk_surface_t* self, sk_canvas_t* canvas, float x, float y, sk_paint_t* paint);
SK4D_API void sk4d_surface_flush(sk_surface_t* self);
SK4D_API void sk4d_surface_flush_and_submit(sk_surface_t* self, gr_backendsemaphore_t* semaphores[], int32_t count, const gr_backendsurfacemutablestate_t* new_state, bool sync_cpu);
SK4D_API sk_canvas_t* sk4d_surface_get_canvas(sk_surface_t* self);
SK4D_API void sk4d_surface_get_props(const sk_surface_t* self, /*out*/ sk_surfaceprops_t* result);
SK4D_API sk_surface_t* sk4d_surface_make_from_mtk_view(gr_directcontext_t* context, gr_mtl_handle_t view, gr_surfaceorigin_t origin, int32_t sample_count, sk_colortype_t color_type, sk_colorspace_t* color_space, const sk_surfaceprops_t* props);
SK4D_API sk_surface_t* sk4d_surface_make_from_render_target(gr_directcontext_t* context, const gr_backendrendertarget_t* render_target, gr_surfaceorigin_t origin, sk_colortype_t color_type, sk_colorspace_t* color_space, const sk_surfaceprops_t* props);
SK4D_API sk_surface_t* sk4d_surface_make_from_texture(gr_directcontext_t* context, const gr_backendtexture_t* texture, gr_surfaceorigin_t origin, int32_t sample_count, sk_colortype_t color_type, sk_colorspace_t* color_space, const sk_surfaceprops_t* props);
SK4D_API sk_image_t* sk4d_surface_make_image_snapshot(sk_surface_t* self);
SK4D_API sk_image_t* sk4d_surface_make_image_snapshot2(sk_surface_t* self, const sk_irect_t* bounds);
SK4D_API sk_surface_t* sk4d_surface_make_raster(const sk_imageinfo_t* image_info, size_t row_bytes, const sk_surfaceprops_t* props);
SK4D_API sk_surface_t* sk4d_surface_make_raster_direct(const sk_pixmap_t* pixmap, sk_surface_raster_release_proc proc, void* proc_context, const sk_surfaceprops_t* props);
SK4D_API sk_surface_t* sk4d_surface_make_render_target(gr_directcontext_t* context, bool is_budgeted, const sk_imageinfo_t* image_info, int32_t sample_count, gr_surfaceorigin_t origin, const sk_surfaceprops_t* props, bool should_create_with_mips);
SK4D_API sk_pixmap_t* sk4d_surface_peek_pixels(sk_surface_t* self);
SK4D_API bool sk4d_surface_read_pixels(sk_surface_t* self, const sk_pixmap_t* dest, int32_t src_x, int32_t src_y);
SK4D_API void sk4d_surface_wait(sk_surface_t* self, const gr_backendsemaphore_t* semaphores[], int32_t count);
SK4D_API void sk4d_surface_write_pixels(sk_surface_t* self, const sk_pixmap_t* src, int32_t dest_x, int32_t dest_y);

SK4D_C_PLUS_PLUS_END_GUARD

#endif
