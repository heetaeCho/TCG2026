// File: poppler-document-convert-page-mode-test_2166.cc

#include <gtest/gtest.h>

// Include the public enums/types used by the helper.
#include "poppler/Catalog.h"
#include "poppler-document.h"

// NOTE:
// `convert_page_mode` is a `static` function in poppler-document.cc (internal linkage).
// To test it as a black box via its observable return values, we include the .cc so the
// symbol is available in this translation unit.
#include "poppler-document.cc"

namespace {

class ConvertPageModeTest_2166 : public ::testing::Test {};

TEST_F(ConvertPageModeTest_2166, OutlinesMapsToUseOutlines_2166)
{
    EXPECT_EQ(convert_page_mode(Catalog::pageModeOutlines), POPPLER_PAGE_MODE_USE_OUTLINES);
}

TEST_F(ConvertPageModeTest_2166, ThumbsMapsToUseThumbs_2166)
{
    EXPECT_EQ(convert_page_mode(Catalog::pageModeThumbs), POPPLER_PAGE_MODE_USE_THUMBS);
}

TEST_F(ConvertPageModeTest_2166, FullScreenMapsToFullScreen_2166)
{
    EXPECT_EQ(convert_page_mode(Catalog::pageModeFullScreen), POPPLER_PAGE_MODE_FULL_SCREEN);
}

TEST_F(ConvertPageModeTest_2166, OCMapsToUseOC_2166)
{
    EXPECT_EQ(convert_page_mode(Catalog::pageModeOC), POPPLER_PAGE_MODE_USE_OC);
}

TEST_F(ConvertPageModeTest_2166, AttachMapsToUseAttachments_2166)
{
    EXPECT_EQ(convert_page_mode(Catalog::pageModeAttach), POPPLER_PAGE_MODE_USE_ATTACHMENTS);
}

TEST_F(ConvertPageModeTest_2166, NoneMapsToUnsetBoundary_2166)
{
    // Boundary case: pageModeNone is explicitly enumerated; current behavior returns UNSET.
    EXPECT_EQ(convert_page_mode(Catalog::pageModeNone), POPPLER_PAGE_MODE_UNSET);
}

TEST_F(ConvertPageModeTest_2166, NullMapsToUnsetBoundary_2166)
{
    // Boundary case: pageModeNull is an extra enum value; behavior falls through to default.
    EXPECT_EQ(convert_page_mode(Catalog::pageModeNull), POPPLER_PAGE_MODE_UNSET);
}

TEST_F(ConvertPageModeTest_2166, UnknownValueMapsToUnsetErrorCase_2166)
{
    // Exceptional/error-ish case: value outside known enumerators should hit default.
    const auto unknown = static_cast<Catalog::PageMode>(999);
    EXPECT_EQ(convert_page_mode(unknown), POPPLER_PAGE_MODE_UNSET);
}

} // namespace