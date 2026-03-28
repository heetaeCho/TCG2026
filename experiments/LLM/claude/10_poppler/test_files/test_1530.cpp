#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

// Declaration of the function under test
std::string utf16ToUtf8(const uint16_t *utf16, int maxUtf16);

class Utf16ToUtf8Test_1530 : public ::testing::Test {
protected:
};

// Test empty string (null terminator at start)
TEST_F(Utf16ToUtf8Test_1530, EmptyString_1530) {
    uint16_t input[] = {0};
    std::string result = utf16ToUtf8(input, 10);
    EXPECT_EQ(result, "");
}

// Test simple ASCII characters
TEST_F(Utf16ToUtf8Test_1530, SimpleAscii_1530) {
    // "Hello" in UTF-16
    uint16_t input[] = {'H', 'e', 'l', 'l', 'o', 0};
    std::string result = utf16ToUtf8(input, 5);
    EXPECT_EQ(result, "Hello");
}

// Test single ASCII character
TEST_F(Utf16ToUtf8Test_1530, SingleAsciiChar_1530) {
    uint16_t input[] = {'A', 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "A");
}

// Test maxUtf16 limits the number of characters processed
TEST_F(Utf16ToUtf8Test_1530, MaxUtf16LimitsProcessing_1530) {
    uint16_t input[] = {'H', 'e', 'l', 'l', 'o', 0};
    std::string result = utf16ToUtf8(input, 3);
    EXPECT_EQ(result, "Hel");
}

// Test maxUtf16 of zero
TEST_F(Utf16ToUtf8Test_1530, MaxUtf16Zero_1530) {
    uint16_t input[] = {'H', 'e', 'l', 'l', 'o', 0};
    std::string result = utf16ToUtf8(input, 0);
    EXPECT_EQ(result, "");
}

