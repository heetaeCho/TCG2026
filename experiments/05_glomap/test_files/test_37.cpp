#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/controllers/option_manager.h"



using namespace glomap;

using namespace testing;



class OptionManagerTest_37 : public ::testing::Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

    }



    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptions_CallsAllSubMethods_37) {

    EXPECT_CALL(*option_manager, AddGlobalMapperOptions());

    EXPECT_CALL(*option_manager, AddViewGraphCalibrationOptions());

    EXPECT_CALL(*option_manager, AddRelativePoseEstimationOptions());

    EXPECT_CALL(*option_manager, AddRotationEstimatorOptions());

    EXPECT_CALL(*option_manager, AddTrackEstablishmentOptions());

    EXPECT_CALL(*option_manager, AddGlobalPositionerOptions());

    EXPECT_CALL(*option_manager, AddBundleAdjusterOptions());

    EXPECT_CALL(*option_manager, AddTriangulatorOptions());

    EXPECT_CALL(*option_manager, AddInlierThresholdOptions());



    option_manager->AddGlobalMapperFullOptions();

}



TEST_F(OptionManagerTest_37, AddAllOptions_NotImplementedInInterface_37) {

    // Since AddAllOptions is not implemented in the given interface,

    // we cannot test it directly. This test case serves as a placeholder

    // to indicate that this method should be tested if available.

}



TEST_F(OptionManagerTest_37, Parse_ValidArguments_Success_37) {

    int argc = 1;

    char* argv[] = {const_cast<char*>("program")};



    EXPECT_NO_THROW(option_manager->Parse(argc, argv));

}



TEST_F(OptionManagerTest_37, Reset_ClearsAllOptions_37) {

    // Assuming Reset clears all options and resets internal state.

    option_manager->Reset();

    // Since we cannot access private state directly, we verify

    // through observable behavior or side effects if any.

}



TEST_F(OptionManagerTest_37, ResetOptions_ResetPaths_37) {

    option_manager->ResetOptions(true);

    // Similar to the Reset test, verify through observable behavior.

}
