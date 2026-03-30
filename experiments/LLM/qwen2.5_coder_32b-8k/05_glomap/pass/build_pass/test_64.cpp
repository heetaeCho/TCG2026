#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Eigen/Dense>

#include "glomap/math/gravity.cc"



namespace {



using ::testing::DoubleEq;



class CalcAngleTest_64 : public ::testing::Test {

protected:

    Eigen::Vector3d gravity1;

    Eigen::Vector3d gravity2;



    void SetUp() override {

        gravity1 = Eigen::Vector3d(0, 0, 1);

        gravity2 = Eigen::Vector3d(0, 0, 1);

    }

};



TEST_F(CalcAngleTest_64, IdenticalVectorsReturnZero_64) {

    EXPECT_THAT(glomap::CalcAngle(gravity1, gravity2), DoubleEq(0.0));

}



TEST_F(CalcAngleTest_64, OrthogonalVectorsReturnNinety_64) {

    gravity2 = Eigen::Vector3d(1, 0, 0);

    EXPECT_THAT(glomap::CalcAngle(gravity1, gravity2), DoubleEq(90.0));

}



TEST_F(CalcAngleTest_64, OppositeVectorsReturnEighteenZero_64) {

    gravity2 = Eigen::Vector3d(0, 0, -1);

    EXPECT_THAT(glomap::CalcAngle(gravity1, gravity2), DoubleEq(180.0));

}



TEST_F(CalcAngleTest_64, SmallAngleVectorsReturnCorrectValue_64) {

    gravity2 = Eigen::Vector3d(0, 0.1, 1);

    EXPECT_NEAR(glomap::CalcAngle(gravity1, gravity2), 5.729577951308232, 1e-9);

}



TEST_F(CalcAngleTest_64, BoundaryConditionWithZeroVector_64) {

    gravity2 = Eigen::Vector3d(0, 0, 0);

    EXPECT_THROW(glomap::CalcAngle(gravity1, gravity2), std::runtime_error); // Assuming it throws an error for zero vector

}



TEST_F(CalcAngleTest_64, LargeValuesVectorsReturnCorrectValue_64) {

    gravity1 = Eigen::Vector3d(1e9, 0, 1e9);

    gravity2 = Eigen::Vector3d(0, 1e9, 0);

    EXPECT_NEAR(glomap::CalcAngle(gravity1, gravity2), 90.0, 1e-9);

}



} // namespace
