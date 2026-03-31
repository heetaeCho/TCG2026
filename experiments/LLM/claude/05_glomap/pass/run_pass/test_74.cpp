#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

// Forward declare the function under test
namespace glomap {
Eigen::Matrix3d AngleAxisToRotation(const Eigen::Vector3d& aa_vec);
}

class AngleAxisToRotationTest_74 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
    static constexpr double kLooseTolerance = 1e-6;
};

// Test that zero angle-axis vector produces identity matrix
TEST_F(AngleAxisToRotationTest_74, ZeroVector_ReturnsIdentity_74) {
    Eigen::Vector3d aa_vec(0.0, 0.0, 0.0);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    EXPECT_NEAR(R(0, 0), 1.0, kTolerance);
    EXPECT_NEAR(R(1, 1), 1.0, kTolerance);
    EXPECT_NEAR(R(2, 2), 1.0, kTolerance);
    EXPECT_NEAR(R(0, 1), 0.0, kTolerance);
    EXPECT_NEAR(R(0, 2), 0.0, kTolerance);
    EXPECT_NEAR(R(1, 0), 0.0, kTolerance);
    EXPECT_NEAR(R(1, 2), 0.0, kTolerance);
    EXPECT_NEAR(R(2, 0), 0.0, kTolerance);
    EXPECT_NEAR(R(2, 1), 0.0, kTolerance);
}

