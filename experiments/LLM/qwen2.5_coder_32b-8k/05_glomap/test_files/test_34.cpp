#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "option_manager.h"



using namespace glomap;



class OptionManagerTest_34 : public ::testing::Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

    }



    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_34, AddDatabaseOptions_AddsOptionOnce_34) {

    EXPECT_EQ(option_manager->added_database_options_, false);

    option_manager->AddDatabaseOptions();

    EXPECT_EQ(option_manager->added_database_options_, true);



    // Call again to ensure it doesn't add twice

    option_manager->AddDatabaseOptions();

    EXPECT_EQ(option_manager->added_database_options_, true);

}



TEST_F(OptionManagerTest_34, AddDatabaseOptions_DoesNotModifyImagePath_34) {

    auto original_image_path = option_manager->image_path;

    option_manager->AddDatabaseOptions();

    EXPECT_EQ(option_manager->image_path, original_image_path);

}



TEST_F(OptionManagerTest_34, AddDatabaseOptions_DoesNotModifyMapper_34) {

    auto original_mapper = option_manager->mapper;

    option_manager->AddDatabaseOptions();

    EXPECT_EQ(option_manager->mapper, original_mapper);

}



TEST_F(OptionManagerTest_34, AddDatabaseOptions_DoesNotModifyGravityRefiner_34) {

    auto original_gravity_refiner = option_manager->gravity_refiner;

    option_manager->AddDatabaseOptions();

    EXPECT_EQ(option_manager->gravity_refiner, original_gravity_refiner);

}
