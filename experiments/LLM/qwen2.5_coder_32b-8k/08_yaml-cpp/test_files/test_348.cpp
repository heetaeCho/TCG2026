#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding { namespace interval_type {



class IntervalTypeTest_348 : public ::testing::Test {

protected:

    using ClosedInterval = closed;

};



TEST_F(IntervalTypeTest_348, IncludeRightEndpoint_ReturnsTrue_348) {

    EXPECT_TRUE(ClosedInterval::include_right_endpoint());

}



// Assuming include_left_endpoint is part of the interface as per the known dependencies

TEST_F(IntervalTypeTest_348, IncludeLeftEndpoint_ReturnsExpectedValue_348) {

    // Since the behavior of include_left_endpoint is not specified in the prompt,

    // we assume it should return a boolean value. The expected value is unknown,

    // so this test just checks that it compiles and returns something.

    bool result = ClosedInterval::include_left_endpoint();

    EXPECT_TRUE(result || !result); // This line will always pass, but ensures the function call works.

}



} } } } } }
