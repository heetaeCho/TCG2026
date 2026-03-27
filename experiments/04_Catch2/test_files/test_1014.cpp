#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"

#include "./TestProjects/Catch2/src/catch2/catch_test_spec.hpp"

#include "./TestProjects/Catch2/interfaces/catch_interfaces_config.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;

using testing::NiceMock;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const override));

    MOCK_METHOD(StringRef, name, (), (const override));

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const override));

    MOCK_METHOD(bool, shouldDebugBreak, (), (const override));

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const override));

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const override));

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const override));

    MOCK_METHOD(int, abortAfter, (), (const override));

    MOCK_METHOD(bool, showInvisibles, (), (const override));

    MOCK_METHOD(ShowDurations, showDurations, (), (const override));

    MOCK_METHOD(double, minDuration, (), (const override));

    MOCK_METHOD(const TestSpec&, testSpec, (), (const override));

    MOCK_METHOD(bool, hasTestFilters, (), (const override));

    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const override));

    MOCK_METHOD(TestRunOrder, runOrder, (), (const override));

    MOCK_METHOD(uint32_t, rngSeed, (), (const override));

    MOCK_METHOD(unsigned int, shardCount, (), (const override));

    MOCK_METHOD(unsigned int, shardIndex, (), (const override));

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const override));

    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const override));

    MOCK_METHOD(Verbosity, verbosity, (), (const override));

    MOCK_METHOD(bool, skipBenchmarks, (), (const override));

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const override));

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const override));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const override));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const override));

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const override));

};



class MockTestSpec : public TestSpec {

public:

    MOCK_METHOD(bool, hasFilters, (), (const override));

    MOCK_METHOD(bool, matches, (const TestCaseInfo&), (const override));

    MOCK_METHOD(TestSpec::Matches, matchesByFilter, (const std::vector<TestCaseHandle>&, const IConfig&), (const override));

    MOCK_METHOD(const TestSpec::vectorStrings&, getInvalidSpecs, (), (const override));

};



class MockITestInvoker : public ITestInvoker {

public:

    MOCK_METHOD(void, invoke, (), (const override));

};



TEST_F(Catch2FilterTests_1014, NoFiltersNoHiddenCases_1014) {

    std::vector<TestCaseHandle> testCases = {

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("TestName"), SourceLineInfo("", 0)), new MockITestInvoker()),

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("AnotherTest"), SourceLineInfo("", 1)), new MockITestInvoker())

    };



    NiceMock<MockIConfig> config;

    EXPECT_CALL(config, shardCount()).WillOnce(testing::Return(1));

    EXPECT_CALL(config, shardIndex()).WillOnce(testing::Return(0));



    NiceMock<MockTestSpec> testSpec;

    EXPECT_CALL(testSpec, hasFilters()).WillOnce(testing::Return(false));



    std::vector<TestCaseHandle> filtered = filterTests(testCases, testSpec, config);



    ASSERT_EQ(filtered.size(), 2);

}



TEST_F(Catch2FilterTests_1014, NoFiltersWithHiddenCases_1014) {

    std::vector<TestCaseHandle> testCases = {

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("TestName"), SourceLineInfo("", 0)), new MockITestInvoker()),

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("[.][hidden]HiddenTest"), SourceLineInfo("", 1)), new MockITestInvoker())

    };



    NiceMock<MockIConfig> config;

    EXPECT_CALL(config, shardCount()).WillOnce(testing::Return(1));

    EXPECT_CALL(config, shardIndex()).WillOnce(testing::Return(0));



    NiceMock<MockTestSpec> testSpec;

    EXPECT_CALL(testSpec, hasFilters()).WillOnce(testing::Return(false));



    std::vector<TestCaseHandle> filtered = filterTests(testCases, testSpec, config);



    ASSERT_EQ(filtered.size(), 1);

}



TEST_F(Catch2FilterTests_1014, WithFiltersMatchingCase_1014) {

    std::vector<TestCaseHandle> testCases = {

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("TestName"), SourceLineInfo("", 0)), new MockITestInvoker()),

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("[tag]TaggedTest"), SourceLineInfo("", 1)), new MockITestInvoker())

    };



    NiceMock<MockIConfig> config;

    EXPECT_CALL(config, shardCount()).WillOnce(testing::Return(1));

    EXPECT_CALL(config, shardIndex()).WillOnce(testing::Return(0));



    NiceMock<MockTestSpec> testSpec;

    EXPECT_CALL(testSpec, hasFilters()).WillOnce(testing::Return(true));

    EXPECT_CALL(testSpec, matches(testing::_)).WillRepeatedly(testing::Invoke([](const TestCaseInfo& info) {

        return info.tagsAsString().find("[tag]") != std::string::npos;

    }));



    std::vector<TestCaseHandle> filtered = filterTests(testCases, testSpec, config);



    ASSERT_EQ(filtered.size(), 1);

}



TEST_F(Catch2FilterTests_1014, WithFiltersNoMatchingCase_1014) {

    std::vector<TestCaseHandle> testCases = {

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("TestName"), SourceLineInfo("", 0)), new MockITestInvoker()),

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("[tag]TaggedTest"), SourceLineInfo("", 1)), new MockITestInvoker())

    };



    NiceMock<MockIConfig> config;

    EXPECT_CALL(config, shardCount()).WillOnce(testing::Return(1));

    EXPECT_CALL(config, shardIndex()).WillOnce(testing::Return(0));



    NiceMock<MockTestSpec> testSpec;

    EXPECT_CALL(testSpec, hasFilters()).WillOnce(testing::Return(true));

    EXPECT_CALL(testSpec, matches(testing::_)).WillRepeatedly(testing::Return(false));



    std::vector<TestCaseHandle> filtered = filterTests(testCases, testSpec, config);



    ASSERT_EQ(filtered.size(), 0);

}



TEST_F(Catch2FilterTests_1014, ShardingSingleShard_1014) {

    std::vector<TestCaseHandle> testCases = {

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("TestName"), SourceLineInfo("", 0)), new MockITestInvoker()),

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("AnotherTest"), SourceLineInfo("", 1)), new MockITestInvoker())

    };



    NiceMock<MockIConfig> config;

    EXPECT_CALL(config, shardCount()).WillOnce(testing::Return(1));

    EXPECT_CALL(config, shardIndex()).WillOnce(testing::Return(0));



    NiceMock<MockTestSpec> testSpec;

    EXPECT_CALL(testSpec, hasFilters()).WillOnce(testing::Return(false));



    std::vector<TestCaseHandle> filtered = filterTests(testCases, testSpec, config);



    ASSERT_EQ(filtered.size(), 2);

}



TEST_F(Catch2FilterTests_1014, ShardingMultipleShards_1014) {

    std::vector<TestCaseHandle> testCases = {

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("TestName"), SourceLineInfo("", 0)), new MockITestInvoker()),

        TestCaseHandle(new TestCaseInfo("ClassName", NameAndTags("AnotherTest"), SourceLineInfo("", 1)), new MockITestInvoker())

    };



    NiceMock<MockIConfig> config;

    EXPECT_CALL(config, shardCount()).WillOnce(testing::Return(2));

    EXPECT_CALL(config, shardIndex()).WillOnce(testing::Return(0));



    NiceMock<MockTestSpec> testSpec;

    EXPECT_CALL(testSpec, hasFilters()).WillOnce(testing::Return(false));



    std::vector<TestCaseHandle> filtered = filterTests(testCases, testSpec, config);



    ASSERT_EQ(filtered.size(), 1);

}
