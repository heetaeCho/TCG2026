#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

// We need to access the types from the deeply nested namespace
// The function is in YAML::jkj::dragonbox::jkj::dragonbox
// We'll use the appropriate namespace alias for clarity

using namespace YAML::jkj::dragonbox::jkj::dragonbox;

class ComputeDeltaTest_393 : public ::testing::Test {
protected:
    // Helper to call compute_delta with specific types
    // cache_entry_type and cache_bits should be defined in the dragonbox implementation
};

// Test with beta = 0, which should shift by (cache_bits - 1)
TEST_F(ComputeDeltaTest_393, BetaZeroShiftsMaximum_393) {
    cache_entry_type cache = cache_entry_type(1) << (cache_bits - 1);
    auto result = compute_delta(cache, int(0));
    // Shifting cache >> (cache_bits - 1 - 0) = cache >> (cache_bits - 1)
    // cache has bit (cache_bits-1) set, so result should be 1
    EXPECT_EQ(result, static_cast<detail::stdr::uint_least64_t>(1));
}

// Test with a known cache value and beta
TEST_F(ComputeDeltaTest_393, KnownValueComputation_393) {
    // Set all bits in cache to get a predictable shift result
    cache_entry_type cache = ~cache_entry_type(0);
    int beta = 0;
    auto result = compute_delta(cache, beta);
    // cache >> (cache_bits - 1) should give us the top bit pattern cast to uint_least64_t
    auto expected = static_cast<detail::stdr::uint_least64_t>(cache >> (cache_bits - 1 - beta));
    EXPECT_EQ(result, expected);
}

// Test with maximum beta value (cache_bits - 1), shifting by 0
TEST_F(ComputeDeltaTest_393, MaxBetaNoShift_393) {
    cache_entry_type cache = cache_entry_type(0xFF);
    int beta = cache_bits - 1;
    auto result = compute_delta(cache, beta);
    // cache >> (cache_bits - 1 - (cache_bits - 1)) = cache >> 0 = cache
    auto expected = static_cast<detail::stdr::uint_least64_t>(cache);
    EXPECT_EQ(result, expected);
}

// Test with zero cache value
TEST_F(ComputeDeltaTest_393, ZeroCacheReturnsZero_393) {
    cache_entry_type cache = cache_entry_type(0);
    int beta = 0;
    auto result = compute_delta(cache, beta);
    EXPECT_EQ(result, static_cast<detail::stdr::uint_least64_t>(0));
}

// Test with zero cache and max beta
TEST_F(ComputeDeltaTest_393, ZeroCacheMaxBetaReturnsZero_393) {
    cache_entry_type cache = cache_entry_type(0);
    int beta = cache_bits - 1;
    auto result = compute_delta(cache, beta);
    EXPECT_EQ(result, static_cast<detail::stdr::uint_least64_t>(0));
}

// Test with intermediate beta value
TEST_F(ComputeDeltaTest_393, IntermediateBetaValue_393) {
    cache_entry_type cache = cache_entry_type(1) << (cache_bits / 2);
    int beta = cache_bits / 2;
    auto result = compute_delta(cache, beta);
    auto expected = static_cast<detail::stdr::uint_least64_t>(cache >> (cache_bits - 1 - beta));
    EXPECT_EQ(result, expected);
}

// Test constexpr property - compute_delta should be usable at compile time
TEST_F(ComputeDeltaTest_393, ConstexprComputation_393) {
    constexpr cache_entry_type cache = cache_entry_type(0x1234);
    constexpr int beta = 0;
    constexpr auto result = compute_delta(cache, beta);
    auto expected = static_cast<detail::stdr::uint_least64_t>(cache >> (cache_bits - 1 - beta));
    EXPECT_EQ(result, expected);
}

}  // namespace
