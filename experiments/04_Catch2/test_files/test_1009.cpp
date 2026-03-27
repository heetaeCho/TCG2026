#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_test_spec.hpp"

#include "catch_interfaces_config.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;

using ::testing::ElementsAre;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const));

    MOCK_METHOD(StringRef, name, (), (const));

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const));

    MOCK_METHOD(bool, shouldDebugBreak, (), (const));

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const));

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const));

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const));

    MOCK_METHOD(int, abortAfter, (), (const));

    MOCK_METHOD(bool, showInvisibles, (), (const));

    MOCK_METHOD(ShowDurations, showDurations, (), (const));

    MOCK_METHOD(double, minDuration, (), (const));

    MOCK_METHOD(const TestSpec&, testSpec, (), (const));

    MOCK_METHOD(bool, hasTestFilters, (), (const));

    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const));

    MOCK_METHOD(TestRunOrder, runOrder, (), (const));

    MOCK_METHOD(uint32_t, rngSeed, (), (const));

    MOCK_METHOD(unsigned int, shardCount, (), (const));

    MOCK_METHOD(unsigned int, shardIndex, (), (const));

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const));

    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const));

    MOCK_METHOD(Verbosity, verbosity, (), (const));

    MOCK_METHOD(bool, skipBenchmarks, (), (const));

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const));

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const));

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const));

};



class TestSpecTest_1009 : public ::testing::Test {

protected:

    std::vector<TestCaseHandle> testCases;

    MockIConfig mockConfig;

    TestCaseInfo testCaseInfo;

    TestCaseHandle testCaseHandle;



    void SetUp() override {

        testCaseInfo = TestCaseInfo("TestName", "Description", SourceLineInfo("", 0));

        testCaseHandle = TestCaseHandle(&testCaseInfo, nullptr);

        testCases.push_back(testCaseHandle);

    }

};



TEST_F(TestSpecTest_1009, MatchesByFilter_ReturnsEmptyMatches_WhenNoFilters_1009) {

    TestSpec testSpec;

    EXPECT_CALL(mockConfig, testSpec()).WillOnce(ReturnRef(testSpec));



    auto result = testSpec.matchesByFilter(testCases, mockConfig);

    EXPECT_TRUE(result.empty());

}



TEST_F(TestSpecTest_1009, MatchesByFilter_ReturnsMatchingTestCases_WhenFiltersMatch_1009) {

    TestSpec testSpec;

    Filter filter;

    filter.m_required.push_back(Detail::make_unique<Pattern>("TestName"));

    testSpec.m_filters.push_back(filter);



    EXPECT_CALL(mockConfig, testSpec()).WillOnce(ReturnRef(testSpec));



    auto result = testSpec.matchesByFilter(testCases, mockConfig);

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0].currentMatches.size(), 1);

    EXPECT_EQ(&testCaseHandle, result[0].currentMatches[0]);

}



TEST_F(TestSpecTest_1009, MatchesByFilter_ReturnsNoMatches_WhenFiltersDoNotMatch_1009) {

    TestSpec testSpec;

    Filter filter;

    filter.m_required.push_back(Detail::make_unique<Pattern>("NonExistentName"));

    testSpec.m_filters.push_back(filter);



    EXPECT_CALL(mockConfig, testSpec()).WillOnce(ReturnRef(testSpec));



    auto result = testSpec.matchesByFilter(testCases, mockConfig);

    ASSERT_EQ(result.size(), 1);

    EXPECT_TRUE(result[0].currentMatches.empty());

}



TEST_F(TestSpecTest_1009, MatchesByFilter_ReturnsNoMatches_WhenForbiddenFiltersMatch_1009) {

    TestSpec testSpec;

    Filter filter;

    filter.m_forbidden.push_back(Detail::make_unique<Pattern>("TestName"));

    testSpec.m_filters.push_back(filter);



    EXPECT_CALL(mockConfig, testSpec()).WillOnce(ReturnRef(testSpec));



    auto result = testSpec.matchesByFilter(testCases, mockConfig);

    ASSERT_EQ(result.size(), 1);

    EXPECT_TRUE(result[0].currentMatches.empty());

}



TEST_F(TestSpecTest_1009, MatchesByFilter_ReturnsMatches_WhenMultipleRequiredFiltersMatch_1009) {

    TestSpec testSpec;

    Filter filter;

    filter.m_required.push_back(Detail::make_unique<Pattern>("TestName"));

    filter.m_required.push_back(Detail::make_unique<Pattern>("Description"));

    testSpec.m_filters.push_back(filter);



    EXPECT_CALL(mockConfig, testSpec()).WillOnce(ReturnRef(testSpec));



    auto result = testSpec.matchesByFilter(testCases, mockConfig);

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0].currentMatches.size(), 1);

    EXPECT_EQ(&testCaseHandle, result[0].currentMatches[0]);

}



TEST_F(TestSpecTest_1009, MatchesByFilter_ReturnsNoMatches_WhenMultipleRequiredFiltersDoNotMatch_1009) {

    TestSpec testSpec;

    Filter filter;

    filter.m_required.push_back(Detail::make_unique<Pattern>("TestName"));

    filter.m_required.push_back(Detail::make_unique<Pattern>("NonExistentDescription"));

    testSpec.m_filters.push_back(filter);



    EXPECT_CALL(mockConfig, testSpec()).WillOnce(ReturnRef(testSpec));



    auto result = testSpec.matchesByFilter(testCases, mockConfig);

    ASSERT_EQ(result.size(), 1);

    EXPECT_TRUE(result[0].currentMatches.empty());

}
