#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Helper callback function for TextOutputDev constructor that takes a function
static void textOutputCallback(void *stream, const char *text, int len) {
    // Simple callback that does nothing - used for testing
}

class TextOutputDevTest_1224 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a TextOutputDev using the callback-based constructor
        // Using nullptr for stream, physLayout=false, fixedPitch=0, rawOrder=false, discardDiag=false
        dev = std::make_unique<TextOutputDev>(textOutputCallback, nullptr, false, 0.0, false, false);
    }

    void TearDown() override {
        dev.reset();
    }

    std::unique_ptr<TextOutputDev> dev;
};

// Test that the object is created successfully and is valid
TEST_F(TextOutputDevTest_1224, ConstructionWithCallback_1224) {
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->isOk());
}

// Test setTextEOL with eolUnix
TEST_F(TextOutputDevTest_1224, SetTextEOLUnix_1224) {
    // Should not throw or crash
    EXPECT_NO_THROW(dev->setTextEOL(eolUnix));
}

// Test setTextEOL with eolDOS
TEST_F(TextOutputDevTest_1224, SetTextEOLDOS_1224) {
    EXPECT_NO_THROW(dev->setTextEOL(eolDOS));
}

// Test setTextEOL with eolMac
TEST_F(TextOutputDevTest_1224, SetTextEOLMac_1224) {
    EXPECT_NO_THROW(dev->setTextEOL(eolMac));
}

// Test setTextPageBreaks
TEST_F(TextOutputDevTest_1224, SetTextPageBreaksTrue_1224) {
    EXPECT_NO_THROW(dev->setTextPageBreaks(true));
}

TEST_F(TextOutputDevTest_1224, SetTextPageBreaksFalse_1224) {
    EXPECT_NO_THROW(dev->setTextPageBreaks(false));
}

// Test enableHTMLExtras
TEST_F(TextOutputDevTest_1224, EnableHTMLExtrasTrue_1224) {
    EXPECT_NO_THROW(dev->enableHTMLExtras(true));
}

TEST_F(TextOutputDevTest_1224, EnableHTMLExtrasFalse_1224) {
    EXPECT_NO_THROW(dev->enableHTMLExtras(false));
}

// Test setMergeCombining
TEST_F(TextOutputDevTest_1224, SetMergeCombiningTrue_1224) {
    EXPECT_NO_THROW(dev->setMergeCombining(true));
}

TEST_F(TextOutputDevTest_1224, SetMergeCombiningFalse_1224) {
    EXPECT_NO_THROW(dev->setMergeCombining(false));
}

// Test setMinColSpacing1 and getMinColSpacing1
TEST_F(TextOutputDevTest_1224, SetAndGetMinColSpacing1_1224) {
    dev->setMinColSpacing1(2.5);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 2.5);
}

TEST_F(TextOutputDevTest_1224, SetMinColSpacing1Zero_1224) {
    dev->setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 0.0);
}

TEST_F(TextOutputDevTest_1224, SetMinColSpacing1Negative_1224) {
    dev->setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), -1.0);
}

TEST_F(TextOutputDevTest_1224, SetMinColSpacing1Large_1224) {
    dev->setMinColSpacing1(1000.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1000.0);
}

// Test OutputDev interface methods
TEST_F(TextOutputDevTest_1224, UpsideDown_1224) {
    // upsideDown should return a boolean value
    bool result = dev->upsideDown();
    // Just verify it returns without error; actual value depends on implementation
    (void)result;
}

TEST_F(TextOutputDevTest_1224, UseDrawChar_1224) {
    bool result = dev->useDrawChar();
    // TextOutputDev typically uses drawChar
    EXPECT_TRUE(result);
}

TEST_F(TextOutputDevTest_1224, InterpretType3Chars_1224) {
    bool result = dev->interpretType3Chars();
    (void)result;
}

TEST_F(TextOutputDevTest_1224, NeedNonText_1224) {
    bool result = dev->needNonText();
    (void)result;
}

TEST_F(TextOutputDevTest_1224, NeedCharCount_1224) {
    bool result = dev->needCharCount();
    (void)result;
}

// Test makeWordList on empty page (no content drawn)
TEST_F(TextOutputDevTest_1224, MakeWordListEmpty_1224) {
    auto wordList = dev->makeWordList();
    // Should return a valid (possibly empty) word list
    ASSERT_NE(wordList, nullptr);
}

