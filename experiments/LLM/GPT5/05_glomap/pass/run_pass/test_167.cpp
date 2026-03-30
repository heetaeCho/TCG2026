// File: fetzer_focal_length_cost_test_167.cc

#include <memory>
#include <vector>

#include <gtest/gtest.h>
#include <ceres/ceres.h>
#include <Eigen/Core>

#include "glomap/estimators/cost_function.h"

namespace {

class FetzerFocalLengthCostTest_167 : public ::testing::Test {
 protected:
  static Eigen::Matrix3d MakeFundamentalMatrix() {
    Eigen::Matrix3d F = Eigen::Matrix3d::Identity();
    F(0, 1) = 0.1;
    F(1, 2) = -0.2;
    return F;
  }

  static Eigen::Vector2d MakePrincipalPoint0() {
    Eigen::Vector2d p;
    p << 320.0, 240.0;
    return p;
  }

  static Eigen::Vector2d MakePrincipalPoint1() {
    Eigen::Vector2d p;
    p << 321.0, 239.0;
    return p;
  }
};

// Basic sanity: Create() should return a non-null CostFunction.
TEST_F(FetzerFocalLengthCostTest_167, CreateReturnsNonNull_167) {
  const Eigen::Matrix3d F = MakeFundamentalMatrix();
  const Eigen::Vector2d p0 = MakePrincipalPoint0();
  const Eigen::Vector2d p1 = MakePrincipalPoint1();

  std::unique_ptr<ceres::CostFunction> cost(
      glomap::FetzerFocalLengthCost::Create(F, p0, p1));

  EXPECT_NE(cost, nullptr);
}

// Interface check: CostFunction created from FetzerFocalLengthCost should
// expose two parameter blocks, matching the two pointer arguments in operator().
TEST_F(FetzerFocalLengthCostTest_167, CreateProvidesTwoParameterBlocks_167) {
  const Eigen::Matrix3d F = MakeFundamentalMatrix();
  const Eigen::Vector2d p0 = MakePrincipalPoint0();
  const Eigen::Vector2d p1 = MakePrincipalPoint1();

  std::unique_ptr<ceres::CostFunction> cost(
      glomap::FetzerFocalLengthCost::Create(F, p0, p1));
  ASSERT_NE(cost, nullptr);

  const std::vector<int32_t>& block_sizes = cost->parameter_block_sizes();
  EXPECT_EQ(block_sizes.size(), 2u);
}

// Normal operation: Evaluate() on the CostFunction with valid parameter blocks
// should succeed (return true) and produce a residual vector of the advertised size.
TEST_F(FetzerFocalLengthCostTest_167, EvaluateWithValidParametersSucceeds_167) {
  const Eigen::Matrix3d F = MakeFundamentalMatrix();
  const Eigen::Vector2d p0 = MakePrincipalPoint0();
  const Eigen::Vector2d p1 = MakePrincipalPoint1();

  std::unique_ptr<ceres::CostFunction> cost(
      glomap::FetzerFocalLengthCost::Create(F, p0, p1));
  ASSERT_NE(cost, nullptr);

  const std::vector<int32_t>& block_sizes = cost->parameter_block_sizes();
  ASSERT_EQ(block_sizes.size(), 2u);

  const int num_residuals = cost->num_residuals();
  ASSERT_GT(num_residuals, 0);

  std::vector<double> param0(block_sizes[0], 1.0);
  std::vector<double> param1(block_sizes[1], 2.0);
  std::vector<double> residuals(num_residuals, 0.0);

  const double* parameters[] = {param0.data(), param1.data()};

  const bool ok = cost->Evaluate(parameters, residuals.data(), nullptr);
  EXPECT_TRUE(ok);
}

// Boundary-ish case: use a zero fundamental matrix and verify that the
// created CostFunction still evaluates successfully for valid parameters.
TEST_F(FetzerFocalLengthCostTest_167, EvaluateWithZeroFundamentalMatrixSucceeds_167) {
  Eigen::Matrix3d F = Eigen::Matrix3d::Zero();
  const Eigen::Vector2d p0 = MakePrincipalPoint0();
  const Eigen::Vector2d p1 = MakePrincipalPoint1();

  std::unique_ptr<ceres::CostFunction> cost(
      glomap::FetzerFocalLengthCost::Create(F, p0, p1));
  ASSERT_NE(cost, nullptr);

  const std::vector<int32_t>& block_sizes = cost->parameter_block_sizes();
  ASSERT_EQ(block_sizes.size(), 2u);

  const int num_residuals = cost->num_residuals();
  ASSERT_GT(num_residuals, 0);

  std::vector<double> param0(block_sizes[0], 0.0);
  std::vector<double> param1(block_sizes[1], 0.0);
  std::vector<double> residuals(num_residuals, 0.0);

  const double* parameters[] = {param0.data(), param1.data()};

  const bool ok = cost->Evaluate(parameters, residuals.data(), nullptr);
  EXPECT_TRUE(ok);
}

// Cross-check between Create() and the functor operator(): use the dimensions
// inferred from the CostFunction to call the functor's operator() directly.
TEST_F(FetzerFocalLengthCostTest_167, FunctorOperatorAcceptsMatchingDimensions_167) {
  const Eigen::Matrix3d F = MakeFundamentalMatrix();
  const Eigen::Vector2d p0 = MakePrincipalPoint0();
  const Eigen::Vector2d p1 = MakePrincipalPoint1();

  // First, query dimensions through the created CostFunction.
  std::unique_ptr<ceres::CostFunction> cost(
      glomap::FetzerFocalLengthCost::Create(F, p0, p1));
  ASSERT_NE(cost, nullptr);

  const std::vector<int32_t>& block_sizes = cost->parameter_block_sizes();
  ASSERT_EQ(block_sizes.size(), 2u);

  const int num_residuals = cost->num_residuals();
  ASSERT_GT(num_residuals, 0);

  // Now construct the functor and call operator() with arrays of matching sizes.
  glomap::FetzerFocalLengthCost functor(F, p0, p1);

  std::vector<double> fi(block_sizes[0], 0.5);
  std::vector<double> fj(block_sizes[1], -0.3);
  std::vector<double> residuals(num_residuals, 0.0);

  const bool ok = functor(fi.data(), fj.data(), residuals.data());
  EXPECT_TRUE(ok);
}

}  // namespace
