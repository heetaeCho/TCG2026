// File: global_positioner_options_test_24.cc

#include <memory>
#include <limits>
#include <cmath>

#include <gtest/gtest.h>
#include <ceres/loss_function.h>  // For ceres::LossFunction and ceres::HuberLoss

#include "glomap/estimators/global_positioning.h"

namespace glomap {

class GlobalPositionerOptionsTest_24 : public ::testing::Test {
 protected:
  GlobalPositionerOptions options_;
};

// [Normal operation]
// Verify that CreateLossFunction returns a non-null shared_ptr.
TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunctionReturnsNonNull_24) {
  std::shared_ptr<ceres::LossFunction> loss = options_.CreateLossFunction();
  EXPECT_NE(loss, nullptr);
}

// [Normal operation / Type check]
// Verify that the created loss function is a ceres::HuberLoss instance
// (i.e., the dynamic type is as expected).
TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunctionReturnsHuberLossInstance_24) {
  std::shared_ptr<ceres::LossFunction> loss = options_.CreateLossFunction();

  // The pointer should be non-null.
  ASSERT_NE(loss, nullptr);

  // The dynamic type should be ceres::HuberLoss.
  ceres::HuberLoss* huber_loss = dynamic_cast<ceres::HuberLoss*>(loss.get());
  EXPECT_NE(huber_loss, nullptr);
}

// [Boundary / Factory behavior]
// Verify that each call to CreateLossFunction returns a distinct instance
// (no unexpected sharing/caching of the same object).
TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunctionReturnsDistinctInstances_24) {
  std::shared_ptr<ceres::LossFunction> loss1 = options_.CreateLossFunction();
  std::shared_ptr<ceres::LossFunction> loss2 = options_.CreateLossFunction();

  ASSERT_NE(loss1, nullptr);
  ASSERT_NE(loss2, nullptr);

  // Distinct shared_ptr instances should not manage the same object.
  EXPECT_NE(loss1.get(), loss2.get());
}

// [Observable behavior via base interface]
// Verify that the returned loss function behaves like a proper ceres::LossFunction
// by checking that Evaluate writes valid values into the output buffer.
TEST_F(GlobalPositionerOptionsTest_24, CreatedLossFunctionEvaluatesWithoutNaN_24) {
  std::shared_ptr<ceres::LossFunction> loss = options_.CreateLossFunction();
  ASSERT_NE(loss, nullptr);

  double rho[3];
  // Initialize with NaNs to detect if Evaluate actually writes into them.
  rho[0] = std::numeric_limits<double>::quiet_NaN();
  rho[1] = std::numeric_limits<double>::quiet_NaN();
  rho[2] = std::numeric_limits<double>::quiet_NaN();

  // Use a simple positive squared residual.
  const double squared_norm = 1.0;
  loss->Evaluate(squared_norm, rho);

  // After Evaluate, at least rho[0] should be a finite value.
  EXPECT_FALSE(std::isnan(rho[0]));
}

}  // namespace glomap
