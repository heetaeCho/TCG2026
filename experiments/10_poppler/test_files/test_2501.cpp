#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "TextOutputDev.h"



using ::testing::_;

using ::testing::Return;

using ::testing::Invoke;



class MockPopplerPage : public PopplerPage {

public:

    MOCK_METHOD(std::shared_ptr<TextPage>, get_text_page, (), (override));

};



class MockTextPage : public TextPage {

public:

    MOCK_METHOD(std::vector<std::vector<std::unique_ptr<TextWordSelection>>>, getSelectionWords, (const PDFRectangle*, SelectionStyle), (override));

};



class MockTextWord : public TextWord {

public:

    MOCK_METHOD(void, getCharBBox, (int, double*, double*, double*, double*), (const, override));

    MOCK_METHOD(void, getBBox, (double*, double*, double*, double*) const, (override));

    MOCK_METHOD(bool, hasSpaceAfter, (), (const, override));

};



class MockTextWordSelection : public TextWordSelection {

public:

    MOCK_CONST_METHOD0(getWord, const TextWord*());

    MOCK_CONST_METHOD0(getBegin, int());

    MOCK_CONST_METHOD0(getEnd, int());

};



TEST_F(PopplerPageTest_2501, NormalOperation_ReturnsTrue_2501) {

    MockPopplerPage mock_page;

    MockTextPage mock_text_page;

    MockTextWordSelection mock_word_selection;

    MockTextWord mock_word;



    PDFRectangle selection(0., 0., 100., 100.);

    PopplerRectangle area = {0, 0, 100, 100};

    PopplerRectangle *rectangles;

    guint n_rectangles;



    EXPECT_CALL(mock_page, get_text_page()).WillOnce(Return(std::make_shared<MockTextPage>(mock_text_page)));



    std::vector<std::unique_ptr<TextWordSelection>> line_words;

    line_words.emplace_back(new MockTextWordSelection(&mock_word, 0, 1));



    std::vector<std::vector<std::unique_ptr<TextWordSelection>>> word_list = {std::move(line_words)};

    EXPECT_CALL(mock_text_page, getSelectionWords(_, selectionStyleGlyph)).WillOnce(Return(word_list));



    EXPECT_CALL(mock_word, getCharBBox(0, _, _, _, _)).Times(1);

    EXPECT_CALL(mock_word, getBBox(_, _, _, _)).Times(2).WillRepeatedly(Invoke([](double* x1, double* y1, double* x2, double* y2) {

        *x1 = 0.; *y1 = 0.; *x2 = 50.; *y2 = 50.;

    }));

    EXPECT_CALL(mock_word, hasSpaceAfter()).WillOnce(Return(false));



    gboolean result = poppler_page_get_text_layout_for_area(&mock_page, &area, &rectangles, &n_rectangles);

    EXPECT_TRUE(result);

    EXPECT_EQ(n_rectangles, 1);

    g_free(rectangles);

}



TEST_F(PopplerPageTest_2501, EmptySelection_ReturnsFalse_2501) {

    MockPopplerPage mock_page;

    MockTextPage mock_text_page;



    PDFRectangle selection(0., 0., 100., 100.);

    PopplerRectangle area = {0, 0, 100, 100};

    PopplerRectangle *rectangles;

    guint n_rectangles;



    EXPECT_CALL(mock_page, get_text_page()).WillOnce(Return(std::make_shared<MockTextPage>(mock_text_page)));



    std::vector<std::vector<std::unique_ptr<TextWordSelection>>> word_list = {};

    EXPECT_CALL(mock_text_page, getSelectionWords(_, selectionStyleGlyph)).WillOnce(Return(word_list));



    gboolean result = poppler_page_get_text_layout_for_area(&mock_page, &area, &rectangles, &n_rectangles);

    EXPECT_FALSE(result);

    EXPECT_EQ(n_rectangles, 0);

}



