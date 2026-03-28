#include <gtest/gtest.h>
#include "TextOutputDev.h"

class TextWordTest_1197 : public ::testing::Test {
protected:
    // You can create helper methods here, if needed, for setup or mock initialization
    void SetUp() override {
        // Initialize necessary test data if any.
    }

    void TearDown() override {
        // Clean up after each test if needed.
    }
};

// Test normal operation for the nextWord function
TEST_F(TextWordTest_1197, NextWord_NormalOperation_1197) {
    // Assuming `TextWord` objects are created via the constructor
    TextWord word1(nullptr, 0, 12.0);  // Example constructor parameters
    TextWord word2(nullptr, 0, 12.0);
    word1.next = &word2;  // Link words

    // Test that nextWord correctly returns the next word.
    EXPECT_EQ(word1.nextWord(), &word2);
}

// Test boundary condition: nextWord is nullptr (end of list)
TEST_F(TextWordTest_1197, NextWord_Nullptr_1197) {
    TextWord word(nullptr, 0, 12.0);
    
    // Test that nextWord returns nullptr when there is no next word.
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test for exceptional behavior when accessing a nullptr in nextWord
TEST_F(TextWordTest_1197, NextWord_ExceptionalCase_1197) {
    TextWord word(nullptr, 0, 12.0);
    word.next = nullptr;  // Ensure no next word
    
    // Test that the next word is nullptr, simulating the end of the word list.
    EXPECT_EQ(word.nextWord(), nullptr);
}

// Test normal operation for getLength function
TEST_F(TextWordTest_1197, GetLength_NormalOperation_1197) {
    TextWord word(nullptr, 0, 12.0);
    // Suppose we set a length in the constructor or via some method
    int expectedLength = 5;  // Assuming length is 5 for this example
    
    // Test that the length of the word is as expected
    EXPECT_EQ(word.getLength(), expectedLength);
}

// Test boundary condition for getLength function with an empty word
TEST_F(TextWordTest_1197, GetLength_EmptyWord_1197) {
    TextWord word(nullptr, 0, 12.0);
    int expectedLength = 0;  // Empty word should have length 0
    
    // Test that the length is zero for an empty word
    EXPECT_EQ(word.getLength(), expectedLength);
}

// Test exceptional behavior for getLength function (uninitialized)
TEST_F(TextWordTest_1197, GetLength_Uninitialized_1197) {
    TextWord word(nullptr, 0, 12.0);
    
    // Assuming we test a case where the word was not properly initialized
    // This would require either mocking or assuming undefined behavior.
    // Since length is publicly accessible, we can check if it's an expected value.
    EXPECT_GT(word.getLength(), -1);  // Ensure length is a non-negative value
}

// Test getFontInfo for normal case
TEST_F(TextWordTest_1197, GetFontInfo_NormalOperation_1197) {
    TextWord word(nullptr, 0, 12.0);
    const TextFontInfo* fontInfo = word.getFontInfo(0);
    
    // Test that getFontInfo returns a non-null pointer (assuming a valid font is set)
    EXPECT_NE(fontInfo, nullptr);
}

// Test getFontInfo boundary condition with invalid index
TEST_F(TextWordTest_1197, GetFontInfo_InvalidIndex_1197) {
    TextWord word(nullptr, 0, 12.0);
    
    // Test that getFontInfo returns nullptr for invalid index
    EXPECT_EQ(word.getFontInfo(-1), nullptr);
    EXPECT_EQ(word.getFontInfo(9999), nullptr);
}

// Test getColor function for normal operation
TEST_F(TextWordTest_1197, GetColor_NormalOperation_1197) {
    TextWord word(nullptr, 0, 12.0);
    double r, g, b;
    
    word.getColor(&r, &g, &b);
    
    // Test that color values are within a valid range (0-1 for RGB)
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test getRotation function for normal case
TEST_F(TextWordTest_1197, GetRotation_NormalOperation_1197) {
    TextWord word(nullptr, 90, 12.0);  // Rotation set to 90 degrees
    
    // Test that the rotation value is as expected
    EXPECT_EQ(word.getRotation(), 90);
}

// Test getRotation boundary condition (no rotation)
TEST_F(TextWordTest_1197, GetRotation_NoRotation_1197) {
    TextWord word(nullptr, 0, 12.0);  // No rotation
    
    // Test that the rotation is 0 when no rotation is set
    EXPECT_EQ(word.getRotation(), 0);
}

// Test the exceptional case of trying to get a non-existent character
TEST_F(TextWordTest_1197, GetChar_ExceptionalCase_1197) {
    TextWord word(nullptr, 0, 12.0);
    
    // Test out-of-bounds access for getChar
    EXPECT_EQ(word.getChar(999), nullptr);
}

// Test nextWord chaining (verify external interaction)
TEST_F(TextWordTest_1197, NextWord_Chaining_1197) {
    TextWord word1(nullptr, 0, 12.0);
    TextWord word2(nullptr, 0, 12.0);
    word1.next = &word2;  // Link word1 to word2
    
    // Mock external behavior: verify that word1's next word is correctly linked
    const TextWord* next = word1.nextWord();
    EXPECT_EQ(next, &word2);
}