// Test rotation around X-axis by pi/2
TEST_F(AngleAxisToRotationTest_74, RotationAroundXAxis_90Degrees_74) {
    double angle = M_PI / 2.0;
    Eigen::Vector3d aa_vec(angle, 0.0, 0.0);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    Eigen::Matrix3d expected = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test rotation around Y-axis by pi/2
TEST_F(AngleAxisToRotationTest_74, RotationAroundYAxis_90Degrees_74) {
    double angle = M_PI / 2.0;
    Eigen::Vector3d aa_vec(0.0, angle, 0.0);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    Eigen::Matrix3d expected = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test rotation around Z-axis by pi/2
TEST_F(AngleAxisToRotationTest_74, RotationAroundZAxis_90Degrees_74) {
    double angle = M_PI / 2.0;
    Eigen::Vector3d aa_vec(0.0, 0.0, angle);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    Eigen::Matrix3d expected = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test rotation by pi (180 degrees) around X-axis
TEST_F(AngleAxisToRotationTest_74, RotationAroundXAxis_180Degrees_74) {
    double angle = M_PI;
    Eigen::Vector3d aa_vec(angle, 0.0, 0.0);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    Eigen::Matrix3d expected = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test that the result is a valid rotation matrix (R^T * R = I, det(R) = 1)
TEST_F(AngleAxisToRotationTest_74, ResultIsValidRotationMatrix_74) {
    Eigen::Vector3d aa_vec(0.5, -0.3, 0.8);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    // Check R^T * R = I
    Eigen::Matrix3d RtR = R.transpose() * R;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(RtR(i, j), (i == j) ? 1.0 : 0.0, kLooseTolerance);
    
    // Check det(R) = 1
    EXPECT_NEAR(R.determinant(), 1.0, kLooseTolerance);
}

// Test with a very small angle-axis vector (near-zero, should use linear approximation branch)
TEST_F(AngleAxisToRotationTest_74, VerySmallAngle_LinearApproximation_74) {
    double tiny = 1e-15;
    Eigen::Vector3d aa_vec(tiny, tiny, tiny);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    // For very small angles, the result should be approximately identity
    // with small off-diagonal elements
    EXPECT_NEAR(R(0, 0), 1.0, kLooseTolerance);
    EXPECT_NEAR(R(1, 1), 1.0, kLooseTolerance);
    EXPECT_NEAR(R(2, 2), 1.0, kLooseTolerance);
}

// Test with an arbitrary angle-axis vector
TEST_F(AngleAxisToRotationTest_74, ArbitraryRotation_74) {
    Eigen::Vector3d aa_vec(1.2, -0.5, 0.7);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    double norm = aa_vec.norm();
    Eigen::Matrix3d expected = Eigen::AngleAxisd(norm, aa_vec.normalized()).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test with negative angle components
TEST_F(AngleAxisToRotationTest_74, NegativeAngleComponents_74) {
    Eigen::Vector3d aa_vec(-0.8, -1.2, -0.3);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    double norm = aa_vec.norm();
    Eigen::Matrix3d expected = Eigen::AngleAxisd(norm, aa_vec.normalized()).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test that result is orthogonal for small angle case
TEST_F(AngleAxisToRotationTest_74, SmallAngle_ApproximatelyOrthogonal_74) {
    Eigen::Vector3d aa_vec(1e-12, 2e-12, -1e-12);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    // For very small angles in the linear approximation branch,
    // R^T * R should be approximately I
    Eigen::Matrix3d RtR = R.transpose() * R;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(RtR(i, j), (i == j) ? 1.0 : 0.0, kLooseTolerance);
}

// Test with a large angle (> 2*pi)
TEST_F(AngleAxisToRotationTest_74, LargeAngle_74) {
    Eigen::Vector3d axis = Eigen::Vector3d(1.0, 1.0, 1.0).normalized();
    double angle = 3.0 * M_PI;
    Eigen::Vector3d aa_vec = angle * axis;
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    Eigen::Matrix3d expected = Eigen::AngleAxisd(angle, axis).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test the small-angle linear approximation gives correct skew-symmetric structure
TEST_F(AngleAxisToRotationTest_74, SmallAngle_SkewSymmetricStructure_74) {
    // Use values that are very small
    double a = 1e-14, b = 2e-14, c = 3e-14;
    Eigen::Vector3d aa_vec(a, b, c);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    // According to the code, for small angles:
    // R = I + [aa_vec]_x (skew-symmetric)
    // Diagonal should be 1
    EXPECT_NEAR(R(0, 0), 1.0, kTolerance);
    EXPECT_NEAR(R(1, 1), 1.0, kTolerance);
    EXPECT_NEAR(R(2, 2), 1.0, kTolerance);
    
    // Off-diagonals should follow the pattern from the code
    EXPECT_NEAR(R(1, 0), c, kTolerance);   // aa_vec[2]
    EXPECT_NEAR(R(2, 0), -b, kTolerance);  // -aa_vec[1]
    EXPECT_NEAR(R(0, 1), -c, kTolerance);  // -aa_vec[2]
    EXPECT_NEAR(R(2, 1), a, kTolerance);   // aa_vec[0]
    EXPECT_NEAR(R(0, 2), b, kTolerance);   // aa_vec[1]
    EXPECT_NEAR(R(1, 2), -a, kTolerance);  // -aa_vec[0]
}

// Test rotation by 2*pi should give approximately identity
TEST_F(AngleAxisToRotationTest_74, FullRotation_2Pi_ApproximatelyIdentity_74) {
    Eigen::Vector3d axis = Eigen::Vector3d(0.0, 0.0, 1.0);
    double angle = 2.0 * M_PI;
    Eigen::Vector3d aa_vec = angle * axis;
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), (i == j) ? 1.0 : 0.0, kLooseTolerance);
}

// Test that only one component non-zero works correctly
TEST_F(AngleAxisToRotationTest_74, SingleAxisRotation_74) {
    double angle = 1.0;
    Eigen::Vector3d aa_vec(0.0, angle, 0.0);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    Eigen::Matrix3d expected = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()).toRotationMatrix();
    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(R(i, j), expected(i, j), kLooseTolerance);
}

// Test boundary between small and large angle (near EPS threshold)
TEST_F(AngleAxisToRotationTest_74, NearEPSBoundary_AboveEPS_74) {
    // Assuming EPS is something like 1e-6 or similar
    // Use a small but not tiny angle
    double small_angle = 1e-4;
    Eigen::Vector3d aa_vec(small_angle, 0.0, 0.0);
    Eigen::Matrix3d R = glomap::AngleAxisToRotation(aa_vec);
    
    // Should be a valid rotation matrix
    Eigen::Matrix3d RtR = R.transpose() * R;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(RtR(i, j), (i == j) ? 1.0 : 0.0, kLooseTolerance);
    
    EXPECT_NEAR(R.determinant(), 1.0, kLooseTolerance);
}
