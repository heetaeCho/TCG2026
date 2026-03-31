#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::detail::bits;

// ============================================================
// Tests for rotr with uint32_t and bit_width = 32
// ============================================================

class RotrUint32Test_302 : public ::testing::Test {};

TEST_F(RotrUint32Test_302, RotateByZero_302) {
    // Rotating by 0 should return the same value
    uint32_t val = 0xDEADBEEF;
    uint32_t result = rotr<32>(val, 0);
    EXPECT_EQ(result, val);
}

TEST_F(RotrUint32Test_302, RotateByFullWidth_302) {
    // Rotating by the full bit_width should return the same value (since r & (32-1) == 0)
    uint32_t val = 0xDEADBEEF;
    uint32_t result = rotr<32>(val, 32);
    EXPECT_EQ(result, val);
}

TEST_F(RotrUint32Test_302, RotateByOne_302) {
    // 0x00000001 rotated right by 1 should give 0x80000000
    uint32_t val = 0x00000001;
    uint32_t result = rotr<32>(val, 1);
    EXPECT_EQ(result, 0x80000000u);
}

TEST_F(RotrUint32Test_302, RotateByHalfWidth_302) {
    // 0x0000FFFF rotated right by 16 should give 0xFFFF0000
    uint32_t val = 0x0000FFFF;
    uint32_t result = rotr<32>(val, 16);
    EXPECT_EQ(result, 0xFFFF0000u);
}

TEST_F(RotrUint32Test_302, RotateAllOnes_302) {
    // All ones rotated by any amount should remain all ones
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(rotr<32>(val, 0), 0xFFFFFFFFu);
    EXPECT_EQ(rotr<32>(val, 1), 0xFFFFFFFFu);
    EXPECT_EQ(rotr<32>(val, 15), 0xFFFFFFFFu);
    EXPECT_EQ(rotr<32>(val, 31), 0xFFFFFFFFu);
}

TEST_F(RotrUint32Test_302, RotateZero_302) {
    // Zero rotated by any amount should remain zero
    uint32_t val = 0x00000000;
    EXPECT_EQ(rotr<32>(val, 0), 0u);
    EXPECT_EQ(rotr<32>(val, 1), 0u);
    EXPECT_EQ(rotr<32>(val, 16), 0u);
    EXPECT_EQ(rotr<32>(val, 31), 0u);
}

TEST_F(RotrUint32Test_302, RotateByMaxMinusOne_302) {
    // Rotating by 31 (bit_width - 1)
    // 0x80000000 rotated right by 31 should give 0x00000001
    uint32_t val = 0x80000000;
    uint32_t result = rotr<32>(val, 31);
    EXPECT_EQ(result, 0x00000001u);
}

TEST_F(RotrUint32Test_302, RotateKnownPattern_302) {
    // 0x12345678 rotated right by 8
    // Low 8 bits (0x78) go to the top, rest shifts right
    uint32_t val = 0x12345678;
    uint32_t result = rotr<32>(val, 8);
    EXPECT_EQ(result, 0x78123456u);
}

TEST_F(RotrUint32Test_302, RotateKnownPatternBy4_302) {
    // 0xABCDEF01 rotated right by 4
    // Low nibble (0x1) goes to top, rest shifts right
    uint32_t val = 0xABCDEF01;
    uint32_t result = rotr<32>(val, 4);
    EXPECT_EQ(result, 0x1ABCDEF0u);
}

TEST_F(RotrUint32Test_302, DoubleRotationReturnsOriginal_302) {
    // Rotating right by r, then by (32 - r) should return original
    uint32_t val = 0xCAFEBABE;
    uint32_t intermediate = rotr<32>(val, 13);
    uint32_t result = rotr<32>(intermediate, 32 - 13);
    EXPECT_EQ(result, val);
}

TEST_F(RotrUint32Test_302, RotateByMultipleOfWidth_302) {
    // r = 64, which is 2 * 32; r & 31 == 0, so same as rotate by 0
    uint32_t val = 0x13579BDF;
    uint32_t result = rotr<32>(val, 64);
    EXPECT_EQ(result, val);
}

TEST_F(RotrUint32Test_302, RotateByWidthPlusOne_302) {
    // r = 33; r & 31 == 1, so same as rotate by 1
    uint32_t val = 0x00000001;
    uint32_t result = rotr<32>(val, 33);
    EXPECT_EQ(result, 0x80000000u);
}

