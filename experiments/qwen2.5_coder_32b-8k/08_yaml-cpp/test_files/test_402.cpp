#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace wuint {



class DragonboxTest_402 : public ::testing::Test {

protected:

    using ShiftAmountType = std::size_t;

    cache_entry_type cache;



    void SetUp() override {

        // Initialize the cache with some values

        cache.high_ = 123456789;

        cache.low_ = 987654321;

    }

};



TEST_F(DragonboxTest_402, ComputeRightEndpointForShorterIntervalCase_NormalOperation_402) {

    ShiftAmountType beta = 5;

    carrier_uint result = wuint::compute_right_endpoint_for_shorter_interval_case(cache, beta);

    // Expected result is calculated based on the formula provided in the function

    carrier_uint expected = (cache.high() + (cache.high() >> (significand_bits + 1))) >> ShiftAmountType(total_bits - significand_bits - 1 - beta);

    EXPECT_EQ(result, expected);

}



TEST_F(DragonboxTest_402, ComputeRightEndpointForShorterIntervalCase_BoundaryCondition_BetaZero_402) {

    ShiftAmountType beta = 0;

    carrier_uint result = wuint::compute_right_endpoint_for_shorter_interval_case(cache, beta);

    // Expected result is calculated based on the formula provided in the function with beta = 0

    carrier_uint expected = (cache.high() + (cache.high() >> (significand_bits + 1))) >> ShiftAmountType(total_bits - significand_bits - 1);

    EXPECT_EQ(result, expected);

}



TEST_F(DragonboxTest_402, ComputeRightEndpointForShorterIntervalCase_BoundaryCondition_MaxBeta_402) {

    ShiftAmountType beta = std::numeric_limits<ShiftAmountType>::max();

    carrier_uint result = wuint::compute_right_endpoint_for_shorter_interval_case(cache, beta);

    // Expected result is calculated based on the formula provided in the function with max beta

    carrier_uint expected = (cache.high() + (cache.high() >> (significand_bits + 1))) >> ShiftAmountType(total_bits - significand_bits - 1 - beta);

    EXPECT_EQ(result, expected);

}



TEST_F(DragonboxTest_402, ComputeRightEndpointForShorterIntervalCase_LargeHighValue_402) {

    cache.high_ = std::numeric_limits<std::uint_least64_t>::max();

    ShiftAmountType beta = 5;

    carrier_uint result = wuint::compute_right_endpoint_for_shorter_interval_case(cache, beta);

    // Expected result is calculated based on the formula provided in the function with max high value

    carrier_uint expected = (cache.high() + (cache.high() >> (significand_bits + 1))) >> ShiftAmountType(total_bits - significand_bits - 1 - beta);

    EXPECT_EQ(result, expected);

}



TEST_F(DragonboxTest_402, ComputeRightEndpointForShorterIntervalCase_ZeroHighValue_402) {

    cache.high_ = 0;

    ShiftAmountType beta = 5;

    carrier_uint result = wuint::compute_right_endpoint_for_shorter_interval_case(cache, beta);

    // Expected result is calculated based on the formula provided in the function with zero high value

    carrier_uint expected = (cache.high() + (cache.high() >> (significand_bits + 1))) >> ShiftAmountType(total_bits - significand_bits - 1 - beta);

    EXPECT_EQ(result, expected);

}



} } } } } }
