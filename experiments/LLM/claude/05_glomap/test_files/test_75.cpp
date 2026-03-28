#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Based on the code, we need the Rigid3d struct and CenterFromPose function
// Infer the minimal Rigid3d structure from usage in the code
namespace glomap {

struct Rigid3d {
    Eigen::Quaterniond rotation;
    Eigen::Vector3d translation;
    
    Rigid3d() : rotation(Eigen::Quaterniond::Identity()), translation(Eigen::Vector3d::Zero()) {}
    Rigid3d(const Eigen::Quaterniond& r, const Eigen::Vector3d& t) : rotation(r), translation(t) {}
};

Eigen::Vector3d CenterFromPose(const Rigid3d& pose);

}  // namespace glomap

namespace {

class Rigid3dTest_75 : public ::testing::Test {
protected:
    static constexpr double kEpsilon = 1e-10;
};

// Test: Identity rotation with zero translation should give zero center
TEST_F(Rigid3dTest_75, IdentityPoseGivesZeroCenter_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d::Zero();
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, kEpsilon);
    EXPECT_NEAR(center.y(), 0.0, kEpsilon);
    EXPECT_NEAR(center.z(), 0.0, kEpsilon);
}

// Test: Identity rotation with non-zero translation
// center = R^{-1} * (-t) = I * (-t) = -t
TEST_F(Rigid3dTest_75, IdentityRotationNonZeroTranslation_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(1.0, 2.0, 3.0);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), -1.0, kEpsilon);
    EXPECT_NEAR(center.y(), -2.0, kEpsilon);
    EXPECT_NEAR(center.z(), -3.0, kEpsilon);
}

// Test: 90-degree rotation around Z-axis with translation
TEST_F(Rigid3dTest_75, Rotation90DegreesAroundZ_75) {
    glomap::Rigid3d pose;
    // 90 degrees around Z-axis
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
    pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);
    
    // center = R^{-1} * (-t)
    // R^{-1} is -90 deg around Z, so rotating (-1, 0, 0) by -90 deg around Z:
    // (-1, 0, 0) -> (0, 1, 0) ... wait let me compute properly
    // R (90 deg Z) maps (1,0,0) -> (0,1,0), (0,1,0) -> (-1,0,0)
    // R^{-1} maps (1,0,0) -> (0,-1,0), (0,1,0) -> (1,0,0)
    // center = R^{-1} * (-1, 0, 0) = (0, 1, 0)
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, kEpsilon);
    EXPECT_NEAR(center.y(), 1.0, kEpsilon);
    EXPECT_NEAR(center.z(), 0.0, kEpsilon);
}

// Test: 180-degree rotation around X-axis with translation
TEST_F(Rigid3dTest_75, Rotation180DegreesAroundX_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX()));
    pose.translation = Eigen::Vector3d(0.0, 1.0, 0.0);
    
    // R (180 deg X): (x,y,z) -> (x,-y,-z)
    // R^{-1} = R (since 180 deg rotation is its own inverse)
    // center = R^{-1} * (0, -1, 0) = (0, 1, 0)
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, kEpsilon);
    EXPECT_NEAR(center.y(), 1.0, kEpsilon);
    EXPECT_NEAR(center.z(), 0.0, kEpsilon);
}

// Test: 90-degree rotation around Y-axis with translation along Z
TEST_F(Rigid3dTest_75, Rotation90DegreesAroundY_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitY()));
    pose.translation = Eigen::Vector3d(0.0, 0.0, 1.0);
    
    // R (90 deg Y): (1,0,0)->(0,0,-1), (0,0,1)->(1,0,0)
    // R^{-1} (−90 deg Y): (1,0,0)->(0,0,1), (0,0,1)->(-1,0,0), (0,0,-1)->(1,0,0)
    // center = R^{-1} * (0, 0, -1) = (1, 0, 0)
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 1.0, kEpsilon);
    EXPECT_NEAR(center.y(), 0.0, kEpsilon);
    EXPECT_NEAR(center.z(), 0.0, kEpsilon);
}

