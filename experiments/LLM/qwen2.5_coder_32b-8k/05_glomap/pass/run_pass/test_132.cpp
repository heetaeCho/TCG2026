#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Eigen/Dense"

#include <cmath>



namespace glomap {

    double RotUpToAngle(const Eigen::Matrix3d& R_up);

}



using namespace testing;



TEST(RotUpToAngleTest_132, NormalOperation_132) {

    Eigen::Matrix3d identity = Eigen::Matrix3d::Identity();

    EXPECT_DOUBLE_EQ(glomap::RotUpToAngle(identity), 0.0);



    Eigen::Matrix3d rot_x_pi_over_2;

    rot_x_pi_over_2 << 1, 0, 0,

                       0, std::cos(M_PI/2), -std::sin(M_PI/2),

                       0, std::sin(M_PI/2), std::cos(M_PI/2);

    EXPECT_DOUBLE_EQ(glomap::RotUpToAngle(rot_x_pi_over_2), M_PI/2);



    Eigen::Matrix3d rot_y_pi_over_2;

    rot_y_pi_over_2 << std::cos(M_PI/2), 0, std::sin(M_PI/2),

                       0, 1, 0,

                       -std::sin(M_PI/2), 0, std::cos(M_PI/2);

    EXPECT_DOUBLE_EQ(glomap::RotUpToAngle(rot_y_pi_over_2), M_PI/2);



    Eigen::Matrix3d rot_z_pi_over_2;

    rot_z_pi_over_2 << std::cos(M_PI/2), -std::sin(M_PI/2), 0,

                       std::sin(M_PI/2), std::cos(M_PI/2), 0,

                       0, 0, 1;

    EXPECT_DOUBLE_EQ(glomap::RotUpToAngle(rot_z_pi_over_2), M_PI/2);

}



TEST(RotUpToAngleTest_132, BoundaryConditions_132) {

    Eigen::Matrix3d zero_matrix = Eigen::Matrix3d::Zero();

    EXPECT_TRUE(std::isnan(glomap::RotUpToAngle(zero_matrix)));



    Eigen::Matrix3d invalid_rot;

    invalid_rot << 0, 1, 0,

                   1, 0, 0,

                   0, 0, -1;

    EXPECT_TRUE(std::isnan(glomap::RotUpToAngle(invalid_rot)));

}



TEST(RotUpToAngleTest_132, ExceptionalCases_132) {

    // In this specific function, there are no exceptional cases that throw exceptions,

    // but invalid rotation matrices may return NaN. This is tested in BoundaryConditions.

}
