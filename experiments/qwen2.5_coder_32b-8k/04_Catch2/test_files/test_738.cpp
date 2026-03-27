#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_738 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        data.showInvisibles = false; // Default value

        config = Config(data);

    }

};



TEST_F(ConfigTest_738, ShowInvisibles_DefaultValue_738) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_738, ShowInvisibles_SetTrue_738) {

    data.showInvisibles = true;

    Config configWithInvisibles(data);

    EXPECT_TRUE(configWithInvisibles.showInvisibles());

}



TEST_F(ConfigTest_738, ListTests_DefaultValue_738) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_738, ListTags_DefaultValue_738) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_738, ListReporters_DefaultValue_738) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_738, ListListeners_DefaultValue_738) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_738, ShowHelp_DefaultValue_738) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_738, AllowThrows_DefaultValue_738) {

    EXPECT_TRUE(config.allowThrows()); // Assuming default is true

}



TEST_F(ConfigTest_738, Name_DefaultValue_738) {

    EXPECT_EQ("", config.name().c_str());

}



TEST_F(ConfigTest_738, IncludeSuccessfulResults_DefaultValue_738) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_738, WarnAboutMissingAssertions_DefaultValue_738) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_738, WarnAboutUnmatchedTestSpecs_DefaultValue_738) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_738, ZeroTestsCountAsSuccess_DefaultValue_738) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_738, ShowDurations_DefaultValue_738) {

    EXPECT_EQ(ShowDurations::DefaultForReporter, config.showDurations());

}



TEST_F(ConfigTest_738, MinDuration_DefaultValue_738) {

    EXPECT_EQ(-1, config.minDuration());

}



TEST_F(ConfigTest_738, RunOrder_DefaultValue_738) {

    EXPECT_EQ(TestRunOrder::Declared, config.runOrder());

}



TEST_F(ConfigTest_738, RngSeed_DefaultValue_738) {

    EXPECT_NE(0u, config.rngSeed()); // Assuming non-zero default

}



TEST_F(ConfigTest_738, ShardCount_DefaultValue_738) {

    EXPECT_EQ(1u, config.shardCount());

}



TEST_F(ConfigTest_738, ShardIndex_DefaultValue_738) {

    EXPECT_EQ(0u, config.shardIndex());

}



TEST_F(ConfigTest_738, DefaultColourMode_DefaultValue_738) {

    EXPECT_EQ(ColourMode::PlatformDefault, config.defaultColourMode());

}



TEST_F(ConfigTest_738, ShouldDebugBreak_DefaultValue_738) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_738, AbortAfter_DefaultValue_738) {

    EXPECT_EQ(-1, config.abortAfter());

}



TEST_F(ConfigTest_738, SkipBenchmarks_DefaultValue_738) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_738, BenchmarkNoAnalysis_DefaultValue_738) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_738, BenchmarkSamples_DefaultValue_738) {

    EXPECT_EQ(100u, config.benchmarkSamples());

}



TEST_F(ConfigTest_738, BenchmarkConfidenceInterval_DefaultValue_738) {

    EXPECT_DOUBLE_EQ(0.95, config.benchmarkConfidenceInterval());

}



TEST_F(ConfigTest_738, BenchmarkResamples_DefaultValue_738) {

    EXPECT_EQ(100000u, config.benchmarkResamples());

}



TEST_F(ConfigTest_738, BenchmarkWarmupTime_DefaultValue_738) {

    EXPECT_EQ(std::chrono::milliseconds{100}, config.benchmarkWarmupTime());

}



TEST_F(ConfigTest_738, GetTestsOrTags_EmptyByDefault_738) {

    EXPECT_TRUE(config.getTestsOrTags().empty());

}



TEST_F(ConfigTest_738, GetSectionsToRun_EmptyByDefault_738) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



TEST_F(ConfigTest_738, HasTestFilters_DefaultValue_738) {

    EXPECT_FALSE(config.hasTestFilters());

}
