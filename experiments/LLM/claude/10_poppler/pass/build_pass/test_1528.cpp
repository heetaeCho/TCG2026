#include <gtest/gtest.h>
#include <cstdint>

// Constants matching the implementation
const uint32_t UTF16_ACCEPT = 0;
const uint32_t UTF16_REJECT = static_cast<uint32_t>(-1);

// Re-declare the function under test (inline function from the source)
inline uint32_t decodeUtf16(uint32_t *state, uint32_t *codePoint, uint16_t codeUnit)
{
    if (*state == 0) {
        if (codeUnit >= 0xd800 && codeUnit < 0xdc00) {
            /* surrogate pair */
            *state = codeUnit;
            return *state;
        }
        if (codeUnit >= 0xdc00 && codeUnit < 0xe000) {
            /* invalid low surrogate */
            return UTF16_REJECT;
        }
        *codePoint = codeUnit;
        return UTF16_ACCEPT;
    }
    if (codeUnit >= 0xdc00 && codeUnit < 0xe000) {
        *codePoint = (((*state & 0x3ff) << 10) | (codeUnit & 0x3ff)) + 0x10000;
        *state = 0;
        return UTF16_ACCEPT;
    }
    /* invalid high surrogate */
    return UTF16_REJECT;
}

class DecodeUtf16Test_1528 : public ::testing::Test {
protected:
    uint32_t state;
    uint32_t codePoint;

    void SetUp() override
    {
        state = 0;
        codePoint = 0;
    }
};

// Test BMP character: ASCII 'A' (U+0041)
TEST_F(DecodeUtf16Test_1528, BasicBMPCharacter_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0x0041);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x0041u);
    EXPECT_EQ(state, 0u);
}

// Test BMP character: null (U+0000)
TEST_F(DecodeUtf16Test_1528, NullCharacter_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0x0000);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x0000u);
}

// Test BMP character just below surrogate range (U+D7FF)
TEST_F(DecodeUtf16Test_1528, BMPJustBelowSurrogateRange_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xD7FF);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0xD7FFu);
}

// Test BMP character just above surrogate range (U+E000)
TEST_F(DecodeUtf16Test_1528, BMPJustAboveSurrogateRange_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xE000);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0xE000u);
}

// Test BMP max (U+FFFF)
TEST_F(DecodeUtf16Test_1528, BMPMaxCharacter_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xFFFF);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0xFFFFu);
}

// Test high surrogate sets state and returns non-zero (not accept/reject)
TEST_F(DecodeUtf16Test_1528, HighSurrogateSetsState_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xD800);
    EXPECT_NE(result, UTF16_ACCEPT);
    EXPECT_NE(result, UTF16_REJECT);
    EXPECT_EQ(state, 0xD800u);
}

// Test high surrogate at upper boundary (0xDBFF)
TEST_F(DecodeUtf16Test_1528, HighSurrogateUpperBoundary_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDBFF);
    EXPECT_NE(result, UTF16_ACCEPT);
    EXPECT_NE(result, UTF16_REJECT);
    EXPECT_EQ(state, 0xDBFFu);
}

// Test lone low surrogate is rejected (state == 0)
TEST_F(DecodeUtf16Test_1528, LoneLowSurrogateRejected_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDC00);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test low surrogate at upper boundary rejected when state == 0
TEST_F(DecodeUtf16Test_1528, LoneLowSurrogateUpperBoundaryRejected_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDFFF);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test valid surrogate pair: U+10000 (D800, DC00)
TEST_F(DecodeUtf16Test_1528, ValidSurrogatePairMinSupplementary_1528)
{
    uint32_t result1 = decodeUtf16(&state, &codePoint, 0xD800);
    EXPECT_NE(result1, UTF16_ACCEPT);
    EXPECT_NE(result1, UTF16_REJECT);

    uint32_t result2 = decodeUtf16(&state, &codePoint, 0xDC00);
    EXPECT_EQ(result2, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x10000u);
    EXPECT_EQ(state, 0u);
}

// Test valid surrogate pair: U+10FFFF (DBFF, DFFF)
TEST_F(DecodeUtf16Test_1528, ValidSurrogatePairMaxSupplementary_1528)
{
    uint32_t result1 = decodeUtf16(&state, &codePoint, 0xDBFF);
    EXPECT_NE(result1, UTF16_ACCEPT);

    uint32_t result2 = decodeUtf16(&state, &codePoint, 0xDFFF);
    EXPECT_EQ(result2, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x10FFFFu);
    EXPECT_EQ(state, 0u);
}

// Test valid surrogate pair: U+1F600 (emoji) = D83D, DE00
TEST_F(DecodeUtf16Test_1528, ValidSurrogatePairEmoji_1528)
{
    uint32_t result1 = decodeUtf16(&state, &codePoint, 0xD83D);
    EXPECT_NE(result1, UTF16_ACCEPT);

    uint32_t result2 = decodeUtf16(&state, &codePoint, 0xDE00);
    EXPECT_EQ(result2, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x1F600u);
    EXPECT_EQ(state, 0u);
}

