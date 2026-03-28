#include <gtest/gtest.h>
#include "matroskavideo.hpp"  // Include the header for MatroskaVideo

namespace Exiv2 {

// Test fixture for MatroskaVideo
class MatroskaVideoTest_104 : public ::testing::Test {
protected:
    // You can set up test data here if needed
    MatroskaVideoTest_104() = default;
    ~MatroskaVideoTest_104() override = default;
};

// Normal operation test cases
TEST_F(MatroskaVideoTest_104, FindBlockSize_128_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(128);  // 10000000 in binary
    EXPECT_EQ(result, 1);  // Block size 1 as expected for the MSB
}

TEST_F(MatroskaVideoTest_104, FindBlockSize_64_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(64);  // 01000000 in binary
    EXPECT_EQ(result, 2);  // Block size 2 as expected for 64 (second bit set)
}

TEST_F(MatroskaVideoTest_104, FindBlockSize_32_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(32);  // 00100000 in binary
    EXPECT_EQ(result, 3);  // Block size 3 as expected for 32
}

TEST_F(MatroskaVideoTest_104, FindBlockSize_16_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(16);  // 00010000 in binary
    EXPECT_EQ(result, 4);  // Block size 4 as expected for 16
}

TEST_F(MatroskaVideoTest_104, FindBlockSize_8_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(8);  // 00001000 in binary
    EXPECT_EQ(result, 5);  // Block size 5 as expected for 8
}

TEST_F(MatroskaVideoTest_104, FindBlockSize_4_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(4);  // 00000100 in binary
    EXPECT_EQ(result, 6);  // Block size 6 as expected for 4
}

TEST_F(MatroskaVideoTest_104, FindBlockSize_2_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(2);  // 00000010 in binary
    EXPECT_EQ(result, 7);  // Block size 7 as expected for 2
}

TEST_F(MatroskaVideoTest_104, FindBlockSize_1_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(1);  // 00000001 in binary
    EXPECT_EQ(result, 8);  // Block size 8 as expected for 1
}

// Boundary case where all bits are set (255)
TEST_F(MatroskaVideoTest_104, FindBlockSize_255_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(255);  // 11111111 in binary
    EXPECT_EQ(result, 8);  // Block size 8 as expected for the maximum possible value
}

// Edge case where the byte is 0 (no bits set)
TEST_F(MatroskaVideoTest_104, FindBlockSize_0_104) {
    MatroskaVideo video;
    uint32_t result = video.findBlockSize(0);  // 00000000 in binary
    EXPECT_EQ(result, 0);  // Block size 0 as expected for a byte with no set bits
}

}  // namespace Exiv2