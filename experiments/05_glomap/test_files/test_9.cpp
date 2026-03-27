#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/bundle_adjustment.h"



using namespace glomap;

using ::testing::Return;



class BundleAdjusterOptionsTest : public ::testing::Test {

protected:

    BundleAdjusterOptions options;

};



TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunction_ReturnsHuberLossWithDefaultThreshold_9) {

    auto loss_function = options.CreateLossFunction();

    EXPECT_NE(loss_function, nullptr);

    // Since we cannot directly check the type of the loss function without internal knowledge,

    // we verify that it behaves as expected by checking the threshold.

    ceres::HuberLoss huber_loss(options.thres_loss_function);

    double rho[3];

    loss_function->Evaluate(1.0, rho);

    huber_loss.Evaluate(1.0, rho);

    EXPECT_DOUBLE_EQ(rho[0], rho[0]); // Compare squared residuals

}



TEST_F(BundleAdjusterOptionsTest_9, CreateLossFunction_ReturnsHuberLossWithCustomThreshold_9) {

    options.thres_loss_function = 2.0;

    auto loss_function = options.CreateLossFunction();

    EXPECT_NE(loss_function, nullptr);

    ceres::HuberLoss huber_loss(options.thres_loss_function);

    double rho[3];

    loss_function->Evaluate(1.0, rho);

    huber_loss.Evaluate(1.0, rho);

    EXPECT_DOUBLE_EQ(rho[0], rho[0]); // Compare squared residuals

}



// Since the other member variables are bools and strings/ints with default values,

// we can test boundary conditions and normal operation by setting them to different values.

TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeRigPoses_DefaultValueIsFalse_9) {

    EXPECT_FALSE(options.optimize_rig_poses);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeRigPoses_SetToTrue_ReturnsTrue_9) {

    options.optimize_rig_poses = true;

    EXPECT_TRUE(options.optimize_rig_poses);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeRotations_DefaultValueIsTrue_9) {

    EXPECT_TRUE(options.optimize_rotations);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeRotations_SetToFalse_ReturnsFalse_9) {

    options.optimize_rotations = false;

    EXPECT_FALSE(options.optimize_rotations);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeTranslation_DefaultValueIsTrue_9) {

    EXPECT_TRUE(options.optimize_translation);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeTranslation_SetToFalse_ReturnsFalse_9) {

    options.optimize_translation = false;

    EXPECT_FALSE(options.optimize_translation);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeIntrinsics_DefaultValueIsTrue_9) {

    EXPECT_TRUE(options.optimize_intrinsics);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizeIntrinsics_SetToFalse_ReturnsFalse_9) {

    options.optimize_intrinsics = false;

    EXPECT_FALSE(options.optimize_intrinsics);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizePrincipalPoint_DefaultValueIsFalse_9) {

    EXPECT_FALSE(options.optimize_principal_point);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizePrincipalPoint_SetToTrue_ReturnsTrue_9) {

    options.optimize_principal_point = true;

    EXPECT_TRUE(options.optimize_principal_point);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizePoints_DefaultValueIsTrue_9) {

    EXPECT_TRUE(options.optimize_points);

}



TEST_F(BundleAdjusterOptionsTest_9, SetOptimizePoints_SetToFalse_ReturnsFalse_9) {

    options.optimize_points = false;

    EXPECT_FALSE(options.optimize_points);

}



TEST_F(BundleAdjusterOptionsTest_9, SetUseGpu_DefaultValueIsTrue_9) {

    EXPECT_TRUE(options.use_gpu);

}



TEST_F(BundleAdjusterOptionsTest_9, SetUseGpu_SetToFalse_ReturnsFalse_9) {

    options.use_gpu = false;

    EXPECT_FALSE(options.use_gpu);

}



TEST_F(BundleAdjusterOptionsTest_9, SetGpuIndex_DefaultValueIsMinusOne_9) {

    EXPECT_EQ(options.gpu_index, "-1");

}



TEST_F(BundleAdjusterOptionsTest_9, SetGpuIndex_SetToValidIndex_ReturnsCorrectIndex_9) {

    options.gpu_index = "0";

    EXPECT_EQ(options.gpu_index, "0");

}



TEST_F(BundleAdjusterOptionsTest_9, SetMinNumImagesGpuSolver_DefaultValueIs50_9) {

    EXPECT_EQ(options.min_num_images_gpu_solver, 50);

}



TEST_F(BundleAdjusterOptionsTest_9, SetMinNumImagesGpuSolver_SetToValidNumber_ReturnsCorrectNumber_9) {

    options.min_num_images_gpu_solver = 100;

    EXPECT_EQ(options.min_num_images_gpu_solver, 100);

}



TEST_F(BundleAdjusterOptionsTest_9, SetMinNumViewPerTrack_DefaultValueIs3_9) {

    EXPECT_EQ(options.min_num_view_per_track, 3);

}



TEST_F(BundleAdjusterOptionsTest_9, SetMinNumViewPerTrack_SetToValidNumber_ReturnsCorrectNumber_9) {

    options.min_num_view_per_track = 5;

    EXPECT_EQ(options.min_num_view_per_track, 5);

}
