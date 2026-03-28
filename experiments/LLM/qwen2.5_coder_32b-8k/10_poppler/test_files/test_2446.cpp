#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



// Mock class for TextPage to simulate its behavior

class MockTextPage : public TextPage {

public:

    MOCK_METHOD10(findText, bool(gunichar*, glong, bool, bool, gboolean, bool, bool, bool, bool, double*, double*, double*, double*, PDFRectangle*, bool*));

};



// Test fixture for PopplerPage

class PopplerPageTest : public ::testing::Test {

protected:

    void SetUp() override {

        page = new PopplerPage();

        text_page = std::make_shared<MockTextPage>();

        page->text = text_page;

    }



    void TearDown() override {

        delete page;

    }



    PopplerPage* page;

    std::shared_ptr<MockTextPage> text_page;

};



// Normal operation: find single match

TEST_F(PopplerPageTest, FindSingleMatch_2446) {

    gunichar ucs4_text[] = {'t', 'e', 's', 't'};

    double xMin = 1.0, yMin = 1.0, xMax = 2.0, yMax = 2.0;

    PDFRectangle continueMatch;

    bool ignoredHyphen;



    EXPECT_CALL(*text_page, findText(ucs4_text, 4, _, _, false, false, false, false, false, &xMin, &yMin, &xMax, &yMax, testing::_, &ignoredHyphen))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<9>(PDFRectangle(1.0, 1.0, 2.0, 2.0)),

            testing::Return(true)))

        .WillOnce(testing::Return(false));



    GList* matches = poppler_page_find_text_with_options(page, "test", POPPLER_FIND_DEFAULT);

    ASSERT_EQ(g_list_length(matches), 1);



    PopplerRectangleExtended* match = static_cast<PopplerRectangleExtended*>(matches->data);

    EXPECT_DOUBLE_EQ(match->x1, 1.0);

    EXPECT_DOUBLE_EQ(match->y1, 2.0); // Assuming height is 3 for this test

    EXPECT_DOUBLE_EQ(match->x2, 2.0);

    EXPECT_DOUBLE_EQ(match->y2, 1.0);



    g_list_free(matches);

}



// Normal operation: find multiple matches

TEST_F(PopplerPageTest, FindMultipleMatches_2446) {

    gunichar ucs4_text[] = {'t', 'e', 's', 't'};

    double xMin = 1.0, yMin = 1.0, xMax = 2.0, yMax = 2.0;

    PDFRectangle continueMatch;

    bool ignoredHyphen;



    EXPECT_CALL(*text_page, findText(ucs4_text, 4, _, _, false, false, false, false, false, &xMin, &yMin, &xMax, &yMax, testing::_, &ignoredHyphen))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<9>(PDFRectangle(1.0, 1.0, 2.0, 2.0)),

            testing::Return(true)))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<9>(PDFRectangle(3.0, 3.0, 4.0, 4.0)),

            testing::Return(true)))

        .WillOnce(testing::Return(false));



    GList* matches = poppler_page_find_text_with_options(page, "test", POPPLER_FIND_DEFAULT);

    ASSERT_EQ(g_list_length(matches), 2);



    PopplerRectangleExtended* match1 = static_cast<PopplerRectangleExtended*>(matches->data);

    EXPECT_DOUBLE_EQ(match1->x1, 1.0);

    EXPECT_DOUBLE_EQ(match1->y1, 2.0); // Assuming height is 3 for this test

    EXPECT_DOUBLE_EQ(match1->x2, 2.0);

    EXPECT_DOUBLE_EQ(match1->y2, 1.0);



    PopplerRectangleExtended* match2 = static_cast<PopplerRectangleExtended*>(matches->next->data);

    EXPECT_DOUBLE_EQ(match2->x1, 3.0);

    EXPECT_DOUBLE_EQ(match2->y1, 1.0); // Assuming height is 4 for this test

    EXPECT_DOUBLE_EQ(match2->x2, 4.0);

    EXPECT_DOUBLE_EQ(match2->y2, 0.0);



    g_list_free(matches);

}



// Boundary condition: no matches found

TEST_F(PopplerPageTest, NoMatchesFound_2446) {

    gunichar ucs4_text[] = {'t', 'e', 's', 't'};

    double xMin = 1.0, yMin = 1.0, xMax = 2.0, yMax = 2.0;

    PDFRectangle continueMatch;

    bool ignoredHyphen;



    EXPECT_CALL(*text_page, findText(ucs4_text, 4, _, _, false, false, false, false, false, &xMin, &yMin, &xMax, &yMax, testing::_, &ignoredHyphen))

        .WillOnce(testing::Return(false));



    GList* matches = poppler_page_find_text_with_options(page, "test", POPPLER_FIND_DEFAULT);

    EXPECT_EQ(g_list_length(matches), 0);



    g_list_free(matches);

}



// Boundary condition: empty text input

TEST_F(PopplerPageTest, EmptyTextInput_2446) {

    GList* matches = poppler_page_find_text_with_options(page, "", POPPLER_FIND_DEFAULT);

    EXPECT_EQ(g_list_length(matches), 0);



    g_list_free(matches);

}



// Exceptional case: null text input

TEST_F(PopplerPageTest, NullTextInput_2446) {

    GList* matches = poppler_page_find_text_with_options(page, nullptr, POPPLER_FIND_DEFAULT);

    EXPECT_EQ(matches, nullptr);

}



// Verification of external interactions: findText is called with correct parameters

TEST_F(PopplerPageTest, FindTextCalledWithCorrectParameters_2446) {

    gunichar ucs4_text[] = {'t', 'e', 's', 't'};

    double xMin = 1.0, yMin = 1.0, xMax = 2.0, yMax = 2.0;

    PDFRectangle continueMatch;

    bool ignoredHyphen;



    EXPECT_CALL(*text_page, findText(ucs4_text, 4, _, _, false, false, false, false, false, &xMin, &yMin, &xMax, &yMax, testing::_, &ignoredHyphen))

        .WillOnce(testing::Return(false));



    poppler_page_find_text_with_options(page, "test", POPPLER_FIND_DEFAULT);

}
