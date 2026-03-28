#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <vector>
#include <optional>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GooString.h"
#include "Link.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Helper callback function for TextOutputFunc-based constructor
static void textOutputCallback(void *stream, const char *text, int len) {
    if (stream) {
        std::string *output = static_cast<std::string *>(stream);
        output->append(text, len);
    }
}

class TextOutputDevTest_1222 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test: Constructor with file name (nullptr for stdout-like behavior)
TEST_F(TextOutputDevTest_1222, ConstructWithNullFileName_1222) {
    TextOutputDev dev(nullptr, false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Constructor with callback function
TEST_F(TextOutputDevTest_1222, ConstructWithCallback_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Constructor with invalid file path
TEST_F(TextOutputDevTest_1222, ConstructWithInvalidFilePath_1222) {
    TextOutputDev dev("/nonexistent/path/that/should/fail/output.txt", false, 0.0, false, false, false);
    // isOk() should return false if file cannot be opened
    // This depends on implementation, but typically an invalid path should fail
    // We just verify it doesn't crash
}

// Test: needCharCount returns true
TEST_F(TextOutputDevTest_1222, NeedCharCountReturnsTrue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.needCharCount());
}

// Test: upsideDown returns expected value
TEST_F(TextOutputDevTest_1222, UpsideDownReturnValue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    // upsideDown() should return a consistent boolean
    bool result = dev.upsideDown();
    (void)result; // just verify it doesn't crash; exact value depends on implementation
}

// Test: useDrawChar returns expected value
TEST_F(TextOutputDevTest_1222, UseDrawCharReturnValue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.useDrawChar());
}

// Test: interpretType3Chars returns expected value
TEST_F(TextOutputDevTest_1222, InterpretType3CharsReturnValue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.interpretType3Chars());
}

// Test: needNonText returns expected value
TEST_F(TextOutputDevTest_1222, NeedNonTextReturnValue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    bool result = dev.needNonText();
    (void)result; // verify no crash
}

// Test: setTextEOL and verify it doesn't crash
TEST_F(TextOutputDevTest_1222, SetTextEOL_Unix_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setTextEOL(eolUnix);
    // No crash expected
}

TEST_F(TextOutputDevTest_1222, SetTextEOL_DOS_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setTextEOL(eolDOS);
}

TEST_F(TextOutputDevTest_1222, SetTextEOL_Mac_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setTextEOL(eolMac);
}

// Test: setTextPageBreaks
TEST_F(TextOutputDevTest_1222, SetTextPageBreaksTrue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setTextPageBreaks(true);
    // No crash expected
}

TEST_F(TextOutputDevTest_1222, SetTextPageBreaksFalse_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setTextPageBreaks(false);
}

// Test: enableHTMLExtras
TEST_F(TextOutputDevTest_1222, EnableHTMLExtrasTrue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.enableHTMLExtras(true);
}

TEST_F(TextOutputDevTest_1222, EnableHTMLExtrasFalse_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.enableHTMLExtras(false);
}

// Test: setMergeCombining
TEST_F(TextOutputDevTest_1222, SetMergeCombiningTrue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMergeCombining(true);
}

TEST_F(TextOutputDevTest_1222, SetMergeCombiningFalse_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMergeCombining(false);
}

// Test: getMinColSpacing1 and setMinColSpacing1
TEST_F(TextOutputDevTest_1222, SetAndGetMinColSpacing1_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(3.5);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 3.5);
}

TEST_F(TextOutputDevTest_1222, SetMinColSpacing1Zero_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 0.0);
}

TEST_F(TextOutputDevTest_1222, SetMinColSpacing1Negative_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), -1.0);
}

// Test: getText with empty optional (no area restriction)
TEST_F(TextOutputDevTest_1222, GetTextEmptyOptional_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::optional<PDFRectangle> area;
    GooString *result = dev.getText(area);
    // Without any pages processed, getText should return empty or valid string
    ASSERT_NE(result, nullptr);
    delete result;
}

