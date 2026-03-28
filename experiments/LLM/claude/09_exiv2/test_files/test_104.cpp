#include <gtest/gtest.h>
#include <cstdint>

// Minimal type definitions to match the interface
using byte = uint8_t;

namespace Exiv2 {
class MatroskaVideo {
public:
    uint32_t findBlockSize(byte b) {
        if (b & 128) return 1;
        if (b & 64) return 2;
        if (b & 32) return 3;
        if (b & 16) return 4;
        if (b & 8) return 5;
        if (b & 4) return 6;
        if (b & 2) return 7;
        if (b & 1) return 8;
        return 0;
    }
};
}

class MatroskaVideoTest_104 : public ::testing::Test {
protected:
    Exiv2::MatroskaVideo video;
};

// Test: Byte with highest bit set (bit 7) should return block size 1
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit7Set_Returns1_104) {
    EXPECT_EQ(video.findBlockSize(0x80), 1u);  // 10000000
}

// Test: Byte with only bit 7 set among upper bits
TEST_F(MatroskaVideoTest_104, FindBlockSize_0xFF_Returns1_104) {
    EXPECT_EQ(video.findBlockSize(0xFF), 1u);  // All bits set, highest wins
}

// Test: Byte with bit 6 set (no bit 7) should return block size 2
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit6Set_Returns2_104) {
    EXPECT_EQ(video.findBlockSize(0x40), 2u);  // 01000000
}

// Test: Byte with bit 5 set (no bits 7,6) should return block size 3
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit5Set_Returns3_104) {
    EXPECT_EQ(video.findBlockSize(0x20), 3u);  // 00100000
}

// Test: Byte with bit 4 set (no bits 7,6,5) should return block size 4
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit4Set_Returns4_104) {
    EXPECT_EQ(video.findBlockSize(0x10), 4u);  // 00010000
}

// Test: Byte with bit 3 set (no bits 7-4) should return block size 5
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit3Set_Returns5_104) {
    EXPECT_EQ(video.findBlockSize(0x08), 5u);  // 00001000
}

// Test: Byte with bit 2 set (no bits 7-3) should return block size 6
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit2Set_Returns6_104) {
    EXPECT_EQ(video.findBlockSize(0x04), 6u);  // 00000100
}

// Test: Byte with bit 1 set (no bits 7-2) should return block size 7
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit1Set_Returns7_104) {
    EXPECT_EQ(video.findBlockSize(0x02), 7u);  // 00000010
}

// Test: Byte with only bit 0 set should return block size 8
TEST_F(MatroskaVideoTest_104, FindBlockSize_Bit0Set_Returns8_104) {
    EXPECT_EQ(video.findBlockSize(0x01), 8u);  // 00000001
}

// Test: Byte with no bits set should return 0
TEST_F(MatroskaVideoTest_104, FindBlockSize_ZeroByte_Returns0_104) {
    EXPECT_EQ(video.findBlockSize(0x00), 0u);  // 00000000
}

// Test: Byte with bits 6 and lower set, but not bit 7 => returns 2
TEST_F(MatroskaVideoTest_104, FindBlockSize_0x7F_Returns2_104) {
    EXPECT_EQ(video.findBlockSize(0x7F), 2u);  // 01111111
}

// Test: Byte with bits 5 and lower set, but not bits 7,6 => returns 3
TEST_F(MatroskaVideoTest_104, FindBlockSize_0x3F_Returns3_104) {
    EXPECT_EQ(video.findBlockSize(0x3F), 3u);  // 00111111
}

// Test: Byte with bits 4 and lower set => returns 4
TEST_F(MatroskaVideoTest_104, FindBlockSize_0x1F_Returns4_104) {
    EXPECT_EQ(video.findBlockSize(0x1F), 4u);  // 00011111
}

// Test: Byte with bits 3 and lower set => returns 5
TEST_F(MatroskaVideoTest_104, FindBlockSize_0x0F_Returns5_104) {
    EXPECT_EQ(video.findBlockSize(0x0F), 5u);  // 00001111
}

// Test: Byte with bits 2 and lower set => returns 6
TEST_F(MatroskaVideoTest_104, FindBlockSize_0x07_Returns6_104) {
    EXPECT_EQ(video.findBlockSize(0x07), 6u);  // 00000111
}

// Test: Byte with bits 1 and 0 set => returns 7
TEST_F(MatroskaVideoTest_104, FindBlockSize_0x03_Returns7_104) {
    EXPECT_EQ(video.findBlockSize(0x03), 7u);  // 00000011
}

// Test: Highest bit dominates even when lower bits are also set
TEST_F(MatroskaVideoTest_104, FindBlockSize_HighestBitDominates_104) {
    EXPECT_EQ(video.findBlockSize(0x81), 1u);  // 10000001 - bit 7 dominates
    EXPECT_EQ(video.findBlockSize(0xC0), 1u);  // 11000000 - bit 7 dominates
    EXPECT_EQ(video.findBlockSize(0x41), 2u);  // 01000001 - bit 6 dominates
    EXPECT_EQ(video.findBlockSize(0x21), 3u);  // 00100001 - bit 5 dominates
    EXPECT_EQ(video.findBlockSize(0x11), 4u);  // 00010001 - bit 4 dominates
    EXPECT_EQ(video.findBlockSize(0x09), 5u);  // 00001001 - bit 3 dominates
    EXPECT_EQ(video.findBlockSize(0x05), 6u);  // 00000101 - bit 2 dominates
}

// Test: Specific EBML-like values
TEST_F(MatroskaVideoTest_104, FindBlockSize_EBMLValues_104) {
    // EBML element IDs commonly start with specific bit patterns
    EXPECT_EQ(video.findBlockSize(0x1A), 4u);  // Common in Matroska headers
    EXPECT_EQ(video.findBlockSize(0xA3), 1u);  // SimpleBlock element
    EXPECT_EQ(video.findBlockSize(0x42), 2u);  // Some EBML element
}

// Test: All possible single-bit values
TEST_F(MatroskaVideoTest_104, FindBlockSize_AllSingleBitValues_104) {
    EXPECT_EQ(video.findBlockSize(128), 1u);
    EXPECT_EQ(video.findBlockSize(64), 2u);
    EXPECT_EQ(video.findBlockSize(32), 3u);
    EXPECT_EQ(video.findBlockSize(16), 4u);
    EXPECT_EQ(video.findBlockSize(8), 5u);
    EXPECT_EQ(video.findBlockSize(4), 6u);
    EXPECT_EQ(video.findBlockSize(2), 7u);
    EXPECT_EQ(video.findBlockSize(1), 8u);
}

// Test: Boundary - maximum byte value
TEST_F(MatroskaVideoTest_104, FindBlockSize_MaxByteValue_104) {
    EXPECT_EQ(video.findBlockSize(255), 1u);
}

// Test: Values just below power-of-two boundaries
TEST_F(MatroskaVideoTest_104, FindBlockSize_BelowPowerOfTwo_104) {
    EXPECT_EQ(video.findBlockSize(127), 2u);  // 01111111
    EXPECT_EQ(video.findBlockSize(63), 3u);   // 00111111
    EXPECT_EQ(video.findBlockSize(31), 4u);   // 00011111
    EXPECT_EQ(video.findBlockSize(15), 5u);   // 00001111
    EXPECT_EQ(video.findBlockSize(7), 6u);    // 00000111
    EXPECT_EQ(video.findBlockSize(3), 7u);    // 00000011
}
