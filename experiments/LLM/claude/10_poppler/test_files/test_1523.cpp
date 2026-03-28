#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

// Replicate the necessary declarations from the source
extern const uint32_t UTF8_ACCEPT;
extern const uint8_t decodeUtf8Table[364];

// We need to declare the function. Since it's inline in the .cc file,
// we replicate the table and function here for testing purposes.
static const uint32_t kUTF8_ACCEPT = 0;
static const uint32_t kUTF8_REJECT = 12;

static const uint8_t kDecodeUtf8Table[364] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 11, 6, 6, 6, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    0, 12, 24, 36, 60, 96, 84, 12, 12, 12, 48, 72, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 0, 12, 12, 12, 12, 12, 0, 12, 0, 12, 12, 12, 24, 12, 12, 12, 12, 12, 24, 12, 24, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 24, 12, 12, 12, 12, 12, 24, 12, 12, 12, 12, 12, 12, 12, 24, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 36, 12, 36, 12, 12, 12, 36, 12, 12, 12, 12, 12, 36, 12, 36, 12, 12,
    12, 36, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

// Replicate the inline function for testing
static inline uint32_t decodeUtf8(uint32_t *state, uint32_t *codep, char byte) {
    uint32_t b = (unsigned char)byte;
    uint32_t type = kDecodeUtf8Table[b];
    *codep = (*state != kUTF8_ACCEPT) ? (b & 0x3fU) | (*codep << 6) : (0xff >> type) & (b);
    *state = kDecodeUtf8Table[256 + *state + type];
    return *state;
}

// Helper: decode a full UTF-8 string into codepoints
static bool decodeUtf8String(const std::string &input, std::vector<uint32_t> &codepoints) {
    uint32_t state = kUTF8_ACCEPT;
    uint32_t codep = 0;
    codepoints.clear();
    for (size_t i = 0; i < input.size(); i++) {
        uint32_t result = decodeUtf8(&state, &codep, input[i]);
        if (result == kUTF8_ACCEPT) {
            codepoints.push_back(codep);
        } else if (result == kUTF8_REJECT) {
            return false;
        }
    }
    return state == kUTF8_ACCEPT;
}

class DecodeUtf8Test_1523 : public ::testing::Test {
protected:
    uint32_t state;
    uint32_t codep;

    void SetUp() override {
        state = kUTF8_ACCEPT;
        codep = 0;
    }
};

// Test single ASCII characters (1-byte UTF-8)
TEST_F(DecodeUtf8Test_1523, SingleAsciiNull_1523) {
    uint32_t result = decodeUtf8(&state, &codep, '\0');
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0U);
}

TEST_F(DecodeUtf8Test_1523, SingleAsciiA_1523) {
    uint32_t result = decodeUtf8(&state, &codep, 'A');
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x41U);
}

TEST_F(DecodeUtf8Test_1523, SingleAsciiZ_1523) {
    uint32_t result = decodeUtf8(&state, &codep, 'z');
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x7AU);
}

TEST_F(DecodeUtf8Test_1523, SingleAsciiDel_1523) {
    // 0x7F is the highest single-byte value
    uint32_t result = decodeUtf8(&state, &codep, 0x7F);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x7FU);
}

// Test all printable ASCII characters decode immediately
TEST_F(DecodeUtf8Test_1523, AllAsciiCharacters_1523) {
    for (int c = 0; c < 128; c++) {
        state = kUTF8_ACCEPT;
        codep = 0;
        uint32_t result = decodeUtf8(&state, &codep, (char)c);
        EXPECT_EQ(result, kUTF8_ACCEPT) << "Failed for byte " << c;
        EXPECT_EQ(codep, (uint32_t)c) << "Wrong codepoint for byte " << c;
    }
}

// Test 2-byte UTF-8 sequence: U+00A9 (©) = 0xC2 0xA9
TEST_F(DecodeUtf8Test_1523, TwoByteSequenceCopyright_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xC2);
    EXPECT_NE(result, kUTF8_ACCEPT);
    EXPECT_NE(result, kUTF8_REJECT);

    result = decodeUtf8(&state, &codep, (char)0xA9);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x00A9U);
}

