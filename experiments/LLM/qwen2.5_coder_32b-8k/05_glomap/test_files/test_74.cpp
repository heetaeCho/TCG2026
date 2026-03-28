#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/math/rigid3d.cc"

#include <Eigen/Dense>



using namespace glomap;

using namespace Eigen;



TEST(AngleAxisToRotationTest_74, NormalOperation_ZeroVector_74) {

    Vector3d aa_vec(0.0, 0.0, 0.0);

    Matrix3d expected_rotation = Matrix3d::Identity();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, NormalOperation_UnitXVector_74) {

    Vector3d aa_vec(1.0, 0.0, 0.0);

    Matrix3d expected_rotation = AngleAxis<double>(1.0, Vector3d::UnitX()).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, NormalOperation_UnitYVector_74) {

    Vector3d aa_vec(0.0, 1.0, 0.0);

    Matrix3d expected_rotation = AngleAxis<double>(1.0, Vector3d::UnitY()).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, NormalOperation_UnitZVector_74) {

    Vector3d aa_vec(0.0, 0.0, 1.0);

    Matrix3d expected_rotation = AngleAxis<double>(1.0, Vector3d::UnitZ()).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, BoundaryCondition_SmallAngle_74) {

    Vector3d aa_vec(0.001, 0.0, 0.0);

    Matrix3d expected_rotation = AngleAxis<double>(0.001, Vector3d::UnitX()).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, BoundaryCondition_LargeAngle_74) {

    Vector3d aa_vec(M_PI, 0.0, 0.0);

    Matrix3d expected_rotation = AngleAxis<double>(M_PI, Vector3d::UnitX()).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, ExceptionalCase_NegativeAngle_74) {

    Vector3d aa_vec(-1.0, 0.0, 0.0);

    Matrix3d expected_rotation = AngleAxis<double>(-1.0, Vector3d::UnitX()).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, ExceptionalCase_ArbitraryVector_74) {

    Vector3d aa_vec(1.0, 2.0, 3.0);

    double norm = aa_vec.norm();

    Vector3d axis = aa_vec / norm;

    Matrix3d expected_rotation = AngleAxis<double>(norm, axis).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, BoundaryCondition_VerySmallAngle_74) {

    Vector3d aa_vec(1e-10, 0.0, 0.0);

    Matrix3d expected_rotation = AngleAxis<double>(1e-10, Vector3d::UnitX()).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}



TEST(AngleAxisToRotationTest_74, BoundaryCondition_SpecialCaseVector_74) {

    Vector3d aa_vec(1.0, -1.0, 1.0);

    double norm = aa_vec.norm();

    Vector3d axis = aa_vec / norm;

    Matrix3d expected_rotation = AngleAxis<double>(norm, axis).toRotationMatrix();

    EXPECT_TRUE(AngleAxisToRotation(aa_vec).isApprox(expected_rotation));

}
