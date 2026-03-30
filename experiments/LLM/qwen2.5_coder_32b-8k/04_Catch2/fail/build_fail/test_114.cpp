#include <gtest/gtest.h>

#include "catch_interfaces_reporter.hpp"

#include <map>



using namespace Catch;



class ReporterConfigTest_114 : public ::testing::Test {

protected:

    std::map<std::string, std::string> customOptions;

    ReporterConfig* reporterConfig;



    virtual void SetUp() {

        customOptions = {{"option1", "value1"}, {"option2", "value2"}};

        reporterConfig = new ReporterConfig(nullptr, nullptr, ColourMode::None, customOptions);

    }



    virtual void TearDown() {

        delete reporterConfig;

    }

};



TEST_F(ReporterConfigTest_114, CustomOptionsReturnsCorrectMap_114) {

    const std::map<std::string, std::string>& returnedOptions = reporterConfig->customOptions();

    EXPECT_EQ(returnedOptions, customOptions);

}



TEST_F(ReporterConfigTest_114, CustomOptionsEmptyMap_114) {

    ReporterConfig emptyConfig(nullptr, nullptr, ColourMode::None, {});

    const std::map<std::string, std::string>& returnedOptions = emptyConfig.customOptions();

    EXPECT_TRUE(returnedOptions.empty());

}



TEST_F(ReporterConfigTest_114, CustomOptionsSingleElementMap_114) {

    std::map<std::string, std::string> singleOption = {{"option1", "value1"}};

    ReporterConfig singleConfig(nullptr, nullptr, ColourMode::None, singleOption);

    const std::map<std::string, std::string>& returnedOptions = singleConfig.customOptions();

    EXPECT_EQ(returnedOptions, singleOption);

}



TEST_F(ReporterConfigTest_114, CustomOptionsLargeMap_114) {

    std::map<std::string, std::string> largeOptions;

    for (int i = 0; i < 100; ++i) {

        largeOptions["option" + std::to_string(i)] = "value" + std::to_string(i);

    }

    ReporterConfig largeConfig(nullptr, nullptr, ColourMode::None, largeOptions);

    const std::map<std::string, std::string>& returnedOptions = largeConfig.customOptions();

    EXPECT_EQ(returnedOptions, largeOptions);

}
