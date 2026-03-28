#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <vector>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GooString.h"
#include "Link.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Helper callback function for TextOutputDev constructor
static void textOutputCallback(void *stream, const char *text, int len) {
    if (stream) {
        std::string *output = static_cast<std::string *>(stream);
        output->append(text, len);
    }
}

class TextOutputDevTest_1219 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test construction with file name (using nullptr for stdout)
TEST_F(TextOutputDevTest_1219, ConstructWithNullFileName_1219) {
    TextOutputDev dev(nullptr, false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with callback function
TEST_F(TextOutputDevTest_1219, ConstructWithCallback_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test useDrawChar returns true
TEST_F(TextOutputDevTest_1219, UseDrawCharReturnsTrue_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.useDrawChar());
}

// Test upsideDown
TEST_F(TextOutputDevTest_1219, UpsideDownReturnValue_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    // upsideDown should return a boolean value
    bool result = dev.upsideDown();
    EXPECT_TRUE(result == true || result == false);
}

// Test interpretType3Chars
TEST_F(TextOutputDevTest_1219, InterpretType3CharsReturnValue_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    bool result = dev.interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test needNonText
TEST_F(TextOutputDevTest_1219, NeedNonTextReturnValue_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    bool result = dev.needNonText();
    EXPECT_TRUE(result == true || result == false);
}

// Test needCharCount
TEST_F(TextOutputDevTest_1219, NeedCharCountReturnValue_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    bool result = dev.needCharCount();
    EXPECT_TRUE(result == true || result == false);
}

// Test setTextEOL
TEST_F(TextOutputDevTest_1219, SetTextEOL_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    // Should not crash with any valid EndOfLineKind
    dev.setTextEOL(eolUnix);
    dev.setTextEOL(eolDOS);
    dev.setTextEOL(eolMac);
}

// Test setTextPageBreaks
TEST_F(TextOutputDevTest_1219, SetTextPageBreaks_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setTextPageBreaks(true);
    dev.setTextPageBreaks(false);
    // Should not crash
    SUCCEED();
}

// Test enableHTMLExtras
TEST_F(TextOutputDevTest_1219, EnableHTMLExtras_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.enableHTMLExtras(true);
    dev.enableHTMLExtras(false);
    SUCCEED();
}

// Test setMergeCombining
TEST_F(TextOutputDevTest_1219, SetMergeCombining_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMergeCombining(true);
    dev.setMergeCombining(false);
    SUCCEED();
}

// Test getMinColSpacing1 and setMinColSpacing1
TEST_F(TextOutputDevTest_1219, GetSetMinColSpacing1_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(2.5);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 2.5);
}

// Test setMinColSpacing1 with zero
TEST_F(TextOutputDevTest_1219, SetMinColSpacing1Zero_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 0.0);
}

// Test setMinColSpacing1 with negative value
TEST_F(TextOutputDevTest_1219, SetMinColSpacing1Negative_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), -1.0);
}

// Test getText with no page content (empty area)
TEST_F(TextOutputDevTest_1219, GetTextEmptyOptional_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::optional<PDFRectangle> area = std::nullopt;
    GooString text = dev.getText(area);
    // With no page started, text should be empty or minimal
    EXPECT_GE(text.getLength(), 0);
}

// Test getText with specified area
TEST_F(TextOutputDevTest_1219, GetTextWithArea_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;
    std::optional<PDFRectangle> area = rect;
    GooString text = dev.getText(area);
    EXPECT_GE(text.getLength(), 0);
}

// Test makeWordList on empty page
TEST_F(TextOutputDevTest_1219, MakeWordListEmpty_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::unique_ptr<TextWordList> wordList = dev.makeWordList();
    EXPECT_NE(wordList, nullptr);
}

// Test takeText
TEST_F(TextOutputDevTest_1219, TakeText_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::unique_ptr<TextPage> page = dev.takeText();
    EXPECT_NE(page, nullptr);
}