// Test two-byte UTF-8 characters (BMP characters like Latin Extended)
TEST_F(Utf16ToUtf8Test_1530, TwoByteUtf8Chars_1530) {
    // U+00E9 = é (Latin small letter e with acute)
    uint16_t input[] = {0x00E9, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xC3\xA9");
}

// Test three-byte UTF-8 characters (BMP characters)
TEST_F(Utf16ToUtf8Test_1530, ThreeByteUtf8Chars_1530) {
    // U+4E16 = 世 (CJK character)
    uint16_t input[] = {0x4E16, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xE4\xB8\x96");
}

// Test surrogate pairs (characters beyond BMP, four-byte UTF-8)
TEST_F(Utf16ToUtf8Test_1530, SurrogatePair_1530) {
    // U+1F600 (😀) = D83D DE00 in UTF-16 surrogate pair
    uint16_t input[] = {0xD83D, 0xDE00, 0};
    std::string result = utf16ToUtf8(input, 2);
    EXPECT_EQ(result, "\xF0\x9F\x98\x80");
}

// Test multiple surrogate pairs
TEST_F(Utf16ToUtf8Test_1530, MultipleSurrogatePairs_1530) {
    // U+1F600 (😀) and U+1F601 (😁)
    uint16_t input[] = {0xD83D, 0xDE00, 0xD83D, 0xDE01, 0};
    std::string result = utf16ToUtf8(input, 4);
    EXPECT_EQ(result, "\xF0\x9F\x98\x80\xF0\x9F\x98\x81");
}

// Test mixed ASCII and non-ASCII
TEST_F(Utf16ToUtf8Test_1530, MixedAsciiAndNonAscii_1530) {
    // "Aé" = A (0x41), é (0x00E9)
    uint16_t input[] = {0x0041, 0x00E9, 0};
    std::string result = utf16ToUtf8(input, 2);
    EXPECT_EQ(result, "A\xC3\xA9");
}

// Test lone high surrogate (incomplete pair) - should produce replacement char
TEST_F(Utf16ToUtf8Test_1530, LoneHighSurrogate_1530) {
    // High surrogate 0xD800 followed by non-surrogate
    uint16_t input[] = {0xD800, 0x0041, 0};
    std::string result = utf16ToUtf8(input, 2);
    // The lone high surrogate should result in a replacement character
    // followed by 'A'
    // Replacement char U+FFFD = EF BF BD in UTF-8
    EXPECT_FALSE(result.empty());
}

// Test lone high surrogate at end of string
TEST_F(Utf16ToUtf8Test_1530, LoneHighSurrogateAtEnd_1530) {
    uint16_t input[] = {0xD800, 0};
    std::string result = utf16ToUtf8(input, 1);
    // Should produce replacement character
    // U+FFFD = EF BF BD
    EXPECT_EQ(result, "\xEF\xBF\xBD");
}

// Test lone low surrogate (should be rejected)
TEST_F(Utf16ToUtf8Test_1530, LoneLowSurrogate_1530) {
    uint16_t input[] = {0xDC00, 0};
    std::string result = utf16ToUtf8(input, 1);
    // Should produce replacement character
    EXPECT_EQ(result, "\xEF\xBF\xBD");
}

// Test null character in the middle terminates processing
TEST_F(Utf16ToUtf8Test_1530, NullTerminatesEarly_1530) {
    uint16_t input[] = {'H', 0, 'l', 'l', 'o'};
    std::string result = utf16ToUtf8(input, 5);
    EXPECT_EQ(result, "H");
}

// Test U+0080 boundary (start of two-byte UTF-8)
TEST_F(Utf16ToUtf8Test_1530, BoundaryU0080_1530) {
    uint16_t input[] = {0x0080, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xC2\x80");
}

// Test U+07FF boundary (end of two-byte UTF-8)
TEST_F(Utf16ToUtf8Test_1530, BoundaryU07FF_1530) {
    uint16_t input[] = {0x07FF, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xDF\xBF");
}

// Test U+0800 boundary (start of three-byte UTF-8)
TEST_F(Utf16ToUtf8Test_1530, BoundaryU0800_1530) {
    uint16_t input[] = {0x0800, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xE0\xA0\x80");
}

// Test U+FFFF (last BMP character, excluding surrogates)
TEST_F(Utf16ToUtf8Test_1530, BoundaryUFFFF_1530) {
    uint16_t input[] = {0xFFFF, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xEF\xBF\xBF");
}

// Test U+FFFE (non-character but still valid codepoint)
TEST_F(Utf16ToUtf8Test_1530, NonCharacterUFFFE_1530) {
    uint16_t input[] = {0xFFFE, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xEF\xBF\xBE");
}

// Test replacement character itself U+FFFD
TEST_F(Utf16ToUtf8Test_1530, ReplacementCharInput_1530) {
    uint16_t input[] = {0xFFFD, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\xEF\xBF\xBD");
}

// Test surrogate pair at max codepoint U+10FFFF
TEST_F(Utf16ToUtf8Test_1530, MaxCodepointSurrogatePair_1530) {
    // U+10FFFF = DBFF DFFF in UTF-16
    uint16_t input[] = {0xDBFF, 0xDFFF, 0};
    std::string result = utf16ToUtf8(input, 2);
    EXPECT_EQ(result, "\xF4\x8F\xBF\xBF");
}

// Test surrogate pair for U+10000 (first supplementary character)
TEST_F(Utf16ToUtf8Test_1530, FirstSupplementaryChar_1530) {
    // U+10000 = D800 DC00 in UTF-16
    uint16_t input[] = {0xD800, 0xDC00, 0};
    std::string result = utf16ToUtf8(input, 2);
    EXPECT_EQ(result, "\xF0\x90\x80\x80");
}

// Test maxUtf16 cuts in the middle of a surrogate pair
TEST_F(Utf16ToUtf8Test_1530, MaxUtf16CutsSurrogatePair_1530) {
    // U+1F600 = D83D DE00, but we only allow 1 unit
    uint16_t input[] = {0xD83D, 0xDE00, 0};
    std::string result = utf16ToUtf8(input, 1);
    // Only the high surrogate is seen, should produce replacement char
    EXPECT_EQ(result, "\xEF\xBF\xBD");
}

// Test long string of ASCII characters
TEST_F(Utf16ToUtf8Test_1530, LongAsciiString_1530) {
    std::vector<uint16_t> input(101);
    for (int i = 0; i < 100; i++) {
        input[i] = 'a';
    }
    input[100] = 0;
    std::string result = utf16ToUtf8(input.data(), 100);
    EXPECT_EQ(result, std::string(100, 'a'));
}

// Test mixed BMP and supplementary characters
TEST_F(Utf16ToUtf8Test_1530, MixedBmpAndSupplementary_1530) {
    // 'A', U+4E16 (世), U+1F600 (😀), 'B'
    uint16_t input[] = {0x0041, 0x4E16, 0xD83D, 0xDE00, 0x0042, 0};
    std::string result = utf16ToUtf8(input, 5);
    EXPECT_EQ(result, "A\xE4\xB8\x96\xF0\x9F\x98\x80" "B");
}

// Test single character U+0001
TEST_F(Utf16ToUtf8Test_1530, MinNonNullChar_1530) {
    uint16_t input[] = {0x0001, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\x01");
}

// Test U+007F (max single-byte UTF-8)
TEST_F(Utf16ToUtf8Test_1530, MaxSingleByteUtf8_1530) {
    uint16_t input[] = {0x007F, 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "\x7F");
}

// Test high surrogate followed by another high surrogate
TEST_F(Utf16ToUtf8Test_1530, TwoHighSurrogates_1530) {
    uint16_t input[] = {0xD800, 0xD801, 0xDC00, 0};
    std::string result = utf16ToUtf8(input, 3);
    // First high surrogate is rejected when second high surrogate is seen
    // Then second pair D801 DC00 should form a valid codepoint
    EXPECT_FALSE(result.empty());
}

// Test maxUtf16 negative (edge case)
TEST_F(Utf16ToUtf8Test_1530, NegativeMaxUtf16_1530) {
    uint16_t input[] = {'A', 0};
    std::string result = utf16ToUtf8(input, -1);
    // nIn starts at 0 and nIn < -1 is false for signed comparison
    // so nothing should be processed
    EXPECT_EQ(result, "");
}

// Test maxUtf16 of 1 with single character
TEST_F(Utf16ToUtf8Test_1530, MaxUtf16One_1530) {
    uint16_t input[] = {'Z', 'Y', 0};
    std::string result = utf16ToUtf8(input, 1);
    EXPECT_EQ(result, "Z");
}

// Test BOM (Byte Order Mark) U+FEFF
TEST_F(Utf16ToUtf8Test_1530, ByteOrderMark_1530) {
    uint16_t input[] = {0xFEFF, 0x0041, 0};
    std::string result = utf16ToUtf8(input, 2);
    EXPECT_EQ(result, "\xEF\xBB\xBF" "A");
}
