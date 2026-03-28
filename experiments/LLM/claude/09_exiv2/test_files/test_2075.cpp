#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the implementation to access the static function
// We need the types and internal functions
#include "source/UnicodeConversions.hpp"
#include "source/UnicodeConversions.cpp"

class UTF32NatToUTF16NatTest_2075 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Basic ASCII conversion (BMP characters only)
TEST_F(UTF32NatToUTF16NatTest_2075, BasicASCIIConversion_2075) {
    UTF32Unit utf32In[] = { 0x0041, 0x0042, 0x0043 }; // A, B, C
    UTF16Unit utf16Out[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 3, utf16Out, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(utf16Out[0], 0x0041);
    EXPECT_EQ(utf16Out[1], 0x0042);
    EXPECT_EQ(utf16Out[2], 0x0043);
}

// Test: Single BMP character
TEST_F(UTF32NatToUTF16NatTest_2075, SingleBMPCharacter_2075) {
    UTF32Unit utf32In[] = { 0x00E9 }; // é
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x00E9);
}

// Test: Supplementary character (requires surrogate pair)
TEST_F(UTF32NatToUTF16NatTest_2075, SupplementaryCharacterSurrogatePair_2075) {
    UTF32Unit utf32In[] = { 0x10000 }; // Linear B Syllable B008 A
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // Surrogate pair for U+10000: high=0xD800, low=0xDC00
    EXPECT_EQ(utf16Out[0], 0xD800);
    EXPECT_EQ(utf16Out[1], 0xDC00);
}

// Test: Emoji character U+1F600 (surrogate pair)
TEST_F(UTF32NatToUTF16NatTest_2075, EmojiSurrogatePair_2075) {
    UTF32Unit utf32In[] = { 0x1F600 }; // 😀
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+1F600: high surrogate = 0xD83D, low surrogate = 0xDE00
    EXPECT_EQ(utf16Out[0], 0xD83D);
    EXPECT_EQ(utf16Out[1], 0xDE00);
}

// Test: Mixed BMP and supplementary characters
TEST_F(UTF32NatToUTF16NatTest_2075, MixedBMPAndSupplementary_2075) {
    UTF32Unit utf32In[] = { 0x0041, 0x10000, 0x0042 }; // A, U+10000, B
    UTF16Unit utf16Out[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 3, utf16Out, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 4u); // 1 + 2 + 1
    EXPECT_EQ(utf16Out[0], 0x0041);
    EXPECT_EQ(utf16Out[1], 0xD800);
    EXPECT_EQ(utf16Out[2], 0xDC00);
    EXPECT_EQ(utf16Out[3], 0x0042);
}

