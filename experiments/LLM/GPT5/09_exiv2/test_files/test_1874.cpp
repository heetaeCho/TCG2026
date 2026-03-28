#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <cstring>

// Mock for external dependencies if needed (assuming `CodePoint_from_UTF8` is an external function)
extern "C" {
    void CodePoint_from_UTF8(const unsigned char *utf8Str, size_t maxLength, unsigned int *cp, size_t *u8Len);
}

// The following is based on the provided code snippet.
#define BanAllEntityUsage 0

static inline XMP_Uns32 GetCodePoint(const XMP_Uns8 **utf8Str_io) {
    const XMP_Uns8 *u8Ptr = *utf8Str_io;
    XMP_Uns32 cp;
    size_t u8Len;
    CodePoint_from_UTF8(u8Ptr, 4, &cp, &u8Len);  // Throws exception on error.
    *utf8Str_io = u8Ptr + u8Len;
    return cp;
}

class GetCodePointTest : public ::testing::Test {
protected:
    // Test setup, teardown can be added here if needed
};

TEST_F(GetCodePointTest, GetCodePoint_NormalCase_1874) {
    const unsigned char input[] = {0xE2, 0x82, 0xAC, 0}; // UTF-8 for €
    const unsigned char *utf8Ptr = input;

    // Mocked behavior of CodePoint_from_UTF8 (assuming it processes UTF-8 properly)
    XMP_Uns32 result = GetCodePoint(&utf8Ptr);

    // The € character is U+20AC in Unicode
    EXPECT_EQ(result, 0x20AC);
    EXPECT_EQ(utf8Ptr, input + 3);  // 3 bytes processed for this character
}

TEST_F(GetCodePointTest, GetCodePoint_EmptyString_1875) {
    const unsigned char input[] = {0}; // Empty string (null byte)
    const unsigned char *utf8Ptr = input;

    EXPECT_THROW(GetCodePoint(&utf8Ptr), std::invalid_argument);
}

TEST_F(GetCodePointTest, GetCodePoint_InvalidUTF8_1876) {
    const unsigned char input[] = {0x80, 0}; // Invalid UTF-8 byte sequence
    const unsigned char *utf8Ptr = input;

    EXPECT_THROW(GetCodePoint(&utf8Ptr), std::invalid_argument);
}

TEST_F(GetCodePointTest, GetCodePoint_OneByteCharacter_1877) {
    const unsigned char input[] = {0x41, 0}; // ASCII 'A'
    const unsigned char *utf8Ptr = input;

    // 'A' is U+0041
    XMP_Uns32 result = GetCodePoint(&utf8Ptr);
    EXPECT_EQ(result, 0x0041);
    EXPECT_EQ(utf8Ptr, input + 1); // 1 byte processed for this character
}

TEST_F(GetCodePointTest, GetCodePoint_MultiByteCharacter_1878) {
    const unsigned char input[] = {0xF0, 0x9F, 0x92, 0x96, 0}; // UTF-8 for 💖
    const unsigned char *utf8Ptr = input;

    XMP_Uns32 result = GetCodePoint(&utf8Ptr);

    // 💖 character is U+1F496
    EXPECT_EQ(result, 0x1F496);
    EXPECT_EQ(utf8Ptr, input + 4);  // 4 bytes processed for this character
}

TEST_F(GetCodePointTest, GetCodePoint_SingleByteBoundary_1879) {
    const unsigned char input[] = {0x7F, 0}; // ASCII boundary character
    const unsigned char *utf8Ptr = input;

    XMP_Uns32 result = GetCodePoint(&utf8Ptr);

    // 0x7F is a valid single byte character in ASCII
    EXPECT_EQ(result, 0x7F);
    EXPECT_EQ(utf8Ptr, input + 1);  // 1 byte processed
}

TEST_F(GetCodePointTest, GetCodePoint_TwoByteCharacter_1880) {
    const unsigned char input[] = {0xC2, 0xA9, 0}; // UTF-8 for ©
    const unsigned char *utf8Ptr = input;

    XMP_Uns32 result = GetCodePoint(&utf8Ptr);

    // © is U+00A9
    EXPECT_EQ(result, 0x00A9);
    EXPECT_EQ(utf8Ptr, input + 2);  // 2 bytes processed for this character
}

TEST_F(GetCodePointTest, GetCodePoint_MoreThanFourBytes_1881) {
    const unsigned char input[] = {0xF4, 0x8F, 0xBF, 0xBF, 0}; // UTF-8 for a character beyond U+10FFFF
    const unsigned char *utf8Ptr = input;

    EXPECT_THROW(GetCodePoint(&utf8Ptr), std::invalid_argument);  // Exception should be thrown for illegal character
}