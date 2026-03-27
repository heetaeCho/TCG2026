#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Test Fixture for TextWord class
class TextWordTest_1185 : public ::testing::Test {
protected:
    // Sample constructor and member setup
    TextWord *textWord;

    void SetUp() override {
        // Initialize a TextWord object with mock values
        const GfxState* state = nullptr;  // Mocked GfxState pointer
        int rot = 0;
        double fontSize = 12.0;
        textWord = new TextWord(state, rot, fontSize);
    }

    void TearDown() override {
        // Clean up after each test
        delete textWord;
    }
};

// Test normal operation of getBBox function
TEST_F(TextWordTest_1185, GetBBox_NormalOperation_1185) {
    double xMin, yMin, xMax, yMax;
    textWord->getBBox(&xMin, &yMin, &xMax, &yMax);

    // Check if the bounding box values are set correctly
    EXPECT_EQ(xMin, 0);
    EXPECT_EQ(yMin, 0);
    EXPECT_EQ(xMax, 0);
    EXPECT_EQ(yMax, 0);
}

// Test normal operation of getFontSize function
TEST_F(TextWordTest_1185, GetFontSize_NormalOperation_1185) {
    double fontSize = textWord->getFontSize();
    EXPECT_EQ(fontSize, 12.0);
}

// Test normal operation of getRotation function
TEST_F(TextWordTest_1185, GetRotation_NormalOperation_1185) {
    int rotation = textWord->getRotation();
    EXPECT_EQ(rotation, 0);
}

// Test boundary case for getCharIdx function
TEST_F(TextWordTest_1185, GetCharBBox_BoundaryCase_1185) {
    double xMin, yMin, xMax, yMax;
    int charIdx = 0;  // Boundary index, assuming 0 is valid here
    textWord->getCharBBox(charIdx, &xMin, &yMin, &xMax, &yMax);

    // Check if bounding box is returned correctly for first character
    EXPECT_EQ(xMin, 0);
    EXPECT_EQ(yMin, 0);
    EXPECT_EQ(xMax, 0);
    EXPECT_EQ(yMax, 0);
}

// Test exceptional case for getCharBBox function with invalid charIdx
TEST_F(TextWordTest_1185, GetCharBBox_ExceptionalCase_1185) {
    double xMin, yMin, xMax, yMax;
    int invalidCharIdx = -1;  // Invalid character index

    EXPECT_THROW(textWord->getCharBBox(invalidCharIdx, &xMin, &yMin, &xMax, &yMax), std::out_of_range);
}

// Test if getNext returns the correct next word (boundary case with no next word)
TEST_F(TextWordTest_1185, GetNextWord_NoNext_1185) {
    const TextWord* nextWord = textWord->getNext();
    EXPECT_EQ(nextWord, nullptr);  // Expecting no next word
}

// Test interaction with external dependencies like getLink
TEST_F(TextWordTest_1185, GetLink_NormalOperation_1185) {
    const AnnotLink* link = textWord->getLink();
    EXPECT_EQ(link, nullptr);  // Assuming link is null initially
}

// Test normal operation of getColor function
TEST_F(TextWordTest_1185, GetColor_NormalOperation_1185) {
    double r, g, b;
    textWord->getColor(&r, &g, &b);

    // Check if color values are correctly set
    EXPECT_EQ(r, 0);
    EXPECT_EQ(g, 0);
    EXPECT_EQ(b, 0);
}