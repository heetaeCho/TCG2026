#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

// Forward declare the function from the glomap namespace
namespace glomap {
Eigen::Matrix3d GetAlignRot(const Eigen::Vector3d& gravity);
}

class GravityTest_62 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
};

// Test that the result is a valid rotation matrix (orthogonal with det = +1) for a simple downward gravity
TEST_F(GravityTest_62, ResultIsValidRotationMatrix_DownwardGravity_62) {
    Eigen::Vector3d gravity(0.0, -9.81, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    // Check orthogonality: R^T * R should be identity
    Eigen::Matrix3d shouldBeIdentity = R.transpose() * R;
    EXPECT_TRUE(shouldBeIdentity.isApprox(Eigen::Matrix3d::Identity(), kTolerance))
        << "R^T * R = \n" << shouldBeIdentity;

    // Check determinant is +1
    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
}

// Test that column 1 of R is the normalized gravity vector
TEST_F(GravityTest_62, Column1IsNormalizedGravity_62) {
    Eigen::Vector3d gravity(0.0, -9.81, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    Eigen::Vector3d expected_col1 = gravity.normalized();
    EXPECT_TRUE(R.col(1).isApprox(expected_col1, kTolerance))
        << "R.col(1) = " << R.col(1).transpose() << "\nexpected = " << expected_col1.transpose();
}

// Test with gravity along the positive z-axis
TEST_F(GravityTest_62, GravityAlongPositiveZ_62) {
    Eigen::Vector3d gravity(0.0, 0.0, 1.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    // R should be a valid rotation matrix
    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));

    // Column 1 should be normalized gravity
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}

// Test with gravity along the positive x-axis
TEST_F(GravityTest_62, GravityAlongPositiveX_62) {
    Eigen::Vector3d gravity(5.0, 0.0, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}

// Test with gravity along the negative x-axis
TEST_F(GravityTest_62, GravityAlongNegativeX_62) {
    Eigen::Vector3d gravity(-3.0, 0.0, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}

// Test with gravity along the positive y-axis
TEST_F(GravityTest_62, GravityAlongPositiveY_62) {
    Eigen::Vector3d gravity(0.0, 1.0, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}

// Test with an arbitrary gravity direction
TEST_F(GravityTest_62, ArbitraryGravityDirection_62) {
    Eigen::Vector3d gravity(1.0, 2.0, 3.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}

// Test with another arbitrary gravity direction (negative components)
TEST_F(GravityTest_62, ArbitraryNegativeGravityDirection_62) {
    Eigen::Vector3d gravity(-1.0, -2.0, -3.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}

// Test that columns are mutually orthogonal
TEST_F(GravityTest_62, ColumnsAreMutuallyOrthogonal_62) {
    Eigen::Vector3d gravity(1.0, -1.0, 0.5);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.col(0).dot(R.col(1)), 0.0, kTolerance);
    EXPECT_NEAR(R.col(0).dot(R.col(2)), 0.0, kTolerance);
    EXPECT_NEAR(R.col(1).dot(R.col(2)), 0.0, kTolerance);
}

// Test that all columns have unit norm
TEST_F(GravityTest_62, ColumnsHaveUnitNorm_62) {
    Eigen::Vector3d gravity(3.0, 4.0, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.col(0).norm(), 1.0, kTolerance);
    EXPECT_NEAR(R.col(1).norm(), 1.0, kTolerance);
    EXPECT_NEAR(R.col(2).norm(), 1.0, kTolerance);
}

// Test with a very small magnitude gravity vector (but non-zero)
TEST_F(GravityTest_62, SmallMagnitudeGravity_62) {
    Eigen::Vector3d gravity(1e-12, 1e-12, 1e-12);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    // Column 1 should still be the normalized gravity
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), 1e-6));

    // Should still be a rotation matrix (det = +1)
    EXPECT_NEAR(R.determinant(), 1.0, 1e-6);
}

// Test with a very large magnitude gravity vector
TEST_F(GravityTest_62, LargeMagnitudeGravity_62) {
    Eigen::Vector3d gravity(1e10, -1e10, 1e10);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}

// Test with unit vector input (already normalized)
TEST_F(GravityTest_62, UnitVectorInput_62) {
    Eigen::Vector3d gravity = Eigen::Vector3d(1.0, 1.0, 1.0).normalized();
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity, kTolerance));
}

// Test with negative y-axis (common downward gravity in many conventions)
TEST_F(GravityTest_62, NegativeYAxis_62) {
    Eigen::Vector3d gravity(0.0, -1.0, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(Eigen::Vector3d(0.0, -1.0, 0.0), kTolerance));
}

// Test with negative z-axis
TEST_F(GravityTest_62, NegativeZAxis_62) {
    Eigen::Vector3d gravity(0.0, 0.0, -1.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(Eigen::Vector3d(0.0, 0.0, -1.0), kTolerance));
}

// Test that the cross product of col(0) and col(1) gives col(2) (right-handed frame)
TEST_F(GravityTest_62, RightHandedCoordinateSystem_62) {
    Eigen::Vector3d gravity(2.0, -3.0, 1.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    // For a proper rotation matrix with det=+1, col(0) x col(1) = col(2)
    Eigen::Vector3d cross = R.col(0).cross(R.col(1));
    EXPECT_TRUE(cross.isApprox(R.col(2), kTolerance))
        << "col(0) x col(1) = " << cross.transpose() << "\ncol(2) = " << R.col(2).transpose();
}

// Test consistency: calling with the same input should give the same result
TEST_F(GravityTest_62, Deterministic_62) {
    Eigen::Vector3d gravity(1.5, -2.5, 3.5);
    Eigen::Matrix3d R1 = glomap::GetAlignRot(gravity);
    Eigen::Matrix3d R2 = glomap::GetAlignRot(gravity);

    EXPECT_TRUE(R1.isApprox(R2, kTolerance));
}

// Test with a gravity vector that has only two non-zero components
TEST_F(GravityTest_62, TwoNonZeroComponents_62) {
    Eigen::Vector3d gravity(1.0, 1.0, 0.0);
    Eigen::Matrix3d R = glomap::GetAlignRot(gravity);

    EXPECT_NEAR(R.determinant(), 1.0, kTolerance);
    EXPECT_TRUE((R.transpose() * R).isApprox(Eigen::Matrix3d::Identity(), kTolerance));
    EXPECT_TRUE(R.col(1).isApprox(gravity.normalized(), kTolerance));
}
