#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/minoltamn_int.cpp"



namespace {



class InRangeTest : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(InRangeTest_1017, ValueInRange_ReturnsTrue_1017) {

    EXPECT_TRUE(Exiv2::Internal::inRange(5, 1, 10));

}



TEST_F(InRangeTest_1017, ValueAtMinBoundary_ReturnsTrue_1017) {

    EXPECT_TRUE(Exiv2::Internal::inRange(1, 1, 10));

}



TEST_F(InRangeTest_1017, ValueAtMaxBoundary_ReturnsTrue_1017) {

    EXPECT_TRUE(Exiv2::Internal::inRange(10, 1, 10));

}



TEST_F(InRangeTest_1017, ValueBelowMin_ReturnsFalse_1017) {

    EXPECT_FALSE(Exiv2::Internal::inRange(0, 1, 10));

}



TEST_F(InRangeTest_1017, ValueAboveMax_ReturnsFalse_1017) {

    EXPECT_FALSE(Exiv2::Internal::inRange(11, 1, 10));

}



TEST_F(InRangeTest_1017, NegativeValueInRange_ReturnsTrue_1017) {

    EXPECT_TRUE(Exiv2::Internal::inRange(-5, -10, 0));

}



TEST_F(InRangeTest_1017, NegativeMinNegativeValueInRange_ReturnsTrue_1017) {

    EXPECT_TRUE(Exiv2::Internal::inRange(-5, -10, -1));

}



TEST_F(InRangeTest_1017, NegativeMaxNegativeValueInRange_ReturnsTrue_1017) {

    EXPECT_TRUE(Exiv2::Internal::inRange(-5, -6, 0));

}



TEST_F(InRangeTest_1017, ZeroInZeroRange_ReturnsTrue_1017) {

    EXPECT_TRUE(Exiv2::Internal::inRange(0, 0, 0));

}



TEST_F(InRangeTest_1017, SingleValueRangeOutside_ReturnsFalse_1017) {

    EXPECT_FALSE(Exiv2::Internal::inRange(1, 0, 0));

}



}  // namespace
