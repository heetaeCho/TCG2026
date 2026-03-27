#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "./TestProjects/glomap/glomap/math/rigid3d.cc"



namespace glomap {



// Test fixture for AngleAxisToRotation tests

class AngleAxisToRotationTest_147 : public ::testing::Test {

protected:

    Eigen::Vector3d angle_axis;

};



TEST_F(AngleAxisToRotationTest_147, NormalOperation_147) {

    angle_axis << 1.0, 2.0, 3.0;

    Eigen::Matrix3d rotation_matrix = AngleAxisToRotation(angle_axis);

    EXPECT_TRUE(rotation_matrix.isUnitary());

}



TEST_F(AngleAxisToRotationTest_147, ZeroAngleAxis_147) {

    angle_axis << 0.0, 0.0, 0.0;

    Eigen::Matrix3d rotation_matrix = AngleAxisToRotation(angle_axis);

    EXPECT_TRUE(rotation_matrix.isIdentity());

}



TEST_F(AngleAxisToRotationTest_147, SmallAngleAxisBelowEps_147) {

    angle_axis << EPS / 2, 0.0, 0.0;

    Eigen::Matrix3d rotation_matrix = AngleAxisToRotation(angle_axis);

    EXPECT_TRUE(rotation_matrix.isIdentity());

}



TEST_F(AngleAxisToRotationTest_147, SmallAngleAxisAboveEps_147) {

    angle_axis << EPS * 2, 0.0, 0.0;

    Eigen::Matrix3d rotation_matrix = AngleAxisToRotation(angle_axis);

    EXPECT_FALSE(rotation_matrix.isIdentity());

}



TEST_F(AngleAxisToRotationTest_147, LargeAngleAxis_147) {

    angle_axis << 100.0, 200.0, 300.0;

    Eigen::Matrix3d rotation_matrix = AngleAxisToRotation(angle_axis);

    EXPECT_TRUE(rotation_matrix.isUnitary());

}



TEST_F(AngleAxisToRotationTest_147, NegativeAngleAxis_147) {

    angle_axis << -1.0, -2.0, -3.0;

    Eigen::Matrix3d rotation_matrix = AngleAxisToRotation(angle_axis);

    EXPECT_TRUE(rotation_matrix.isUnitary());

}



TEST_F(AngleAxisToRotationTest_147, BoundaryConditionEps_147) {

    angle_axis << EPS, 0.0, 0.0;

    Eigen::Matrix3d rotation_matrix = AngleAxisToRotation(angle_axis);

    EXPECT_FALSE(rotation_matrix.isIdentity());

}



} // namespace glomap
