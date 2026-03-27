#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::binary_to_decimal_rounding;



// Since the struct 'toward_zero' and its static method 'prefer_round_down' do not have any external dependencies,

// there's no need to use Google Mock in this case. We will focus on verifying the return value of the function.



class TowardZeroPolicyTest_389 : public ::testing::Test {

protected:

    using CarrierUInt = uint64_t; // Assuming a common type for testing, can be changed as needed

};



TEST_F(TowardZeroPolicyTest_389, PreferRoundDown_AlwaysReturnsTrue_389) {

    EXPECT_TRUE(toward_zero::prefer_round_down<CarrierUInt>(0));

    EXPECT_TRUE(toward_zero::prefer_round_down<CarrierUInt>(1));

    EXPECT_TRUE(toward_zero::prefer_round_down<CarrierUInt>(std::numeric_limits<CarrierUInt>::max()));

}



TEST_F(TowardZeroPolicyTest_389, PreferRoundDown_BoundaryValuesReturnTrue_389) {

    EXPECT_TRUE(toward_zero::prefer_round_down<CarrierUInt>(std::numeric_limits<CarrierUInt>::min()));

    EXPECT_TRUE(toward_zero::prefer_round_down<CarrierUInt>(std::numeric_limits<CarrierUInt>::max() - 1));

}
