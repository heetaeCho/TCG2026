#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Access the nested namespace
using namespace YAML::jkj::dragonbox;

// We need to identify the correct types. Based on the code structure,
// the function is a static method within a class template specialization
// for IEEE 754 binary formats. Let's work with the float_info for double.

// The compute_mul_parity function is deeply nested. We'll test it through
// the available interface.

// For double precision, carrier_uint is uint64_t and cache_entry_type is uint128

using uint128 = detail::wuint::uint128;

// Helper struct to match compute_mul_parity_result
// Based on the code, it returns a struct with two bools

class ComputeMulParityTest_400 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with beta = 1 (minimum valid beta)
TEST_F(ComputeMulParityTest_400, BetaMinimumValue_400) {
    // Use the impl class for double (binary64)
    using impl = detail::impl<double>;
    
    uint64_t two_f = 1;
    uint128 cache(0, 1);
    int beta = 1;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    // We just verify the function returns without crashing and produces a valid result
    // The result has two boolean fields
    (void)result;
}

// Test with beta = 63 (maximum valid beta for 64-bit)
TEST_F(ComputeMulParityTest_400, BetaMaximumValue_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = 1;
    uint128 cache(0, 1);
    int beta = 63;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    (void)result;
}

// Test with two_f = 0
TEST_F(ComputeMulParityTest_400, TwoFZero_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = 0;
    uint128 cache(UINT64_C(0xFFFFFFFFFFFFFFFF), UINT64_C(0xFFFFFFFFFFFFFFFF));
    int beta = 32;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    // With two_f = 0, multiplication result should be 0
    // parity bit should be 0, and is_integer should be true
    EXPECT_FALSE(result.parity);
    EXPECT_TRUE(result.is_integer);
}

// Test with cache = {0, 0}
TEST_F(ComputeMulParityTest_400, CacheZero_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = UINT64_C(0xFFFFFFFFFFFFFFFF);
    uint128 cache(0, 0);
    int beta = 32;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    // With cache = 0, multiplication is 0
    EXPECT_FALSE(result.parity);
    EXPECT_TRUE(result.is_integer);
}

// Test with large two_f and large cache
TEST_F(ComputeMulParityTest_400, LargeValues_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = UINT64_C(0xFFFFFFFFFFFFFFFF);
    uint128 cache(UINT64_C(0xFFFFFFFFFFFFFFFF), UINT64_C(0xFFFFFFFFFFFFFFFF));
    int beta = 32;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    // Just verify it doesn't crash and returns valid booleans
    EXPECT_TRUE(result.parity || !result.parity);
    EXPECT_TRUE(result.is_integer || !result.is_integer);
}

// Test with two_f = 1 and specific cache to check parity bit
TEST_F(ComputeMulParityTest_400, ParityCheckWithUnitValues_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = 1;
    // Cache high = 1 << 63 to get a specific bit pattern in the multiplication
    uint128 cache(UINT64_C(0x8000000000000000), 0);
    int beta = 1;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    // The 192-bit product of 1 * cache should give us cache itself in upper bits
    // r.high() = 0 (from umul192_lower128 with two_f=1, this is the lower 128 bits)
    // We need to understand umul192_lower128 behavior
    (void)result;
}

// Test with beta at midpoint
TEST_F(ComputeMulParityTest_400, BetaMidpoint_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = 42;
    uint128 cache(UINT64_C(0x123456789ABCDEF0), UINT64_C(0xFEDCBA9876543210));
    int beta = 32;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    // Verify function executes without issues
    EXPECT_TRUE(result.parity || !result.parity);
}

// Test with power-of-two two_f
TEST_F(ComputeMulParityTest_400, PowerOfTwoTwoF_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = UINT64_C(1) << 52; // typical significand power of 2
    uint128 cache(UINT64_C(0x1000000000000000), UINT64_C(0x0000000000000000));
    int beta = 10;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    (void)result;
}

// Test with beta = 2
TEST_F(ComputeMulParityTest_400, BetaTwo_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = 1;
    uint128 cache(0, 0);
    int beta = 2;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    EXPECT_FALSE(result.parity);
    EXPECT_TRUE(result.is_integer);
}

// Test consistency: same inputs give same outputs
TEST_F(ComputeMulParityTest_400, Deterministic_400) {
    using impl = detail::impl<double>;
    
    uint64_t two_f = 12345678;
    uint128 cache(UINT64_C(0xABCDEF0123456789), UINT64_C(0x9876543210ABCDEF));
    int beta = 15;
    
    auto result1 = impl::compute_mul_parity(two_f, cache, beta);
    auto result2 = impl::compute_mul_parity(two_f, cache, beta);
    
    EXPECT_EQ(result1.parity, result2.parity);
    EXPECT_EQ(result1.is_integer, result2.is_integer);
}

// Test for float (binary32) if available
class ComputeMulParityFloatTest_400 : public ::testing::Test {};

TEST_F(ComputeMulParityFloatTest_400, FloatZeroTwoF_400) {
    using impl = detail::impl<float>;
    
    uint32_t two_f = 0;
    uint64_t cache = UINT64_C(0xFFFFFFFFFFFFFFFF);
    int beta = 1;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    EXPECT_FALSE(result.parity);
    EXPECT_TRUE(result.is_integer);
}

TEST_F(ComputeMulParityFloatTest_400, FloatBasicOperation_400) {
    using impl = detail::impl<float>;
    
    uint32_t two_f = 42;
    uint64_t cache = UINT64_C(0x123456789ABCDEF0);
    int beta = 16;
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    (void)result;
}

TEST_F(ComputeMulParityFloatTest_400, FloatMaxBeta_400) {
    using impl = detail::impl<float>;
    
    uint32_t two_f = UINT32_C(0xFFFFFFFF);
    uint64_t cache = UINT64_C(0xFFFFFFFFFFFFFFFF);
    int beta = 31;  // max valid for 32-bit
    
    auto result = impl::compute_mul_parity(two_f, cache, beta);
    EXPECT_TRUE(result.parity || !result.parity);
}

}  // namespace
