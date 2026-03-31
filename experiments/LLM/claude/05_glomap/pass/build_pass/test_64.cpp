#include <gtest/gtest.h>
#include <Eigen/Core>
#include <cmath>

namespace glomap {
double CalcAngle(const Eigen::Vector3d& gravity1, const Eigen::Vector3d& gravity2);
}

class CalcAngleTest_64 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
};

// Test that the angle between two identical vectors is 0 degrees
TEST_F(CalcAngleTest_64, IdenticalVectors_ReturnsZero_64) {
    Eigen::Vector3d v(1.0, 0.0, 0.0);
    double angle = glomap::CalcAngle(v, v);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test that the angle between two opposite vectors is 180 degrees
TEST_F(CalcAngleTest_64, OppositeVectors_Returns180_64) {
    Eigen::Vector3d v1(1.0, 0.0, 0.0);
    Eigen::Vector3d v2(-1.0, 0.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test that the angle between two perpendicular vectors is 90 degrees
TEST_F(CalcAngleTest_64, PerpendicularVectors_Returns90_64) {
    Eigen::Vector3d v1(1.0, 0.0, 0.0);
    Eigen::Vector3d v2(0.0, 1.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test angle between standard basis vectors X and Z
TEST_F(CalcAngleTest_64, XandZBasisVectors_Returns90_64) {
    Eigen::Vector3d v1(1.0, 0.0, 0.0);
    Eigen::Vector3d v2(0.0, 0.0, 1.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test angle between Y and Z basis vectors
TEST_F(CalcAngleTest_64, YandZBasisVectors_Returns90_64) {
    Eigen::Vector3d v1(0.0, 1.0, 0.0);
    Eigen::Vector3d v2(0.0, 0.0, 1.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test known 45-degree angle
TEST_F(CalcAngleTest_64, FortyFiveDegreeAngle_64) {
    Eigen::Vector3d v1(1.0, 0.0, 0.0);
    Eigen::Vector3d v2(1.0, 1.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 45.0, kTolerance);
}

// Test known 60-degree angle
TEST_F(CalcAngleTest_64, SixtyDegreeAngle_64) {
    Eigen::Vector3d v1(1.0, 0.0, 0.0);
    Eigen::Vector3d v2(0.5, std::sqrt(3.0) / 2.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 60.0, 1e-8);
}

// Test with non-unit vectors (scaling should not affect the angle)
TEST_F(CalcAngleTest_64, ScaledVectors_SameAngle_64) {
    Eigen::Vector3d v1(2.0, 0.0, 0.0);
    Eigen::Vector3d v2(0.0, 5.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test that scaling a vector does not change the angle
TEST_F(CalcAngleTest_64, ScalingDoesNotAffectAngle_64) {
    Eigen::Vector3d v1(1.0, 1.0, 0.0);
    Eigen::Vector3d v2(0.0, 1.0, 0.0);
    double angle1 = glomap::CalcAngle(v1, v2);

    Eigen::Vector3d v1_scaled = v1 * 100.0;
    Eigen::Vector3d v2_scaled = v2 * 0.001;
    double angle2 = glomap::CalcAngle(v1_scaled, v2_scaled);

    EXPECT_NEAR(angle1, angle2, 1e-8);
}

// Test commutativity: CalcAngle(a, b) == CalcAngle(b, a)
TEST_F(CalcAngleTest_64, Commutativity_64) {
    Eigen::Vector3d v1(1.0, 2.0, 3.0);
    Eigen::Vector3d v2(4.0, 5.0, 6.0);
    double angle1 = glomap::CalcAngle(v1, v2);
    double angle2 = glomap::CalcAngle(v2, v1);
    EXPECT_NEAR(angle1, angle2, kTolerance);
}

// Test with negative components
TEST_F(CalcAngleTest_64, NegativeComponents_64) {
    Eigen::Vector3d v1(-1.0, -1.0, 0.0);
    Eigen::Vector3d v2(1.0, 1.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test with arbitrary 3D vectors and verify result is in [0, 180]
TEST_F(CalcAngleTest_64, ResultInValidRange_64) {
    Eigen::Vector3d v1(1.3, -2.7, 4.1);
    Eigen::Vector3d v2(-0.5, 3.2, 1.8);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_GE(angle, 0.0);
    EXPECT_LE(angle, 180.0);
}

// Test angle with one vector along diagonal
TEST_F(CalcAngleTest_64, DiagonalVector_64) {
    Eigen::Vector3d v1(1.0, 1.0, 1.0);
    Eigen::Vector3d v2(1.0, 0.0, 0.0);
    // cos(theta) = 1/sqrt(3), theta = acos(1/sqrt(3)) in degrees
    double expected = std::acos(1.0 / std::sqrt(3.0)) * 180.0 / M_PI;
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, expected, 1e-8);
}

// Test with very small vectors (but non-zero)
TEST_F(CalcAngleTest_64, VerySmallVectors_64) {
    Eigen::Vector3d v1(1e-15, 0.0, 0.0);
    Eigen::Vector3d v2(0.0, 1e-15, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 90.0, 1e-4);
}

// Test with very large vectors
TEST_F(CalcAngleTest_64, VeryLargeVectors_64) {
    Eigen::Vector3d v1(1e15, 0.0, 0.0);
    Eigen::Vector3d v2(0.0, 1e15, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test angle between a vector and its negation is 180
TEST_F(CalcAngleTest_64, VectorAndNegation_64) {
    Eigen::Vector3d v(3.0, -4.0, 5.0);
    double angle = glomap::CalcAngle(v, -v);
    EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test known 120-degree angle
TEST_F(CalcAngleTest_64, OneTwentyDegreeAngle_64) {
    Eigen::Vector3d v1(1.0, 0.0, 0.0);
    Eigen::Vector3d v2(-0.5, std::sqrt(3.0) / 2.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 120.0, 1e-8);
}

// Test that parallel vectors (same direction) give 0 degrees
TEST_F(CalcAngleTest_64, ParallelSameDirection_64) {
    Eigen::Vector3d v1(1.0, 2.0, 3.0);
    Eigen::Vector3d v2(2.0, 4.0, 6.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test that anti-parallel vectors give 180 degrees
TEST_F(CalcAngleTest_64, AntiParallel_64) {
    Eigen::Vector3d v1(1.0, 2.0, 3.0);
    Eigen::Vector3d v2(-2.0, -4.0, -6.0);
    double angle = glomap::CalcAngle(v1, v2);
    EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test output is in degrees, not radians
TEST_F(CalcAngleTest_64, OutputInDegrees_64) {
    Eigen::Vector3d v1(1.0, 0.0, 0.0);
    Eigen::Vector3d v2(0.0, 1.0, 0.0);
    double angle = glomap::CalcAngle(v1, v2);
    // 90 degrees, not pi/2 radians
    EXPECT_GT(angle, 1.6);  // pi/2 ≈ 1.5708, so if in radians would be ~1.57
    EXPECT_NEAR(angle, 90.0, kTolerance);
}
