#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        data.listTests = false;

        data.listTags = false;

        data.listReporters = false;

        data.listListeners = false;

        config = Config(data);

    }

};



TEST_F(ConfigTest_712, ListTests_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_712, ListTags_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_712, ListReporters_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_712, ListListeners_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_712, SetListTests_ReturnsTrue_712) {

    data.listTests = true;

    Config configWithTests(data);

    EXPECT_TRUE(configWithTests.listTests());

}



TEST_F(ConfigTest_712, GetReporterSpecs_ReturnsEmptyVectorByDefault_712) {

    EXPECT_EQ(config.getReporterSpecs().size(), 0);

}



TEST_F(ConfigTest_712, GetProcessedReporterSpecs_ReturnsEmptyVectorByDefault_712) {

    EXPECT_EQ(config.getProcessedReporterSpecs().size(), 0);

}



TEST_F(ConfigTest_712, GetTestsOrTags_ReturnsEmptyVectorByDefault_712) {

    EXPECT_EQ(config.getTestsOrTags().size(), 0);

}



TEST_F(ConfigTest_712, GetSectionsToRun_ReturnsEmptyVectorByDefault_712) {

    EXPECT_EQ(config.getSectionsToRun().size(), 0);

}



TEST_F(ConfigTest_712, HasTestFilters_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.hasTestFilters());

}



TEST_F(ConfigTest_712, ShowHelp_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_712, AllowThrows_ReturnsTrueByDefault_712) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_712, Name_ReturnsEmptyStringByDefault_712) {

    EXPECT_EQ(config.name().toString(), "");

}



TEST_F(ConfigTest_712, IncludeSuccessfulResults_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_712, WarnAboutMissingAssertions_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_712, WarnAboutUnmatchedTestSpecs_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_712, ZeroTestsCountAsSuccess_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_712, ShowDurations_ReturnsDefaultForReporterByDefault_712) {

    EXPECT_EQ(config.showDurations(), ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_712, MinDuration_ReturnsNegativeOneByDefault_712) {

    EXPECT_DOUBLE_EQ(config.minDuration(), -1.0);

}



TEST_F(ConfigTest_712, RunOrder_ReturnsDeclaredByDefault_712) {

    EXPECT_EQ(config.runOrder(), TestRunOrder::Declared);

}



TEST_F(ConfigTest_712, ShardCount_ReturnsOneByDefault_712) {

    EXPECT_EQ(config.shardCount(), 1U);

}



TEST_F(ConfigTest_712, ShardIndex_ReturnsZeroByDefault_712) {

    EXPECT_EQ(config.shardIndex(), 0U);

}



TEST_F(ConfigTest_712, DefaultColourMode_ReturnsPlatformDefaultByDefault_712) {

    EXPECT_EQ(config.defaultColourMode(), ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_712, ShouldDebugBreak_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.shouldDebugBreak());

}



TEST_F(ConfigTest_712, AbortAfter_ReturnsNegativeOneByDefault_712) {

    EXPECT_EQ(config.abortAfter(), -1);

}



TEST_F(ConfigTest_712, ShowInvisibles_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.showInvisibles());

}



TEST_F(ConfigTest_712, Verbosity_ReturnsNormalByDefault_712) {

    EXPECT_EQ(config.verbosity(), Verbosity::Normal);

}



TEST_F(ConfigTest_712, SkipBenchmarks_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_712, BenchmarkNoAnalysis_ReturnsFalseByDefault_712) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_712, BenchmarkSamples_ReturnsHundredByDefault_712) {

    EXPECT_EQ(config.benchmarkSamples(), 100U);

}



TEST_F(ConfigTest_712, BenchmarkConfidenceInterval_Returns95PercentByDefault_712) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.94999999999999996);

}



TEST_F(ConfigTest_712, BenchmarkResamples_ReturnsHundredThousandByDefault_712) {

    EXPECT_EQ(config.benchmarkResamples(), 100000U);

}



TEST_F(ConfigTest_712, BenchmarkWarmupTime_ReturnsOneHundredMillisecondsByDefault_712) {

    EXPECT_EQ(config.benchmarkWarmupTime().count(), 100);

}