TEST_F(PopplerPageTest_2501, InvalidArea_ReturnsFalse_2501) {

    MockPopplerPage mock_page;

    PopplerRectangle area = {100, 100, 0, 0};

    PopplerRectangle *rectangles;

    guint n_rectangles;



    gboolean result = poppler_page_get_text_layout_for_area(&mock_page, &area, &rectangles, &n_rectangles);

    EXPECT_FALSE(result);

}



TEST_F(PopplerPageTest_2501, NullArea_ReturnsFalse_2501) {

    MockPopplerPage mock_page;

    PopplerRectangle *rectangles;

    guint n_rectangles;



    gboolean result = poppler_page_get_text_layout_for_area(&mock_page, nullptr, &rectangles, &n_rectangles);

    EXPECT_FALSE(result);

}



TEST_F(PopplerPageTest_2501, NullRectangles_ReturnsFalse_2501) {

    MockPopplerPage mock_page;

    PopplerRectangle area = {0, 0, 100, 100};

    guint n_rectangles;



    gboolean result = poppler_page_get_text_layout_for_area(&mock_page, &area, nullptr, &n_rectangles);

    EXPECT_FALSE(result);

}



TEST_F(PopplerPageTest_2501, NullNRectangles_ReturnsFalse_2501) {

    MockPopplerPage mock_page;

    PopplerRectangle area = {0, 0, 100, 100};

    PopplerRectangle *rectangles;



    gboolean result = poppler_page_get_text_layout_for_area(&mock_page, &area, &rectangles, nullptr);

    EXPECT_FALSE(result);

}



TEST_F(PopplerPageTest_2501, MultipleWords_ReturnsTrue_2501) {

    MockPopplerPage mock_page;

    MockTextPage mock_text_page;

    MockTextWordSelection mock_word_selection1;

    MockTextWordSelection mock_word_selection2;

    MockTextWord mock_word1;

    MockTextWord mock_word2;



    PDFRectangle selection(0., 0., 100., 100.);

    PopplerRectangle area = {0, 0, 100, 100};

    PopplerRectangle *rectangles;

    guint n_rectangles;



    EXPECT_CALL(mock_page, get_text_page()).WillOnce(Return(std::make_shared<MockTextPage>(mock_text_page)));



    std::vector<std::unique_ptr<TextWordSelection>> line_words;

    line_words.emplace_back(new MockTextWordSelection(&mock_word1, 0, 1));

    line_words.emplace_back(new MockTextWordSelection(&mock_word2, 0, 1));



    std::vector<std::vector<std::unique_ptr<TextWordSelection>>> word_list = {std::move(line_words)};

    EXPECT_CALL(mock_text_page, getSelectionWords(_, selectionStyleGlyph)).WillOnce(Return(word_list));



    EXPECT_CALL(mock_word1, getCharBBox(0, _, _, _, _)).Times(1);

    EXPECT_CALL(mock_word2, getCharBBox(0, _, _, _, _)).Times(1);



    EXPECT_CALL(mock_word1, getBBox(_, _, _, _)).Times(2).WillRepeatedly(Invoke([](double* x1, double* y1, double* x2, double* y2) {

        *x1 = 0.; *y1 = 0.; *x2 = 50.; *y2 = 50.;

    }));

    EXPECT_CALL(mock_word2, getBBox(_, _, _, _)).Times(2).WillRepeatedly(Invoke([](double* x1, double* y1, double* x2, double* y2) {

        *x1 = 50.; *y1 = 0.; *x2 = 100.; *y2 = 50.;

    }));



    EXPECT_CALL(mock_word1, hasSpaceAfter()).WillOnce(Return(true));

    EXPECT_CALL(mock_word2, hasSpaceAfter()).WillOnce(Return(false));



    gboolean result = poppler_page_get_text_layout_for_area(&mock_page, &area, &rectangles, &n_rectangles);

    EXPECT_TRUE(result);

    EXPECT_EQ(n_rectangles, 3);

    g_free(rectangles);

}
