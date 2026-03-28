#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
namespace re2 {
char* utfrune(const char* s, int c);
}

using re2::utfrune;

// Test finding an ASCII character in a pure ASCII string
TEST(UtfruneTest_209, FindAsciiCharInAsciiString_209) {
    const char* s = "hello world";
    char* result = utfrune(s, 'w');
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 6);
}

// Test finding the first character of the string
TEST(UtfruneTest_209, FindFirstCharacter_209) {
    const char* s = "abcdef";
    char* result = utfrune(s, 'a');
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s);
}

// Test finding the last character of the string
TEST(UtfruneTest_209, FindLastCharacter_209) {
    const char* s = "abcdef";
    char* result = utfrune(s, 'f');
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 5);
}

// Test character not found in ASCII string
TEST(UtfruneTest_209, AsciiCharNotFound_209) {
    const char* s = "hello";
    char* result = utfrune(s, 'z');
    EXPECT_EQ(result, nullptr);
}

// Test empty string returns null
TEST(UtfruneTest_209, EmptyStringReturnsNull_209) {
    const char* s = "";
    char* result = utfrune(s, 'a');
    EXPECT_EQ(result, nullptr);
}

// Test finding null character (c == 0) in ASCII range — strchr behavior
TEST(UtfruneTest_209, FindNullCharacterAscii_209) {
    const char* s = "hello";
    char* result = utfrune(s, '\0');
    ASSERT_NE(result, nullptr);
    // strchr with '\0' returns pointer to the null terminator
    EXPECT_EQ(*result, '\0');
    EXPECT_EQ(result, s + 5);
}

// Test finding a multi-byte UTF-8 character (2-byte: e.g., U+00E9, é)
TEST(UtfruneTest_209, FindTwoByteUtf8Char_209) {
    // U+00E9 is 'é', encoded as 0xC3 0xA9
    const char* s = "caf\xC3\xA9";
    int rune = 0x00E9; // é
    char* result = utfrune(s, rune);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 3);
}

// Test finding a 3-byte UTF-8 character (e.g., U+4E16, 世)
TEST(UtfruneTest_209, FindThreeByteUtf8Char_209) {
    // U+4E16 is '世', encoded as 0xE4 0xB8 0x96
    const char* s = "hello\xE4\xB8\x96world";
    int rune = 0x4E16;
    char* result = utfrune(s, rune);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 5);
}

// Test multi-byte character not found
TEST(UtfruneTest_209, MultiByteCharNotFound_209) {
    const char* s = "hello world";
    int rune = 0x4E16; // 世
    char* result = utfrune(s, rune);
    EXPECT_EQ(result, nullptr);
}

// Test finding a 4-byte UTF-8 character (e.g., U+1F600, 😀)
TEST(UtfruneTest_209, FindFourByteUtf8Char_209) {
    // U+1F600 encoded as 0xF0 0x9F 0x98 0x80
    const char* s = "hi\xF0\x9F\x98\x80there";
    int rune = 0x1F600;
    char* result = utfrune(s, rune);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 2);
}

// Test finding first occurrence when character appears multiple times
TEST(UtfruneTest_209, FindFirstOccurrenceOfDuplicate_209) {
    const char* s = "abcabc";
    char* result = utfrune(s, 'b');
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 1);
}

// Test string with mixed ASCII and multi-byte characters, searching for ASCII
TEST(UtfruneTest_209, FindAsciiInMixedString_209) {
    // "a世b" — search for 'b'
    const char* s = "a\xE4\xB8\x96" "b";
    char* result = utfrune(s, 'b');
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, 'b');
}

// Test searching for Runesync boundary value (128)
TEST(UtfruneTest_209, FindRuneSyncBoundary_209) {
    // U+0080 is encoded as 0xC2 0x80
    const char* s = "abc\xC2\x80" "def";
    int rune = 128; // Runesync
    char* result = utfrune(s, rune);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 3);
}

// Test searching for value just below Runesync (127, DEL)
TEST(UtfruneTest_209, FindBelowRuneSync_209) {
    // 127 is DEL character, single byte, below Runesync
    char buf[] = {'a', 'b', 127, 'c', '\0'};
    char* result = utfrune(buf, 127);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, buf + 2);
}

// Test with a string that is purely multi-byte UTF-8 characters
TEST(UtfruneTest_209, PureMultiByteStringSearch_209) {
    // "世界" = U+4E16 U+754C
    // U+4E16: 0xE4 0xB8 0x96
    // U+754C: 0xE7 0x95 0x8C
    const char* s = "\xE4\xB8\x96\xE7\x95\x8C";
    int rune = 0x754C; // 界
    char* result = utfrune(s, rune);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 3);
}

// Test with single character string
TEST(UtfruneTest_209, SingleCharStringFound_209) {
    const char* s = "x";
    char* result = utfrune(s, 'x');
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s);
}

// Test with single character string not found
TEST(UtfruneTest_209, SingleCharStringNotFound_209) {
    const char* s = "x";
    char* result = utfrune(s, 'y');
    EXPECT_EQ(result, nullptr);
}

// Test Runemax boundary
TEST(UtfruneTest_209, SearchForRunemax_209) {
    // Runemax = 0x10FFFF, encoded as F4 8F BF BF
    const char* s = "\xF4\x8F\xBF\xBF";
    int rune = 0x10FFFF;
    char* result = utfrune(s, rune);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s);
}

// Test that first occurrence of a multi-byte character is returned
TEST(UtfruneTest_209, FirstOccurrenceMultiByte_209) {
    // Two occurrences of U+00E9 (é)
    const char* s = "\xC3\xA9" "abc" "\xC3\xA9";
    int rune = 0x00E9;
    char* result = utfrune(s, rune);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s); // Should return the first occurrence
}
