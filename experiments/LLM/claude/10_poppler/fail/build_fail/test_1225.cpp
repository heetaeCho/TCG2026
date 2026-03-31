#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Helper callback function for TextOutputDev constructor that takes a function
static void dummyOutputFunc(void *stream, const char *text, int len) {
    // Do nothing
}

class TextOutputDevTest_1225 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a TextOutputDev using the function-based constructor
        // Using nullptr/dummy values where appropriate
        dev = std::make_unique<TextOutputDev>(dummyOutputFunc, nullptr, false, 0.0, false, false);
    }

    void TearDown() override {
        dev.reset();
    }

    std::unique_ptr<TextOutputDev> dev;
};

// Test that the device is created successfully and isOk returns true
TEST_F(TextOutputDevTest_1225, ConstructionWithFuncIsOk_1225) {
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->isOk());
}

// Test setTextPageBreaks with true
TEST_F(TextOutputDevTest_1225, SetTextPageBreaksTrue_1225) {
    // Should not crash or throw
    dev->setTextPageBreaks(true);
    // No direct getter for textPageBreaks, but we verify it doesn't crash
    SUCCEED();
}

// Test setTextPageBreaks with false
TEST_F(TextOutputDevTest_1225, SetTextPageBreaksFalse_1225) {
    dev->setTextPageBreaks(false);
    SUCCEED();
}

// Test toggling setTextPageBreaks multiple times
TEST_F(TextOutputDevTest_1225, SetTextPageBreaksToggle_1225) {
    dev->setTextPageBreaks(true);
    dev->setTextPageBreaks(false);
    dev->setTextPageBreaks(true);
    dev->setTextPageBreaks(false);
    SUCCEED();
}

// Test setTextEOL
TEST_F(TextOutputDevTest_1225, SetTextEOL_Unix_1225) {
    dev->setTextEOL(eolUnix);
    SUCCEED();
}

TEST_F(TextOutputDevTest_1225, SetTextEOL_DOS_1225) {
    dev->setTextEOL(eolDOS);
    SUCCEED();
}

TEST_F(TextOutputDevTest_1225, SetTextEOL_Mac_1225) {
    dev->setTextEOL(eolMac);
    SUCCEED();
}

// Test enableHTMLExtras
TEST_F(TextOutputDevTest_1225, EnableHTMLExtrasTrue_1225) {
    dev->enableHTMLExtras(true);
    SUCCEED();
}

TEST_F(TextOutputDevTest_1225, EnableHTMLExtrasFalse_1225) {
    dev->enableHTMLExtras(false);
    SUCCEED();
}

// Test upsideDown
TEST_F(TextOutputDevTest_1225, UpsideDown_1225) {
    // TextOutputDev typically returns true for upsideDown
    bool result = dev->upsideDown();
    EXPECT_TRUE(result);
}

// Test useDrawChar
TEST_F(TextOutputDevTest_1225, UseDrawChar_1225) {
    // TextOutputDev should use drawChar
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result);
}

// Test interpretType3Chars
TEST_F(TextOutputDevTest_1225, InterpretType3Chars_1225) {
    bool result = dev->interpretType3Chars();
    // Typically false for TextOutputDev
    EXPECT_FALSE(result);
}

// Test needNonText
TEST_F(TextOutputDevTest_1225, NeedNonText_1225) {
    bool result = dev->needNonText();
    EXPECT_FALSE(result);
}

// Test needCharCount
TEST_F(TextOutputDevTest_1225, NeedCharCount_1225) {
    bool result = dev->needCharCount();
    EXPECT_TRUE(result);
}

// Test setMergeCombining
TEST_F(TextOutputDevTest_1225, SetMergeCombiningTrue_1225) {
    dev->setMergeCombining(true);
    SUCCEED();
}

TEST_F(TextOutputDevTest_1225, SetMergeCombiningFalse_1225) {
    dev->setMergeCombining(false);
    SUCCEED();
}

