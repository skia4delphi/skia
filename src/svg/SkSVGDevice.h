/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGDevice_DEFINED
#define SkSVGDevice_DEFINED

#include "include/core/SkCanvas.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkSpan.h"
#include "include/core/SkString.h"
#include "include/core/SkTypes.h"
#include "include/private/SkTArray.h"
#include "include/private/SkTypeTraits.h"
#include "include/svg/SkSVGCanvas.h"
#include "include/utils/SkParsePath.h"
#include "src/core/SkClipStackDevice.h"

#include <cstdint>
#include <memory>

namespace sktext {
class GlyphRunList;
}

class SkDevice;
class SkBitmap;
class SkBlender;
class SkClipStack;
class SkData;
class SkImage;
class SkMesh;
class SkPaint;
class SkPath;
class SkRRect;
class SkSpecialImage;
class SkVertices;
class SkXMLWriter;
struct SkISize;
struct SkPoint;
struct SkRect;
struct SkSamplingOptions;

class SkSVGDevice final : public SkClipStackDevice {
public:
    static sk_sp<SkDevice> Make(const SkISize& size,
                                std::unique_ptr<SkXMLWriter>,
                                SkSVGCanvas::Options opts);

    void drawPaint(const SkPaint& paint) override;
    void drawAnnotation(const SkRect& rect, const char key[], SkData* value) override;
    void drawPoints(SkCanvas::PointMode, SkSpan<const SkPoint>, const SkPaint&) override;
    void drawImageRect(const SkImage* image, const SkRect* src, const SkRect& dst,
                       const SkSamplingOptions&, const SkPaint& paint,
                       SkCanvas::SrcRectConstraint constraint) override;
    void drawRect(const SkRect& r, const SkPaint& paint) override;
    void drawOval(const SkRect& oval, const SkPaint& paint) override;
    void drawRRect(const SkRRect& rr, const SkPaint& paint) override;
    void drawPath(const SkPath& path,
                  const SkPaint& paint) override;

    void drawVertices(const SkVertices*, sk_sp<SkBlender>, const SkPaint&, bool) override;
    void drawMesh(const SkMesh&, sk_sp<SkBlender>, const SkPaint&) override;

    sk_sp<SkDevice> createDevice(const CreateInfo&, const SkPaint* layerPaint) override;
    void drawDevice(SkDevice*, const SkSamplingOptions&, const SkPaint&) override;
    void drawSpecial(SkSpecialImage*, const SkMatrix& localToDevice, const SkSamplingOptions&,
                     const SkPaint&, SkCanvas::SrcRectConstraint) override;

private:
    SkSVGDevice(const SkISize& size, std::unique_ptr<SkXMLWriter>, SkSVGCanvas::Options);
    // Layer device, which writes its content in place through the parent's writer.
    SkSVGDevice(const SkISize& size, SkSVGDevice* parent);
    ~SkSVGDevice() override;

    void onDrawGlyphRunList(SkCanvas*, const sktext::GlyphRunList&, const SkPaint& paint) override;

    struct MxCp;
    void drawBitmapCommon(const MxCp&, const SkBitmap& bm, const SkPaint& paint);

    void syncClipStack(const SkClipStack&);

    // All devices write in the root device space, so layer content needs no extra transform.
    SkMatrix localToGlobal(const SkMatrix& localToDevice) const;
    SkRect globalClipBounds() const;

    void closeActiveLayer();
    void closeLayer();

    SkParsePath::PathEncoding pathEncoding() const;

    class AutoElement;
    class ResourceBucket;

    std::unique_ptr<SkXMLWriter>    fOwnedWriter;
    SkXMLWriter*                    fWriter;
    std::unique_ptr<ResourceBucket> fOwnedResourceBucket;
    ResourceBucket*                 fResourceBucket;
    const SkSVGCanvas::Options      fOpts;

    SkSVGDevice* fParent      = nullptr;
    SkSVGDevice* fActiveLayer = nullptr;
    // Mask written by the last luminance layer, applied by the next kSrcIn layer.
    SkString     fPendingMaskID;

    struct ClipRec {
        std::unique_ptr<AutoElement> fClipPathElem;
        uint32_t                     fGenID;

        static_assert(::sk_is_trivially_relocatable<decltype(fClipPathElem)>::value);

        using sk_is_trivially_relocatable = std::true_type;
    };

    std::unique_ptr<AutoElement> fRootElement;
    skia_private::TArray<ClipRec> fClipStack;
};

#endif // SkSVGDevice_DEFINED
