#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Helper callback function for TextOutputDev constructor
static void textOutputFunc(void *stream, const char *text, int len) {
    // No-op callback for testing
}

class TextOutputDevTest_1227 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a TextOutputDev using the callback-based constructor
        dev = std::make_unique<TextOutputDev>(textOutputFunc, nullptr, false, 0.0, false, false);
    }

    void TearDown() override {
        dev.reset();
    }

    std::unique_ptr<TextOutputDev> dev;
};

// Test that the device is created successfully and isOk returns true
TEST_F(TextOutputDevTest_1227, IsOkAfterConstruction_1227) {
    EXPECT_TRUE(dev->isOk());
}

// Test setMinColSpacing1 and getMinColSpacing1 with a normal positive value
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1NormalValue_1227) {
    dev->setMinColSpacing1(3.5);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 3.5);
}

// Test setMinColSpacing1 with zero
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1Zero_1227) {
    dev->setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 0.0);
}

// Test setMinColSpacing1 with a negative value
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1NegativeValue_1227) {
    dev->setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), -1.0);
}

// Test setMinColSpacing1 with a very large value
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1LargeValue_1227) {
    dev->setMinColSpacing1(1e15);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1e15);
}

// Test setMinColSpacing1 with a very small positive value
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1SmallPositiveValue_1227) {
    dev->setMinColSpacing1(1e-10);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1e-10);
}

// Test that setMinColSpacing1 can be called multiple times and retains the last value
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1MultipleTimes_1227) {
    dev->setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1.0);
    dev->setMinColSpacing1(2.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 2.0);
    dev->setMinColSpacing1(5.5);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 5.5);
}

// Test upsideDown returns expected value
TEST_F(TextOutputDevTest_1227, UpsideDown_1227) {
    // Just verify it returns a bool without crashing
    bool result = dev->upsideDown();
    (void)result; // We just verify it doesn't crash
}

// Test useDrawChar returns expected value
TEST_F(TextOutputDevTest_1227, UseDrawChar_1227) {
    bool result = dev->useDrawChar();
    // TextOutputDev typically returns true for useDrawChar
    EXPECT_TRUE(result);
}

// Test interpretType3Chars returns expected value
TEST_F(TextOutputDevTest_1227, InterpretType3Chars_1227) {
    bool result = dev->interpretType3Chars();
    (void)result; // Verify no crash
}

// Test needNonText returns expected value
TEST_F(TextOutputDevTest_1227, NeedNonText_1227) {
    bool result = dev->needNonText();
    (void)result; // Verify no crash
}

// Test needCharCount returns expected value
TEST_F(TextOutputDevTest_1227, NeedCharCount_1227) {
    bool result = dev->needCharCount();
    (void)result; // Verify no crash
}

// Test setTextPageBreaks
TEST_F(TextOutputDevTest_1227, SetTextPageBreaks_1227) {
    // Verify it doesn't crash when called with true/false
    dev->setTextPageBreaks(true);
    dev->setTextPageBreaks(false);
}

// Test setMergeCombining
TEST_F(TextOutputDevTest_1227, SetMergeCombining_1227) {
    dev->setMergeCombining(true);
    dev->setMergeCombining(false);
}

// Test enableHTMLExtras
TEST_F(TextOutputDevTest_1227, EnableHTMLExtras_1227) {
    dev->enableHTMLExtras(true);
    dev->enableHTMLExtras(false);
}

// Test setTextEOL with different values
TEST_F(TextOutputDevTest_1227, SetTextEOL_1227) {
    dev->setTextEOL(eolUnix);
    dev->setTextEOL(eolDOS);
    dev->setTextEOL(eolMac);
}

// Test makeWordList on empty page (no content drawn)
TEST_F(TextOutputDevTest_1227, MakeWordListEmpty_1227) {
    auto wordList = dev->makeWordList();
    ASSERT_NE(wordList, nullptr);
    EXPECT_EQ(wordList->getLength(), 0);
}

// Test takeText returns a non-null TextPage
TEST_F(TextOutputDevTest_1227, TakeText_1227) {
    auto textPage = dev->takeText();
    EXPECT_NE(textPage, nullptr);
}

// Test getText with no content returns empty string
TEST_F(TextOutputDevTest_1227, GetTextEmpty_1227) {
    std::optional<PDFRectangle> area = std::nullopt;
    GooString result = dev->getText(area);
    // With no pages or content, result should be empty or near-empty
    // Just verify it doesn't crash
}

// Test getFlows on empty device
TEST_F(TextOutputDevTest_1227, GetFlowsEmpty_1227) {
    const TextFlow *flows = dev->getFlows();
    // On a fresh device with no content, flows may be null
    // Just verify no crash
    (void)flows;
}

// Test construction with file name (nullptr to output to stdout or test behavior)
TEST_F(TextOutputDevTest_1227, ConstructWithNullFileName_1227) {
    // Passing nullptr as filename typically means output to stdout
    TextOutputDev fileDev(nullptr, false, 0.0, false, false, false);
    EXPECT_TRUE(fileDev.isOk());
}

// Test construction with different physLayout and fixedPitch parameters
TEST_F(TextOutputDevTest_1227, ConstructWithPhysLayout_1227) {
    TextOutputDev physDev(textOutputFunc, nullptr, true, 10.0, false, false);
    EXPECT_TRUE(physDev.isOk());
}

// Test construction with rawOrder
TEST_F(TextOutputDevTest_1227, ConstructWithRawOrder_1227) {
    TextOutputDev rawDev(textOutputFunc, nullptr, false, 0.0, true, false);
    EXPECT_TRUE(rawDev.isOk());
}

// Test construction with discardDiag
TEST_F(TextOutputDevTest_1227, ConstructWithDiscardDiag_1227) {
    TextOutputDev diagDev(textOutputFunc, nullptr, false, 0.0, false, true);
    EXPECT_TRUE(diagDev.isOk());
}

// Test setMinColSpacing1 with infinity
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1Infinity_1227) {
    double inf = std::numeric_limits<double>::infinity();
    dev->setMinColSpacing1(inf);
    EXPECT_EQ(dev->getMinColSpacing1(), inf);
}

// Test setMinColSpacing1 with negative infinity
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1NegativeInfinity_1227) {
    double neg_inf = -std::numeric_limits<double>::infinity();
    dev->setMinColSpacing1(neg_inf);
    EXPECT_EQ(dev->getMinColSpacing1(), neg_inf);
}

// Test setMinColSpacing1 with max double
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1MaxDouble_1227) {
    double maxVal = std::numeric_limits<double>::max();
    dev->setMinColSpacing1(maxVal);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), maxVal);
}

// Test setMinColSpacing1 with min positive double
TEST_F(TextOutputDevTest_1227, SetMinColSpacing1MinPositiveDouble_1227) {
    double minVal = std::numeric_limits<double>::min();
    dev->setMinColSpacing1(minVal);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), minVal);
}