// Test: makeWordList without any content
TEST_F(TextOutputDevTest_1222, MakeWordListEmpty_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::unique_ptr<TextWordList> wordList = dev.makeWordList();
    ASSERT_NE(wordList, nullptr);
    EXPECT_EQ(wordList->getLength(), 0);
}

// Test: takeText
TEST_F(TextOutputDevTest_1222, TakeText_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::unique_ptr<TextPage> page = dev.takeText();
    ASSERT_NE(page, nullptr);
}

// Test: getFlows without any content
TEST_F(TextOutputDevTest_1222, GetFlowsEmpty_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    const TextFlow *flows = dev.getFlows();
    // Without pages processed, flows should be null
    EXPECT_EQ(flows, nullptr);
}

// Test: findText with empty search on empty page
TEST_F(TextOutputDevTest_1222, FindTextEmptyPage_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = { 'a' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 1, true, true, false, false, false, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test: findCharRange on empty page
TEST_F(TextOutputDevTest_1222, FindCharRangeEmptyPage_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test: physLayout constructor parameter
TEST_F(TextOutputDevTest_1222, ConstructWithPhysLayout_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: fixedPitch constructor parameter
TEST_F(TextOutputDevTest_1222, ConstructWithFixedPitch_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 12.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: rawOrder constructor parameter
TEST_F(TextOutputDevTest_1222, ConstructWithRawOrder_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: discardDiag constructor parameter
TEST_F(TextOutputDevTest_1222, ConstructWithDiscardDiag_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test: startPage and endPage without crash
TEST_F(TextOutputDevTest_1222, StartAndEndPage_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.startPage(1, nullptr, nullptr);
    dev.endPage();
    // Should not crash
}

// Test: incCharCount
TEST_F(TextOutputDevTest_1222, IncCharCount_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.incCharCount(10);
    // Should not crash
}

// Test: incCharCount with zero
TEST_F(TextOutputDevTest_1222, IncCharCountZero_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.incCharCount(0);
}

// Test: Multiple setMinColSpacing1 calls
TEST_F(TextOutputDevTest_1222, MultipleSetMinColSpacing1_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 1.0);
    dev.setMinColSpacing1(5.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 5.0);
    dev.setMinColSpacing1(100.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 100.0);
}

// Test: getText with PDFRectangle area
TEST_F(TextOutputDevTest_1222, GetTextWithArea_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;
    std::optional<PDFRectangle> area(rect);
    GooString *result = dev.getText(area);
    ASSERT_NE(result, nullptr);
    delete result;
}

// Test: getSelectionText on empty page
TEST_F(TextOutputDevTest_1222, GetSelectionTextEmpty_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    GooString *result = dev.getSelectionText(&selection, selectionStyleGlyph);
    ASSERT_NE(result, nullptr);
    delete result;
}

// Test: Constructor with callback and null stream
TEST_F(TextOutputDevTest_1222, ConstructWithCallbackNullStream_1222) {
    TextOutputDev dev(textOutputCallback, nullptr, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: findText with backward search
TEST_F(TextOutputDevTest_1222, FindTextBackwardEmptyPage_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = { 'h', 'e', 'l', 'l', 'o' };
    double xMin = 0, yMin = 0, xMax = 1000, yMax = 1000;
    bool found = dev.findText(searchStr, 5, true, true, false, false, false, true, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test: findText with case sensitive
TEST_F(TextOutputDevTest_1222, FindTextCaseSensitiveEmptyPage_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = { 'A' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 1, true, true, false, false, true, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test: findText with whole word
TEST_F(TextOutputDevTest_1222, FindTextWholeWordEmptyPage_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    Unicode searchStr[] = { 't', 'e', 's', 't' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 4, true, true, false, false, false, false, true,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test: Large minColSpacing1 value
TEST_F(TextOutputDevTest_1222, SetMinColSpacing1LargeValue_1222) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(1e10);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 1e10);
}
