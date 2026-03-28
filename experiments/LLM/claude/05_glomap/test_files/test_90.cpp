#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "glomap/scene/frame.h"

namespace glomap {
namespace {

class GravityInfoTest_90 : public ::testing::Test {
 protected:
  GravityInfo gravity_info_;
};

// Test default construction state
TEST_F(GravityInfoTest_90, DefaultConstruction_HasGravityIsFalse_90) {
  EXPECT_FALSE(gravity_info_.has_gravity);
}

TEST_F(GravityInfoTest_90, DefaultConstruction_GravityIsZero_90) {
  Eigen::Vector3d gravity = gravity_info_.GetGravity();
  EXPECT_DOUBLE_EQ(gravity.x(), 0.0);
  EXPECT_DOUBLE_EQ(gravity.y(), 0.0);
  EXPECT_DOUBLE_EQ(gravity.z(), 0.0);
}

TEST_F(GravityInfoTest_90, DefaultConstruction_RAlignIsIdentity_90) {
  Eigen::Matrix3d r_align = gravity_info_.GetRAlign();
  EXPECT_TRUE(r_align.isApprox(Eigen::Matrix3d::Identity()));
}

// Test SetGravity sets has_gravity to true
TEST_F(GravityInfoTest_90, SetGravity_SetsHasGravityTrue_90) {
  Eigen::Vector3d g(0.0, 0.0, -9.81);
  gravity_info_.SetGravity(g);
  EXPECT_TRUE(gravity_info_.has_gravity);
}

// Test SetGravity stores the gravity vector correctly
TEST_F(GravityInfoTest_90, SetGravity_StoresGravityVector_90) {
  Eigen::Vector3d g(0.0, -9.81, 0.0);
  gravity_info_.SetGravity(g);
  Eigen::Vector3d retrieved = gravity_info_.GetGravity();
  EXPECT_TRUE(retrieved.isApprox(g));
}

// Test SetGravity with unit downward vector
TEST_F(GravityInfoTest_90, SetGravity_UnitDownwardVector_90) {
  Eigen::Vector3d g(0.0, 0.0, -1.0);
  gravity_info_.SetGravity(g);
  EXPECT_TRUE(gravity_info_.has_gravity);
  EXPECT_TRUE(gravity_info_.GetGravity().isApprox(g));
}

// Test SetGravity updates R_align (should no longer be identity for non-trivial gravity)
TEST_F(GravityInfoTest_90, SetGravity_UpdatesRAlign_90) {
  Eigen::Vector3d g(1.0, 0.0, 0.0);
  gravity_info_.SetGravity(g);
  Eigen::Matrix3d r_align = gravity_info_.GetRAlign();
  // R_align should be a valid rotation matrix (orthogonal, det=1)
  EXPECT_NEAR((r_align * r_align.transpose() - Eigen::Matrix3d::Identity()).norm(), 0.0, 1e-10);
  EXPECT_NEAR(r_align.determinant(), 1.0, 1e-10);
}

// Test SetGravity with arbitrary vector
TEST_F(GravityInfoTest_90, SetGravity_ArbitraryVector_90) {
  Eigen::Vector3d g(1.0, 2.0, 3.0);
  gravity_info_.SetGravity(g);
  EXPECT_TRUE(gravity_info_.has_gravity);
  EXPECT_TRUE(gravity_info_.GetGravity().isApprox(g));
}

// Test SetGravity called multiple times updates correctly
TEST_F(GravityInfoTest_90, SetGravity_CalledMultipleTimes_UpdatesCorrectly_90) {
  Eigen::Vector3d g1(0.0, 0.0, -9.81);
  Eigen::Vector3d g2(0.0, -9.81, 0.0);

  gravity_info_.SetGravity(g1);
  EXPECT_TRUE(gravity_info_.GetGravity().isApprox(g1));

  gravity_info_.SetGravity(g2);
  EXPECT_TRUE(gravity_info_.GetGravity().isApprox(g2));
  EXPECT_TRUE(gravity_info_.has_gravity);
}

// Test SetGravity with negative components
TEST_F(GravityInfoTest_90, SetGravity_NegativeComponents_90) {
  Eigen::Vector3d g(-1.0, -2.0, -3.0);
  gravity_info_.SetGravity(g);
  EXPECT_TRUE(gravity_info_.has_gravity);
  EXPECT_TRUE(gravity_info_.GetGravity().isApprox(g));
}

// Test that R_align is a proper rotation matrix for various gravity directions
TEST_F(GravityInfoTest_90, SetGravity_RAlignIsProperRotation_YAxis_90) {
  Eigen::Vector3d g(0.0, 1.0, 0.0);
  gravity_info_.SetGravity(g);
  Eigen::Matrix3d r_align = gravity_info_.GetRAlign();
  EXPECT_NEAR((r_align * r_align.transpose() - Eigen::Matrix3d::Identity()).norm(), 0.0, 1e-10);
  EXPECT_NEAR(r_align.determinant(), 1.0, 1e-10);
}

TEST_F(GravityInfoTest_90, SetGravity_RAlignIsProperRotation_DiagonalVector_90) {
  Eigen::Vector3d g(1.0, 1.0, 1.0);
  gravity_info_.SetGravity(g);
  Eigen::Matrix3d r_align = gravity_info_.GetRAlign();
  EXPECT_NEAR((r_align * r_align.transpose() - Eigen::Matrix3d::Identity()).norm(), 0.0, 1e-10);
  EXPECT_NEAR(r_align.determinant(), 1.0, 1e-10);
}

// Test GetRAlign const correctness (can call on const object after setup)
TEST_F(GravityInfoTest_90, GetRAlign_ReturnsConstReference_90) {
  Eigen::Vector3d g(0.0, 0.0, -9.81);
  gravity_info_.SetGravity(g);
  const GravityInfo& const_ref = gravity_info_;
  const Eigen::Matrix3d& r_align = const_ref.GetRAlign();
  EXPECT_NEAR(r_align.determinant(), 1.0, 1e-10);
}

// Test GetGravity const correctness
TEST_F(GravityInfoTest_90, GetGravity_ReturnsCorrectValueFromConst_90) {
  Eigen::Vector3d g(3.0, 4.0, 5.0);
  gravity_info_.SetGravity(g);
  const GravityInfo& const_ref = gravity_info_;
  Eigen::Vector3d retrieved = const_ref.GetGravity();
  EXPECT_TRUE(retrieved.isApprox(g));
}

// Test that different gravity vectors produce different R_align
TEST_F(GravityInfoTest_90, SetGravity_DifferentVectorsProduceDifferentRAlign_90) {
  GravityInfo info1, info2;
  info1.SetGravity(Eigen::Vector3d(1.0, 0.0, 0.0));
  info2.SetGravity(Eigen::Vector3d(0.0, 1.0, 0.0));
  // These should generally produce different alignment rotations
  EXPECT_FALSE(info1.GetRAlign().isApprox(info2.GetRAlign()));
}

// Test with very small gravity vector
TEST_F(GravityInfoTest_90, SetGravity_SmallVector_90) {
  Eigen::Vector3d g(1e-10, 1e-10, 1e-10);
  gravity_info_.SetGravity(g);
  EXPECT_TRUE(gravity_info_.has_gravity);
  EXPECT_TRUE(gravity_info_.GetGravity().isApprox(g));
}

// Test with large gravity vector
TEST_F(GravityInfoTest_90, SetGravity_LargeVector_90) {
  Eigen::Vector3d g(1e6, 1e6, 1e6);
  gravity_info_.SetGravity(g);
  EXPECT_TRUE(gravity_info_.has_gravity);
  EXPECT_TRUE(gravity_info_.GetGravity().isApprox(g));
}

}  // namespace
}  // namespace glomap
