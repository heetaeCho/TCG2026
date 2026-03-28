#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



class DragonboxImplTest : public ::testing::Test {

protected:

    using FormatTraits = /* Define a suitable FormatTraits for testing */;

    using Impl = impl<FormatTraits>;

};



TEST_F(DragonboxImplTest, IsLeftEndpointIntegerShorterInterval_ReturnsTrueForBoundaryLowerThreshold_410) {

    exponent_int binary_exponent = case_shorter_interval_left_endpoint_lower_threshold;

    EXPECT_TRUE(Impl::is_left_endpoint_integer_shorter_interval(binary_exponent));

}



TEST_F(DragonboxImplTest, IsLeftEndpointIntegerShorterInterval_ReturnsTrueForBoundaryUpperThreshold_410) {

    exponent_int binary_exponent = case_shorter_interval_left_endpoint_upper_threshold;

    EXPECT_TRUE(Impl::is_left_endpoint_integer_shorter_interval(binary_exponent));

}



TEST_F(DragonboxImplTest, IsLeftEndpointIntegerShorterInterval_ReturnsFalseBelowLowerThreshold_410) {

    exponent_int binary_exponent = case_shorter_interval_left_endpoint_lower_threshold - 1;

    EXPECT_FALSE(Impl::is_left_endpoint_integer_shorter_interval(binary_exponent));

}



TEST_F(DragonboxImplTest, IsLeftEndpointIntegerShorterInterval_ReturnsFalseAboveUpperThreshold_410) {

    exponent_int binary_exponent = case_shorter_interval_left_endpoint_upper_threshold + 1;

    EXPECT_FALSE(Impl::is_left_endpoint_integer_shorter_interval(binary_exponent));

}



} } } }
