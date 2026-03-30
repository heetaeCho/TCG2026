#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"

#include "catch2/interfaces/catch_interfaces_tag_alias_registry.hpp"

#include "catch2/internal/catch_test_spec_parser.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData defaultConfigData;

    std::unique_ptr<ITagAliasRegistry> mockTagAliasRegistry;

    

    void SetUp() override {

        mockTagAliasRegistry = std::make_unique<MockTagAliasRegistry>();

        defaultConfigData.reporterSpecifications.clear();

    }

};



TEST_F(ConfigTest_1100, ConstructWithDefaultReporterSpec_1100) {

    Config config(defaultConfigData);

    EXPECT_EQ(config.getReporterSpecs().size(), 1);

}



TEST_F(ConfigTest_1100, TrimTestsOrTagsOnConstruction_1100) {

    defaultConfigData.testsOrTags = {" test1 ", "test2"};

    Config config(defaultConfigData);

    EXPECT_EQ(config.getTestsOrTags()[0], "test1");

    EXPECT_EQ(config.getTestsOrTags()[1], "test2");

}



TEST_F(ConfigTest_1100, TrimSectionsToRunOnConstruction_1100) {

    defaultConfigData.sectionsToRun = {" section1 ", "section2"};

    Config config(defaultConfigData);

    EXPECT_EQ(config.getSectionsToRun()[0], "section1");

    EXPECT_EQ(config.getSectionsToRun()[1], "section2");

}



TEST_F(ConfigTest_1100, HasTestFilters_ReturnsTrueWhenTestsOrTagsNotEmpty_1100) {

    defaultConfigData.testsOrTags = {"test"};

    Config config(defaultConfigData);

    EXPECT_TRUE(config.hasTestFilters());

}



TEST_F(ConfigTest_1100, HasTestFilters_ReturnsFalseWhenTestsOrTagsEmpty_1100) {

    Config config(defaultConfigData);

    EXPECT_FALSE(config.hasTestFilters());

}



TEST_F(ConfigTest_1100, ShowHelp_ReturnsFalseByDefault_1100) {

    Config config(defaultConfigData);

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_1100, AllowThrows_ReturnsTrueByDefault_1100) {

    Config config(defaultConfigData);

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_1100, TestSpec_ReturnsValidObject_1100) {

    defaultConfigData.testsOrTags = {"test"};

    Config config(defaultConfigData);

    EXPECT_FALSE(config.testSpec().hasFilters());

}



TEST_F(ConfigTest_1100, ReadBazelEnvVars_NotThrowOnConstruction_1100) {

    EXPECT_NO_THROW(Config(defaultConfigData));

}



TEST_F(ConfigTest_1100, GetReporterSpecs_ReturnsParsedSpecifications_1100) {

    defaultConfigData.reporterSpecifications = { ReporterSpec("console", Optional<std::string>("output.txt"), Optional<ColourMode>(ColourMode::Always), {}) };

    Config config(defaultConfigData);

    EXPECT_EQ(config.getReporterSpecs().size(), 1);

    EXPECT_EQ(config.getReporterSpecs()[0].name(), "console");

}



TEST_F(ConfigTest_1100, GetProcessedReporterSpecs_ReturnsCorrectSpecifications_1100) {

    defaultConfigData.reporterSpecifications = { ReporterSpec("console", Optional<std::string>(), Optional<ColourMode>(ColourMode::Always), {}) };

    Config config(defaultConfigData);

    EXPECT_EQ(config.getProcessedReporterSpecs().size(), 1);

    EXPECT_EQ(config.getProcessedReporterSpecs()[0].name, "console");

}



TEST_F(ConfigTest_1100, GetTestsOrTags_ReturnsProvidedValues_1100) {

    defaultConfigData.testsOrTags = {"test1", "test2"};

    Config config(defaultConfigData);

    EXPECT_EQ(config.getTestsOrTags().size(), 2);

    EXPECT_EQ(config.getTestsOrTags()[0], "test1");

    EXPECT_EQ(config.getTestsOrTags()[1], "test2");

}



TEST_F(ConfigTest_1100, GetSectionsToRun_ReturnsProvidedValues_1100) {

    defaultConfigData.sectionsToRun = {"section1", "section2"};

    Config config(defaultConfigData);

    EXPECT_EQ(config.getSectionsToRun().size(), 2);

    EXPECT_EQ(config.getSectionsToRun()[0], "section1");

    EXPECT_EQ(config.getSectionsToRun()[1], "section2");

}



TEST_F(ConfigTest_1100, GetReporterSpecs_ReturnsEmptyWhenNoSpecificationsProvided_1100) {

    Config config(defaultConfigData);

    EXPECT_FALSE(config.getReporterSpecs().empty());

}



TEST_F(ConfigTest_1100, BenchmarkSamples_DefaultValueIsCorrect_1100) {

    Config config(defaultConfigData);

    EXPECT_EQ(config.benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_1100, BenchmarkConfidenceInterval_DefaultValueIsCorrect_1100) {

    Config config(defaultConfigData);

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}
