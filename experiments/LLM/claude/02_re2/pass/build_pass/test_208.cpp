#include <gtest/gtest.h>
#include "util/utf.h"

namespace re2 {

// Declaration of the function under test
int utflen(const char *s);

// Also need chartorune for setup verification
int chartorune(Rune *rune, const char *str);
int runetochar(char *str, const Rune *rune);

} // namespace re2

class UtfLenTest_208 : public ::testing::Test {
protected:
};

// Test empty string returns 0
TEST_F(UtfLenTest_208, EmptyStringReturnsZero_208) {
    EXPECT_EQ(0, re2::utflen(""));
}

// Test single ASCII character
TEST_F(UtfLenTest_208, SingleAsciiCharacter_208) {
    EXPECT_EQ(1, re2::utflen("a"));
}

// Test multiple ASCII characters
TEST_F(UtfLenTest_208, MultipleAsciiCharacters_208) {
    EXPECT_EQ(5, re2::utflen("hello"));
}

// Test single-byte boundary: all characters below 128
TEST_F(UtfLenTest_208, AllAsciiCharacters_208) {
    EXPECT_EQ(26, re2::utflen("abcdefghijklmnopqrstuvwxyz"));
}

// Test string with spaces and punctuation (ASCII)
TEST_F(UtfLenTest_208, AsciiWithSpacesAndPunctuation_208) {
    EXPECT_EQ(13, re2::utflen("Hello, World!"));
}

// Test two-byte UTF-8 characters (e.g., Latin characters with accents)
TEST_F(UtfLenTest_208, TwoByteUtf8Characters_208) {
    // é is U+00E9, encoded as 0xC3 0xA9 in UTF-8
    const char s[] = {(char)0xC3, (char)0xA9, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test multiple two-byte UTF-8 characters
TEST_F(UtfLenTest_208, MultipleTwoByteUtf8Characters_208) {
    // "éàü" - three 2-byte characters
    const char s[] = {(char)0xC3, (char)0xA9, (char)0xC3, (char)0xA0, (char)0xC3, (char)0xBC, 0};
    EXPECT_EQ(3, re2::utflen(s));
}

// Test three-byte UTF-8 characters (e.g., CJK characters)
TEST_F(UtfLenTest_208, ThreeByteUtf8Characters_208) {
    // 中 is U+4E2D, encoded as 0xE4 0xB8 0xAD
    const char s[] = {(char)0xE4, (char)0xB8, (char)0xAD, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test four-byte UTF-8 characters (e.g., emoji)
TEST_F(UtfLenTest_208, FourByteUtf8Characters_208) {
    // U+1F600 (😀) encoded as 0xF0 0x9F 0x98 0x80
    const char s[] = {(char)0xF0, (char)0x9F, (char)0x98, (char)0x80, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test mixed ASCII and multi-byte UTF-8
TEST_F(UtfLenTest_208, MixedAsciiAndMultiByte_208) {
    // "aé" - 1 ASCII + 1 two-byte
    const char s[] = {'a', (char)0xC3, (char)0xA9, 0};
    EXPECT_EQ(2, re2::utflen(s));
}

// Test mixed ASCII and three-byte UTF-8
TEST_F(UtfLenTest_208, MixedAsciiAndThreeByte_208) {
    // "a中b" - ASCII + 3-byte + ASCII
    const char s[] = {'a', (char)0xE4, (char)0xB8, (char)0xAD, 'b', 0};
    EXPECT_EQ(3, re2::utflen(s));
}

// Test string with only one character at ASCII boundary (DEL, 0x7F)
TEST_F(UtfLenTest_208, AsciiBoundaryChar127_208) {
    const char s[] = {0x7F, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test single character at value 1 (SOH)
TEST_F(UtfLenTest_208, SingleCharValue1_208) {
    const char s[] = {0x01, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test longer ASCII string
TEST_F(UtfLenTest_208, LongerAsciiString_208) {
    EXPECT_EQ(100, re2::utflen(
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"));
}

// Test multiple four-byte UTF-8 characters
TEST_F(UtfLenTest_208, MultipleFourByteCharacters_208) {
    // Two U+1F600 characters
    const char s[] = {
        (char)0xF0, (char)0x9F, (char)0x98, (char)0x80,
        (char)0xF0, (char)0x9F, (char)0x98, (char)0x80,
        0
    };
    EXPECT_EQ(2, re2::utflen(s));
}

// Test using runetochar to build a string and verify with utflen
TEST_F(UtfLenTest_208, BuiltFromRuneToChar_208) {
    char buf[20] = {};
    re2::Rune runes[] = {0x41, 0xE9, 0x4E2D, 0x1F600}; // A, é, 中, 😀
    int pos = 0;
    for (int i = 0; i < 4; i++) {
        pos += re2::runetochar(buf + pos, &runes[i]);
    }
    buf[pos] = 0;
    EXPECT_EQ(4, re2::utflen(buf));
}

// Test string consisting only of 2-byte boundary character (U+0080)
TEST_F(UtfLenTest_208, TwoByteBoundaryU0080_208) {
    // U+0080 encoded as 0xC2 0x80
    const char s[] = {(char)0xC2, (char)0x80, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test string consisting of three-byte boundary character (U+0800)
TEST_F(UtfLenTest_208, ThreeByteBoundaryU0800_208) {
    // U+0800 encoded as 0xE0 0xA0 0x80
    const char s[] = {(char)0xE0, (char)0xA0, (char)0x80, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test string consisting of four-byte boundary character (U+10000)
TEST_F(UtfLenTest_208, FourByteBoundaryU10000_208) {
    // U+10000 encoded as 0xF0 0x90 0x80 0x80
    const char s[] = {(char)0xF0, (char)0x90, (char)0x80, (char)0x80, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test invalid UTF-8 sequence (lone continuation byte)
TEST_F(UtfLenTest_208, InvalidLoneContinuationByte_208) {
    // 0x80 is a lone continuation byte - should be treated as one rune (Runeerror)
    const char s[] = {(char)0x80, 0};
    EXPECT_EQ(1, re2::utflen(s));
}

// Test invalid UTF-8: overlong 2-byte sequence
TEST_F(UtfLenTest_208, InvalidOverlong2Byte_208) {
    // 0xC0 0x80 is an overlong encoding of U+0000
    const char s[] = {(char)0xC0, (char)0x80, 0};
    // Should count as some number of runes (implementation dependent, but at least 1)
    EXPECT_GE(re2::utflen(s), 1);
}

// Test mix of valid and invalid bytes
TEST_F(UtfLenTest_208, MixedValidAndInvalidBytes_208) {
    // 'a' followed by lone continuation byte 0x80 followed by 'b'
    const char s[] = {'a', (char)0x80, 'b', 0};
    EXPECT_EQ(3, re2::utflen(s));
}

// Test all digits
TEST_F(UtfLenTest_208, AllDigits_208) {
    EXPECT_EQ(10, re2::utflen("0123456789"));
}

// Test single space
TEST_F(UtfLenTest_208, SingleSpace_208) {
    EXPECT_EQ(1, re2::utflen(" "));
}
