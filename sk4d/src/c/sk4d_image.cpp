/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <memory>
#include <utility>

#include "include/c/sk4d_image.h"
#include "src/c/sk4d_mapping.h"
#include "src/image/SkImage_Base.h"
#include "src/codec/SkCodecImageGenerator.h"
#include "src/image/SkImageGeneratorPriv.h"

// DEPRECATED
bool sk4d_image_encode_to_file(const sk_image_t* self, const char file_name[], sk_encodedimageformat_t format, int32_t quality) {
    SkFILEWStream file(file_name);
    return sk4d_image_encode_to_stream(self, ToWStream(&file), format, quality);
}

// DEPRECATED
bool sk4d_image_encode_to_stream(const sk_image_t* self, sk_wstream_t* w_stream, sk_encodedimageformat_t format, int32_t quality) {
    SkBitmap bitmap;
    auto direct = as_IB(AsImage(self))->directContext();
    if (as_IB(AsImage(self))->getROPixels(direct, &bitmap)) {
        SkPixmap src;
        if (bitmap.peekPixels(&src)) {
            switch (format) {
                case PNG_SK_ENCODEDIMAGEFORMAT: {
                    return SkPngEncoder::Encode(AsWStream(w_stream), src, {});
                }
                case JPEG_SK_ENCODEDIMAGEFORMAT: {
                    SkJpegEncoder::Options opts;
                    opts.fQuality = quality;
                    return SkJpegEncoder::Encode(AsWStream(w_stream), src, opts);
                }
                case WEBP_SK_ENCODEDIMAGEFORMAT: {
                    SkWebpEncoder::Options opts;
                    opts.fQuality = quality;
                    return SkWebpEncoder::Encode(AsWStream(w_stream), src, opts);
                }
                default:
                    return false;
            }
        }   
    }
    return false;
}

sk_alphatype_t sk4d_image_get_alpha_type(const sk_image_t* self) {
    return ToAlphaType(AsImage(self)->alphaType());
}

sk_colorspace_t* sk4d_image_get_color_space(const sk_image_t* self) {
    return ToColorSpace(AsImage(self)->refColorSpace().release());
}

sk_colortype_t sk4d_image_get_color_type(const sk_image_t* self) {
    return ToColorType(AsImage(self)->colorType());
}

int32_t sk4d_image_get_height(const sk_image_t* self) {
    return AsImage(self)->height();
}

void sk4d_image_get_image_info(const sk_image_t* self, sk_imageinfo_t* result) {
    *result = ToImageInfo(AsImage(self)->imageInfo());
}

uint32_t sk4d_image_get_unique_id(const sk_image_t* self) {
    return AsImage(self)->uniqueID();
}

int32_t sk4d_image_get_width(const sk_image_t* self) {
    return AsImage(self)->width();
}

bool sk4d_image_is_lazy_generated(const sk_image_t* self) {
    return AsImage(self)->isLazyGenerated();
}

bool sk4d_image_is_texture_backed(const sk_image_t* self) {
    return AsImage(self)->isTextureBacked();
}

bool sk4d_image_is_valid(const sk_image_t* self, gr_directcontext_t* context) {
    return AsImage(self)->isValid(SK4D_ONLY_GPU(AsGrDirectContext(context), nullptr));
}

sk_image_t* sk4d_image_make_cross_context(gr_directcontext_t* context, const sk_pixmap_t* pixmap, bool build_mips, bool limit_to_max_texture_size) {
    return SK4D_ONLY_GPU(ToImage(SkImages::CrossContextTextureFromPixmap(AsGrDirectContext(context), AsPixmap(*pixmap), build_mips, limit_to_max_texture_size).release()), nullptr);

}

sk_image_t* sk4d_image_make_from_adopted_texture(gr_directcontext_t* context, const gr_backendtexture_t* texture, gr_surfaceorigin_t origin, sk_colortype_t color_type, sk_alphatype_t alpha_type, sk_colorspace_t* color_space) {
    return SK4D_ONLY_GPU(ToImage(SkImages::AdoptTextureFrom(AsGrDirectContext(context), AsGrBackendTexture(*texture), AsGrSurfaceOrigin(origin), AsColorType(color_type), AsAlphaType(alpha_type), sk_ref_sp(AsColorSpace(color_space))).release()), nullptr);
}

static sk_sp<SkImage> SkImageMakeFromEncoded(sk_sp<SkData> encoded) {
    if (!encoded || encoded->size() == 0)
        return nullptr;
    return SkImages::DeferredFromGenerator(SkCodecImageGenerator::MakeFromEncodedCodec(encoded));
}

// DEPRECATED
sk_image_t* sk4d_image_make_from_encoded_file(const char file_name[]) {
    auto data = SkData::MakeFromFileName(file_name);
    return ToImage(SkImageMakeFromEncoded(std::move(data)).release());
}

// DEPRECATED
sk_image_t* sk4d_image_make_from_encoded_stream(sk_stream_t* stream) {
    if (!AsStream(stream)->hasLength())
        return nullptr;
    auto data = SkData::MakeFromStream(AsStream(stream), AsStream(stream)->getLength());
    return ToImage(SkImageMakeFromEncoded(std::move(data)).release());
}

