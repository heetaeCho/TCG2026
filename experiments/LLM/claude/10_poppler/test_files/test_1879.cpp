#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

// We need to declare the function under test since it's static in the source file.
// To test a static function, we include the source file directly or re-declare it.
// Since the function is static, we need to include the .cc file to access it.
// However, this is a common testing pattern for static functions.

// Forward declare the function signature - we'll include the source to get access
// to the static function. Since it's static, we need to either:
// 1. Include the .cc file
// 2. Or create a test wrapper

// For this test, we'll replicate the exact function signature and include the source.
// We use a workaround: define a test-accessible version by including the source.

// Since we can't directly call static functions from another translation unit,
// we include the implementation file.
#include "CharCodeToUnicode.cc"

class GetCharFromStringTest_1879 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: reading characters from a non-empty string
TEST_F(GetCharFromStringTest_1879, ReadsFirstCharacter_1879) {
    unsigned char str[] = "Hello";
    unsigned char *ptr = str;
    
    int c = getCharFromString(&ptr);
    
    EXPECT_EQ(c, 'H');
}

// Test that the pointer advances after reading a character
TEST_F(GetCharFromStringTest_1879, AdvancesPointerAfterRead_1879) {
    unsigned char str[] = "Hello";
    unsigned char *ptr = str;
    
    getCharFromString(&ptr);
    
    EXPECT_EQ(ptr, str + 1);
}

// Test reading multiple characters sequentially
TEST_F(GetCharFromStringTest_1879, ReadsMultipleCharactersSequentially_1879) {
    unsigned char str[] = "ABC";
    unsigned char *ptr = str;
    
    int c1 = getCharFromString(&ptr);
    int c2 = getCharFromString(&ptr);
    int c3 = getCharFromString(&ptr);
    
    EXPECT_EQ(c1, 'A');
    EXPECT_EQ(c2, 'B');
    EXPECT_EQ(c3, 'C');
}

// Test that reading past end of string returns EOF
TEST_F(GetCharFromStringTest_1879, ReturnsEOFAtEndOfString_1879) {
    unsigned char str[] = "A";
    unsigned char *ptr = str;
    
    getCharFromString(&ptr); // Read 'A'
    int c = getCharFromString(&ptr); // Should be EOF (null terminator)
    
    EXPECT_EQ(c, EOF);
}

// Test empty string returns EOF immediately
TEST_F(GetCharFromStringTest_1879, ReturnsEOFForEmptyString_1879) {
    unsigned char str[] = "";
    unsigned char *ptr = str;
    
    int c = getCharFromString(&ptr);
    
    EXPECT_EQ(c, EOF);
}

// Test that pointer does not advance when EOF is returned
TEST_F(GetCharFromStringTest_1879, PointerDoesNotAdvanceOnEOF_1879) {
    unsigned char str[] = "";
    unsigned char *ptr = str;
    unsigned char *original_ptr = ptr;
    
    getCharFromString(&ptr);
    
    // Pointer should remain pointing to the null terminator
    EXPECT_EQ(ptr, original_ptr);
}

// Test repeated EOF calls on empty string
TEST_F(GetCharFromStringTest_1879, RepeatedEOFCallsOnEmptyString_1879) {
    unsigned char str[] = "";
    unsigned char *ptr = str;
    
    int c1 = getCharFromString(&ptr);
    int c2 = getCharFromString(&ptr);
    int c3 = getCharFromString(&ptr);
    
    EXPECT_EQ(c1, EOF);
    EXPECT_EQ(c2, EOF);
    EXPECT_EQ(c3, EOF);
}

// Test single character string
TEST_F(GetCharFromStringTest_1879, SingleCharacterString_1879) {
    unsigned char str[] = "X";
    unsigned char *ptr = str;
    
    int c1 = getCharFromString(&ptr);
    int c2 = getCharFromString(&ptr);
    
    EXPECT_EQ(c1, 'X');
    EXPECT_EQ(c2, EOF);
}

// Test reading entire string and then getting EOF
TEST_F(GetCharFromStringTest_1879, ReadEntireStringThenEOF_1879) {
    unsigned char str[] = "Hi";
    unsigned char *ptr = str;
    
    EXPECT_EQ(getCharFromString(&ptr), 'H');
    EXPECT_EQ(getCharFromString(&ptr), 'i');
    EXPECT_EQ(getCharFromString(&ptr), EOF);
    EXPECT_EQ(getCharFromString(&ptr), EOF); // Still EOF
}

// Test with high-byte characters (values > 127)
TEST_F(GetCharFromStringTest_1879, HighByteCharacters_1879) {
    unsigned char str[] = { 0xFF, 0x80, 0x01, 0x00 };
    unsigned char *ptr = str;
    
    int c1 = getCharFromString(&ptr);
    int c2 = getCharFromString(&ptr);
    int c3 = getCharFromString(&ptr);
    int c4 = getCharFromString(&ptr);
    
    EXPECT_EQ(c1, 0xFF);
    EXPECT_EQ(c2, 0x80);
    EXPECT_EQ(c3, 0x01);
    EXPECT_EQ(c4, EOF);
}

// Test that the character value is returned as unsigned (not sign-extended)
TEST_F(GetCharFromStringTest_1879, ReturnsUnsignedCharValue_1879) {
    unsigned char str[] = { 0xFE, 0x00 };
    unsigned char *ptr = str;
    
    int c = getCharFromString(&ptr);
    
    EXPECT_EQ(c, 0xFE);
    EXPECT_GT(c, 0); // Should be positive, not sign-extended to negative
}

// Test with a longer string to verify sequential reads
TEST_F(GetCharFromStringTest_1879, LongerStringSequentialReads_1879) {
    unsigned char str[] = "Hello, World!";
    unsigned char *ptr = str;
    size_t len = strlen((char *)str);
    
    for (size_t i = 0; i < len; ++i) {
        int c = getCharFromString(&ptr);
        EXPECT_EQ(c, str[i]) << "Mismatch at index " << i;
    }
    
    // After reading all characters, should get EOF
    EXPECT_EQ(getCharFromString(&ptr), EOF);
}

// Test pointer advancement through entire string
TEST_F(GetCharFromStringTest_1879, PointerAdvancementThroughString_1879) {
    unsigned char str[] = "Test";
    unsigned char *ptr = str;
    
    for (int i = 0; i < 4; ++i) {
        getCharFromString(&ptr);
        EXPECT_EQ(ptr, str + i + 1) << "Pointer not at expected position after read " << (i + 1);
    }
}
