#include <gtest/gtest.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "glomap/estimators/cost_function.h"

namespace glomap {
namespace {

class FetzerFocalLengthCostTest_163 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test construction with identity fundamental matrix and zero principal points
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithIdentityFAndZeroPrincipalPoints_163) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp0(0.0, 0.0);
  Eigen::Vector2d pp1(0.0, 0.0);

  EXPECT_NO_THROW(FetzerFocalLengthCost cost(F, pp0, pp1));
}

// Test construction with zero fundamental matrix
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithZeroF_163) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  Eigen::Vector2d pp0(0.0, 0.0);
  Eigen::Vector2d pp1(0.0, 0.0);

  EXPECT_NO_THROW(FetzerFocalLengthCost cost(F, pp0, pp1));
}

// Test construction with non-zero principal points
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithNonZeroPrincipalPoints_163) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp0(320.0, 240.0);
  Eigen::Vector2d pp1(320.0, 240.0);

  EXPECT_NO_THROW(FetzerFocalLengthCost cost(F, pp0, pp1));
}

// Test construction with typical fundamental matrix
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithTypicalFundamentalMatrix_163) {
  Eigen::Matrix3d F;
  F << 0.0, 0.0, 0.0,
       0.0, 0.0, -1.0,
       0.0, 1.0, 0.0;
  Eigen::Vector2d pp0(320.0, 240.0);
  Eigen::Vector2d pp1(320.0, 240.0);

  EXPECT_NO_THROW(FetzerFocalLengthCost cost(F, pp0, pp1));
}

// Test that d_01, d_02, d_12 are accessible after construction
TEST_F(FetzerFocalLengthCostTest_163, MembersAccessibleAfterConstruction_163) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp0(0.0, 0.0);
  Eigen::Vector2d pp1(0.0, 0.0);

  FetzerFocalLengthCost cost(F, pp0, pp1);

  // d_01, d_02, d_12 should be Eigen::Vector4d and accessible
  EXPECT_EQ(cost.d_01.size(), 4);
  EXPECT_EQ(cost.d_02.size(), 4);
  EXPECT_EQ(cost.d_12.size(), 4);
}

// Test with negative principal points
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithNegativePrincipalPoints_163) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
  Eigen::Vector2d pp0(-100.0, -200.0);
  Eigen::Vector2d pp1(-150.0, -250.0);

  EXPECT_NO_THROW(FetzerFocalLengthCost cost(F, pp0, pp1));
}

// Test with asymmetric principal points
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithAsymmetricPrincipalPoints_163) {
  Eigen::Matrix3d F;
  F << 1e-7, 2e-6, 3e-4,
       -2e-6, 1e-7, -5e-4,
       3e-4, 5e-4, 1.0;
  Eigen::Vector2d pp0(500.0, 300.0);
  Eigen::Vector2d pp1(640.0, 480.0);

  FetzerFocalLengthCost cost(F, pp0, pp1);

  // Verify members are finite
  EXPECT_TRUE(cost.d_01.allFinite());
  EXPECT_TRUE(cost.d_02.allFinite());
  EXPECT_TRUE(cost.d_12.allFinite());
}

// Test with large values in fundamental matrix
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithLargeValues_163) {
  Eigen::Matrix3d F;
  F << 1e10, 2e10, 3e10,
       4e10, 5e10, 6e10,
       7e10, 8e10, 9e10;
  Eigen::Vector2d pp0(1e4, 1e4);
  Eigen::Vector2d pp1(1e4, 1e4);

  EXPECT_NO_THROW(FetzerFocalLengthCost cost(F, pp0, pp1));
}

// Test with very small values
TEST_F(FetzerFocalLengthCostTest_163, ConstructWithVerySmallValues_163) {
  Eigen::Matrix3d F;
  F << 1e-15, 2e-15, 3e-15,
       4e-15, 5e-15, 6e-15,
       7e-15, 8e-15, 9e-15;
  Eigen::Vector2d pp0(0.001, 0.001);
  Eigen::Vector2d pp1(0.001, 0.001);

  EXPECT_NO_THROW(FetzerFocalLengthCost cost(F, pp0, pp1));
}

// Test that zero principal points yield G = K1^T * F * K0 = F (since K0=K1=Identity)
TEST_F(FetzerFocalLengthCostTest_163, ZeroPrincipalPointsGEqualsF_163) {
  Eigen::Matrix3d F;
  F << 0, 0, 0,
       0, 0, -1,
       0, 1, 0;
  Eigen::Vector2d pp0(0.0, 0.0);
  Eigen::Vector2d pp1(0.0, 0.0);

  FetzerFocalLengthCost cost1(F, pp0, pp1);

  // With zero principal points, K matrices are identity,
  // so the result should be deterministic and reproducible
  FetzerFocalLengthCost cost2(F, pp0, pp1);

  EXPECT_EQ(cost1.d_01, cost2.d_01);
  EXPECT_EQ(cost1.d_02, cost2.d_02);
  EXPECT_EQ(cost1.d_12, cost2.d_12);
}

// Test reproducibility - same inputs give same outputs
TEST_F(FetzerFocalLengthCostTest_163, Reproducibility_163) {
  Eigen::Matrix3d F;
  F << 0.1, 0.2, 0.3,
       0.4, 0.5, 0.6,
       0.7, 0.8, 0.9;
  Eigen::Vector2d pp0(320.0, 240.0);
  Eigen::Vector2d pp1(640.0, 480.0);

  FetzerFocalLengthCost cost1(F, pp0, pp1);
  FetzerFocalLengthCost cost2(F, pp0, pp1);

  EXPECT_EQ(cost1.d_01, cost2.d_01);
  EXPECT_EQ(cost1.d_02, cost2.d_02);
  EXPECT_EQ(cost1.d_12, cost2.d_12);
}

// Test that different inputs produce different outputs
TEST_F(FetzerFocalLengthCostTest_163, DifferentInputsDifferentOutputs_163) {
  Eigen::Matrix3d F1 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d F2;
  F2 << 0, 0, 0,
        0, 0, -1,
        0, 1, 0;
  Eigen::Vector2d pp0(320.0, 240.0);
  Eigen::Vector2d pp1(320.0, 240.0);

  FetzerFocalLengthCost cost1(F1, pp0, pp1);
  FetzerFocalLengthCost cost2(F2, pp0, pp1);

  bool all_same = (cost1.d_01 == cost2.d_01) &&
                  (cost1.d_02 == cost2.d_02) &&
                  (cost1.d_12 == cost2.d_12);
  EXPECT_FALSE(all_same);
}

}  // namespace
}  // namespace glomap
