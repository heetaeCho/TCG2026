// File: poppler-document-convert-page-layout-test.cc
//
// Unit tests for convert_page_layout() in glib/poppler-document.cc
//
// NOTE: This is a black-box test of the observable mapping defined by the
// public enums and the function signature shown in the prompt. We do not
// depend on any internal state.
//
// The production function is `static` in poppler-document.cc. To test it
// without re-implementing logic, we compile-link the implementation unit into
// this test TU by including the .cc after temporarily redefining `static`.
// This is a common unit-testing technique for file-local helpers.

#include <gtest/gtest.h>

// Minimal includes for the enums used by the interface snippet.
#include "poppler-document.h"
#include "Catalog.h"

// Expose file-local `static` for testing by including the implementation unit.
// (No internal logic is re-implemented here; we call the real function.)
#pragma push_macro("static")
#undef static
#define static /* exposed_for_test */
#include "poppler-document.cc"
#pragma pop_macro("static")

namespace {

class ConvertPageLayoutTest_2165 : public ::testing::Test {};

// Normal operation: each known Catalog::PageLayout maps to the expected PopplerPageLayout.
TEST_F(ConvertPageLayoutTest_2165, MapsSinglePage_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutSinglePage),
            POPPLER_PAGE_LAYOUT_SINGLE_PAGE);
}

TEST_F(ConvertPageLayoutTest_2165, MapsOneColumn_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutOneColumn),
            POPPLER_PAGE_LAYOUT_ONE_COLUMN);
}

TEST_F(ConvertPageLayoutTest_2165, MapsTwoColumnLeft_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutTwoColumnLeft),
            POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT);
}

TEST_F(ConvertPageLayoutTest_2165, MapsTwoColumnRight_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutTwoColumnRight),
            POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT);
}

TEST_F(ConvertPageLayoutTest_2165, MapsTwoPageLeft_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutTwoPageLeft),
            POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT);
}

TEST_F(ConvertPageLayoutTest_2165, MapsTwoPageRight_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutTwoPageRight),
            POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);
}

// Boundary / default handling: explicit "none" should map to UNSET.
TEST_F(ConvertPageLayoutTest_2165, MapsNoneToUnset_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutNone),
            POPPLER_PAGE_LAYOUT_UNSET);
}

// Error / exceptional (observable) cases: values not listed explicitly in the switch
// must follow the default path and map to UNSET.
// We test both a known extra enum value (pageLayoutNull) and an out-of-range cast.
TEST_F(ConvertPageLayoutTest_2165, MapsNullEnumToUnset_2165) {
  EXPECT_EQ(convert_page_layout(Catalog::pageLayoutNull),
            POPPLER_PAGE_LAYOUT_UNSET);
}

TEST_F(ConvertPageLayoutTest_2165, MapsOutOfRangeValueToUnset_2165) {
  const auto bogus = static_cast<Catalog::PageLayout>(-1);
  EXPECT_EQ(convert_page_layout(bogus), POPPLER_PAGE_LAYOUT_UNSET);

  const auto too_large = static_cast<Catalog::PageLayout>(9999);
  EXPECT_EQ(convert_page_layout(too_large), POPPLER_PAGE_LAYOUT_UNSET);
}

}  // namespace