#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Eigen/Dense>

#include "rigid3d.cc" // Assuming this file is included in the test environment



namespace glomap {



class CalcAngleTest_144 : public ::testing::Test {

protected:

    Eigen::Matrix3d identity_matrix = Eigen::Matrix3d::Identity();

    Eigen::Matrix3d rotation_x_pi_over_2;

    

    CalcAngleTest_144() {

        // Initialize a 90-degree rotation matrix around the x-axis

        double angle = EIGEN_PI / 2;

        rotation_x_pi_over_2 << 

            1, 0, 0,

            0, std::cos(angle), -std::sin(angle),

            0, std::sin(angle), std::cos(angle);

    }

};



TEST_F(CalcAngleTest_144, IdentityMatrices_ReturnZeroAngle_144) {

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, identity_matrix), 0.0);

}



TEST_F(CalcAngleTest_144, SameRotationMatrix_ReturnZeroAngle_144) {

    EXPECT_DOUBLE_EQ(CalcAngle(rotation_x_pi_over_2, rotation_x_pi_over_2), 0.0);

}



TEST_F(CalcAngleTest_144, OrthogonalRotations_Return90DegreeAngle_144) {

    EXPECT_NEAR(CalcAngle(identity_matrix, rotation_x_pi_over_2), 90.0, 1e-6);

}



TEST_F(CalcAngleTest_144, OppositeRotations_Return180DegreeAngle_144) {

    EXPECT_NEAR(CalcAngle(rotation_x_pi_over_2, rotation_x_pi_over_2.transpose()), 180.0, 1e-6);

}



TEST_F(CalcAngleTest_144, CosineClamping_LowerBound_144) {

    Eigen::Matrix3d invalid_matrix;

    invalid_matrix << 

        -2, 0, 0,

        0, 1, 0,

        0, 0, 1;

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, invalid_matrix), 180.0);

}



TEST_F(CalcAngleTest_144, CosineClamping_UpperBound_144) {

    Eigen::Matrix3d invalid_matrix;

    invalid_matrix << 

        2, 0, 0,

        0, 1, 0,

        0, 0, 1;

    EXPECT_DOUBLE_EQ(CalcAngle(identity_matrix, invalid_matrix), 0.0);

}



} // namespace glomap
