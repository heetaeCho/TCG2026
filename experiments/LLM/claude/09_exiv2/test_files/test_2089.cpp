#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include <vector>

// Include the implementation file since the function is static
// We need the types and the function
#include "xmpsdk/src/UnicodeConversions.cpp"

// Helper to byte-swap a 32-bit value to create swapped input
static UTF32Unit SwapUTF32(UTF32Unit val) {
    return ((val & 0xFF) << 24) |
           ((val & 0xFF00) << 8) |
           ((val & 0xFF0000) >> 8) |
           ((val & 0xFF000000) >> 24);
}

class UTF32SwpToUTF16NatTest_2089 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic ASCII character conversion (BMP, single unit)
TEST_F(UTF32SwpToUTF16NatTest_2089, BasicASCIIConversion_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041) }; // 'A'
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(output[0], 0x0041);
}

// Test multiple BMP characters
TEST_F(UTF32SwpToUTF16NatTest_2089, MultipleBMPCharacters_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0048), SwapUTF32(0x0065), SwapUTF32(0x006C) }; // H, e, l
    UTF16Unit output[10] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 3, output, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(output[0], 0x0048);
    EXPECT_EQ(output[1], 0x0065);
    EXPECT_EQ(output[2], 0x006C);
}

// Test supplementary character (requires surrogate pair in UTF-16)
TEST_F(UTF32SwpToUTF16NatTest_2089, SupplementaryCharacter_2089) {
    // U+10000 (first supplementary character)
    UTF32Unit input[] = { SwapUTF32(0x10000) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+10000 -> surrogate pair: D800 DC00
    EXPECT_EQ(output[0], 0xD800);
    EXPECT_EQ(output[1], 0xDC00);
}

// Test emoji character U+1F600 (supplementary)
TEST_F(UTF32SwpToUTF16NatTest_2089, EmojiSupplementaryCharacter_2089) {
    UTF32Unit input[] = { SwapUTF32(0x1F600) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+1F600 -> D83D DE00
    EXPECT_EQ(output[0], 0xD83D);
    EXPECT_EQ(output[1], 0xDE00);
}

// Test mixed BMP and supplementary characters
TEST_F(UTF32SwpToUTF16NatTest_2089, MixedBMPAndSupplementary_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041), SwapUTF32(0x10000), SwapUTF32(0x0042) };
    UTF16Unit output[10] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 3, output, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 4u); // 1 + 2 + 1
    EXPECT_EQ(output[0], 0x0041);
    EXPECT_EQ(output[1], 0xD800);
    EXPECT_EQ(output[2], 0xDC00);
    EXPECT_EQ(output[3], 0x0042);
}

// Test zero-length input
TEST_F(UTF32SwpToUTF16NatTest_2089, ZeroLengthInput_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 0, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test zero-length output buffer
TEST_F(UTF32SwpToUTF16NatTest_2089, ZeroLengthOutput_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041) };
    UTF16Unit output[1] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 0, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test output buffer too small for surrogate pair
TEST_F(UTF32SwpToUTF16NatTest_2089, OutputBufferTooSmallForSurrogate_2089) {
    // Supplementary character needs 2 UTF-16 units, but only 1 available
    UTF32Unit input[] = { SwapUTF32(0x10000) };
    UTF16Unit output[1] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 1, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test output buffer exactly fits BMP characters
TEST_F(UTF32SwpToUTF16NatTest_2089, OutputBufferExactFitBMP_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041), SwapUTF32(0x0042), SwapUTF32(0x0043) };
    UTF16Unit output[3] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 3, output, 3, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
}

// Test output buffer smaller than input (truncation)
TEST_F(UTF32SwpToUTF16NatTest_2089, OutputBufferSmallerThanInput_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041), SwapUTF32(0x0042), SwapUTF32(0x0043) };
    UTF16Unit output[2] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 3, output, 2, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(output[0], 0x0041);
    EXPECT_EQ(output[1], 0x0042);
}

