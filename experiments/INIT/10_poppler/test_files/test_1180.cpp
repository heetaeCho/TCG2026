#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

using ::testing::_;
using ::testing::Return;

// Mock classes for dependencies
class MockTextFontInfo : public TextFontInfo {
public:
    MOCK_CONST_METHOD0(getFontSize, double());
    MOCK_CONST_METHOD0(getName, std::string());
};

// Unit Test for TextWord Class
class TextWordTest_1180 : public testing::Test {
protected:
    const GfxState* state = nullptr;  // Assuming a valid GfxState object should be used here
    TextWord* textWord;

    void SetUp() override {
        textWord = new TextWord(state, 0, 12.0);  // Assuming rot=0, font size=12.0
    }

    void TearDown() override {
        delete textWord;
    }
};

// Test for getNext() function (Normal Operation)
TEST_F(TextWordTest_1180, GetNextReturnsCorrectTextWord_1180) {
    TextWord* nextWord = new TextWord(state, 0, 12.0);
    textWord->merge(nextWord);

    ASSERT_EQ(textWord->getNext(), nextWord);  // Ensure next TextWord is correctly set
}

// Test for getNext() function (Null case)
TEST_F(TextWordTest_1180, GetNextReturnsNullWhenNoNext_1180) {
    ASSERT_EQ(textWord->getNext(), nullptr);  // If no next word, should return null
}

// Test for getLength() function
TEST_F(TextWordTest_1180, GetLengthReturnsCorrectLength_1180) {
    int length = textWord->getLength();
    ASSERT_GT(length, 0);  // The length should be greater than zero as TextWord is initialized
}

// Test for getFontSize() function
TEST_F(TextWordTest_1180, GetFontSizeReturnsCorrectSize_1180) {
    double fontSize = textWord->getFontSize();
    ASSERT_EQ(fontSize, 12.0);  // Check that font size is correctly set to 12.0
}

// Test for getRotation() function
TEST_F(TextWordTest_1180, GetRotationReturnsCorrectRotation_1180) {
    int rotation = textWord->getRotation();
    ASSERT_EQ(rotation, 0);  // Rotation should be zero as it's initialized with zero
}

// Test for getChar() function (Boundary Condition)
TEST_F(TextWordTest_1180, GetCharReturnsCorrectCharacter_1180) {
    int idx = 0;
    const Unicode* character = textWord->getChar(idx);
    ASSERT_NE(character, nullptr);  // Ensure that we get a valid Unicode character at index 0
}

// Test for getBBox() function (Boundary Condition)
TEST_F(TextWordTest_1180, GetBBoxReturnsValidBounds_1180) {
    double xMin, yMin, xMax, yMax;
    textWord->getBBox(&xMin, &yMin, &xMax, &yMax);
    ASSERT_LE(xMin, xMax);  // Ensure the bounding box has correct coordinates
    ASSERT_LE(yMin, yMax);
}

// Test for merge() function (Normal Operation)
TEST_F(TextWordTest_1180, MergeCombinesTextWords_1180) {
    TextWord* newWord = new TextWord(state, 0, 12.0);
    textWord->merge(newWord);
    ASSERT_EQ(textWord->getNext(), newWord);  // Ensure the merge works and sets the next word
}

// Test for isUnderlined() function (Boundary Condition)
TEST_F(TextWordTest_1180, IsUnderlinedReturnsFalseByDefault_1180) {
    ASSERT_FALSE(textWord->isUnderlined());  // Ensure the default value is false
}

// Test for getColor() function (Normal Operation)
TEST_F(TextWordTest_1180, GetColorReturnsCorrectColor_1180) {
    double r, g, b;
    textWord->getColor(&r, &g, &b);
    ASSERT_GE(r, 0.0);  // Color values should be in the range [0.0, 1.0]
    ASSERT_LE(r, 1.0);
    ASSERT_GE(g, 0.0);
    ASSERT_LE(g, 1.0);
    ASSERT_GE(b, 0.0);
    ASSERT_LE(b, 1.0);
}

// Test for nextWord() function (Boundary Condition)
TEST_F(TextWordTest_1180, NextWordReturnsNullWhenNoNextWord_1180) {
    ASSERT_EQ(textWord->nextWord(), nullptr);  // If no next word is set, nextWord should return null
}

// Test for addCombining() function (Exceptional Case)
TEST_F(TextWordTest_1180, AddCombiningFailsWithNullFont_1180) {
    TextFontInfo* font = nullptr;
    bool result = textWord->addCombining(font, 12.0, 0.0, 0.0, 1.0, 1.0, 0, 1, 'a', 'a', Matrix());
    ASSERT_FALSE(result);  // Ensure that addCombining fails when font is null
}