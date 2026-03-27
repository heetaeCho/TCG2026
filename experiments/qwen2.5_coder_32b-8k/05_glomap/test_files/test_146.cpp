#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/rigid3d.h"

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



TEST(RotationToAngleAxisTest_146, IdentityRotation_ReturnsZeroVector_146) {

    Matrix3d identity = Matrix3d::Identity();

    Vector3d result = RotationToAngleAxis(identity);

    EXPECT_TRUE(result.isApprox(Vector3d(0, 0, 0)));

}



TEST(RotationToAngleAxisTest_146, RotateAroundX90_ReturnsCorrectVector_146) {

    Matrix3d rot;

    rot << 1, 0, 0,

           0, 0,-1,

           0, 1, 0;

    Vector3d result = RotationToAngleAxis(rot);

    EXPECT_TRUE(result.isApprox(Vector3d(M_PI_2, 0, 0)));

}



TEST(RotationToAngleAxisTest_146, RotateAroundY90_ReturnsCorrectVector_146) {

    Matrix3d rot;

    rot << 0, 0, 1,

           0, 1, 0,

          -1, 0, 0;

    Vector3d result = RotationToAngleAxis(rot);

    EXPECT_TRUE(result.isApprox(Vector3d(0, M_PI_2, 0)));

}



TEST(RotationToAngleAxisTest_146, RotateAroundZ90_ReturnsCorrectVector_146) {

    Matrix3d rot;

    rot << 0,-1, 0,

           1, 0, 0,

           0, 0, 1;

    Vector3d result = RotationToAngleAxis(rot);

    EXPECT_TRUE(result.isApprox(Vector3d(0, 0, M_PI_2)));

}



TEST(RotationToAngleAxisTest_146, LargeRotation_ReturnsCorrectVector_146) {

    Matrix3d rot;

    double angle = 5 * M_PI / 4; // 225 degrees

    Vector3d axis(1, 1, 1).normalized();

    AngleAxis<double> aa(angle, axis);

    rot = aa.matrix();



    Vector3d result = RotationToAngleAxis(rot);

    EXPECT_TRUE(result.isApprox(axis * angle));

}



TEST(RotationToAngleAxisTest_146, SmallRotation_ReturnsCorrectVector_146) {

    Matrix3d rot;

    double angle = M_PI / 180; // 1 degree

    Vector3d axis(1, 0, 0);

    AngleAxis<double> aa(angle, axis);

    rot = aa.matrix();



    Vector3d result = RotationToAngleAxis(rot);

    EXPECT_TRUE(result.isApprox(axis * angle));

}



TEST(RotationToAngleAxisTest_146, NearIdentityRotation_ReturnsSmallVector_146) {

    Matrix3d rot;

    double angle = 0.0001; // very small angle

    Vector3d axis(1, 0, 0);

    AngleAxis<double> aa(angle, axis);

    rot = aa.matrix();



    Vector3d result = RotationToAngleAxis(rot);

    EXPECT_TRUE(result.isApprox(axis * angle));

}
