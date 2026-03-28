#include <catch2/catch_test_spec.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_test_spec_parser.hpp>
#include <catch2/catch_tag_alias_autoregistrar.hpp>
#include <catch2/internal/catch_test_case_info_hasher.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>
#include <chrono>

using namespace Catch;

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

class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, invoke, (), (const, override));
};

class TestSpecMatchesByFilterTest_1009 : public ::testing::Test {
protected:
    MockConfig config;
    MockTestInvoker invoker;

    void SetUp() override {
        ON_CALL(config, allowThrows()).WillByDefault(::testing::Return(true));
    }

    TestCaseInfo makeTestCaseInfo(const std::string& name, 
                                  const std::string& tags = "",
                                  const SourceLineInfo& lineInfo = {"test.cpp", 1}) {
        // Use Catch2's mechanisms to create TestCaseInfo
        return TestCaseInfo(""_catch_sr, {lineInfo}, StringRef(name), 
                           {}, {});
    }
};

TEST_F(TestSpecMatchesByFilterTest_1009, EmptyTestSpecReturnsEmptyMatches_1009) {
    TestSpec spec;
    std::vector<TestCaseHandle> testCases;
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    EXPECT_TRUE(matches.empty());
}

TEST_F(TestSpecMatchesByFilterTest_1009, EmptyTestSpecHasNoFilters_1009) {
    TestSpec spec;
    
    EXPECT_FALSE(spec.hasFilters());
}

