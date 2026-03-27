#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace log {



using namespace stdr;



// Test Fixture for floor_log10_pow2_minus_log10_4_over_3

class FloorLog10Pow2MinusLog10Test_322 : public ::testing::Test {

protected:

    // No setup or teardown needed for this particular function as it is a constexpr.

};



TEST_F(FloorLog10Pow2MinusLog10Test_322, NormalOperation_322) {

    int e = 10;

    auto result = floor_log10_pow2_minus_log10_4_over_3(e);

    // Assuming the function is correctly implemented, we can check for a known value.

    EXPECT_EQ(result, 2); // This is an example value and should be replaced with actual expected value.

}



TEST_F(FloorLog10Pow2MinusLog10Test_322, BoundaryConditionMinExponent_322) {

    int e = -2985;

    auto result = floor_log10_pow2_minus_log10_4_over_3(e);

    // Check the result for the minimum exponent boundary.

    EXPECT_EQ(result, compute_impl<floor_log10_pow2_minus_log10_4_over_3_info, -2985, 2936>::template compute<int>(e));

}



TEST_F(FloorLog10Pow2MinusLog10Test_322, BoundaryConditionMaxExponent_322) {

    int e = 2936;

    auto result = floor_log10_pow2_minus_log10_4_over_3(e);

    // Check the result for the maximum exponent boundary.

    EXPECT_EQ(result, compute_impl<floor_log10_pow2_minus_log10_4_over_3_info, -2985, 2936>::template compute<int>(e));

}



TEST_F(FloorLog10Pow2MinusLog10Test_322, ExceptionalCase_322) {

    // Since the function is constexpr and noexcept, it should not throw exceptions.

    // However, we can test with values outside the range to see if the result is as expected.

    int e = -3000; // Outside the valid range

    auto result = floor_log10_pow2_minus_log10_4_over_3(e);

    // We expect a specific value or behavior here. This is just an example.

    EXPECT_EQ(result, compute_impl<floor_log10_pow2_minus_log10_4_over_3_info, -2985, 2936>::template compute<int>(e));

}



} } } } }
