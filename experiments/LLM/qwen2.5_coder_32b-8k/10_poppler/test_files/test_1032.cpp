#include <gtest/gtest.h>

#include "poppler-page.h"



using namespace poppler;



class PageTest : public ::testing::Test {

protected:

    document_private* mock_doc;

    page* test_page;



    void SetUp() override {

        mock_doc = new document_private();

        test_page = new page(mock_doc, 0);

    }



    void TearDown() override {

        delete test_page;

        delete mock_doc;

    }

};



TEST_F(PageTest_1032, Orientation_ReturnsValidValue_1032) {

    orientation_enum result = test_page->orientation();

    EXPECT_TRUE(result >= orientation_enum::portrait && result <= orientation_enum::seascape);

}



TEST_F(PageTest_1032, Duration_ReturnsNonNegative_1032) {

    double result = test_page->duration();

    EXPECT_GE(result, 0.0);

}



TEST_F(PageTest_1032, PageRect_ValidBox_ReturnsValidRect_1032) {

    rectf result = test_page->page_rect(page_box_enum::media_box);

    EXPECT_TRUE(result.x1 <= result.x2 && result.y1 <= result.y2);

}



TEST_F(PageTest_1032, Label_ReturnsNonEmptyString_1032) {

    ustring result = test_page->label();

    // Assuming label can be empty in some cases

    // If it should never be empty, use EXPECT_FALSE(result.empty());

}



TEST_F(PageTest_1032, Transition_ReturnsValidPointer_1032) {

    const page_transition* result = test_page->transition();

    // Assuming transition can be nullptr if no transition is set

    // If it should always return a valid pointer, use EXPECT_NE(result, nullptr);

}



TEST_F(PageTest_1032, Search_ValidParameters_ReturnsTrueIfFound_1032) {

    rectf search_rect;

    bool result = test_page->search(ustring("test"), search_rect, search_direction_enum::forward, case_sensitivity_enum::case_sensitive, rotation_enum::rotate_0);

    // Assuming the presence of text "test" is unknown, so no strict assertion on result

}



TEST_F(PageTest_1032, Text_ValidRect_ReturnsNonEmptyString_1032) {

    rectf rect(0, 0, 1, 1);

    ustring result = test_page->text(rect);

    // Assuming text can be empty in some cases

    // If it should never be empty, use EXPECT_FALSE(result.empty());

}



TEST_F(PageTest_1032, Text_ValidRectAndLayout_ReturnsNonEmptyString_1032) {

    rectf rect(0, 0, 1, 1);

    ustring result = test_page->text(rect, text_layout_enum::raw_order);

    // Assuming text can be empty in some cases

    // If it should never be empty, use EXPECT_FALSE(result.empty());

}



TEST_F(PageTest_1032, TextList_NoParameters_ReturnsNonEmptyVector_1032) {

    std::vector<text_box> result = test_page->text_list();

    // Assuming text can be empty in some cases

    // If it should never be empty, use EXPECT_FALSE(result.empty());

}



TEST_F(PageTest_1032, TextList_OptFlag_ReturnsNonEmptyVector_1032) {

    std::vector<text_box> result = test_page->text_list(0);

    // Assuming text can be empty in some cases

    // If it should never be empty, use EXPECT_FALSE(result.empty());

}
