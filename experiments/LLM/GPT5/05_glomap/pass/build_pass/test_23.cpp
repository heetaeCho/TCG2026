#include <gtest/gtest.h>
#include <memory>
#include <cmath>

#include "glomap/estimators/gravity_refinement.h"
#include <ceres/loss_function.h>

class GravityRefinerOptionsTest_23 : public ::testing::Test {
protected:
    glomap::GravityRefinerOptions options_;
};

// Normal operation: CreateLossFunction returns a valid loss function
// and it can be evaluated for a typical squared residual.
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionReturnsUsableLoss_23) {
    std::shared_ptr<ceres::LossFunction> loss = options_.CreateLossFunction();

    ASSERT_NE(loss, nullptr);

    double rho[3] = {0.0, 0.0, 0.0};
    const double sq_norm = 1.0;

    loss->Evaluate(sq_norm, rho);

    // Basic observable properties: finite values and non-negative primary loss.
    EXPECT_TRUE(std::isfinite(rho[0]));
    EXPECT_TRUE(std::isfinite(rho[1]));
    EXPECT_TRUE(std::isfinite(rho[2]));
    EXPECT_GE(rho[0], 0.0);
}

// Parameter sensitivity: Changing max_gravity_error should change the
// behavior of the created loss function (for the same residual).
TEST_F(GravityRefinerOptionsTest_23, LossFunctionDependsOnMaxGravityError_23) {
    glomap::GravityRefinerOptions options_default;
    glomap::GravityRefinerOptions options_modified;

    // Use a clearly different value to make behavioral difference more likely.
    options_modified.max_gravity_error = 10.0;

    std::shared_ptr<ceres::LossFunction> loss_default =
        options_default.CreateLossFunction();
    std::shared_ptr<ceres::LossFunction> loss_modified =
        options_modified.CreateLossFunction();

    ASSERT_NE(loss_default, nullptr);
    ASSERT_NE(loss_modified, nullptr);

    double rho_default[3] = {0.0, 0.0, 0.0};
    double rho_modified[3] = {0.0, 0.0, 0.0};
    const double sq_norm = 1.0;

    loss_default->Evaluate(sq_norm, rho_default);
    loss_modified->Evaluate(sq_norm, rho_modified);

    // Observable behavior: at least one of the loss outputs should differ
    // when the configuration value is changed.
    EXPECT_NE(rho_default[0], rho_modified[0]);
    // Optional: check at least one of the derivatives differs as well.
    // This keeps the test focused on behavior, not on exact formula.
    // (No expectation on sign or magnitude.)
    EXPECT_TRUE(
        (rho_default[1] != rho_modified[1]) ||
        (rho_default[2] != rho_modified[2]));
}

// Boundary condition: Very small max_gravity_error (including zero) should
// still yield a usable loss function (no crash, finite outputs).
TEST_F(GravityRefinerOptionsTest_23, ZeroOrSmallMaxGravityErrorProducesUsableLoss_23) {
    glomap::GravityRefinerOptions options_small;
    options_small.max_gravity_error = 0.0;  // boundary / extreme value

    std::shared_ptr<ceres::LossFunction> loss = options_small.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    double rho[3] = {0.0, 0.0, 0.0};
    const double sq_norm = 1.0;

    // Main expectation: Evaluate can be called and produces finite values.
    loss->Evaluate(sq_norm, rho);

    EXPECT_TRUE(std::isfinite(rho[0]));
    EXPECT_TRUE(std::isfinite(rho[1]));
    EXPECT_TRUE(std::isfinite(rho[2]));
}
