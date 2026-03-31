#include <cstdint>
#include <gtest/gtest.h>
#include "re2/re2.h"

// Since FindMSBSet is a static function internal to re2.cc and not exposed
// through any public header, we replicate the function signature for testing
// purposes. This tests the algorithm's correctness as specified in the code.
namespace re2_test {

static int FindMSBSet(uint32_t n) {
#if defined(__GNUC__)
    return 31 ^ __builtin_clz(n);
#elif defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
    unsigned long c;
    _BitScanReverse(&c, n);
    return static_cast<int>(c);
#else
    int c = 0;
    for (int shift = 1 << 4; shift != 0; shift >>= 1) {
        uint32_t word = n >> shift;
        if (word != 0) {
            n = word;
            c += shift;
        }
    }
    return c;
#endif
}

}  // namespace re2_test

class FindMSBSetTest_246 : public ::testing::Test {};

// Test with value 1 (bit 0 set)
TEST_F(FindMSBSetTest_246, SingleBitZero_246) {
    EXPECT_EQ(re2_test::FindMSBSet(1), 0);
}

// Test with value 2 (bit 1 set)
TEST_F(FindMSBSetTest_246, SingleBitOne_246) {
    EXPECT_EQ(re2_test::FindMSBSet(2), 1);
}

// Test with value 4 (bit 2 set)
TEST_F(FindMSBSetTest_246, SingleBitTwo_246) {
    EXPECT_EQ(re2_test::FindMSBSet(4), 2);
}

// Test with all powers of two
TEST_F(FindMSBSetTest_246, AllPowersOfTwo_246) {
    for (int i = 0; i < 32; i++) {
        uint32_t val = uint32_t{1} << i;
        EXPECT_EQ(re2_test::FindMSBSet(val), i) << "Failed for 2^" << i;
    }
}

// Test with value 3 (bits 0 and 1 set, MSB is bit 1)
TEST_F(FindMSBSetTest_246, ValueThree_246) {
    EXPECT_EQ(re2_test::FindMSBSet(3), 1);
}

// Test with value 0xFF (bits 0-7, MSB is bit 7)
TEST_F(FindMSBSetTest_246, Value0xFF_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0xFF), 7);
}

// Test with value 0xFFFF (bits 0-15, MSB is bit 15)
TEST_F(FindMSBSetTest_246, Value0xFFFF_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0xFFFF), 15);
}

// Test with max uint32_t value (all bits set, MSB is bit 31)
TEST_F(FindMSBSetTest_246, MaxUint32_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0xFFFFFFFF), 31);
}

// Test with value 0x80000000 (only bit 31 set)
TEST_F(FindMSBSetTest_246, HighestBitOnly_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0x80000000), 31);
}

// Test with value 7 (bits 0-2 set, MSB is bit 2)
TEST_F(FindMSBSetTest_246, ValueSeven_246) {
    EXPECT_EQ(re2_test::FindMSBSet(7), 2);
}

// Test with value 0x100 (bit 8 set)
TEST_F(FindMSBSetTest_246, Value0x100_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0x100), 8);
}

// Test with adjacent values to verify MSB transitions
TEST_F(FindMSBSetTest_246, BoundaryTransitions_246) {
    for (int i = 1; i < 31; i++) {
        uint32_t power = uint32_t{1} << i;
        EXPECT_EQ(re2_test::FindMSBSet(power - 1), i - 1) << "Failed for (2^" << i << ")-1";
        EXPECT_EQ(re2_test::FindMSBSet(power), i) << "Failed for 2^" << i;
        EXPECT_EQ(re2_test::FindMSBSet(power + 1), i) << "Failed for (2^" << i << ")+1";
    }
}

// Test with 0x55555555 pattern (alternating bits)
TEST_F(FindMSBSetTest_246, AlternatingBitsPattern_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0x55555555), 30);
}

// Test with 0xAAAAAAAA pattern (alternating bits, other pattern)
TEST_F(FindMSBSetTest_246, AlternatingBitsPatternB_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0xAAAAAAAA), 31);
}

// Test with value 0x10000 (bit 16)
TEST_F(FindMSBSetTest_246, Bit16_246) {
    EXPECT_EQ(re2_test::FindMSBSet(0x10000), 16);
}