// Test high surrogate followed by BMP character (not low surrogate) -> reject
TEST_F(DecodeUtf16Test_1528, HighSurrogateFollowedByBMPIsRejected_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);
    EXPECT_NE(state, 0u);

    uint32_t result = decodeUtf16(&state, &codePoint, 0x0041);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test high surrogate followed by another high surrogate -> reject
TEST_F(DecodeUtf16Test_1528, HighSurrogateFollowedByHighSurrogateIsRejected_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);
    EXPECT_NE(state, 0u);

    uint32_t result = decodeUtf16(&state, &codePoint, 0xD801);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test high surrogate followed by value above surrogate range -> reject
TEST_F(DecodeUtf16Test_1528, HighSurrogateFollowedByNonSurrogateHighIsRejected_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);

    uint32_t result = decodeUtf16(&state, &codePoint, 0xE000);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test high surrogate followed by 0xFFFF -> reject
TEST_F(DecodeUtf16Test_1528, HighSurrogateFollowedByFFFFIsRejected_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);

    uint32_t result = decodeUtf16(&state, &codePoint, 0xFFFF);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test high surrogate followed by 0x0000 -> reject
TEST_F(DecodeUtf16Test_1528, HighSurrogateFollowedByNullIsRejected_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);

    uint32_t result = decodeUtf16(&state, &codePoint, 0x0000);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test multiple BMP characters in sequence
TEST_F(DecodeUtf16Test_1528, MultipleBMPCharactersInSequence_1528)
{
    uint32_t result;

    result = decodeUtf16(&state, &codePoint, 0x0048); // 'H'
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x0048u);

    result = decodeUtf16(&state, &codePoint, 0x0069); // 'i'
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x0069u);
}

// Test valid surrogate pair followed by BMP character
TEST_F(DecodeUtf16Test_1528, SurrogatePairFollowedByBMP_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDC00);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x10000u);
    EXPECT_EQ(state, 0u);

    // Now a BMP character should work
    result = decodeUtf16(&state, &codePoint, 0x0041);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x0041u);
}

// Test state is properly returned for high surrogate
TEST_F(DecodeUtf16Test_1528, HighSurrogateReturnsStateValue_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xD834);
    EXPECT_EQ(result, 0xD834u);
    EXPECT_EQ(state, 0xD834u);
}

// Test boundary: 0xDC00 is the first valid low surrogate
TEST_F(DecodeUtf16Test_1528, LowSurrogateBoundaryDC00_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDC00);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x10000u);
}

// Test boundary: 0xDFFF is the last valid low surrogate
TEST_F(DecodeUtf16Test_1528, LowSurrogateBoundaryDFFF_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDFFF);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x103FFu);
}

// Test boundary: 0xDBFF (last high surrogate) with 0xDC00 (first low surrogate)
TEST_F(DecodeUtf16Test_1528, HighSurrogateDBFFWithLowDC00_1528)
{
    decodeUtf16(&state, &codePoint, 0xDBFF);
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDC00);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x10FC00u);
}

// Test that codePoint is not modified when high surrogate is received
TEST_F(DecodeUtf16Test_1528, CodePointUnchangedOnHighSurrogate_1528)
{
    codePoint = 0x12345;
    decodeUtf16(&state, &codePoint, 0xD800);
    // codePoint should remain unchanged since we just stored state
    EXPECT_EQ(codePoint, 0x12345u);
}

// Test lone low surrogate 0xDC01
TEST_F(DecodeUtf16Test_1528, LoneLowSurrogateDC01Rejected_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDC01);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test high surrogate followed by value just below low surrogate range (0xDBFF)
TEST_F(DecodeUtf16Test_1528, HighSurrogateFollowedByDBFFRejected_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDBFF);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test high surrogate followed by value at 0xD800 (another high surrogate)
TEST_F(DecodeUtf16Test_1528, HighSurrogateFollowedByD800Rejected_1528)
{
    decodeUtf16(&state, &codePoint, 0xD800);
    uint32_t result = decodeUtf16(&state, &codePoint, 0xD800);
    EXPECT_EQ(result, UTF16_REJECT);
}

// Test valid surrogate pair computation: D834 DD1E = U+1D11E (Musical Symbol G Clef)
TEST_F(DecodeUtf16Test_1528, ValidSurrogatePairMusicalSymbol_1528)
{
    decodeUtf16(&state, &codePoint, 0xD834);
    uint32_t result = decodeUtf16(&state, &codePoint, 0xDD1E);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0x1D11Eu);
    EXPECT_EQ(state, 0u);
}

// Test BMP character in private use area (U+F000)
TEST_F(DecodeUtf16Test_1528, BMPPrivateUseArea_1528)
{
    uint32_t result = decodeUtf16(&state, &codePoint, 0xF000);
    EXPECT_EQ(result, UTF16_ACCEPT);
    EXPECT_EQ(codePoint, 0xF000u);
}

// Test that UTF16_REJECT is (uint32_t)-1
TEST_F(DecodeUtf16Test_1528, RejectValueIsMaxUint32_1528)
{
    EXPECT_EQ(UTF16_REJECT, static_cast<uint32_t>(-1));
}

// Test that UTF16_ACCEPT is 0
TEST_F(DecodeUtf16Test_1528, AcceptValueIsZero_1528)
{
    EXPECT_EQ(UTF16_ACCEPT, 0u);
}
