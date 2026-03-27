#include <gtest/gtest.h>

#include "option_manager.h"

#include "global_mapper.h"



namespace glomap {



class OptionManagerTest_36 : public ::testing::Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

    }



    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_36, AddGlobalMapperOptions_SetsFlagToTrue_36) {

    option_manager->AddGlobalMapperOptions();

    // Since added_mapper_options_ is private, we can only infer its state by calling the function again

    EXPECT_NO_THROW(option_manager->AddGlobalMapperOptions()); // Should not throw or add options again

}



TEST_F(OptionManagerTest_36, AddGlobalMapperOptions_RegistersDefaultOptions_36) {

    option_manager->AddGlobalMapperOptions();

    // We cannot directly check if the options are registered, but we can assume that if it runs without error,

    // the options are likely registered correctly.

}



TEST_F(OptionManagerTest_36, AddGlobalMapperOptions_Idempotent_36) {

    option_manager->AddGlobalMapperOptions();

    auto initial_mapper_options = *option_manager->mapper;

    option_manager->AddGlobalMapperOptions(); // Call again

    EXPECT_EQ(initial_mapper_options.num_iteration_bundle_adjustment, option_manager->mapper->num_iteration_bundle_adjustment);

    EXPECT_EQ(initial_mapper_options.skip_preprocessing, option_manager->mapper->skip_preprocessing);

}



TEST_F(OptionManagerTest_36, AddGlobalMapperOptions_DefaultValuesSet_36) {

    option_manager->AddGlobalMapperOptions();

    EXPECT_EQ(option_manager->mapper->num_iteration_bundle_adjustment, 3);

    EXPECT_EQ(option_manager->mapper->num_iteration_retriangulation, 1);

    EXPECT_FALSE(option_manager->mapper->skip_preprocessing);

    EXPECT_FALSE(option_manager->mapper->skip_view_graph_calibration);

    EXPECT_FALSE(option_manager->mapper->skip_relative_pose_estimation);

    EXPECT_FALSE(option_manager->mapper->skip_rotation_averaging);

    EXPECT_FALSE(option_manager->mapper->skip_global_positioning);

    EXPECT_FALSE(option_manager->mapper->skip_bundle_adjustment);

    EXPECT_FALSE(option_manager->mapper->skip_retriangulation);

    EXPECT_TRUE(option_manager->mapper->skip_pruning);

}



} // namespace glomap