// Test setMinColSpacing1 and getMinColSpacing1
TEST_F(TextOutputDevTest_1225, SetAndGetMinColSpacing1_1225) {
    double val = 3.5;
    dev->setMinColSpacing1(val);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), val);
}

TEST_F(TextOutputDevTest_1225, SetMinColSpacing1Zero_1225) {
    dev->setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 0.0);
}

TEST_F(TextOutputDevTest_1225, SetMinColSpacing1Negative_1225) {
    dev->setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), -1.0);
}

TEST_F(TextOutputDevTest_1225, SetMinColSpacing1Large_1225) {
    dev->setMinColSpacing1(1000000.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1000000.0);
}

// Test makeWordList without any content
TEST_F(TextOutputDevTest_1225, MakeWordListEmpty_1225) {
    auto wordList = dev->makeWordList();
    ASSERT_NE(wordList, nullptr);
    EXPECT_EQ(wordList->getLength(), 0);
}

// Test takeText
TEST_F(TextOutputDevTest_1225, TakeTextNotNull_1225) {
    auto textPage = dev->takeText();
    EXPECT_NE(textPage, nullptr);
}

// Test getFlows without content
TEST_F(TextOutputDevTest_1225, GetFlowsEmpty_1225) {
    const TextFlow *flows = dev->getFlows();
    // Without any content, flows should be nullptr
    EXPECT_EQ(flows, nullptr);
}

// Test getText with empty area (no content added)
TEST_F(TextOutputDevTest_1225, GetTextEmptyArea_1225) {
    std::optional<PDFRectangle> area = std::nullopt;
    GooString result = dev->getText(area);
    // With no content, text should be empty or just a newline-like string
    // We just check it doesn't crash
    SUCCEED();
}

// Test construction with file output (using /dev/null or similar)
TEST_F(TextOutputDevTest_1225, ConstructionWithFile_1225) {
#ifdef _WIN32
    TextOutputDev fileDev("NUL", false, 0.0, false, false, false);
#else
    TextOutputDev fileDev("/dev/null", false, 0.0, false, false, false);
#endif
    EXPECT_TRUE(fileDev.isOk());
}

// Test construction with physical layout
TEST_F(TextOutputDevTest_1225, ConstructionWithPhysLayout_1225) {
    TextOutputDev physDev(dummyOutputFunc, nullptr, true, 0.0, false, false);
    EXPECT_TRUE(physDev.isOk());
}

// Test construction with fixed pitch
TEST_F(TextOutputDevTest_1225, ConstructionWithFixedPitch_1225) {
    TextOutputDev fpDev(dummyOutputFunc, nullptr, false, 10.0, false, false);
    EXPECT_TRUE(fpDev.isOk());
}

// Test construction with raw order
TEST_F(TextOutputDevTest_1225, ConstructionWithRawOrder_1225) {
    TextOutputDev rawDev(dummyOutputFunc, nullptr, false, 0.0, true, false);
    EXPECT_TRUE(rawDev.isOk());
}

// Test construction with discard diagonal
TEST_F(TextOutputDevTest_1225, ConstructionWithDiscardDiag_1225) {
    TextOutputDev diagDev(dummyOutputFunc, nullptr, false, 0.0, false, true);
    EXPECT_TRUE(diagDev.isOk());
}

// Test findText with empty content (should return false)
TEST_F(TextOutputDevTest_1225, FindTextOnEmptyPage_1225) {
    Unicode searchStr[] = { 'h', 'e', 'l', 'l', 'o' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev->findText(searchStr, 5, true, true, false, false, false, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findCharRange with empty content
TEST_F(TextOutputDevTest_1225, FindCharRangeOnEmptyPage_1225) {
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev->findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test incCharCount doesn't crash
TEST_F(TextOutputDevTest_1225, IncCharCountNoCrash_1225) {
    dev->incCharCount(5);
    SUCCEED();
}

TEST_F(TextOutputDevTest_1225, IncCharCountZero_1225) {
    dev->incCharCount(0);
    SUCCEED();
}
