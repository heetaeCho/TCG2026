#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_all.hpp"

using namespace Catch;

// Mock for IConfig
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

// Mock for ITestInvoker
class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, invoke, (), (const, override));
};

class FilterTestsTest_1014 : public ::testing::Test {
protected:
    MockConfig config;
    MockTestInvoker invoker;

    void SetUp() override {
        // Default: single shard (no sharding)
        ON_CALL(config, shardCount()).WillByDefault(::testing::Return(1));
        ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(0));
    }

    std::unique_ptr<TestCaseInfo> makeTestCaseInfo(const std::string& name, bool hidden = false) {
        std::string tags = hidden ? "[.][hidden]" : "";
        NameAndTags nat(name, tags);
        SourceLineInfo lineInfo("test_file.cpp", 1);
        return std::make_unique<TestCaseInfo>(StringRef("TestClass"), nat, lineInfo);
    }
};

// Test: Empty test cases with no filters returns empty
TEST_F(FilterTestsTest_1014, EmptyTestCasesReturnsEmpty_1014) {
    std::vector<TestCaseHandle> testCases;
    TestSpec testSpec;

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_TRUE(result.empty());
}

// Test: No filters - non-hidden tests are included
TEST_F(FilterTestsTest_1014, NoFiltersIncludesNonHiddenTests_1014) {
    auto info1 = makeTestCaseInfo("VisibleTest1");
    auto info2 = makeTestCaseInfo("VisibleTest2");

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info1.get(), &invoker));
    testCases.push_back(TestCaseHandle(info2.get(), &invoker));

    TestSpec testSpec; // no filters

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_EQ(result.size(), 2u);
}

// Test: No filters - hidden tests are excluded
TEST_F(FilterTestsTest_1014, NoFiltersExcludesHiddenTests_1014) {
    auto info1 = makeTestCaseInfo("VisibleTest");
    auto info2 = makeTestCaseInfo("HiddenTest", true);

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info1.get(), &invoker));
    testCases.push_back(TestCaseHandle(info2.get(), &invoker));

    TestSpec testSpec; // no filters

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getTestCaseInfo().name, "VisibleTest");
}

// Test: All hidden tests with no filters returns empty
TEST_F(FilterTestsTest_1014, NoFiltersAllHiddenReturnsEmpty_1014) {
    auto info1 = makeTestCaseInfo("Hidden1", true);
    auto info2 = makeTestCaseInfo("Hidden2", true);

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info1.get(), &invoker));
    testCases.push_back(TestCaseHandle(info2.get(), &invoker));

    TestSpec testSpec;

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_TRUE(result.empty());
}

// Test: Sharding with shard count > 1 returns a subset
TEST_F(FilterTestsTest_1014, ShardingReturnsSubset_1014) {
    std::vector<std::unique_ptr<TestCaseInfo>> infos;
    std::vector<TestCaseHandle> testCases;

    for (int i = 0; i < 10; ++i) {
        infos.push_back(makeTestCaseInfo("Test" + std::to_string(i)));
        testCases.push_back(TestCaseHandle(infos.back().get(), &invoker));
    }

    TestSpec testSpec;

    // Shard 0 of 2
    ON_CALL(config, shardCount()).WillByDefault(::testing::Return(2));
    ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(0));

    auto shard0 = filterTests(testCases, testSpec, config);

    // Shard 1 of 2
    ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(1));

    auto shard1 = filterTests(testCases, testSpec, config);

    // Both shards together should cover all test cases
    EXPECT_EQ(shard0.size() + shard1.size(), 10u);
    EXPECT_GT(shard0.size(), 0u);
    EXPECT_GT(shard1.size(), 0u);
}

