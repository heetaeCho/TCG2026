#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



using namespace Catch;



class ConfigTest_717 : public ::testing::Test {

protected:

    ConfigData data;

    Config config;



    void SetUp() override {

        // Initialize with default values or specific values if needed

        config = Config(data);

    }

};



TEST_F(ConfigTest_717, GetSectionsToRun_ReturnsEmptyVector_717) {

    EXPECT_TRUE(config.getSectionsToRun().empty());

}



TEST_F(ConfigTest_717, ListTests_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.listTests());

}



TEST_F(ConfigTest_717, ListTags_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.listTags());

}



TEST_F(ConfigTest_717, ListReporters_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.listReporters());

}



TEST_F(ConfigTest_717, ListListeners_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.listListeners());

}



TEST_F(ConfigTest_717, ShowHelp_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.showHelp());

}



TEST_F(ConfigTest_717, AllowThrows_DefaultValueIsTrue_717) {

    EXPECT_TRUE(config.allowThrows());

}



TEST_F(ConfigTest_717, IncludeSuccessfulResults_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.includeSuccessfulResults());

}



TEST_F(ConfigTest_717, WarnAboutMissingAssertions_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.warnAboutMissingAssertions());

}



TEST_F(ConfigTest_717, WarnAboutUnmatchedTestSpecs_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_717, ZeroTestsCountAsSuccess_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_717, ShowDurations_DefaultValueIsDefaultForReporter_717) {

    EXPECT_EQ(ShowDurations::DefaultForReporter, config.showDurations());

}



TEST_F(ConfigTest_717, MinDuration_DefaultValueIsNegativeOne_717) {

    EXPECT_DOUBLE_EQ(-1.0, config.minDuration());

}



TEST_F(ConfigTest_717, RunOrder_DefaultValueIsDeclared_717) {

    EXPECT_EQ(TestRunOrder::Declared, config.runOrder());

}



TEST_F(ConfigTest_717, ShardCount_DefaultValueIsOne_717) {

    EXPECT_EQ(1u, config.shardCount());

}



TEST_F(ConfigTest_717, ShardIndex_DefaultValueIsZero_717) {

    EXPECT_EQ(0u, config.shardIndex());

}



TEST_F(ConfigTest_717, SkipBenchmarks_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.skipBenchmarks());

}



TEST_F(ConfigTest_717, BenchmarkNoAnalysis_DefaultValueIsFalse_717) {

    EXPECT_FALSE(config.benchmarkNoAnalysis());

}



TEST_F(ConfigTest_717, BenchmarkSamples_DefaultValueIsHundred_717) {

    EXPECT_EQ(100u, config.benchmarkSamples());

}



TEST_F(ConfigTest_717, BenchmarkConfidenceInterval_DefaultValueIsApprox95Percent_717) {

    EXPECT_DOUBLE_EQ(0.95, config.benchmarkConfidenceInterval());

}



TEST_F(ConfigTest_717, BenchmarkResamples_DefaultValueIsHundredThousand_717) {

    EXPECT_EQ(100000u, config.benchmarkResamples());

}
