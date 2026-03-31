#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the public header for Unicode conversions from XMP SDK
#include "source/UnicodeConversions.hpp"

class UnicodeConversionsTest_2069 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test BMP character conversion (non-surrogate, simple case)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_BasicBMPCharacter_2069) {
    // ASCII 'A' = 0x0041
    UTF16Unit utf16In[] = { 0x0041 };
    size_t utf16Len = 1;
    UTF32Unit cpOut = 0;
    size_t utf16Read = 0;

    // Use the public conversion function that internally calls CodePoint_from_UTF16Nat
    // Convert a simple UTF-16 buffer to UTF-32
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read2 = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read2, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0041));
    EXPECT_EQ(utf16Read2, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test empty input
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_EmptyInput_2069) {
    UTF16Unit utf16In[] = { 0x0041 };
    size_t utf16Len = 0;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test surrogate pair (character outside BMP, e.g., U+10000 = D800 DC00)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_SurrogatePair_2069) {
    // U+10000 encoded as surrogate pair: high=0xD800, low=0xDC00
    UTF16Unit utf16In[] = { 0xD800, 0xDC00 };
    size_t utf16Len = 2;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x10000));
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test surrogate pair for U+1F600 (😀) = D83D DE00
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_SurrogatePairEmoji_2069) {
    UTF16Unit utf16In[] = { 0xD83D, 0xDE00 };
    size_t utf16Len = 2;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x1F600));
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test multiple BMP characters
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_MultipleBMPCharacters_2069) {
    UTF16Unit utf16In[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F }; // "Hello"
    size_t utf16Len = 5;
    UTF32Unit utf32Buf[8] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Written, 5u);
    EXPECT_EQ(utf16Read, 5u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0048));
    EXPECT_EQ(utf32Buf[1], static_cast<UTF32Unit>(0x0065));
    EXPECT_EQ(utf32Buf[2], static_cast<UTF32Unit>(0x006C));
    EXPECT_EQ(utf32Buf[3], static_cast<UTF32Unit>(0x006C));
    EXPECT_EQ(utf32Buf[4], static_cast<UTF32Unit>(0x006F));
}

// Test boundary: character just below surrogate range (0xD7FF)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_BelowSurrogateRange_2069) {
    UTF16Unit utf16In[] = { 0xD7FF };
    size_t utf16Len = 1;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0xD7FF));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test boundary: character just above surrogate range (0xE000)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_AboveSurrogateRange_2069) {
    UTF16Unit utf16In[] = { 0xE000 };
    size_t utf16Len = 1;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0xE000));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test boundary: max BMP character 0xFFFF
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_MaxBMPCharacter_2069) {
    UTF16Unit utf16In[] = { 0xFFFF };
    size_t utf16Len = 1;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0xFFFF));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test null character (0x0000)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_NullCharacter_2069) {
    UTF16Unit utf16In[] = { 0x0000 };
    size_t utf16Len = 1;
    UTF32Unit utf32Buf[4] = {0xFFFFFFFF};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0000));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test mixed BMP and surrogate pairs
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_MixedBMPAndSurrogate_2069) {
    // 'A' followed by U+10000 (surrogate pair) followed by 'B'
    UTF16Unit utf16In[] = { 0x0041, 0xD800, 0xDC00, 0x0042 };
    size_t utf16Len = 4;
    UTF32Unit utf32Buf[8] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0041));
    EXPECT_EQ(utf32Buf[1], static_cast<UTF32Unit>(0x10000));
    EXPECT_EQ(utf32Buf[2], static_cast<UTF32Unit>(0x0042));
}

// Test surrogate pair at boundary: high surrogate at end of input (only 1 unit for pair)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_IncompleteSurrogatePair_2069) {
    // High surrogate alone - should be handled as an error or partial read
    UTF16Unit utf16In[] = { 0xD800 };
    size_t utf16Len = 1;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    // This may throw or produce specific behavior for incomplete surrogate
    // We just verify it doesn't crash and returns some defined state
    try {
        UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, sizeof(utf32Buf)/sizeof(UTF32Unit), &utf16Read, &utf32Written);
        // If it doesn't throw, verify read count is reasonable
        EXPECT_LE(utf16Read, 1u);
    } catch (...) {
        // Exception for malformed input is acceptable
        SUCCEED();
    }
}

// Test UTF-32 to UTF-16 round-trip for BMP character
TEST_F(UnicodeConversionsTest_2069, RoundTrip_BMP_UTF32ToUTF16ToUTF32_2069) {
    UTF32Unit originalCP = 0x4E2D; // Chinese character '中'
    UTF16Unit utf16Buf[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(&originalCP, 1, utf16Buf, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);

    // Convert back
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read2 = 0;
    size_t utf32Written2 = 0;

    UTF16Nat_to_UTF32Nat(utf16Buf, utf16Written, utf32Buf, 4, &utf16Read2, &utf32Written2);

    EXPECT_EQ(utf32Buf[0], originalCP);
}

// Test UTF-32 to UTF-16 round-trip for supplementary character
TEST_F(UnicodeConversionsTest_2069, RoundTrip_Supplementary_UTF32ToUTF16ToUTF32_2069) {
    UTF32Unit originalCP = 0x1F600; // 😀
    UTF16Unit utf16Buf[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(&originalCP, 1, utf16Buf, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);

    // Convert back
    UTF32Unit utf32Result[4] = {0};
    size_t utf16Read2 = 0;
    size_t utf32Written2 = 0;

    UTF16Nat_to_UTF32Nat(utf16Buf, utf16Written, utf32Result, 4, &utf16Read2, &utf32Written2);

    EXPECT_EQ(utf32Result[0], originalCP);
}

// Test with output buffer of zero size
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_ZeroOutputBuffer_2069) {
    UTF16Unit utf16In[] = { 0x0041 };
    size_t utf16Len = 1;
    UTF32Unit utf32Buf[1] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, 0, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test high surrogate boundaries: 0xD800 (first) and 0xDBFF (last high surrogate)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_SurrogatePairLastHighSurrogate_2069) {
    // U+10FC00 = DBFF DC00
    UTF16Unit utf16In[] = { 0xDBFF, 0xDC00 };
    size_t utf16Len = 2;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x10FC00));
}

