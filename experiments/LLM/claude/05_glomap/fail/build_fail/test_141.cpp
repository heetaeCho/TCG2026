#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

// Based on the code, we need to define the Rigid3d struct and the CalcAngle function
// We infer from the usage that Rigid3d has a 'rotation' member of type Eigen::Quaterniond

namespace glomap {

struct Rigid3d {
    Eigen::Quaterniond rotation;
    Eigen::Vector3d translation;
    
    Rigid3d() : rotation(Eigen::Quaterniond::Identity()), translation(Eigen::Vector3d::Zero()) {}
    Rigid3d(const Eigen::Quaterniond& q, const Eigen::Vector3d& t) : rotation(q), translation(t) {}
};

double CalcAngle(const Rigid3d& pose1, const Rigid3d& pose2);

}  // namespace glomap

namespace {

class CalcAngleTest_141 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
};

// Test that the angle between two identical poses is 0 degrees
TEST_F(CalcAngleTest_141, IdenticalPosesReturnZero_141) {
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    glomap::Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test that a 90-degree rotation around the Z axis gives 90 degrees
TEST_F(CalcAngleTest_141, NinetyDegreeRotationAroundZ_141) {
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose2(q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test that a 180-degree rotation gives 180 degrees
TEST_F(CalcAngleTest_141, OneEightyDegreeRotation_141) {
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX()));
    glomap::Rigid3d pose2(q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test that the angle is symmetric: CalcAngle(a, b) == CalcAngle(b, a)
TEST_F(CalcAngleTest_141, SymmetricAngle_141) {
    Eigen::Quaterniond q1(Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitY()));
    Eigen::Quaterniond q2(Eigen::AngleAxisd(M_PI / 3.0, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose1(q1, Eigen::Vector3d(1, 2, 3));
    glomap::Rigid3d pose2(q2, Eigen::Vector3d(4, 5, 6));
    
    double angle1 = glomap::CalcAngle(pose1, pose2);
    double angle2 = glomap::CalcAngle(pose2, pose1);
    EXPECT_NEAR(angle1, angle2, kTolerance);
}

// Test that translation does not affect the angle
TEST_F(CalcAngleTest_141, TranslationDoesNotAffectAngle_141) {
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    glomap::Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(100, 200, 300));
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test a 45-degree rotation
TEST_F(CalcAngleTest_141, FortyFiveDegreeRotation_141) {
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitX()));
    glomap::Rigid3d pose2(q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 45.0, kTolerance);
}

// Test angle between two non-identity rotations
TEST_F(CalcAngleTest_141, TwoNonIdentityRotations_141) {
    // Both rotated 45 degrees around Z but in opposite directions
    Eigen::Quaterniond q1(Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitZ()));
    Eigen::Quaterniond q2(Eigen::AngleAxisd(-M_PI / 4.0, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose1(q1, Eigen::Vector3d::Zero());
    glomap::Rigid3d pose2(q2, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test with a very small rotation angle
TEST_F(CalcAngleTest_141, VerySmallRotation_141) {
    double small_angle_rad = 1e-8;  // very small angle in radians
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    Eigen::Quaterniond q(Eigen::AngleAxisd(small_angle_rad, Eigen::Vector3d::UnitX()));
    glomap::Rigid3d pose2(q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    double expected_degrees = small_angle_rad * 180.0 / M_PI;
    EXPECT_NEAR(angle, expected_degrees, 1e-5);
}

// Test that angle is always non-negative
TEST_F(CalcAngleTest_141, AngleIsNonNegative_141) {
    Eigen::Quaterniond q1(Eigen::AngleAxisd(M_PI / 6.0, Eigen::Vector3d::UnitY()));
    Eigen::Quaterniond q2(Eigen::AngleAxisd(2.0 * M_PI / 3.0, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose1(q1, Eigen::Vector3d(1, 0, 0));
    glomap::Rigid3d pose2(q2, Eigen::Vector3d(0, 1, 0));
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_GE(angle, 0.0);
}

// Test angle does not exceed 180 degrees
TEST_F(CalcAngleTest_141, AngleDoesNotExceed180_141) {
    // Even with a rotation of 270 degrees, the angular distance should be 90
    Eigen::Quaterniond q(Eigen::AngleAxisd(3.0 * M_PI / 2.0, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    glomap::Rigid3d pose2(q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_LE(angle, 180.0 + kTolerance);
}

// Test rotation around arbitrary axis
TEST_F(CalcAngleTest_141, ArbitraryAxisRotation_141) {
    Eigen::Vector3d axis(1, 1, 1);
    axis.normalize();
    double rotation_angle = M_PI / 3.0;  // 60 degrees
    
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    Eigen::Quaterniond q(Eigen::AngleAxisd(rotation_angle, axis));
    glomap::Rigid3d pose2(q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 60.0, kTolerance);
}

// Test with equivalent quaternions (q and -q represent same rotation)
TEST_F(CalcAngleTest_141, EquivalentQuaternions_141) {
    Eigen::Quaterniond q(Eigen::AngleAxisd(M_PI / 3.0, Eigen::Vector3d::UnitX()));
    Eigen::Quaterniond neg_q(-q.w(), -q.x(), -q.y(), -q.z());
    
    glomap::Rigid3d pose1(q, Eigen::Vector3d::Zero());
    glomap::Rigid3d pose2(neg_q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    // q and -q represent the same rotation, so the angle should be 0
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test default constructed poses
TEST_F(CalcAngleTest_141, DefaultConstructedPoses_141) {
    glomap::Rigid3d pose1;
    glomap::Rigid3d pose2;
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test full 360-degree rotation (should map to 0)
TEST_F(CalcAngleTest_141, FullRotationMapsToZero_141) {
    Eigen::Quaterniond q(Eigen::AngleAxisd(2.0 * M_PI, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d::Zero());
    glomap::Rigid3d pose2(q, Eigen::Vector3d::Zero());
    
    double angle = glomap::CalcAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, 1e-6);
}

}  // namespace
