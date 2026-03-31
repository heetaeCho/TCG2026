#include <gtest/gtest.h>
#include <string>
#include <string_view>

// Declaration of the function under test
int utf8CountUtf16CodeUnits(std::string_view utf8);

class Utf8CountUtf16CodeUnitsTest_1525 : public ::testing::Test {
protected:
};

// Test empty string returns 0
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, EmptyString_1525) {
    EXPECT_EQ(utf8CountUtf16CodeUnits(""), 0);
}

// Test single ASCII character (1 byte UTF-8, BMP, 1 UTF-16 code unit)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SingleAsciiChar_1525) {
    EXPECT_EQ(utf8CountUtf16CodeUnits("A"), 1);
}

// Test multiple ASCII characters
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, MultipleAsciiChars_1525) {
    EXPECT_EQ(utf8CountUtf16CodeUnits("Hello"), 5);
}

// Test null byte (U+0000) - single byte in UTF-8 but need string_view to handle it
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, NullByte_1525) {
    std::string_view sv("\0", 1);
    EXPECT_EQ(utf8CountUtf16CodeUnits(sv), 1);
}

// Test 2-byte UTF-8 character (e.g., U+00E9, é)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, TwoByteUtf8Char_1525) {
    // U+00E9 = 0xC3 0xA9
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xC3\xA9"), 1);
}

// Test 3-byte UTF-8 character (e.g., U+4E16, 世)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, ThreeByteUtf8Char_1525) {
    // U+4E16 = 0xE4 0xB8 0x96
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xE4\xB8\x96"), 1);
}

// Test 4-byte UTF-8 character (supplementary plane, requires surrogate pair = 2 UTF-16 code units)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, FourByteUtf8CharSurrogatePair_1525) {
    // U+1F600 (😀) = 0xF0 0x9F 0x98 0x80
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xF0\x9F\x98\x80"), 2);
}

// Test U+10000 (first supplementary character, requires surrogate pair)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, FirstSupplementaryChar_1525) {
    // U+10000 = 0xF0 0x90 0x80 0x80
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xF0\x90\x80\x80"), 2);
}

// Test U+10FFFF (last valid Unicode codepoint, requires surrogate pair)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, LastValidUnicodeCodepoint_1525) {
    // U+10FFFF = 0xF4 0x8F 0xBF 0xBF
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xF4\x8F\xBF\xBF"), 2);
}

// Test U+FFFF (last BMP character, 1 UTF-16 code unit)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, LastBmpChar_1525) {
    // U+FFFF = 0xEF 0xBF 0xBF
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xEF\xBF\xBF"), 1);
}

// Test mixed ASCII and multi-byte characters
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, MixedAsciiAndMultiByte_1525) {
    // "Aé世😀" = A(1) + é(1) + 世(1) + 😀(2) = 5
    EXPECT_EQ(utf8CountUtf16CodeUnits("A\xC3\xA9\xE4\xB8\x96\xF0\x9F\x98\x80"), 5);
}

// Test invalid single byte (continuation byte without leading byte)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidContinuationByte_1525) {
    // 0x80 is a continuation byte, not valid as a start byte
    EXPECT_EQ(utf8CountUtf16CodeUnits("\x80"), 1);
}

// Test multiple invalid continuation bytes
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, MultipleInvalidContinuationBytes_1525) {
    // Each invalid byte should produce a replacement char count of 1
    EXPECT_EQ(utf8CountUtf16CodeUnits("\x80\x80\x80"), 3);
}

// Test truncated 2-byte sequence
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, Truncated2ByteSequence_1525) {
    // 0xC3 starts a 2-byte sequence but no continuation byte follows
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xC3"), 1);
}

// Test truncated 3-byte sequence (missing last byte)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, Truncated3ByteSequence_1525) {
    // 0xE4 0xB8 starts a 3-byte sequence but missing the third byte
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xE4\xB8"), 1);
}

// Test truncated 4-byte sequence (missing last byte)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, Truncated4ByteSequence_1525) {
    // 0xF0 0x9F 0x98 starts a 4-byte sequence but missing the fourth byte
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xF0\x9F\x98"), 1);
}

// Test invalid byte 0xFF
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidByte0xFF_1525) {
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xFF"), 1);
}

