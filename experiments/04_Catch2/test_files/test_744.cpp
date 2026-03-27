#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData data;

    Config* config;



    void SetUp() override {

        config = new Config(data);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ConfigTest_744, BenchmarkResamples_DefaultValue_744) {

    EXPECT_EQ(config->benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_744, ListTests_DefaultValue_744) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(ConfigTest_744, ListTags_DefaultValue_744) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(ConfigTest_744, ListReporters_DefaultValue_744) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_744, ListListeners_DefaultValue_744) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(ConfigTest_744, ShowHelp_DefaultValue_744) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_744, AllowThrows_DefaultValue_744) {

    EXPECT_TRUE(config->allowThrows());

}



TEST_F(ConfigTest_744, IncludeSuccessfulResults_DefaultValue_744) {

    EXPECT_FALSE(config->includeSuccessfulResults());

}



TEST_F(ConfigTest_744, WarnAboutMissingAssertions_DefaultValue_744) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_744, WarnAboutUnmatchedTestSpecs_DefaultValue_744) {

    EXPECT_FALSE(config->warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_744, ZeroTestsCountAsSuccess_DefaultValue_744) {

    EXPECT_FALSE(config->zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_744, ShowDurations_DefaultValue_744) {

    EXPECT_EQ(config->showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_744, MinDuration_DefaultValue_744) {

    EXPECT_DOUBLE_EQ(config->minDuration(), -1.0);

}



TEST_F(ConfigTest_744, RunOrder_DefaultValue_744) {

    EXPECT_EQ(config->runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_744, RngSeed_DefaultValue_744) {

    EXPECT_NE(config->rngSeed(), 0u); // Assuming generateRandomSeed does not return 0

}



TEST_F(ConfigTest_744, ShardCount_DefaultValue_744) {

    EXPECT_EQ(config->shardCount(), 1u);

}



TEST_F(ConfigTest_744, ShardIndex_DefaultValue_744) {

    EXPECT_EQ(config->shardIndex(), 0u);

}



TEST_F(ConfigTest_744, DefaultColourMode_DefaultValue_744) {

    EXPECT_EQ(config->defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_744, ShouldDebugBreak_DefaultValue_744) {

    EXPECT_FALSE(config->shouldDebugBreak());

}



TEST_F(ConfigTest_744, AbortAfter_DefaultValue_744) {

    EXPECT_EQ(config->abortAfter(), -1);

}



TEST_F(ConfigTest_744, ShowInvisibles_DefaultValue_744) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(ConfigTest_744, Verbosity_DefaultValue_744) {

    EXPECT_EQ(config->verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_744, SkipBenchmarks_DefaultValue_744) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(ConfigTest_744, BenchmarkNoAnalysis_DefaultValue_744) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(ConfigTest_744, BenchmarkSamples_DefaultValue_744) {

    EXPECT_EQ(config->benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_744, BenchmarkConfidenceInterval_DefaultValue_744) {

    EXPECT_DOUBLE_EQ(config->benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_744, BenchmarkWarmupTime_DefaultValue_744) {

    EXPECT_EQ(config->benchmarkWarmupTime().count(), 100);

}



TEST_F(ConfigTest_744, GetTestsOrTags_EmptyByDefault_744) {

    EXPECT_TRUE(config->getTestsOrTags().empty());

}



TEST_F(ConfigTest_744, GetSectionsToRun_EmptyByDefault_744) {

    EXPECT_TRUE(config->getSectionsToRun().empty());

}



TEST_F(ConfigTest_744, GetReporterSpecs_EmptyByDefault_744) {

    EXPECT_TRUE(config->getReporterSpecs().empty());

}



TEST_F(ConfigTest_744, HasTestFilters_DefaultValue_744) {

    EXPECT_FALSE(config->hasTestFilters());

}
