#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/reporters/catch_reporter_common_base.cpp"



using namespace Catch;

using ::testing::_;

using ::testing::MockFunction;



class MockConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const, override));

    MOCK_METHOD(StringRef, name, (), (const, override));

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));

    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));

    MOCK_METHOD(int, abortAfter, (), (const, override));

    MOCK_METHOD(bool, showInvisibles, (), (const, override));

    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));

    MOCK_METHOD(double, minDuration, (), (const, override));

    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));

    MOCK_METHOD(bool, hasTestFilters, (), (const, override));

    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));

    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));

    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));

    MOCK_METHOD(unsigned int, shardCount, (), (const, override));

    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));

    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));

    MOCK_METHOD(Verbosity, verbosity, (), (const, override));

    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));

};



class ReporterBaseTest_780 : public ::testing::Test {

protected:

    MockConfig mockConfig;

    ReporterBase reporter{ReporterConfig{&mockConfig, std::make_unique<std::ostringstream>(), ColourMode::None}};



    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ReporterBaseTest_780, ListTags_NormalOperation_780) {

    std::vector<TagInfo> tags = {TagInfo{"tag1"}, TagInfo{"tag2"}};

    EXPECT_CALL(mockConfig, hasTestFilters()).WillOnce(::testing::Return(false));

    reporter.listTags(tags);

}



TEST_F(ReporterBaseTest_780, ListTags_NoTags_780) {

    std::vector<TagInfo> tags = {};

    EXPECT_CALL(mockConfig, hasTestFilters()).WillOnce(::testing::Return(false));

    reporter.listTags(tags);

}



TEST_F(ReporterBaseTest_780, ListTags_HasTestFilters_780) {

    std::vector<TagInfo> tags = {TagInfo{"tag1"}, TagInfo{"tag2"}};

    EXPECT_CALL(mockConfig, hasTestFilters()).WillOnce(::testing::Return(true));

    reporter.listTags(tags);

}
