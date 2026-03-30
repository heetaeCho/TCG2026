#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"  // Assuming this is the correct header file path for the TextWord class

// Test suite for the TextWord class
class TextWordTest_1193 : public ::testing::Test {
protected:
    // Test setup can go here if needed, such as initializing common resources for all tests
};

// Test case for checking the `getLink` function
TEST_F(TextWordTest_1193, GetLinkReturnsCorrectLink_1193) {
    // Setup
    AnnotLink expectedLink;
    TextWord word(nullptr, 0, 12.0);  // Assuming a constructor with default parameters
    // Set the link (simulate the internal behavior or assume external setting)
    // word.link = &expectedLink;  // For testing purposes, assume the link is set externally.

    // Call the method and check the result
    const AnnotLink* result = word.getLink();

    // Verify that the result is the expected link
    EXPECT_EQ(result, &expectedLink);
}

// Test case for checking the `getFontInfo` function with valid index
TEST_F(TextWordTest_1193, GetFontInfoReturnsCorrectFontInfo_1194) {
    // Setup
    TextFontInfo fontInfo;
    TextWord word(nullptr, 0, 12.0);
    
    // Simulate adding a font info to the word's collection (this would normally be done via addChar or similar)
    // Assuming a function or way to set the font info for testing.
    
    // Call the method and check the result
    const TextFontInfo* result = word.getFontInfo(0);

    // Verify the expected behavior (the specific content of fontInfo would depend on your implementation)
    EXPECT_EQ(result, &fontInfo);
}

// Test case for boundary condition (empty word, check if nextWord returns nullptr)
TEST_F(TextWordTest_1193, NextWordReturnsNullForEmptyWord_1195) {
    // Setup
    TextWord word(nullptr, 0, 12.0);

    // Call the method and check the result
    const TextWord* nextWord = word.nextWord();

    // Verify that the next word is nullptr (empty word case)
    EXPECT_EQ(nextWord, nullptr);
}

// Test case for boundary condition (word with a next word, check nextWord behavior)
TEST_F(TextWordTest_1193, NextWordReturnsCorrectWord_1196) {
    // Setup
    TextWord word1(nullptr, 0, 12.0);
    TextWord word2(nullptr, 0, 12.0);
    
    // Manually setting next word (simulate linking the words)
    // word1.next = &word2;

    // Call the method and check the result
    const TextWord* nextWord = word1.nextWord();

    // Verify that the next word is the correct one
    EXPECT_EQ(nextWord, &word2);
}

// Test case for boundary condition (getBBox on empty word)
TEST_F(TextWordTest_1193, GetBBoxReturnsCorrectBBoxForEmptyWord_1197) {
    // Setup
    TextWord word(nullptr, 0, 12.0);

    // Call the method and check the result
    double xMin, yMin, xMax, yMax;
    word.getBBox(&xMin, &yMin, &xMax, &yMax);

    // Verify expected values, assuming they default to 0 for an empty word
    EXPECT_DOUBLE_EQ(xMin, 0.0);
    EXPECT_DOUBLE_EQ(yMin, 0.0);
    EXPECT_DOUBLE_EQ(xMax, 0.0);
    EXPECT_DOUBLE_EQ(yMax, 0.0);
}

// Test case for exceptional case (invalid character index for getChar)
TEST_F(TextWordTest_1193, GetCharReturnsNullForInvalidIndex_1198) {
    // Setup
    TextWord word(nullptr, 0, 12.0);

    // Call the method with an invalid index
    const Unicode* result = word.getChar(-1);

    // Verify that the result is null (invalid index)
    EXPECT_EQ(result, nullptr);
}

// Test case for checking `getFontName` with an invalid index
TEST_F(TextWordTest_1193, GetFontNameReturnsNullForInvalidIndex_1199) {
    // Setup
    TextWord word(nullptr, 0, 12.0);

    // Call the method with an invalid index
    const GooString* result = word.getFontName(-1);

    // Verify that the result is null (invalid index)
    EXPECT_EQ(result, nullptr);
}

// Test case for boundary condition (testing spaceAfter)
TEST_F(TextWordTest_1193, SpaceAfterReturnsCorrectValue_1200) {
    // Setup
    TextWord word(nullptr, 0, 12.0);

    // Assuming spaceAfter is set during word creation or via an addChar call
    bool result = word.getSpaceAfter();

    // Verify the expected result (true or false depending on spaceAfter behavior)
    EXPECT_EQ(result, true);  // assuming spaceAfter is true for this test
}

// Test case for error condition (handling rotation edge case)
TEST_F(TextWordTest_1193, GetRotationReturnsCorrectValue_1201) {
    // Setup
    TextWord word(nullptr, 90, 12.0);  // Assuming a rotation of 90 degrees

    // Call the method and check the result
    int result = word.getRotation();

    // Verify that the rotation is as expected
    EXPECT_EQ(result, 90);
}