// Test low surrogate boundaries: 0xDC00 (first) and 0xDFFF (last)
TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_SurrogatePairMaxCodePoint_2069) {
    // U+10FFFF = DBFF DFFF
    UTF16Unit utf16In[] = { 0xDBFF, 0xDFFF };
    size_t utf16Len = 2;
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, utf16Len, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x10FFFF));
}
#include <gtest/gtest.h>
#include <cstring>
#include <vector>

#include "source/UnicodeConversions.hpp"

class UnicodeConversionsTest_2069 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_BasicBMPCharacter_2069) {
    UTF16Unit utf16In[] = { 0x0041 };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0041));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_EmptyInput_2069) {
    UTF16Unit utf16In[] = { 0x0041 };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 0, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_SurrogatePair_2069) {
    UTF16Unit utf16In[] = { 0xD800, 0xDC00 };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 2, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x10000));
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_SurrogatePairEmoji_2069) {
    UTF16Unit utf16In[] = { 0xD83D, 0xDE00 };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 2, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x1F600));
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_MultipleBMPCharacters_2069) {
    UTF16Unit utf16In[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F };
    UTF32Unit utf32Buf[8] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 5, utf32Buf, 8, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Written, 5u);
    EXPECT_EQ(utf16Read, 5u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0048));
    EXPECT_EQ(utf32Buf[1], static_cast<UTF32Unit>(0x0065));
    EXPECT_EQ(utf32Buf[2], static_cast<UTF32Unit>(0x006C));
    EXPECT_EQ(utf32Buf[3], static_cast<UTF32Unit>(0x006C));
    EXPECT_EQ(utf32Buf[4], static_cast<UTF32Unit>(0x006F));
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_BelowSurrogateRange_2069) {
    UTF16Unit utf16In[] = { 0xD7FF };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0xD7FF));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_AboveSurrogateRange_2069) {
    UTF16Unit utf16In[] = { 0xE000 };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0xE000));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_MaxBMPCharacter_2069) {
    UTF16Unit utf16In[] = { 0xFFFF };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0xFFFF));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_NullCharacter_2069) {
    UTF16Unit utf16In[] = { 0x0000 };
    UTF32Unit utf32Buf[4] = {0xFFFFFFFF};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0000));
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_MixedBMPAndSurrogate_2069) {
    UTF16Unit utf16In[] = { 0x0041, 0xD800, 0xDC00, 0x0042 };
    UTF32Unit utf32Buf[8] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 4, utf32Buf, 8, &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x0041));
    EXPECT_EQ(utf32Buf[1], static_cast<UTF32Unit>(0x10000));
    EXPECT_EQ(utf32Buf[2], static_cast<UTF32Unit>(0x0042));
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_ZeroOutputBuffer_2069) {
    UTF16Unit utf16In[] = { 0x0041 };
    UTF32Unit utf32Buf[1] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Buf, 0, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_SurrogatePairMaxCodePoint_2069) {
    UTF16Unit utf16In[] = { 0xDBFF, 0xDFFF };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 2, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x10FFFF));
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_LastHighSurrogateFirstLowSurrogate_2069) {
    UTF16Unit utf16In[] = { 0xDBFF, 0xDC00 };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16Nat_to_UTF32Nat(utf16In, 2, utf32Buf, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Buf[0], static_cast<UTF32Unit>(0x10FC00));
}

TEST_F(UnicodeConversionsTest_2069, RoundTrip_BMP_UTF32ToUTF16ToUTF32_2069) {
    UTF32Unit originalCP = 0x4E2D;
    UTF16Unit utf16Buf[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(&originalCP, 1, utf16Buf, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);

    UTF32Unit resultBuf[4] = {0};
    size_t utf16Read2 = 0;
    size_t utf32Written2 = 0;

    UTF16Nat_to_UTF32Nat(utf16Buf, utf16Written, resultBuf, 4, &utf16Read2, &utf32Written2);

    EXPECT_EQ(resultBuf[0], originalCP);
}

TEST_F(UnicodeConversionsTest_2069, RoundTrip_Supplementary_UTF32ToUTF16ToUTF32_2069) {
    UTF32Unit originalCP = 0x1F600;
    UTF16Unit utf16Buf[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(&originalCP, 1, utf16Buf, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);

    UTF32Unit resultBuf[4] = {0};
    size_t utf16Read2 = 0;
    size_t utf32Written2 = 0;

    UTF16Nat_to_UTF32Nat(utf16Buf, utf16Written, resultBuf, 4, &utf16Read2, &utf32Written2);

    EXPECT_EQ(resultBuf[0], originalCP);
}

TEST_F(UnicodeConversionsTest_2069, UTF16ToUTF32_IncompleteSurrogatePair_2069) {
    UTF16Unit utf16In[] = { 0xD800 };
    UTF32Unit utf32Buf[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    try {
        UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Buf, 4, &utf16Read, &utf32Written);
        EXPECT_LE(utf16Read, 1u);
    } catch (...) {
        SUCCEED();
    }
}
