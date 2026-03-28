#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <optional>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GooString.h"
#include "Link.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Callback function for TextOutputDev constructor
static void textOutputCallback(void *stream, const char *text, int len) {
    if (stream) {
        std::string *output = static_cast<std::string *>(stream);
        output->append(text, len);
    }
}

class TextOutputDevTest_1220 : public ::testing::Test {
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
TEST_F(TextOutputDevTest_1220, ConstructWithNullFileName_1220) {
    TextOutputDev dev(nullptr, false, 0.0, false, false, false);
    // When fileName is nullptr, it typically writes to stdout, isOk should be true
    EXPECT_TRUE(dev.isOk());
}

// Test construction with callback function
TEST_F(TextOutputDevTest_1220, ConstructWithCallback_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test interpretType3Chars returns false
TEST_F(TextOutputDevTest_1220, InterpretType3CharsReturnsFalse_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test upsideDown returns true (typical for OutputDev subclasses that handle text)
TEST_F(TextOutputDevTest_1220, UpsideDownReturnValue_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test useDrawChar returns true
TEST_F(TextOutputDevTest_1220, UseDrawCharReturnValue_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.useDrawChar());
}

// Test needNonText returns false
TEST_F(TextOutputDevTest_1220, NeedNonTextReturnValue_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_FALSE(dev.needNonText());
}

// Test needCharCount returns true
TEST_F(TextOutputDevTest_1220, NeedCharCountReturnValue_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.needCharCount());
}

// Test setMergeCombining does not crash
TEST_F(TextOutputDevTest_1220, SetMergeCombiningDoesNotCrash_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_NO_FATAL_FAILURE(dev.setMergeCombining(true));
    EXPECT_NO_FATAL_FAILURE(dev.setMergeCombining(false));
}

// Test enableHTMLExtras does not crash
TEST_F(TextOutputDevTest_1220, EnableHTMLExtrasDoesNotCrash_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_NO_FATAL_FAILURE(dev.enableHTMLExtras(true));
    EXPECT_NO_FATAL_FAILURE(dev.enableHTMLExtras(false));
}

// Test setTextEOL with different EndOfLineKind values
TEST_F(TextOutputDevTest_1220, SetTextEOLDoesNotCrash_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_NO_FATAL_FAILURE(dev.setTextEOL(eolUnix));
    EXPECT_NO_FATAL_FAILURE(dev.setTextEOL(eolDOS));
    EXPECT_NO_FATAL_FAILURE(dev.setTextEOL(eolMac));
}

// Test setTextPageBreaks
TEST_F(TextOutputDevTest_1220, SetTextPageBreaksDoesNotCrash_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_NO_FATAL_FAILURE(dev.setTextPageBreaks(true));
    EXPECT_NO_FATAL_FAILURE(dev.setTextPageBreaks(false));
}

// Test getMinColSpacing1 and setMinColSpacing1
TEST_F(TextOutputDevTest_1220, MinColSpacing1GetSet_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(3.5);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 3.5);
}

// Test setMinColSpacing1 with zero
TEST_F(TextOutputDevTest_1220, MinColSpacing1SetToZero_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 0.0);
}

// Test setMinColSpacing1 with negative value
TEST_F(TextOutputDevTest_1220, MinColSpacing1SetNegative_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), -1.0);
}

// Test getText with no page loaded returns empty or handles gracefully
TEST_F(TextOutputDevTest_1220, GetTextWithNoPage_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    std::optional<PDFRectangle> area;
    GooString *text = dev.getText(area);
    ASSERT_NE(text, nullptr);
    // With no page data, text should be empty
    EXPECT_EQ(text->getLength(), 0);
    delete text;
}

// Test makeWordList with no page data
TEST_F(TextOutputDevTest_1220, MakeWordListNoPage_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    auto wordList = dev.makeWordList();
    EXPECT_NE(wordList, nullptr);
}

// Test takeText returns a TextPage
TEST_F(TextOutputDevTest_1220, TakeTextReturnsTextPage_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    auto textPage = dev.takeText();
    EXPECT_NE(textPage, nullptr);
}

// Test getFlows with no page data
TEST_F(TextOutputDevTest_1220, GetFlowsNoPage_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    const TextFlow *flows = dev.getFlows();
    // With no page data, flows should be nullptr
    EXPECT_EQ(flows, nullptr);
}

// Test findText with empty search on empty page
TEST_F(TextOutputDevTest_1220, FindTextOnEmptyPage_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    
    Unicode searchStr[] = { 'a' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 1, true, true, false, false, false, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test construction with physical layout enabled
TEST_F(TextOutputDevTest_1220, ConstructWithPhysLayout_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 10.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with raw order
TEST_F(TextOutputDevTest_1220, ConstructWithRawOrder_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with discard diagonal
TEST_F(TextOutputDevTest_1220, ConstructWithDiscardDiag_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test findCharRange on empty page
TEST_F(TextOutputDevTest_1220, FindCharRangeOnEmptyPage_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool result = dev.findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    // On empty page, should not find the range
    EXPECT_FALSE(result);
}

// Test construction with file that cannot be opened
TEST_F(TextOutputDevTest_1220, ConstructWithInvalidFile_1220) {
    // Attempt to open a file in a non-existent directory
    TextOutputDev dev("/nonexistent_dir/nonexistent_file.txt", false, 0.0, false, false, false);
    EXPECT_FALSE(dev.isOk());
}

// Test construction with callback and null stream
TEST_F(TextOutputDevTest_1220, ConstructWithCallbackNullStream_1220) {
    TextOutputDev dev(textOutputCallback, nullptr, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test incCharCount does not crash
TEST_F(TextOutputDevTest_1220, IncCharCountDoesNotCrash_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_NO_FATAL_FAILURE(dev.incCharCount(5));
    EXPECT_NO_FATAL_FAILURE(dev.incCharCount(0));
}

// Test multiple setMinColSpacing1 calls
TEST_F(TextOutputDevTest_1220, MinColSpacing1MultipleSet_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    dev.setMinColSpacing1(1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 1.0);
    dev.setMinColSpacing1(2.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 2.0);
    dev.setMinColSpacing1(100.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 100.0);
}

// Test takeText followed by getFlows (page should be reset)
TEST_F(TextOutputDevTest_1220, TakeTextResetsPage_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    auto textPage = dev.takeText();
    EXPECT_NE(textPage, nullptr);
    // After takeText, internal text page is replaced; getFlows on new page should be null
    const TextFlow *flows = dev.getFlows();
    EXPECT_EQ(flows, nullptr);
}

// Test findText with zero length search
TEST_F(TextOutputDevTest_1220, FindTextZeroLength_1220) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    
    Unicode searchStr[] = { 'a' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 0, true, true, false, false, false, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}