// ============================================================
// Tests for rotr with uint64_t and bit_width = 64
// ============================================================

class RotrUint64Test_302 : public ::testing::Test {};

TEST_F(RotrUint64Test_302, RotateByZero_302) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t result = rotr<64>(val, 0);
    EXPECT_EQ(result, val);
}

TEST_F(RotrUint64Test_302, RotateByFullWidth_302) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t result = rotr<64>(val, 64);
    EXPECT_EQ(result, val);
}

TEST_F(RotrUint64Test_302, RotateByOne_302) {
    uint64_t val = 0x0000000000000001ULL;
    uint64_t result = rotr<64>(val, 1);
    EXPECT_EQ(result, 0x8000000000000000ULL);
}

TEST_F(RotrUint64Test_302, RotateByHalfWidth_302) {
    uint64_t val = 0x00000000FFFFFFFFULL;
    uint64_t result = rotr<64>(val, 32);
    EXPECT_EQ(result, 0xFFFFFFFF00000000ULL);
}

TEST_F(RotrUint64Test_302, RotateAllOnes_302) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(rotr<64>(val, 0), val);
    EXPECT_EQ(rotr<64>(val, 1), val);
    EXPECT_EQ(rotr<64>(val, 32), val);
    EXPECT_EQ(rotr<64>(val, 63), val);
}

TEST_F(RotrUint64Test_302, RotateZero_302) {
    uint64_t val = 0x0000000000000000ULL;
    EXPECT_EQ(rotr<64>(val, 0), 0ULL);
    EXPECT_EQ(rotr<64>(val, 1), 0ULL);
    EXPECT_EQ(rotr<64>(val, 32), 0ULL);
    EXPECT_EQ(rotr<64>(val, 63), 0ULL);
}

TEST_F(RotrUint64Test_302, RotateBy63_302) {
    // MSB set, rotate right by 63 should give 0x0000000000000001
    uint64_t val = 0x8000000000000000ULL;
    uint64_t result = rotr<64>(val, 63);
    EXPECT_EQ(result, 0x0000000000000001ULL);
}

TEST_F(RotrUint64Test_302, DoubleRotationReturnsOriginal_302) {
    uint64_t val = 0x123456789ABCDEF0ULL;
    uint64_t intermediate = rotr<64>(val, 17);
    uint64_t result = rotr<64>(intermediate, 64 - 17);
    EXPECT_EQ(result, val);
}

TEST_F(RotrUint64Test_302, RotateKnownPatternBy8_302) {
    // 0x0123456789ABCDEF rotated right by 8
    // Low byte 0xEF goes to top
    uint64_t val = 0x0123456789ABCDEFULL;
    uint64_t result = rotr<64>(val, 8);
    EXPECT_EQ(result, 0xEF0123456789ABCDULL);
}

// ============================================================
// Tests for rotr with smaller bit_width (sub-word rotation)
// ============================================================

class RotrSmallBitWidthTest_302 : public ::testing::Test {};

TEST_F(RotrSmallBitWidthTest_302, BitWidth8RotateByZero_302) {
    // Using bit_width = 8 on a uint32_t; only the low 8 bits matter for rotation
    uint32_t val = 0x01; // only low 8 bits: 00000001
    uint32_t result = rotr<8>(val, 0);
    EXPECT_EQ(result, val);
}

TEST_F(RotrSmallBitWidthTest_302, BitWidth8RotateByOne_302) {
    // val = 0x01 (00000001), rotate right by 1 within 8 bits -> 10000000 = 0x80
    // But since the UInt is uint32_t, we get the bits placed correctly
    uint32_t val = 0x01;
    uint32_t result = rotr<8>(val, 1);
    EXPECT_EQ(result, 0x80u);
}

TEST_F(RotrSmallBitWidthTest_302, BitWidth8RotateByFour_302) {
    // val = 0xAB (10101011), rotate right by 4 -> 10111010 = 0xBA
    uint32_t val = 0xAB;
    uint32_t result = rotr<8>(val, 4);
    EXPECT_EQ(result, 0xBAu);
}

TEST_F(RotrSmallBitWidthTest_302, BitWidth16RotateByEight_302) {
    // val = 0x1234, rotate right by 8 within 16 bits -> 0x3412
    uint32_t val = 0x1234;
    uint32_t result = rotr<16>(val, 8);
    EXPECT_EQ(result, 0x3412u);
}

