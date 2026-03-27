#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



class ConfigTest_730 : public ::testing::Test {

protected:

    Catch::ConfigData configData;

    Catch::Config* config;



    void SetUp() override {

        config = new Catch::Config(configData);

    }



    void TearDown() override {

        delete config;

    }

};



TEST_F(ConfigTest_730, MinDuration_DefaultValue_730) {

    EXPECT_EQ(config->minDuration(), -1.0);

}



TEST_F(ConfigTest_730, ListTests_DefaultValue_730) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(ConfigTest_730, ListTags_DefaultValue_730) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(ConfigTest_730, ListReporters_DefaultValue_730) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_730, ListListeners_DefaultValue_730) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(ConfigTest_730, ShowHelp_DefaultValue_730) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_730, AllowThrows_DefaultValue_730) {

    EXPECT_TRUE(config->allowThrows());

}



TEST_F(ConfigTest_730, IncludeSuccessfulResults_DefaultValue_730) {

    EXPECT_FALSE(config->includeSuccessfulResults());

}



TEST_F(ConfigTest_730, WarnAboutMissingAssertions_DefaultValue_730) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_730, WarnAboutUnmatchedTestSpecs_DefaultValue_730) {

    EXPECT_FALSE(config->warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_730, ZeroTestsCountAsSuccess_DefaultValue_730) {

    EXPECT_FALSE(config->zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_730, ShowDurations_DefaultValue_730) {

    EXPECT_EQ(config->showDurations(), Catch::ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_730, RunOrder_DefaultValue_730) {

    EXPECT_EQ(config->runOrder(), Catch::TestRunOrder::Declared);

}



TEST_F(ConfigTest_730, RngSeed_DefaultValue_730) {

    // Assuming rngSeed generates a non-negative value by default

    EXPECT_GE(config->rngSeed(), 0u);

}



TEST_F(ConfigTest_730, ShardCount_DefaultValue_730) {

    EXPECT_EQ(config->shardCount(), 1u);

}



TEST_F(ConfigTest_730, ShardIndex_DefaultValue_730) {

    EXPECT_EQ(config->shardIndex(), 0u);

}



TEST_F(ConfigTest_730, DefaultColourMode_DefaultValue_730) {

    EXPECT_EQ(config->defaultColourMode(), Catch::ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_730, ShouldDebugBreak_DefaultValue_730) {

    EXPECT_FALSE(config->shouldDebugBreak());

}



TEST_F(ConfigTest_730, AbortAfter_DefaultValue_730) {

    EXPECT_EQ(config->abortAfter(), -1);

}



TEST_F(ConfigTest_730, ShowInvisibles_DefaultValue_730) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(ConfigTest_730, Verbosity_DefaultValue_730) {

    EXPECT_EQ(config->verbosity(), Catch::Verbosity::Normal);

}



TEST_F(ConfigTest_730, SkipBenchmarks_DefaultValue_730) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(ConfigTest_730, BenchmarkNoAnalysis_DefaultValue_730) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(ConfigTest_730, BenchmarkSamples_DefaultValue_730) {

    EXPECT_EQ(config->benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_730, BenchmarkConfidenceInterval_DefaultValue_730) {

    EXPECT_DOUBLE_EQ(config->benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_730, BenchmarkResamples_DefaultValue_730) {

    EXPECT_EQ(config->benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_730, BenchmarkWarmupTime_DefaultValue_730) {

    EXPECT_EQ(config->benchmarkWarmupTime().count(), 100);

}