// Test: Sharding with shard count = 1, shard index = 0 returns all filtered
TEST_F(FilterTestsTest_1014, SingleShardReturnsAll_1014) {
    std::vector<std::unique_ptr<TestCaseInfo>> infos;
    std::vector<TestCaseHandle> testCases;

    for (int i = 0; i < 5; ++i) {
        infos.push_back(makeTestCaseInfo("Test" + std::to_string(i)));
        testCases.push_back(TestCaseHandle(infos.back().get(), &invoker));
    }

    TestSpec testSpec;
    ON_CALL(config, shardCount()).WillByDefault(::testing::Return(1));
    ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(0));

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_EQ(result.size(), 5u);
}

// Test: With filters, matching test spec includes matching tests (including hidden ones)
TEST_F(FilterTestsTest_1014, WithFiltersMatchingTestsIncluded_1014) {
    auto info1 = makeTestCaseInfo("VisibleTest");
    auto info2 = makeTestCaseInfo("HiddenTest", true);

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info1.get(), &invoker));
    testCases.push_back(TestCaseHandle(info2.get(), &invoker));

    // Create a TestSpec with a filter that matches all tests
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("*");
    TestSpec testSpec = parser.testSpec();

    ASSERT_TRUE(testSpec.hasFilters());

    auto result = filterTests(testCases, testSpec, config);

    // With wildcard filter, both visible and hidden tests should match
    EXPECT_GE(result.size(), 1u);
}

// Test: With filters, non-matching tests are excluded
TEST_F(FilterTestsTest_1014, WithFiltersNonMatchingExcluded_1014) {
    auto info1 = makeTestCaseInfo("AppleTest");
    auto info2 = makeTestCaseInfo("BananaTest");

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info1.get(), &invoker));
    testCases.push_back(TestCaseHandle(info2.get(), &invoker));

    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("AppleTest");
    TestSpec testSpec = parser.testSpec();

    ASSERT_TRUE(testSpec.hasFilters());

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getTestCaseInfo().name, "AppleTest");
}

// Test: With filters that match nothing, returns empty
TEST_F(FilterTestsTest_1014, WithFilterMatchingNothingReturnsEmpty_1014) {
    auto info1 = makeTestCaseInfo("TestA");
    auto info2 = makeTestCaseInfo("TestB");

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info1.get(), &invoker));
    testCases.push_back(TestCaseHandle(info2.get(), &invoker));

    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("NonExistentTestName");
    TestSpec testSpec = parser.testSpec();

    ASSERT_TRUE(testSpec.hasFilters());

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_TRUE(result.empty());
}

// Test: Sharding distributes evenly with multiple shards
TEST_F(FilterTestsTest_1014, ShardingDistributesTests_1014) {
    std::vector<std::unique_ptr<TestCaseInfo>> infos;
    std::vector<TestCaseHandle> testCases;

    for (int i = 0; i < 12; ++i) {
        infos.push_back(makeTestCaseInfo("Test" + std::to_string(i)));
        testCases.push_back(TestCaseHandle(infos.back().get(), &invoker));
    }

    TestSpec testSpec;
    ON_CALL(config, shardCount()).WillByDefault(::testing::Return(3));

    size_t totalFromShards = 0;
    for (unsigned int s = 0; s < 3; ++s) {
        ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(s));
        auto shard = filterTests(testCases, testSpec, config);
        totalFromShards += shard.size();
        EXPECT_GT(shard.size(), 0u);
    }

    EXPECT_EQ(totalFromShards, 12u);
}

// Test: Single test case, not hidden, no filters
TEST_F(FilterTestsTest_1014, SingleVisibleTestNoFilters_1014) {
    auto info = makeTestCaseInfo("OnlyTest");

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info.get(), &invoker));

    TestSpec testSpec;

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getTestCaseInfo().name, "OnlyTest");
}

// Test: Single hidden test case, no filters - should be excluded
TEST_F(FilterTestsTest_1014, SingleHiddenTestNoFilters_1014) {
    auto info = makeTestCaseInfo("HiddenOnly", true);

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(info.get(), &invoker));

    TestSpec testSpec;

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_TRUE(result.empty());
}

