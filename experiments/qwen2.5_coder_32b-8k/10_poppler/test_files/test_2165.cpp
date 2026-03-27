#include <gtest/gtest.h>

#include "./TestProjects/poppler/glib/poppler-document.h"

#include "./TestProjects/poppler/poppler/Catalog.h"



using namespace Catalog;



TEST(ConvertPageLayoutTest_2165, SinglePageConversion_2165) {

    EXPECT_EQ(convert_page_layout(pageLayoutSinglePage), POPPLER_PAGE_LAYOUT_SINGLE_PAGE);

}



TEST(ConvertPageLayoutTest_2165, OneColumnConversion_2165) {

    EXPECT_EQ(convert_page_layout(pageLayoutOneColumn), POPPLER_PAGE_LAYOUT_ONE_COLUMN);

}



TEST(ConvertPageLayoutTest_2165, TwoColumnLeftConversion_2165) {

    EXPECT_EQ(convert_page_layout(pageLayoutTwoColumnLeft), POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT);

}



TEST(ConvertPageLayoutTest_2165, TwoColumnRightConversion_2165) {

    EXPECT_EQ(convert_page_layout(pageLayoutTwoColumnRight), POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT);

}



TEST(ConvertPageLayoutTest_2165, TwoPageLeftConversion_2165) {

    EXPECT_EQ(convert_page_layout(pageLayoutTwoPageLeft), POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT);

}



TEST(ConvertPageLayoutTest_2165, TwoPageRightConversion_2165) {

    EXPECT_EQ(convert_page_layout(pageLayoutTwoPageRight), POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);

}



TEST(ConvertPageLayoutTest_2165, NoneConversion_2165) {

    EXPECT_EQ(convert_page_layout(pageLayoutNone), POPPLER_PAGE_LAYOUT_UNSET);

}



TEST(ConvertPageLayoutTest_2165, DefaultCaseConversion_2165) {

    EXPECT_EQ(convert_page_layout(static_cast<PageLayout>(-1)), POPPLER_PAGE_LAYOUT_UNSET);

}
