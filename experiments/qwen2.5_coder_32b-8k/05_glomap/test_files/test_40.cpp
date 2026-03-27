#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/controllers/option_manager.h"

#include "glomap/estimators/view_graph_calibration.h"



using namespace glomap;

using ::testing::Test;



class OptionManagerTest_40 : public Test {

protected:

    void SetUp() override {

        mapper = std::make_shared<GlobalMapperOptions>();

        option_manager = std::make_unique<OptionManager>(false);

        option_manager->mapper = mapper;

    }



    std::shared_ptr<GlobalMapperOptions> mapper;

    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_40, AddViewGraphCalibrationOptions_SetsFlag_40) {

    EXPECT_FALSE(option_manager->added_view_graph_calibration_options_);

    option_manager->AddViewGraphCalibrationOptions();

    EXPECT_TRUE(option_manager->added_view_graph_calibration_options_);

}



TEST_F(OptionManagerTest_40, AddViewGraphCalibrationOptions_AddsDefaultOptions_40) {

    option_manager->AddViewGraphCalibrationOptions();



    EXPECT_DOUBLE_EQ(mapper->opt_vgcalib.thres_lower_ratio, 0.10000000000000001);

    EXPECT_DOUBLE_EQ(mapper->opt_vgcalib.thres_higher_ratio, 10);

    EXPECT_DOUBLE_EQ(mapper->opt_vgcalib.thres_two_view_error, 2.);

}



TEST_F(OptionManagerTest_40, AddViewGraphCalibrationOptions_Idempotent_40) {

    option_manager->AddViewGraphCalibrationOptions();

    double initial_lower_ratio = mapper->opt_vgcalib.thres_lower_ratio;

    

    // Call again

    option_manager->AddViewGraphCalibrationOptions();



    EXPECT_DOUBLE_EQ(mapper->opt_vgcalib.thres_lower_ratio, initial_lower_ratio);

}



TEST_F(OptionManagerTest_40, AddViewGraphCalibrationOptions_NoExternalInteraction_40) {

    // No external interactions to verify in this case as it's a local operation

    option_manager->AddViewGraphCalibrationOptions();

}
