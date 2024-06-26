/*
 * Copyright 2022 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef skgpu_graphite_VulkanResourceProvider_DEFINED
#define skgpu_graphite_VulkanResourceProvider_DEFINED

#include "src/gpu/graphite/ResourceProvider.h"

namespace skgpu::graphite {

class VulkanResourceProvider final : public ResourceProvider {
public:
    VulkanResourceProvider(SharedContext* sharedContext, SingleOwner*);
    ~VulkanResourceProvider() override;

    sk_sp<Texture> createWrappedTexture(const BackendTexture&) override { return nullptr; }

private:
    sk_sp<GraphicsPipeline> createGraphicsPipeline(const SkRuntimeEffectDictionary*,
                                                   const GraphicsPipelineDesc&,
                                                   const RenderPassDesc&) override {
        return nullptr;
    }
    sk_sp<ComputePipeline> createComputePipeline(const ComputePipelineDesc&) override {
        return nullptr;
    }

    sk_sp<Texture> createTexture(SkISize, const TextureInfo&, SkBudgeted) override {
        return nullptr;
    }
    sk_sp<Buffer> createBuffer(size_t size, BufferType type, PrioritizeGpuReads) override {
        return nullptr;
    }

    sk_sp<Sampler> createSampler(const SkSamplingOptions&,
                                 SkTileMode xTileMode,
                                 SkTileMode yTileMode) override {
        return nullptr;
    }

    BackendTexture onCreateBackendTexture(SkISize dimensions, const TextureInfo&) override;
    void onDeleteBackendTexture(BackendTexture&) override {}
};

} // namespace skgpu::graphite

#endif // skgpu_graphite_VulkanResourceProvider_DEFINED
