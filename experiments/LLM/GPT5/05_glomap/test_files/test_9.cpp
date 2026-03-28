#include <gtest/gtest.h>
#include <ceres/ceres.h>

#include "glomap/estimators/bundle_adjustment.h"

using glomap::BundleAdjusterOptions;

// Test fixture
class BundleAdjusterOptionsTest_9 : public ::testing::Test {
protected:
    BundleAdjusterOptions options_;
};

//------------------------------------------------------------------------------
// Constructor / default values
//------------------------------------------------------------------------------

TEST_F(BundleAdjusterOptionsTest_9, DefaultConstructorSetsExpectedFlags_9) {
    // These are public members, so we can directly check their default values.

    EXPECT_FALSE(options_.optimize_rig_poses);
    EXPECT_TRUE(options_.optimize_rotations);
    EXPECT_TRUE(options_.optimize_translation);
    EXPECT_TRUE(options_.optimize_intrinsics);
    EXPECT_FALSE(options_.optimize_principal_point);
    EXPECT_TRUE(options_.optimize_points);
    EXPECT_TRUE(options_.use_gpu);

    // Boundary-related numeric defaults
    EXPECT_GE(options_.min_num_images_gpu_solver, 0);
    EXPECT_GE(options_.min_num_view_per_track, 0);

    // gpu_index is default-constructed string; the header snippet shows "-1",
    // but we only assert that it's not an obviously invalid empty state here.
    EXPECT_FALSE(options_.gpu_index.empty());
}

//------------------------------------------------------------------------------
// CreateLossFunction: normal behavior
//------------------------------------------------------------------------------

TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionReturnsNonNullHuberLoss_9) {
    // Normal operation: should return a non-null loss function.
    std::shared_ptr<ceres::LossFunction> loss = options_.CreateLossFunction();

    ASSERT_NE(loss, nullptr);

    // Check that the dynamic type is ceres::HuberLoss as specified
    // by the current implementation.
    auto* huber = dynamic_cast<ceres::HuberLoss*>(loss.get());
    EXPECT_NE(huber, nullptr);

    // Also verify that Evaluate can be called without issues.
    double rho[3] = {0.0, 0.0, 0.0};
    EXPECT_NO_THROW(loss->Evaluate(0.5, rho));
}

//------------------------------------------------------------------------------
// CreateLossFunction: uses current thres_loss_function
//------------------------------------------------------------------------------

TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionUsesCurrentThreshold_9) {
    // Change the threshold and verify that the created loss behaves
    // consistently with a reference HuberLoss constructed with the same value.
    options_.thres_loss_function = 0.25;

    std::shared_ptr<ceres::LossFunction> loss_from_options =
        options_.CreateLossFunction();
    ASSERT_NE(loss_from_options, nullptr);

    ceres::HuberLoss reference_loss(options_.thres_loss_function);

    // Compare the outputs of the two loss functions for a couple of inputs.
    double s_values[] = {0.01, 0.25, 1.0};
    for (double s : s_values) {
        double rho_from_options[3] = {0.0, 0.0, 0.0};
        double rho_reference[3]    = {0.0, 0.0, 0.0};

        loss_from_options->Evaluate(s, rho_from_options);
        reference_loss.Evaluate(s, rho_reference);

        EXPECT_DOUBLE_EQ(rho_from_options[0], rho_reference[0]);
        EXPECT_DOUBLE_EQ(rho_from_options[1], rho_reference[1]);
        EXPECT_DOUBLE_EQ(rho_from_options[2], rho_reference[2]);
    }
}

//------------------------------------------------------------------------------
// CreateLossFunction: boundary / exceptional thresholds
//------------------------------------------------------------------------------

TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunctionHandlesExtremeThresholds_9) {
    // Very small positive threshold (close to zero).
    options_.thres_loss_function = 1e-12;
    auto small_loss = options_.CreateLossFunction();
    ASSERT_NE(small_loss, nullptr);
    double rho_small[3] = {0.0, 0.0, 0.0};
    EXPECT_NO_THROW(small_loss->Evaluate(1.0, rho_small));

    // Negative threshold: even if this is not recommended, we only check
    // that the interface behaves in a defined way (no null, no throw).
    options_.thres_loss_function = -1.0;
    auto negative_loss = options_.CreateLossFunction();
    ASSERT_NE(negative_loss, nullptr);
    double rho_negative[3] = {0.0, 0.0, 0.0};
    EXPECT_NO_THROW(negative_loss->Evaluate(1.0, rho_negative));
}
