#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-page.cc"

#include "./TestProjects/poppler/poppler/TextOutputDev.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class MockTextPage : public TextPage {

public:

    MOCK_METHOD(bool, findText, (const Unicode * s, int len, bool startAtTop, bool stopAtBottom, bool startAtLast, bool stopAtLast, bool caseSensitive, bool ignoreDiacritics, bool matchAcrossLines, bool backward, bool wholeWord, double * xMin, double * yMin, double * xMax, double * yMax), (override));

};



class PageDataTest : public ::testing::Test {

protected:

    std::unique_ptr<MockTextPage> mock_text_page_;

    QVector<Unicode> search_text_;

    double s_left_, s_top_, s_right_, s_bottom_;



    void SetUp() override {

        mock_text_page_ = std::make_unique<MockTextPage>();

        search_text_.append('t');

        search_text_.append('e');

        search_text_.append('s');

        search_text_.append('t');

        s_left_ = 0.0;

        s_top_ = 0.0;

        s_right_ = 0.0;

        s_bottom_ = 0.0;

    }

};



TEST_F(PageDataTest, PerformSingleTextSearch_FromTop_Success_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, true, true, false, false, false, false, false, false, false, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(true));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::FromTop, false, false, false, false);



    EXPECT_TRUE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_NextResult_Success_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, false, true, true, false, false, false, false, false, false, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(true));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::NextResult, false, false, false, false);



    EXPECT_TRUE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_PreviousResult_Success_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, false, true, true, false, false, false, false, true, false, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(true));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::PreviousResult, false, false, false, false);



    EXPECT_TRUE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_InvalidDirection_Failure_1442) {

    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, static_cast<Page::SearchDirection>(-1), false, false, false, false);



    EXPECT_FALSE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_CaseSensitive_Success_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, true, true, false, false, true, false, false, false, false, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(true));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::FromTop, true, false, false, false);



    EXPECT_TRUE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_WholeWords_Success_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, true, true, false, false, false, false, true, false, false, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(true));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::FromTop, false, true, false, false);



    EXPECT_TRUE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_IgnoreDiacritics_Success_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, true, true, false, false, false, true, false, false, false, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(true));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::FromTop, false, false, true, false);



    EXPECT_TRUE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_MatchAcrossLines_Success_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, true, true, false, false, false, false, false, false, true, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(true));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::FromTop, false, false, false, true);



    EXPECT_TRUE(result);

}



TEST_F(PageDataTest, PerformSingleTextSearch_NoMatch_Failure_1442) {

    EXPECT_CALL(*mock_text_page_, findText(_, _, true, true, false, false, false, false, false, false, false, &s_left_, &s_top_, &s_right_, &s_bottom_))

        .WillOnce(Return(false));



    PageData page_data;

    bool result = page_data.performSingleTextSearch(mock_text_page_.get(), search_text_, s_left_, s_top_, s_right_, s_bottom_, Page::FromTop, false, false, false, false);



    EXPECT_FALSE(result);

}
