#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"

#include "glomap/estimators/gravity_refinement.h"

#include "glomap/controllers/global_mapper.h"



using namespace glomap;



class OptionManagerTest_50 : public ::testing::Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

        option_manager->database_path = std::make_shared<std::string>();

        option_manager->image_path = std::make_shared<std::string>();

        option_manager->mapper = std::make_shared<GlobalMapperOptions>();

        option_manager->gravity_refiner = std::make_shared<GravityRefinerOptions>();

    }



    void TearDown() override {

        option_manager.reset();

    }



    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_50, ResetOptions_ResetPathsTrue_DatabasePathEmpty_50) {

    *option_manager->database_path = "test_db";

    option_manager->ResetOptions(true);

    EXPECT_EQ(*option_manager->database_path, "");

}



TEST_F(OptionManagerTest_50, ResetOptions_ResetPathsTrue_ImagePathEmpty_50) {

    *option_manager->image_path = "test_img";

    option_manager->ResetOptions(true);

    EXPECT_EQ(*option_manager->image_path, "");

}



TEST_F(OptionManagerTest_50, ResetOptions_ResetPathsFalse_DatabasePathUnchanged_50) {

    *option_manager->database_path = "test_db";

    option_manager->ResetOptions(false);

    EXPECT_EQ(*option_manager->database_path, "test_db");

}



TEST_F(OptionManagerTest_50, ResetOptions_ResetPathsFalse_ImagePathUnchanged_50) {

    *option_manager->image_path = "test_img";

    option_manager->ResetOptions(false);

    EXPECT_EQ(*option_manager->image_path, "test_img");

}



TEST_F(OptionManagerTest_50, ResetOptions_GlobalMapperReset_50) {

    option_manager->mapper->num_iteration_bundle_adjustment = 10;

    option_manager->ResetOptions(true);

    EXPECT_EQ(option_manager->mapper->num_iteration_bundle_adjustment, GlobalMapperOptions().num_iteration_bundle_adjustment);

}



TEST_F(OptionManagerTest_50, ResetOptions_GravityRefinerReset_50) {

    option_manager->gravity_refiner->max_outlier_ratio = 0.9;

    option_manager->ResetOptions(true);

    EXPECT_EQ(option_manager->gravity_refiner->max_outlier_ratio, GravityRefinerOptions().max_outlier_ratio);

}



TEST_F(OptionManagerTest_50, ResetOptions_BoundaryCondition_EmptyPaths_50) {

    *option_manager->database_path = "";

    *option_manager->image_path = "";

    option_manager->ResetOptions(true);

    EXPECT_EQ(*option_manager->database_path, "");

    EXPECT_EQ(*option_manager->image_path, "");

}



TEST_F(OptionManagerTest_50, ResetOptions_BoundaryCondition_DefaultValues_50) {

    GlobalMapperOptions default_mapper;

    GravityRefinerOptions default_gravity_refiner;



    option_manager->ResetOptions(true);

    EXPECT_EQ(*(option_manager->mapper), default_mapper);

    EXPECT_EQ(*(option_manager->gravity_refiner), default_gravity_refiner);

}
