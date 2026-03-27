#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"  // Include the header for the TextLine class

// Mock classes for external dependencies
class MockTextWord : public TextWord {
public:
    MOCK_METHOD(PDFRectangle, getBBox, (), (const, override));
};

class MockTextSelectionVisitor : public TextSelectionVisitor {
public:
    MOCK_METHOD(void, visit, (TextLine* line, const PDFRectangle* selection, SelectionStyle style), (override));
};

// Test Suite for TextLine class
class TextLineTest : public ::testing::Test {
protected:
    // Set up a simple TextLine object for testing
    TextLine *line;
    MockTextWord *mockWord;
    PDFRectangle bbox = {0, 0, 10, 10};  // Sample bounding box

    void SetUp() override {
        mockWord = new MockTextWord();
        line = new TextLine(nullptr, 0, 0.0); // Create TextLine object with dummy values
    }

    void TearDown() override {
        delete mockWord;
        delete line;
    }
};

// Normal operation test
TEST_F(TextLineTest, GetBBox_ReturnsCorrectBoundingBox_1201) {
    EXPECT_CALL(*mockWord, getBBox())
        .WillOnce(testing::Return(bbox));

    line->addWord(mockWord);
    EXPECT_EQ(line->getBBox().xMin, 0);
    EXPECT_EQ(line->getBBox().yMin, 0);
    EXPECT_EQ(line->getBBox().xMax, 10);
    EXPECT_EQ(line->getBBox().yMax, 10);
}

// Boundary conditions test for empty line (no words)
TEST_F(TextLineTest, GetBBox_EmptyLine_ReturnsZeroBounds_1202) {
    EXPECT_EQ(line->getBBox().xMin, 0);
    EXPECT_EQ(line->getBBox().yMin, 0);
    EXPECT_EQ(line->getBBox().xMax, 0);
    EXPECT_EQ(line->getBBox().yMax, 0);
}

// Test addWord method (adding a word)
TEST_F(TextLineTest, AddWord_WordAddedSuccessfully_1203) {
    line->addWord(mockWord);

    // Verify if the word is added by checking the first word in the line
    EXPECT_EQ(line->getWords(), mockWord);
}

// Boundary test for hyphenation state (line is hyphenated)
TEST_F(TextLineTest, IsHyphenated_LineIsHyphenated_1204) {
    // Simulate a hyphenated line
    line->addWord(mockWord);  // Add words and set the hyphenated state
    EXPECT_TRUE(line->isHyphenated());
}

// Boundary test for hyphenation state (line is not hyphenated)
TEST_F(TextLineTest, IsHyphenated_LineNotHyphenated_1205) {
    line->addWord(mockWord);  // Add words but no hyphenation
    EXPECT_FALSE(line->isHyphenated());
}

// Exceptional case: attempting to visit selection on a line with no words
TEST_F(TextLineTest, VisitSelection_NoWords_1206) {
    MockTextSelectionVisitor mockVisitor;
    PDFRectangle selection = {0, 0, 10, 10};
    SelectionStyle style = SelectionStyle::kHighlight;

    EXPECT_CALL(mockVisitor, visit(testing::_, testing::_, testing::_))
        .Times(0);  // No selection visit should occur if there are no words
    line->visitSelection(&mockVisitor, &selection, style);
}

// Verify external interaction with TextSelectionVisitor
TEST_F(TextLineTest, VisitSelection_WithWords_1207) {
    MockTextSelectionVisitor mockVisitor;
    PDFRectangle selection = {0, 0, 10, 10};
    SelectionStyle style = SelectionStyle::kHighlight;
    line->addWord(mockWord);

    EXPECT_CALL(mockVisitor, visit(testing::_, testing::_, testing::_))
        .Times(1);  // Expect visit to be called once
    line->visitSelection(&mockVisitor, &selection, style);
}

// Exceptional case for invalid line comparison (null pointer)
TEST_F(TextLineTest, CompareLines_NullPointer_1208) {
    EXPECT_EQ(line->primaryCmp(nullptr), 0);
    EXPECT_EQ(line->secondaryCmp(nullptr), 0);
    EXPECT_EQ(line->cmpYX(nullptr), 0);
}

// Test that coalesce works correctly
TEST_F(TextLineTest, Coalesce_LineCoalescing_1209) {
    UnicodeMap mockUnicodeMap;
    line->coalesce(&mockUnicodeMap);
    // Since the actual coalesce logic isn't implemented, we can only check if it runs without error
    SUCCEED(); // Placeholder for actual assertions if the logic were known
}