#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/estimators/global_positioning.h"

#include <ceres/ceres.h>



using namespace glomap;

using namespace ceres;



TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunction_ReturnsHuberLoss_24) {

    GlobalPositionerOptions options;

    auto loss_function = options.CreateLossFunction();

    EXPECT_TRUE(dynamic_pointer_cast<HuberLoss>(loss_function) != nullptr);

}



TEST_F(GlobalPositionerOptionsTest_24, CreateLossFunction_HuberLossThresholdCorrect_24) {

    GlobalPositionerOptions options;

    auto loss_function = dynamic_pointer_cast<HuberLoss>(options.CreateLossFunction());

    ASSERT_NE(loss_function, nullptr);

    EXPECT_DOUBLE_EQ(loss_function->GetThreshold(), 0.10000000000000001);

}



TEST_F(GlobalPositionerOptionsTest_24, DefaultConstructor_SetsDefaultValues_24) {

    GlobalPositionerOptions options;

    EXPECT_TRUE(options.generate_random_positions);

    EXPECT_TRUE(options.generate_random_points);

    EXPECT_TRUE(options.generate_scales);

    EXPECT_TRUE(options.optimize_positions);

    EXPECT_TRUE(options.optimize_scales);

    EXPECT_EQ(options.seed, 1);

    EXPECT_EQ(options.constraint_type, ONLY_POINTS);

    EXPECT_DOUBLE_EQ(options.constraint_reweight_scale, 1.0);

}



TEST_F(GlobalPositionerOptionsTest_24, Constructor_InheritsBaseValues_24) {

    GlobalPositionerOptions options;

    EXPECT_DOUBLE_EQ(options.thres_loss_function, 0.10000000000000001);

}
