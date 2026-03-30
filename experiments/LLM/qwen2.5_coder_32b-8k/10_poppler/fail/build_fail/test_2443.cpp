#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "PDFRectangle.h"

#include "TextOutputDev.h"



using namespace testing;



class MockPopplerPage : public PopplerPage {

public:

    MOCK_METHOD(std::shared_ptr<TextPage>, get_text_page, (), (override));

};



TEST_F(MockPopplerPageTest_2443, GetSelectedText_GlyphStyle_ReturnsValidString_2443) {

    MockPopplerPage mockPage;

    auto mockTextPage = std::make_shared<NiceMock<MockTextPage>>();

    EXPECT_CALL(mockPage, get_text_page()).WillOnce(Return(mockTextPage));



    ON_CALL(*mockTextPage, getSelectionText(_, _)).WillByDefault(Return(GooString("Sample Text")));



    PopplerRectangle selectionRect{0.1, 0.2, 0.3, 0.4};

    char* result = poppler_page_get_selected_text(&mockPage, POPPLER_SELECTION_GLYPH, &selectionRect);



    ASSERT_STREQ(result, "Sample Text");

    g_free(result);

}



TEST_F(MockPopplerPageTest_2443, GetSelectedText_WordStyle_ReturnsValidString_2443) {

    MockPopplerPage mockPage;

    auto mockTextPage = std::make_shared<NiceMock<MockTextPage>>();

    EXPECT_CALL(mockPage, get_text_page()).WillOnce(Return(mockTextPage));



    ON_CALL(*mockTextPage, getSelectionText(_, _)).WillByDefault(Return(GooString("Sample Word")));



    PopplerRectangle selectionRect{0.1, 0.2, 0.3, 0.4};

    char* result = poppler_page_get_selected_text(&mockPage, POPPLER_SELECTION_WORD, &selectionRect);



    ASSERT_STREQ(result, "Sample Word");

    g_free(result);

}



TEST_F(MockPopplerPageTest_2443, GetSelectedText_LineStyle_ReturnsValidString_2443) {

    MockPopplerPage mockPage;

    auto mockTextPage = std::make_shared<NiceMock<MockTextPage>>();

    EXPECT_CALL(mockPage, get_text_page()).WillOnce(Return(mockTextPage));



    ON_CALL(*mockTextPage, getSelectionText(_, _)).WillByDefault(Return(GooString("Sample Line")));



    PopplerRectangle selectionRect{0.1, 0.2, 0.3, 0.4};

    char* result = poppler_page_get_selected_text(&mockPage, POPPLER_SELECTION_LINE, &selectionRect);



    ASSERT_STREQ(result, "Sample Line");

    g_free(result);

}



TEST_F(MockPopplerPageTest_2443, GetSelectedText_NullSelection_ReturnsNull_2443) {

    MockPopplerPage mockPage;

    EXPECT_CALL(mockPage, get_text_page()).Times(0);



    char* result = poppler_page_get_selected_text(&mockPage, POPPLER_SELECTION_GLYPH, nullptr);



    ASSERT_EQ(result, nullptr);

}



TEST_F(MockPopplerPageTest_2443, GetSelectedText_NullPage_ReturnsNull_2443) {

    MockPopplerPage mockPage;

    EXPECT_CALL(mockPage, get_text_page()).Times(0);



    PopplerRectangle selectionRect{0.1, 0.2, 0.3, 0.4};

    char* result = poppler_page_get_selected_text(nullptr, POPPLER_SELECTION_GLYPH, &selectionRect);



    ASSERT_EQ(result, nullptr);

}



TEST_F(MockPopplerPageTest_2443, GetSelectedText_EmptySelection_ReturnsEmptyString_2443) {

    MockPopplerPage mockPage;

    auto mockTextPage = std::make_shared<NiceMock<MockTextPage>>();

    EXPECT_CALL(mockPage, get_text_page()).WillOnce(Return(mockTextPage));



    ON_CALL(*mockTextPage, getSelectionText(_, _)).WillByDefault(Return(GooString("")));



    PopplerRectangle selectionRect{0.1, 0.2, 0.3, 0.4};

    char* result = poppler_page_get_selected_text(&mockPage, POPPLER_SELECTION_GLYPH, &selectionRect);



    ASSERT_STREQ(result, "");

    g_free(result);

}
