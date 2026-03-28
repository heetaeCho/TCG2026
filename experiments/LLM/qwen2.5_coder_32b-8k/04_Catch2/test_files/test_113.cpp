#include <gtest/gtest.h>

#include "catch_interfaces_reporter.hpp"



using namespace Catch;



class ReporterConfigTest_113 : public ::testing::Test {

protected:

    Detail::unique_ptr<IStream> stream = nullptr;

    IConfig const* fullConfig = nullptr;

    ColourMode colourMode = ColourMode::None;

    std::map<std::string, std::string> customOptions;



    ReporterConfig config{fullConfig, CATCH_MOVE(stream), colourMode, CATCH_MOVE(customOptions)};

};



TEST_F(ReporterConfigTest_113, DefaultConstructorInitializesCorrectly_113) {

    EXPECT_EQ(config.colourMode(), ColourMode::None);

}



TEST_F(ReporterConfigTest_113, FullConfigReturnsProvidedValue_113) {

    EXPECT_EQ(config.fullConfig(), fullConfig);

}



TEST_F(ReporterConfigTest_113, CustomOptionsReturnsProvidedValue_113) {

    EXPECT_EQ(config.customOptions().size(), customOptions.size());

}



TEST_F(ReporterConfigTest_113, TakeStreamTransfersOwnership_113) {

    auto streamPtr = config.takeStream();

    EXPECT_EQ(stream.get(), nullptr);

    EXPECT_NE(streamPtr.get(), nullptr);

}



TEST_F(ReporterConfigTest_113, MoveConstructorPreservesState_113) {

    ReporterConfig movedConfig{CATCH_MOVE(config)};

    EXPECT_EQ(movedConfig.colourMode(), ColourMode::None);

    EXPECT_EQ(movedConfig.fullConfig(), fullConfig);

    EXPECT_EQ(movedConfig.customOptions().size(), customOptions.size());

}



TEST_F(ReporterConfigTest_113, MoveAssignmentOperatorPreservesState_113) {

    ReporterConfig newConfig{fullConfig, CATCH_MOVE(stream), colourMode, CATCH_MOVE(customOptions)};

    newConfig = CATCH_MOVE(config);

    EXPECT_EQ(newConfig.colourMode(), ColourMode::None);

    EXPECT_EQ(newConfig.fullConfig(), fullConfig);

    EXPECT_EQ(newConfig.customOptions().size(), customOptions.size());

}



TEST_F(ReporterConfigTest_113, ConstMethodsDoNotModifyState_113) {

    auto constColourMode = config.colourMode();

    auto constFullConfig = config.fullConfig();

    auto constCustomOptions = config.customOptions();



    EXPECT_EQ(config.colourMode(), constColourMode);

    EXPECT_EQ(config.fullConfig(), constFullConfig);

    EXPECT_EQ(config.customOptions(), constCustomOptions);

}
