#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

class Umul128Upper64Test_308 : public ::testing::Test {
protected:
};

// Test: Multiplying zero by zero should yield zero
TEST_F(Umul128Upper64Test_308, ZeroTimesZero_308) {
    auto result = umul128_upper64(0ULL, 0ULL);
    EXPECT_EQ(result, 0ULL);
}

// Test: Multiplying zero by any number should yield zero upper 64 bits
TEST_F(Umul128Upper64Test_308, ZeroTimesNonZero_308) {
    EXPECT_EQ(umul128_upper64(0ULL, 1ULL), 0ULL);
    EXPECT_EQ(umul128_upper64(0ULL, UINT64_MAX), 0ULL);
    EXPECT_EQ(umul128_upper64(1ULL, 0ULL), 0ULL);
    EXPECT_EQ(umul128_upper64(UINT64_MAX, 0ULL), 0ULL);
}

// Test: Multiplying one by any number - upper 64 bits should be zero for small numbers
TEST_F(Umul128Upper64Test_308, OneTimesSmallNumber_308) {
    EXPECT_EQ(umul128_upper64(1ULL, 1ULL), 0ULL);
    EXPECT_EQ(umul128_upper64(1ULL, 100ULL), 0ULL);
    EXPECT_EQ(umul128_upper64(1ULL, 0xFFFFFFFFULL), 0ULL);
}

// Test: 1 * UINT64_MAX should have upper 64 bits = 0
TEST_F(Umul128Upper64Test_308, OneTimesMaxUint64_308) {
    // 1 * UINT64_MAX = UINT64_MAX, which fits in 64 bits, so upper = 0
    EXPECT_EQ(umul128_upper64(1ULL, UINT64_MAX), 0ULL);
    EXPECT_EQ(umul128_upper64(UINT64_MAX, 1ULL), 0ULL);
}

// Test: 2 * UINT64_MAX = 2*0xFFFFFFFFFFFFFFFF = 0x1FFFFFFFFFFFFFFFE
// Upper 64 bits = 1
TEST_F(Umul128Upper64Test_308, TwoTimesMaxUint64_308) {
    auto result = umul128_upper64(2ULL, UINT64_MAX);
    EXPECT_EQ(result, 1ULL);
}

// Test: UINT64_MAX * UINT64_MAX
// (2^64 - 1)^2 = 2^128 - 2*2^64 + 1
// Upper 64 bits = 2^64 - 2 = 0xFFFFFFFFFFFFFFFE
TEST_F(Umul128Upper64Test_308, MaxTimesMax_308) {
    auto result = umul128_upper64(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(result, UINT64_MAX - 1ULL);  // 0xFFFFFFFFFFFFFFFE
}

// Test: (2^32) * (2^32) = 2^64, upper 64 bits = 1
TEST_F(Umul128Upper64Test_308, PowerOf2_32_Squared_308) {
    uint64_t val = 1ULL << 32;
    auto result = umul128_upper64(val, val);
    EXPECT_EQ(result, 1ULL);
}

// Test: (2^63) * 2 = 2^64, upper 64 bits = 1
TEST_F(Umul128Upper64Test_308, HalfMaxTimeTwo_308) {
    uint64_t half = 1ULL << 63;
    auto result = umul128_upper64(half, 2ULL);
    EXPECT_EQ(result, 1ULL);
}

// Test: (2^63) * (2^63) = 2^126, upper 64 bits = 2^62
TEST_F(Umul128Upper64Test_308, HalfMaxTimesHalfMax_308) {
    uint64_t half = 1ULL << 63;
    auto result = umul128_upper64(half, half);
    EXPECT_EQ(result, 1ULL << 62);
}

// Test: Commutativity - x*y should equal y*x
TEST_F(Umul128Upper64Test_308, Commutativity_308) {
    uint64_t x = 0x123456789ABCDEF0ULL;
    uint64_t y = 0xFEDCBA9876543210ULL;
    EXPECT_EQ(umul128_upper64(x, y), umul128_upper64(y, x));
}

// Test: Known value computation
// 0x100000000 * 0x100000000 = 0x10000000000000000, upper = 1
TEST_F(Umul128Upper64Test_308, KnownValueFourGigTimesForGig_308) {
    uint64_t fourG = 0x100000000ULL;
    EXPECT_EQ(umul128_upper64(fourG, fourG), 1ULL);
}

// Test: Small values that fit within 64-bit result should have upper = 0
TEST_F(Umul128Upper64Test_308, SmallValuesUpperZero_308) {
    EXPECT_EQ(umul128_upper64(1000ULL, 1000ULL), 0ULL);
    EXPECT_EQ(umul128_upper64(0xFFFFULL, 0xFFFFULL), 0ULL);
    EXPECT_EQ(umul128_upper64(0xFFFFFFFFULL, 1ULL), 0ULL);
}

// Test: Values just at the boundary where result starts to overflow 64 bits
// (2^32) * (2^32 - 1) = 2^64 - 2^32, upper 64 bits = 0
TEST_F(Umul128Upper64Test_308, BoundaryNoOverflow_308) {
    uint64_t a = 1ULL << 32;
    uint64_t b = (1ULL << 32) - 1;
    // a * b = 2^64 - 2^32, which is less than 2^64, so upper = 0
    EXPECT_EQ(umul128_upper64(a, b), 0ULL);
}

// Test: Large values
// 0xFFFFFFFF00000000 * 0x2 = 0x1FFFFFFFE00000000
// Upper 64 bits = 1
TEST_F(Umul128Upper64Test_308, LargeValueTimesTwo_308) {
    uint64_t a = 0xFFFFFFFF00000000ULL;
    auto result = umul128_upper64(a, 2ULL);
    EXPECT_EQ(result, 1ULL);
}

// Test: Specific known computation
// 0x8000000000000000 * 4 = 2^65, upper = 2
TEST_F(Umul128Upper64Test_308, SpecificKnownComputation_308) {
    uint64_t a = 0x8000000000000000ULL;
    auto result = umul128_upper64(a, 4ULL);
    EXPECT_EQ(result, 2ULL);
}

// Test: Another specific computation to verify correctness
// (2^64 - 1) * 3 = 3 * 2^64 - 3
// = (2 * 2^64) + (2^64 - 3)
// Upper 64 bits = 2
TEST_F(Umul128Upper64Test_308, MaxTimesThree_308) {
    auto result = umul128_upper64(UINT64_MAX, 3ULL);
    EXPECT_EQ(result, 2ULL);
}

// Test: Symmetry with different large values
TEST_F(Umul128Upper64Test_308, SymmetryLargeValues_308) {
    uint64_t x = 0xDEADBEEFCAFEBABEULL;
    uint64_t y = 0xBADC0FFEE0DDF00DULL;
    EXPECT_EQ(umul128_upper64(x, y), umul128_upper64(y, x));
}

// Test: Power of two multiplications
// 2^33 * 2^33 = 2^66, upper = 4
TEST_F(Umul128Upper64Test_308, PowerOfTwoMultiplication_308) {
    uint64_t a = 1ULL << 33;
    auto result = umul128_upper64(a, a);
    EXPECT_EQ(result, 1ULL << 2);  // 2^66 >> 64 = 4
}

// Test: 2^48 * 2^48 = 2^96, upper = 2^32
TEST_F(Umul128Upper64Test_308, PowerOfTwoLarger_308) {
    uint64_t a = 1ULL << 48;
    auto result = umul128_upper64(a, a);
    EXPECT_EQ(result, 1ULL << 32);
}
