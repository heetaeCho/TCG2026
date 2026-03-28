#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Include the header that declares CheckCheirality and Rigid3d
// Based on the file path, we infer the header location
namespace glomap {

struct Rigid3d {
    Eigen::Quaterniond rotation;
    Eigen::Vector3d translation;
    
    Rigid3d() : rotation(Eigen::Quaterniond::Identity()), translation(Eigen::Vector3d::Zero()) {}
    Rigid3d(const Eigen::Quaterniond& r, const Eigen::Vector3d& t) : rotation(r), translation(t) {}
};

bool CheckCheirality(const Rigid3d& pose,
                     const Eigen::Vector3d& x1,
                     const Eigen::Vector3d& x2,
                     double min_depth,
                     double max_depth);

}  // namespace glomap

class CheckCheiralityTest_135 : public ::testing::Test {
protected:
    glomap::Rigid3d identity_pose;
    
    void SetUp() override {
        identity_pose = glomap::Rigid3d(
            Eigen::Quaterniond::Identity(),
            Eigen::Vector3d::Zero()
        );
    }
};

// Test: Identity rotation with zero translation
// With zero translation, b1 = 0 and b2 = 0, so lambda1 = 0 and lambda2 = 0.
// With min_depth > 0 (after scaling), both lambdas should fail the check.
TEST_F(CheckCheiralityTest_135, IdentityPoseZeroTranslation_ReturnsFalse_135) {
    Eigen::Vector3d x1(0, 0, 1);
    Eigen::Vector3d x2(0, 0, 1);
    
    bool result = glomap::CheckCheirality(identity_pose, x1, x2, 0.01, 100.0);
    EXPECT_FALSE(result);
}

// Test: Points in front of both cameras with a pure translation along Z
TEST_F(CheckCheiralityTest_135, PureTranslationPointsInFront_135) {
    // Camera 2 is translated along the x-axis
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    // x1 and x2 are directions that are sufficiently different
    Eigen::Vector3d x1(0.5, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.5, 0, 1);
    x2.normalize();
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 1000.0);
    // Both points should be in front of both cameras
    EXPECT_TRUE(result);
}

// Test: Points behind a camera should fail cheirality
TEST_F(CheckCheiralityTest_135, PointsBehindCamera_ReturnsFalse_135) {
    // Camera 2 is translated along the x-axis
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    // Both directions point roughly the same way - parallel rays
    // x1 and x2 pointing in nearly the same direction won't triangulate well
    Eigen::Vector3d x1(0, 0, -1);  // pointing backward
    Eigen::Vector3d x2(0, 0, -1);  // pointing backward
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.01, 100.0);
    EXPECT_FALSE(result);
}

// Test: min_depth equals max_depth (very strict range)
TEST_F(CheckCheiralityTest_135, MinDepthEqualsMaxDepth_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    Eigen::Vector3d x1(0.5, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.5, 0, 1);
    x2.normalize();
    
    // When min_depth == max_depth, lambda must be strictly > min and strictly < max
    // which is impossible when they are equal
    bool result = glomap::CheckCheirality(pose, x1, x2, 5.0, 5.0);
    EXPECT_FALSE(result);
}

// Test: Very large max_depth should not prevent valid points
TEST_F(CheckCheiralityTest_135, LargeMaxDepth_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    Eigen::Vector3d x1(0.3, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.3, 0, 1);
    x2.normalize();
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 1e10);
    EXPECT_TRUE(result);
}

// Test: Negative min_depth (allowing points slightly behind)
TEST_F(CheckCheiralityTest_135, NegativeMinDepth_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    Eigen::Vector3d x1(0.5, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.5, 0, 1);
    x2.normalize();
    
    bool result = glomap::CheckCheirality(pose, x1, x2, -1.0, 1000.0);
    EXPECT_TRUE(result);
}

// Test: Rotation of 180 degrees should flip the point
TEST_F(CheckCheiralityTest_135, Rotation180Degrees_135) {
    // Rotate 180 degrees around Y axis
    Eigen::Quaterniond rot(Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitY()));
    glomap::Rigid3d pose(rot, Eigen::Vector3d(2, 0, 0));
    
    // Points looking forward
    Eigen::Vector3d x1(0, 0, 1);
    Eigen::Vector3d x2(0, 0, 1);  // After 180 rotation, this effectively looks backward
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.01, 100.0);
    // After rotation, camera 2 looks in the opposite direction
    // The triangulated point will likely be behind one camera
    EXPECT_FALSE(result);
}

