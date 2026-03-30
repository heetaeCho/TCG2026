#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/estimators/bundle_adjustment.h"

#include <memory>



using namespace glomap;

using ::testing::Return;



class BundleAdjusterOptionsTest : public ::testing::Test {

protected:

    std::shared_ptr<BundleAdjusterOptions> options;



    void SetUp() override {

        options = std::make_shared<BundleAdjusterOptions>();

    }

};



TEST_F(BundleAdjusterOptionsTest_161, DefaultConstructorInitializesValuesCorrectly_161) {

    EXPECT_DOUBLE_EQ(options->thres_loss_function, 1.0);

    EXPECT_EQ(options->solver_options.max_num_iterations, 200);

    EXPECT_FALSE(options->optimize_rig_poses);

    EXPECT_TRUE(options->optimize_rotations);

    EXPECT_TRUE(options->optimize_translation);

    EXPECT_TRUE(options->optimize_intrinsics);

    EXPECT_FALSE(options->optimize_principal_point);

    EXPECT_TRUE(options->optimize_points);

    EXPECT_TRUE(options->use_gpu);

    EXPECT_EQ(options->gpu_index, "-1");

    EXPECT_EQ(options->min_num_images_gpu_solver, 50);

    EXPECT_EQ(options->min_num_view_per_track, 3);

}



TEST_F(BundleAdjusterOptionsTest_161, CreateLossFunctionReturnsNonNullPointer_161) {

    std::shared_ptr<ceres::LossFunction> loss_function = options->CreateLossFunction();

    EXPECT_NE(loss_function, nullptr);

}



// Assuming CreateLossFunction has observable behavior that can be tested

TEST_F(BundleAdjusterOptionsTest_161, CreateLossFunctionCreatesCorrectTypeOfLossFunction_161) {

    std::shared_ptr<ceres::LossFunction> loss_function = options->CreateLossFunction();

    // Assuming a specific type of LossFunction is created, e.g., ceres::HuberLoss

    EXPECT_TRUE(dynamic_cast<ceres::HuberLoss*>(loss_function.get()) != nullptr);

}



// Boundary condition test for thres_loss_function

TEST_F(BundleAdjusterOptionsTest_161, ThresLossFunctionBoundaryCondition_161) {

    options->thres_loss_function = 0.0;

    EXPECT_DOUBLE_EQ(options->thres_loss_function, 0.0);



    options->thres_loss_function = std::numeric_limits<double>::max();

    EXPECT_DOUBLE_EQ(options->thres_loss_function, std::numeric_limits<double>::max());

}



// Boundary condition test for solver_options.max_num_iterations

TEST_F(BundleAdjusterOptionsTest_161, SolverOptionsMaxNumIterationsBoundaryCondition_161) {

    options->solver_options.max_num_iterations = 0;

    EXPECT_EQ(options->solver_options.max_num_iterations, 0);



    options->solver_options.max_num_iterations = std::numeric_limits<int>::max();

    EXPECT_EQ(options->solver_options.max_num_iterations, std::numeric_limits<int>::max());

}



// Boundary condition test for min_num_images_gpu_solver

TEST_F(BundleAdjusterOptionsTest_161, MinNumImagesGPUSolverBoundaryCondition_161) {

    options->min_num_images_gpu_solver = 0;

    EXPECT_EQ(options->min_num_images_gpu_solver, 0);



    options->min_num_images_gpu_solver = std::numeric_limits<int>::max();

    EXPECT_EQ(options->min_num_images_gpu_solver, std::numeric_limits<int>::max());

}



// Boundary condition test for min_num_view_per_track

TEST_F(BundleAdjusterOptionsTest_161, MinNumViewPerTrackBoundaryCondition_161) {

    options->min_num_view_per_track = 0;

    EXPECT_EQ(options->min_num_view_per_track, 0);



    options->min_num_view_per_track = std::numeric_limits<int>::max();

    EXPECT_EQ(options->min_num_view_per_track, std::numeric_limits<int>::max());

}
