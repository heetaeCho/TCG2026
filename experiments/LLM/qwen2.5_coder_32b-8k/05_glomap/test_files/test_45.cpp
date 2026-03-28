#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "option_manager.h"

#include "global_mapper.h"

#include "bundle_adjustment.h"



using namespace glomap;

using ::testing::Eq;



class OptionManagerTest_45 : public ::testing::Test {

protected:

    void SetUp() override {

        mapper = std::make_shared<GlobalMapperOptions>();

        option_manager = std::make_unique<OptionManager>(false);

        option_manager->mapper = mapper;

    }



    std::shared_ptr<GlobalMapperOptions> mapper;

    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_45, AddBundleAdjusterOptions_SetsFlags_45) {

    EXPECT_FALSE(option_manager->added_bundle_adjustment_options_);

    option_manager->AddBundleAdjusterOptions();

    EXPECT_TRUE(option_manager->added_bundle_adjustment_options_);

}



TEST_F(OptionManagerTest_45, AddBundleAdjusterOptions_RegistersDefaultOptions_45) {

    option_manager->AddBundleAdjusterOptions();



    EXPECT_EQ(mapper->opt_ba.use_gpu, true);

    EXPECT_EQ(mapper->opt_ba.gpu_index, "-1");

    EXPECT_EQ(mapper->opt_ba.optimize_rig_poses, false);

    EXPECT_EQ(mapper->opt_ba.optimize_rotations, true);

    EXPECT_EQ(mapper->opt_ba.optimize_translation, true);

    EXPECT_EQ(mapper->opt_ba.optimize_intrinsics, true);

    EXPECT_EQ(mapper->opt_ba.optimize_principal_point, false);

    EXPECT_EQ(mapper->opt_ba.optimize_points, true);

    EXPECT_DOUBLE_EQ(mapper->opt_ba.thres_loss_function, 0.10000000000000001);

}



TEST_F(OptionManagerTest_45, AddBundleAdjusterOptions_Idempotent_45) {

    option_manager->AddBundleAdjusterOptions();

    auto initial_gpu_index = mapper->opt_ba.gpu_index;



    option_manager->AddBundleAdjusterOptions();

    EXPECT_EQ(mapper->opt_ba.gpu_index, initial_gpu_index);

}



TEST_F(OptionManagerTest_45, AddBundleAdjusterOptions_NoMapper_CrashesOrDoesNothing_45) {

    option_manager->mapper.reset();

    // Assuming this function either does nothing or crashes. Since we are treating it as a black box,

    // we can't test for the crash, but we can ensure no exception is thrown.

    EXPECT_NO_THROW(option_manager->AddBundleAdjusterOptions());

}
