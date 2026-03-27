#include <gtest/gtest.h>

#define TEST_ID 1875

// Mocking external dependencies (if needed)
// Assuming that there are no external dependencies in the partial code provided

// The function under test
static inline bool IsStartChar_ASCII(XMP_Uns32 cp) {
    if ( (('a' <= cp) && (cp <= 'z')) || (('A' <= cp) && (cp <= 'Z')) || (cp == '_') )
        return true;
    return false;
}

// Test suite for the IsStartChar_ASCII function
TEST_F(UnicodeInlinesTest_1875, IsStartChar_ASCII_ValidLowercase_Character_1875) {
    // Test for lowercase alphabet
    XMP_Uns32 cp = 'a';
    EXPECT_TRUE(IsStartChar_ASCII(cp));

    cp = 'z';
    EXPECT_TRUE(IsStartChar_ASCII(cp));
}

TEST_F(UnicodeInlinesTest_1875, IsStartChar_ASCII_ValidUppercase_Character_1875) {
    // Test for uppercase alphabet
    XMP_Uns32 cp = 'A';
    EXPECT_TRUE(IsStartChar_ASCII(cp));

    cp = 'Z';
    EXPECT_TRUE(IsStartChar_ASCII(cp));
}

TEST_F(UnicodeInlinesTest_1875, IsStartChar_ASCII_UnderScore_Character_1875) {
    // Test for underscore character
    XMP_Uns32 cp = '_';
    EXPECT_TRUE(IsStartChar_ASCII(cp));
}

TEST_F(UnicodeInlinesTest_1875, IsStartChar_ASCII_InvalidCharacter_1875) {
    // Test for invalid character
    XMP_Uns32 cp = '1';
    EXPECT_FALSE(IsStartChar_ASCII(cp));

    cp = '@';
    EXPECT_FALSE(IsStartChar_ASCII(cp));
}

TEST_F(UnicodeInlinesTest_1875, IsStartChar_ASCII_EmptyCharacter_1875) {
    // Test for edge case of empty character (NULL, 0)
    XMP_Uns32 cp = 0;
    EXPECT_FALSE(IsStartChar_ASCII(cp));
}