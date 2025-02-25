#include "src/sk4d_comp.h"

#include <mutex>
#include "include/core/SkFontStyle.h"

#ifdef SK_FONTMGR_FONTCONFIG_AVAILABLE
#include "include/ports/SkFontMgr_fontconfig.h"
#include "include/ports/SkFontScanner_FreeType.h"
#endif

#ifdef SK_FONTMGR_CORETEXT_AVAILABLE
#include "include/ports/SkFontMgr_mac_ct.h"
#endif

#ifdef SK_FONTMGR_DIRECTWRITE_AVAILABLE
#include "include/ports/SkTypeface_win.h"
#endif

#ifdef SK_FONTMGR_FREETYPE_DIRECTORY_AVAILABLE
#include "include/ports/SkFontMgr_directory.h"
#endif

#ifndef SK_FONT_FILE_PREFIX
    #if defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)
        #define SK_FONT_FILE_PREFIX "/System/Library/Fonts/"
    #else
        #define SK_FONT_FILE_PREFIX "/usr/share/fonts/"
    #endif
#endif

#if defined(SK_UNICODE_ICU_IMPLEMENTATION)
#include "modules/skunicode/include/SkUnicode_icu.h"
#endif

#if defined(SK_UNICODE_LIBGRAPHEME_IMPLEMENTATION)
#include "modules/skunicode/include/SkUnicode_libgrapheme.h"
#endif

#if defined(SK_UNICODE_ICU4X_IMPLEMENTATION)
#include "modules/skunicode/include/SkUnicode_icu4x.h"
#endif

sk_sp<SkFontMgr> Sk4DComp::FontMgrRefDefault() {
    static std::once_flag once;
    static sk_sp<SkFontMgr> singleton;
    std::call_once(once, []{
#if defined(SK_FONTMGR_FONTCONFIG_AVAILABLE)
        singleton = SkFontMgr_New_FontConfig(nullptr, SkFontScanner_Make_FreeType());
#elif defined(SK_FONTMGR_CORETEXT_AVAILABLE)
        singleton = SkFontMgr_New_CoreText(nullptr);
#elif defined(SK_FONTMGR_DIRECTWRITE_AVAILABLE)
        singleton = SkFontMgr_New_DirectWrite();
#elif defined(SK_FONTMGR_FREETYPE_DIRECTORY_AVAILABLE)
        singleton = SkFontMgr_New_Custom_Directory(SK_FONT_FILE_PREFIX);
#else
        singleton = SkFontMgr::RefEmpty();
#endif
    });
    return singleton;
}

static SkTypeface* GetDefaultTypeface() {
    static std::once_flag once;
    static sk_sp<SkTypeface> singleton;
    std::call_once(once, []{
        sk_sp<SkFontMgr> fm(Sk4DComp::FontMgrRefDefault());
        auto t = fm->legacyMakeTypeface(nullptr, SkFontStyle(SkFontStyle::kNormal_Weight, SkFontStyle::kNormal_Width, SkFontStyle::kUpright_Slant));
        singleton = t ? t : SkTypeface::MakeEmpty();
    });
    return singleton.get();
}

sk_sp<SkTypeface> Sk4DComp::MakeDefaultTypeface() {
    return sk_ref_sp(GetDefaultTypeface());
}

sk_sp<SkUnicode> Sk4DComp::UnicodeMake() {
#if defined(SK_UNICODE_ICU_IMPLEMENTATION)
    if (auto unicode = SkUnicodes::ICU::Make()) {
        return unicode;
    }
#endif
#if defined(SK_UNICODE_LIBGRAPHEME_IMPLEMENTATION)
    if (auto unicode = SkUnicodes::Libgrapheme::Make()) {
        return unicode;
    }
#endif
#if defined(SK_UNICODE_ICU4X_IMPLEMENTATION)
    if (auto unicode = SkUnicodes::ICU4X::Make()) {
        return unicode;
    }
#endif
    return nullptr;
}
