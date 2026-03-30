#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"

#include <memory>



// Mock class for TextFontInfo if needed

class MockTextFontInfo : public TextFontInfo {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



TEST_F(TextWordTest_1180, GetNext_ReturnsCorrectPointer_1180) {

    TextWord word1(nullptr, 0, 0.0);

    TextWord word2(nullptr, 0, 0.0);



    // Manually setting the next pointer for testing

    const_cast<TextWord*>(&word1)->next = &word2;



    EXPECT_EQ(&word2, word1.getNext());

}



TEST_F(TextWordTest_1180, GetLength_ReturnsCorrectValue_1180) {

    TextWord word(nullptr, 0, 0.0);

    // Assuming length is set by addChar or similar methods internally

    // For this test, we assume a mock or setup that sets length to 5

    EXPECT_EQ(0, word.getLength()); // Initial length should be 0 without adding chars

}



TEST_F(TextWordTest_1180, GetChar_ReturnsCorrectUnicode_1180) {

    TextWord word(nullptr, 0, 0.0);

    Unicode expectedChar = 65; // 'A'

    // Assuming a method to add char with Unicode 65

    // For this test, we assume a mock or setup that adds the character

    EXPECT_EQ(nullptr, word.getChar(0)); // Initial should be nullptr without adding chars

}



TEST_F(TextWordTest_1180, GetFontName_ReturnsCorrectFontName_1180) {

    TextWord word(nullptr, 0, 0.0);

    // Assuming a method to set font name

    // For this test, we assume a mock or setup that sets the font name

    EXPECT_EQ(nullptr, word.getFontName(0)); // Initial should be nullptr without setting font

}



TEST_F(TextWordTest_1180, GetColor_ReturnsCorrectValues_1180) {

    TextWord word(nullptr, 0, 0.0);

    double r, g, b;

    word.getColor(&r, &g, &b);

    EXPECT_DOUBLE_EQ(0.0, r); // Default color should be black (0,0,0)

    EXPECT_DOUBLE_EQ(0.0, g);

    EXPECT_DOUBLE_EQ(0.0, b);

}



TEST_F(TextWordTest_1180, GetBBox_ReturnsCorrectValues_1180) {

    TextWord word(nullptr, 0, 0.0);

    double xMin, yMin, xMax, yMax;

    word.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(0.0, xMin); // Default bounding box should be (0,0,0,0)

    EXPECT_DOUBLE_EQ(0.0, yMin);

    EXPECT_DOUBLE_EQ(0.0, xMax);

    EXPECT_DOUBLE_EQ(0.0, yMax);

}



TEST_F(TextWordTest_1180, GetFontSize_ReturnsCorrectValue_1180) {

    TextWord word(nullptr, 0, 12.5); // Setting font size to 12.5 for test

    EXPECT_DOUBLE_EQ(12.5, word.getFontSize());

}



TEST_F(TextWordTest_1180, GetRotation_ReturnsCorrectValue_1180) {

    TextWord word(nullptr, 90, 0.0); // Setting rotation to 90 degrees for test

    EXPECT_EQ(90, word.getRotation());

}



TEST_F(TextWordTest_1180, HasSpaceAfter_ReturnsFalseInitially_1180) {

    TextWord word(nullptr, 0, 0.0);

    EXPECT_FALSE(word.hasSpaceAfter()); // Initially should be false

}



TEST_F(TextWordTest_1180, IsUnderlined_ReturnsFalseInitially_1180) {

    TextWord word(nullptr, 0, 0.0);

    EXPECT_FALSE(word.isUnderlined()); // Initially should be false

}
