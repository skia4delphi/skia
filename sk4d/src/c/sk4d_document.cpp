/*
 * Copyright (c) 2011-2026 Google LLC.
 * Copyright (c) 2021-2026 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 *
 */

#ifdef SK_SUPPORT_XPS
    #include <cstdlib>
    #include <mutex>
    #include <XpsObjectModel.h>
#if defined(SK_CODEC_ENCODES_PNG)
    #include "include/encode/SkPngEncoder.h"
#endif
#endif

#include "include/c/sk4d_document.h"
#include "src/c/sk4d_mapping.h"

#if defined(SK_CODEC_ENCODES_JPEG) && defined(SK_CODEC_DECODES_JPEG)
#include "include/docs/SkPDFJpegHelpers.h"
#endif

static SkPDF::Metadata prepare_pdf_metadata(SkPDF::Metadata metadata) {
#if defined(SK_CODEC_ENCODES_JPEG) && defined(SK_CODEC_DECODES_JPEG)
    metadata.jpegDecoder = SkPDF::JPEG::Decode;
    metadata.jpegEncoder = SkPDF::JPEG::Encode;
#else
    metadata.allowNoJpegs = true;
#endif
    return metadata;
}

#ifdef SK_SUPPORT_XPS
#ifdef __MINGW32__
const GUID __declspec(selectany) CLSID_XpsOMObjectFactory = { 0xe974d26d, 0x3d9b, 0x4d47, { 0x88, 0xcc, 0x38, 0x72, 0xf2, 0xdc, 0x35, 0x85 } };
#endif

static IXpsOMObjectFactory* g_xps_factory = nullptr;

static void destroy_xps_factory(void) {
    if (g_xps_factory)
        g_xps_factory->Release();
}

static void create_xps_factory(IXpsOMObjectFactory** factory) {
    if (SUCCEEDED(CoCreateInstance(CLSID_XpsOMObjectFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(factory))))
        atexit(destroy_xps_factory);
}

static IXpsOMObjectFactory* get_xps_factory(void) {
    static std::once_flag flag;
    std::call_once(flag, create_xps_factory, &g_xps_factory);
    return g_xps_factory;
}

static SkXPS::Options prepare_xps_options(float dpi) {
    SkXPS::Options options{.dpi = dpi};
#if defined(SK_CODEC_ENCODES_PNG)
    options.pngEncoder = [](SkWStream* stream, const SkPixmap& pixmap) {
        return SkPngEncoder::Encode(stream, pixmap, {});
    };
#else
    options.allowNoPngs = true;
#endif
    return options;
}
#endif

sk_canvas_t* sk4d_document_begin_page(sk_document_t* self, float width, float height, const sk_rect_t* content) {
    return ToCanvas(AsDocument(self)->beginPage(width, height, AsRect(content)));
}

void sk4d_document_close(sk_document_t* self) {
    AsDocument(self)->close();
}

void sk4d_document_end_page(sk_document_t* self) {
    AsDocument(self)->endPage();
}

sk_document_t* sk4d_document_make_pdf(sk_wstream_t* w_stream) {
    return ToDocument(SkPDF::MakeDocument(AsWStream(w_stream), prepare_pdf_metadata({})).release());
}

sk_document_t* sk4d_document_make_pdf2(sk_wstream_t* w_stream, const sk_pdfmetadata_t* metadata) {
    return ToDocument(SkPDF::MakeDocument(AsWStream(w_stream), prepare_pdf_metadata(AsPDFMetadata(metadata))).release());
}

sk_document_t* sk4d_document_make_xps(sk_wstream_t* w_stream, float dpi) {
    SK4D_ONLY_XPS(
        IXpsOMObjectFactory* factory = get_xps_factory();
    if (!factory)
            return nullptr;)
    return SK4D_ONLY_XPS(ToDocument(SkXPS::MakeDocument(
            AsWStream(w_stream), factory, prepare_xps_options(dpi)).release()), nullptr);
}

void sk4d_document_terminate(sk_document_t* self) {
    AsDocument(self)->abort();
}
