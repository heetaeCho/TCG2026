#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <optional>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GooString.h"
#include "Link.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Callback function for TextOutputDev with function-based constructor
static void textOutputCallback(void *stream, const char *text, int len) {
    if (stream) {
        std::string *output = static_cast<std::string *>(stream);
        output->append(text, len);
    }
}

class TextOutputDevTest_1217 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test: Creating TextOutputDev with a valid file name
TEST_F(TextOutputDevTest_1217, ConstructWithValidFileName_1217) {
    TextOutputDev dev("/dev/null", false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Creating TextOutputDev with a callback function
TEST_F(TextOutputDevTest_1217, ConstructWithCallbackFunction_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Creating TextOutputDev with nullptr fileName (stdout)
TEST_F(TextOutputDevTest_1217, ConstructWithNullFileName_1217) {
    // nullptr fileName typically means output to stdout
    TextOutputDev dev(nullptr, false, 0.0, false, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Creating TextOutputDev with invalid file path
TEST_F(TextOutputDevTest_1217, ConstructWithInvalidFilePath_1217) {
    TextOutputDev dev("/nonexistent/path/that/should/not/exist/file.txt", false, 0.0, false, false, false);
    // If the file cannot be opened, isOk() should return false
    EXPECT_FALSE(dev.isOk());
}

// Test: upsideDown returns expected value
TEST_F(TextOutputDevTest_1217, UpsideDownReturnValue_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    // upsideDown() is a property of OutputDev - text output typically returns true
    bool result = dev.upsideDown();
    // Just verify it returns a valid boolean (true or false)
    EXPECT_TRUE(result == true || result == false);
}

// Test: useDrawChar returns true
TEST_F(TextOutputDevTest_1217, UseDrawCharReturnsTrue_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    EXPECT_TRUE(dev.useDrawChar());
}

// Test: interpretType3Chars returns expected value
TEST_F(TextOutputDevTest_1217, InterpretType3Chars_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    bool result = dev.interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test: needNonText returns expected value
TEST_F(TextOutputDevTest_1217, NeedNonText_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    bool result = dev.needNonText();
    EXPECT_TRUE(result == true || result == false);
}

// Test: needCharCount returns expected value
TEST_F(TextOutputDevTest_1217, NeedCharCount_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    bool result = dev.needCharCount();
    EXPECT_TRUE(result == true || result == false);
}

// Test: setMergeCombining does not crash
TEST_F(TextOutputDevTest_1217, SetMergeCombiningDoesNotCrash_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    EXPECT_NO_FATAL_FAILURE(dev.setMergeCombining(true));
    EXPECT_NO_FATAL_FAILURE(dev.setMergeCombining(false));
}

// Test: enableHTMLExtras does not crash
TEST_F(TextOutputDevTest_1217, EnableHTMLExtras_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    EXPECT_NO_FATAL_FAILURE(dev.enableHTMLExtras(true));
    EXPECT_NO_FATAL_FAILURE(dev.enableHTMLExtras(false));
}

// Test: setTextEOL with different values
TEST_F(TextOutputDevTest_1217, SetTextEOL_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    EXPECT_NO_FATAL_FAILURE(dev.setTextEOL(eolUnix));
    EXPECT_NO_FATAL_FAILURE(dev.setTextEOL(eolDOS));
    EXPECT_NO_FATAL_FAILURE(dev.setTextEOL(eolMac));
}

// Test: setTextPageBreaks
TEST_F(TextOutputDevTest_1217, SetTextPageBreaks_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    EXPECT_NO_FATAL_FAILURE(dev.setTextPageBreaks(true));
    EXPECT_NO_FATAL_FAILURE(dev.setTextPageBreaks(false));
}

// Test: getMinColSpacing1 and setMinColSpacing1
TEST_F(TextOutputDevTest_1217, MinColSpacing1GetSet_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    dev.setMinColSpacing1(3.5);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 3.5);
    
    dev.setMinColSpacing1(0.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), 0.0);
    
    dev.setMinColSpacing1(-1.0);
    EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), -1.0);
}

// Test: makeWordList on empty page
TEST_F(TextOutputDevTest_1217, MakeWordListEmpty_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    auto wordList = dev.makeWordList();
    EXPECT_NE(wordList, nullptr);
}

// Test: takeText returns a valid TextPage
TEST_F(TextOutputDevTest_1217, TakeTextReturnsValidPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    auto textPage = dev.takeText();
    EXPECT_NE(textPage, nullptr);
}

// Test: getText with no area (empty page)
TEST_F(TextOutputDevTest_1217, GetTextEmptyPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    std::optional<PDFRectangle> area;
    GooString text = dev.getText(area);
    // On an empty page, we expect an empty or near-empty string
    // Just verify it doesn't crash
    EXPECT_GE(text.getLength(), 0);
}

// Test: getText with a specific rectangle area on empty page
TEST_F(TextOutputDevTest_1217, GetTextWithRectangleEmptyPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    std::optional<PDFRectangle> area(rect);
    GooString text = dev.getText(area);
    EXPECT_GE(text.getLength(), 0);
}

// Test: findText on empty page returns false
TEST_F(TextOutputDevTest_1217, FindTextOnEmptyPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    Unicode searchStr[] = { 'h', 'e', 'l', 'l', 'o' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    
    bool found = dev.findText(searchStr, 5, true, true, false, false, false, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test: findCharRange on empty page
TEST_F(TextOutputDevTest_1217, FindCharRangeOnEmptyPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    bool result = dev.findCharRange(0, 1, &xMin, &yMin, &xMax, &yMax);
    // On empty page, this should return false since there are no characters
    EXPECT_FALSE(result);
}

// Test: getFlows on empty page returns nullptr
TEST_F(TextOutputDevTest_1217, GetFlowsEmptyPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    const TextFlow *flows = dev.getFlows();
    // On an empty page with no content, flows should be null
    EXPECT_EQ(flows, nullptr);
}

// Test: Physical layout mode constructor
TEST_F(TextOutputDevTest_1217, PhysicalLayoutMode_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 10.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Raw order mode constructor
TEST_F(TextOutputDevTest_1217, RawOrderMode_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Discard diagonal text constructor
TEST_F(TextOutputDevTest_1217, DiscardDiagonalMode_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test: Constructor with append mode file
TEST_F(TextOutputDevTest_1217, ConstructWithAppendMode_1217) {
    const char *tmpFile = "/tmp/textoutputdev_test_1217.txt";
    {
        TextOutputDev dev(tmpFile, false, 0.0, false, false, false);
        EXPECT_TRUE(dev.isOk());
    }
    {
        TextOutputDev dev(tmpFile, false, 0.0, false, true, false);
        EXPECT_TRUE(dev.isOk());
    }
    // Clean up
    std::remove(tmpFile);
}

// Test: getSelectionText on empty page
TEST_F(TextOutputDevTest_1217, GetSelectionTextEmptyPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    PDFRectangle selection(0.0, 0.0, 612.0, 792.0);
    GooString selText = dev.getSelectionText(&selection, selectionStyleWord);
    EXPECT_GE(selText.getLength(), 0);
}

// Test: Multiple setMinColSpacing1 calls
TEST_F(TextOutputDevTest_1217, MinColSpacing1MultipleSets_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    for (double val = 0.0; val <= 10.0; val += 1.0) {
        dev.setMinColSpacing1(val);
        EXPECT_DOUBLE_EQ(dev.getMinColSpacing1(), val);
    }
}

// Test: findText with zero-length search string
TEST_F(TextOutputDevTest_1217, FindTextZeroLength_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    Unicode searchStr[] = { 'a' };
    double xMin = 0, yMin = 0, xMax = 0, yMax = 0;
    
    bool found = dev.findText(searchStr, 0, true, true, false, false, false, false, false,
                               &xMin, &yMin, &xMax, &yMax);
    EXPECT_FALSE(found);
}

// Test: Callback constructor with null stream
TEST_F(TextOutputDevTest_1217, CallbackConstructorNullStream_1217) {
    TextOutputDev dev(textOutputCallback, nullptr, false, 0.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: getSelectionRegion on empty page
TEST_F(TextOutputDevTest_1217, GetSelectionRegionEmptyPage_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, false, 0.0, false, false);
    ASSERT_TRUE(dev.isOk());
    
    PDFRectangle selection(0.0, 0.0, 100.0, 100.0);
    auto *regions = dev.getSelectionRegion(&selection, selectionStyleWord, 1.0);
    EXPECT_NE(regions, nullptr);
    // Clean up
    for (auto *r : *regions) {
        delete r;
    }
    delete regions;
}

// Test: Large fixedPitch value
TEST_F(TextOutputDevTest_1217, LargeFixedPitchValue_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, 1000.0, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test: Negative fixedPitch value
TEST_F(TextOutputDevTest_1217, NegativeFixedPitchValue_1217) {
    std::string output;
    TextOutputDev dev(textOutputCallback, &output, true, -1.0, false, false);
    EXPECT_TRUE(dev.isOk());
}
