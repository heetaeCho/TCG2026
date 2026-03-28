#include <gtest/gtest.h>

#include "helper_functions.cpp"



namespace Exiv2 {



class GetAspectRatioTest_121 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(GetAspectRatioTest_121, NormalOperationSquare_121) {

    EXPECT_EQ(getAspectRatio(100, 100), "1:1");

}



TEST_F(GetAspectRatioTest_121, NormalOperationRectangleWidthGreaterThanHeight_121) {

    EXPECT_EQ(getAspectRatio(400, 300), "4:3");

}



TEST_F(GetAspectRatioTest_121, NormalOperationRectangleHeightGreaterThanWidth_121) {

    EXPECT_EQ(getAspectRatio(300, 400), "3:4");

}



TEST_F(GetAspectRatioTest_121, BoundaryConditionZeroWidth_121) {

    EXPECT_EQ(getAspectRatio(0, 100), "0:100");

}



TEST_F(GetAspectRatioTest_121, BoundaryConditionZeroHeight_121) {

    EXPECT_EQ(getAspectRatio(100, 0), "100:0");

}



TEST_F(GetAspectRatioTest_121, BoundaryConditionBothZero_121) {

    EXPECT_EQ(getAspectRatio(0, 0), "0:0");

}



} // namespace Exiv2
