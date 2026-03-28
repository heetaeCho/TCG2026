#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/controllers/option_manager.h"



using namespace glomap;

using ::testing::_;



class OptionManagerTest_41 : public ::testing::Test {

protected:

    void SetUp() override {

        mapper = std::make_shared<GlobalMapperOptions>();

        option_manager = std::make_unique<OptionManager>(false);

        option_manager->mapper = mapper;

    }



    std::shared_ptr<GlobalMapperOptions> mapper;

    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_41, AddRelativePoseEstimationOptions_AddsOptionOnce_41) {

    int initial_max_epipolar_error = mapper->opt_relpose.ransac_options.max_epipolar_error;



    option_manager->AddRelativePoseEstimationOptions();

    EXPECT_NE(initial_max_epipolar_error, mapper->opt_relpose.ransac_options.max_epipolar_error);



    int max_epipolar_error_after_first_call = mapper->opt_relpose.ransac_options.max_epipolar_error;

    

    option_manager->AddRelativePoseEstimationOptions();

    EXPECT_EQ(max_epipolar_error_after_first_call, mapper->opt_relpose.ransac_options.max_epipolar_error);

}



TEST_F(OptionManagerTest_41, AddRelativePoseEstimationOptions_DoesNotCrashIfMapperIsNullptr_41) {

    option_manager->mapper = nullptr;

    

    EXPECT_NO_THROW(option_manager->AddRelativePoseEstimationOptions());

}
