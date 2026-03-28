#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_config.hpp"



namespace Catch {

    class MockIConfig : public IConfig {

    public:

        MOCK_CONST_METHOD0(listTests, bool());

        MOCK_CONST_METHOD0(listTags, bool());

        MOCK_CONST_METHOD0(listReporters, bool());

        MOCK_CONST_METHOD0(listListeners, bool());

        MOCK_CONST_METHOD0(getReporterSpecs, const std::vector<ReporterSpec>&());

        MOCK_CONST_METHOD0(getProcessedReporterSpecs, const std::vector<ProcessedReporterSpec>&());

        MOCK_CONST_METHOD0(getTestsOrTags, const std::vector<std::string>&());

        MOCK_CONST_METHOD0(getSectionsToRun, const std::vector<std::string>&());

        MOCK_CONST_METHOD0(testSpec, const TestSpec&());

        MOCK_CONST_METHOD0(hasTestFilters, bool());

        MOCK_CONST_METHOD0(showHelp, bool());

        MOCK_CONST_METHOD0(allowThrows, bool());

        MOCK_CONST_METHOD0(name, StringRef());

        MOCK_CONST_METHOD0(includeSuccessfulResults, bool());

        MOCK_CONST_METHOD0(warnAboutMissingAssertions, bool());

        MOCK_CONST_METHOD0(warnAboutUnmatchedTestSpecs, bool());

        MOCK_CONST_METHOD0(zeroTestsCountAsSuccess, bool());

        MOCK_CONST_METHOD0(showDurations, ShowDurations());

        MOCK_CONST_METHOD0(minDuration, double());

        MOCK_CONST_METHOD0(runOrder, TestRunOrder());

        MOCK_CONST_METHOD0(rngSeed, uint32_t());

        MOCK_CONST_METHOD0(shardCount, unsigned int());

        MOCK_CONST_METHOD0(shardIndex, unsigned int());

        MOCK_CONST_METHOD0(defaultColourMode, ColourMode());

        MOCK_CONST_METHOD0(shouldDebugBreak, bool());

        MOCK_CONST_METHOD0(abortAfter, int());

        MOCK_CONST_METHOD0(showInvisibles, bool());

        MOCK_CONST_METHOD0(verbosity, Verbosity());

        MOCK_CONST_METHOD0(skipBenchmarks, bool());

        MOCK_CONST_METHOD0(benchmarkNoAnalysis, bool());

        MOCK_CONST_METHOD0(benchmarkSamples, unsigned int());

        MOCK_CONST_METHOD0(benchmarkConfidenceInterval, double());

        MOCK_CONST_METHOD0(benchmarkResamples, unsigned int());

        MOCK_CONST_METHOD0(benchmarkWarmupTime, std::chrono::milliseconds());

    };

}



class ConfigTest : public ::testing::Test {

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



TEST_F(ConfigTest_716, GetTestsOrTags_ReturnsEmptyVector_716) {

    EXPECT_TRUE(config->getTestsOrTags().empty());

}



TEST_F(ConfigTest_716, GetTestsOrTags_ReturnsProvidedValues_716) {

    configData.testsOrTags = {"test1", "test2"};

    Catch::Config configWithTests(configData);

    EXPECT_EQ(configWithTests.getTestsOrTags(), std::vector<std::string>{"test1", "test2"});

}



TEST_F(ConfigTest_716, GetSectionsToRun_ReturnsEmptyVector_716) {

    EXPECT_TRUE(config->getSectionsToRun().empty());

}



TEST_F(ConfigTest_716, ListTests_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->listTests());

}



TEST_F(ConfigTest_716, ListTags_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->listTags());

}



TEST_F(ConfigTest_716, ListReporters_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->listReporters());

}



TEST_F(ConfigTest_716, ListListeners_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->listListeners());

}



TEST_F(ConfigTest_716, ShowHelp_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->showHelp());

}



TEST_F(ConfigTest_716, AllowThrows_ReturnsTrueByDefault_716) {

    EXPECT_TRUE(config->allowThrows());

}



TEST_F(ConfigTest_716, IncludeSuccessfulResults_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->includeSuccessfulResults());

}



TEST_F(ConfigTest_716, WarnAboutMissingAssertions_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->warnAboutMissingAssertions());

}



TEST_F(ConfigTest_716, WarnAboutUnmatchedTestSpecs_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->warnAboutUnmatchedTestSpecs());

}



TEST_F(ConfigTest_716, ZeroTestsCountAsSuccess_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->zeroTestsCountAsSuccess());

}



TEST_F(ConfigTest_716, ShowDurations_ReturnsDefaultValue_716) {

    EXPECT_EQ(config->showDurations(), Catch::ShowDurations::DefaultForReporter);

}



TEST_F(ConfigTest_716, MinDuration_ReturnsNegativeOneByDefault_716) {

    EXPECT_DOUBLE_EQ(config->minDuration(), -1.0);

}



TEST_F(ConfigTest_716, RunOrder_ReturnsDeclaredByDefault_716) {

    EXPECT_EQ(config->runOrder(), Catch::TestRunOrder::Declared);

}



TEST_F(ConfigTest_716, RngSeed_ReturnsGeneratedValue_716) {

    EXPECT_NE(config->rngSeed(), 0u); // Assuming generateRandomSeed does not return 0

}



TEST_F(ConfigTest_716, ShardCount_ReturnsOneByDefault_716) {

    EXPECT_EQ(config->shardCount(), 1u);

}



TEST_F(ConfigTest_716, ShardIndex_ReturnsZeroByDefault_716) {

    EXPECT_EQ(config->shardIndex(), 0u);

}



TEST_F(ConfigTest_716, DefaultColourMode_ReturnsPlatformDefault_716) {

    EXPECT_EQ(config->defaultColourMode(), Catch::ColourMode::PlatformDefault);

}



TEST_F(ConfigTest_716, ShouldDebugBreak_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->shouldDebugBreak());

}



TEST_F(ConfigTest_716, AbortAfter_ReturnsNegativeOneByDefault_716) {

    EXPECT_EQ(config->abortAfter(), -1);

}



TEST_F(ConfigTest_716, ShowInvisibles_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->showInvisibles());

}



TEST_F(ConfigTest_716, Verbosity_ReturnsNormalByDefault_716) {

    EXPECT_EQ(config->verbosity(), Catch::Verbosity::Normal);

}



TEST_F(ConfigTest_716, SkipBenchmarks_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->skipBenchmarks());

}



TEST_F(ConfigTest_716, BenchmarkNoAnalysis_ReturnsFalseByDefault_716) {

    EXPECT_FALSE(config->benchmarkNoAnalysis());

}



TEST_F(ConfigTest_716, BenchmarkSamples_ReturnsHundredByDefault_716) {

    EXPECT_EQ(config->benchmarkSamples(), 100u);

}



TEST_F(ConfigTest_716, BenchmarkConfidenceInterval_ReturnsApproximateValue_716) {

    EXPECT_DOUBLE_EQ(config->benchmarkConfidenceInterval(), 0.95);

}



TEST_F(ConfigTest_716, BenchmarkResamples_ReturnsHundredThousandByDefault_716) {

    EXPECT_EQ(config->benchmarkResamples(), 100000u);

}



TEST_F(ConfigTest_716, BenchmarkWarmupTime_ReturnsOneHundredMillisecondsByDefault_716) {

    EXPECT_EQ(config->benchmarkWarmupTime().count(), 100);

}
