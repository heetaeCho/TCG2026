#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <climits>

// Include the implementation file directly since the function is static
// We need access to the types and the static function
#include "xmpsdk/src/UnicodeConversions.cpp"

class UTF32NatToUTF16SwpTest_2088 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to swap bytes of a UTF16Unit
static UTF16Unit SwapUTF16(UTF16Unit val) {
    return static_cast<UTF16Unit>(((val >> 8) & 0xFF) | ((val & 0xFF) << 8));
}

// Test: Single BMP character conversion
TEST_F(UTF32NatToUTF16SwpTest_2088, SingleBMPCharacter_2088) {
    UTF32Unit input[] = { 0x0041 }; // 'A'
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(SwapUTF16(output[0]), 0x0041);
}

// Test: Multiple BMP characters
TEST_F(UTF32NatToUTF16SwpTest_2088, MultipleBMPCharacters_2088) {
    UTF32Unit input[] = { 0x0041, 0x0042, 0x0043 }; // 'A', 'B', 'C'
    UTF16Unit output[8] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 3, output, 8, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(SwapUTF16(output[0]), 0x0041);
    EXPECT_EQ(SwapUTF16(output[1]), 0x0042);
    EXPECT_EQ(SwapUTF16(output[2]), 0x0043);
}

// Test: Supplementary character requiring surrogate pair
TEST_F(UTF32NatToUTF16SwpTest_2088, SupplementaryCharacterSurrogatePair_2088) {
    UTF32Unit input[] = { 0x10000 }; // First supplementary character
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+10000 -> high surrogate 0xD800, low surrogate 0xDC00
    EXPECT_EQ(SwapUTF16(output[0]), 0xD800);
    EXPECT_EQ(SwapUTF16(output[1]), 0xDC00);
}

// Test: Mixed BMP and supplementary characters
TEST_F(UTF32NatToUTF16SwpTest_2088, MixedBMPAndSupplementary_2088) {
    UTF32Unit input[] = { 0x0041, 0x10000, 0x0042 };
    UTF16Unit output[8] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 3, output, 8, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 4u); // 1 + 2 + 1
    EXPECT_EQ(SwapUTF16(output[0]), 0x0041);
    EXPECT_EQ(SwapUTF16(output[1]), 0xD800);
    EXPECT_EQ(SwapUTF16(output[2]), 0xDC00);
    EXPECT_EQ(SwapUTF16(output[3]), 0x0042);
}

