#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the implementation to access internal functions
// We need to make static functions accessible for testing
#define static
#include "UnicodeConversions.cpp"
#undef static

class UTF32SwpToUTF16SwpTest_2085 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic BMP character conversion
TEST_F(UTF32SwpToUTF16SwpTest_2085, BasicBMPConversion_2085) {
    // Prepare a swapped UTF-32 'A' (0x00000041)
    // Swapped means bytes are reversed
    UTF32Unit input[1];
    input[0] = 0x41000000; // 'A' byte-swapped
    
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
}

// Test empty input
TEST_F(UTF32SwpToUTF16SwpTest_2085, EmptyInput_2085) {
    UTF32Unit input[1] = {0};
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 0, output, 4, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test empty output buffer
TEST_F(UTF32SwpToUTF16SwpTest_2085, EmptyOutputBuffer_2085) {
    UTF32Unit input[1];
    input[0] = 0x41000000;
    
    UTF16Unit output[1] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 0, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test multiple BMP characters
TEST_F(UTF32SwpToUTF16SwpTest_2085, MultipleBMPCharacters_2085) {
    UTF32Unit input[3];
    input[0] = 0x41000000; // 'A' swapped
    input[1] = 0x42000000; // 'B' swapped
    input[2] = 0x43000000; // 'C' swapped
    
    UTF16Unit output[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 3, output, 10, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
}

// Test supplementary character (surrogate pair needed) - code point > 0xFFFF
TEST_F(UTF32SwpToUTF16SwpTest_2085, SupplementaryCharacterSurrogatePair_2085) {
    // U+10000 byte-swapped: 0x00010000 -> 0x00000100
    UTF32Unit input[1];
    input[0] = 0x00000100; // U+10000 swapped (0x00010000 byte-swapped)
    
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u); // Surrogate pair = 2 UTF-16 units
}

// Test surrogate pair with insufficient output space
TEST_F(UTF32SwpToUTF16SwpTest_2085, SurrogatePairInsufficientOutput_2085) {
    // U+10000 byte-swapped
    UTF32Unit input[1];
    input[0] = 0x00000100; // U+10000 swapped
    
    UTF16Unit output[1] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 1, &utf32Read, &utf16Written);
    
    // Not enough room for surrogate pair (needs 2, only 1 available)
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test mixed BMP and supplementary characters
TEST_F(UTF32SwpToUTF16SwpTest_2085, MixedBMPAndSupplementary_2085) {
    UTF32Unit input[3];
    input[0] = 0x41000000; // 'A' swapped (BMP)
    input[1] = 0x00000100; // U+10000 swapped (supplementary)
    input[2] = 0x42000000; // 'B' swapped (BMP)
    
    UTF16Unit output[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 3, output, 10, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 4u); // 1 + 2 + 1
}

// Test output buffer exactly fits BMP characters
TEST_F(UTF32SwpToUTF16SwpTest_2085, OutputBufferExactFitBMP_2085) {
    UTF32Unit input[3];
    input[0] = 0x41000000;
    input[1] = 0x42000000;
    input[2] = 0x43000000;
    
    UTF16Unit output[3] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 3, output, 3, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
}

// Test output buffer too small for all input
TEST_F(UTF32SwpToUTF16SwpTest_2085, OutputBufferTooSmall_2085) {
    UTF32Unit input[5];
    for (int i = 0; i < 5; i++) {
        input[i] = 0x41000000; // 'A' swapped
    }
    
    UTF16Unit output[3] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 5, output, 3, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
}

// Test single character
TEST_F(UTF32SwpToUTF16SwpTest_2085, SingleCharacter_2085) {
    UTF32Unit input[1];
    input[0] = 0x41000000;
    
    UTF16Unit output[1] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 1, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
}

// Test supplementary character exactly fits output buffer of size 2
TEST_F(UTF32SwpToUTF16SwpTest_2085, SurrogatePairExactFit_2085) {
    UTF32Unit input[1];
    input[0] = 0x00000100; // U+10000 swapped
    
    UTF16Unit output[2] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 2, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
}

// Test consecutive supplementary characters
TEST_F(UTF32SwpToUTF16SwpTest_2085, ConsecutiveSupplementaryCharacters_2085) {
    UTF32Unit input[2];
    input[0] = 0x00000100; // U+10000 swapped
    input[1] = 0x01000100; // U+10001 swapped
    
    UTF16Unit output[10] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 2, output, 10, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 2u);
    EXPECT_EQ(utf16Written, 4u); // 2 surrogate pairs
}

// Test BMP boundary value 0xFFFF (max BMP, swapped)
TEST_F(UTF32SwpToUTF16SwpTest_2085, BMPBoundaryMaxValue_2085) {
    UTF32Unit input[1];
    input[0] = 0xFFFF0000; // 0x0000FFFF swapped
    
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 1u); // Still BMP, no surrogate needed
}

// Test value just above BMP boundary (0x10000 swapped)
TEST_F(UTF32SwpToUTF16SwpTest_2085, JustAboveBMPBoundary_2085) {
    UTF32Unit input[1];
    input[0] = 0x00000100; // 0x00010000 swapped
    
    UTF16Unit output[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;
    
    UTF32Swp_to_UTF16Swp(input, 1, output, 4, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u); // Surrogate pair needed
}

// Test that read and written counts are zero-initialized correctly on empty
TEST_F(UTF32SwpToUTF16SwpTest_2085, ZeroLengthBothBuffers_2085) {
    UTF32Unit input[1] = {0};
    UTF16Unit output[1] = {0};
    size_t utf32Read = 99;
    size_t utf16Written = 99;
    
    UTF32Swp_to_UTF16Swp(input, 0, output, 0, &utf32Read, &utf16Written);
    
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}
