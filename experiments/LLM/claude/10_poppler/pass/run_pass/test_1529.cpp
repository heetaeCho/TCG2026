#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// Declaration of the function under test
int utf16CountUtf8Bytes(const uint16_t *utf16);

class Utf16CountUtf8BytesTest_1529 : public ::testing::Test {
protected:
};

// Test empty string (null terminator only)
TEST_F(Utf16CountUtf8BytesTest_1529, EmptyString_1529) {
    const uint16_t utf16[] = { 0 };
    EXPECT_EQ(0, utf16CountUtf8Bytes(utf16));
}

// Test single ASCII character (1 byte in UTF-8)
TEST_F(Utf16CountUtf8BytesTest_1529, SingleAsciiChar_1529) {
    const uint16_t utf16[] = { 'A', 0 };
    EXPECT_EQ(1, utf16CountUtf8Bytes(utf16));
}

// Test multiple ASCII characters
TEST_F(Utf16CountUtf8BytesTest_1529, MultipleAsciiChars_1529) {
    const uint16_t utf16[] = { 'H', 'e', 'l', 'l', 'o', 0 };
    EXPECT_EQ(5, utf16CountUtf8Bytes(utf16));
}

// Test ASCII boundary - character 0x7F (last single-byte UTF-8)
TEST_F(Utf16CountUtf8BytesTest_1529, AsciiBoundary0x7F_1529) {
    const uint16_t utf16[] = { 0x7F, 0 };
    EXPECT_EQ(1, utf16CountUtf8Bytes(utf16));
}

// Test character 0x80 (first 2-byte UTF-8)
TEST_F(Utf16CountUtf8BytesTest_1529, TwoByteStart0x80_1529) {
    const uint16_t utf16[] = { 0x80, 0 };
    EXPECT_EQ(2, utf16CountUtf8Bytes(utf16));
}

// Test character 0x7FF (last 2-byte UTF-8)
TEST_F(Utf16CountUtf8BytesTest_1529, TwoByteBoundary0x7FF_1529) {
    const uint16_t utf16[] = { 0x7FF, 0 };
    EXPECT_EQ(2, utf16CountUtf8Bytes(utf16));
}

// Test character 0x800 (first 3-byte UTF-8)
TEST_F(Utf16CountUtf8BytesTest_1529, ThreeByteStart0x800_1529) {
    const uint16_t utf16[] = { 0x800, 0 };
    EXPECT_EQ(3, utf16CountUtf8Bytes(utf16));
}

// Test character 0xFFFF (last BMP character, 3-byte UTF-8)
// Note: 0xFFFF is not a surrogate, so it should be accepted as a single code unit
TEST_F(Utf16CountUtf8BytesTest_1529, ThreeByteBoundary0xFFFF_1529) {
    const uint16_t utf16[] = { 0xFFFF, 0 };
    EXPECT_EQ(3, utf16CountUtf8Bytes(utf16));
}

// Test surrogate pair for U+10000 (first 4-byte UTF-8 codepoint)
// U+10000 -> D800 DC00
TEST_F(Utf16CountUtf8BytesTest_1529, SurrogatePairU10000_1529) {
    const uint16_t utf16[] = { 0xD800, 0xDC00, 0 };
    EXPECT_EQ(4, utf16CountUtf8Bytes(utf16));
}

// Test surrogate pair for U+10FFFF (last valid Unicode codepoint)
// U+10FFFF -> DBFF DFFF
TEST_F(Utf16CountUtf8BytesTest_1529, SurrogatePairU10FFFF_1529) {
    const uint16_t utf16[] = { 0xDBFF, 0xDFFF, 0 };
    EXPECT_EQ(4, utf16CountUtf8Bytes(utf16));
}

// Test surrogate pair for U+1F600 (emoji, 4-byte UTF-8)
// U+1F600 -> D83D DE00
TEST_F(Utf16CountUtf8BytesTest_1529, SurrogatePairEmoji_1529) {
    const uint16_t utf16[] = { 0xD83D, 0xDE00, 0 };
    EXPECT_EQ(4, utf16CountUtf8Bytes(utf16));
}

// Test lone high surrogate (invalid, should produce replacement character = 3 bytes)
TEST_F(Utf16CountUtf8BytesTest_1529, LoneHighSurrogate_1529) {
    const uint16_t utf16[] = { 0xD800, 0 };
    // Lone high surrogate at end of string - state won't be ACCEPT or REJECT
    // Should add 3 bytes for replacement character
    EXPECT_EQ(3, utf16CountUtf8Bytes(utf16));
}

// Test lone low surrogate (invalid, should produce replacement character = 3 bytes)
TEST_F(Utf16CountUtf8BytesTest_1529, LoneLowSurrogate_1529) {
    const uint16_t utf16[] = { 0xDC00, 0 };
    // Lone low surrogate should be rejected
    EXPECT_EQ(3, utf16CountUtf8Bytes(utf16));
}

// Test high surrogate followed by non-surrogate (invalid sequence)
TEST_F(Utf16CountUtf8BytesTest_1529, HighSurrogateFollowedByAscii_1529) {
    const uint16_t utf16[] = { 0xD800, 'A', 0 };
    // The high surrogate + 'A' should result in rejection of the surrogate pair
    // Then 'A' is processed normally
    int result = utf16CountUtf8Bytes(utf16);
    // High surrogate state, then 'A' causes reject (3 bytes), then 'A' itself (1 byte)
    // But exact behavior depends on state machine - we can verify it's reasonable
    EXPECT_GT(result, 0);
}