// Test: Empty input (zero length)
TEST_F(UTF32NatToUTF16NatTest_2075, EmptyInput_2075) {
    UTF32Unit utf32In[] = { 0x0041 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 0, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Output buffer too small for BMP characters
TEST_F(UTF32NatToUTF16NatTest_2075, OutputBufferTooSmallBMP_2075) {
    UTF32Unit utf32In[] = { 0x0041, 0x0042, 0x0043 };
    UTF16Unit utf16Out[2] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 3, utf16Out, 2, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0x0041);
    EXPECT_EQ(utf16Out[1], 0x0042);
}

// Test: Output buffer too small for surrogate pair (only 1 slot for a supplementary char)
TEST_F(UTF32NatToUTF16NatTest_2075, OutputBufferTooSmallForSurrogate_2075) {
    UTF32Unit utf32In[] = { 0x10000 };
    UTF16Unit utf16Out[1] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 1, &utf32Read, &utf16Written);

    // Not enough room for surrogate pair (needs 2 UTF16 units)
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Zero output buffer length
TEST_F(UTF32NatToUTF16NatTest_2075, ZeroOutputBufferLength_2075) {
    UTF32Unit utf32In[] = { 0x0041 };
    UTF16Unit utf16Out[1] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 0, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: BMP boundary value 0xFFFF
TEST_F(UTF32NatToUTF16NatTest_2075, BMPBoundaryMaxFFFF_2075) {
    UTF32Unit utf32In[] = { 0xFFFF };
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0xFFFF);
}

// Test: Just above BMP boundary (0x10000 requires surrogate)
TEST_F(UTF32NatToUTF16NatTest_2075, JustAboveBMPBoundary_2075) {
    UTF32Unit utf32In[] = { 0x10000 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: Multiple consecutive supplementary characters
TEST_F(UTF32NatToUTF16NatTest_2075, MultipleSupplementaryCharacters_2075) {
    UTF32Unit utf32In[] = { 0x10000, 0x10001, 0x10002 };
    UTF16Unit utf16Out[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 3, utf16Out, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 6u); // Each needs 2 UTF16 units
}

// Test: Supplementary followed by BMP
TEST_F(UTF32NatToUTF16NatTest_2075, SupplementaryFollowedByBMP_2075) {
    UTF32Unit utf32In[] = { 0x10000, 0x0041 };
    UTF16Unit utf16Out[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 2, utf16Out, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 3u); // 2 for surrogate + 1 for BMP
    EXPECT_EQ(utf16Out[2], 0x0041);
}

// Test: Output buffer exactly fits surrogate pair
TEST_F(UTF32NatToUTF16NatTest_2075, ExactFitSurrogatePair_2075) {
    UTF32Unit utf32In[] = { 0x10000 };
    UTF16Unit utf16Out[2] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 2, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: BMP followed by supplementary with limited output
TEST_F(UTF32NatToUTF16NatTest_2075, BMPThenSupplementaryLimitedOutput_2075) {
    UTF32Unit utf32In[] = { 0x0041, 0x10000 };
    UTF16Unit utf16Out[2] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 2, utf16Out, 2, &utf32Read, &utf16Written);

    // First BMP char uses 1, then only 1 left for surrogate (needs 2) -> stops
    // But actually the inner loop processes 1 BMP, then tries surrogate
    // Surrogate needs 2, only 1 left => goto Done
    // Actually let's check: after BMP, utf16Left=1, utf32Left=1
    // inner while checks inUnit > 0xFFFF -> true, calls CodePoint_to_UTF16Nat_Surrogate with utf16Left=1
    // that should return len=0 => goto Done
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x0041);
}

// Test: Large BMP sequence
TEST_F(UTF32NatToUTF16NatTest_2075, LargeBMPSequence_2075) {
    const size_t count = 100;
    std::vector<UTF32Unit> utf32In(count);
    for (size_t i = 0; i < count; ++i) {
        utf32In[i] = static_cast<UTF32Unit>(0x0030 + (i % 10)); // digits 0-9 repeating
    }
    std::vector<UTF16Unit> utf16Out(count + 10, 0);
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In.data(), count, utf16Out.data(), count + 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, count);
    EXPECT_EQ(utf16Written, count);
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(utf16Out[i], static_cast<UTF16Unit>(0x0030 + (i % 10)));
    }
}

// Test: U+10FFFF (maximum valid Unicode code point)
TEST_F(UTF32NatToUTF16NatTest_2075, MaxUnicodeCodePoint_2075) {
    UTF32Unit utf32In[] = { 0x10FFFF };
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+10FFFF: high surrogate = 0xDBFF, low surrogate = 0xDFFF
    EXPECT_EQ(utf16Out[0], 0xDBFF);
    EXPECT_EQ(utf16Out[1], 0xDFFF);
}

// Test: Null character (U+0000)
TEST_F(UTF32NatToUTF16NatTest_2075, NullCharacter_2075) {
    UTF32Unit utf32In[] = { 0x0000 };
    UTF16Unit utf16Out[4] = {0xFFFF};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x0000);
}

// Test: Alternating BMP and supplementary characters
TEST_F(UTF32NatToUTF16NatTest_2075, AlternatingBMPAndSupplementary_2075) {
    UTF32Unit utf32In[] = { 0x0041, 0x10000, 0x0042, 0x10001 };
    UTF16Unit utf16Out[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 4, utf16Out, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 4u);
    EXPECT_EQ(utf16Written, 6u); // 1 + 2 + 1 + 2
}

// Test: Output buffer size exactly matches needed for mixed content
TEST_F(UTF32NatToUTF16NatTest_2075, ExactOutputForMixedContent_2075) {
    UTF32Unit utf32In[] = { 0x0041, 0x10000 }; // needs 1 + 2 = 3 UTF16 units
    UTF16Unit utf16Out[3] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32Nat_to_UTF16Nat(utf32In, 2, utf16Out, 3, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(utf16Out[0], 0x0041);
}