// Test: Mixed visible and hidden, no filters, verify only visible returned
TEST_F(FilterTestsTest_1014, MixedVisibleHiddenNoFilters_1014) {
    auto visible1 = makeTestCaseInfo("Visible1");
    auto hidden1 = makeTestCaseInfo("Hidden1", true);
    auto visible2 = makeTestCaseInfo("Visible2");
    auto hidden2 = makeTestCaseInfo("Hidden2", true);
    auto visible3 = makeTestCaseInfo("Visible3");

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(visible1.get(), &invoker));
    testCases.push_back(TestCaseHandle(hidden1.get(), &invoker));
    testCases.push_back(TestCaseHandle(visible2.get(), &invoker));
    testCases.push_back(TestCaseHandle(hidden2.get(), &invoker));
    testCases.push_back(TestCaseHandle(visible3.get(), &invoker));

    TestSpec testSpec;

    auto result = filterTests(testCases, testSpec, config);

    EXPECT_EQ(result.size(), 3u);
}

// Test: Wildcard filter includes hidden tests
TEST_F(FilterTestsTest_1014, WildcardFilterIncludesHiddenTests_1014) {
    auto visible = makeTestCaseInfo("VisibleTest");
    auto hidden = makeTestCaseInfo("HiddenTest", true);

    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(visible.get(), &invoker));
    testCases.push_back(TestCaseHandle(hidden.get(), &invoker));

    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("*");
    TestSpec testSpec = parser.testSpec();

    auto result = filterTests(testCases, testSpec, config);

    // Wildcard should match both visible and hidden
    EXPECT_EQ(result.size(), 2u);
}

// Test: Sharding with uneven distribution
TEST_F(FilterTestsTest_1014, ShardingUnevenDistribution_1014) {
    std::vector<std::unique_ptr<TestCaseInfo>> infos;
    std::vector<TestCaseHandle> testCases;

    // 7 tests, 3 shards - uneven
    for (int i = 0; i < 7; ++i) {
        infos.push_back(makeTestCaseInfo("Test" + std::to_string(i)));
        testCases.push_back(TestCaseHandle(infos.back().get(), &invoker));
    }

    TestSpec testSpec;
    ON_CALL(config, shardCount()).WillByDefault(::testing::Return(3));

    size_t totalFromShards = 0;
    for (unsigned int s = 0; s < 3; ++s) {
        ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(s));
        auto shard = filterTests(testCases, testSpec, config);
        totalFromShards += shard.size();
    }

    EXPECT_EQ(totalFromShards, 7u);
}

// Test: Shards don't overlap - each test appears in exactly one shard
TEST_F(FilterTestsTest_1014, ShardsDoNotOverlap_1014) {
    std::vector<std::unique_ptr<TestCaseInfo>> infos;
    std::vector<TestCaseHandle> testCases;

    for (int i = 0; i < 6; ++i) {
        infos.push_back(makeTestCaseInfo("Test" + std::to_string(i)));
        testCases.push_back(TestCaseHandle(infos.back().get(), &invoker));
    }

    TestSpec testSpec;
    ON_CALL(config, shardCount()).WillByDefault(::testing::Return(2));

    ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(0));
    auto shard0 = filterTests(testCases, testSpec, config);

    ON_CALL(config, shardIndex()).WillByDefault(::testing::Return(1));
    auto shard1 = filterTests(testCases, testSpec, config);

    // Collect all test names from both shards
    std::set<std::string> allNames;
    for (auto& tc : shard0) allNames.insert(std::string(tc.getTestCaseInfo().name));
    for (auto& tc : shard1) allNames.insert(std::string(tc.getTestCaseInfo().name));

    // All 6 unique tests should be present
    EXPECT_EQ(allNames.size(), 6u);
    EXPECT_EQ(shard0.size() + shard1.size(), 6u);
}
