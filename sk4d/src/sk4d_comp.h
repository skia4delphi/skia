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

sk_sp<SkFontMgr> SkFontMgrRefDefault();
sk_sp<SkTypeface> SkTypefaceRefDefault();

//------------------------------------------------------------------------------

#include "modules/skunicode/include/SkUnicode.h"

sk_sp<SkUnicode> SkUnicodeMake();

#endif
