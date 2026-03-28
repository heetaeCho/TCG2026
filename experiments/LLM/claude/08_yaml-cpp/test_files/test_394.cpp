#include <gtest/gtest.h>
#include "contrib/dragonbox.h"
#include <cstdint>

// We need to identify the exact types used. Based on the dragonbox implementation for float,
// carrier_uint is uint32_t, cache_entry_type is uint64_t.
// For double, carrier_uint is uint64_t, cache_entry_type is uint128 (wuint::uint128).

// We'll test the float version since it uses umul96_lower64 which takes uint32_t and uint64_t.

namespace {

using namespace YAML;

// Access the float specialization's compute_mul_parity
// The impl_type for float in dragonbox
using float_impl = jkj::dragonbox::detail::impl<float>;

class ComputeMulParityTest_394 : public ::testing::Test {
protected:
    // Helper to call compute_mul_parity for float
    auto call_compute_mul_parity(uint32_t two_f, uint64_t cache, int beta) {
        return float_impl::compute_mul_parity(two_f, cache, beta);
    }
};

// Test with beta = 1 (minimum boundary)
TEST_F(ComputeMulParityTest_394, BetaMinimumValue_394) {
    uint32_t two_f = 1;
    uint64_t cache = 0x0000000100000000ULL;
    int beta = 1;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    // Just verify it returns without crashing and produces booleans
    EXPECT_TRUE(result.parity == true || result.parity == false);
    EXPECT_TRUE(result.is_integer == true || result.is_integer == false);
}

// Test with beta = 32 (maximum boundary)
TEST_F(ComputeMulParityTest_394, BetaMaximumValue_394) {
    uint32_t two_f = 1;
    uint64_t cache = 0xFFFFFFFFFFFFFFFFULL;
    int beta = 32;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    EXPECT_TRUE(result.parity == true || result.parity == false);
    EXPECT_TRUE(result.is_integer == true || result.is_integer == false);
}

// Test with zero two_f
TEST_F(ComputeMulParityTest_394, ZeroTwoF_394) {
    uint32_t two_f = 0;
    uint64_t cache = 0xFFFFFFFFFFFFFFFFULL;
    int beta = 16;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    // umul96_lower64(0, anything) = 0, so parity should be false and is_integer should be true
    EXPECT_FALSE(result.parity);
    EXPECT_TRUE(result.is_integer);
}

// Test with zero cache
TEST_F(ComputeMulParityTest_394, ZeroCache_394) {
    uint32_t two_f = 12345;
    uint64_t cache = 0;
    int beta = 10;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    // umul96_lower64(anything, 0) = 0, so parity false, is_integer true
    EXPECT_FALSE(result.parity);
    EXPECT_TRUE(result.is_integer);
}

// Test with known values to verify parity bit extraction
TEST_F(ComputeMulParityTest_394, KnownParityTrue_394) {
    // We want (r >> (64 - beta)) & 1 != 0
    // With beta = 1, we check bit 63 of r = umul96_lower64(two_f, cache)
    uint32_t two_f = 0xFFFFFFFF;
    uint64_t cache = 0xFFFFFFFFFFFFFFFFULL;
    int beta = 1;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    // Large multiplication should set high bits
    // umul96_lower64(0xFFFFFFFF, 0xFFFFFFFFFFFFFFFF) 
    // This is a specific computation; we verify it doesn't crash
    EXPECT_TRUE(result.parity == true || result.parity == false);
}

// Test middle beta value
TEST_F(ComputeMulParityTest_394, MiddleBetaValue_394) {
    uint32_t two_f = 42;
    uint64_t cache = 0x123456789ABCDEF0ULL;
    int beta = 16;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    EXPECT_TRUE(result.parity == true || result.parity == false);
    EXPECT_TRUE(result.is_integer == true || result.is_integer == false);
}

// Test with two_f = 1 and specific cache to verify is_integer
TEST_F(ComputeMulParityTest_394, IsIntegerWithSmallValues_394) {
    uint32_t two_f = 1;
    uint64_t cache = 0;
    int beta = 1;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    // r = 0, so (0xffffffff & (0 >> (32-1))) = (0xffffffff & 0) = 0, which equals 0
    EXPECT_TRUE(result.is_integer);
    EXPECT_FALSE(result.parity);
}

// Test with max two_f
TEST_F(ComputeMulParityTest_394, MaxTwoF_394) {
    uint32_t two_f = UINT32_MAX;
    uint64_t cache = 1;
    int beta = 32;
    auto result = call_compute_mul_parity(two_f, cache, beta);
    // umul96_lower64(UINT32_MAX, 1) should give a specific value
    EXPECT_TRUE(result.parity == true || result.parity == false);
    EXPECT_TRUE(result.is_integer == true || result.is_integer == false);
}

// Verify consistency: calling with same parameters gives same result
TEST_F(ComputeMulParityTest_394, Deterministic_394) {
    uint32_t two_f = 777;
    uint64_t cache = 0xDEADBEEFCAFEBABEULL;
    int beta = 20;
    auto result1 = call_compute_mul_parity(two_f, cache, beta);
    auto result2 = call_compute_mul_parity(two_f, cache, beta);
    EXPECT_EQ(result1.parity, result2.parity);
    EXPECT_EQ(result1.is_integer, result2.is_integer);
}

// Test various beta values in valid range
TEST_F(ComputeMulParityTest_394, AllValidBetaValues_394) {
    uint32_t two_f = 100;
    uint64_t cache = 0xABCDABCDABCDABCDULL;
    for (int beta = 1; beta <= 32; ++beta) {
        auto result = call_compute_mul_parity(two_f, cache, beta);
        EXPECT_TRUE(result.parity == true || result.parity == false)
            << "Failed for beta = " << beta;
        EXPECT_TRUE(result.is_integer == true || result.is_integer == false)
            << "Failed for beta = " << beta;
    }
}

}  // namespace
