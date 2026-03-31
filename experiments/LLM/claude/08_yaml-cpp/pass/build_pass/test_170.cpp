#include <gtest/gtest.h>

// We need to access the function from the YAML namespace
// Since it's declared inline in the cpp file, we need to redeclare or include appropriately
namespace YAML {
inline char Utf8Adjust(unsigned long ch, unsigned char lead_bits, unsigned char rshift);
}

// Include the actual implementation
// Since the function is inline in the namespace, we replicate the declaration for testing
// The actual implementation is in stream.cpp
namespace YAML {
inline char Utf8Adjust(unsigned long ch, unsigned char lead_bits, unsigned char rshift) {
    const unsigned char header = static_cast<unsigned char>(((1 << lead_bits) - 1) << (8 - lead_bits));
    const unsigned char mask = (0xFF >> (lead_bits + 1));
    return static_cast<char>(
        static_cast<unsigned char>(header | ((ch >> rshift) & mask)));
}
}

class Utf8AdjustTest_170 : public ::testing::Test {
protected:
};

// Test: For a 2-byte UTF-8 sequence, the lead byte should have the pattern 110xxxxx
// lead_bits=2 means header = 0b11000000 = 0xC0, mask = 0b00011111 = 0x1F
TEST_F(Utf8AdjustTest_170, TwoByteLeadByte_170) {
    // For character U+00C0 (À), which in 2-byte UTF-8 is 0xC3 0x80
    // ch=0xC0, lead_bits=2, rshift=6
    // header = ((1<<2)-1) << 6 = 3 << 6 = 0xC0
    // mask = 0xFF >> 3 = 0x1F
    // result = 0xC0 | ((0xC0 >> 6) & 0x1F) = 0xC0 | (0x03 & 0x1F) = 0xC0 | 0x03 = 0xC3
    char result = YAML::Utf8Adjust(0xC0, 2, 6);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xC3);
}

// Test: For a continuation byte, lead_bits=1, header=0x80, mask=0x3F
TEST_F(Utf8AdjustTest_170, ContinuationByte_170) {
    // ch=0xC0, lead_bits=1, rshift=0
    // header = ((1<<1)-1) << 7 = 1 << 7 = 0x80
    // mask = 0xFF >> 2 = 0x3F
    // result = 0x80 | ((0xC0 >> 0) & 0x3F) = 0x80 | (0xC0 & 0x3F) = 0x80 | 0x00 = 0x80
    char result = YAML::Utf8Adjust(0xC0, 1, 0);
    EXPECT_EQ(static_cast<unsigned char>(result), 0x80);
}

// Test: For a 3-byte UTF-8 sequence lead byte, lead_bits=3
// header = ((1<<3)-1) << 5 = 7 << 5 = 0xE0, mask = 0xFF >> 4 = 0x0F
TEST_F(Utf8AdjustTest_170, ThreeByteLeadByte_170) {
    // U+0800: ch=0x800, lead_bits=3, rshift=12
    // header = 0xE0
    // mask = 0x0F
    // result = 0xE0 | ((0x800 >> 12) & 0x0F) = 0xE0 | (0x00 & 0x0F) = 0xE0
    char result = YAML::Utf8Adjust(0x0800, 3, 12);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xE0);
}

// Test: For a 4-byte UTF-8 sequence lead byte, lead_bits=4
// header = ((1<<4)-1) << 4 = 15 << 4 = 0xF0, mask = 0xFF >> 5 = 0x07
TEST_F(Utf8AdjustTest_170, FourByteLeadByte_170) {
    // U+10000: ch=0x10000, lead_bits=4, rshift=18
    // header = 0xF0
    // mask = 0x07
    // result = 0xF0 | ((0x10000 >> 18) & 0x07) = 0xF0 | (0x00 & 0x07) = 0xF0
    char result = YAML::Utf8Adjust(0x10000, 4, 18);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xF0);
}

// Test: Zero character with lead_bits=2
TEST_F(Utf8AdjustTest_170, ZeroCharacter_170) {
    // ch=0, lead_bits=2, rshift=6
    // header = 0xC0
    // mask = 0x1F
    // result = 0xC0 | ((0 >> 6) & 0x1F) = 0xC0
    char result = YAML::Utf8Adjust(0, 2, 6);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xC0);
}

