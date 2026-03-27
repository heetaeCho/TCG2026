#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/glomap/math/rigid3d.h"

#include <Eigen/Geometry>



using namespace glomap;

using namespace Eigen;



// Test fixture for Rigid3dToAngleAxis tests

class Rigid3dToAngleAxisTest_72 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(Rigid3dToAngleAxisTest_72, IdentityRotation_ReturnsZeroVector_72) {

    Rigid3d identity_pose = Rigid3d(Isometry3d::Identity());

    Vector3d result = Rigid3dToAngleAxis(identity_pose);

    EXPECT_TRUE(result.isApprox(Vector3d(0.0, 0.0, 0.0)));

}



TEST_F(Rigid3dToAngleAxisTest_72, RotationAroundX_ReturnsCorrectVector_72) {

    Isometry3d pose = Isometry3d::Identity();

    double angle = M_PI / 4; // 45 degrees

    pose.rotate(AngleAxisd(angle, Vector3d::UnitX()));

    Rigid3d rigid_pose(pose);

    Vector3d result = Rigid3dToAngleAxis(rigid_pose);

    EXPECT_TRUE(result.isApprox(Vector3d(angle, 0.0, 0.0)));

}



TEST_F(Rigid3dToAngleAxisTest_72, RotationAroundY_ReturnsCorrectVector_72) {

    Isometry3d pose = Isometry3d::Identity();

    double angle = M_PI / 4; // 45 degrees

    pose.rotate(AngleAxisd(angle, Vector3d::UnitY()));

    Rigid3d rigid_pose(pose);

    Vector3d result = Rigid3dToAngleAxis(rigid_pose);

    EXPECT_TRUE(result.isApprox(Vector3d(0.0, angle, 0.0)));

}



TEST_F(Rigid3dToAngleAxisTest_72, RotationAroundZ_ReturnsCorrectVector_72) {

    Isometry3d pose = Isometry3d::Identity();

    double angle = M_PI / 4; // 45 degrees

    pose.rotate(AngleAxisd(angle, Vector3d::UnitZ()));

    Rigid3d rigid_pose(pose);

    Vector3d result = Rigid3dToAngleAxis(rigid_pose);

    EXPECT_TRUE(result.isApprox(Vector3d(0.0, 0.0, angle)));

}



TEST_F(Rigid3dToAngleAxisTest_72, FullRotation_ReturnsFullAngleVector_72) {

    Isometry3d pose = Isometry3d::Identity();

    double angle = M_PI; // 180 degrees

    pose.rotate(AngleAxisd(angle, Vector3d(1.0, 1.0, 1.0).normalized()));

    Rigid3d rigid_pose(pose);

    Vector3d result = Rigid3dToAngleAxis(rigid_pose);

    EXPECT_TRUE(result.isApprox(Vector3d::Constant(M_PI / sqrt(3))));

}



TEST_F(Rigid3dToAngleAxisTest_72, LargeRotation_ReturnsScaledVector_72) {

    Isometry3d pose = Isometry3d::Identity();

    double angle = 2 * M_PI; // 360 degrees (full circle)

    pose.rotate(AngleAxisd(angle, Vector3d(1.0, 0.0, 0.0)));

    Rigid3d rigid_pose(pose);

    Vector3d result = Rigid3dToAngleAxis(rigid_pose);

    EXPECT_TRUE(result.isApprox(Vector3d::Zero()));

}



TEST_F(Rigid3dToAngleAxisTest_72, SmallRotation_ReturnsSmallVector_72) {

    Isometry3d pose = Isometry3d::Identity();

    double angle = 0.01; // very small angle

    pose.rotate(AngleAxisd(angle, Vector3d(0.0, 0.0, 1.0)));

    Rigid3d rigid_pose(pose);

    Vector3d result = Rigid3dToAngleAxis(rigid_pose);

    EXPECT_TRUE(result.isApprox(Vector3d(0.0, 0.0, angle)));

}
