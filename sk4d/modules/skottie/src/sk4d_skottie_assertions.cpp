/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <type_traits>

#include "src/c/sk4d_assertions.h"
#include "modules/skottie/include/sk4d_skottie_types.h"

#include "include/core/SkRefCnt.h"
#include "modules/skottie/include/Skottie.h"


/*
 * ASSERTIONS OF DEFINITIONS
 */

static_assert(static_cast<int>(skottie::Animation::kSkipTopLevelIsolation)   == SK_SKIP_TOP_LEVEL_ISOLATION_SK_SKOTTIE_ANIMATION_RENDER_FLAG,   "");
static_assert(static_cast<int>(skottie::Animation::kDisableTopLevelClipping) == SK_DISABLE_TOP_LEVEL_CLIPPING_SK_SKOTTIE_ANIMATION_RENDER_FLAG, "");


/*
 * ASSERTIONS OF REFERENCED OBJECT0S (NON-VIRTUAL)
 */

static_assert(!std::is_base_of<SkRefCnt, skottie::Animation>::value, "");
