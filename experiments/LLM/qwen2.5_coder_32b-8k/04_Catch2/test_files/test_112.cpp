#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::NotNull;



class ReporterConfigTest_112 : public ::testing::Test {

protected:

    const IConfig* mockFullConfig = nullptr; // Assuming this is a valid pointer in the context of the tests

    Detail::unique_ptr<IStream> mockStream = nullptr; // Assuming this is a valid unique_ptr in the context of the tests

    ColourMode defaultColourMode = ColourMode::Default;

    std::map<std::string, std::string> customOptions;



    ReporterConfig* config;



    void SetUp() override {

        config = new ReporterConfig(mockFullConfig, CATCH_MOVE(mockStream), defaultColourMode, CATCH_MOVE(customOptions));

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ReporterConfigTest_112, FullConfigReturnsCorrectPointer_112) {

    EXPECT_EQ(config->fullConfig(), mockFullConfig);

}



TEST_F(ReporterConfigTest_112, ColourModeReturnsDefault_112) {

    EXPECT_EQ(config->colourMode(), defaultColourMode);

}



TEST_F(ReporterConfigTest_112, CustomOptionsReturnsEmptyMap_112) {

    EXPECT_TRUE(config->customOptions().empty());

}



TEST_F(ReporterConfigTest_112, TakeStreamReturnsNonNullPointer_112) {

    EXPECT_THAT(config->takeStream(), NotNull());

}



// Boundary condition tests

TEST_F(ReporterConfigTest_112, FullConfigWithNullPointer_112) {

    ReporterConfig nullConfig(nullptr, CATCH_MOVE(mockStream), defaultColourMode, CATCH_MOVE(customOptions));

    EXPECT_EQ(nullConfig.fullConfig(), nullptr);

}



TEST_F(ReporterConfigTest_112, CustomOptionsWithNonEmptyMap_112) {

    std::map<std::string, std::string> nonEmptyCustomOptions = {{"key", "value"}};

    ReporterConfig customConfig(mockFullConfig, CATCH_MOVE(mockStream), defaultColourMode, CATCH_MOVE(nonEmptyCustomOptions));

    EXPECT_EQ(customConfig.customOptions().size(), 1);

    EXPECT_EQ(customConfig.customOptions().at("key"), "value");

}



// Exceptional or error cases

TEST_F(ReporterConfigTest_112, TakeStreamTwiceReturnsNullPointerOnSecondCall_112) {

    config->takeStream();

    EXPECT_THAT(config->takeStream(), ::testing::IsNull());

}
