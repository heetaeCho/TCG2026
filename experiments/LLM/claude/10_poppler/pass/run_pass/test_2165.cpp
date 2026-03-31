#include <gtest/gtest.h>

// Include necessary headers
// We need to replicate or include the enums and the function under test

// From Catalog.h
namespace Catalog {
enum PageLayout {
    pageLayoutNone = 0,
    pageLayoutSinglePage = 1,
    pageLayoutOneColumn = 2,
    pageLayoutTwoColumnLeft = 3,
    pageLayoutTwoColumnRight = 4,
    pageLayoutTwoPageLeft = 5,
    pageLayoutTwoPageRight = 6,
    pageLayoutNull = 7
};
}

// From poppler-document.h
enum PopplerPageLayout {
    POPPLER_PAGE_LAYOUT_UNSET = 0,
    POPPLER_PAGE_LAYOUT_SINGLE_PAGE = 1,
    POPPLER_PAGE_LAYOUT_ONE_COLUMN = 2,
    POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT = 3,
    POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT = 4,
    POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT = 5,
    POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT = 6
};

// The function under test (from poppler-document.cc)
static PopplerPageLayout convert_page_layout(Catalog::PageLayout pageLayout)
{
    switch (pageLayout) {
    case Catalog::pageLayoutSinglePage:
        return POPPLER_PAGE_LAYOUT_SINGLE_PAGE;
    case Catalog::pageLayoutOneColumn:
        return POPPLER_PAGE_LAYOUT_ONE_COLUMN;
    case Catalog::pageLayoutTwoColumnLeft:
        return POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT;
    case Catalog::pageLayoutTwoColumnRight:
        return POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT;
    case Catalog::pageLayoutTwoPageLeft:
        return POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT;
    case Catalog::pageLayoutTwoPageRight:
        return POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT;
    case Catalog::pageLayoutNone:
    default:
        return POPPLER_PAGE_LAYOUT_UNSET;
    }
}

class ConvertPageLayoutTest_2165 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(ConvertPageLayoutTest_2165, SinglePageLayout_2165)
{
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_SINGLE_PAGE, convert_page_layout(Catalog::pageLayoutSinglePage));
}

TEST_F(ConvertPageLayoutTest_2165, OneColumnLayout_2165)
{
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_ONE_COLUMN, convert_page_layout(Catalog::pageLayoutOneColumn));
}

TEST_F(ConvertPageLayoutTest_2165, TwoColumnLeftLayout_2165)
{
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT, convert_page_layout(Catalog::pageLayoutTwoColumnLeft));
}

TEST_F(ConvertPageLayoutTest_2165, TwoColumnRightLayout_2165)
{
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT, convert_page_layout(Catalog::pageLayoutTwoColumnRight));
}

TEST_F(ConvertPageLayoutTest_2165, TwoPageLeftLayout_2165)
{
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT, convert_page_layout(Catalog::pageLayoutTwoPageLeft));
}

TEST_F(ConvertPageLayoutTest_2165, TwoPageRightLayout_2165)
{
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT, convert_page_layout(Catalog::pageLayoutTwoPageRight));
}

// Boundary / special cases

TEST_F(ConvertPageLayoutTest_2165, NoneLayoutReturnsUnset_2165)
{
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_UNSET, convert_page_layout(Catalog::pageLayoutNone));
}

TEST_F(ConvertPageLayoutTest_2165, NullLayoutReturnsUnset_2165)
{
    // pageLayoutNull is not explicitly handled, should fall to default -> UNSET
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_UNSET, convert_page_layout(Catalog::pageLayoutNull));
}

TEST_F(ConvertPageLayoutTest_2165, UnknownValueReturnsUnset_2165)
{
    // Casting an out-of-range integer to the enum to test default case
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_UNSET, convert_page_layout(static_cast<Catalog::PageLayout>(100)));
}

TEST_F(ConvertPageLayoutTest_2165, NegativeValueReturnsUnset_2165)
{
    // Negative value should also hit the default case
    EXPECT_EQ(POPPLER_PAGE_LAYOUT_UNSET, convert_page_layout(static_cast<Catalog::PageLayout>(-1)));
}

// Verify all valid enum values map correctly (comprehensive check)

TEST_F(ConvertPageLayoutTest_2165, AllValidMappingsAreCorrect_2165)
{
    struct TestCase {
        Catalog::PageLayout input;
        PopplerPageLayout expected;
    };

    TestCase cases[] = {
        { Catalog::pageLayoutNone, POPPLER_PAGE_LAYOUT_UNSET },
        { Catalog::pageLayoutSinglePage, POPPLER_PAGE_LAYOUT_SINGLE_PAGE },
        { Catalog::pageLayoutOneColumn, POPPLER_PAGE_LAYOUT_ONE_COLUMN },
        { Catalog::pageLayoutTwoColumnLeft, POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT },
        { Catalog::pageLayoutTwoColumnRight, POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT },
        { Catalog::pageLayoutTwoPageLeft, POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT },
        { Catalog::pageLayoutTwoPageRight, POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT },
        { Catalog::pageLayoutNull, POPPLER_PAGE_LAYOUT_UNSET },
    };

    for (const auto &tc : cases) {
        EXPECT_EQ(tc.expected, convert_page_layout(tc.input))
            << "Failed for input enum value: " << static_cast<int>(tc.input);
    }
}

// Verify return type consistency

TEST_F(ConvertPageLayoutTest_2165, ReturnTypeIsValidPopplerEnum_2165)
{
    PopplerPageLayout result = convert_page_layout(Catalog::pageLayoutSinglePage);
    EXPECT_GE(result, POPPLER_PAGE_LAYOUT_UNSET);
    EXPECT_LE(result, POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);
}

TEST_F(ConvertPageLayoutTest_2165, DefaultCaseReturnTypeIsValidPopplerEnum_2165)
{
    PopplerPageLayout result = convert_page_layout(static_cast<Catalog::PageLayout>(999));
    EXPECT_GE(result, POPPLER_PAGE_LAYOUT_UNSET);
    EXPECT_LE(result, POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);
}
