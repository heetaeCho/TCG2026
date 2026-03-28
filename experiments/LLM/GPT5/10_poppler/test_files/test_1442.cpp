#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-page.h"
#include "./TestProjects/poppler/qt5/src/poppler-page-private.h"

// Mock classes to simulate the dependencies for testing
class MockTextPage : public TextPage {
public:
    MOCK_METHOD(bool, findText, (const Unicode* s, int len, bool startAtTop, bool stopAtBottom, bool startAtLast, bool stopAtLast, bool caseSensitive, bool ignoreDiacritics, bool matchAcrossLines, bool backward, bool wholeWord, double* xMin, double* yMin, double* xMax, double* yMax, PDFRectangle* continueMatch, _Bool* ignoredHyphen), (override));
};

// Unit test fixture
class PageDataTest_1442 : public ::testing::Test {
protected:
    Poppler::PageData pageData;

    void SetUp() override {
        // Setup any necessary state for each test here
    }

    void TearDown() override {
        // Clean up any state after each test if needed
    }
};

// Test: Normal operation of performSingleTextSearch
TEST_F(PageDataTest_1442, PerformSingleTextSearch_NormalOperation_1442) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeData;
    double sLeft = 0, sTop = 0, sRight = 0, sBottom = 0;
    Page::SearchDirection direction = Page::FromTop;
    bool caseSensitive = true, words = false, diacritics = false, acrossLines = false;

    // Setup the mock to return true for findText
    EXPECT_CALL(mockTextPage, findText(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(true));

    // Call the function
    bool result = pageData.performSingleTextSearch(&mockTextPage, unicodeData, sLeft, sTop, sRight, sBottom, direction, caseSensitive, words, diacritics, acrossLines);

    // Assert the expected result
    ASSERT_TRUE(result);
}

// Test: Boundary condition with empty Unicode vector
TEST_F(PageDataTest_1442, PerformSingleTextSearch_EmptyUnicode_1442) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeData;  // Empty
    double sLeft = 0, sTop = 0, sRight = 0, sBottom = 0;
    Page::SearchDirection direction = Page::FromTop;
    bool caseSensitive = true, words = false, diacritics = false, acrossLines = false;

    EXPECT_CALL(mockTextPage, findText(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(false));

    bool result = pageData.performSingleTextSearch(&mockTextPage, unicodeData, sLeft, sTop, sRight, sBottom, direction, caseSensitive, words, diacritics, acrossLines);

    ASSERT_FALSE(result);  // Expect failure since no text is given to search
}

// Test: Exceptional case - invalid direction
TEST_F(PageDataTest_1442, PerformSingleTextSearch_InvalidDirection_1442) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeData;
    double sLeft = 0, sTop = 0, sRight = 0, sBottom = 0;
    Page::SearchDirection direction = static_cast<Page::SearchDirection>(999);  // Invalid direction
    bool caseSensitive = true, words = false, diacritics = false, acrossLines = false;

    EXPECT_CALL(mockTextPage, findText(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(false));

    bool result = pageData.performSingleTextSearch(&mockTextPage, unicodeData, sLeft, sTop, sRight, sBottom, direction, caseSensitive, words, diacritics, acrossLines);

    ASSERT_FALSE(result);  // Expect failure due to invalid direction
}

// Test: Boundary case - direction NextResult
TEST_F(PageDataTest_1442, PerformSingleTextSearch_NextResult_1442) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeData;
    double sLeft = 0, sTop = 0, sRight = 0, sBottom = 0;
    Page::SearchDirection direction = Page::NextResult;
    bool caseSensitive = false, words = true, diacritics = false, acrossLines = false;

    // Expect the mock to return true indicating the text was found
    EXPECT_CALL(mockTextPage, findText(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(true));

    bool result = pageData.performSingleTextSearch(&mockTextPage, unicodeData, sLeft, sTop, sRight, sBottom, direction, caseSensitive, words, diacritics, acrossLines);

    ASSERT_TRUE(result);  // Expect success as the mock simulates a found text
}