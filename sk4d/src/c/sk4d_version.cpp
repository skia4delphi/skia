/*
 * Copyright (c) 2011-2026 Google LLC.
 * Copyright (c) 2021-2026 Skia4Delphi Project.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/c/sk4d_version.h"

void sk4d_version_get(int32_t* major, int32_t* minor, int32_t* patch) {
    *major = SK4D_VERSION_MAJOR;
    *minor = SK4D_VERSION_MINOR;
    *patch = SK4D_VERSION_PATCH;
}
