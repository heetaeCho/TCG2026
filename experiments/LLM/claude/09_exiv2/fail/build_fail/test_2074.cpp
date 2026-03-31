#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <vector>

// Include the implementation file to access the static function
// We need the types and the function
namespace {
    typedef uint16_t UTF16Unit;
    typedef uint32_t UTF32Unit;
    typedef uint32_t CodePoint;
}

// Since UTF16Nat_to_UTF32Nat is static, we include the source to get access
// We need to handle the dependencies
#include "xmpsdk/include/UnicodeConversions.hpp"

// If direct inclusion doesn't work, we test through the public API
// The public API typically provides functions like UTF16_to_UTF32

class UTF16NatToUTF32NatTest_2074 : public ::testing::Test {
protected:
    static const size_t kMaxUTF32 = 256;
    static const size_t kMaxUTF16 = 512;
    
    UTF32Unit utf32Out[256];
    size_t utf16Read;
    size_t utf32Written;
    
    void SetUp() override {
        memset(utf32Out, 0, sizeof(utf32Out));
        utf16Read = 0;
        utf32Written = 0;
    }
};

// Test basic ASCII conversion (BMP characters below 0xD800)
TEST_F(UTF16NatToUTF32NatTest_2074, BasicASCIIConversion_2074) {
    UTF16Unit input[] = { 0x0041, 0x0042, 0x0043 }; // A, B, C
    size_t inputLen = 3;
    size_t outputLen = 3;
    
    UTF16Nat_to_UTF32Nat(input, inputLen, utf32Out, outputLen, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
    EXPECT_EQ(utf32Out[1], 0x0042u);
    EXPECT_EQ(utf32Out[2], 0x0043u);
}

// Test empty input
TEST_F(UTF16NatToUTF32NatTest_2074, EmptyInput_2074) {
    UTF16Unit input[] = { 0x0041 };
    
    UTF16Nat_to_UTF32Nat(input, 0, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test zero output buffer length
TEST_F(UTF16NatToUTF32NatTest_2074, ZeroOutputBuffer_2074) {
    UTF16Unit input[] = { 0x0041, 0x0042 };
    
    UTF16Nat_to_UTF32Nat(input, 2, utf32Out, 0, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test surrogate pair conversion (U+10000 = D800 DC00)
TEST_F(UTF16NatToUTF32NatTest_2074, SurrogatePairConversion_2074) {
    UTF16Unit input[] = { 0xD800, 0xDC00 }; // U+10000
    
    UTF16Nat_to_UTF32Nat(input, 2, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x10000u);
}

// Test surrogate pair for U+10FFFF (DBFF DFFF)
TEST_F(UTF16NatToUTF32NatTest_2074, MaxSurrogatePair_2074) {
    UTF16Unit input[] = { 0xDBFF, 0xDFFF }; // U+10FFFF
    
    UTF16Nat_to_UTF32Nat(input, 2, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x10FFFFu);
}

// Test mixed BMP and surrogate pairs
TEST_F(UTF16NatToUTF32NatTest_2074, MixedBMPAndSurrogates_2074) {
    UTF16Unit input[] = { 0x0041, 0xD800, 0xDC00, 0x0042 }; // A, U+10000, B
    
    UTF16Nat_to_UTF32Nat(input, 4, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
    EXPECT_EQ(utf32Out[1], 0x10000u);
    EXPECT_EQ(utf32Out[2], 0x0042u);
}

// Test output buffer smaller than needed (truncation at BMP)
TEST_F(UTF16NatToUTF32NatTest_2074, OutputBufferTooSmallBMP_2074) {
    UTF16Unit input[] = { 0x0041, 0x0042, 0x0043 };
    
    UTF16Nat_to_UTF32Nat(input, 3, utf32Out, 2, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
    EXPECT_EQ(utf32Out[1], 0x0042u);
}

// Test incomplete surrogate pair (only high surrogate, input ends)
TEST_F(UTF16NatToUTF32NatTest_2074, IncompleteSurrogatePair_2074) {
    UTF16Unit input[] = { 0xD800 }; // Only high surrogate, no low
    
    UTF16Nat_to_UTF32Nat(input, 1, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    // Should stop because input ends in the middle of a surrogate pair
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test BMP characters just below surrogate range
TEST_F(UTF16NatToUTF32NatTest_2074, BMPBelowSurrogateRange_2074) {
    UTF16Unit input[] = { 0xD7FF }; // Just below surrogate range
    
    UTF16Nat_to_UTF32Nat(input, 1, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0xD7FFu);
}

// Test BMP characters just above surrogate range
TEST_F(UTF16NatToUTF32NatTest_2074, BMPAboveSurrogateRange_2074) {
    UTF16Unit input[] = { 0xE000 }; // Just above surrogate range
    
    UTF16Nat_to_UTF32Nat(input, 1, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0xE000u);
}

// Test multiple surrogate pairs in sequence
TEST_F(UTF16NatToUTF32NatTest_2074, MultipleSurrogatePairs_2074) {
    UTF16Unit input[] = { 0xD800, 0xDC00, 0xD801, 0xDC01 }; // U+10000, U+10401
    
    UTF16Nat_to_UTF32Nat(input, 4, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], 0x10000u);
    EXPECT_EQ(utf32Out[1], 0x10401u);
}

// Test output buffer exactly 1 with surrogate pair input
TEST_F(UTF16NatToUTF32NatTest_2074, OutputBufferOneWithSurrogate_2074) {
    UTF16Unit input[] = { 0xD800, 0xDC00, 0x0041 };
    
    UTF16Nat_to_UTF32Nat(input, 3, utf32Out, 1, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x10000u);
}

// Test single BMP character
TEST_F(UTF16NatToUTF32NatTest_2074, SingleBMPCharacter_2074) {
    UTF16Unit input[] = { 0x4E2D }; // Chinese character
    
    UTF16Nat_to_UTF32Nat(input, 1, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x4E2Du);
}

// Test null character (U+0000)
TEST_F(UTF16NatToUTF32NatTest_2074, NullCharacter_2074) {
    UTF16Unit input[] = { 0x0000 };
    
    UTF16Nat_to_UTF32Nat(input, 1, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x0000u);
}

// Test BMP followed by incomplete surrogate at end of input
TEST_F(UTF16NatToUTF32NatTest_2074, BMPFollowedByIncompleteSurrogate_2074) {
    UTF16Unit input[] = { 0x0041, 0xD800 }; // A, then lone high surrogate
    
    UTF16Nat_to_UTF32Nat(input, 2, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    // Should convert A and then stop at the incomplete surrogate
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
}

// Test U+FFFF (max BMP value, not a surrogate)
TEST_F(UTF16NatToUTF32NatTest_2074, MaxBMPValue_2074) {
    UTF16Unit input[] = { 0xFFFF };
    
    UTF16Nat_to_UTF32Nat(input, 1, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0xFFFFu);
}

// Test large input with all BMP characters
TEST_F(UTF16NatToUTF32NatTest_2074, LargeBMPInput_2074) {
    const size_t count = 100;
    std::vector<UTF16Unit> input(count);
    for (size_t i = 0; i < count; ++i) {
        input[i] = static_cast<UTF16Unit>(0x0041 + (i % 26));
    }
    
    UTF32Unit largeOut[100];
    memset(largeOut, 0, sizeof(largeOut));
    
    UTF16Nat_to_UTF32Nat(input.data(), count, largeOut, count, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, count);
    EXPECT_EQ(utf32Written, count);
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(largeOut[i], static_cast<UTF32Unit>(0x0041 + (i % 26)));
    }
}

// Test surrogate pair U+1F600 (emoji grinning face) = D83D DE00
TEST_F(UTF16NatToUTF32NatTest_2074, EmojiSurrogatePair_2074) {
    UTF16Unit input[] = { 0xD83D, 0xDE00 }; // U+1F600
    
    UTF16Nat_to_UTF32Nat(input, 2, utf32Out, kMaxUTF32, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x1F600u);
}

// Test output buffer size exactly matches needed for surrogates
TEST_F(UTF16NatToUTF32NatTest_2074, ExactOutputForSurrogates_2074) {
    UTF16Unit input[] = { 0xD800, 0xDC00, 0xD801, 0xDC01 };
    
    UTF16Nat_to_UTF32Nat(input, 4, utf32Out, 2, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 2u);
}

// Test output buffer has room for only 1 when 2 surrogate pairs present
TEST_F(UTF16NatToUTF32NatTest_2074, OutputBufferLimitsConversion_2074) {
    UTF16Unit input[] = { 0xD800, 0xDC00, 0xD801, 0xDC01 };
    
    UTF16Nat_to_UTF32Nat(input, 4, utf32Out, 1, &utf16Read, &utf32Written);
    
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x10000u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
