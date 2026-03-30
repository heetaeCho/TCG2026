#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "gravity_refinement.h"



namespace glomap {



class GravityRefinerOptionsTest : public ::testing::Test {

protected:

    GravityRefinerOptions options;

};



TEST_F(GravityRefinerOptionsTest_23, CreateLossFunction_ReturnsNonNullPointer_23) {

    EXPECT_NE(options.CreateLossFunction(), nullptr);

}



TEST_F(GravityRefinerOptionsTest_23, CreateLossFunction_CorrectType_23) {

    auto loss_function = options.CreateLossFunction();

    EXPECT_TRUE(std::dynamic_pointer_cast<ceres::ArctanLoss>(loss_function) != nullptr);

}



TEST_F(GravityRefinerOptionsTest_23, CreateLossFunction_DefaultMaxGravityError_23) {

    double expected_scale = 1 - std::cos(DegToRad(1.0));

    auto loss_function = std::dynamic_pointer_cast<ceres::ArctanLoss>(options.CreateLossFunction());

    EXPECT_DOUBLE_EQ(loss_function->scale(), expected_scale);

}



TEST_F(GravityRefinerOptionsTest_23, CreateLossFunction_CustomMaxGravityError_23) {

    options.max_gravity_error = 2.0;

    double expected_scale = 1 - std::cos(DegToRad(2.0));

    auto loss_function = std::dynamic_pointer_cast<ceres::ArctanLoss>(options.CreateLossFunction());

    EXPECT_DOUBLE_EQ(loss_function->scale(), expected_scale);

}



TEST_F(GravityRefinerOptionsTest_23, CreateLossFunction_MaxGravityError_Zero_23) {

    options.max_gravity_error = 0.0;

    double expected_scale = 1 - std::cos(DegToRad(0.0));

    auto loss_function = std::dynamic_pointer_cast<ceres::ArctanLoss>(options.CreateLossFunction());

    EXPECT_DOUBLE_EQ(loss_function->scale(), expected_scale);

}



TEST_F(GravityRefinerOptionsTest_23, CreateLossFunction_MaxGravityError_Negative_23) {

    options.max_gravity_error = -1.0;

    double expected_scale = 1 - std::cos(DegToRad(-1.0));

    auto loss_function = std::dynamic_pointer_cast<ceres::ArctanLoss>(options.CreateLossFunction());

    EXPECT_DOUBLE_EQ(loss_function->scale(), expected_scale);

}



} // namespace glomap
