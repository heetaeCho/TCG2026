#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Helper callback function for TextOutputDev constructor that takes a function
static void textOutputCallback(void *stream, const char *text, int len) {
    // Simple callback that does nothing
}

class TextOutputDevTest_1223 : public ::testing::Test {
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

// Test that the device is properly created and reports ok
TEST_F(TextOutputDevTest_1223, IsOkAfterConstruction_1223) {
    EXPECT_TRUE(dev->isOk());
}

// Test enableHTMLExtras with true
TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasTrue_1223) {
    // Should not throw or crash
    EXPECT_NO_FATAL_FAILURE(dev->enableHTMLExtras(true));
}

// Test enableHTMLExtras with false
TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasFalse_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->enableHTMLExtras(false));
}

// Test toggling enableHTMLExtras
TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasToggle_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->enableHTMLExtras(true));
    EXPECT_NO_FATAL_FAILURE(dev->enableHTMLExtras(false));
    EXPECT_NO_FATAL_FAILURE(dev->enableHTMLExtras(true));
}

// Test setTextEOL with different EndOfLineKind values
TEST_F(TextOutputDevTest_1223, SetTextEOLUnix_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->setTextEOL(eolUnix));
}

TEST_F(TextOutputDevTest_1223, SetTextEOLDOS_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->setTextEOL(eolDOS));
}

TEST_F(TextOutputDevTest_1223, SetTextEOLMac_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->setTextEOL(eolMac));
}

// Test setTextPageBreaks
TEST_F(TextOutputDevTest_1223, SetTextPageBreaksTrue_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->setTextPageBreaks(true));
}

TEST_F(TextOutputDevTest_1223, SetTextPageBreaksFalse_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->setTextPageBreaks(false));
}

// Test setMinColSpacing1 and getMinColSpacing1
TEST_F(TextOutputDevTest_1223, SetAndGetMinColSpacing1_1223) {
    dev->setMinColSpacing1(3.5);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 3.5);
}

TEST_F(TextOutputDevTest_1223, SetMinColSpacing1Zero_1223) {
    dev->setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 0.0);
}

TEST_F(TextOutputDevTest_1223, SetMinColSpacing1Negative_1223) {
    dev->setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), -1.0);
}

TEST_F(TextOutputDevTest_1223, SetMinColSpacing1Large_1223) {
    dev->setMinColSpacing1(1000000.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1000000.0);
}

// Test useDrawChar returns true (TextOutputDev typically uses drawChar)
TEST_F(TextOutputDevTest_1223, UseDrawCharReturnsTrue_1223) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test upsideDown
TEST_F(TextOutputDevTest_1223, UpsideDown_1223) {
    // Just verify it returns a consistent value without crashing
    bool result = dev->upsideDown();
    // Call again to verify consistency
    EXPECT_EQ(result, dev->upsideDown());
}

// Test interpretType3Chars
TEST_F(TextOutputDevTest_1223, InterpretType3Chars_1223) {
    bool result = dev->interpretType3Chars();
    EXPECT_EQ(result, dev->interpretType3Chars());
}

// Test needNonText
TEST_F(TextOutputDevTest_1223, NeedNonText_1223) {
    bool result = dev->needNonText();
    EXPECT_EQ(result, dev->needNonText());
}

// Test needCharCount
TEST_F(TextOutputDevTest_1223, NeedCharCount_1223) {
    bool result = dev->needCharCount();
    EXPECT_EQ(result, dev->needCharCount());
}

// Test setMergeCombining
TEST_F(TextOutputDevTest_1223, SetMergeCombiningTrue_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->setMergeCombining(true));
}

TEST_F(TextOutputDevTest_1223, SetMergeCombiningFalse_1223) {
    EXPECT_NO_FATAL_FAILURE(dev->setMergeCombining(false));
}

// Test makeWordList returns a non-null unique_ptr (even if empty)
TEST_F(TextOutputDevTest_1223, MakeWordListNotNull_1223) {
    auto wordList = dev->makeWordList();
    EXPECT_NE(wordList, nullptr);
}

// Test takeText returns a non-null unique_ptr
TEST_F(TextOutputDevTest_1223, TakeTextNotNull_1223) {
    auto textPage = dev->takeText();
    EXPECT_NE(textPage, nullptr);
}

// Test getText with no content area (empty optional)
TEST_F(TextOutputDevTest_1223, GetTextEmptyArea_1223) {
    std::optional<PDFRectangle> area = std::nullopt;
    GooString *result = dev->getText(area);
    // Should return some string (possibly empty) without crashing
    EXPECT_NE(result, nullptr);
    delete result;
}

// Test getText with a specific area
TEST_F(TextOutputDevTest_1223, GetTextWithArea_1223) {
    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;
    std::optional<PDFRectangle> area = rect;
    GooString *result = dev->getText(area);
    EXPECT_NE(result, nullptr);
    delete result;
}

// Test construction with file-based constructor (using /dev/null or similar)
TEST(TextOutputDevFileTest_1223, ConstructWithDevNull_1223) {
#ifdef _WIN32
    const char *nullDev = "NUL";
#else
    const char *nullDev = "/dev/null";
#endif
    TextOutputDev fileDev(nullDev, false, 0.0, false, false, false);
    EXPECT_TRUE(fileDev.isOk());
}

// Test construction with append mode
TEST(TextOutputDevFileTest_1223, ConstructWithAppendMode_1223) {
#ifdef _WIN32
    const char *nullDev = "NUL";
#else
    const char *nullDev = "/dev/null";
#endif
    TextOutputDev fileDev(nullDev, false, 0.0, false, true, false);
    EXPECT_TRUE(fileDev.isOk());
}

// Test construction with physical layout mode
TEST(TextOutputDevFileTest_1223, ConstructWithPhysLayout_1223) {
    TextOutputDev dev(textOutputCallback, nullptr, true, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with fixed pitch
TEST(TextOutputDevFileTest_1223, ConstructWithFixedPitch_1223) {
    TextOutputDev dev(textOutputCallback, nullptr, false, 12.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with raw order
TEST(TextOutputDevFileTest_1223, ConstructWithRawOrder_1223) {
    TextOutputDev dev(textOutputCallback, nullptr, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with discardDiag
TEST(TextOutputDevFileTest_1223, ConstructWithDiscardDiag_1223) {
    TextOutputDev dev(textOutputCallback, nullptr, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test setMinColSpacing1 multiple times
TEST_F(TextOutputDevTest_1223, SetMinColSpacing1MultipleTimes_1223) {
    dev->setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 1.0);
    dev->setMinColSpacing1(2.0);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 2.0);
    dev->setMinColSpacing1(0.5);
    EXPECT_DOUBLE_EQ(dev->getMinColSpacing1(), 0.5);
}

// Test getFlows when no content has been processed
TEST_F(TextOutputDevTest_1223, GetFlowsNoContent_1223) {
    const TextFlow *flows = dev->getFlows();
    // With no content, flows should be null
    EXPECT_EQ(flows, nullptr);
}

// Test findText with empty search (zero length)
TEST_F(TextOutputDevTest_1223, FindTextNoContent_1223) {
    Unicode searchStr[] = { 'A' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev->findText(searchStr, 1, true, true, false, false, false, false, false,
                                &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findCharRange with no content
TEST_F(TextOutputDevTest_1223, FindCharRangeNoContent_1223) {
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev->findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    // With no content, should return false
    EXPECT_FALSE(found);
}