// Test getFlows on empty page
TEST_F(TextOutputDevTest_1224, GetFlowsEmpty_1224) {
    const TextFlow *flows = dev->getFlows();
    // On an empty page, flows may be nullptr
    // Just verify no crash
    (void)flows;
}

// Test takeText
TEST_F(TextOutputDevTest_1224, TakeText_1224) {
    auto textPage = dev->takeText();
    ASSERT_NE(textPage, nullptr);
}

// Test getText with empty optional (no area restriction)
TEST_F(TextOutputDevTest_1224, GetTextNoArea_1224) {
    std::optional<PDFRectangle> area;
    GooString result = dev->getText(area);
    // On empty content, should return empty or valid string
    (void)result;
}

// Test getText with a specified area
TEST_F(TextOutputDevTest_1224, GetTextWithArea_1224) {
    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;
    std::optional<PDFRectangle> area(rect);
    GooString result = dev->getText(area);
    (void)result;
}

// Test findText with empty content (should not find anything)
TEST_F(TextOutputDevTest_1224, FindTextEmptyContent_1224) {
    Unicode searchStr[] = { 'h', 'e', 'l', 'l', 'o' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev->findText(searchStr, 5, true, true, false, false, false, false, false,
                                &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findCharRange on empty content
TEST_F(TextOutputDevTest_1224, FindCharRangeEmpty_1224) {
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev->findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test construction with file name (using /dev/null or similar)
TEST_F(TextOutputDevTest_1224, ConstructionWithFileName_1224) {
    // Use "-" which typically means stdout, or a temp file
    TextOutputDev fileDev("-", false, 0.0, false, false, false);
    EXPECT_TRUE(fileDev.isOk());
}

// Test multiple setTextEOL calls (switching between modes)
TEST_F(TextOutputDevTest_1224, SetTextEOLMultipleTimes_1224) {
    dev->setTextEOL(eolUnix);
    dev->setTextEOL(eolDOS);
    dev->setTextEOL(eolMac);
    dev->setTextEOL(eolUnix);
    // Should not crash or cause issues
}

// Test setMinColSpacing1 multiple times
TEST_F(TextOutputDevTest_1224, SetMinColSpacing1MultipleTimes_1224) {
    dev->setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1.0);
    dev->setMinColSpacing1(5.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 5.0);
    dev->setMinColSpacing1(0.001);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 0.001);
}

// Test getSelectionText on empty content
TEST_F(TextOutputDevTest_1224, GetSelectionTextEmpty_1224) {
    PDFRectangle selection;
    selection.x1 = 0;
    selection.y1 = 0;
    selection.x2 = 100;
    selection.y2 = 100;
    GooString result = dev->getSelectionText(&selection, selectionStyleWord);
    // Should return empty or valid string on empty content
    (void)result;
}

// Test incCharCount
TEST_F(TextOutputDevTest_1224, IncCharCount_1224) {
    EXPECT_NO_THROW(dev->incCharCount(0));
    EXPECT_NO_THROW(dev->incCharCount(5));
    EXPECT_NO_THROW(dev->incCharCount(100));
}

// Test construction with physLayout=true
TEST_F(TextOutputDevTest_1224, ConstructionWithPhysLayout_1224) {
    TextOutputDev physDev(textOutputCallback, nullptr, true, 0.0, false, false);
    EXPECT_TRUE(physDev.isOk());
}

// Test construction with fixedPitch
TEST_F(TextOutputDevTest_1224, ConstructionWithFixedPitch_1224) {
    TextOutputDev fpDev(textOutputCallback, nullptr, false, 10.0, false, false);
    EXPECT_TRUE(fpDev.isOk());
}

// Test construction with rawOrder
TEST_F(TextOutputDevTest_1224, ConstructionWithRawOrder_1224) {
    TextOutputDev rawDev(textOutputCallback, nullptr, false, 0.0, true, false);
    EXPECT_TRUE(rawDev.isOk());
}

// Test construction with discardDiag
TEST_F(TextOutputDevTest_1224, ConstructionWithDiscardDiag_1224) {
    TextOutputDev diagDev(textOutputCallback, nullptr, false, 0.0, false, true);
    EXPECT_TRUE(diagDev.isOk());
}
