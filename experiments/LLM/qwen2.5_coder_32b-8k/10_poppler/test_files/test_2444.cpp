#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler.h"



// Mocking external collaborators if necessary

class MockPopplerPage {

public:

    MOCK_METHOD(void, poppler_page_get_size, (PopplerRectangle *), ());

    MOCK_METHOD(char*, poppler_page_get_selected_text, (PopplerSelectionStyle style, PopplerRectangle *rect), ());

};



extern "C" {

    char* poppler_page_get_text(PopplerPage* page) {

        static MockPopplerPage mock;

        PopplerRectangle rectangle = { 0, 0, 0, 0 };

        g_return_val_if_fail(POPPLER_IS_PAGE(page), NULL);

        mock.poppler_page_get_size(&rectangle.x2, &rectangle.y2);

        return mock.poppler_page_get_selected_text(POPPLER_SELECTION_GLYPH, &rectangle);

    }

}



class PopplerPageTest_2444 : public ::testing::Test {

protected:

    MockPopplerPage* mock;

    PopplerPage page;



    void SetUp() override {

        mock = new MockPopplerPage();

    }



    void TearDown() override {

        delete mock;

    }

};



TEST_F(PopplerPageTest_2444, NormalOperation_2444) {

    PopplerRectangle rect = {0, 0, 100, 100};

    EXPECT_CALL(*mock, poppler_page_get_size(testing::_))

        .WillOnce(testing::SetArgReferee<0>(rect.y2));

    EXPECT_CALL(*mock, poppler_page_get_selected_text(POPPLER_SELECTION_GLYPH, testing::_))

        .WillOnce(testing::Return(const_cast<char*>("Sample Text")));



    char* result = poppler_page_get_text(&page);

    ASSERT_STREQ(result, "Sample Text");

}



TEST_F(PopplerPageTest_2444, BoundaryCondition_ZeroSize_2444) {

    PopplerRectangle rect = {0, 0, 0, 0};

    EXPECT_CALL(*mock, poppler_page_get_size(testing::_))

        .WillOnce(testing::SetArgReferee<0>(rect.y2));

    EXPECT_CALL(*mock, poppler_page_get_selected_text(POPPLER_SELECTION_GLYPH, testing::_))

        .WillOnce(testing::Return(nullptr));



    char* result = poppler_page_get_text(&page);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2444, InvalidPagePointer_2444) {

    EXPECT_CALL(*mock, poppler_page_get_size(testing::_)).Times(0);

    EXPECT_CALL(*mock, poppler_page_get_selected_text(testing::_, testing::_)).Times(0);



    char* result = poppler_page_get_text(nullptr);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2444, ExternalInteraction_CallbackInvocation_2444) {

    PopplerRectangle rect = {0, 0, 100, 100};

    EXPECT_CALL(*mock, poppler_page_get_size(testing::_))

        .WillOnce(testing::SetArgReferee<0>(rect.y2));

    EXPECT_CALL(*mock, poppler_page_get_selected_text(POPPLER_SELECTION_GLYPH, testing::_))

        .WillOnce(testing::Return(const_cast<char*>("Sample Text")));



    char* result = poppler_page_get_text(&page);

    ASSERT_STREQ(result, "Sample Text");

}
