#include <gtest/gtest.h>



using namespace Catalog;



TEST(convert_page_mode_Test_2166, NormalOperation_PageModeOutlines_2166) {

    EXPECT_EQ(convert_page_mode(pageModeOutlines), POPPLER_PAGE_MODE_USE_OUTLINES);

}



TEST(convert_page_mode_Test_2166, NormalOperation_PageModeThumbs_2166) {

    EXPECT_EQ(convert_page_mode(pageModeThumbs), POPPLER_PAGE_MODE_USE_THUMBS);

}



TEST(convert_page_mode_Test_2166, NormalOperation_PageModeFullScreen_2166) {

    EXPECT_EQ(convert_page_mode(pageModeFullScreen), POPPLER_PAGE_MODE_FULL_SCREEN);

}



TEST(convert_page_mode_Test_2166, NormalOperation_PageModeOC_2166) {

    EXPECT_EQ(convert_page_mode(pageModeOC), POPPLER_PAGE_MODE_USE_OC);

}



TEST(convert_page_mode_Test_2166, NormalOperation_PageModeAttach_2166) {

    EXPECT_EQ(convert_page_mode(pageModeAttach), POPPLER_PAGE_MODE_USE_ATTACHMENTS);

}



TEST(convert_page_mode_Test_2166, BoundaryCondition_PageModeNone_2166) {

    EXPECT_EQ(convert_page_mode(pageModeNone), POPPLER_PAGE_MODE_UNSET);

}



TEST(convert_page_mode_Test_2166, BoundaryCondition_DefaultCase_2166) {

    EXPECT_EQ(convert_page_mode(static_cast<PageMode>(99)), POPPLER_PAGE_MODE_UNSET);

}
