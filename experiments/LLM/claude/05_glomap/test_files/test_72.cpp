#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

// Include the header that defines Rigid3d and the function
// Based on the code, we need to include the appropriate header
namespace glomap {

// Forward declaration based on usage in the .cc file
// Rigid3d appears to have a 'rotation' member that is compatible with Eigen::AngleAxis
struct Rigid3d {
    Eigen::Quaterniond rotation;
    Eigen::Vector3d translation;
    
    Rigid3d() : rotation(Eigen::Quaterniond::Identity()), translation(Eigen::Vector3d::Zero()) {}
    Rigid3d(const Eigen::Quaterniond& r, const Eigen::Vector3d& t) : rotation(r), translation(t) {}
};

Eigen::Vector3d Rigid3dToAngleAxis(const Rigid3d& pose);

}  // namespace glomap

class Rigid3dToAngleAxisTest_72 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
};

// Test identity rotation returns zero angle-axis vector
TEST_F(Rigid3dToAngleAxisTest_72, IdentityRotationReturnsZeroVector_72) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d::Zero();

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), 0.0, kTolerance);
}

// Test 90 degree rotation around Z axis
TEST_F(Rigid3dToAngleAxisTest_72, Rotation90DegreesAroundZ_72) {
    double angle = M_PI / 2.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    EXPECT_NEAR(result.x(), 0.0, kTolerance);
    EXPECT_NEAR(result.y(), 0.0, kTolerance);
    EXPECT_NEAR(result.z(), angle, kTolerance);
}

// Test 90 degree rotation around X axis
TEST_F(Rigid3dToAngleAxisTest_72, Rotation90DegreesAroundX_72) {
    double angle = M_PI / 2.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    EXPECT_NEAR(result.x(), angle, kTolerance);
    EXPECT_NEAR(result.y(), 0.0, kTolerance);
    EXPECT_NEAR(result.z(), 0.0, kTolerance);
}

// Test 90 degree rotation around Y axis
TEST_F(Rigid3dToAngleAxisTest_72, Rotation90DegreesAroundY_72) {
    double angle = M_PI / 2.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    EXPECT_NEAR(result.x(), 0.0, kTolerance);
    EXPECT_NEAR(result.y(), angle, kTolerance);
    EXPECT_NEAR(result.z(), 0.0, kTolerance);
}

// Test 180 degree rotation around Z axis
TEST_F(Rigid3dToAngleAxisTest_72, Rotation180DegreesAroundZ_72) {
    double angle = M_PI;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    // The axis should be along Z (possibly positive or negative)
    EXPECT_NEAR(std::abs(result.z()), angle, kTolerance);
}

// Test small angle rotation
TEST_F(Rigid3dToAngleAxisTest_72, SmallAngleRotation_72) {
    double angle = 1e-6;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, 1e-5);
}

// Test arbitrary axis rotation
TEST_F(Rigid3dToAngleAxisTest_72, ArbitraryAxisRotation_72) {
    double angle = 1.2;
    Eigen::Vector3d axis(1.0, 2.0, 3.0);
    axis.normalize();
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    Eigen::Vector3d expected = angle * axis;
    EXPECT_NEAR(result.x(), expected.x(), kTolerance);
    EXPECT_NEAR(result.y(), expected.y(), kTolerance);
    EXPECT_NEAR(result.z(), expected.z(), kTolerance);
}

// Test that translation does not affect the result
TEST_F(Rigid3dToAngleAxisTest_72, TranslationDoesNotAffectResult_72) {
    double angle = M_PI / 4.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()));
    
    glomap::Rigid3d pose_no_trans(q, Eigen::Vector3d::Zero());
    glomap::Rigid3d pose_with_trans(q, Eigen::Vector3d(10.0, 20.0, 30.0));

    Eigen::Vector3d result1 = glomap::Rigid3dToAngleAxis(pose_no_trans);
    Eigen::Vector3d result2 = glomap::Rigid3dToAngleAxis(pose_with_trans);

    EXPECT_NEAR(result1.x(), result2.x(), kTolerance);
    EXPECT_NEAR(result1.y(), result2.y(), kTolerance);
    EXPECT_NEAR(result1.z(), result2.z(), kTolerance);
}

// Test negative rotation (opposite direction)
TEST_F(Rigid3dToAngleAxisTest_72, NegativeRotation_72) {
    double angle = -M_PI / 3.0;
    // AngleAxisd normalizes to positive angle, so we handle this carefully
    Eigen::AngleAxisd aa(angle, Eigen::Vector3d::UnitZ());
    Eigen::Quaterniond q(aa);
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    // The magnitude should be the absolute angle
    // The direction depends on the convention used by Eigen
    EXPECT_NEAR(result.norm(), std::abs(angle), kTolerance);
}

// Test round-trip: angle-axis -> quaternion -> Rigid3d -> angle-axis
TEST_F(Rigid3dToAngleAxisTest_72, RoundTripConsistency_72) {
    Eigen::Vector3d original_aa(0.3, -0.5, 0.7);
    double angle = original_aa.norm();
    Eigen::Vector3d axis = original_aa.normalized();
    
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
    glomap::Rigid3d pose(q, Eigen::Vector3d(1.0, 2.0, 3.0));

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.x(), original_aa.x(), kTolerance);
    EXPECT_NEAR(result.y(), original_aa.y(), kTolerance);
    EXPECT_NEAR(result.z(), original_aa.z(), kTolerance);
}

// Test 45 degree rotation around a diagonal axis
TEST_F(Rigid3dToAngleAxisTest_72, Rotation45DegreesDiagonalAxis_72) {
    double angle = M_PI / 4.0;
    Eigen::Vector3d axis = Eigen::Vector3d(1.0, 1.0, 1.0).normalized();
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    Eigen::Vector3d expected = angle * axis;
    EXPECT_NEAR(result.norm(), angle, kTolerance);
    EXPECT_NEAR(result.x(), expected.x(), kTolerance);
    EXPECT_NEAR(result.y(), expected.y(), kTolerance);
    EXPECT_NEAR(result.z(), expected.z(), kTolerance);
}

// Test very close to 180 degrees
TEST_F(Rigid3dToAngleAxisTest_72, NearlyPiRotation_72) {
    double angle = M_PI - 1e-8;
    Eigen::Vector3d axis = Eigen::Vector3d::UnitX();
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, 1e-6);
}

// Test default constructed Rigid3d (identity)
TEST_F(Rigid3dToAngleAxisTest_72, DefaultConstructedRigid3d_72) {
    glomap::Rigid3d pose;

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.x(), 0.0, kTolerance);
    EXPECT_NEAR(result.y(), 0.0, kTolerance);
    EXPECT_NEAR(result.z(), 0.0, kTolerance);
}

// Test full rotation (2*pi should behave as identity or near-zero)
TEST_F(Rigid3dToAngleAxisTest_72, FullRotation2Pi_72) {
    // A rotation of 2*pi is equivalent to identity
    // However, due to quaternion double cover, the quaternion for 2*pi rotation
    // is -identity, and AngleAxis may return 0 or 2*pi
    double angle = 2.0 * M_PI;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    // The result should be near zero or near 2*pi in magnitude
    // Since quaternion for 2pi is approximately -identity, angle-axis should give ~0 or ~2pi
    double norm = result.norm();
    bool is_near_zero = norm < 1e-6;
    bool is_near_2pi = std::abs(norm - 2.0 * M_PI) < 1e-6;
    EXPECT_TRUE(is_near_zero || is_near_2pi);
}
