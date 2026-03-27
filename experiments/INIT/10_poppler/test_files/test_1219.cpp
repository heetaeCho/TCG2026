#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Mock class for dependencies
class MockOutputDev : public OutputDev {
public:
    MOCK_METHOD(void, startPage, (int, GfxState*, XRef*), (override));
    MOCK_METHOD(void, endPage, (), (override));
    MOCK_METHOD(void, restoreState, (GfxState*), (override));
    MOCK_METHOD(void, updateFont, (GfxState*), (override));
    MOCK_METHOD(void, beginString, (GfxState*, const GooString*), (override));
    MOCK_METHOD(void, endString, (GfxState*), (override));
    MOCK_METHOD(void, drawChar, (GfxState*, double, double, double, double, double, double, CharCode, int, const Unicode*, int), (override));
    MOCK_METHOD(void, incCharCount, (int), (override));
    MOCK_METHOD(void, beginActualText, (GfxState*, const GooString*), (override));
    MOCK_METHOD(void, endActualText, (GfxState*), (override));
    MOCK_METHOD(void, stroke, (GfxState*), (override));
    MOCK_METHOD(void, fill, (GfxState*), (override));
    MOCK_METHOD(void, eoFill, (GfxState*), (override));
    MOCK_METHOD(void, processLink, (AnnotLink*), (override));
    MOCK_METHOD(bool, findText, (const Unicode*, int, bool, bool, bool, bool, bool, bool, bool, double*, double*, double*, double*), (const, override));
    MOCK_METHOD(GooString, getText, (const std::optional<PDFRectangle>&), (const, override));
    MOCK_METHOD(bool, findCharRange, (int, int, double*, double*, double*, double*), (const, override));
    MOCK_METHOD(void, drawSelection, (OutputDev*, double, int, const PDFRectangle*, SelectionStyle, const GfxColor*, const GfxColor*, double, bool), (override));
    MOCK_METHOD(std::vector<PDFRectangle*>*, getSelectionRegion, (const PDFRectangle*, SelectionStyle, double), (override));
    MOCK_METHOD(GooString, getSelectionText, (const PDFRectangle*, SelectionStyle), (override));
    MOCK_METHOD(void, setMergeCombining, (bool), (override));
    MOCK_METHOD(std::unique_ptr<TextWordList>, makeWordList, (), (override));
    MOCK_METHOD(std::unique_ptr<TextPage>, takeText, (), (override));
    MOCK_METHOD(const TextFlow*, getFlows, (), (const, override));
    MOCK_METHOD(GooString, getText, (const int&), (const, override));
    MOCK_METHOD(bool, isOk, (), (override));
    MOCK_METHOD(bool, upsideDown, (), (override));
    MOCK_METHOD(bool, useDrawChar, (), (override));
    MOCK_METHOD(bool, interpretType3Chars, (), (override));
    MOCK_METHOD(bool, needNonText, (), (override));
    MOCK_METHOD(bool, needCharCount, (), (override));
    MOCK_METHOD(void, enableHTMLExtras, (bool), (override));
    MOCK_METHOD(void, setTextEOL, (EndOfLineKind), (override));
    MOCK_METHOD(void, setTextPageBreaks, (bool), (override));
    MOCK_METHOD(double, getMinColSpacing1, (), (const, override));
    MOCK_METHOD(void, setMinColSpacing1, (double), (override));
};

TEST_F(TextOutputDev_1219, useDrawCharReturnsTrue_1219) {
    TextOutputDev textOutputDev("testFile", true, 10.0, true, true, false);
    
    // Verify the expected behavior of useDrawChar
    EXPECT_TRUE(textOutputDev.useDrawChar());
}

TEST_F(TextOutputDev_1219, setMinColSpacing1Works_1219) {
    TextOutputDev textOutputDev("testFile", true, 10.0, true, true, false);
    
    // Set minColSpacing1 and verify that it works
    textOutputDev.setMinColSpacing1(5.0);
    EXPECT_EQ(textOutputDev.getMinColSpacing1(), 5.0);
}

TEST_F(TextOutputDev_1219, setTextEOLWorks_1219) {
    TextOutputDev textOutputDev("testFile", true, 10.0, true, true, false);
    
    // Test setting TextEOL and ensure it's set correctly
    textOutputDev.setTextEOL(EndOfLineKind::eolLF);
    // Verifying if the setting has the desired effect would require implementing a getter or internal observation.
}

TEST_F(TextOutputDev_1219, startPageCallsMockedStartPage_1219) {
    MockOutputDev mockOutputDev;
    TextOutputDev textOutputDev(mockOutputDev);

    // Set up the mock expectation
    EXPECT_CALL(mockOutputDev, startPage(1, nullptr, nullptr)).Times(1);

    // Call startPage and verify the mock was invoked
    textOutputDev.startPage(1, nullptr, nullptr);
}

TEST_F(TextOutputDev_1219, endPageCallsMockedEndPage_1219) {
    MockOutputDev mockOutputDev;
    TextOutputDev textOutputDev(mockOutputDev);

    // Set up the mock expectation
    EXPECT_CALL(mockOutputDev, endPage()).Times(1);

    // Call endPage and verify the mock was invoked
    textOutputDev.endPage();
}

TEST_F(TextOutputDev_1219, findTextReturnsTrueForExistingText_1219) {
    MockOutputDev mockOutputDev;
    TextOutputDev textOutputDev(mockOutputDev);

    Unicode searchText = Unicode("sample");
    double xMin, yMin, xMax, yMax;

    // Set up the mock expectation for findText
    EXPECT_CALL(mockOutputDev, findText(&searchText, 6, true, true, true, true, false, false, false, &xMin, &yMin, &xMax, &yMax))
        .WillOnce(testing::Return(true));

    // Verify findText behavior
    EXPECT_TRUE(textOutputDev.findText(&searchText, 6, true, true, true, true, false, false, false, &xMin, &yMin, &xMax, &yMax));
}

TEST_F(TextOutputDev_1219, getTextReturnsNonEmptyText_1219) {
    MockOutputDev mockOutputDev;
    TextOutputDev textOutputDev(mockOutputDev);

    GooString text("Sample text content");
    
    // Mock the getText method to return the expected string
    EXPECT_CALL(mockOutputDev, getText(testing::_)).WillOnce(testing::Return(text));

    // Test getText
    EXPECT_EQ(textOutputDev.getText(0), text);
}

TEST_F(TextOutputDev_1219, enableHTMLExtrasChangesFlag_1219) {
    TextOutputDev textOutputDev("testFile", true, 10.0, true, true, false);

    // Test enabling HTML extras
    textOutputDev.enableHTMLExtras(true);
    // As the function doesn't return a value, we'd need to verify its side effects.
    // This could be verified if we had a getter for the HTML flag or through more observable behavior.
}