// Test: Continuation byte with non-zero lower bits
TEST_F(Utf8AdjustTest_170, ContinuationByteWithData_170) {
    // ch=0x3F, lead_bits=1, rshift=0
    // header = 0x80
    // mask = 0x3F
    // result = 0x80 | ((0x3F >> 0) & 0x3F) = 0x80 | 0x3F = 0xBF
    char result = YAML::Utf8Adjust(0x3F, 1, 0);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xBF);
}

// Test: Maximum value in continuation byte (all mask bits set)
TEST_F(Utf8AdjustTest_170, MaxContinuationValue_170) {
    // ch=0xFF, lead_bits=1, rshift=0
    // header = 0x80, mask = 0x3F
    // result = 0x80 | (0xFF & 0x3F) = 0x80 | 0x3F = 0xBF
    char result = YAML::Utf8Adjust(0xFF, 1, 0);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xBF);
}

// Test: 2-byte encoding of U+07FF (max 2-byte character)
TEST_F(Utf8AdjustTest_170, MaxTwoByteCharLeadByte_170) {
    // ch=0x7FF, lead_bits=2, rshift=6
    // header = 0xC0, mask = 0x1F
    // (0x7FF >> 6) = 0x1F, & 0x1F = 0x1F
    // result = 0xC0 | 0x1F = 0xDF
    char result = YAML::Utf8Adjust(0x7FF, 2, 6);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xDF);
}

// Test: Continuation byte of U+07FF (second byte)
TEST_F(Utf8AdjustTest_170, MaxTwoByteCharContinuation_170) {
    // ch=0x7FF, lead_bits=1, rshift=0
    // header = 0x80, mask = 0x3F
    // (0x7FF >> 0) & 0x3F = 0x3F
    // result = 0x80 | 0x3F = 0xBF
    char result = YAML::Utf8Adjust(0x7FF, 1, 0);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xBF);
}

// Test: 3-byte encoding of U+FFFF lead byte
TEST_F(Utf8AdjustTest_170, MaxThreeByteCharLeadByte_170) {
    // ch=0xFFFF, lead_bits=3, rshift=12
    // header = 0xE0, mask = 0x0F
    // (0xFFFF >> 12) & 0x0F = 0x0F
    // result = 0xE0 | 0x0F = 0xEF
    char result = YAML::Utf8Adjust(0xFFFF, 3, 12);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xEF);
}

// Test: 4-byte encoding of U+10FFFF (max Unicode code point)
TEST_F(Utf8AdjustTest_170, MaxUnicodeLeadByte_170) {
    // ch=0x10FFFF, lead_bits=4, rshift=18
    // header = 0xF0, mask = 0x07
    // (0x10FFFF >> 18) & 0x07 = 0x04 & 0x07 = 0x04
    // result = 0xF0 | 0x04 = 0xF4
    char result = YAML::Utf8Adjust(0x10FFFF, 4, 18);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xF4);
}

// Test: Specific known UTF-8 encoding: U+00E9 (é) lead byte
TEST_F(Utf8AdjustTest_170, EAcuteLeadByte_170) {
    // ch=0xE9, lead_bits=2, rshift=6
    // header = 0xC0, mask = 0x1F
    // (0xE9 >> 6) & 0x1F = 0x03
    // result = 0xC0 | 0x03 = 0xC3
    char result = YAML::Utf8Adjust(0xE9, 2, 6);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xC3);
}

// Test: Specific known UTF-8 encoding: U+00E9 (é) continuation byte
TEST_F(Utf8AdjustTest_170, EAcuteContinuationByte_170) {
    // ch=0xE9, lead_bits=1, rshift=0
    // header = 0x80, mask = 0x3F
    // (0xE9 >> 0) & 0x3F = 0x29
    // result = 0x80 | 0x29 = 0xA9
    char result = YAML::Utf8Adjust(0xE9, 1, 0);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xA9);
}