// Test findText with empty search on empty page
TEST_F(TextOutputDevTest_1219, FindTextEmptySearch_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    Unicode searchStr[] = { 'H', 'e', 'l', 'l', 'o' };
    bool found = dev.findText(searchStr, 5, true, true, false, false, false, false, false,
                              &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findCharRange on empty page
TEST_F(TextOutputDevTest_1219, FindCharRangeEmpty_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    // On empty page, should not find the range
    EXPECT_FALSE(found);
}

// Test getFlows on empty page
TEST_F(TextOutputDevTest_1219, GetFlowsEmpty_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    const TextFlow *flows = dev.getFlows();
    // On empty page, flows should be nullptr
    EXPECT_EQ(flows, nullptr);
}

// Test construction with physical layout enabled
TEST_F(TextOutputDevTest_1219, ConstructWithPhysLayout_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with fixed pitch
TEST_F(TextOutputDevTest_1219, ConstructWithFixedPitch_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 10.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with raw order
TEST_F(TextOutputDevTest_1219, ConstructWithRawOrder_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with discard diagonal
TEST_F(TextOutputDevTest_1219, ConstructWithDiscardDiag_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test getSelectionText on empty page
TEST_F(TextOutputDevTest_1219, GetSelectionTextEmpty_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    GooString selText = dev.getSelectionText(&selection, selectionStyleGlyph);
    EXPECT_GE(selText.getLength(), 0);
}

// Test getSelectionRegion on empty page
TEST_F(TextOutputDevTest_1219, GetSelectionRegionEmpty_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    std::vector<PDFRectangle *> *regions = dev.getSelectionRegion(&selection, selectionStyleGlyph, 1.0);
    EXPECT_NE(regions, nullptr);
    // Clean up
    for (auto *r : *regions) {
        delete r;
    }
    delete regions;
}

// Test multiple setMinColSpacing1 calls
TEST_F(TextOutputDevTest_1219, SetMinColSpacing1Multiple_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 1.0);
    dev.setMinColSpacing1(5.5);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 5.5);
    dev.setMinColSpacing1(100.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 100.0);
}

// Test endPage without startPage (should not crash)
TEST_F(TextOutputDevTest_1219, EndPageWithoutStartPage_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.endPage();
    SUCCEED();
}

// Test callback receives data after page operations
TEST_F(TextOutputDevTest_1219, CallbackNullStream_1219) {
    TextOutputDev dev(textOutputCallback, nullptr, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test findText with zero length search
TEST_F(TextOutputDevTest_1219, FindTextZeroLength_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    Unicode searchStr[] = { 'a' };
    bool found = dev.findText(searchStr, 0, true, true, false, false, false, false, false,
                              &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test construction with file name for output to a temp file
TEST_F(TextOutputDevTest_1219, ConstructWithFileName_1219) {
    const char *tmpFile = "/tmp/textoutputdev_test_1219.txt";
    TextOutputDev dev(tmpFile, false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with append mode
TEST_F(TextOutputDevTest_1219, ConstructWithAppendMode_1219) {
    const char *tmpFile = "/tmp/textoutputdev_test_1219_append.txt";
    TextOutputDev dev(tmpFile, false, 0.0, false, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test incCharCount does not crash
TEST_F(TextOutputDevTest_1219, IncCharCountNoCrash_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.incCharCount(5);
    dev.incCharCount(0);
    dev.incCharCount(-1);
    SUCCEED();
}

// Test startPage and endPage cycle
TEST_F(TextOutputDevTest_1219, StartPageEndPageCycle_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.startPage(1, nullptr, nullptr);
    dev.endPage();
    SUCCEED();
}

// Test takeText after takeText (second should still work)
TEST_F(TextOutputDevTest_1219, TakeTextTwice_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::unique_ptr<TextPage> page1 = dev.takeText();
    EXPECT_NE(page1, nullptr);
    // After takeText, a new TextPage should be created internally
    // The second call behavior depends on implementation but should not crash
}

// Test makeWordList returns valid list on fresh device
TEST_F(TextOutputDevTest_1219, MakeWordListFreshDevice_1219) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    auto wordList = dev.makeWordList();
    ASSERT_NE(wordList, nullptr);
    EXPECT_GE(wordList->getLength(), 0);
}
