#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-page-private.h"
#include "TextOutputDev.h"
#include "TextPage.h"
#include "GooString.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

// Mocking external dependencies
class MockTextOutputDev : public TextOutputDev {
public:
    MOCK_METHOD(bool, findText, (const Unicode * s, int len, bool startAtTop, bool stopAtBottom, bool startAtLast, bool stopAtLast, bool caseSensitive, bool backward, bool wholeWord, double * xMin, double * yMin, double * xMax, double * yMax), (const, override));
    MOCK_METHOD(std::unique_ptr<TextPage>, takeText, (), (override));
};

class PageDataTest : public ::testing::Test {
protected:
    Poppler::PageData pageData;
    MockTextOutputDev mockTextOutputDev;
    QVector<Unicode> unicodeVec;

    // Helper function to set up the mock call
    void setUpMockFindText(bool returnValue) {
        EXPECT_CALL(mockTextOutputDev, findText(_, _, _, _, _, _, _, _, _, _, _, _, _))
            .WillOnce(Return(returnValue));
    }
};

// Test for normal operation of prepareTextSearch
TEST_F(PageDataTest, PrepareTextSearch_NormalOperation_1441) {
    QString text = "sample text";
    QVector<Unicode> u;
    auto textPage = pageData.prepareTextSearch(text, Poppler::Page::Rotation::rotate0, &u);

    // Verify that the textPage is properly prepared
    ASSERT_NE(textPage, nullptr);
    EXPECT_FALSE(u.isEmpty());
}

// Test for boundary case of empty text in prepareTextSearch
TEST_F(PageDataTest, PrepareTextSearch_EmptyText_1442) {
    QString text = "";
    QVector<Unicode> u;
    auto textPage = pageData.prepareTextSearch(text, Poppler::Page::Rotation::rotate0, &u);

    // Expect that an empty text does not generate a valid textPage
    ASSERT_NE(textPage, nullptr);
    EXPECT_TRUE(u.isEmpty());
}

// Test for boundary case of a very large text input in prepareTextSearch
TEST_F(PageDataTest, PrepareTextSearch_LargeText_1443) {
    QString text = QString(10000, 'a');  // A large text of 10,000 'a' characters
    QVector<Unicode> u;
    auto textPage = pageData.prepareTextSearch(text, Poppler::Page::Rotation::rotate0, &u);

    // Verify that the large input text is handled correctly
    ASSERT_NE(textPage, nullptr);
    EXPECT_EQ(u.size(), 10000);
}

// Test for exceptional case: invalid rotation angle in prepareTextSearch
TEST_F(PageDataTest, PrepareTextSearch_InvalidRotation_1444) {
    QString text = "valid text";
    QVector<Unicode> u;
    
    // Pass an invalid rotation angle (invalid enum or unsupported value)
    EXPECT_THROW(pageData.prepareTextSearch(text, static_cast<Poppler::Page::Rotation>(-1), &u), std::out_of_range);
}

// Test for normal operation of performSingleTextSearch
TEST_F(PageDataTest, PerformSingleTextSearch_NormalOperation_1445) {
    QString text = "sample text";
    QVector<Unicode> u;
    double sLeft, sTop, sRight, sBottom;

    setUpMockFindText(true);
    bool result = pageData.performSingleTextSearch(&mockTextOutputDev, u, sLeft, sTop, sRight, sBottom, Poppler::Page::SearchDirection::searchTopToBottom, false, true, true, false);

    EXPECT_TRUE(result);
}

// Test for exceptional case: performSingleTextSearch returns false
TEST_F(PageDataTest, PerformSingleTextSearch_Failure_1446) {
    QString text = "sample text";
    QVector<Unicode> u;
    double sLeft, sTop, sRight, sBottom;

    setUpMockFindText(false);
    bool result = pageData.performSingleTextSearch(&mockTextOutputDev, u, sLeft, sTop, sRight, sBottom, Poppler::Page::SearchDirection::searchTopToBottom, false, true, true, false);

    EXPECT_FALSE(result);
}

// Test for normal operation of performMultipleTextSearch
TEST_F(PageDataTest, PerformMultipleTextSearch_NormalOperation_1447) {
    QString text = "sample text";
    QVector<Unicode> u;
    
    // Mock behavior for multiple text search
    setUpMockFindText(true);
    QList<QRectF> regions = pageData.performMultipleTextSearch(&mockTextOutputDev, u, false, true, true, false);

    // Expect the search regions list to be non-empty
    EXPECT_FALSE(regions.isEmpty());
}

// Test for boundary case: performMultipleTextSearch with an empty text input
TEST_F(PageDataTest, PerformMultipleTextSearch_EmptyText_1448) {
    QString text = "";
    QVector<Unicode> u;

    setUpMockFindText(false);
    QList<QRectF> regions = pageData.performMultipleTextSearch(&mockTextOutputDev, u, false, true, true, false);

    // Expect no search regions to be found for an empty text input
    EXPECT_TRUE(regions.isEmpty());
}

// Test for exceptional case: performing search without setting required fields
TEST_F(PageDataTest, PerformMultipleTextSearch_NoSearchSetup_1449) {
    QVector<Unicode> u;
    QList<QRectF> regions = pageData.performMultipleTextSearch(&mockTextOutputDev, u, false, false, false, false);

    // Expect that the search doesn't return any regions
    EXPECT_TRUE(regions.isEmpty());
}