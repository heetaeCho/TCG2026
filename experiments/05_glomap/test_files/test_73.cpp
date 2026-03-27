#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Eigen/Dense>

#include "./TestProjects/glomap/glomap/math/rigid3d.cc"



namespace glomap {



using ::testing::DoubleNear;



class RotationToAngleAxisTest_73 : public ::testing::Test {

protected:

    static constexpr double kTolerance = 1e-9;

};



TEST_F(RotationToAngleAxisTest_73, IdentityRotation_73) {

    Eigen::Matrix3d identity_matrix = Eigen::Matrix3d::Identity();

    Eigen::Vector3d result = RotationToAngleAxis(identity_matrix);

    EXPECT_TRUE(result.isZero(kTolerance));

}



TEST_F(RotationToAngleAxisTest_73, RotateX90Degrees_73) {

    double angle = M_PI / 2;

    Eigen::Matrix3d rotation_matrix;

    rotation_matrix = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX());

    Eigen::Vector3d result = RotationToAngleAxis(rotation_matrix);

    EXPECT_THAT(result.x(), DoubleNear(angle, kTolerance));

    EXPECT_TRUE(result.y() == 0 && result.z() == 0);

}



TEST_F(RotationToAngleAxisTest_73, RotateY180Degrees_73) {

    double angle = M_PI;

    Eigen::Matrix3d rotation_matrix;

    rotation_matrix = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY());

    Eigen::Vector3d result = RotationToAngleAxis(rotation_matrix);

    EXPECT_TRUE(result.x() == 0);

    EXPECT_THAT(result.y(), DoubleNear(angle, kTolerance));

    EXPECT_TRUE(result.z() == 0);

}



TEST_F(RotationToAngleAxisTest_73, RotateZ45Degrees_73) {

    double angle = M_PI / 4;

    Eigen::Matrix3d rotation_matrix;

    rotation_matrix = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ());

    Eigen::Vector3d result = RotationToAngleAxis(rotation_matrix);

    EXPECT_TRUE(result.x() == 0 && result.y() == 0);

    EXPECT_THAT(result.z(), DoubleNear(angle, kTolerance));

}



TEST_F(RotationToAngleAxisTest_73, RotateArbitrary_73) {

    double angle_x = M_PI / 4;

    double angle_y = M_PI / 6;

    double angle_z = -M_PI / 8;



    Eigen::Matrix3d rotation_matrix =

        Eigen::AngleAxisd(angle_x, Eigen::Vector3d::UnitX()) *

        Eigen::AngleAxisd(angle_y, Eigen::Vector3d::UnitY()) *

        Eigen::AngleAxisd(angle_z, Eigen::Vector3d::UnitZ());



    Eigen::Vector3d result = RotationToAngleAxis(rotation_matrix);

    // Verification of the angle-axis representation is more complex for arbitrary rotations.

    // We can check if the norm of the resulting vector is within a reasonable range of the expected angle.

    double expected_angle = std::sqrt(angle_x * angle_x + angle_y * angle_y + angle_z * angle_z);

    EXPECT_NEAR(result.norm(), expected_angle, kTolerance);

}



TEST_F(RotationToAngleAxisTest_73, BoundaryConditionSmallRotation_73) {

    double small_angle = 1e-6;

    Eigen::Matrix3d rotation_matrix;

    rotation_matrix = Eigen::AngleAxisd(small_angle, Eigen::Vector3d::UnitX());

    Eigen::Vector3d result = RotationToAngleAxis(rotation_matrix);

    EXPECT_THAT(result.x(), DoubleNear(small_angle, kTolerance));

    EXPECT_TRUE(result.y() == 0 && result.z() == 0);

}



TEST_F(RotationToAngleAxisTest_73, BoundaryConditionLargeRotation_73) {

    double large_angle = 2 * M_PI - 1e-6;

    Eigen::Matrix3d rotation_matrix;

    rotation_matrix = Eigen::AngleAxisd(large_angle, Eigen::Vector3d::UnitX());

    Eigen::Vector3d result = RotationToAngleAxis(rotation_matrix);

    EXPECT_THAT(result.x(), DoubleNear(large_angle, kTolerance));

    EXPECT_TRUE(result.y() == 0 && result.z() == 0);

}



} // namespace glomap
