#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QList>
#include <QRectF>
#include <QVector>
#include <limits>
#include <optional>
#include "poppler-page-private.h"
#include "TextPage.h"

namespace Poppler {

class MockTextPage : public TextPage {
public:
    MOCK_METHOD(bool, findText, (
        const Unicode *s, int len, bool startAtTop, bool stopAtBottom,
        bool startAtLast, bool stopAtLast, bool caseSensitive, bool ignoreDiacritics,
        bool matchAcrossLines, bool backward, bool wholeWord, double *xMin, 
        double *yMin, double *xMax, double *yMax, PDFRectangle *continueMatch,
        bool *ignoredHyphen), (override));
};

class PageDataTest_1443 : public ::testing::Test {
protected:
    // Test-specific setup and teardown can go here

    std::unique_ptr<PageData> pageData;

    void SetUp() override {
        pageData = std::make_unique<PageData>();
    }

    void TearDown() override {
        pageData.reset();
    }
};

// Test case for normal operation
TEST_F(PageDataTest_1443, PerformMultipleTextSearch_NormalOperation_1443) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeVector = { 'H', 'e', 'l', 'l', 'o' }; // Example search term 'Hello'
    double left = 0.0, top = 0.0, right = 0.0, bottom = 0.0;
    bool caseSensitive = false, wholeWord = true, diacritics = false, acrossLines = false;

    // Set up mock expectations
    EXPECT_CALL(mockTextPage, findText(
        testing::_, testing::_, testing::_, testing::_, testing::_, testing::_,
        testing::_, testing::_, testing::_, testing::_, testing::_, 
        testing::_ , testing::_ , testing::_ , testing::_ , testing::_ 
    )).WillOnce(testing::Return(true));

    QList<QRectF> results = pageData->performMultipleTextSearch(&mockTextPage, unicodeVector, caseSensitive, wholeWord, diacritics, acrossLines);
    
    EXPECT_EQ(results.size(), 1);
    EXPECT_FLOAT_EQ(results[0].left(), left);
    EXPECT_FLOAT_EQ(results[0].top(), top);
    EXPECT_FLOAT_EQ(results[0].right(), right);
    EXPECT_FLOAT_EQ(results[0].bottom(), bottom);
}

// Test case for boundary conditions
TEST_F(PageDataTest_1443, PerformMultipleTextSearch_EmptyText_1443) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeVector;  // Empty search term
    double left = 0.0, top = 0.0, right = 0.0, bottom = 0.0;
    bool caseSensitive = false, wholeWord = true, diacritics = false, acrossLines = false;

    // Set up mock expectations
    EXPECT_CALL(mockTextPage, findText(
        testing::_, testing::_, testing::_, testing::_, testing::_, testing::_,
        testing::_, testing::_, testing::_, testing::_, testing::_, 
        testing::_ , testing::_ , testing::_ , testing::_ , testing::_ 
    )).WillOnce(testing::Return(false));

    QList<QRectF> results = pageData->performMultipleTextSearch(&mockTextPage, unicodeVector, caseSensitive, wholeWord, diacritics, acrossLines);
    
    EXPECT_EQ(results.size(), 0);  // No results found for empty text
}

// Test case for error condition with invalid arguments
TEST_F(PageDataTest_1443, PerformMultipleTextSearch_InvalidArguments_1443) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeVector = { 'W', 'r', 'o', 'n', 'g' }; // Example search term 'Wrong'
    double left = 0.0, top = 0.0, right = 0.0, bottom = 0.0;
    bool caseSensitive = true, wholeWord = false, diacritics = true, acrossLines = false;

    // Set up mock expectations
    EXPECT_CALL(mockTextPage, findText(
        testing::_, testing::_, testing::_, testing::_, testing::_, testing::_,
        testing::_, testing::_, testing::_, testing::_, testing::_, 
        testing::_ , testing::_ , testing::_ , testing::_ , testing::_ 
    )).WillOnce(testing::Return(false));  // Simulate error (no results found)

    QList<QRectF> results = pageData->performMultipleTextSearch(&mockTextPage, unicodeVector, caseSensitive, wholeWord, diacritics, acrossLines);
    
    EXPECT_EQ(results.size(), 0);  // No results should be found on invalid arguments
}

// Test case for verification of external interaction (mock handler)
TEST_F(PageDataTest_1443, PerformMultipleTextSearch_ExternalInteraction_1443) {
    MockTextPage mockTextPage;
    QVector<Unicode> unicodeVector = { 'F', 'o', 'o' };  // Search term 'Foo'
    double left = 0.0, top = 0.0, right = 0.0, bottom = 0.0;
    bool caseSensitive = false, wholeWord = true, diacritics = false, acrossLines = true;

    // Set up mock expectations
    EXPECT_CALL(mockTextPage, findText(
        testing::_, testing::_, testing::_, testing::_, testing::_, testing::_,
        testing::_, testing::_, testing::_, testing::_, testing::_, 
        testing::_ , testing::_ , testing::_ , testing::_ , testing::_ 
    )).WillOnce(testing::Return(true));

    QList<QRectF> results = pageData->performMultipleTextSearch(&mockTextPage, unicodeVector, caseSensitive, wholeWord, diacritics, acrossLines);
    
    EXPECT_EQ(results.size(), 1);  // Ensure that the mock was correctly interacted with
    EXPECT_FLOAT_EQ(results[0].left(), left);
}

}  // namespace Poppler