sk_image_t* sk4d_image_make_from_picture(sk_picture_t* picture, const sk_isize_t* dimensions, const sk_matrix_t* matrix, const sk_paint_t* paint, sk_colorspace_t* color_space, const sk_surfaceprops_t* props) {
    SkMatrix m;
    if (matrix)
        m = AsMatrix(matrix);
    std::unique_ptr<SkImageGenerator> gen;
    if (props)
        gen = SkImageGenerators::MakeFromPicture(AsISize(*dimensions), sk_ref_sp(AsPicture(picture)), (matrix) ? &m : nullptr, AsPaint(paint), SkImages::BitDepth::kU8, sk_ref_sp(AsColorSpace(color_space)), AsSurfaceProps(props));
    else
        gen = SkImageGenerators::MakeFromPicture(AsISize(*dimensions), sk_ref_sp(AsPicture(picture)), (matrix) ? &m : nullptr, AsPaint(paint), SkImages::BitDepth::kU8, sk_ref_sp(AsColorSpace(color_space)));
    return ToImage(SkImages::DeferredFromGenerator(std::move(gen)).release());
}

sk_image_t* sk4d_image_make_from_raster(const sk_pixmap_t* pixmap, sk_image_raster_release_proc proc, void* proc_context) {
    return ToImage(SkImages::RasterFromPixmap(AsPixmap(*pixmap), proc, proc_context).release());
}

sk_image_t* sk4d_image_make_from_texture(gr_directcontext_t* context, const gr_backendtexture_t* texture, gr_surfaceorigin_t origin, sk_colortype_t color_type, sk_alphatype_t alpha_type, sk_colorspace_t* color_space, sk_image_texture_release_proc proc, void* proc_context) {
    return SK4D_ONLY_GPU(ToImage(SkImages::BorrowTextureFrom(AsGrDirectContext(context), AsGrBackendTexture(*texture), AsGrSurfaceOrigin(origin), AsColorType(color_type), AsAlphaType(alpha_type), sk_ref_sp(AsColorSpace(color_space)), proc, proc_context).release()), nullptr);
}

sk_image_t* sk4d_image_make_non_texture_image(const sk_image_t* self) {
    return ToImage(AsImage(self)->makeNonTextureImage().release());
}

sk_image_t* sk4d_image_make_raster_copy(const sk_pixmap_t* pixmap) {
    return ToImage(SkImages::RasterFromPixmapCopy(AsPixmap(*pixmap)).release());
}

sk_image_t* sk4d_image_make_raster_image(const sk_image_t* self) {
    return ToImage(AsImage(self)->makeRasterImage().release());
}

sk_shader_t* sk4d_image_make_raw_shader(const sk_image_t* self, sk_tilemode_t tile_mode_x, sk_tilemode_t tile_mode_y, const sk_samplingoptions_t* sampling, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    return ToShader(AsImage(self)->makeRawShader(AsTileMode(tile_mode_x), AsTileMode(tile_mode_y), AsSamplingOptions(*sampling), (local_matrix) ? &m : nullptr).release());
}

sk_shader_t* sk4d_image_make_shader(const sk_image_t* self, sk_tilemode_t tile_mode_x, sk_tilemode_t tile_mode_y, const sk_samplingoptions_t* sampling, const sk_matrix_t* local_matrix) {
    SkMatrix m;
    if (local_matrix)
        m = AsMatrix(local_matrix);
    return ToShader(AsImage(self)->makeShader(AsTileMode(tile_mode_x), AsTileMode(tile_mode_y), AsSamplingOptions(*sampling), (local_matrix) ? &m : nullptr).release());
}

sk_image_t* sk4d_image_make_subset(const sk_image_t* self, const sk_irect_t* subset, gr_directcontext_t* context) {
    return ToImage(AsImage(self)->makeSubset(SK4D_ONLY_GPU(AsGrDirectContext(context), nullptr), AsIRect(*subset)).release());
}

sk_image_t* sk4d_image_make_texture_image(const sk_image_t* self, gr_directcontext_t* context, bool is_mipmapped) {
    SK4D_ONLY_GPU(auto r = SkImages::TextureFromImage(AsGrDirectContext(context), AsImage(self), AsGrMipmapped(is_mipmapped));)
    return SK4D_ONLY_GPU(ToImage(r.release()), nullptr);
}

sk_image_t* sk4d_image_make_with_filter(const sk_image_t* self, gr_directcontext_t* context, const sk_imagefilter_t* filter, const sk_irect_t* subset, const sk_irect_t* clip_bounds, sk_irect_t* out_subset, sk_ipoint_t* offset) {
    SK4D_ONLY_GPU(
        if (context)
            return ToImage(SkImages::MakeWithFilter(AsGrDirectContext(context), sk_ref_sp(AsImage(self)), AsImageFilter(filter), AsIRect(*subset), AsIRect(*clip_bounds), AsIRect(out_subset), AsIPoint(offset)).release());)
    return ToImage(SkImages::MakeWithFilter(sk_ref_sp(AsImage(self)), AsImageFilter(filter), AsIRect(*subset), AsIRect(*clip_bounds), AsIRect(out_subset), AsIPoint(offset)).release());
}

sk_pixmap_t* sk4d_image_peek_pixels(const sk_image_t* self) {
    auto r = std::make_unique<SkPixmap>();
    return AsImage(self)->peekPixels(r.get()) ? ToPixmap(r.release()) : nullptr;
}

bool sk4d_image_read_pixels(const sk_image_t* self, gr_directcontext_t* context, const sk_pixmap_t* dest, int32_t src_x, int32_t src_y, sk_imagecachinghint_t caching_hint) {
    return AsImage(self)->readPixels(SK4D_ONLY_GPU(AsGrDirectContext(context), nullptr), AsPixmap(*dest), src_x, src_y, AsImageCachingHint(caching_hint));
}

bool sk4d_image_scale_pixels(const sk_image_t* self, const sk_pixmap_t* dest, const sk_samplingoptions_t* sampling, sk_imagecachinghint_t caching_hint) {
    return AsImage(self)->scalePixels(AsPixmap(*dest), AsSamplingOptions(*sampling), AsImageCachingHint(caching_hint));
}
