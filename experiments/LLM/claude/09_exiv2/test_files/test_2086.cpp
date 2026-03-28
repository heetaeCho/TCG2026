#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <cstdint>

// Include the header that declares the Unicode conversion functions
// The xmpsdk typically exposes these through a header
#include "UnicodeConversions.hpp"

class UTF16NatToUTF32SwpTest_2086 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic ASCII-range character conversion (BMP, no surrogates)
TEST_F(UTF16NatToUTF32SwpTest_2086, BasicASCIIConversion_2086) {
    // 'A' = 0x0041
    UTF16Unit utf16In[] = { 0x0041 };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 1, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    // The output should be byte-swapped version of 0x00000041
}

// Test multiple BMP characters
TEST_F(UTF16NatToUTF32SwpTest_2086, MultipleBMPCharacters_2086) {
    UTF16Unit utf16In[] = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F }; // "Hello"
    UTF32Unit utf32Out[5] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 5, utf32Out, 5, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 5u);
    EXPECT_EQ(utf32Written, 5u);
}

// Test output buffer smaller than input
TEST_F(UTF16NatToUTF32SwpTest_2086, OutputBufferSmaller_2086) {
    UTF16Unit utf16In[] = { 0x0041, 0x0042, 0x0043, 0x0044 };
    UTF32Unit utf32Out[2] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 4, utf32Out, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 2u);
}

// Test surrogate pair conversion (U+10000 = D800 DC00)
TEST_F(UTF16NatToUTF32SwpTest_2086, SurrogatePairConversion_2086) {
    UTF16Unit utf16In[] = { 0xD800, 0xDC00 }; // U+10000
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 2, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test surrogate pair U+1F600 (😀) = D83D DE00
TEST_F(UTF16NatToUTF32SwpTest_2086, EmojiSurrogatePair_2086) {
    UTF16Unit utf16In[] = { 0xD83D, 0xDE00 }; // U+1F600
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 2, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test mixed BMP and surrogate pairs
TEST_F(UTF16NatToUTF32SwpTest_2086, MixedBMPAndSurrogates_2086) {
    // 'A', U+10000 (D800 DC00), 'B'
    UTF16Unit utf16In[] = { 0x0041, 0xD800, 0xDC00, 0x0042 };
    UTF32Unit utf32Out[3] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 4, utf32Out, 3, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 3u);
}

// Test incomplete surrogate pair at end of input (only high surrogate)
TEST_F(UTF16NatToUTF32SwpTest_2086, IncompleteSurrogatePair_2086) {
    UTF16Unit utf16In[] = { 0xD800 }; // High surrogate only
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 1, utf32Out, 1, &utf16Read, &utf32Written);

    // Should stop because input ends in middle of surrogate pair
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test zero-length input
TEST_F(UTF16NatToUTF32SwpTest_2086, ZeroLengthInput_2086) {
    UTF16Unit utf16In[] = { 0x0041 };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 0, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test zero-length output
TEST_F(UTF16NatToUTF32SwpTest_2086, ZeroLengthOutput_2086) {
    UTF16Unit utf16In[] = { 0x0041 };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 1, utf32Out, 0, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test BMP character just below surrogate range (0xD7FF)
TEST_F(UTF16NatToUTF32SwpTest_2086, BelowSurrogateRange_2086) {
    UTF16Unit utf16In[] = { 0xD7FF };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 1, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test BMP character just above surrogate range (0xE000)
TEST_F(UTF16NatToUTF32SwpTest_2086, AboveSurrogateRange_2086) {
    UTF16Unit utf16In[] = { 0xE000 };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 1, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test high surrogate at start boundary (0xD800)
TEST_F(UTF16NatToUTF32SwpTest_2086, HighSurrogateBoundary_2086) {
    UTF16Unit utf16In[] = { 0xD800, 0xDC00 };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 2, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test high surrogate at end boundary (0xDBFF) with low surrogate (0xDFFF) = U+10FFFF
TEST_F(UTF16NatToUTF32SwpTest_2086, MaxSurrogatePair_2086) {
    UTF16Unit utf16In[] = { 0xDBFF, 0xDFFF }; // U+10FFFF
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 2, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test BMP followed by incomplete surrogate at end
TEST_F(UTF16NatToUTF32SwpTest_2086, BMPThenIncompleteSurrogate_2086) {
    UTF16Unit utf16In[] = { 0x0041, 0xD800 }; // 'A' then incomplete surrogate
    UTF32Unit utf32Out[2] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 2, utf32Out, 2, &utf16Read, &utf32Written);

    // Should convert 'A' but stop at incomplete surrogate
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test multiple surrogate pairs
TEST_F(UTF16NatToUTF32SwpTest_2086, MultipleSurrogatePairs_2086) {
    // U+10000 and U+10001
    UTF16Unit utf16In[] = { 0xD800, 0xDC00, 0xD800, 0xDC01 };
    UTF32Unit utf32Out[2] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 4, utf32Out, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 2u);
}

// Test output buffer limits conversion of surrogate pairs
TEST_F(UTF16NatToUTF32SwpTest_2086, OutputBufferLimitsSurrogatePairs_2086) {
    // Two surrogate pairs but only room for one output
    UTF16Unit utf16In[] = { 0xD800, 0xDC00, 0xD800, 0xDC01 };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 4, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test large BMP value (0xFFFF)
TEST_F(UTF16NatToUTF32SwpTest_2086, MaxBMPValue_2086) {
    UTF16Unit utf16In[] = { 0xFFFF };
    UTF32Unit utf32Out[1] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 1, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test single unit value of 0x0000 (null character)
TEST_F(UTF16NatToUTF32SwpTest_2086, NullCharacter_2086) {
    UTF16Unit utf16In[] = { 0x0000 };
    UTF32Unit utf32Out[1] = { 0xFFFFFFFF };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 1, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
}

// Test surrogate pair followed by BMP character
TEST_F(UTF16NatToUTF32SwpTest_2086, SurrogateThenBMP_2086) {
    UTF16Unit utf16In[] = { 0xD800, 0xDC00, 0x0042 }; // U+10000, 'B'
    UTF32Unit utf32Out[2] = { 0 };
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Nat_to_UTF32Swp(utf16In, 3, utf32Out, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf32Written, 2u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