// Test invalid byte 0xFE
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidByte0xFE_1525) {
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xFE"), 1);
}

// Test overlong 2-byte encoding (e.g., U+0000 encoded as 0xC0 0x80)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, Overlong2ByteEncoding_1525) {
    // 0xC0 0x80 is an overlong encoding - behavior depends on decoder
    // The decoder should reject this; each invalid state increments count
    int result = utf8CountUtf16CodeUnits("\xC0\x80");
    EXPECT_GE(result, 1);
}

// Test valid followed by invalid
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, ValidFollowedByInvalid_1525) {
    // "A" + invalid continuation byte
    EXPECT_EQ(utf8CountUtf16CodeUnits("A\x80"), 2);
}

// Test invalid followed by valid
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, InvalidFollowedByValid_1525) {
    // Invalid continuation byte + "A"
    EXPECT_EQ(utf8CountUtf16CodeUnits("\x80""A"), 2);
}

// Test U+0080 (smallest 2-byte UTF-8 character)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SmallestTwoByteChar_1525) {
    // U+0080 = 0xC2 0x80
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xC2\x80"), 1);
}

// Test U+0800 (smallest 3-byte UTF-8 character)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SmallestThreeByteChar_1525) {
    // U+0800 = 0xE0 0xA0 0x80
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xE0\xA0\x80"), 1);
}

// Test U+D800 area (surrogate range, technically invalid Unicode but valid as UTF-8 bytes)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, SurrogateRange_1525) {
    // U+D800 = 0xED 0xA0 0x80 - this is in surrogate range
    int result = utf8CountUtf16CodeUnits("\xED\xA0\x80");
    // Depending on decoder strictness, this may be accepted or rejected
    EXPECT_GE(result, 1);
}

// Test long string of ASCII
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, LongAsciiString_1525) {
    std::string longStr(1000, 'x');
    EXPECT_EQ(utf8CountUtf16CodeUnits(longStr), 1000);
}

// Test long string of 4-byte characters (all surrogate pairs)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, LongFourByteString_1525) {
    std::string longStr;
    for (int i = 0; i < 100; i++) {
        longStr += "\xF0\x9F\x98\x80"; // U+1F600
    }
    EXPECT_EQ(utf8CountUtf16CodeUnits(longStr), 200);
}

// Test incomplete multi-byte at end followed by nothing (tests the trailing state check)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, IncompleteAtEnd4Byte_1525) {
    // Start of a 4-byte sequence with only 2 continuation bytes
    EXPECT_EQ(utf8CountUtf16CodeUnits("A\xF0\x9F\x98"), 2);
}

// Test string with only 2-byte characters
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, OnlyTwoByteChars_1525) {
    // "éèê" = 3 characters, each 2 bytes, each 1 UTF-16 code unit
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xC3\xA9\xC3\xA8\xC3\xAA"), 3);
}

// Test broken sequence mid-stream followed by valid character
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, BrokenSequenceMidStreamFollowedByValid_1525) {
    // Start 2-byte seq (0xC3) then immediately start a valid ASCII 'B' instead of continuation
    // 0xC3 expects continuation, but 'B' (0x42) is not a continuation byte -> reject + accept 'B'
    int result = utf8CountUtf16CodeUnits("\xC3""B");
    EXPECT_EQ(result, 2);
}

// Test U+007F (last single-byte / ASCII character)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, LastAsciiChar_1525) {
    EXPECT_EQ(utf8CountUtf16CodeUnits("\x7F"), 1);
}

// Test U+07FF (last 2-byte UTF-8 character)
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, LastTwoByteChar_1525) {
    // U+07FF = 0xDF 0xBF
    EXPECT_EQ(utf8CountUtf16CodeUnits("\xDF\xBF"), 1);
}

// Test consecutive invalid bytes followed by valid multi-byte
TEST_F(Utf8CountUtf16CodeUnitsTest_1525, ConsecutiveInvalidThenValid_1525) {
    // Two invalid bytes + valid 3-byte char
    // 0xFF 0xFE 0xE4 0xB8 0x96
    int result = utf8CountUtf16CodeUnits("\xFF\xFE\xE4\xB8\x96");
    EXPECT_GE(result, 3); // At least 2 replacement + 1 valid
}
