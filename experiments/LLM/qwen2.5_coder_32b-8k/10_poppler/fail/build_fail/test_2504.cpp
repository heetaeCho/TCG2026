#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



using namespace testing;



class PopplerPageTest_2504 : public Test {

protected:

    void SetUp() override {

        page = new _PopplerPage();

        page->text = std::make_shared<TextPage>();

        area = new PopplerRectangle{0, 0, 100, 100};

    }



    void TearDown() override {

        delete area;

        delete page;

    }



    _PopplerPage* page;

    PopplerRectangle* area;

};



TEST_F(PopplerPageTest_2504, GetTextAttributesForArea_ReturnsNullWhenNoWordsFound_2504) {

    EXPECT_CALL(*page->text, getSelectionWords(_, _)).WillOnce(Return(std::vector<std::vector<std::unique_ptr<TextWordSelection>>>{});

    GList* result = poppler_page_get_text_attributes_for_area(page, area);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2504, GetTextAttributesForArea_ReturnsValidGListWhenWordsFound_2504) {

    auto word1 = std::make_unique<TextWordSelection>(nullptr, 0, 5);

    auto word2 = std::make_unique<TextWordSelection>(nullptr, 6, 10);



    std::vector<std::unique_ptr<TextWordSelection>> line_words;

    line_words.push_back(std::move(word1));

    line_words.push_back(std::move(word2));



    std::vector<std::vector<std::unique_ptr<TextWordSelection>>> word_list;

    word_list.push_back(std::move(line_words));



    EXPECT_CALL(*page->text, getSelectionWords(_, _)).WillOnce(Return(word_list));



    GList* result = poppler_page_get_text_attributes_for_area(page, area);

    EXPECT_NE(result, nullptr);



    g_list_free_full(result, (GDestroyNotify)poppler_text_attributes_free);

}



TEST_F(PopplerPageTest_2504, GetTextAttributesForArea_HandlesBoundaryConditions_2504) {

    PopplerRectangle small_area{0, 0, 1, 1};



    auto word = std::make_unique<TextWordSelection>(nullptr, 0, 1);



    std::vector<std::unique_ptr<TextWordSelection>> line_words;

    line_words.push_back(std::move(word));



    std::vector<std::vector<std::unique_ptr<TextWordSelection>>> word_list;

    word_list.push_back(std::move(line_words));



    EXPECT_CALL(*page->text, getSelectionWords(_, _)).WillOnce(Return(word_list));



    GList* result = poppler_page_get_text_attributes_for_area(page, &small_area);

    EXPECT_NE(result, nullptr);



    g_list_free_full(result, (GDestroyNotify)poppler_text_attributes_free);

}



TEST_F(PopplerPageTest_2504, GetTextAttributesForArea_ReturnsNullWhenInvalidAreaProvided_2504) {

    PopplerRectangle invalid_area{100, 100, 90, 90};

    GList* result = poppler_page_get_text_attributes_for_area(page, &invalid_area);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2504, GetTextAttributesForArea_ReturnsNullWhenNullAreaProvided_2504) {

    GList* result = poppler_page_get_text_attributes_for_area(page, nullptr);

    EXPECT_EQ(result, nullptr);

}
