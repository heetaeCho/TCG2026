#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::log;



// Test fixture for floor_log2 function

class FloorLog2Test_315 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



TEST_F(FloorLog2Test_315, ZeroInputReturnsNegativeOne_315) {

    EXPECT_EQ(floor_log2(0u), -1);

}



TEST_F(FloorLog2Test_315, OneInputReturnsZero_315) {

    EXPECT_EQ(floor_log2(1u), 0);

}



TEST_F(FloorLog2Test_315, TwoInputReturnsOne_315) {

    EXPECT_EQ(floor_log2(2u), 1);

}



TEST_F(FloorLog2Test_315, ThreeInputReturnsOne_315) {

    EXPECT_EQ(floor_log2(3u), 1);

}



TEST_F(FloorLog2Test_315, FourInputReturnsTwo_315) {

    EXPECT_EQ(floor_log2(4u), 2);

}



TEST_F(FloorLog2Test_315, EightInputReturnsThree_315) {

    EXPECT_EQ(floor_log2(8u), 3);

}



TEST_F(FloorLog2Test_315, MaxUnsignedIntInputReturnsThirtyOneOrSixtyThree_315) {

    #ifdef UINT_MAX

        EXPECT_EQ(floor_log2(UINT_MAX), sizeof(unsigned int) * 8 - 1);

    #endif

}
