#include <gtest/gtest.h>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

// Include the header for Rigid3d and CalcTransAngle
// Based on the code, we need the glomap namespace and Rigid3d type
namespace glomap {

// Rigid3d likely wraps a rotation and translation, similar to Sophus or colmap's Rigid3d
// We define it here if not available from headers, based on usage in the code
struct Rigid3d {
    Eigen::Quaterniond rotation;
    Eigen::Vector3d translation;
    
    Rigid3d() : rotation(Eigen::Quaterniond::Identity()), translation(Eigen::Vector3d::Zero()) {}
    Rigid3d(const Eigen::Quaterniond& q, const Eigen::Vector3d& t) : rotation(q), translation(t) {}
};

double CalcTransAngle(const Rigid3d& pose1, const Rigid3d& pose2);

}  // namespace glomap

using namespace glomap;

class CalcTransAngleTest_143 : public ::testing::Test {
protected:
    static constexpr double kTolerance = 1e-8;
};

// Test: Same translation direction should give 0 degrees
TEST_F(CalcTransAngleTest_143, SameDirection_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(2, 0, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test: Opposite translation directions should give 180 degrees
TEST_F(CalcTransAngleTest_143, OppositeDirection_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(-1, 0, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 180.0, kTolerance);
}

// Test: Perpendicular translations should give 90 degrees
TEST_F(CalcTransAngleTest_143, PerpendicularDirections_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 1, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test: 45 degree angle between translations
TEST_F(CalcTransAngleTest_143, FortyFiveDegrees_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 1, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 45.0, kTolerance);
}

// Test: Same poses should return 0
TEST_F(CalcTransAngleTest_143, IdenticalPoses_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(3, 4, 5));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(3, 4, 5));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test: Scaled same direction should still be 0 degrees
TEST_F(CalcTransAngleTest_143, ScaledSameDirection_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 2, 3));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(10, 20, 30));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test: Symmetry - CalcTransAngle(a, b) == CalcTransAngle(b, a)
TEST_F(CalcTransAngleTest_143, Symmetry_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 2, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 3, 4));
    
    double angle1 = CalcTransAngle(pose1, pose2);
    double angle2 = CalcTransAngle(pose2, pose1);
    EXPECT_NEAR(angle1, angle2, kTolerance);
}

// Test: 3D perpendicular vectors
TEST_F(CalcTransAngleTest_143, Perpendicular3D_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 0, 1));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 1, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test: 60 degree angle
TEST_F(CalcTransAngleTest_143, SixtyDegrees_143) {
    // cos(60°) = 0.5, so dot product / (norm*norm) = 0.5
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), 
                  Eigen::Vector3d(std::cos(M_PI / 3.0), std::sin(M_PI / 3.0), 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 60.0, kTolerance);
}

// Test: 120 degree angle
TEST_F(CalcTransAngleTest_143, OneTwentyDegrees_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), 
                  Eigen::Vector3d(std::cos(2.0 * M_PI / 3.0), std::sin(2.0 * M_PI / 3.0), 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 120.0, kTolerance);
}

// Test: Rotation component of Rigid3d should not affect the angle
TEST_F(CalcTransAngleTest_143, RotationDoesNotAffectAngle_143) {
    Eigen::Quaterniond q1(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ()));
    Eigen::Quaterniond q2(Eigen::AngleAxisd(1.5, Eigen::Vector3d::UnitY()));
    
    Rigid3d pose1(q1, Eigen::Vector3d(1, 0, 0));
    Rigid3d pose2(q2, Eigen::Vector3d(0, 1, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test: Negative translations that are in same direction
TEST_F(CalcTransAngleTest_143, NegativeTranslationsSameDirection_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(-1, -2, -3));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(-2, -4, -6));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 0.0, kTolerance);
}

// Test: Very small translations (near zero but not zero)
TEST_F(CalcTransAngleTest_143, VerySmallTranslations_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1e-10, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 1e-10, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test: Large magnitude translations
TEST_F(CalcTransAngleTest_143, LargeTranslations_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1e10, 0, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 1e10, 0));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 90.0, kTolerance);
}

// Test: Result is always non-negative
TEST_F(CalcTransAngleTest_143, ResultNonNegative_143) {
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, -1, 0.5));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(-0.3, 2, -1));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_GE(angle, 0.0);
    EXPECT_LE(angle, 180.0);
}

// Test: Result is bounded between 0 and 180
TEST_F(CalcTransAngleTest_143, ResultBounded_143) {
    // Test with various random-ish vectors
    std::vector<Eigen::Vector3d> translations = {
        {1, 2, 3}, {-1, 5, -2}, {0.1, -0.5, 0.3}, {100, -200, 300}
    };
    
    for (size_t i = 0; i < translations.size(); ++i) {
        for (size_t j = 0; j < translations.size(); ++j) {
            Rigid3d p1(Eigen::Quaterniond::Identity(), translations[i]);
            Rigid3d p2(Eigen::Quaterniond::Identity(), translations[j]);
            double angle = CalcTransAngle(p1, p2);
            EXPECT_GE(angle, 0.0) << "i=" << i << " j=" << j;
            EXPECT_LE(angle, 180.0 + kTolerance) << "i=" << i << " j=" << j;
        }
    }
}

// Test: Unit vectors in all three axes
TEST_F(CalcTransAngleTest_143, AllAxisPerpendicular_143) {
    Rigid3d poseX(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 0));
    Rigid3d poseY(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 1, 0));
    Rigid3d poseZ(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0, 0, 1));
    
    EXPECT_NEAR(CalcTransAngle(poseX, poseY), 90.0, kTolerance);
    EXPECT_NEAR(CalcTransAngle(poseY, poseZ), 90.0, kTolerance);
    EXPECT_NEAR(CalcTransAngle(poseX, poseZ), 90.0, kTolerance);
}

// Test: Angle between diagonal vectors
TEST_F(CalcTransAngleTest_143, DiagonalVectors_143) {
    // (1,1,0) and (1,0,1) -> cos = 1/2, angle = 60 degrees
    Rigid3d pose1(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 1, 0));
    Rigid3d pose2(Eigen::Quaterniond::Identity(), Eigen::Vector3d(1, 0, 1));
    
    double angle = CalcTransAngle(pose1, pose2);
    EXPECT_NEAR(angle, 60.0, kTolerance);
}
