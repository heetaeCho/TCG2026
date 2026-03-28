#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Test fixture for TextWord class
class TextWordTest_1179 : public ::testing::Test {
protected:
    // Sample state for the tests
    const GfxState* state = nullptr;
    int rotation = 0;
    double fontSize = 12.0;
    TextWord* word;

    // SetUp method to initialize the object for each test case
    void SetUp() override {
        word = new TextWord(state, rotation, fontSize);
    }

    // TearDown method to clean up after each test case
    void TearDown() override {
        delete word;
    }
};

// Normal operation test case for getFontInfo
TEST_F(TextWordTest_1179, GetFontInfo_ReturnsCorrectFontInfo_1179) {
    TextFontInfo* fontInfo = word->getFontInfo(0);
    EXPECT_NE(fontInfo, nullptr);  // Assuming the font info is initialized
}

// Boundary test case for getFontInfo (empty state or boundary condition)
TEST_F(TextWordTest_1179, GetFontInfo_ThrowsForInvalidIndex_1180) {
    EXPECT_THROW(word->getFontInfo(-1), std::out_of_range);
    EXPECT_THROW(word->getFontInfo(100), std::out_of_range); // Assuming there are fewer than 100 chars
}

// Normal operation test case for getLength
TEST_F(TextWordTest_1179, GetLength_ReturnsCorrectLength_1181) {
    int length = word->getLength();
    EXPECT_GT(length, 0);  // Assuming TextWord contains some characters
}

// Boundary test case for getLength (empty or minimal state)
TEST_F(TextWordTest_1179, GetLength_ReturnsZeroForEmptyTextWord_1182) {
    TextWord emptyWord(state, 0, 0);  // Create a word with no content
    EXPECT_EQ(emptyWord.getLength(), 0);  // No characters, so length should be 0
}

// Normal operation test case for getText
TEST_F(TextWordTest_1179, GetText_ReturnsCorrectText_1183) {
    auto text = word->getText();
    EXPECT_NE(text, nullptr);  // Assuming it returns a non-null pointer
    EXPECT_GT(text->length(), 0);  // The word should contain some text
}

// Exceptional case for getText (edge case)
TEST_F(TextWordTest_1179, GetText_HandlesEmptyTextWord_1184) {
    TextWord emptyWord(state, 0, 0);
    auto text = emptyWord.getText();
    EXPECT_EQ(text->length(), 0);  // Empty word should return an empty string
}

// Normal operation test case for getColor
TEST_F(TextWordTest_1179, GetColor_ReturnsCorrectColor_1185) {
    double r, g, b;
    word->getColor(&r, &g, &b);
    EXPECT_GE(r, 0.0);  // Color values should be valid
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Boundary test case for getColor (extreme values)
TEST_F(TextWordTest_1179, GetColor_HandlesNoColor_1186) {
    // Simulate a color-less TextWord, assuming this scenario exists
    TextWord noColorWord(state, 0, 0); 
    double r, g, b;
    noColorWord.getColor(&r, &g, &b);
    EXPECT_EQ(r, 0.0);
    EXPECT_EQ(g, 0.0);
    EXPECT_EQ(b, 0.0);
}

// Normal operation test case for nextWord
TEST_F(TextWordTest_1179, NextWord_ReturnsCorrectWord_1187) {
    TextWord* next = word->nextWord();
    EXPECT_NE(next, nullptr);  // Assuming the next word exists
}

// Exceptional case for nextWord (no next word)
TEST_F(TextWordTest_1179, NextWord_ReturnsNullForLastWord_1188) {
    TextWord lastWord(state, 0, 0);  // Last word in a sequence
    TextWord* next = lastWord.nextWord();
    EXPECT_EQ(next, nullptr);  // No next word should be returned
}

// Test for proper handling of rotation
TEST_F(TextWordTest_1179, GetRotation_ReturnsCorrectRotation_1189) {
    int rotation = word->getRotation();
    EXPECT_EQ(rotation, 0);  // Assuming rotation was initialized to 0
}

// Test for spaceAfter field (normal and boundary condition)
TEST_F(TextWordTest_1179, HasSpaceAfter_ReturnsCorrectResult_1190) {
    EXPECT_TRUE(word->hasSpaceAfter());  // Assuming default spaceAfter is true
    TextWord noSpaceWord(state, 0, 0);  // Create a word with no space after
    EXPECT_FALSE(noSpaceWord.hasSpaceAfter());  // Should return false
}