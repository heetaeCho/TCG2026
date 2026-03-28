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

// Helper callback function for TextOutputDev with function output
static void textOutputCallback(void *stream, const char *text, int len) {
    if (stream) {
        std::string *output = static_cast<std::string *>(stream);
        output->append(text, len);
    }
}

class TextOutputDevTest_1218 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test construction with file output (using /dev/null or "-" for stdout)
TEST_F(TextOutputDevTest_1218, ConstructWithDashForStdout_1218) {
    TextOutputDev dev("-", false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with callback function
TEST_F(TextOutputDevTest_1218, ConstructWithCallback_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test upsideDown returns true
TEST_F(TextOutputDevTest_1218, UpsideDownReturnsTrue_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test useDrawChar returns true
TEST_F(TextOutputDevTest_1218, UseDrawCharReturnsTrue_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.useDrawChar());
}

// Test interpretType3Chars returns false
TEST_F(TextOutputDevTest_1218, InterpretType3CharsReturnsFalse_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test needNonText returns false
TEST_F(TextOutputDevTest_1218, NeedNonTextReturnsFalse_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_FALSE(dev.needNonText());
}

// Test needCharCount returns true
TEST_F(TextOutputDevTest_1218, NeedCharCountReturnsTrue_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.needCharCount());
}

// Test isOk with valid callback construction
TEST_F(TextOutputDevTest_1218, IsOkWithCallbackConstruction_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with invalid file
TEST_F(TextOutputDevTest_1218, ConstructWithInvalidFile_1218) {
    TextOutputDev dev("/nonexistent/path/that/should/fail/output.txt", false, 0.0, false, false, false);
    EXPECT_FALSE(dev.isOk());
}

// Test setMergeCombining does not crash
TEST_F(TextOutputDevTest_1218, SetMergeCombiningNoCrash_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.setMergeCombining(true);
    dev.setMergeCombining(false);
}

// Test enableHTMLExtras does not crash
TEST_F(TextOutputDevTest_1218, EnableHTMLExtrasNoCrash_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.enableHTMLExtras(true);
    dev.enableHTMLExtras(false);
}

// Test setTextEOL with different EOL kinds
TEST_F(TextOutputDevTest_1218, SetTextEOL_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.setTextEOL(eolUnix);
    dev.setTextEOL(eolDOS);
    dev.setTextEOL(eolMac);
}

// Test setTextPageBreaks
TEST_F(TextOutputDevTest_1218, SetTextPageBreaks_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.setTextPageBreaks(true);
    dev.setTextPageBreaks(false);
}

// Test getMinColSpacing1 and setMinColSpacing1
TEST_F(TextOutputDevTest_1218, MinColSpacing1GetSet_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.setMinColSpacing1(2.5);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 2.5);
}

// Test setMinColSpacing1 with zero
TEST_F(TextOutputDevTest_1218, MinColSpacing1Zero_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 0.0);
}

// Test setMinColSpacing1 with negative value
TEST_F(TextOutputDevTest_1218, MinColSpacing1Negative_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), -1.0);
}

// Test makeWordList returns a valid (possibly empty) list without pages
TEST_F(TextOutputDevTest_1218, MakeWordListWithoutPages_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    auto wordList = dev.makeWordList();
    EXPECT_NE(wordList, nullptr);
}

// Test takeText returns a valid TextPage
TEST_F(TextOutputDevTest_1218, TakeTextReturnsValidPage_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    auto textPage = dev.takeText();
    EXPECT_NE(textPage, nullptr);
}

// Test getText with no content returns empty or valid string
TEST_F(TextOutputDevTest_1218, GetTextWithNoContent_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    std::optional<PDFRectangle> area = std::nullopt;
    GooString *text = dev.getText(area);
    ASSERT_NE(text, nullptr);
    // With no content, getText should return an empty or near-empty string
    delete text;
}

// Test getFlows returns nullptr when no content is loaded
TEST_F(TextOutputDevTest_1218, GetFlowsNullWhenNoContent_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    const TextFlow *flows = dev.getFlows();
    // With no pages processed, flows should be null
    EXPECT_EQ(flows, nullptr);
}

// Test findText with empty text on empty page
TEST_F(TextOutputDevTest_1218, FindTextOnEmptyPage_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    Unicode searchStr[] = { 'H', 'e', 'l', 'l', 'o' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findText(searchStr, 5, true, true, false, false, false, false, false,
                              &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test findCharRange on empty page
TEST_F(TextOutputDevTest_1218, FindCharRangeOnEmptyPage_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool found = dev.findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test construction with physLayout enabled
TEST_F(TextOutputDevTest_1218, ConstructWithPhysLayout_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with fixedPitch
TEST_F(TextOutputDevTest_1218, ConstructWithFixedPitch_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 10.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with rawOrder
TEST_F(TextOutputDevTest_1218, ConstructWithRawOrder_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with discardDiag
TEST_F(TextOutputDevTest_1218, ConstructWithDiscardDiag_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with all options enabled
TEST_F(TextOutputDevTest_1218, ConstructWithAllOptions_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 12.0, true, true);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with null callback function
TEST_F(TextOutputDevTest_1218, ConstructWithNullCallback_1218) {
    TextOutputDev dev(static_cast<TextOutputFunc>(nullptr), nullptr, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test that setMinColSpacing1 with large value works
TEST_F(TextOutputDevTest_1218, MinColSpacing1LargeValue_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.setMinColSpacing1(1000000.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 1000000.0);
}

// Test multiple takeText calls
TEST_F(TextOutputDevTest_1218, MultipleTakeTextCalls_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    auto textPage1 = dev.takeText();
    EXPECT_NE(textPage1, nullptr);
    
    // After takeText, the internal text page should be replaced
    // A second call should still work
    auto textPage2 = dev.takeText();
    EXPECT_NE(textPage2, nullptr);
}

// Test endPage without startPage (should not crash)
TEST_F(TextOutputDevTest_1218, EndPageWithoutStartPage_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.endPage();
}

// Test incCharCount does not crash
TEST_F(TextOutputDevTest_1218, IncCharCountNoCrash_1218) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    dev.incCharCount(5);
    dev.incCharCount(0);
    dev.incCharCount(-1);
}