TEST_F(RotrSmallBitWidthTest_302, BitWidth4RotateByOne_302) {
    // bit_width=4, val=0x1 (0001), rotr by 1 -> 1000 = 0x8
    uint32_t val = 0x01;
    uint32_t result = rotr<4>(val, 1);
    EXPECT_EQ(result, 0x8u);
}

TEST_F(RotrSmallBitWidthTest_302, BitWidth4RotateByTwo_302) {
    // bit_width=4, val=0x5 (0101), rotr by 2 -> 0101 = 0x5 (symmetric pattern)
    uint32_t val = 0x05;
    uint32_t result = rotr<4>(val, 2);
    EXPECT_EQ(result, 0x05u);
}

// ============================================================
// Test with uint16_t
// ============================================================

class RotrUint16Test_302 : public ::testing::Test {};

TEST_F(RotrUint16Test_302, BitWidth16RotateByZero_302) {
    uint16_t val = 0xBEEF;
    uint16_t result = rotr<16>(val, static_cast<unsigned int>(0));
    EXPECT_EQ(result, 0xBEEFu);
}

TEST_F(RotrUint16Test_302, BitWidth16RotateByOne_302) {
    uint16_t val = 0x0001;
    uint16_t result = rotr<16>(val, 1);
    EXPECT_EQ(result, 0x8000u);
}

TEST_F(RotrUint16Test_302, BitWidth16RotateBy8_302) {
    uint16_t val = 0xABCD;
    uint16_t result = rotr<16>(val, 8);
    EXPECT_EQ(result, 0xCDABu);
}

TEST_F(RotrUint16Test_302, BitWidth16AllOnes_302) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(rotr<16>(val, 0), static_cast<uint16_t>(0xFFFF));
    EXPECT_EQ(rotr<16>(val, 5), static_cast<uint16_t>(0xFFFF));
    EXPECT_EQ(rotr<16>(val, 15), static_cast<uint16_t>(0xFFFF));
}

// ============================================================
// Tests for uint8_t
// ============================================================

class RotrUint8Test_302 : public ::testing::Test {};

TEST_F(RotrUint8Test_302, BitWidth8RotateByZero_302) {
    uint8_t val = 0xAB;
    uint8_t result = rotr<8>(val, 0);
    EXPECT_EQ(result, 0xABu);
}

TEST_F(RotrUint8Test_302, BitWidth8RotateByOne_302) {
    uint8_t val = 0x01;
    uint8_t result = rotr<8>(val, 1);
    EXPECT_EQ(result, 0x80u);
}

TEST_F(RotrUint8Test_302, BitWidth8RotateByFour_302) {
    uint8_t val = 0xF0;
    uint8_t result = rotr<8>(val, 4);
    EXPECT_EQ(result, 0x0Fu);
}

TEST_F(RotrUint8Test_302, BitWidth8RotateBySeven_302) {
    // 0x01 (00000001) rotated right by 7 -> 00000010 = 0x02
    uint8_t val = 0x01;
    uint8_t result = rotr<8>(val, 7);
    EXPECT_EQ(result, 0x02u);
}

// ============================================================
// Edge case: single bit power of two bit_width
// ============================================================

class RotrSingleBitTest_302 : public ::testing::Test {};

TEST_F(RotrSingleBitTest_302, BitWidth1RotateByZero_302) {
    // bit_width=1, val=1, rotate by 0 -> 1
    uint32_t val = 1;
    uint32_t result = rotr<1>(val, 0);
    EXPECT_EQ(result, 1u);
}

TEST_F(RotrSingleBitTest_302, BitWidth1RotateByOne_302) {
    // bit_width=1, r & (1-1) = r & 0 = 0; same as rotate by 0
    uint32_t val = 1;
    uint32_t result = rotr<1>(val, 1);
    EXPECT_EQ(result, 1u);
}

TEST_F(RotrSingleBitTest_302, BitWidth2RotateByOne_302) {
    // bit_width=2, val=0x01 (01), rotate right by 1 -> 10 = 0x02
    uint32_t val = 0x01;
    uint32_t result = rotr<2>(val, 1);
    EXPECT_EQ(result, 0x02u);
}

} // anonymous namespace
