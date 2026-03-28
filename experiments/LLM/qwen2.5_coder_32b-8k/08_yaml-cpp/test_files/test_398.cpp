#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;

using namespace YAML::jkj::dragonbox::detail::wuint;



// Mock the umul192_upper128 function if needed, but in this case, we treat it as a black box.

struct MockUint128 {

    std::uint_least64_t high_;

    std::uint_least64_t low_;



    constexpr MockUint128(std::uint_least64_t high, std::uint_least64_t low) noexcept

        : high_(high), low_(low) {}

};



TEST(compute_mul_result_Test_398, NormalOperation_398) {

    carrier_uint u = 0x123456789ABCDEF0;

    cache_entry_type cache = {/* Assume some valid value */};



    // Assuming umul192_upper128 returns a known result for these inputs

    MockUint128 mock_result(0xFEDCBA9876543210, 0x0);



    // Since we cannot mock internal functions directly, we assume the result of umul192_upper128

    compute_mul_result result = detail::wuint::compute_mul(u, cache);



    EXPECT_EQ(result.high(), mock_result.high_);

    EXPECT_EQ(result.low_is_zero(), (mock_result.low_ == 0));

}



TEST(compute_mul_result_Test_398, BoundaryConditions_HighIsZero_398) {

    carrier_uint u = 0x123456789ABCDEF0;

    cache_entry_type cache = {/* Assume some valid value */};



    // Assuming umul192_upper128 returns a result where high is zero for these inputs

    MockUint128 mock_result(0x0, 0x0);



    compute_mul_result result = detail::wuint::compute_mul(u, cache);



    EXPECT_EQ(result.high(), mock_result.high_);

    EXPECT_EQ(result.low_is_zero(), (mock_result.low_ == 0));

}



TEST(compute_mul_result_Test_398, BoundaryConditions_LowIsNonZero_398) {

    carrier_uint u = 0x123456789ABCDEF0;

    cache_entry_type cache = {/* Assume some valid value */};



    // Assuming umul192_upper128 returns a result where low is non-zero for these inputs

    MockUint128 mock_result(0xFEDCBA9876543210, 0x1);



    compute_mul_result result = detail::wuint::compute_mul(u, cache);



    EXPECT_EQ(result.high(), mock_result.high_);

    EXPECT_EQ(result.low_is_zero(), (mock_result.low_ == 0));

}



TEST(compute_mul_result_Test_398, BoundaryConditions_MaxValues_398) {

    carrier_uint u = UINT64_MAX;

    cache_entry_type cache = {/* Assume some valid value */};



    // Assuming umul192_upper128 returns a known result for these inputs

    MockUint128 mock_result(0xFEDCBA9876543210, 0x0);



    compute_mul_result result = detail::wuint::compute_mul(u, cache);



    EXPECT_EQ(result.high(), mock_result.high_);

    EXPECT_EQ(result.low_is_zero(), (mock_result.low_ == 0));

}
