#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

// Navigate to the correct namespace for the types we need
using namespace YAML::jkj::dragonbox;

// Access uint128 from the detail::wuint namespace
using YAML::jkj::dragonbox::detail::wuint::uint128;

class Uint128Test_399 : public ::testing::Test {
protected:
};

// Test default construction and parameterized construction
TEST_F(Uint128Test_399, ConstructWithHighAndLow_399) {
    uint128 val(0x123456789ABCDEF0ULL, 0xFEDCBA9876543210ULL);
    EXPECT_EQ(val.high(), 0x123456789ABCDEF0ULL);
    EXPECT_EQ(val.low(), 0xFEDCBA9876543210ULL);
}

TEST_F(Uint128Test_399, ConstructWithZeros_399) {
    uint128 val(0ULL, 0ULL);
    EXPECT_EQ(val.high(), 0ULL);
    EXPECT_EQ(val.low(), 0ULL);
}

TEST_F(Uint128Test_399, ConstructWithMaxValues_399) {
    uint128 val(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(val.high(), UINT64_MAX);
    EXPECT_EQ(val.low(), UINT64_MAX);
}

TEST_F(Uint128Test_399, HighAccessor_399) {
    uint128 val(42ULL, 100ULL);
    EXPECT_EQ(val.high(), 42ULL);
}

TEST_F(Uint128Test_399, LowAccessor_399) {
    uint128 val(42ULL, 100ULL);
    EXPECT_EQ(val.low(), 100ULL);
}

// Test operator+=
TEST_F(Uint128Test_399, PlusEqualsNoOverflow_399) {
    uint128 val(0ULL, 10ULL);
    val += 5ULL;
    EXPECT_EQ(val.low(), 15ULL);
    EXPECT_EQ(val.high(), 0ULL);
}

TEST_F(Uint128Test_399, PlusEqualsWithOverflow_399) {
    uint128 val(0ULL, UINT64_MAX);
    val += 1ULL;
    EXPECT_EQ(val.low(), 0ULL);
    EXPECT_EQ(val.high(), 1ULL);
}

TEST_F(Uint128Test_399, PlusEqualsWithOverflowLargeHigh_399) {
    uint128 val(5ULL, UINT64_MAX);
    val += 1ULL;
    EXPECT_EQ(val.low(), 0ULL);
    EXPECT_EQ(val.high(), 6ULL);
}

TEST_F(Uint128Test_399, PlusEqualsZero_399) {
    uint128 val(3ULL, 7ULL);
    val += 0ULL;
    EXPECT_EQ(val.low(), 7ULL);
    EXPECT_EQ(val.high(), 3ULL);
}

TEST_F(Uint128Test_399, PlusEqualsWithLargeOverflow_399) {
    uint128 val(0ULL, UINT64_MAX - 5);
    val += 10ULL;
    EXPECT_EQ(val.low(), 4ULL);
    EXPECT_EQ(val.high(), 1ULL);
}

// Note: compute_delta tests depend on the specific template instantiation context
// and cache_entry_type / total_bits which are defined within specific policy classes.
// The function computes: uint64_t(cache.high() >> (total_bits - 1 - beta))
// Without knowing the exact policy/total_bits value, we test uint128 thoroughly.

TEST_F(Uint128Test_399, HighOnlySet_399) {
    uint128 val(0xAAAAAAAAAAAAAAAAULL, 0ULL);
    EXPECT_EQ(val.high(), 0xAAAAAAAAAAAAAAAAULL);
    EXPECT_EQ(val.low(), 0ULL);
}

TEST_F(Uint128Test_399, LowOnlySet_399) {
    uint128 val(0ULL, 0x5555555555555555ULL);
    EXPECT_EQ(val.high(), 0ULL);
    EXPECT_EQ(val.low(), 0x5555555555555555ULL);
}

TEST_F(Uint128Test_399, PlusEqualsChaining_399) {
    uint128 val(0ULL, 0ULL);
    val += 100ULL;
    val += 200ULL;
    EXPECT_EQ(val.low(), 300ULL);
    EXPECT_EQ(val.high(), 0ULL);
}

TEST_F(Uint128Test_399, PlusEqualsMaxValue_399) {
    uint128 val(0ULL, 0ULL);
    val += UINT64_MAX;
    EXPECT_EQ(val.low(), UINT64_MAX);
    EXPECT_EQ(val.high(), 0ULL);
}
