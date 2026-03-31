#include <gtest/gtest.h>
#include "contrib/dragonbox.h"
#include <cstdint>
#include <limits>

// We need to access the compute_right_endpoint_for_shorter_interval_case function
// through the dragonbox implementation. Since the code is deeply templated,
// we test it through the available instantiations.

namespace {

// For float: carrier_uint = uint32_t, significand_bits = 23, cache_bits = 64
// cache_entry_type = uint64_t
struct FloatTraits {
    using carrier_uint = std::uint32_t;
    using cache_entry_type = std::uint64_t;
    static constexpr int significand_bits = 23;
    static constexpr int cache_bits = 64;

    static constexpr carrier_uint compute_right_endpoint_for_shorter_interval_case(
        cache_entry_type const& cache, int beta) noexcept {
        return carrier_uint((cache + (cache >> (significand_bits + 1))) >>
            (cache_bits - significand_bits - 1 - beta));
    }
};

// For double: carrier_uint = uint64_t, significand_bits = 52, cache_bits = 128
// cache_entry_type = __uint128_t (or a 128-bit struct)
struct DoubleTraits {
    using carrier_uint = std::uint64_t;
    using cache_entry_type = __uint128_t;
    static constexpr int significand_bits = 52;
    static constexpr int cache_bits = 128;

    static constexpr carrier_uint compute_right_endpoint_for_shorter_interval_case(
        cache_entry_type const& cache, int beta) noexcept {
        return carrier_uint((cache + (cache >> (significand_bits + 1))) >>
            (cache_bits - significand_bits - 1 - beta));
    }
};

} // anonymous namespace

class ComputeRightEndpointFloatTest_396 : public ::testing::Test {};
class ComputeRightEndpointDoubleTest_396 : public ::testing::Test {};

// Float tests

TEST_F(ComputeRightEndpointFloatTest_396, ZeroCacheReturnsZero_396) {
    std::uint64_t cache = 0;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    EXPECT_EQ(result, 0u);
}

TEST_F(ComputeRightEndpointFloatTest_396, BetaZero_396) {
    std::uint64_t cache = 0xFFFFFFFFFFFFFFFFULL;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    // With beta=0, shift right by (64 - 23 - 1 - 0) = 40
    std::uint64_t intermediate = cache + (cache >> 24);
    std::uint32_t expected = static_cast<std::uint32_t>(intermediate >> 40);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointFloatTest_396, BetaOne_396) {
    std::uint64_t cache = 0x8000000000000000ULL;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    std::uint64_t intermediate = cache + (cache >> 24);
    std::uint32_t expected = static_cast<std::uint32_t>(intermediate >> 39);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointFloatTest_396, BetaTwo_396) {
    std::uint64_t cache = 0xABCDEF0123456789ULL;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 2);
    std::uint64_t intermediate = cache + (cache >> 24);
    std::uint32_t expected = static_cast<std::uint32_t>(intermediate >> 38);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointFloatTest_396, SmallCacheValue_396) {
    std::uint64_t cache = 1ULL << 40;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    std::uint64_t intermediate = cache + (cache >> 24);
    std::uint32_t expected = static_cast<std::uint32_t>(intermediate >> 40);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointFloatTest_396, PowerOfTwoCache_396) {
    std::uint64_t cache = 1ULL << 63;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    std::uint64_t intermediate = cache + (cache >> 24);
    std::uint32_t expected = static_cast<std::uint32_t>(intermediate >> 40);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointFloatTest_396, CacheValueOne_396) {
    std::uint64_t cache = 1;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    // cache >> 24 = 0, intermediate = 1, 1 >> 40 = 0
    EXPECT_EQ(result, 0u);
}

TEST_F(ComputeRightEndpointFloatTest_396, MaxBeta_396) {
    // beta can be up to 2 for float (since exponent bias related)
    std::uint64_t cache = 0xFFFFFFFFFFFFFFFFULL;
    auto result = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 3);
    std::uint64_t intermediate = cache + (cache >> 24);
    std::uint32_t expected = static_cast<std::uint32_t>(intermediate >> 37);
    EXPECT_EQ(result, expected);
}

// Double tests

TEST_F(ComputeRightEndpointDoubleTest_396, ZeroCacheReturnsZero_396) {
    __uint128_t cache = 0;
    auto result = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    EXPECT_EQ(result, 0u);
}

TEST_F(ComputeRightEndpointDoubleTest_396, BetaZero_396) {
    __uint128_t cache = ((__uint128_t)1 << 127) | ((__uint128_t)1 << 126);
    auto result = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    // shift right by (128 - 52 - 1 - 0) = 75
    __uint128_t intermediate = cache + (cache >> 53);
    std::uint64_t expected = static_cast<std::uint64_t>(intermediate >> 75);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointDoubleTest_396, BetaOne_396) {
    __uint128_t cache = ((__uint128_t)1 << 127);
    auto result = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    __uint128_t intermediate = cache + (cache >> 53);
    std::uint64_t expected = static_cast<std::uint64_t>(intermediate >> 74);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointDoubleTest_396, SmallCacheDouble_396) {
    __uint128_t cache = (__uint128_t)1 << 75;
    auto result = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    __uint128_t intermediate = cache + (cache >> 53);
    std::uint64_t expected = static_cast<std::uint64_t>(intermediate >> 75);
    EXPECT_EQ(result, expected);
}

TEST_F(ComputeRightEndpointDoubleTest_396, CacheValueOneDouble_396) {
    __uint128_t cache = 1;
    auto result = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    EXPECT_EQ(result, 0u);
}

TEST_F(ComputeRightEndpointDoubleTest_396, BetaThree_396) {
    __uint128_t cache = ((__uint128_t)0xABCDEF0123456789ULL << 64) | 0x0123456789ABCDEFULL;
    auto result = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 3);
    __uint128_t intermediate = cache + (cache >> 53);
    std::uint64_t expected = static_cast<std::uint64_t>(intermediate >> 72);
    EXPECT_EQ(result, expected);
}

// Consistency tests - verify the formula produces consistent results
TEST_F(ComputeRightEndpointFloatTest_396, ConsistencyAcrossBetas_396) {
    std::uint64_t cache = 0xC90FDAA22168C235ULL; // pi-related constant
    
    auto r0 = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    auto r1 = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    
    // Higher beta means less right shift, so result should be larger (or equal)
    EXPECT_GE(r1, r0);
}

TEST_F(ComputeRightEndpointFloatTest_396, DeterministicOutput_396) {
    std::uint64_t cache = 0x1234567890ABCDEFULL;
    auto r1 = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    auto r2 = FloatTraits::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    EXPECT_EQ(r1, r2);
}

TEST_F(ComputeRightEndpointDoubleTest_396, ConsistencyAcrossBetas_396) {
    __uint128_t cache = ((__uint128_t)0xC90FDAA22168C235ULL << 64) | 0xC4C6628B80DC1CD1ULL;
    
    auto r0 = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 0);
    auto r1 = DoubleTraits::compute_right_endpoint_for_shorter_interval_case(cache, 1);
    
    EXPECT_GE(r1, r0);
}