// Test: Arbitrary rotation and translation
TEST_F(Rigid3dTest_75, ArbitraryPose_75) {
    Eigen::Quaterniond q(Eigen::AngleAxisd(0.5, Eigen::Vector3d(1.0, 1.0, 1.0).normalized()));
    Eigen::Vector3d t(3.0, -2.0, 1.0);
    
    glomap::Rigid3d pose(q, t);
    
    // Compute expected: center = q.inverse() * (-t)
    Eigen::Vector3d expected = q.inverse() * (-t);
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), expected.x(), kEpsilon);
    EXPECT_NEAR(center.y(), expected.y(), kEpsilon);
    EXPECT_NEAR(center.z(), expected.z(), kEpsilon);
}

// Test: Large translation values
TEST_F(Rigid3dTest_75, LargeTranslation_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(1e6, -1e6, 1e6);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), -1e6, 1e-4);
    EXPECT_NEAR(center.y(), 1e6, 1e-4);
    EXPECT_NEAR(center.z(), -1e6, 1e-4);
}

// Test: Very small translation values
TEST_F(Rigid3dTest_75, SmallTranslation_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(1e-15, -1e-15, 1e-15);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), -1e-15, 1e-25);
    EXPECT_NEAR(center.y(), 1e-15, 1e-25);
    EXPECT_NEAR(center.z(), -1e-15, 1e-25);
}

// Test: Rotation only, no translation -> center should be zero
TEST_F(Rigid3dTest_75, RotationOnlyNoTranslation_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(1.234, Eigen::Vector3d::UnitX()));
    pose.translation = Eigen::Vector3d::Zero();
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, kEpsilon);
    EXPECT_NEAR(center.y(), 0.0, kEpsilon);
    EXPECT_NEAR(center.z(), 0.0, kEpsilon);
}

// Test: Consecutive rotations (compound rotation)
TEST_F(Rigid3dTest_75, CompoundRotation_75) {
    Eigen::Quaterniond q1(Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitX()));
    Eigen::Quaterniond q2(Eigen::AngleAxisd(M_PI / 3.0, Eigen::Vector3d::UnitY()));
    Eigen::Quaterniond q = (q2 * q1).normalized();
    Eigen::Vector3d t(2.0, 3.0, 4.0);
    
    glomap::Rigid3d pose(q, t);
    
    Eigen::Vector3d expected = q.inverse() * (-t);
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), expected.x(), kEpsilon);
    EXPECT_NEAR(center.y(), expected.y(), kEpsilon);
    EXPECT_NEAR(center.z(), expected.z(), kEpsilon);
}

// Test: Negative translation components
TEST_F(Rigid3dTest_75, NegativeTranslation_75) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(-5.0, -10.0, -15.0);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 5.0, kEpsilon);
    EXPECT_NEAR(center.y(), 10.0, kEpsilon);
    EXPECT_NEAR(center.z(), 15.0, kEpsilon);
}

// Test: Consistency - applying pose to its center should give origin
// If C = R^{-1} * (-t), then R*C + t = R * R^{-1} * (-t) + t = -t + t = 0
TEST_F(Rigid3dTest_75, CenterTransformedToOrigin_75) {
    Eigen::Quaterniond q(Eigen::AngleAxisd(0.7, Eigen::Vector3d(0.3, 0.5, 0.8).normalized()));
    Eigen::Vector3d t(1.5, -2.5, 3.5);
    
    glomap::Rigid3d pose(q, t);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    // Transform center by the pose: R * center + t should be origin
    Eigen::Vector3d transformed = q * center + t;
    
    EXPECT_NEAR(transformed.x(), 0.0, kEpsilon);
    EXPECT_NEAR(transformed.y(), 0.0, kEpsilon);
    EXPECT_NEAR(transformed.z(), 0.0, kEpsilon);
}

}  // namespace