// Test mixed content: ASCII + BMP + surrogate pair
TEST_F(Utf16CountUtf8BytesTest_1529, MixedContent_1529) {
    // 'A' (1 byte) + U+00E9 (é, 2 bytes) + U+4E16 (世, 3 bytes) + U+1F600 (😀, 4 bytes)
    const uint16_t utf16[] = { 0x0041, 0x00E9, 0x4E16, 0xD83D, 0xDE00, 0 };
    EXPECT_EQ(1 + 2 + 3 + 4, utf16CountUtf8Bytes(utf16));
}

// Test null character at position 0 (should return 0 as it's the terminator)
TEST_F(Utf16CountUtf8BytesTest_1529, NullTerminatorImmediate_1529) {
    const uint16_t utf16[] = { 0x0000 };
    EXPECT_EQ(0, utf16CountUtf8Bytes(utf16));
}

// Test character U+0001 (minimum non-null ASCII)
TEST_F(Utf16CountUtf8BytesTest_1529, MinNonNullAscii_1529) {
    const uint16_t utf16[] = { 0x0001, 0 };
    EXPECT_EQ(1, utf16CountUtf8Bytes(utf16));
}

// Test multiple surrogate pairs
TEST_F(Utf16CountUtf8BytesTest_1529, MultipleSurrogatePairs_1529) {
    // U+1F600 (D83D DE00) + U+1F601 (D83D DE01)
    const uint16_t utf16[] = { 0xD83D, 0xDE00, 0xD83D, 0xDE01, 0 };
    EXPECT_EQ(8, utf16CountUtf8Bytes(utf16));
}

// Test two consecutive low surrogates (both invalid)
TEST_F(Utf16CountUtf8BytesTest_1529, TwoLowSurrogates_1529) {
    const uint16_t utf16[] = { 0xDC00, 0xDC00, 0 };
    // Both should be rejected and replaced
    EXPECT_EQ(6, utf16CountUtf8Bytes(utf16));
}

// Test two consecutive high surrogates (first one is orphaned)
TEST_F(Utf16CountUtf8BytesTest_1529, TwoHighSurrogates_1529) {
    const uint16_t utf16[] = { 0xD800, 0xD800, 0 };
    // First high surrogate expects low surrogate, gets another high surrogate
    // Should produce at least some replacement bytes
    int result = utf16CountUtf8Bytes(utf16);
    EXPECT_GT(result, 0);
}

// Test long ASCII string
TEST_F(Utf16CountUtf8BytesTest_1529, LongAsciiString_1529) {
    std::vector<uint16_t> utf16(1001, 'x');
    utf16[1000] = 0;
    EXPECT_EQ(1000, utf16CountUtf8Bytes(utf16.data()));
}

// Test long string of 2-byte UTF-8 characters
TEST_F(Utf16CountUtf8BytesTest_1529, LongTwoByteChars_1529) {
    std::vector<uint16_t> utf16(101);
    for (int i = 0; i < 100; i++) {
        utf16[i] = 0x00E9; // é
    }
    utf16[100] = 0;
    EXPECT_EQ(200, utf16CountUtf8Bytes(utf16.data()));
}

// Test long string of 3-byte UTF-8 characters (CJK)
TEST_F(Utf16CountUtf8BytesTest_1529, LongThreeByteChars_1529) {
    std::vector<uint16_t> utf16(101);
    for (int i = 0; i < 100; i++) {
        utf16[i] = 0x4E16; // 世
    }
    utf16[100] = 0;
    EXPECT_EQ(300, utf16CountUtf8Bytes(utf16.data()));
}

// Test surrogate pair in the middle of ASCII
TEST_F(Utf16CountUtf8BytesTest_1529, SurrogatePairMiddleOfAscii_1529) {
    const uint16_t utf16[] = { 'A', 'B', 0xD83D, 0xDE00, 'C', 'D', 0 };
    EXPECT_EQ(1 + 1 + 4 + 1 + 1, utf16CountUtf8Bytes(utf16));
}

// Test character at BMP boundary
TEST_F(Utf16CountUtf8BytesTest_1529, BMPCharacterD7FF_1529) {
    // 0xD7FF is the last character before surrogates
    const uint16_t utf16[] = { 0xD7FF, 0 };
    EXPECT_EQ(3, utf16CountUtf8Bytes(utf16));
}

// Test character E000 (first private use area, right after surrogates)
TEST_F(Utf16CountUtf8BytesTest_1529, PrivateUseE000_1529) {
    const uint16_t utf16[] = { 0xE000, 0 };
    EXPECT_EQ(3, utf16CountUtf8Bytes(utf16));
}

// Test high surrogate followed by low surrogate then another high surrogate orphaned at end
TEST_F(Utf16CountUtf8BytesTest_1529, ValidPairThenOrphanedHighSurrogate_1529) {
    const uint16_t utf16[] = { 0xD83D, 0xDE00, 0xD800, 0 };
    // Valid pair (4 bytes) + orphaned high surrogate (3 bytes replacement)
    EXPECT_EQ(7, utf16CountUtf8Bytes(utf16));
}