TEST_F(TestSpecMatchesByFilterTest_1009, EmptyTestSpecMatchesNothing_1009) {
    TestSpec spec;
    std::vector<TestCaseHandle> testCases;
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    EXPECT_EQ(matches.size(), 0u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterWithNoTestCases_1009) {
    // Parse a filter
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("SomeTest");
    TestSpec spec = parser.testSpec();
    
    std::vector<TestCaseHandle> testCases;
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    // Should have one filter match entry (one filter), but with no matching test cases
    EXPECT_EQ(matches.size(), 1u);
    EXPECT_TRUE(matches[0].tests.empty());
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterFindsMatchingTest_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("MyTestName");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "MyTestName"_catch_sr, 
                                                     std::vector<StringRef>{}, 
                                                     std::vector<StringRef>{});
    
    TestCaseHandle handle(tcInfo.get(), &invoker);
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(handle);
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    EXPECT_EQ(matches[0].tests.size(), 1u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterDoesNotMatchDifferentName_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("SomeOtherTest");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "MyTestName"_catch_sr,
                                                     std::vector<StringRef>{},
                                                     std::vector<StringRef>{});
    
    TestCaseHandle handle(tcInfo.get(), &invoker);
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(handle);
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    EXPECT_EQ(matches[0].tests.size(), 0u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterWithThrowsDisabledAndNoThrowTest_1009) {
    // When allowThrows returns false, tests marked as may throw should be filtered out
    ON_CALL(config, allowThrows()).WillByDefault(::testing::Return(false));
    
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("*");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    // Create a test case that is marked with !throws property
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "ThrowingTest"_catch_sr,
                                                     std::vector<StringRef>{},
                                                     std::vector<StringRef>{});
    tcInfo->properties = static_cast<TestCaseProperties>(
        static_cast<uint8_t>(tcInfo->properties) | static_cast<uint8_t>(TestCaseProperties::Throws));
    
    TestCaseHandle handle(tcInfo.get(), &invoker);
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(handle);
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    // isThrowSafe should filter it out when allowThrows is false
    EXPECT_EQ(matches[0].tests.size(), 0u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterWithThrowsEnabledAndThrowingTest_1009) {
    ON_CALL(config, allowThrows()).WillByDefault(::testing::Return(true));
    
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("*");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "ThrowingTest"_catch_sr,
                                                     std::vector<StringRef>{},
                                                     std::vector<StringRef>{});
    tcInfo->properties = static_cast<TestCaseProperties>(
        static_cast<uint8_t>(tcInfo->properties) | static_cast<uint8_t>(TestCaseProperties::Throws));
    
    TestCaseHandle handle(tcInfo.get(), &invoker);
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(handle);
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    EXPECT_EQ(matches[0].tests.size(), 1u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterMultipleTestCases_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("*");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo1 = Detail::make_unique<TestCaseInfo>("", lineInfo, "Test1"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    auto tcInfo2 = Detail::make_unique<TestCaseInfo>("", lineInfo, "Test2"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    auto tcInfo3 = Detail::make_unique<TestCaseInfo>("", lineInfo, "Test3"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(tcInfo1.get(), &invoker));
    testCases.push_back(TestCaseHandle(tcInfo2.get(), &invoker));
    testCases.push_back(TestCaseHandle(tcInfo3.get(), &invoker));
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    EXPECT_EQ(matches[0].tests.size(), 3u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterWildcardMatchesSubstring_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("*Test*");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo1 = Detail::make_unique<TestCaseInfo>("", lineInfo, "MyTestCase"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    auto tcInfo2 = Detail::make_unique<TestCaseInfo>("", lineInfo, "AnotherCase"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(tcInfo1.get(), &invoker));
    testCases.push_back(TestCaseHandle(tcInfo2.get(), &invoker));
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    // Only "MyTestCase" should match "*Test*"
    EXPECT_EQ(matches[0].tests.size(), 1u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, HasFiltersReturnsTrueWhenFiltersExist_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("SomeFilter");
    TestSpec spec = parser.testSpec();
    
    EXPECT_TRUE(spec.hasFilters());
}

TEST_F(TestSpecMatchesByFilterTest_1009, GetInvalidSpecsIsEmptyForValidSpec_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("ValidTest");
    TestSpec spec = parser.testSpec();
    
    EXPECT_TRUE(spec.getInvalidSpecs().empty());
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterMultipleFiltersWithComma_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("Test1,Test2");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo1 = Detail::make_unique<TestCaseInfo>("", lineInfo, "Test1"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    auto tcInfo2 = Detail::make_unique<TestCaseInfo>("", lineInfo, "Test2"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    auto tcInfo3 = Detail::make_unique<TestCaseInfo>("", lineInfo, "Test3"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(tcInfo1.get(), &invoker));
    testCases.push_back(TestCaseHandle(tcInfo2.get(), &invoker));
    testCases.push_back(TestCaseHandle(tcInfo3.get(), &invoker));
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    // Comma separates filters, so we should have 2 filter match entries
    ASSERT_EQ(matches.size(), 2u);
    // First filter "Test1" should match Test1
    EXPECT_EQ(matches[0].tests.size(), 1u);
    // Second filter "Test2" should match Test2
    EXPECT_EQ(matches[1].tests.size(), 1u);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterReturnsPointersToOriginalTestCases_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("TestA");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "TestA"_catch_sr,
                                                     std::vector<StringRef>{},
                                                     std::vector<StringRef>{});
    
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(tcInfo.get(), &invoker));
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    ASSERT_EQ(matches[0].tests.size(), 1u);
    // The pointer should point to the original test case in the vector
    EXPECT_EQ(matches[0].tests[0], &testCases[0]);
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesMethodReturnsTrueForMatchingTestCase_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("MyTest");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "MyTest"_catch_sr,
                                                     std::vector<StringRef>{},
                                                     std::vector<StringRef>{});
    
    EXPECT_TRUE(spec.matches(*tcInfo));
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesMethodReturnsFalseForNonMatchingTestCase_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("MyTest");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "OtherTest"_catch_sr,
                                                     std::vector<StringRef>{},
                                                     std::vector<StringRef>{});
    
    EXPECT_FALSE(spec.matches(*tcInfo));
}

TEST_F(TestSpecMatchesByFilterTest_1009, EmptyTestSpecMatchesReturnsFalse_1009) {
    TestSpec spec;
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo = Detail::make_unique<TestCaseInfo>("", lineInfo, "AnyTest"_catch_sr,
                                                     std::vector<StringRef>{},
                                                     std::vector<StringRef>{});
    
    EXPECT_FALSE(spec.matches(*tcInfo));
}

TEST_F(TestSpecMatchesByFilterTest_1009, MatchesByFilterWithExclusionPattern_1009) {
    TestSpecParser parser(ITagAliasRegistry::get());
    parser.parse("~HiddenTest");
    TestSpec spec = parser.testSpec();
    
    SourceLineInfo lineInfo = {"file.cpp", 1};
    auto tcInfo1 = Detail::make_unique<TestCaseInfo>("", lineInfo, "HiddenTest"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    auto tcInfo2 = Detail::make_unique<TestCaseInfo>("", lineInfo, "VisibleTest"_catch_sr,
                                                      std::vector<StringRef>{},
                                                      std::vector<StringRef>{});
    
    std::vector<TestCaseHandle> testCases;
    testCases.push_back(TestCaseHandle(tcInfo1.get(), &invoker));
    testCases.push_back(TestCaseHandle(tcInfo2.get(), &invoker));
    
    auto matches = spec.matchesByFilter(testCases, config);
    
    ASSERT_EQ(matches.size(), 1u);
    // "HiddenTest" should be excluded, "VisibleTest" should match
    EXPECT_EQ(matches[0].tests.size(), 1u);
}
