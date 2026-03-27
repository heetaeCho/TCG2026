#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "gravity.cc"



namespace glomap {

    class CalcAngleTest_134 : public ::testing::Test {

    protected:

        Eigen::Vector3d gravity1;

        Eigen::Vector3d gravity2;



        void SetUp() override {

            gravity1 = Eigen::Vector3d(1.0, 0.0, 0.0);

            gravity2 = Eigen::Vector3d(0.0, 1.0, 0.0);

        }

    };



    TEST_F(CalcAngleTest_134, OrthogonalVectors_Returns90Degrees_134) {

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_DOUBLE_EQ(angle, 90.0);

    }



    TEST_F(CalcAngleTest_134, ParallelVectorsSameDirection_Returns0Degrees_134) {

        gravity2 = Eigen::Vector3d(1.0, 0.0, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_DOUBLE_EQ(angle, 0.0);

    }



    TEST_F(CalcAngleTest_134, ParallelVectorsOppositeDirection_Returns180Degrees_134) {

        gravity2 = Eigen::Vector3d(-1.0, 0.0, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_DOUBLE_EQ(angle, 180.0);

    }



    TEST_F(CalcAngleTest_134, IdenticalVectors_Returns0Degrees_134) {

        gravity2 = Eigen::Vector3d(1.0, 0.0, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_DOUBLE_EQ(angle, 0.0);

    }



    TEST_F(CalcAngleTest_134, ZeroLengthFirstVector_ReturnsNaN_134) {

        gravity1 = Eigen::Vector3d(0.0, 0.0, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_TRUE(std::isnan(angle));

    }



    TEST_F(CalcAngleTest_134, ZeroLengthSecondVector_ReturnsNaN_134) {

        gravity2 = Eigen::Vector3d(0.0, 0.0, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_TRUE(std::isnan(angle));

    }



    TEST_F(CalcAngleTest_134, ZeroLengthBothVectors_ReturnsNaN_134) {

        gravity1 = Eigen::Vector3d(0.0, 0.0, 0.0);

        gravity2 = Eigen::Vector3d(0.0, 0.0, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_TRUE(std::isnan(angle));

    }



    TEST_F(CalcAngleTest_134, LargeVectors_ReturnsCorrectAngle_134) {

        gravity1 = Eigen::Vector3d(1e9, 0.0, 0.0);

        gravity2 = Eigen::Vector3d(0.0, 1e9, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_DOUBLE_EQ(angle, 90.0);

    }



    TEST_F(CalcAngleTest_134, SmallVectors_ReturnsCorrectAngle_134) {

        gravity1 = Eigen::Vector3d(1e-9, 0.0, 0.0);

        gravity2 = Eigen::Vector3d(0.0, 1e-9, 0.0);

        double angle = CalcAngle(gravity1, gravity2);

        EXPECT_DOUBLE_EQ(angle, 90.0);

    }



} // namespace glomap