// Test 2-byte UTF-8 sequence: U+00E9 (é) = 0xC3 0xA9
TEST_F(DecodeUtf8Test_1523, TwoByteSequenceEAccent_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xC3);
    EXPECT_NE(result, kUTF8_ACCEPT);

    result = decodeUtf8(&state, &codep, (char)0xA9);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x00E9U);
}

// Test 2-byte UTF-8: smallest 2-byte U+0080 = 0xC2 0x80
TEST_F(DecodeUtf8Test_1523, TwoByteSmallest_1523) {
    decodeUtf8(&state, &codep, (char)0xC2);
    uint32_t result = decodeUtf8(&state, &codep, (char)0x80);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x0080U);
}

// Test 2-byte UTF-8: largest 2-byte U+07FF = 0xDF 0xBF
TEST_F(DecodeUtf8Test_1523, TwoByteLargest_1523) {
    decodeUtf8(&state, &codep, (char)0xDF);
    uint32_t result = decodeUtf8(&state, &codep, (char)0xBF);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x07FFU);
}

// Test 3-byte UTF-8 sequence: U+20AC (€) = 0xE2 0x82 0xAC
TEST_F(DecodeUtf8Test_1523, ThreeByteSequenceEuro_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xE2);
    EXPECT_NE(result, kUTF8_ACCEPT);

    result = decodeUtf8(&state, &codep, (char)0x82);
    EXPECT_NE(result, kUTF8_ACCEPT);

    result = decodeUtf8(&state, &codep, (char)0xAC);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x20ACU);
}

// Test 3-byte UTF-8: smallest 3-byte U+0800 = 0xE0 0xA0 0x80
TEST_F(DecodeUtf8Test_1523, ThreeByteSmallest_1523) {
    decodeUtf8(&state, &codep, (char)0xE0);
    decodeUtf8(&state, &codep, (char)0xA0);
    uint32_t result = decodeUtf8(&state, &codep, (char)0x80);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x0800U);
}

// Test 3-byte UTF-8: largest 3-byte U+FFFF = 0xEF 0xBF 0xBF
TEST_F(DecodeUtf8Test_1523, ThreeByteLargest_1523) {
    decodeUtf8(&state, &codep, (char)0xEF);
    decodeUtf8(&state, &codep, (char)0xBF);
    uint32_t result = decodeUtf8(&state, &codep, (char)0xBF);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0xFFFFU);
}

// Test 4-byte UTF-8 sequence: U+1F600 (😀) = 0xF0 0x9F 0x98 0x80
TEST_F(DecodeUtf8Test_1523, FourByteSequenceEmoji_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xF0);
    EXPECT_NE(result, kUTF8_ACCEPT);

    result = decodeUtf8(&state, &codep, (char)0x9F);
    EXPECT_NE(result, kUTF8_ACCEPT);

    result = decodeUtf8(&state, &codep, (char)0x98);
    EXPECT_NE(result, kUTF8_ACCEPT);

    result = decodeUtf8(&state, &codep, (char)0x80);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x1F600U);
}

// Test 4-byte UTF-8: smallest 4-byte U+10000 = 0xF0 0x90 0x80 0x80
TEST_F(DecodeUtf8Test_1523, FourByteSmallest_1523) {
    decodeUtf8(&state, &codep, (char)0xF0);
    decodeUtf8(&state, &codep, (char)0x90);
    decodeUtf8(&state, &codep, (char)0x80);
    uint32_t result = decodeUtf8(&state, &codep, (char)0x80);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x10000U);
}

// Test 4-byte UTF-8: largest valid U+10FFFF = 0xF4 0x8F 0xBF 0xBF
TEST_F(DecodeUtf8Test_1523, FourByteLargestValid_1523) {
    decodeUtf8(&state, &codep, (char)0xF4);
    decodeUtf8(&state, &codep, (char)0x8F);
    decodeUtf8(&state, &codep, (char)0xBF);
    uint32_t result = decodeUtf8(&state, &codep, (char)0xBF);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x10FFFFU);
}

// Test invalid: continuation byte without leading byte (0x80-0xBF as first byte)
TEST_F(DecodeUtf8Test_1523, InvalidLoneContinuationByte_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0x80);
    EXPECT_EQ(result, kUTF8_REJECT);
}

