#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Helper callback function for TextOutputDev constructor that takes a function
static void dummyOutputFunc(void *stream, const char *text, int len) {
    // Do nothing
}

class TextOutputDevTest_1226 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TextOutputDev can be created with a callback function
TEST_F(TextOutputDevTest_1226, ConstructWithCallback_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test getMinColSpacing1 returns default value after construction
TEST_F(TextOutputDevTest_1226, GetMinColSpacing1Default_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    // After construction, getMinColSpacing1 should return some default value
    double val = dev.getMinColSpacing1();
    // We just verify it's callable and returns a finite number
    EXPECT_FALSE(std::isnan(val));
    EXPECT_FALSE(std::isinf(val));
}

// Test setMinColSpacing1 and getMinColSpacing1 round-trip
TEST_F(TextOutputDevTest_1226, SetAndGetMinColSpacing1_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setMinColSpacing1(3.5);
    EXPECT_DOUBLE_EQ(3.5, dev.getMinColSpacing1());
}

// Test setMinColSpacing1 with zero
TEST_F(TextOutputDevTest_1226, SetMinColSpacing1Zero_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(0.0, dev.getMinColSpacing1());
}

// Test setMinColSpacing1 with negative value
TEST_F(TextOutputDevTest_1226, SetMinColSpacing1Negative_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(-1.0, dev.getMinColSpacing1());
}

// Test setMinColSpacing1 with large value
TEST_F(TextOutputDevTest_1226, SetMinColSpacing1Large_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setMinColSpacing1(1e10);
    EXPECT_DOUBLE_EQ(1e10, dev.getMinColSpacing1());
}

// Test setMinColSpacing1 with very small positive value
TEST_F(TextOutputDevTest_1226, SetMinColSpacing1SmallPositive_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setMinColSpacing1(1e-15);
    EXPECT_DOUBLE_EQ(1e-15, dev.getMinColSpacing1());
}

// Test setMinColSpacing1 multiple times overwrites previous value
TEST_F(TextOutputDevTest_1226, SetMinColSpacing1MultipleTimes_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(1.0, dev.getMinColSpacing1());
    dev.setMinColSpacing1(2.0);
    EXPECT_DOUBLE_EQ(2.0, dev.getMinColSpacing1());
    dev.setMinColSpacing1(100.0);
    EXPECT_DOUBLE_EQ(100.0, dev.getMinColSpacing1());
}

// Test upsideDown returns expected value
TEST_F(TextOutputDevTest_1226, UpsideDown_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    // upsideDown is a bool, just verify it's callable
    bool result = dev.upsideDown();
    (void)result; // We just check it doesn't crash
}

// Test useDrawChar returns expected value
TEST_F(TextOutputDevTest_1226, UseDrawChar_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    bool result = dev.useDrawChar();
    // TextOutputDev should use drawChar
    EXPECT_TRUE(result);
}

// Test interpretType3Chars returns expected value
TEST_F(TextOutputDevTest_1226, InterpretType3Chars_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    bool result = dev.interpretType3Chars();
    (void)result; // Just verify it's callable
}

// Test needNonText returns expected value
TEST_F(TextOutputDevTest_1226, NeedNonText_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    bool result = dev.needNonText();
    (void)result;
}

// Test needCharCount returns expected value
TEST_F(TextOutputDevTest_1226, NeedCharCount_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    bool result = dev.needCharCount();
    (void)result;
}

// Test isOk with callback-based constructor
TEST_F(TextOutputDevTest_1226, IsOkWithCallback_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableHTMLExtras doesn't crash
TEST_F(TextOutputDevTest_1226, EnableHTMLExtras_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.enableHTMLExtras(true);
    // No crash is success
    dev.enableHTMLExtras(false);
}

// Test setTextPageBreaks doesn't crash
TEST_F(TextOutputDevTest_1226, SetTextPageBreaks_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setTextPageBreaks(true);
    dev.setTextPageBreaks(false);
}

// Test setTextEOL doesn't crash
TEST_F(TextOutputDevTest_1226, SetTextEOL_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setTextEOL(eolUnix);
    dev.setTextEOL(eolDOS);
    dev.setTextEOL(eolMac);
}

// Test setMergeCombining doesn't crash
TEST_F(TextOutputDevTest_1226, SetMergeCombining_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    dev.setMergeCombining(true);
    dev.setMergeCombining(false);
}

// Test makeWordList returns a result (possibly empty)
TEST_F(TextOutputDevTest_1226, MakeWordList_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    auto wordList = dev.makeWordList();
    EXPECT_NE(nullptr, wordList.get());
}

// Test takeText returns a TextPage
TEST_F(TextOutputDevTest_1226, TakeText_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    auto textPage = dev.takeText();
    EXPECT_NE(nullptr, textPage.get());
}

// Test getText with no content returns empty or valid string
TEST_F(TextOutputDevTest_1226, GetTextNoContent_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    std::optional<PDFRectangle> area = std::nullopt;
    GooString text = dev.getText(area);
    // With no pages processed, text should be empty or at least not crash
    EXPECT_GE(text.getLength(), 0);
}

// Test construction with physLayout=true
TEST_F(TextOutputDevTest_1226, ConstructWithPhysLayout_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, true, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with fixedPitch set
TEST_F(TextOutputDevTest_1226, ConstructWithFixedPitch_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 10.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with rawOrder=true
TEST_F(TextOutputDevTest_1226, ConstructWithRawOrder_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with discardDiag=true
TEST_F(TextOutputDevTest_1226, ConstructWithDiscardDiag_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test file-based constructor with nullptr filename (output to stdout)
TEST_F(TextOutputDevTest_1226, ConstructWithNullFilename_1226) {
    TextOutputDev dev(nullptr, false, 0.0, false, false, false);
    // nullptr filename typically means stdout
    EXPECT_TRUE(dev.isOk());
}

// Test getFlows returns nullptr when no pages have been processed
TEST_F(TextOutputDevTest_1226, GetFlowsNoContent_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    const TextFlow *flows = dev.getFlows();
    // With no content, flows should be nullptr
    EXPECT_EQ(nullptr, flows);
}

// Test findText with empty search on empty document
TEST_F(TextOutputDevTest_1226, FindTextEmptyDocument_1226) {
    TextOutputDev dev(dummyOutputFunc, nullptr, false, 0.0, false, false);
    Unicode searchStr[] = { 'a' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 1, true, true, false, false, false, false, false,
                              &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}
