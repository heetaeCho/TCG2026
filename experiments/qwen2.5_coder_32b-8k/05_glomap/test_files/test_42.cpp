#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/glomap/glomap/controllers/option_manager.h"



using namespace glomap;

using ::testing::Test;



class OptionManagerTest_42 : public Test {

protected:

    std::unique_ptr<OptionManager> option_manager;



    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

    }

};



TEST_F(OptionManagerTest_42, AddRotationEstimatorOptionsOnce_42) {

    // Call the method for the first time

    option_manager->AddRotationEstimatorOptions();



    // Verify that added_rotation_averaging_options_ is set to true

    EXPECT_TRUE(option_manager->added_rotation_averaging_options_);

}



TEST_F(OptionManagerTest_42, AddRotationEstimatorOptionsTwice_42) {

    // Call the method for the first time

    option_manager->AddRotationEstimatorOptions();



    // Call the method again to ensure it doesn't change state

    option_manager->AddRotationEstimatorOptions();



    // Verify that added_rotation_averaging_options_ remains true

    EXPECT_TRUE(option_manager->added_rotation_averaging_options_);

}



TEST_F(OptionManagerTest_42, AddRotationEstimatorOptionsInitialValue_42) {

    // Initial state should be false before any method calls

    EXPECT_FALSE(option_manager->added_rotation_averaging_options_);

}