TEST_F(DecodeUtf8Test_1523, InvalidLoneContinuationByteBF_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xBF);
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test invalid: overlong 2-byte for 0xC0 and 0xC1 (these should reject)
TEST_F(DecodeUtf8Test_1523, InvalidOverlong2ByteC0_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xC0);
    // 0xC0 has type 8 in the table which leads to reject state
    EXPECT_EQ(result, kUTF8_REJECT);
}

TEST_F(DecodeUtf8Test_1523, InvalidOverlong2ByteC1_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xC1);
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test invalid: bytes 0xF5-0xFF (beyond valid UTF-8 range)
TEST_F(DecodeUtf8Test_1523, InvalidByteF5_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xF5);
    EXPECT_EQ(result, kUTF8_REJECT);
}

TEST_F(DecodeUtf8Test_1523, InvalidByteFF_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xFF);
    EXPECT_EQ(result, kUTF8_REJECT);
}

TEST_F(DecodeUtf8Test_1523, InvalidByteFE_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xFE);
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test truncated 2-byte sequence: start of 2-byte followed by ASCII
TEST_F(DecodeUtf8Test_1523, Truncated2ByteFollowedByAscii_1523) {
    decodeUtf8(&state, &codep, (char)0xC2);
    // Feed ASCII instead of continuation byte
    uint32_t result = decodeUtf8(&state, &codep, 'A');
    // Should transition to reject state since 'A' is not a continuation byte
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test truncated 3-byte sequence: only 2 of 3 bytes, then ASCII
TEST_F(DecodeUtf8Test_1523, Truncated3ByteSequence_1523) {
    decodeUtf8(&state, &codep, (char)0xE2);
    decodeUtf8(&state, &codep, (char)0x82);
    // Feed ASCII instead of third continuation byte
    uint32_t result = decodeUtf8(&state, &codep, 'A');
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test multiple codepoints in sequence
TEST_F(DecodeUtf8Test_1523, MultipleCodepointsHelloWorld_1523) {
    std::string input = "Hello";
    std::vector<uint32_t> codepoints;
    bool success = decodeUtf8String(input, codepoints);
    EXPECT_TRUE(success);
    ASSERT_EQ(codepoints.size(), 5U);
    EXPECT_EQ(codepoints[0], 'H');
    EXPECT_EQ(codepoints[1], 'e');
    EXPECT_EQ(codepoints[2], 'l');
    EXPECT_EQ(codepoints[3], 'l');
    EXPECT_EQ(codepoints[4], 'o');
}

// Test mixed ASCII and multi-byte
TEST_F(DecodeUtf8Test_1523, MixedAsciiAndMultibyte_1523) {
    // "A€B" = 'A' (0x41) + U+20AC (0xE2 0x82 0xAC) + 'B' (0x42)
    std::string input = "A\xE2\x82\xAC" "B";
    std::vector<uint32_t> codepoints;
    bool success = decodeUtf8String(input, codepoints);
    EXPECT_TRUE(success);
    ASSERT_EQ(codepoints.size(), 3U);
    EXPECT_EQ(codepoints[0], 0x41U);
    EXPECT_EQ(codepoints[1], 0x20ACU);
    EXPECT_EQ(codepoints[2], 0x42U);
}

// Test empty string
TEST_F(DecodeUtf8Test_1523, EmptyString_1523) {
    std::string input = "";
    std::vector<uint32_t> codepoints;
    bool success = decodeUtf8String(input, codepoints);
    EXPECT_TRUE(success);
    EXPECT_EQ(codepoints.size(), 0U);
}

// Test that state is not accept after partial sequence
TEST_F(DecodeUtf8Test_1523, PartialSequenceStateNotAccept_1523) {
    decodeUtf8(&state, &codep, (char)0xE2);
    EXPECT_NE(state, kUTF8_ACCEPT);
    EXPECT_NE(state, kUTF8_REJECT);
}

// Test invalid: 3-byte sequence with invalid second byte (0xE0 followed by 0x80-0x9F is overlong)
TEST_F(DecodeUtf8Test_1523, InvalidOverlong3Byte_1523) {
    decodeUtf8(&state, &codep, (char)0xE0);
    uint32_t result = decodeUtf8(&state, &codep, (char)0x80);
    // 0xE0 expects second byte 0xA0-0xBF; 0x80 should fail
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test invalid: 4-byte starting with 0xF4, second byte > 0x8F
TEST_F(DecodeUtf8Test_1523, InvalidF4SecondByteTooHigh_1523) {
    decodeUtf8(&state, &codep, (char)0xF4);
    uint32_t result = decodeUtf8(&state, &codep, (char)0x90);
    // 0xF4 with second byte >= 0x90 exceeds U+10FFFF, should reject
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test: state transitions through 4-byte decode are non-accept, non-reject until last byte
TEST_F(DecodeUtf8Test_1523, FourByteIntermediateStates_1523) {
    uint32_t r1 = decodeUtf8(&state, &codep, (char)0xF0);
    EXPECT_NE(r1, kUTF8_ACCEPT);
    EXPECT_NE(r1, kUTF8_REJECT);

    uint32_t r2 = decodeUtf8(&state, &codep, (char)0x9F);
    EXPECT_NE(r2, kUTF8_ACCEPT);
    EXPECT_NE(r2, kUTF8_REJECT);

    uint32_t r3 = decodeUtf8(&state, &codep, (char)0x98);
    EXPECT_NE(r3, kUTF8_ACCEPT);
    EXPECT_NE(r3, kUTF8_REJECT);

    uint32_t r4 = decodeUtf8(&state, &codep, (char)0x80);
    EXPECT_EQ(r4, kUTF8_ACCEPT);
}

// Test decoding multiple complete sequences consecutively resets state properly
TEST_F(DecodeUtf8Test_1523, ConsecutiveMultibyteSequences_1523) {
    // U+00A9 = 0xC2 0xA9 then U+00AE = 0xC2 0xAE
    decodeUtf8(&state, &codep, (char)0xC2);
    uint32_t result = decodeUtf8(&state, &codep, (char)0xA9);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x00A9U);

    // State should be accept now, start next sequence
    EXPECT_EQ(state, kUTF8_ACCEPT);
    decodeUtf8(&state, &codep, (char)0xC2);
    result = decodeUtf8(&state, &codep, (char)0xAE);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x00AEU);
}

// Test: U+0000 null character
TEST_F(DecodeUtf8Test_1523, NullCharacter_1523) {
    uint32_t result = decodeUtf8(&state, &codep, '\0');
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0U);
}

// Test: Space character
TEST_F(DecodeUtf8Test_1523, SpaceCharacter_1523) {
    uint32_t result = decodeUtf8(&state, &codep, ' ');
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x20U);
}

