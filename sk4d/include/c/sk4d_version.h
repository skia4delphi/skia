/*
 * Copyright (c) 2011-2026 Google LLC.
 * Copyright (c) 2021-2026 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef sk4d_version_DEFINED
#define sk4d_version_DEFINED

#include "include/c/sk4d_types.h"

#define SK4D_VERSION_MAJOR 151
#define SK4D_VERSION_MINOR 1
#define SK4D_VERSION_PATCH 0

SK4D_C_PLUS_PLUS_BEGIN_GUARD

SK4D_API void sk4d_version_get(/*out*/ int32_t* major, /*out*/ int32_t* minor, /*out*/ int32_t* patch);

SK4D_C_PLUS_PLUS_END_GUARD

#endif
