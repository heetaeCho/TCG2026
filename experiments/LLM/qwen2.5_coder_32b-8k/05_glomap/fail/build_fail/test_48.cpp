#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/controllers/option_manager.h"

#include "glomap/estimators/gravity_refinement.h"



using namespace glomap;

using ::testing::_;



class OptionManagerTest_48 : public ::testing::Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

        gravity_refiner_options = std::make_shared<GravityRefinerOptions>();

        option_manager->gravity_refiner = gravity_refiner_options;

    }



    std::unique_ptr<OptionManager> option_manager;

    std::shared_ptr<GravityRefinerOptions> gravity_refiner_options;

};



TEST_F(OptionManagerTest_48, AddGravityRefinerOptions_AddsCorrectly_48) {

    EXPECT_FALSE(option_manager->added_gravity_refiner_options_);

    

    option_manager->AddGravityRefinerOptions();

    

    EXPECT_TRUE(option_manager->added_gravity_refiner_options_);

}



TEST_F(OptionManagerTest_48, AddGravityRefinerOptions_Idempotent_48) {

    option_manager->AddGravityRefinerOptions();

    EXPECT_TRUE(option_manager->added_gravity_refiner_options_);



    // Call again to check idempotency

    option_manager->AddGravityRefinerOptions();

    EXPECT_TRUE(option_manager->added_gravity_refiner_options_);

}



TEST_F(OptionManagerTest_48, AddGravityRefinerOptions_DefaultValuesSet_48) {

    option_manager->AddGravityRefinerOptions();



    EXPECT_DOUBLE_EQ(gravity_refiner_options->max_outlier_ratio, 0.5);

    EXPECT_DOUBLE_EQ(gravity_refiner_options->max_gravity_error, 1.);

    EXPECT_EQ(gravity_refiner_options->min_num_neighbors, 7);

}



TEST_F(OptionManagerTest_48, AddGravityRefinerOptions_MultipleCallsNoChange_48) {

    option_manager->AddGravityRefinerOptions();

    double initial_max_outlier_ratio = gravity_refiner_options->max_outlier_ratio;

    double initial_max_gravity_error = gravity_refiner_options->max_gravity_error;

    int initial_min_num_neighbors = gravity_refiner_options->min_num_neighbors;



    // Call again to check no change in values

    option_manager->AddGravityRefinerOptions();

    

    EXPECT_DOUBLE_EQ(gravity_refiner_options->max_outlier_ratio, initial_max_outlier_ratio);

    EXPECT_DOUBLE_EQ(gravity_refiner_options->max_gravity_error, initial_max_gravity_error);

    EXPECT_EQ(gravity_refiner_options->min_num_neighbors, initial_min_num_neighbors);

}
