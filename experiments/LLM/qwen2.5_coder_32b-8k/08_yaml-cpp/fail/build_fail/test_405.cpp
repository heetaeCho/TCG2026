#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



TEST_F(DragonboxImplTest_405, MaxReturnsLargerValue_405) {

    EXPECT_EQ(impl::max(1, 2), 2);

}



TEST_F(DragonboxImplTest_405, MaxReturnsSameValueWhenEqual_405) {

    EXPECT_EQ(impl::max(3, 3), 3);

}



TEST_F(DragonboxImplTest_405, MaxHandlesNegativeValues_405) {

    EXPECT_EQ(impl::max(-1, -2), -1);

}



TEST_F(DragonboxImplTest_405, MaxHandlesMixedSignValues_405) {

    EXPECT_EQ(impl::max(-1, 1), 1);

}



// Assuming compute_nearest and other templated functions have observable behavior through return values or interactions

// Since the actual implementation is not provided, we can only create placeholder tests for these functions



TEST_F(DragonboxImplTest_405, ComputeNearestHandlesBasicCase_405) {

    // Placeholder test case, actual logic cannot be verified without implementation details

    // Assuming compute_nearest returns some expected type and value based on input parameters

}



TEST_F(DragonboxImplTest_405, IsRightEndpointIntegerShorterIntervalBoundaryCondition_405) {

    // Placeholder test case, actual logic cannot be verified without implementation details

    // Assuming is_right_endpoint_integer_shorter_interval returns a bool based on binary_exponent

}



TEST_F(DragonboxImplTest_405, IsLeftEndpointIntegerShorterIntervalBoundaryCondition_405) {

    // Placeholder test case, actual logic cannot be verified without implementation details

    // Assuming is_left_endpoint_integer_shorter_interval returns a bool based on binary_exponent

}



}}}}