// Test: Collinear rays (parallel directions, a ≈ ±1, degenerate case)
TEST_F(CheckCheiralityTest_135, CollinearRays_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    // Both rays pointing in the exact same direction
    Eigen::Vector3d x1(0, 0, 1);
    Eigen::Vector3d x2(0, 0, 1);
    
    // a = -Rx1.dot(x2) = -(0,0,1).(0,0,1) = -1
    // 1 - a*a = 1 - 1 = 0, so min_depth and max_depth become 0
    // lambda1 = b1 - a*b2, b1 = -(0,0,1).(1,0,0) = 0, b2 = (0,0,1).(1,0,0) = 0
    // lambda1 = 0, lambda2 = 0
    // 0 > 0 is false
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.01, 100.0);
    EXPECT_FALSE(result);
}

// Test: Small baseline with points far away
TEST_F(CheckCheiralityTest_135, SmallBaselineFarPoints_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0.001, 0, 0));
    
    Eigen::Vector3d x1(0.001, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.001, 0, 1);
    x2.normalize();
    
    // Points are far away but should still pass cheirality with appropriate depth range
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 1e8);
    EXPECT_TRUE(result);
}

// Test: Max depth too small should reject otherwise valid point
TEST_F(CheckCheiralityTest_135, MaxDepthTooSmall_ReturnsFalse_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    Eigen::Vector3d x1(0.1, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.1, 0, 1);
    x2.normalize();
    
    // With a very small max_depth, the computed depths should exceed it
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 0.00001);
    EXPECT_FALSE(result);
}

// Test: 90-degree rotation with appropriate translation
TEST_F(CheckCheiralityTest_135, Rotation90DegreesValidConfig_135) {
    // Rotate 90 degrees around Y axis - camera 2 looks along -X
    Eigen::Quaterniond rot(Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitY()));
    glomap::Rigid3d pose(rot, Eigen::Vector3d(1, 0, 1));
    
    // x1 pointing forward along Z
    Eigen::Vector3d x1(0, 0, 1);
    // x2 pointing forward along Z in camera 2's frame (which is -X in world)
    Eigen::Vector3d x2(0, 0, 1);
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 100.0);
    // The point should be at the intersection - both cameras looking towards it
    EXPECT_TRUE(result);
}

// Test: Zero direction vectors
TEST_F(CheckCheiralityTest_135, ZeroDirectionVectors_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    Eigen::Vector3d x1(0, 0, 0);
    Eigen::Vector3d x2(0, 0, 0);
    
    // With zero vectors, all dot products are 0, a = 0
    // lambda1 = 0, lambda2 = 0
    // 0 > min_depth * 1 where min_depth > 0 should be false
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.01, 100.0);
    EXPECT_FALSE(result);
}

// Test: min_depth of 0 with valid configuration
TEST_F(CheckCheiralityTest_135, ZeroMinDepth_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    Eigen::Vector3d x1(0.5, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.5, 0, 1);
    x2.normalize();
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 1000.0);
    EXPECT_TRUE(result);
}

// Test: Anti-parallel rays (a = 1)
TEST_F(CheckCheiralityTest_135, AntiParallelRays_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    // x1 and x2 point in opposite directions
    Eigen::Vector3d x1(0, 0, 1);
    Eigen::Vector3d x2(0, 0, -1);
    
    // a = -Rx1.dot(x2) = -(0,0,1).(0,0,-1) = 1
    // 1 - a*a = 0, degenerate
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.01, 100.0);
    EXPECT_FALSE(result);
}

// Test: Symmetric configuration
TEST_F(CheckCheiralityTest_135, SymmetricConfiguration_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(2, 0, 0));
    
    // Symmetric viewing directions
    Eigen::Vector3d x1(1, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-1, 0, 1);
    x2.normalize();
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 100.0);
    EXPECT_TRUE(result);
}

// Test: 3D points (non-planar directions)
TEST_F(CheckCheiralityTest_135, NonPlanarDirections_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    
    Eigen::Vector3d x1(0.3, 0.2, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.3, 0.2, 1);
    x2.normalize();
    
    bool result = glomap::CheckCheirality(pose, x1, x2, 0.0, 100.0);
    EXPECT_TRUE(result);
}

// Test: Very large translation
TEST_F(CheckCheiralityTest_135, VeryLargeTranslation_135) {
    glomap::Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1000, 0, 0));
    
    Eigen::Vector3d x1(0.5, 0, 1);
    x1.normalize();
    Eigen::Vector3d x2(-0.5, 0, 1);
    x2.normalize();
    
    // The depths will be very large due to large translation
    // With a small max_depth, this should fail
    bool result_small_max = glomap::CheckCheirality(pose, x1, x2, 0.0, 1.0);
    EXPECT_FALSE(result_small_max);
    
    // With a sufficiently large max_depth, should pass
    bool result_large_max = glomap::CheckCheirality(pose, x1, x2, 0.0, 1e8);
    EXPECT_TRUE(result_large_max);
}