// Test BMP boundary value 0xFFFF
TEST_F(UTF32SwpToUTF16NatTest_2089, BMPBoundaryValueFFFF_2089) {
    UTF32Unit input[] = { SwapUTF32(0xFFFF) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(output[0], 0xFFFF);
}

// Test first supplementary value 0x10000 (just above BMP)
TEST_F(UTF32SwpToUTF16NatTest_2089, FirstSupplementaryValue_2089) {
    UTF32Unit input[] = { SwapUTF32(0x10000) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
}

// Test maximum valid Unicode code point U+10FFFF
TEST_F(UTF32SwpToUTF16NatTest_2089, MaxUnicodeCodePoint_2089) {
    UTF32Unit input[] = { SwapUTF32(0x10FFFF) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    // U+10FFFF -> DBFF DFFF
    EXPECT_EQ(output[0], 0xDBFF);
    EXPECT_EQ(output[1], 0xDFFF);
}

// Test null character (U+0000)
TEST_F(UTF32SwpToUTF16NatTest_2089, NullCharacter_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0000) };
    UTF16Unit output[4] = {0xFFFF};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(output[0], 0x0000);
}

// Test multiple supplementary characters
TEST_F(UTF32SwpToUTF16NatTest_2089, MultipleSupplementaryCharacters_2089) {
    UTF32Unit input[] = { SwapUTF32(0x10000), SwapUTF32(0x10001) };
    UTF16Unit output[10] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 2, output, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 4u);
    EXPECT_EQ(output[0], 0xD800);
    EXPECT_EQ(output[1], 0xDC00);
    EXPECT_EQ(output[2], 0xD800);
    EXPECT_EQ(output[3], 0xDC01);
}

// Test supplementary followed by BMP
TEST_F(UTF32SwpToUTF16NatTest_2089, SupplementaryThenBMP_2089) {
    UTF32Unit input[] = { SwapUTF32(0x10000), SwapUTF32(0x0041) };
    UTF16Unit output[10] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 2, output, 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(output[0], 0xD800);
    EXPECT_EQ(output[1], 0xDC00);
    EXPECT_EQ(output[2], 0x0041);
}

// Test output buffer exactly fits one surrogate pair but no more
TEST_F(UTF32SwpToUTF16NatTest_2089, OutputExactlyFitsSurrogatePair_2089) {
    UTF32Unit input[] = { SwapUTF32(0x10000), SwapUTF32(0x0041) };
    UTF16Unit output[2] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 2, output, 2, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(output[0], 0xD800);
    EXPECT_EQ(output[1], 0xDC00);
}

// Test CJK character in BMP (e.g., U+4E2D - Chinese "middle")
TEST_F(UTF32SwpToUTF16NatTest_2089, CJKCharacter_2089) {
    UTF32Unit input[] = { SwapUTF32(0x4E2D) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(output[0], 0x4E2D);
}

// Test large input with only BMP characters
TEST_F(UTF32SwpToUTF16NatTest_2089, LargeInputBMPOnly_2089) {
    const size_t count = 100;
    std::vector<UTF32Unit> input(count);
    for (size_t i = 0; i < count; ++i) {
        input[i] = SwapUTF32(0x0041 + (i % 26));
    }
    std::vector<UTF16Unit> output(count + 10, 0);
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input.data(), count, output.data(), count + 10, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, count);
    EXPECT_EQ(utf16Written, count);
}

// Test BMP then supplementary with limited output (BMP fits but supplementary doesn't)
TEST_F(UTF32SwpToUTF16NatTest_2089, BMPFitsButSupplementaryDoesNot_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041), SwapUTF32(0x10000) };
    UTF16Unit output[2] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 2, output, 2, &utf32Read, &utf16Written);

    // 'A' takes 1 unit, supplementary needs 2 more but only 1 left
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(output[0], 0x0041);
}

// Test with output buffer exactly 3 for BMP + supplementary
TEST_F(UTF32SwpToUTF16NatTest_2089, ExactBufferForBMPPlusSurrogate_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0041), SwapUTF32(0x10000) };
    UTF16Unit output[3] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 2, output, 3, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(output[0], 0x0041);
    EXPECT_EQ(output[1], 0xD800);
    EXPECT_EQ(output[2], 0xDC00);
}

// Test single character U+0001 (minimum non-null)
TEST_F(UTF32SwpToUTF16NatTest_2089, MinimumNonNullCharacter_2089) {
    UTF32Unit input[] = { SwapUTF32(0x0001) };
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0, utf16Written = 0;

    UTF32Swp_to_UTF16Nat(input, 1, output, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(output[0], 0x0001);
}
