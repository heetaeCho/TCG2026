#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_config.hpp"



using namespace Catch;

using ::testing::ElementsAre;



class ConfigTest_714 : public ::testing::Test {

protected:

    ConfigData configData;

    Config* config;



    void SetUp() override {

        config = new Config(configData);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ConfigTest_714, ListReportersFalseByDefault_714) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_714, ListReportersTrueWhenSet_714) {

    configData.listReporters = true;

    Config modifiedConfig(configData);

    EXPECT_TRUE(modifiedConfig.listReporters());

}



TEST_F(ConfigTest_714, GetReporterSpecsEmptyByDefault_714) {

    EXPECT_TRUE(config->getReporterSpecs().empty());

}



TEST_F(ConfigTest_714, GetTestsOrTagsEmptyByDefault_714) {

    EXPECT_TRUE(config->getTestsOrTags().empty());

}



TEST_F(ConfigTest_714, GetSectionsToRunEmptyByDefault_714) {

    EXPECT_TRUE(config->getSectionsToRun().empty());

}



TEST_F(ConfigTest_714, AllowThrowsTrueByDefault_714) {

    EXPECT_TRUE(config->allowThrows());

}



TEST_F(ConfigTest_714, ShowHelpFalseByDefault_714) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_714, IncludeSuccessfulResultsTrueByDefault_714) {

    EXPECT_TRUE(config->includeSuccessfulResults());

}



TEST_F(ConfigTest_714, WarnAboutMissingAssertionsFalseByDefault_714) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_714, WarnAboutUnmatchedTestSpecsFalseByDefault_714) {

    EXPECT_FALSE(config->warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_714, ZeroTestsCountAsSuccessFalseByDefault_714) {

    EXPECT_FALSE(config->zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_714, DefaultShowDurationsIsDefaultForReporter_714) {

    EXPECT_EQ(config->showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_714, MinDurationNegativeOneByDefault_714) {

    EXPECT_DOUBLE_EQ(config->minDuration(), -1.0);

}



TEST_F(ConfigTest_714, RunOrderDeclaredByDefault_714) {

    EXPECT_EQ(config->runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_714, DefaultColourModePlatformDefault_714) {

    EXPECT_EQ(config->defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_714, ShouldDebugBreakFalseByDefault_714) {

    EXPECT_FALSE(config->shouldDebugBreak());

}



TEST_F(ConfigTest_714, AbortAfterNegativeOneByDefault_714) {

    EXPECT_EQ(config->abortAfter(), -1);

}



TEST_F(ConfigTest_714, ShowInvisiblesFalseByDefault_714) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(ConfigTest_714, DefaultVerbosityIsNormal_714) {

    EXPECT_EQ(config->verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_714, SkipBenchmarksFalseByDefault_714) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(ConfigTest_714, BenchmarkNoAnalysisFalseByDefault_714) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(ConfigTest_714, BenchmarkSamplesDefaultValue_714) {

    EXPECT_EQ(config->benchmarkSamples(), 100);

}



TEST_F(ConfigTest_714, BenchmarkConfidenceIntervalDefaultValue_714) {

    EXPECT_DOUBLE_EQ(config->benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_714, BenchmarkResamplesDefaultValue_714) {

    EXPECT_EQ(config->benchmarkResamples(), 100000);

}



TEST_F(ConfigTest_714, BenchmarkWarmupTimeDefaultValue_714) {

    EXPECT_EQ(config->benchmarkWarmupTime().count(), 100);

}
