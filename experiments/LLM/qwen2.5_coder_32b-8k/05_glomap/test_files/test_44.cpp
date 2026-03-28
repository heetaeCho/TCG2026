#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "option_manager.h"

#include "global_positioning.h"



namespace glomap {



class OptionManagerTest_44 : public ::testing::Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

        mapper_options = std::make_shared<GlobalMapperOptions>();

        global_positioner_options = &mapper_options->opt_gp;

        option_manager->mapper = mapper_options;

    }



    std::unique_ptr<OptionManager> option_manager;

    std::shared_ptr<GlobalMapperOptions> mapper_options;

    GlobalPositionerOptions* global_positioner_options;

};



TEST_F(OptionManagerTest_44, AddGlobalPositionerOptions_AddsOptionsOnce_44) {

    // Act

    option_manager->AddGlobalPositionerOptions();

    option_manager->AddGlobalPositionerOptions();



    // Assert

    EXPECT_TRUE(option_manager->added_global_positioning_options_);

}



TEST_F(OptionManagerTest_44, AddGlobalPositionerOptions_RegistersDefaultOptions_44) {

    // Act

    option_manager->AddGlobalPositionerOptions();



    // Assert

    EXPECT_EQ(global_positioner_options->use_gpu, false);

    EXPECT_EQ(global_positioner_options->gpu_index, 0);

    EXPECT_EQ(global_positioner_options->optimize_positions, true);

    EXPECT_EQ(global_positioner_options->optimize_points, true);

    EXPECT_EQ(global_positioner_options->optimize_scales, true);

    EXPECT_DOUBLE_EQ(global_positioner_options->thres_loss_function, 0.1);

    EXPECT_EQ(global_positioner_options->solver_options.max_num_iterations, ceres::Solver::Options().max_num_iterations);

}



TEST_F(OptionManagerTest_44, AddGlobalPositionerOptions_DoesNotRegisterIfAlreadyAdded_44) {

    // Arrange

    option_manager->AddGlobalPositionerOptions();

    global_positioner_options->use_gpu = true;



    // Act

    option_manager->AddGlobalPositionerOptions();



    // Assert

    EXPECT_TRUE(option_manager->added_global_positioning_options_);

    EXPECT_EQ(global_positioner_options->use_gpu, true);

}



}  // namespace glomap
