#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/rigid3d.cc"

#include <Eigen/Geometry>



using namespace glomap;

using namespace Eigen;



class Rigid3dToAngleAxisTest_145 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(Rigid3dToAngleAxisTest_145, IdentityRotation_ReturnsZeroVector_145) {

    Rigid3d identity_pose(Translation3d(Vector3d::Zero()), Quaterniond::Identity());

    Vector3d result = Rigid3dToAngleAxis(identity_pose);

    EXPECT_EQ(result, Vector3d::Zero());

}



TEST_F(Rigid3dToAngleAxisTest_145, RotationAroundX_ReturnsCorrectVector_145) {

    double angle = M_PI / 2.0; // 90 degrees

    Rigid3d x_rotation_pose(Translation3d(Vector3d::Zero()), AngleAxisd(angle, Vector3d::UnitX()));

    Vector3d result = Rigid3dToAngleAxis(x_rotation_pose);

    EXPECT_NEAR(result.x(), angle, 1e-6);

    EXPECT_EQ(result.y(), 0.0);

    EXPECT_EQ(result.z(), 0.0);

}



TEST_F(Rigid3dToAngleAxisTest_145, RotationAroundY_ReturnsCorrectVector_145) {

    double angle = M_PI / 2.0; // 90 degrees

    Rigid3d y_rotation_pose(Translation3d(Vector3d::Zero()), AngleAxisd(angle, Vector3d::UnitY()));

    Vector3d result = Rigid3dToAngleAxis(y_rotation_pose);

    EXPECT_EQ(result.x(), 0.0);

    EXPECT_NEAR(result.y(), angle, 1e-6);

    EXPECT_EQ(result.z(), 0.0);

}



TEST_F(Rigid3dToAngleAxisTest_145, RotationAroundZ_ReturnsCorrectVector_145) {

    double angle = M_PI / 2.0; // 90 degrees

    Rigid3d z_rotation_pose(Translation3d(Vector3d::Zero()), AngleAxisd(angle, Vector3d::UnitZ()));

    Vector3d result = Rigid3dToAngleAxis(z_rotation_pose);

    EXPECT_EQ(result.x(), 0.0);

    EXPECT_EQ(result.y(), 0.0);

    EXPECT_NEAR(result.z(), angle, 1e-6);

}



TEST_F(Rigid3dToAngleAxisTest_145, LargeRotation_ReturnsCorrectVector_145) {

    double angle = 2 * M_PI; // Full rotation

    Rigid3d large_rotation_pose(Translation3d(Vector3d::Zero()), AngleAxisd(angle, Vector3d::UnitX()));

    Vector3d result = Rigid3dToAngleAxis(large_rotation_pose);

    EXPECT_NEAR(result.x(), angle, 1e-6);

    EXPECT_EQ(result.y(), 0.0);

    EXPECT_EQ(result.z(), 0.0);

}



TEST_F(Rigid3dToAngleAxisTest_145, SmallRotation_ReturnsCorrectVector_145) {

    double angle = 1e-6; // Very small rotation

    Rigid3d small_rotation_pose(Translation3d(Vector3d::Zero()), AngleAxisd(angle, Vector3d::UnitX()));

    Vector3d result = Rigid3dToAngleAxis(small_rotation_pose);

    EXPECT_NEAR(result.x(), angle, 1e-6);

    EXPECT_EQ(result.y(), 0.0);

    EXPECT_EQ(result.z(), 0.0);

}
