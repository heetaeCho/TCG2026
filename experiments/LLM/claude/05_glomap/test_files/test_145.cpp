#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

// Include the header that defines Rigid3d and the function
// Based on the code, we need the glomap namespace and Rigid3d type
namespace glomap {

// Rigid3d is likely a struct/class containing at least a rotation (Eigen::Quaterniond)
// We infer this from usage: pose.rotation is used as Eigen::AngleAxis<double> constructor arg
// which accepts Eigen::Quaterniond
struct Rigid3d {
    Eigen::Quaterniond rotation;
    Eigen::Vector3d translation;
    
    Rigid3d() : rotation(Eigen::Quaterniond::Identity()), translation(Eigen::Vector3d::Zero()) {}
    Rigid3d(const Eigen::Quaterniond& q, const Eigen::Vector3d& t) : rotation(q), translation(t) {}
};

Eigen::Vector3d Rigid3dToAngleAxis(const Rigid3d& pose);

}  // namespace glomap

class Rigid3dToAngleAxisTest_145 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-10;
};

// Test identity rotation produces zero angle-axis vector
TEST_F(Rigid3dToAngleAxisTest_145, IdentityRotationReturnsZeroVector_145) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d::Zero();

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), 0.0, kTolerance);
}

// Test 90-degree rotation around X axis
TEST_F(Rigid3dToAngleAxisTest_145, Rotation90DegreesAroundXAxis_145) {
    double angle = M_PI / 2.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitX();
    EXPECT_NEAR(result.x(), expected.x(), kTolerance);
    EXPECT_NEAR(result.y(), expected.y(), kTolerance);
    EXPECT_NEAR(result.z(), expected.z(), kTolerance);
}

// Test 90-degree rotation around Y axis
TEST_F(Rigid3dToAngleAxisTest_145, Rotation90DegreesAroundYAxis_145) {
    double angle = M_PI / 2.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitY();
    EXPECT_NEAR(result.x(), expected.x(), kTolerance);
    EXPECT_NEAR(result.y(), expected.y(), kTolerance);
    EXPECT_NEAR(result.z(), expected.z(), kTolerance);
}

// Test 90-degree rotation around Z axis
TEST_F(Rigid3dToAngleAxisTest_145, Rotation90DegreesAroundZAxis_145) {
    double angle = M_PI / 2.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    Eigen::Vector3d expected = angle * Eigen::Vector3d::UnitZ();
    EXPECT_NEAR(result.x(), expected.x(), kTolerance);
    EXPECT_NEAR(result.y(), expected.y(), kTolerance);
    EXPECT_NEAR(result.z(), expected.z(), kTolerance);
}

// Test 180-degree rotation around X axis
TEST_F(Rigid3dToAngleAxisTest_145, Rotation180DegreesAroundXAxis_145) {
    double angle = M_PI;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
}

// Test small rotation angle
TEST_F(Rigid3dToAngleAxisTest_145, SmallRotationAngle_145) {
    double angle = 1e-6;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, 1e-5);
}

// Test arbitrary axis rotation
TEST_F(Rigid3dToAngleAxisTest_145, ArbitraryAxisRotation_145) {
    double angle = 1.2;
    Eigen::Vector3d axis(1.0, 2.0, 3.0);
    axis.normalize();
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    Eigen::Vector3d result_axis = result.normalized();
    EXPECT_NEAR(result_axis.x(), axis.x(), kTolerance);
    EXPECT_NEAR(result_axis.y(), axis.y(), kTolerance);
    EXPECT_NEAR(result_axis.z(), axis.z(), kTolerance);
}

// Test that translation does not affect the angle-axis result
TEST_F(Rigid3dToAngleAxisTest_145, TranslationDoesNotAffectResult_145) {
    double angle = M_PI / 4.0;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()));

    glomap::Rigid3d pose1(q, Eigen::Vector3d::Zero());
    glomap::Rigid3d pose2(q, Eigen::Vector3d(100.0, 200.0, 300.0));

    Eigen::Vector3d result1 = glomap::Rigid3dToAngleAxis(pose1);
    Eigen::Vector3d result2 = glomap::Rigid3dToAngleAxis(pose2);

    EXPECT_NEAR(result1.x(), result2.x(), kTolerance);
    EXPECT_NEAR(result1.y(), result2.y(), kTolerance);
    EXPECT_NEAR(result1.z(), result2.z(), kTolerance);
}

// Test angle magnitude for various angles
TEST_F(Rigid3dToAngleAxisTest_145, AngleMagnitudeIsCorrect_145) {
    std::vector<double> angles = {0.1, 0.5, 1.0, 2.0, 3.0, M_PI};
    Eigen::Vector3d axis = Eigen::Vector3d(1.0, 1.0, 1.0).normalized();

    for (double angle : angles) {
        Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
        glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

        Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

        EXPECT_NEAR(result.norm(), angle, kTolerance)
            << "Failed for angle = " << angle;
    }
}

// Test negative axis direction (quaternion with negative axis still represents valid rotation)
TEST_F(Rigid3dToAngleAxisTest_145, NegativeAxisDirection_145) {
    double angle = 1.0;
    Eigen::Vector3d axis = -Eigen::Vector3d::UnitX();
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    // The result should be equivalent: either angle*axis or (-angle)*(-axis)
    // The norm should be the angle
    EXPECT_NEAR(result.norm(), angle, kTolerance);
    // Direction should be along negative X or the equivalent representation
    Eigen::Vector3d expected = angle * axis;
    EXPECT_NEAR(result.x(), expected.x(), kTolerance);
    EXPECT_NEAR(result.y(), expected.y(), kTolerance);
    EXPECT_NEAR(result.z(), expected.z(), kTolerance);
}

// Test with a quaternion constructed directly (not from AngleAxis)
TEST_F(Rigid3dToAngleAxisTest_145, QuaternionDirectConstruction_145) {
    // 90 degrees around Z: q = (cos(45°), 0, 0, sin(45°))
    double half_angle = M_PI / 4.0;
    Eigen::Quaterniond q(std::cos(half_angle), 0.0, 0.0, std::sin(half_angle));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), M_PI / 2.0, kTolerance);
    EXPECT_NEAR(result.x(), 0.0, kTolerance);
    EXPECT_NEAR(result.y(), 0.0, kTolerance);
    EXPECT_NEAR(result.z(), M_PI / 2.0, kTolerance);
}

// Test roundtrip: angle-axis -> quaternion -> Rigid3dToAngleAxis should give back original
TEST_F(Rigid3dToAngleAxisTest_145, RoundtripConsistency_145) {
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

// Test very small angle (near zero)
TEST_F(Rigid3dToAngleAxisTest_145, VerySmallAngleNearZero_145) {
    double angle = 1e-12;
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    // For very small angles, the result should have very small magnitude
    EXPECT_NEAR(result.norm(), angle, 1e-8);
}

// Test 45 degree rotation
TEST_F(Rigid3dToAngleAxisTest_145, Rotation45Degrees_145) {
    double angle = M_PI / 4.0;
    Eigen::Vector3d axis = Eigen::Vector3d::UnitZ();
    Eigen::Quaterniond q(Eigen::AngleAxisd(angle, axis));
    glomap::Rigid3d pose(q, Eigen::Vector3d::Zero());

    Eigen::Vector3d result = glomap::Rigid3dToAngleAxis(pose);

    EXPECT_NEAR(result.norm(), angle, kTolerance);
    EXPECT_NEAR(result.x(), 0.0, kTolerance);
    EXPECT_NEAR(result.y(), 0.0, kTolerance);
    EXPECT_NEAR(result.z(), angle, kTolerance);
}
