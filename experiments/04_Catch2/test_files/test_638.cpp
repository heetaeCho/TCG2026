#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_polyfills.cpp"



using namespace Catch;

using ::testing::DoubleEq;



TEST(nextafter_638, NormalOperation_638) {

    EXPECT_THAT(nextafter(1.0, 2.0), DoubleEq(1.0 + std::numeric_limits<double>::epsilon()));

}



TEST(nextafter_638, BoundaryCondition_PositiveInfinity_638) {

    EXPECT_EQ(nextafter(std::numeric_limits<double>::max(), std::numeric_limits<double>::infinity()), std::numeric_limits<double>::infinity());

}



TEST(nextafter_638, BoundaryCondition_NegativeInfinity_638) {

    EXPECT_EQ(nextafter(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::infinity()), -std::numeric_limits<double>::infinity());

}



TEST(nextafter_638, BoundaryCondition_ZeroToPositive_638) {

    EXPECT_THAT(nextafter(0.0, 1.0), DoubleEq(std::numeric_limits<double>::denorm_min()));

}



TEST(nextafter_638, BoundaryCondition_ZeroToNegative_638) {

    EXPECT_THAT(nextafter(0.0, -1.0), DoubleEq(-std::numeric_limits<double>::denorm_min()));

}



TEST(nextafter_638, BoundaryCondition_DenormalMinToPositive_638) {

    EXPECT_EQ(nextafter(std::numeric_limits<double>::denorm_min(), 1.0), std::numeric_limits<double>::min());

}



TEST(nextafter_638, BoundaryCondition_DenormalMinToNegative_638) {

    EXPECT_EQ(nextafter(-std::numeric_limits<double>::denorm_min(), -1.0), -std::numeric_limits<double>::min());

}