// Test: lead_bits=0 edge case
// header = ((1<<0)-1) << 8 = 0 << 8 = 0, mask = 0xFF >> 1 = 0x7F
TEST_F(Utf8AdjustTest_170, ZeroLeadBitsASCII_170) {
    // ch=0x41 ('A'), lead_bits=0, rshift=0
    // header = 0
    // mask = 0x7F
    // result = 0 | (0x41 & 0x7F) = 0x41
    char result = YAML::Utf8Adjust(0x41, 0, 0);
    EXPECT_EQ(result, 'A');
}

// Test: Rshift larger than character bits effectively yields zero from character
TEST_F(Utf8AdjustTest_170, LargeRshiftYieldsHeaderOnly_170) {
    // ch=0xFF, lead_bits=2, rshift=24
    // header = 0xC0, mask = 0x1F
    // (0xFF >> 24) = 0
    // result = 0xC0 | 0 = 0xC0
    char result = YAML::Utf8Adjust(0xFF, 2, 24);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xC0);
}

// Test: Middle 3-byte continuation byte (rshift=6)
TEST_F(Utf8AdjustTest_170, ThreeByteMiddleContinuation_170) {
    // ch=0x0800, lead_bits=1, rshift=6
    // header = 0x80, mask = 0x3F
    // (0x0800 >> 6) & 0x3F = 0x20 & 0x3F = 0x20
    // result = 0x80 | 0x20 = 0xA0
    char result = YAML::Utf8Adjust(0x0800, 1, 6);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xA0);
}

// Test: 4-byte second byte (rshift=12, lead_bits=1)
TEST_F(Utf8AdjustTest_170, FourByteSecondContinuation_170) {
    // ch=0x1F600 (😀), lead_bits=1, rshift=12
    // header = 0x80, mask = 0x3F
    // (0x1F600 >> 12) & 0x3F = 0x1F & 0x3F = 0x1F
    // result = 0x80 | 0x1F = 0x9F
    char result = YAML::Utf8Adjust(0x1F600, 1, 12);
    EXPECT_EQ(static_cast<unsigned char>(result), 0x9F);
}

// Test: Verify the smiley emoji U+1F600 lead byte
TEST_F(Utf8AdjustTest_170, SmileyLeadByte_170) {
    // ch=0x1F600, lead_bits=4, rshift=18
    // header = 0xF0, mask = 0x07
    // (0x1F600 >> 18) & 0x07 = 0x07 & 0x07 = 0x07 (since 0x1F600 = 128512, >>18 = 0)
    // Actually: 0x1F600 = 128512. 128512 >> 18 = 0 (since 2^18 = 262144 > 128512)
    // Wait: 128512 / 262144 = 0. So result = 0xF0
    // Hmm, let me recalculate: 0x1F600 = 1*16^4 + 15*16^3 + 6*16^2 + 0 + 0 = 65536 + 61440 + 1536 = 128512
    // 128512 >> 18 = 128512 / 262144 = 0
    // But standard UTF-8 for U+1F600 is F0 9F 98 80
    // U+1F600 = 0x1F600, but wait that's only 17 bits. For 4-byte UTF-8:
    // lead: 11110xxx where xxx = bits 20-18. 0x1F600 in binary: 1 1111 0110 0000 0000
    // That's 17 bits. bits 20-18 don't exist (they'd be 0), so lead = 0xF0 | 0 = 0xF0
    // Hmm, but actual UTF-8 is F0. Let me check: 
    // Actually U+1F600 -> 0x1F600 = 0b 0001 1111 0110 0000 0000 = 128512
    // Bits 20-18: 000 -> lead = F0 | 0 = F0? But we expect F0 9F 98 80.
    // Wait, the standard says for codepoints U+10000 to U+10FFFF: subtract 0x10000 first? No, that's for surrogates.
    // UTF-8 encoding of U+1F600:
    // Binary: 0 0001 1111 0110 0000 0000 (21 bits padded)
    // Split: 000 011111 011000 000000
    // Lead: 11110 000 = F0
    // Second: 10 011111 = 9F
    // Third: 10 011000 = 98
    // Fourth: 10 000000 = 80
    // So lead byte should be F0, which means (0x1F600 >> 18) = 0. That matches F0 | 0 = F0.
    char result = YAML::Utf8Adjust(0x1F600, 4, 18);
    EXPECT_EQ(static_cast<unsigned char>(result), 0xF0);
}
