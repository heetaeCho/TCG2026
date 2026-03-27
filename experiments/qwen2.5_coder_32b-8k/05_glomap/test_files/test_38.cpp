#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/controllers/option_manager.h"

#include "TestProjects/glomap/glomap/controllers/global_mapper.h"



using namespace glomap;

using testing::Mock;



class OptionManagerTest_38 : public ::testing::Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

        global_mapper_options = std::make_shared<GlobalMapperOptions>();

        option_manager->mapper = global_mapper_options;

    }



    std::unique_ptr<OptionManager> option_manager;

    std::shared_ptr<GlobalMapperOptions> global_mapper_options;

};



TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptions_SetsFlagsToTrue_38) {

    option_manager->AddGlobalMapperResumeOptions();



    EXPECT_TRUE(global_mapper_options->skip_preprocessing);

    EXPECT_TRUE(global_mapper_options->skip_view_graph_calibration);

    EXPECT_TRUE(global_mapper_options->skip_relative_pose_estimation);

    EXPECT_TRUE(global_mapper_options->skip_rotation_averaging);

    EXPECT_TRUE(global_mapper_options->skip_track_establishment);

    EXPECT_TRUE(global_mapper_options->skip_retriangulation);

}



TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptions_AddsDefaultOptions_38) {

    option_manager->AddGlobalMapperResumeOptions();



    EXPECT_EQ(option_manager->mapper->num_iteration_bundle_adjustment, 3);

    EXPECT_EQ(option_manager->mapper->num_iteration_retriangulation, 1);

    EXPECT_FALSE(option_manager->mapper->skip_global_positioning);

    EXPECT_FALSE(option_manager->mapper->skip_bundle_adjustment);

    EXPECT_FALSE(option_manager->mapper->skip_pruning);

}



TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptions_Idempotent_38) {

    option_manager->AddGlobalMapperResumeOptions();

    int initial_ba_iterations = global_mapper_options->num_iteration_bundle_adjustment;



    option_manager->AddGlobalMapperResumeOptions();



    EXPECT_EQ(global_mapper_options->num_iteration_bundle_adjustment, initial_ba_iterations);

}



TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptions_SkipIfAlreadyAdded_38) {

    option_manager->added_mapper_options_ = true;

    int initial_ba_iterations = global_mapper_options->num_iteration_bundle_adjustment;



    option_manager->AddGlobalMapperResumeOptions();



    EXPECT_EQ(global_mapper_options->num_iteration_bundle_adjustment, initial_ba_iterations);

}
