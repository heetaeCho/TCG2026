#include <gtest/gtest.h>

// Include necessary headers based on the provided dependencies
// We need to replicate the enums and the function signature for testing

// Forward declarations / definitions based on provided code
namespace Catalog {
enum PageMode {
    pageModeNone = 0,
    pageModeOutlines = 1,
    pageModeThumbs = 2,
    pageModeFullScreen = 3,
    pageModeOC = 4,
    pageModeAttach = 5,
    pageModeNull = 6
};
}

enum PopplerPageMode {
    POPPLER_PAGE_MODE_UNSET = 0,
    POPPLER_PAGE_MODE_NONE = 1,
    POPPLER_PAGE_MODE_USE_OUTLINES = 2,
    POPPLER_PAGE_MODE_USE_THUMBS = 3,
    POPPLER_PAGE_MODE_FULL_SCREEN = 4,
    POPPLER_PAGE_MODE_USE_OC = 5,
    POPPLER_PAGE_MODE_USE_ATTACHMENTS = 6
};

// The function under test - declared as static in the original file,
// we re-declare it here for testing purposes
static PopplerPageMode convert_page_mode(Catalog::PageMode pageMode)
{
    switch (pageMode) {
    case Catalog::pageModeOutlines:
        return POPPLER_PAGE_MODE_USE_OUTLINES;
    case Catalog::pageModeThumbs:
        return POPPLER_PAGE_MODE_USE_THUMBS;
    case Catalog::pageModeFullScreen:
        return POPPLER_PAGE_MODE_FULL_SCREEN;
    case Catalog::pageModeOC:
        return POPPLER_PAGE_MODE_USE_OC;
    case Catalog::pageModeAttach:
        return POPPLER_PAGE_MODE_USE_ATTACHMENTS;
    case Catalog::pageModeNone:
    default:
        return POPPLER_PAGE_MODE_UNSET;
    }
}

class ConvertPageModeTest_2166 : public ::testing::Test {
protected:
    void SetUp() override { }
    void TearDown() override { }
};

// Test normal operation: pageModeOutlines maps to POPPLER_PAGE_MODE_USE_OUTLINES
TEST_F(ConvertPageModeTest_2166, PageModeOutlines_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_USE_OUTLINES, convert_page_mode(Catalog::pageModeOutlines));
}

// Test normal operation: pageModeThumbs maps to POPPLER_PAGE_MODE_USE_THUMBS
TEST_F(ConvertPageModeTest_2166, PageModeThumbs_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_USE_THUMBS, convert_page_mode(Catalog::pageModeThumbs));
}

// Test normal operation: pageModeFullScreen maps to POPPLER_PAGE_MODE_FULL_SCREEN
TEST_F(ConvertPageModeTest_2166, PageModeFullScreen_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_FULL_SCREEN, convert_page_mode(Catalog::pageModeFullScreen));
}

// Test normal operation: pageModeOC maps to POPPLER_PAGE_MODE_USE_OC
TEST_F(ConvertPageModeTest_2166, PageModeOC_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_USE_OC, convert_page_mode(Catalog::pageModeOC));
}

// Test normal operation: pageModeAttach maps to POPPLER_PAGE_MODE_USE_ATTACHMENTS
TEST_F(ConvertPageModeTest_2166, PageModeAttach_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_USE_ATTACHMENTS, convert_page_mode(Catalog::pageModeAttach));
}

// Test normal operation: pageModeNone maps to POPPLER_PAGE_MODE_UNSET
TEST_F(ConvertPageModeTest_2166, PageModeNone_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_UNSET, convert_page_mode(Catalog::pageModeNone));
}

// Test boundary/default case: pageModeNull is not explicitly handled, should fall through to default (UNSET)
TEST_F(ConvertPageModeTest_2166, PageModeNull_FallsToDefault_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_UNSET, convert_page_mode(Catalog::pageModeNull));
}

// Test boundary case: an invalid/unknown enum value should fall through to default (UNSET)
TEST_F(ConvertPageModeTest_2166, InvalidPageMode_FallsToDefault_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_UNSET, convert_page_mode(static_cast<Catalog::PageMode>(99)));
}

// Test boundary case: negative invalid enum value should fall through to default (UNSET)
TEST_F(ConvertPageModeTest_2166, NegativePageMode_FallsToDefault_2166)
{
    EXPECT_EQ(POPPLER_PAGE_MODE_UNSET, convert_page_mode(static_cast<Catalog::PageMode>(-1)));
}

// Test that each valid mapping produces a distinct result
TEST_F(ConvertPageModeTest_2166, AllMappingsAreDistinct_2166)
{
    PopplerPageMode results[] = {
        convert_page_mode(Catalog::pageModeNone),
        convert_page_mode(Catalog::pageModeOutlines),
        convert_page_mode(Catalog::pageModeThumbs),
        convert_page_mode(Catalog::pageModeFullScreen),
        convert_page_mode(Catalog::pageModeOC),
        convert_page_mode(Catalog::pageModeAttach),
    };

    // Check that outlines, thumbs, fullscreen, OC, and attach all produce different results
    for (int i = 1; i < 6; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            EXPECT_NE(results[i], results[j])
                << "Mapping at index " << i << " and " << j << " should be distinct";
        }
    }
}

// Test that pageModeNone and pageModeNull both map to the same value (UNSET)
TEST_F(ConvertPageModeTest_2166, NoneAndNullBothMapToUnset_2166)
{
    EXPECT_EQ(convert_page_mode(Catalog::pageModeNone), convert_page_mode(Catalog::pageModeNull));
}

// Test exact return values for all valid enum values
TEST_F(ConvertPageModeTest_2166, ExactReturnValues_2166)
{
    EXPECT_EQ(0, static_cast<int>(convert_page_mode(Catalog::pageModeNone)));
    EXPECT_EQ(2, static_cast<int>(convert_page_mode(Catalog::pageModeOutlines)));
    EXPECT_EQ(3, static_cast<int>(convert_page_mode(Catalog::pageModeThumbs)));
    EXPECT_EQ(4, static_cast<int>(convert_page_mode(Catalog::pageModeFullScreen)));
    EXPECT_EQ(5, static_cast<int>(convert_page_mode(Catalog::pageModeOC)));
    EXPECT_EQ(6, static_cast<int>(convert_page_mode(Catalog::pageModeAttach)));
}
