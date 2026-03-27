#include <gtest/gtest.h>



using namespace YAML::jkj::dragonbox::detail;



TEST_F(DragonboxImplTest_409, IsRightEndpointIntegerShorterInterval_ReturnsTrueForBoundaryLowerThreshold_409) {

    EXPECT_TRUE(impl::is_right_endpoint_integer_shorter_interval(case_shorter_interval_right_endpoint_lower_threshold));

}



TEST_F(DragonboxImplTest_409, IsRightEndpointIntegerShorterInterval_ReturnsTrueForBoundaryUpperThreshold_409) {

    EXPECT_TRUE(impl::is_right_endpoint_integer_shorter_interval(case_shorter_interval_right_endpoint_upper_threshold));

}



TEST_F(DragonboxImplTest_409, IsRightEndpointIntegerShorterInterval_ReturnsFalseBelowLowerThreshold_409) {

    EXPECT_FALSE(impl::is_right_endpoint_integer_shorter_interval(case_shorter_interval_right_endpoint_lower_threshold - 1));

}



TEST_F(DragonboxImplTest_409, IsRightEndpointIntegerShorterInterval_ReturnsFalseAboveUpperThreshold_409) {

    EXPECT_FALSE(impl::is_right_endpoint_integer_shorter_interval(case_shorter_interval_right_endpoint_upper_threshold + 1));

}



TEST_F(DragonboxImplTest_409, IsRightEndpointIntegerShorterInterval_ReturnsTrueWithinRange_409) {

    exponent_int mid_value = (case_shorter_interval_right_endpoint_lower_threshold + case_shorter_interval_right_endpoint_upper_threshold) / 2;

    EXPECT_TRUE(impl::is_right_endpoint_integer_shorter_interval(mid_value));

}