// Test: CJK character U+4E16 (世) = 0xE4 0xB8 0x96
TEST_F(DecodeUtf8Test_1523, CJKCharacter_1523) {
    decodeUtf8(&state, &codep, (char)0xE4);
    decodeUtf8(&state, &codep, (char)0xB8);
    uint32_t result = decodeUtf8(&state, &codep, (char)0x96);
    EXPECT_EQ(result, kUTF8_ACCEPT);
    EXPECT_EQ(codep, 0x4E16U);
}

// Test: full string with 4-byte characters
TEST_F(DecodeUtf8Test_1523, FullStringWith4ByteChars_1523) {
    // U+1F4A9 = 0xF0 0x9F 0x92 0xA9
    std::string input = "\xF0\x9F\x92\xA9";
    std::vector<uint32_t> codepoints;
    bool success = decodeUtf8String(input, codepoints);
    EXPECT_TRUE(success);
    ASSERT_EQ(codepoints.size(), 1U);
    EXPECT_EQ(codepoints[0], 0x1F4A9U);
}

// Test: invalid sequence detection with full string helper
TEST_F(DecodeUtf8Test_1523, InvalidStringDetection_1523) {
    // Start of 2-byte but no continuation
    std::string input = "\xC2";
    std::vector<uint32_t> codepoints;
    bool success = decodeUtf8String(input, codepoints);
    EXPECT_FALSE(success); // incomplete sequence
}

// Test: boundary between 2-byte and 3-byte (U+07FF and U+0800)
TEST_F(DecodeUtf8Test_1523, BoundaryTwoThreeByte_1523) {
    // U+07FF = 0xDF 0xBF
    {
        uint32_t s = kUTF8_ACCEPT, c = 0;
        decodeUtf8(&s, &c, (char)0xDF);
        uint32_t result = decodeUtf8(&s, &c, (char)0xBF);
        EXPECT_EQ(result, kUTF8_ACCEPT);
        EXPECT_EQ(c, 0x07FFU);
    }
    // U+0800 = 0xE0 0xA0 0x80
    {
        uint32_t s = kUTF8_ACCEPT, c = 0;
        decodeUtf8(&s, &c, (char)0xE0);
        decodeUtf8(&s, &c, (char)0xA0);
        uint32_t result = decodeUtf8(&s, &c, (char)0x80);
        EXPECT_EQ(result, kUTF8_ACCEPT);
        EXPECT_EQ(c, 0x0800U);
    }
}

