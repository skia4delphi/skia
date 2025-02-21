/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/c/sk4d_imageencoder.h"
#include "src/c/sk4d_mapping.h"

bool sk4d_imageencoder_encode_to_file(const char file_name[], const sk_pixmap_t* src, sk_encodedimageformat_t format, int32_t quality) {
    SkFILEWStream file(file_name);
    return sk4d_imageencoder_encode_to_stream(ToWStream(&file), src, format, quality);
}

bool sk4d_imageencoder_encode_to_stream(sk_wstream_t* w_stream, const sk_pixmap_t* src, sk_encodedimageformat_t format, int32_t quality) {
    switch (format) {
        case PNG_SK_ENCODEDIMAGEFORMAT: {
            return SkPngEncoder::Encode(AsWStream(w_stream), AsPixmap(*src), {});
        }
        case JPEG_SK_ENCODEDIMAGEFORMAT: {
            SkJpegEncoder::Options opts;
            opts.fQuality = quality;
            return SkJpegEncoder::Encode(AsWStream(w_stream), AsPixmap(*src), opts);
        }
        case WEBP_SK_ENCODEDIMAGEFORMAT: {
            SkWebpEncoder::Options opts;
            opts.fQuality = quality;
            return SkWebpEncoder::Encode(AsWStream(w_stream), AsPixmap(*src), opts);
        }
        default:
            return false;
    }
    return false;
}
