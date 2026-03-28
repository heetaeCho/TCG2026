#include <gtest/gtest.h>

// The TEST_ID is 1877

// Forward declaration of the function under test
static inline bool IsOtherChar_ASCII(XMP_Uns32 cp);

class UnicodeInlinesTest_1877 : public ::testing::Test {
protected:
    // Setup code (if any) goes here
    void SetUp() override {
        // Code to setup the environment for each test case can be added here
    }

    // Teardown code (if any) goes here
    void TearDown() override {
        // Code to cleanup the environment after each test case can be added here
    }
};

// Test case for normal operation (ASCII digits and symbols)
TEST_F(UnicodeInlinesTest_1877, IsOtherChar_ASCII_ValidDigitsAndSymbols_1877) {
    // Test for digits
    EXPECT_TRUE(IsOtherChar_ASCII('0'));  // ASCII '0'
    EXPECT_TRUE(IsOtherChar_ASCII('9'));  // ASCII '9'
    
    // Test for special characters
    EXPECT_TRUE(IsOtherChar_ASCII('-'));  // ASCII '-'
    EXPECT_TRUE(IsOtherChar_ASCII('.'));  // ASCII '.'
    
    // Test for other characters (non-ASCII)
    EXPECT_FALSE(IsOtherChar_ASCII('A'));  // ASCII 'A' (should not match)
    EXPECT_FALSE(IsOtherChar_ASCII('z'));  // ASCII 'z' (should not match)
}

// Test case for boundary conditions (testing limits of valid characters)
TEST_F(UnicodeInlinesTest_1877, IsOtherChar_ASCII_BoundaryConditions_1877) {
    // Test for valid ASCII digits
    EXPECT_TRUE(IsOtherChar_ASCII('0'));
    EXPECT_TRUE(IsOtherChar_ASCII('9'));

    // Test for boundary between digits and letters
    EXPECT_FALSE(IsOtherChar_ASCII('A'));  // After 9, 'A' should not match
    EXPECT_FALSE(IsOtherChar_ASCII('Z'));  // Uppercase letters should not match
    EXPECT_FALSE(IsOtherChar_ASCII('a'));  // Lowercase letters should not match
}

// Test case for exceptional or error cases (invalid or out-of-range code points)
TEST_F(UnicodeInlinesTest_1877, IsOtherChar_ASCII_InvalidCodePoints_1877) {
    // Test for a negative code point (invalid in Unicode context)
    EXPECT_FALSE(IsOtherChar_ASCII(-1));  // Negative value

    // Test for a large code point (out of expected range)
    EXPECT_FALSE(IsOtherChar_ASCII(0x10FFFF));  // Invalid Unicode code point (beyond valid range)
}

// Test case for verification of external interactions (mock handler calls, if relevant)
TEST_F(UnicodeInlinesTest_1877, IsOtherChar_ASCII_VerifyHandlerCalls_1877) {
    // In this case, there are no external interactions (e.g., callbacks) to mock,
    // so this test case may not apply directly.
    // If interactions are needed, you'd use Google Mock to mock the required behavior.
}

// Test case for other characters not in the valid ASCII set
TEST_F(UnicodeInlinesTest_1877, IsOtherChar_ASCII_InvalidChars_1877) {
    EXPECT_FALSE(IsOtherChar_ASCII('A'));  // Letters are not valid
    EXPECT_FALSE(IsOtherChar_ASCII('$'));  // Symbols are not valid
    EXPECT_FALSE(IsOtherChar_ASCII('@'));  // Special characters are not valid
}