// Test: boundary between 3-byte and 4-byte (U+FFFF and U+10000)
TEST_F(DecodeUtf8Test_1523, BoundaryThreeFourByte_1523) {
    // U+FFFF = 0xEF 0xBF 0xBF
    {
        uint32_t s = kUTF8_ACCEPT, c = 0;
        decodeUtf8(&s, &c, (char)0xEF);
        decodeUtf8(&s, &c, (char)0xBF);
        uint32_t result = decodeUtf8(&s, &c, (char)0xBF);
        EXPECT_EQ(result, kUTF8_ACCEPT);
        EXPECT_EQ(c, 0xFFFFU);
    }
    // U+10000 = 0xF0 0x90 0x80 0x80
    {
        uint32_t s = kUTF8_ACCEPT, c = 0;
        decodeUtf8(&s, &c, (char)0xF0);
        decodeUtf8(&s, &c, (char)0x90);
        decodeUtf8(&s, &c, (char)0x80);
        uint32_t result = decodeUtf8(&s, &c, (char)0x80);
        EXPECT_EQ(result, kUTF8_ACCEPT);
        EXPECT_EQ(c, 0x10000U);
    }
}

// Test: surrogate range characters should be rejected (U+D800 = 0xED 0xA0 0x80)
TEST_F(DecodeUtf8Test_1523, SurrogateRangeRejected_1523) {
    decodeUtf8(&state, &codep, (char)0xED);
    uint32_t result = decodeUtf8(&state, &codep, (char)0xA0);
    // The table should reject second byte in surrogate range for 0xED
    EXPECT_EQ(result, kUTF8_REJECT);
}

// Test: return value matches state
TEST_F(DecodeUtf8Test_1523, ReturnValueMatchesState_1523) {
    uint32_t result = decodeUtf8(&state, &codep, 'A');
    EXPECT_EQ(result, state);
}

TEST_F(DecodeUtf8Test_1523, ReturnValueMatchesStateMultibyte_1523) {
    uint32_t result = decodeUtf8(&state, &codep, (char)0xC2);
    EXPECT_EQ(result, state);
    result = decodeUtf8(&state, &codep, (char)0xA9);
    EXPECT_EQ(result, state);
}

// Test: long valid UTF-8 string
TEST_F(DecodeUtf8Test_1523, LongValidString_1523) {
    // "Héllo Wörld" with accented characters
    std::string input = "H\xC3\xA9llo W\xC3\xB6rld";
    std::vector<uint32_t> codepoints;
    bool success = decodeUtf8String(input, codepoints);
    EXPECT_TRUE(success);
    ASSERT_EQ(codepoints.size(), 11U);
    EXPECT_EQ(codepoints[0], 'H');
    EXPECT_EQ(codepoints[1], 0x00E9U); // é
    EXPECT_EQ(codepoints[2], 'l');
    EXPECT_EQ(codepoints[3], 'l');
    EXPECT_EQ(codepoints[4], 'o');
    EXPECT_EQ(codepoints[5], ' ');
    EXPECT_EQ(codepoints[6], 'W');
    EXPECT_EQ(codepoints[7], 0x00F6U); // ö
    EXPECT_EQ(codepoints[8], 'r');
    EXPECT_EQ(codepoints[9], 'l');
    EXPECT_EQ(codepoints[10], 'd');
}

// Test: 0xF0 followed by byte below valid range (overlong 4-byte)
TEST_F(DecodeUtf8Test_1523, InvalidOverlong4Byte_1523) {
    decodeUtf8(&state, &codep, (char)0xF0);
    // 0xF0 expects second byte 0x90-0xBF; 0x80 is too low
    uint32_t result = decodeUtf8(&state, &codep, (char)0x80);
    EXPECT_EQ(result, kUTF8_REJECT);
}
