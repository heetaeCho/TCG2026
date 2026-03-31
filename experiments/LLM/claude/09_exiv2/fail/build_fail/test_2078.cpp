#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <stdexcept>

// Include necessary headers for the Unicode conversion functions
#include "XMP_Const.h"
#include "XMP_Environment.h"

// We need access to the static function, so we include the source
// First, set up any required macros/types
#ifndef TXMP_STRING_TYPE
#define TXMP_STRING_TYPE std::string
#endif

#include "source/UnicodeConversions.hpp"
#include "source/UnicodeConversions.cpp"

class CodePointFromUTF16SwpSurrogateTest_2078 : public ::testing::Test {
protected:
    UTF32Unit cpOut;
    size_t utf16Read;

    void SetUp() override {
        cpOut = 0;
        utf16Read = 0;
    }

    // Helper to create a byte-swapped UTF16 unit
    UTF16Unit swapBytes16(UTF16Unit val) {
        return static_cast<UTF16Unit>(((val & 0xFF) << 8) | ((val >> 8) & 0xFF));
    }
};

// Test: Valid surrogate pair (U+10000, the smallest supplementary character)
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, ValidSurrogatePair_MinSupplementary_2078) {
    // U+10000 => high surrogate 0xD800, low surrogate 0xDC00
    UTF16Unit input[2];
    input[0] = swapBytes16(0xD800);
    input[1] = swapBytes16(0xDC00);

    CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x10000));
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Valid surrogate pair (U+10FFFF, the maximum code point)
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, ValidSurrogatePair_MaxCodePoint_2078) {
    // U+10FFFF => high surrogate 0xDBFF, low surrogate 0xDFFF
    UTF16Unit input[2];
    input[0] = swapBytes16(0xDBFF);
    input[1] = swapBytes16(0xDFFF);

    CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x10FFFF));
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Valid surrogate pair for U+1D11E (Musical Symbol G Clef)
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, ValidSurrogatePair_GClef_2078) {
    // U+1D11E => high surrogate 0xD834, low surrogate 0xDD1E
    UTF16Unit input[2];
    input[0] = swapBytes16(0xD834);
    input[1] = swapBytes16(0xDD1E);

    CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x1D11E));
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Leading low surrogate (0xDC00-0xDFFF) should throw
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, LeadingLowSurrogate_Throws_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xDC00); // Low surrogate in high position
    input[1] = swapBytes16(0xDC00);

    EXPECT_THROW(
        CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Leading low surrogate at upper bound should throw
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, LeadingLowSurrogateUpperBound_Throws_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xDFFF); // Low surrogate in high position
    input[1] = swapBytes16(0xDC00);

    EXPECT_THROW(
        CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Insufficient input (utf16Len < 2) should set utf16Read to 0
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, InsufficientInput_ReadsZero_2078) {
    UTF16Unit input[1];
    input[0] = swapBytes16(0xD800);

    CodePoint_from_UTF16Swp_Surrogate(input, 1, &cpOut, &utf16Read);

    EXPECT_EQ(utf16Read, 0u);
}

// Test: Missing low surrogate (second unit is not in 0xDC00-0xDFFF range) should throw
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, MissingLowSurrogate_BelowRange_Throws_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xD800);
    input[1] = swapBytes16(0xDBFF); // Another high surrogate instead of low

    EXPECT_THROW(
        CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Missing low surrogate (second unit is regular character) should throw
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, MissingLowSurrogate_RegularChar_Throws_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xD800);
    input[1] = swapBytes16(0x0041); // 'A' - not a low surrogate

    EXPECT_THROW(
        CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Missing low surrogate (second unit is just above range) should throw
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, MissingLowSurrogate_AboveRange_Throws_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xD800);
    input[1] = swapBytes16(0xE000); // Just above low surrogate range

    EXPECT_THROW(
        CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Missing low surrogate (second unit is just below range) should throw
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, MissingLowSurrogate_JustBelowRange_Throws_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xD800);
    input[1] = swapBytes16(0xDBFF); // Just below low surrogate range (0xDC00)

    EXPECT_THROW(
        CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read),
        XMP_Error
    );
}

// Test: Boundary - high surrogate at D800 with low surrogate at DFFF
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, BoundarySurrogatePair_D800_DFFF_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xD800);
    input[1] = swapBytes16(0xDFFF);

    CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read);

    UTF32Unit expected = (((0xD800 & 0x3FF) << 10) | (0xDFFF & 0x3FF)) + 0x10000;
    EXPECT_EQ(cpOut, expected);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: Boundary - high surrogate at DBFF with low surrogate at DC00
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, BoundarySurrogatePair_DBFF_DC00_2078) {
    UTF16Unit input[2];
    input[0] = swapBytes16(0xDBFF);
    input[1] = swapBytes16(0xDC00);

    CodePoint_from_UTF16Swp_Surrogate(input, 2, &cpOut, &utf16Read);

    UTF32Unit expected = (((0xDBFF & 0x3FF) << 10) | (0xDC00 & 0x3FF)) + 0x10000;
    EXPECT_EQ(cpOut, expected);
    EXPECT_EQ(utf16Read, 2u);
}

// Test: utf16Len == 0 should set utf16Read to 0 (insufficient input)
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, ZeroLength_ReadsZero_2078) {
    UTF16Unit input[1];
    input[0] = swapBytes16(0xD800);

    CodePoint_from_UTF16Swp_Surrogate(input, 0, &cpOut, &utf16Read);

    EXPECT_EQ(utf16Read, 0u);
}

// Test: cpOut should not be modified when there's insufficient input
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, InsufficientInput_CpOutUnchanged_2078) {
    UTF16Unit input[1];
    input[0] = swapBytes16(0xD800);
    cpOut = 0x12345678; // Set to known value

    CodePoint_from_UTF16Swp_Surrogate(input, 1, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x12345678)); // Should remain unchanged
    EXPECT_EQ(utf16Read, 0u);
}

// Test: Extra length beyond 2 should still work correctly
TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, ExtraLength_StillReadsTwo_2078) {
    UTF16Unit input[4];
    input[0] = swapBytes16(0xD800);
    input[1] = swapBytes16(0xDC00);
    input[2] = swapBytes16(0x0041);
    input[3] = swapBytes16(0x0042);

    CodePoint_from_UTF16Swp_Surrogate(input, 4, &cpOut, &utf16Read);

    EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x10000));
    EXPECT_EQ(utf16Read, 2u);
}