// Test: Empty input (zero length)
TEST_F(UTF32NatToUTF16SwpTest_2088, EmptyInput_2088) {
    UTF32Unit input[] = { 0x0041 };
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 0, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Zero output buffer length
TEST_F(UTF32NatToUTF16SwpTest_2088, ZeroOutputLength_2088) {
    UTF32Unit input[] = { 0x0041 };
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 0, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Output buffer too small for surrogate pair
TEST_F(UTF32NatToUTF16SwpTest_2088, OutputTooSmallForSurrogatePair_2088) {
    UTF32Unit input[] = { 0x10000 };
    UTF16Unit output[1] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 1, &utf32Read, &utf16Written);

    // Not enough room for surrogate pair (needs 2 UTF16 units)
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Output buffer exactly fits surrogate pair
TEST_F(UTF32NatToUTF16SwpTest_2088, OutputExactlyFitsSurrogatePair_2088) {
    UTF32Unit input[] = { 0x10000 };
    UTF16Unit output[2] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 2, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(SwapUTF16(output[0]), 0xD800);
    EXPECT_EQ(SwapUTF16(output[1]), 0xDC00);
}

// Test: BMP character at boundary 0xFFFF
TEST_F(UTF32NatToUTF16SwpTest_2088, BMPBoundaryCharacter_2088) {
    UTF32Unit input[] = { 0xFFFF };
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(SwapUTF16(output[0]), 0xFFFF);
}

// Test: Character just above BMP (0x10000)
TEST_F(UTF32NatToUTF16SwpTest_2088, JustAboveBMP_2088) {
    UTF32Unit input[] = { 0x10000 };
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: Large supplementary character U+10FFFF (max Unicode)
TEST_F(UTF32NatToUTF16SwpTest_2088, MaxUnicodeCodePoint_2088) {
    UTF32Unit input[] = { 0x10FFFF };
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+10FFFF -> high surrogate 0xDBFF, low surrogate 0xDFFF
    EXPECT_EQ(SwapUTF16(output[0]), 0xDBFF);
    EXPECT_EQ(SwapUTF16(output[1]), 0xDFFF);
}

// Test: Multiple supplementary characters with limited output
TEST_F(UTF32NatToUTF16SwpTest_2088, MultipleSupplementaryLimitedOutput_2088) {
    UTF32Unit input[] = { 0x10000, 0x10001 };
    UTF16Unit output[3] = { 0 }; // Only room for one surrogate pair + 1
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 2, output, 3, &utf32Read, &utf16Written);

    // First surrogate pair takes 2 units, second needs 2 but only 1 left
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: Supplementary character U+1F600 (emoji)
TEST_F(UTF32NatToUTF16SwpTest_2088, EmojiCharacter_2088) {
    UTF32Unit input[] = { 0x1F600 }; // 😀
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+1F600 -> high surrogate 0xD83D, low surrogate 0xDE00
    EXPECT_EQ(SwapUTF16(output[0]), 0xD83D);
    EXPECT_EQ(SwapUTF16(output[1]), 0xDE00);
}

// Test: Single BMP character with exact output size
TEST_F(UTF32NatToUTF16SwpTest_2088, ExactOutputForBMP_2088) {
    UTF32Unit input[] = { 0x0041 };
    UTF16Unit output[1] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 1, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(SwapUTF16(output[0]), 0x0041);
}

// Test: Output limited, partial conversion of BMP
TEST_F(UTF32NatToUTF16SwpTest_2088, PartialBMPConversion_2088) {
    UTF32Unit input[] = { 0x0041, 0x0042, 0x0043 };
    UTF16Unit output[2] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 3, output, 2, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(SwapUTF16(output[0]), 0x0041);
    EXPECT_EQ(SwapUTF16(output[1]), 0x0042);
}

// Test: BMP followed by supplementary, output limited before supplementary
TEST_F(UTF32NatToUTF16SwpTest_2088, BMPThenSupplementaryOutputLimited_2088) {
    UTF32Unit input[] = { 0x0041, 0x10000 };
    UTF16Unit output[2] = { 0 }; // Room for BMP + 1 (not enough for surrogate pair)
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 2, output, 2, &utf32Read, &utf16Written);

    // BMP 'A' takes 1, then supplementary needs 2 but only 1 left
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: Null character (U+0000)
TEST_F(UTF32NatToUTF16SwpTest_2088, NullCharacter_2088) {
    UTF32Unit input[] = { 0x0000 };
    UTF16Unit output[4] = { 0xFFFF };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(SwapUTF16(output[0]), 0x0000);
}

// Test: Byte swap verification - ensure output is actually swapped
TEST_F(UTF32NatToUTF16SwpTest_2088, ByteSwapVerification_2088) {
    UTF32Unit input[] = { 0x0102 }; // Asymmetric bytes for swap detection
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    // The output should be byte-swapped: 0x0102 swapped is 0x0201
    EXPECT_EQ(output[0], 0x0201);
}

// Test: Multiple consecutive supplementary characters
TEST_F(UTF32NatToUTF16SwpTest_2088, MultipleSupplementaryCharacters_2088) {
    UTF32Unit input[] = { 0x10000, 0x10001, 0x10002 };
    UTF16Unit output[8] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 3, output, 8, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 6u); // 3 * 2 surrogate pairs
}

// Test: Supplementary followed by BMP
TEST_F(UTF32NatToUTF16SwpTest_2088, SupplementaryFollowedByBMP_2088) {
    UTF32Unit input[] = { 0x10000, 0x0041 };
    UTF16Unit output[8] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 2, output, 8, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 3u); // 2 for surrogate + 1 for BMP
    EXPECT_EQ(SwapUTF16(output[2]), 0x0041);
}

// Test: Large number of BMP characters
TEST_F(UTF32NatToUTF16SwpTest_2088, LargeNumberOfBMPChars_2088) {
    const size_t count = 256;
    std::vector<UTF32Unit> input(count);
    std::vector<UTF16Unit> output(count, 0);
    for (size_t i = 0; i < count; ++i) {
        input[i] = static_cast<UTF32Unit>(0x0020 + (i % 95)); // Printable ASCII range
    }
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input.data(), count, output.data(), count, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, count);
    EXPECT_EQ(utf16Written, count);
}

// Test: Output buffer exactly 4 for two supplementary characters
TEST_F(UTF32NatToUTF16SwpTest_2088, ExactOutputForTwoSupplementary_2088) {
    UTF32Unit input[] = { 0x10000, 0x10001 };
    UTF16Unit output[4] = { 0 };
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Nat_to_UTF16Swp(input, 2, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 4u);
}
