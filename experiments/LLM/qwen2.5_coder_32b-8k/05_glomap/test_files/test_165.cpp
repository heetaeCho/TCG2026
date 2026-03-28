#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/estimators/global_positioning.h"

#include <memory>



using namespace glomap;

using ::testing::Return;



class GlobalPositionerOptionsTest_165 : public ::testing::Test {

protected:

    GlobalPositionerOptions options;

};



TEST_F(GlobalPositionerOptionsTest_165, DefaultConstructorInitialization_165) {

    EXPECT_EQ(options.thres_loss_function, 1e-1);

    EXPECT_TRUE(options.generate_random_positions);

    EXPECT_TRUE(options.generate_random_points);

    EXPECT_TRUE(options.generate_scales);

    EXPECT_TRUE(options.optimize_positions);

    EXPECT_TRUE(options.optimize_scales);

    EXPECT_EQ(options.seed, 1u);

    EXPECT_EQ(options.constraint_type, ONLY_POINTS);

    EXPECT_EQ(options.constraint_reweight_scale, 1.);

}



TEST_F(GlobalPositionerOptionsTest_165, CreateLossFunction_ReturnsValidPointer_165) {

    auto loss_function = options.CreateLossFunction();

    EXPECT_NE(loss_function.get(), nullptr);

}
