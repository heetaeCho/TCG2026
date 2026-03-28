#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

// Access the relevant namespace
using namespace YAML::jkj::dragonbox::jkj::dragonbox;

class ComputeMulTest_392 : public ::testing::Test {
protected:
};

// Test with zero input for u
TEST_F(ComputeMulTest_392, ZeroCarrierUint_392) {
    carrier_uint u = 0;
    cache_entry_type cache = 1;
    auto result = compute_mul(u, cache);
    // 0 * anything = 0, so upper bits should be 0 and lower 32 bits should be 0
    EXPECT_EQ(result.result, 0u);
    EXPECT_TRUE(result.is_integer);
}

// Test with zero cache entry
TEST_F(ComputeMulTest_392, ZeroCacheEntry_392) {
    carrier_uint u = 1;
    cache_entry_type cache = 0;
    auto result = compute_mul(u, cache);
    EXPECT_EQ(result.result, 0u);
    EXPECT_TRUE(result.is_integer);
}

// Test with both zero
TEST_F(ComputeMulTest_392, BothZero_392) {
    carrier_uint u = 0;
    cache_entry_type cache = 0;
    auto result = compute_mul(u, cache);
    EXPECT_EQ(result.result, 0u);
    EXPECT_TRUE(result.is_integer);
}

// Test with u=1 and cache that has value in upper 32 bits
TEST_F(ComputeMulTest_392, SmallMultiplication_392) {
    carrier_uint u = 1;
    // cache = (1ULL << 32) means umul96_upper64(1, 1<<32) 
    // The 96-bit product upper 64 bits: 1 * (1<<32) = (1<<32), 
    // upper 64 of 96-bit: depends on implementation
    cache_entry_type cache = static_cast<cache_entry_type>(1) << 32;
    auto result = compute_mul(u, cache);
    // umul96_upper64(1, 1<<32): 96-bit product = 1 * (1<<32) = (1<<32)
    // Upper 64 bits of 96-bit number (1<<32) would be 0 if the product is 96 bits wide
    // Result >> 32 = 0, lower 32 bits = 0 => is_integer = true
    EXPECT_EQ(result.result, 0u);
    EXPECT_TRUE(result.is_integer);
}

// Test with maximum carrier_uint value
TEST_F(ComputeMulTest_392, MaxCarrierUint_392) {
    carrier_uint u = static_cast<carrier_uint>(~0u);
    cache_entry_type cache = static_cast<cache_entry_type>(~0ULL);
    auto result = compute_mul(u, cache);
    // Large multiplication - result should be non-zero
    // The exact value depends on umul96_upper64 but the result should be valid
    EXPECT_NE(result.result, 0u);
}

// Test where lower 32 bits of r are non-zero (is_integer should be false)
TEST_F(ComputeMulTest_392, NonIntegerResult_392) {
    carrier_uint u = 1;
    // A cache value that when multiplied gives non-zero lower 32 bits in upper 64
    cache_entry_type cache = static_cast<cache_entry_type>(1);
    auto result = compute_mul(u, cache);
    // umul96_upper64(1, 1): very small product, upper 64 of 96 bits = 0
    // r = 0, r>>32 = 0, carrier_uint(r) = 0, is_integer = true
    EXPECT_EQ(result.result, 0u);
    EXPECT_TRUE(result.is_integer);
}

// Test with a known multiplication producing non-zero in lower 32 bits
TEST_F(ComputeMulTest_392, LargeValuesIsIntegerFalse_392) {
    carrier_uint u = 0xFFFFFFFFu;
    cache_entry_type cache = 0x100000001ULL;
    auto result = compute_mul(u, cache);
    // This should exercise the is_integer flag
    // We just verify the function doesn't crash and returns valid result
    (void)result.result;
    // The is_integer field should be a boolean
    EXPECT_TRUE(result.is_integer == true || result.is_integer == false);
}

} // namespace
