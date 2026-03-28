#include <gtest/gtest.h>
#include <ceres/ceres.h>
#include <cmath>
#include "glomap/estimators/gravity_refinement.h"

namespace glomap {
namespace {

// Helper to convert degrees to radians (matching the likely implementation)
double DegToRad(double deg) {
    return deg * M_PI / 180.0;
}

class GravityRefinerOptionsTest_23 : public ::testing::Test {
protected:
    GravityRefinerOptions options_;
};

// Test that default construction sets expected default values
TEST_F(GravityRefinerOptionsTest_23, DefaultConstruction_23) {
    GravityRefinerOptions opts;
    EXPECT_DOUBLE_EQ(opts.max_outlier_ratio, 0.5);
    EXPECT_DOUBLE_EQ(opts.max_gravity_error, 1.0);
    EXPECT_EQ(opts.min_num_neighbors, 7);
}

// Test that CreateLossFunction returns a non-null pointer
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionReturnsNonNull_23) {
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);
}

// Test that CreateLossFunction returns ArctanLoss with correct parameter for default max_gravity_error
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionDefaultParameter_23) {
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    // Evaluate the loss function at a known point to verify behavior
    // ArctanLoss with parameter a evaluates as: rho[0] = a * atan2(s, a)
    // where s is the squared residual
    double rho[3];
    double s = 1.0;
    loss->Evaluate(s, rho);

    // The parameter should be 1 - cos(DegToRad(1.0))
    double expected_param = 1.0 - std::cos(DegToRad(1.0));

    // Create a reference ArctanLoss with the expected parameter
    ceres::ArctanLoss reference_loss(expected_param);
    double rho_ref[3];
    reference_loss.Evaluate(s, rho_ref);

    EXPECT_NEAR(rho[0], rho_ref[0], 1e-12);
    EXPECT_NEAR(rho[1], rho_ref[1], 1e-12);
    EXPECT_NEAR(rho[2], rho_ref[2], 1e-12);
}

// Test CreateLossFunction with modified max_gravity_error
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionCustomGravityError_23) {
    options_.max_gravity_error = 5.0;
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    double rho[3];
    double s = 2.0;
    loss->Evaluate(s, rho);

    double expected_param = 1.0 - std::cos(DegToRad(5.0));
    ceres::ArctanLoss reference_loss(expected_param);
    double rho_ref[3];
    reference_loss.Evaluate(s, rho_ref);

    EXPECT_NEAR(rho[0], rho_ref[0], 1e-12);
    EXPECT_NEAR(rho[1], rho_ref[1], 1e-12);
    EXPECT_NEAR(rho[2], rho_ref[2], 1e-12);
}

// Test CreateLossFunction with a very small max_gravity_error (boundary)
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionSmallGravityError_23) {
    options_.max_gravity_error = 0.001;
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    double rho[3];
    double s = 0.5;
    loss->Evaluate(s, rho);

    double expected_param = 1.0 - std::cos(DegToRad(0.001));
    ceres::ArctanLoss reference_loss(expected_param);
    double rho_ref[3];
    reference_loss.Evaluate(s, rho_ref);

    EXPECT_NEAR(rho[0], rho_ref[0], 1e-12);
    EXPECT_NEAR(rho[1], rho_ref[1], 1e-12);
    EXPECT_NEAR(rho[2], rho_ref[2], 1e-12);
}

// Test CreateLossFunction with a large max_gravity_error
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionLargeGravityError_23) {
    options_.max_gravity_error = 90.0;
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    double rho[3];
    double s = 10.0;
    loss->Evaluate(s, rho);

    double expected_param = 1.0 - std::cos(DegToRad(90.0));
    ceres::ArctanLoss reference_loss(expected_param);
    double rho_ref[3];
    reference_loss.Evaluate(s, rho_ref);

    EXPECT_NEAR(rho[0], rho_ref[0], 1e-10);
    EXPECT_NEAR(rho[1], rho_ref[1], 1e-10);
    EXPECT_NEAR(rho[2], rho_ref[2], 1e-10);
}

// Test that calling CreateLossFunction multiple times returns independent instances
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionReturnsIndependentInstances_23) {
    auto loss1 = options_.CreateLossFunction();
    auto loss2 = options_.CreateLossFunction();
    ASSERT_NE(loss1, nullptr);
    ASSERT_NE(loss2, nullptr);
    EXPECT_NE(loss1.get(), loss2.get());
}

// Test that modifying max_gravity_error changes the loss function behavior
TEST_F(GravityRefinerOptionsTest_23, DifferentGravityErrorProducesDifferentLoss_23) {
    options_.max_gravity_error = 1.0;
    auto loss1 = options_.CreateLossFunction();

    options_.max_gravity_error = 10.0;
    auto loss2 = options_.CreateLossFunction();

    double rho1[3], rho2[3];
    double s = 5.0;
    loss1->Evaluate(s, rho1);
    loss2->Evaluate(s, rho2);

    // Different parameters should produce different outputs
    EXPECT_NE(rho1[0], rho2[0]);
}

// Test with max_gravity_error = 0 (boundary: cos(0) = 1, so param = 0)
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionZeroGravityError_23) {
    options_.max_gravity_error = 0.0;
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    double rho[3];
    double s = 1.0;
    loss->Evaluate(s, rho);

    double expected_param = 1.0 - std::cos(DegToRad(0.0));  // = 0
    ceres::ArctanLoss reference_loss(expected_param);
    double rho_ref[3];
    reference_loss.Evaluate(s, rho_ref);

    EXPECT_NEAR(rho[0], rho_ref[0], 1e-12);
}

// Test that member fields can be set and read
TEST_F(GravityRefinerOptionsTest_23, MemberFieldsAreAccessible_23) {
    options_.max_outlier_ratio = 0.3;
    EXPECT_DOUBLE_EQ(options_.max_outlier_ratio, 0.3);

    options_.max_gravity_error = 2.5;
    EXPECT_DOUBLE_EQ(options_.max_gravity_error, 2.5);

    options_.min_num_neighbors = 15;
    EXPECT_EQ(options_.min_num_neighbors, 15);
}

// Test loss function evaluation at zero squared residual
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionEvaluateAtZero_23) {
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    double rho[3];
    loss->Evaluate(0.0, rho);

    double expected_param = 1.0 - std::cos(DegToRad(1.0));
    ceres::ArctanLoss reference_loss(expected_param);
    double rho_ref[3];
    reference_loss.Evaluate(0.0, rho_ref);

    EXPECT_NEAR(rho[0], rho_ref[0], 1e-12);
    EXPECT_NEAR(rho[1], rho_ref[1], 1e-12);
    EXPECT_NEAR(rho[2], rho_ref[2], 1e-12);
}

// Test with max_gravity_error = 180 (boundary: cos(pi) = -1, param = 2)
TEST_F(GravityRefinerOptionsTest_23, CreateLossFunctionMaxAngle180_23) {
    options_.max_gravity_error = 180.0;
    auto loss = options_.CreateLossFunction();
    ASSERT_NE(loss, nullptr);

    double rho[3];
    double s = 1.0;
    loss->Evaluate(s, rho);

    double expected_param = 1.0 - std::cos(DegToRad(180.0));  // = 2.0
    ceres::ArctanLoss reference_loss(expected_param);
    double rho_ref[3];
    reference_loss.Evaluate(s, rho_ref);

    EXPECT_NEAR(rho[0], rho_ref[0], 1e-10);
    EXPECT_NEAR(rho[1], rho_ref[1], 1e-10);
    EXPECT_NEAR(rho[2], rho_ref[2], 1e-10);
}

}  // namespace
}  // namespace glomap
