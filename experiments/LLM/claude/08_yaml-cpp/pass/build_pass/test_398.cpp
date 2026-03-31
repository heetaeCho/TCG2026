#include "gtest/gtest.h"
#include "contrib/dragonbox.h"

// Navigate to the correct namespace depth for the types we need
// The actual implementation is deeply nested. We need to access the compute_mul function
// through the proper namespace path.

namespace {

// Try to access the relevant types and functions
using namespace YAML::jkj::dragonbox;

class ComputeMulTest_398 : public ::testing::Test {
protected:
    // Helper to access uint128
    using uint128 = YAML::jkj::dragonbox::detail::wuint::uint128;
};

// Test with zero multiplier
TEST_F(ComputeMulTest_398, ZeroCarrierReturnsZeroHighAndTrueLowFlag_398) {
    // When u is 0, the multiplication result should be 0
    // high should be 0, and low == 0 should be true
    // We need the appropriate cache_entry_type which for double precision
    // is uint128
    uint128 cache(0, 0);
    auto result = YAML::jkj::dragonbox::detail::wuint::umul192_upper128(0, cache);
    // Verify through compute_mul behavior: result.high() should be 0, result.low() == 0 should be true
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test with one as multiplier and small cache
TEST_F(ComputeMulTest_398, OneCarrierWithSmallCache_398) {
    uint128 cache(0, 1);
    auto result = YAML::jkj::dragonbox::detail::wuint::umul192_upper128(1, cache);
    // 1 * {0, 1} in 192-bit multiplication, upper 128 bits should be 0
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test with maximum carrier value and cache of {1, 0}
TEST_F(ComputeMulTest_398, MaxCarrierWithCacheHighOne_398) {
    uint64_t max_u = UINT64_MAX;
    uint128 cache(1, 0);
    auto result = YAML::jkj::dragonbox::detail::wuint::umul192_upper128(max_u, cache);
    // u * cache.high() = UINT64_MAX * 1 = UINT64_MAX
    // The upper 128 bits of 192-bit result
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), UINT64_MAX - 1);
}

// Test with maximum values to check overflow handling
TEST_F(ComputeMulTest_398, MaxCarrierWithMaxCache_398) {
    uint64_t max_u = UINT64_MAX;
    uint128 cache(UINT64_MAX, UINT64_MAX);
    auto result = YAML::jkj::dragonbox::detail::wuint::umul192_upper128(max_u, cache);
    // Large multiplication - high should be close to UINT64_MAX
    EXPECT_EQ(result.high(), UINT64_MAX);
    // low part should be UINT64_MAX (due to carry propagation)
    EXPECT_EQ(result.low(), UINT64_MAX);
}

// Test with carrier = 1 and cache = {UINT64_MAX, UINT64_MAX}
TEST_F(ComputeMulTest_398, OneCarrierWithMaxCache_398) {
    uint128 cache(UINT64_MAX, UINT64_MAX);
    auto result = YAML::jkj::dragonbox::detail::wuint::umul192_upper128(1, cache);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), UINT64_MAX);
}

// Test uint128 basic construction and accessors
TEST_F(ComputeMulTest_398, Uint128ConstructionAndAccessors_398) {
    uint128 val(42, 99);
    EXPECT_EQ(val.high(), 42u);
    EXPECT_EQ(val.low(), 99u);
}

// Test uint128 addition operator
TEST_F(ComputeMulTest_398, Uint128PlusEqualsOperator_398) {
    uint128 val(0, UINT64_MAX);
    val += 1;
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), 0u);
}

// Test uint128 addition without overflow
TEST_F(ComputeMulTest_398, Uint128PlusEqualsNoOverflow_398) {
    uint128 val(5, 10);
    val += 20;
    EXPECT_EQ(val.high(), 5u);
    EXPECT_EQ(val.low(), 30u);
}

}  // namespace
