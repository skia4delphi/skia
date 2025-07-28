/*
 * Copyright (c) 2011-2025 Google LLC.
 * Copyright (c) 2021-2025 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef sk4d_comp_DEFINED
#define sk4d_comp_DEFINED

#include "include/core/SkFontMgr.h"
#include "include/core/SkTypeface.h"
#include "modules/skunicode/include/SkUnicode.h"

namespace Sk4DComp {

sk_sp<SkFontMgr> CustomFontMgrWithSystemFonts(sk_sp<SkFontMgr> customFontManager);
sk_sp<SkFontMgr> FontMgrRefDefault();
sk_sp<SkTypeface> MakeDefaultTypeface();
sk_sp<SkUnicode> UnicodeMake();

} // namespace Sk4DComp

#endif
