#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/rigid3d.h"

#include <Eigen/Geometry>



namespace glomap {



class Rigid3dTest_141 : public ::testing::Test {

protected:

    Eigen::Quaterniond rotation1;

    Eigen::Quaterniond rotation2;

    Rigid3d pose1;

    Rigid3d pose2;



    void SetUp() override {

        rotation1 = Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitX()) *

                    Eigen::AngleAxisd(0.3, Eigen::Vector3d::UnitY());

        rotation2 = Eigen::AngleAxisd(1.0, Eigen::Vector3d::UnitZ());



        pose1 = Rigid3d(Eigen::Vector3d(1, 2, 3), rotation1);

        pose2 = Rigid3d(Eigen::Vector3d(4, 5, 6), rotation2);

    }

};



TEST_F(Rigid3dTest_141, CalcAngle_NormalOperation_141) {

    double angle = CalcAngle(pose1, pose2);

    EXPECT_NEAR(angle, 90.0, 0.01); // Assuming a 90-degree difference for simplicity

}



TEST_F(Rigid3dTest_141, CalcAngle_SameRotation_141) {

    Rigid3d samePose(pose1.translation(), pose1.rotation());

    double angle = CalcAngle(pose1, samePose);

    EXPECT_NEAR(angle, 0.0, 0.01); // Same rotation should yield 0 degrees

}



TEST_F(Rigid3dTest_141, CalcAngle_OppositeRotation_141) {

    Eigen::Quaterniond oppositeRotation = -pose1.rotation();

    Rigid3d oppositePose(pose1.translation(), oppositeRotation);

    double angle = CalcAngle(pose1, oppositePose);

    EXPECT_NEAR(angle, 180.0, 0.01); // Opposite rotation should yield 180 degrees

}



TEST_F(Rigid3dTest_141, CalcAngle_ZeroRotation_141) {

    Rigid3d zeroRotationPose(pose1.translation(), Eigen::Quaterniond::Identity());

    double angle = CalcAngle(zeroRotationPose, pose2);

    EXPECT_NEAR(angle, 57.2958, 0.01); // Assuming a specific value for the rotation difference

}



TEST_F(Rigid3dTest_141, CalcAngle_BoundaryCondition_IdentityRotations_141) {

    Rigid3d identityPose1(Eigen::Vector3d(1, 2, 3), Eigen::Quaterniond::Identity());

    Rigid3d identityPose2(Eigen::Vector3d(4, 5, 6), Eigen::Quaterniond::Identity());

    double angle = CalcAngle(identityPose1, identityPose2);

    EXPECT_NEAR(angle, 0.0, 0.01); // Both rotations are identity

}



} // namespace glomap
