#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Based on the code, we need the Rigid3d struct and CenterFromPose function
// Infer minimal definition of Rigid3d from usage in the .cc file
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

class CenterFromPoseTest_148 : public ::testing::Test {
 protected:
};

// Test with identity rotation and zero translation
// Center should be at origin
TEST_F(CenterFromPoseTest_148, IdentityPoseReturnsOrigin_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d::Zero();
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, 1e-12);
    EXPECT_NEAR(center.y(), 0.0, 1e-12);
    EXPECT_NEAR(center.z(), 0.0, 1e-12);
}

// Test with identity rotation and non-zero translation
// Center = R^{-1} * (-t) = I * (-t) = -t
TEST_F(CenterFromPoseTest_148, IdentityRotationWithTranslation_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(1.0, 2.0, 3.0);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), -1.0, 1e-12);
    EXPECT_NEAR(center.y(), -2.0, 1e-12);
    EXPECT_NEAR(center.z(), -3.0, 1e-12);
}

// Test with 90 degree rotation around Z-axis and zero translation
// Center should be zero since translation is zero
TEST_F(CenterFromPoseTest_148, RotationOnlyNoTranslation_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
    pose.translation = Eigen::Vector3d::Zero();
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, 1e-12);
    EXPECT_NEAR(center.y(), 0.0, 1e-12);
    EXPECT_NEAR(center.z(), 0.0, 1e-12);
}

// Test with 90 degree rotation around Z and translation along X
// R = Rz(90), t = (1, 0, 0)
// R^{-1} = Rz(-90), center = Rz(-90) * (-1, 0, 0) = (0, 1, 0) ... let's compute:
// Rz(-90) rotates (x,y,z) -> (y, -x, z), so (-1, 0, 0) -> (0, 1, 0)
TEST_F(CenterFromPoseTest_148, Rotation90ZWithTranslationX_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitZ()));
    pose.translation = Eigen::Vector3d(1.0, 0.0, 0.0);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, 1e-10);
    EXPECT_NEAR(center.y(), 1.0, 1e-10);
    EXPECT_NEAR(center.z(), 0.0, 1e-10);
}

// Test with 180 degree rotation around X-axis and translation
// R = Rx(180), R^{-1} = Rx(-180) = Rx(180)
// Rx(180): (x,y,z) -> (x, -y, -z)
// center = Rx(180) * (-(1,2,3)) = Rx(180) * (-1,-2,-3) = (-1, 2, 3)
TEST_F(CenterFromPoseTest_148, Rotation180XWithTranslation_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX()));
    pose.translation = Eigen::Vector3d(1.0, 2.0, 3.0);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), -1.0, 1e-10);
    EXPECT_NEAR(center.y(), 2.0, 1e-10);
    EXPECT_NEAR(center.z(), 3.0, 1e-10);
}

// Test with 90 degree rotation around Y-axis and translation
// R = Ry(90), R^{-1} = Ry(-90)
// Ry(-90): (x,y,z) -> (-z, y, x)
// center = Ry(-90) * (-(5, 0, 0)) = Ry(-90) * (-5, 0, 0) = (0, 0, -5)
TEST_F(CenterFromPoseTest_148, Rotation90YWithTranslationX_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitY()));
    pose.translation = Eigen::Vector3d(5.0, 0.0, 0.0);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 0.0, 1e-10);
    EXPECT_NEAR(center.y(), 0.0, 1e-10);
    EXPECT_NEAR(center.z(), -5.0, 1e-10);
}

// Test with arbitrary rotation and translation
// Verify that pose.rotation * center + pose.translation = 0
// i.e., center = R^{-1} * (-t) implies R * center = -t
TEST_F(CenterFromPoseTest_148, ArbitraryPoseSatisfiesInverseRelation_148) {
    Eigen::Quaterniond q(Eigen::AngleAxisd(0.7, Eigen::Vector3d(1.0, 2.0, 3.0).normalized()));
    Eigen::Vector3d t(4.5, -3.2, 1.7);
    
    glomap::Rigid3d pose;
    pose.rotation = q;
    pose.translation = t;
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    // Verify: R * center + t = 0
    Eigen::Vector3d result = pose.rotation * center + pose.translation;
    EXPECT_NEAR(result.x(), 0.0, 1e-10);
    EXPECT_NEAR(result.y(), 0.0, 1e-10);
    EXPECT_NEAR(result.z(), 0.0, 1e-10);
}

// Test with very large translation values
TEST_F(CenterFromPoseTest_148, LargeTranslationValues_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(1e10, -1e10, 1e10);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), -1e10, 1e-2);
    EXPECT_NEAR(center.y(), 1e10, 1e-2);
    EXPECT_NEAR(center.z(), -1e10, 1e-2);
}

// Test with very small translation values
TEST_F(CenterFromPoseTest_148, SmallTranslationValues_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(1e-15, -1e-15, 1e-15);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), -1e-15, 1e-25);
    EXPECT_NEAR(center.y(), 1e-15, 1e-25);
    EXPECT_NEAR(center.z(), -1e-15, 1e-25);
}

// Test with negative translation components
TEST_F(CenterFromPoseTest_148, NegativeTranslation_148) {
    glomap::Rigid3d pose;
    pose.rotation = Eigen::Quaterniond::Identity();
    pose.translation = Eigen::Vector3d(-5.0, -10.0, -15.0);
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    EXPECT_NEAR(center.x(), 5.0, 1e-12);
    EXPECT_NEAR(center.y(), 10.0, 1e-12);
    EXPECT_NEAR(center.z(), 15.0, 1e-12);
}

// Test with a compound rotation (multiple axes)
TEST_F(CenterFromPoseTest_148, CompoundRotationWithTranslation_148) {
    Eigen::Quaterniond q = Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 4.0, Eigen::Vector3d::UnitX())) *
                           Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 3.0, Eigen::Vector3d::UnitY())) *
                           Eigen::Quaterniond(Eigen::AngleAxisd(M_PI / 6.0, Eigen::Vector3d::UnitZ()));
    Eigen::Vector3d t(2.0, -3.0, 7.0);
    
    glomap::Rigid3d pose;
    pose.rotation = q.normalized();
    pose.translation = t;
    
    Eigen::Vector3d center = glomap::CenterFromPose(pose);
    
    // Verify: R * center + t = 0
    Eigen::Vector3d result = pose.rotation * center + pose.translation;
    EXPECT_NEAR(result.x(), 0.0, 1e-10);
    EXPECT_NEAR(result.y(), 0.0, 1e-10);
    EXPECT_NEAR(result.z(), 0.0, 1e-10);
}

// Test consistency: applying CenterFromPose twice with the same pose gives the same result
TEST_F(CenterFromPoseTest_148, Deterministic_148) {
    Eigen::Quaterniond q(Eigen::AngleAxisd(1.23, Eigen::Vector3d(0.5, 0.3, 0.8).normalized()));
    Eigen::Vector3d t(11.0, -22.0, 33.0);
    
    glomap::Rigid3d pose;
    pose.rotation = q;
    pose.translation = t;
    
    Eigen::Vector3d center1 = glomap::CenterFromPose(pose);
    Eigen::Vector3d center2 = glomap::CenterFromPose(pose);
    
    EXPECT_DOUBLE_EQ(center1.x(), center2.x());
    EXPECT_DOUBLE_EQ(center1.y(), center2.y());
    EXPECT_DOUBLE_EQ(center1.z(), center2.z());
}

}  // namespace
