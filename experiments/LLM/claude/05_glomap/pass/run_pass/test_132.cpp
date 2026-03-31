#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

// Forward declare the function under test
namespace glomap {
double RotUpToAngle(const Eigen::Matrix3d& R_up);
}

class GravityTest_132 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
};

// Test with identity matrix (no rotation)
TEST_F(GravityTest_132, IdentityMatrixReturnsZeroAngle_132) {
    Eigen::Matrix3d identity = Eigen::Matrix3d::Identity();
    double angle = glomap::RotUpToAngle(identity);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test with rotation around Y-axis by a known angle
TEST_F(GravityTest_132, RotationAroundYAxis_132) {
    double expected_angle = M_PI / 4.0; // 45 degrees
    Eigen::AngleAxisd rotation(expected_angle, Eigen::Vector3d::UnitY());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    EXPECT_NEAR(angle, expected_angle, kTolerance);
}

// Test with rotation around Y-axis by negative angle
TEST_F(GravityTest_132, NegativeRotationAroundYAxis_132) {
    double expected_angle = -M_PI / 4.0; // -45 degrees
    Eigen::AngleAxisd rotation(expected_angle, Eigen::Vector3d::UnitY());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    EXPECT_NEAR(angle, expected_angle, kTolerance);
}

// Test with 90 degree rotation around Y-axis
TEST_F(GravityTest_132, NinetyDegreeRotationAroundYAxis_132) {
    double expected_angle = M_PI / 2.0;
    Eigen::AngleAxisd rotation(expected_angle, Eigen::Vector3d::UnitY());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    EXPECT_NEAR(angle, expected_angle, kTolerance);
}

// Test with small angle rotation around Y-axis
TEST_F(GravityTest_132, SmallAngleRotationAroundYAxis_132) {
    double expected_angle = 1e-6;
    Eigen::AngleAxisd rotation(expected_angle, Eigen::Vector3d::UnitY());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    EXPECT_NEAR(angle, expected_angle, 1e-5);
}

// Test with rotation around X-axis (y-component of angle-axis should be 0)
TEST_F(GravityTest_132, RotationAroundXAxisYieldsZeroYComponent_132) {
    double rotation_angle = M_PI / 3.0;
    Eigen::AngleAxisd rotation(rotation_angle, Eigen::Vector3d::UnitX());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    // For a pure X-axis rotation, the angle-axis y-component should be 0
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test with rotation around Z-axis (y-component of angle-axis should be 0)
TEST_F(GravityTest_132, RotationAroundZAxisYieldsZeroYComponent_132) {
    double rotation_angle = M_PI / 6.0;
    Eigen::AngleAxisd rotation(rotation_angle, Eigen::Vector3d::UnitZ());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    // For a pure Z-axis rotation, the angle-axis y-component should be 0
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test with 180 degree rotation around Y-axis
TEST_F(GravityTest_132, OneEightyDegreeRotationAroundYAxis_132) {
    double expected_angle = M_PI;
    Eigen::AngleAxisd rotation(expected_angle, Eigen::Vector3d::UnitY());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    EXPECT_NEAR(std::abs(angle), M_PI, kTolerance);
}

// Test with a general rotation that has a Y-component
TEST_F(GravityTest_132, GeneralRotationWithYComponent_132) {
    // Rotation around a general axis
    Eigen::Vector3d axis(0.0, 1.0, 0.0);
    axis.normalize();
    double theta = 0.5;
    Eigen::AngleAxisd rotation(theta, axis);
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    // For rotation purely around Y, the y-component of angle-axis = theta
    EXPECT_NEAR(angle, theta, kTolerance);
}

// Test consistency: applying the same rotation twice should give a predictable result
TEST_F(GravityTest_132, ConsistencyBetweenCalls_132) {
    Eigen::AngleAxisd rotation(M_PI / 5.0, Eigen::Vector3d::UnitY());
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle1 = glomap::RotUpToAngle(R);
    double angle2 = glomap::RotUpToAngle(R);
    EXPECT_DOUBLE_EQ(angle1, angle2);
}

// Test with a mixed-axis rotation
TEST_F(GravityTest_132, MixedAxisRotation_132) {
    Eigen::Vector3d axis(1.0, 1.0, 0.0);
    axis.normalize();
    double theta = M_PI / 4.0;
    Eigen::AngleAxisd rotation(theta, axis);
    Eigen::Matrix3d R = rotation.toRotationMatrix();
    double angle = glomap::RotUpToAngle(R);
    // The angle-axis representation: angle * axis.y() = theta * (1/sqrt(2))
    double expected_y = theta * axis.y();
    EXPECT_NEAR(angle, expected_y, kTolerance);
}
