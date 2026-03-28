#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>
#include <cstring>

#include "TextOutputDev.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Helper callback function for TextOutputFunc constructor
static void textOutputCallback(void *stream, const char *text, int len) {
    if (stream && text) {
        std::string *output = static_cast<std::string *>(stream);
        output->append(text, len);
    }
}

class TextOutputDevTest_1221 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test construction with file name (using nullptr for stdout-like behavior)
TEST_F(TextOutputDevTest_1221, ConstructWithNullFileName_1221) {
    TextOutputDev dev(nullptr, false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with callback function
TEST_F(TextOutputDevTest_1221, ConstructWithCallback_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with physical layout enabled
TEST_F(TextOutputDevTest_1221, ConstructWithPhysLayout_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with fixed pitch
TEST_F(TextOutputDevTest_1221, ConstructWithFixedPitch_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 12.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with raw order
TEST_F(TextOutputDevTest_1221, ConstructWithRawOrder_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with discard diagonal
TEST_F(TextOutputDevTest_1221, ConstructWithDiscardDiag_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test needNonText returns false
TEST_F(TextOutputDevTest_1221, NeedNonTextReturnsFalse_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_FALSE(dev.needNonText());
}

// Test upsideDown returns expected value
TEST_F(TextOutputDevTest_1221, UpsideDown_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    // upsideDown() should return a boolean value
    bool result = dev.upsideDown();
    // Just verify it doesn't crash; the actual value is implementation-defined
    (void)result;
}

// Test useDrawChar returns expected value
TEST_F(TextOutputDevTest_1221, UseDrawChar_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    bool result = dev.useDrawChar();
    EXPECT_TRUE(result);
}

// Test interpretType3Chars returns expected value
TEST_F(TextOutputDevTest_1221, InterpretType3Chars_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    bool result = dev.interpretType3Chars();
    (void)result; // Just verify it doesn't crash
}

// Test needCharCount returns expected value
TEST_F(TextOutputDevTest_1221, NeedCharCount_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    bool result = dev.needCharCount();
    (void)result;
}

// Test setTextEOL
TEST_F(TextOutputDevTest_1221, SetTextEOL_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    // Should not crash with any EOL kind
    dev.setTextEOL(eolUnix);
    dev.setTextEOL(eolDOS);
    dev.setTextEOL(eolMac);
}

// Test setTextPageBreaks
TEST_F(TextOutputDevTest_1221, SetTextPageBreaks_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setTextPageBreaks(true);
    dev.setTextPageBreaks(false);
}

// Test enableHTMLExtras
TEST_F(TextOutputDevTest_1221, EnableHTMLExtras_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.enableHTMLExtras(true);
    dev.enableHTMLExtras(false);
}

// Test setMergeCombining
TEST_F(TextOutputDevTest_1221, SetMergeCombining_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMergeCombining(true);
    dev.setMergeCombining(false);
}

// Test getMinColSpacing1 and setMinColSpacing1
TEST_F(TextOutputDevTest_1221, MinColSpacing1GetSet_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(2.5);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 2.5);
}

// Test setMinColSpacing1 with zero
TEST_F(TextOutputDevTest_1221, MinColSpacing1Zero_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 0.0);
}

// Test setMinColSpacing1 with negative value
TEST_F(TextOutputDevTest_1221, MinColSpacing1Negative_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), -1.0);
}

// Test setMinColSpacing1 with large value
TEST_F(TextOutputDevTest_1221, MinColSpacing1Large_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(99999.99);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 99999.99);
}

// Test takeText returns non-null
TEST_F(TextOutputDevTest_1221, TakeTextReturnsNonNull_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    auto textPage = dev.takeText();
    EXPECT_NE(textPage, nullptr);
}

// Test makeWordList on empty page
TEST_F(TextOutputDevTest_1221, MakeWordListOnEmpty_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    auto wordList = dev.makeWordList();
    EXPECT_NE(wordList, nullptr);
}

// Test getText with no area (optional empty)
TEST_F(TextOutputDevTest_1221, GetTextNoArea_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::optional<PDFRectangle> area;
    GooString *result = dev.getText(area);
    EXPECT_NE(result, nullptr);
    delete result;
}

// Test getText with a specified area
TEST_F(TextOutputDevTest_1221, GetTextWithArea_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;
    std::optional<PDFRectangle> area(rect);
    GooString *result = dev.getText(area);
    EXPECT_NE(result, nullptr);
    delete result;
}

// Test findText with empty search on empty page
TEST_F(TextOutputDevTest_1221, FindTextEmptyPage_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = {'t', 'e', 's', 't'};
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 4, true, true, false, false, false, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findCharRange on empty page
TEST_F(TextOutputDevTest_1221, FindCharRangeEmptyPage_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    // On empty page, should not find the char range
    EXPECT_FALSE(found);
}

// Test getFlows on empty page
TEST_F(TextOutputDevTest_1221, GetFlowsEmptyPage_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    const TextFlow *flows = dev.getFlows();
    // On empty page, flows might be null
    (void)flows; // Just verify no crash
}

// Test construction with invalid file name
TEST_F(TextOutputDevTest_1221, ConstructWithInvalidFile_1221) {
    TextOutputDev dev("/nonexistent/path/to/file.txt", false, 0.0, false, false, false);
    // isOk() may return false for invalid file path
    // This is implementation-defined, just check it doesn't crash
    bool ok = dev.isOk();
    (void)ok;
}

// Test construction with append mode
TEST_F(TextOutputDevTest_1221, ConstructWithAppendMode_1221) {
    // Use "-" for stdout
    TextOutputDev dev("-", false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test getSelectionText with empty selection
TEST_F(TextOutputDevTest_1221, GetSelectionTextEmpty_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    GooString *result = dev.getSelectionText(&selection, selectionStyleWord);
    EXPECT_NE(result, nullptr);
    delete result;
}

// Test getSelectionRegion with empty selection
TEST_F(TextOutputDevTest_1221, GetSelectionRegionEmpty_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    auto *regions = dev.getSelectionRegion(&selection, selectionStyleWord, 1.0);
    EXPECT_NE(regions, nullptr);
    // Clean up
    for (auto *rect : *regions) {
        delete rect;
    }
    delete regions;
}

// Test multiple setMinColSpacing1 calls
TEST_F(TextOutputDevTest_1221, MinColSpacing1MultipleSets_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 1.0);
    dev.setMinColSpacing1(5.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 5.0);
    dev.setMinColSpacing1(0.001);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 0.001);
}

// Test findText with backward search on empty page
TEST_F(TextOutputDevTest_1221, FindTextBackwardEmptyPage_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = {'a'};
    double xMin = 0, yMin = 0, xMax = 1000, yMax = 1000;
    bool found = dev.findText(searchStr, 1, false, false, false, false, false, true, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findText case sensitive on empty page
TEST_F(TextOutputDevTest_1221, FindTextCaseSensitiveEmptyPage_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = {'A', 'B', 'C'};
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 3, true, true, false, false, true, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findText whole word on empty page
TEST_F(TextOutputDevTest_1221, FindTextWholeWordEmptyPage_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = {'w', 'o', 'r', 'd'};
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 4, true, true, false, false, false, false, true,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test startPage and endPage don't crash
TEST_F(TextOutputDevTest_1221, StartPageEndPage_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.startPage(1, nullptr, nullptr);
    dev.endPage();
}

// Test incCharCount doesn't crash
TEST_F(TextOutputDevTest_1221, IncCharCount_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.incCharCount(10);
    dev.incCharCount(0);
    dev.incCharCount(-1);
}

// Test takeText twice - second call should still work (return new text page)
TEST_F(TextOutputDevTest_1221, TakeTextTwice_1221) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    auto textPage1 = dev.takeText();
    EXPECT_NE(textPage1, nullptr);
    // After takeText, a new TextPage should be created internally
    auto textPage2 = dev.takeText();
    EXPECT_NE(textPage2, nullptr);
}
