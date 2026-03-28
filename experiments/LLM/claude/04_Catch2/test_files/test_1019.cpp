#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <chrono>

// Include necessary Catch2 headers
#include "catch2/internal/catch_test_case_registry_impl.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_case_info_hasher.hpp"
#include "catch2/catch_test_spec.hpp"

using namespace Catch;
using ::testing::Return;
using ::testing::ReturnRef;

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

class TestRegistryTest_1019 : public ::testing::Test {
protected:
    void SetUp() override {
        config_ = std::make_unique<MockConfig>();
        // Set up default config behavior
        std::vector<std::string> emptyVec;
        testsOrTags_ = emptyVec;
        sectionsToRun_ = emptyVec;

        ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(*config_, rngSeed()).WillByDefault(Return(0u));
        ON_CALL(*config_, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(*config_, getTestsOrTags()).WillByDefault(ReturnRef(testsOrTags_));
        ON_CALL(*config_, getSectionsToRun()).WillByDefault(ReturnRef(sectionsToRun_));
        ON_CALL(*config_, shardCount()).WillByDefault(Return(1u));
        ON_CALL(*config_, shardIndex()).WillByDefault(Return(0u));
    }

    std::unique_ptr<MockConfig> config_;
    std::vector<std::string> testsOrTags_;
    std::vector<std::string> sectionsToRun_;

    Detail::unique_ptr<TestCaseInfo> makeTestCaseInfo(const std::string& name,
                                                       const std::string& className = "",
                                                       const SourceLineInfo& lineInfo = SourceLineInfo("test.cpp", 1)) {
        // Use Catch2's way of creating TestCaseInfo
        return Detail::make_unique<TestCaseInfo>(
            std::string(className),
            NameAndTags{StringRef(name), StringRef("[test]")},
            lineInfo
        );
    }
};

// Test: Empty registry returns empty sorted list
TEST_F(TestRegistryTest_1019, EmptyRegistryReturnsEmptySortedList_1019) {
    TestRegistry registry;
    auto const& sorted = registry.getAllTestsSorted(*config_);
    EXPECT_TRUE(sorted.empty());
}

// Test: Empty registry returns empty list for getAllTests
TEST_F(TestRegistryTest_1019, EmptyRegistryReturnsEmptyTests_1019) {
    TestRegistry registry;
    auto const& tests = registry.getAllTests();
    EXPECT_TRUE(tests.empty());
}

// Test: Empty registry returns empty list for getAllInfos
TEST_F(TestRegistryTest_1019, EmptyRegistryReturnsEmptyInfos_1019) {
    TestRegistry registry;
    auto const& infos = registry.getAllInfos();
    EXPECT_TRUE(infos.empty());
}

// Test: Registering a single test case
TEST_F(TestRegistryTest_1019, RegisterSingleTestCase_1019) {
    TestRegistry registry;

    auto info = makeTestCaseInfo("TestOne");
    auto invoker = Detail::make_unique<MockTestInvoker>();

    registry.registerTest(std::move(info), std::move(invoker));

    auto const& tests = registry.getAllTests();
    EXPECT_EQ(tests.size(), 1u);

    auto const& infos = registry.getAllInfos();
    EXPECT_EQ(infos.size(), 1u);
}

// Test: Registering multiple test cases
TEST_F(TestRegistryTest_1019, RegisterMultipleTestCases_1019) {
    TestRegistry registry;

    for (int i = 0; i < 5; ++i) {
        auto info = makeTestCaseInfo("Test" + std::to_string(i), "",
                                      SourceLineInfo("test.cpp", static_cast<std::size_t>(i + 1)));
        auto invoker = Detail::make_unique<MockTestInvoker>();
        registry.registerTest(std::move(info), std::move(invoker));
    }

    auto const& tests = registry.getAllTests();
    EXPECT_EQ(tests.size(), 5u);

    auto const& infos = registry.getAllInfos();
    EXPECT_EQ(infos.size(), 5u);
}

// Test: getAllTestsSorted returns correct number of tests
TEST_F(TestRegistryTest_1019, GetAllTestsSortedReturnsCorrectCount_1019) {
    TestRegistry registry;

    for (int i = 0; i < 3; ++i) {
        auto info = makeTestCaseInfo("SortTest" + std::to_string(i), "",
                                      SourceLineInfo("test.cpp", static_cast<std::size_t>(i + 1)));
        auto invoker = Detail::make_unique<MockTestInvoker>();
        registry.registerTest(std::move(info), std::move(invoker));
    }

    auto const& sorted = registry.getAllTestsSorted(*config_);
    EXPECT_EQ(sorted.size(), 3u);
}

// Test: getAllTestsSorted with Declared order
TEST_F(TestRegistryTest_1019, GetAllTestsSortedDeclaredOrder_1019) {
    TestRegistry registry;

    auto info1 = makeTestCaseInfo("ZTest", "", SourceLineInfo("test.cpp", 1));
    auto invoker1 = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info1), std::move(invoker1));

    auto info2 = makeTestCaseInfo("ATest", "", SourceLineInfo("test.cpp", 2));
    auto invoker2 = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info2), std::move(invoker2));

    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));

    auto const& sorted = registry.getAllTestsSorted(*config_);
    EXPECT_EQ(sorted.size(), 2u);
}

// Test: getAllTestsSorted with LexicographicallySorted order
TEST_F(TestRegistryTest_1019, GetAllTestsSortedLexicographicOrder_1019) {
    TestRegistry registry;

    auto info1 = makeTestCaseInfo("ZTest", "", SourceLineInfo("test.cpp", 1));
    auto invoker1 = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info1), std::move(invoker1));

    auto info2 = makeTestCaseInfo("ATest", "", SourceLineInfo("test.cpp", 2));
    auto invoker2 = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info2), std::move(invoker2));

    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::LexicographicallySorted));

    auto const& sorted = registry.getAllTestsSorted(*config_);
    EXPECT_EQ(sorted.size(), 2u);

    // In lexicographic order, "ATest" should come before "ZTest"
    EXPECT_EQ(sorted[0].getTestCaseInfo().name, "ATest");
    EXPECT_EQ(sorted[1].getTestCaseInfo().name, "ZTest");
}

// Test: getAllTestsSorted with Randomized order
TEST_F(TestRegistryTest_1019, GetAllTestsSortedRandomizedOrder_1019) {
    TestRegistry registry;

    for (int i = 0; i < 10; ++i) {
        auto info = makeTestCaseInfo("RandTest" + std::to_string(i), "",
                                      SourceLineInfo("test.cpp", static_cast<std::size_t>(i + 1)));
        auto invoker = Detail::make_unique<MockTestInvoker>();
        registry.registerTest(std::move(info), std::move(invoker));
    }

    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::Randomized));
    ON_CALL(*config_, rngSeed()).WillByDefault(Return(42u));

    auto const& sorted = registry.getAllTestsSorted(*config_);
    EXPECT_EQ(sorted.size(), 10u);
}

// Test: Changing sort order re-sorts
TEST_F(TestRegistryTest_1019, ChangingSortOrderResorts_1019) {
    TestRegistry registry;

    auto info1 = makeTestCaseInfo("ZTest", "", SourceLineInfo("test.cpp", 1));
    auto invoker1 = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info1), std::move(invoker1));

    auto info2 = makeTestCaseInfo("ATest", "", SourceLineInfo("test.cpp", 2));
    auto invoker2 = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info2), std::move(invoker2));

    // First call with Declared order
    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
    auto const& sorted1 = registry.getAllTestsSorted(*config_);
    EXPECT_EQ(sorted1.size(), 2u);

    // Now change to LexicographicallySorted
    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::LexicographicallySorted));
    auto const& sorted2 = registry.getAllTestsSorted(*config_);
    EXPECT_EQ(sorted2.size(), 2u);
    EXPECT_EQ(sorted2[0].getTestCaseInfo().name, "ATest");
    EXPECT_EQ(sorted2[1].getTestCaseInfo().name, "ZTest");
}

// Test: Calling getAllTestsSorted multiple times with same config returns consistent results
TEST_F(TestRegistryTest_1019, ConsistentResultsOnRepeatedCalls_1019) {
    TestRegistry registry;

    for (int i = 0; i < 5; ++i) {
        auto info = makeTestCaseInfo("ConsistentTest" + std::to_string(i), "",
                                      SourceLineInfo("test.cpp", static_cast<std::size_t>(i + 1)));
        auto invoker = Detail::make_unique<MockTestInvoker>();
        registry.registerTest(std::move(info), std::move(invoker));
    }

    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::LexicographicallySorted));

    auto const& sorted1 = registry.getAllTestsSorted(*config_);
    auto const& sorted2 = registry.getAllTestsSorted(*config_);

    EXPECT_EQ(sorted1.size(), sorted2.size());
    for (size_t i = 0; i < sorted1.size(); ++i) {
        EXPECT_EQ(sorted1[i].getTestCaseInfo().name, sorted2[i].getTestCaseInfo().name);
    }
}

// Test: getAllInfos matches registered test info
TEST_F(TestRegistryTest_1019, GetAllInfosMatchesRegistered_1019) {
    TestRegistry registry;

    auto info = makeTestCaseInfo("InfoTest", "", SourceLineInfo("test.cpp", 42));
    auto invoker = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info), std::move(invoker));

    auto const& infos = registry.getAllInfos();
    ASSERT_EQ(infos.size(), 1u);
    EXPECT_EQ(infos[0]->name, "InfoTest");
}

// Test: getAllTests and getAllTestsSorted return same number of elements
TEST_F(TestRegistryTest_1019, AllTestsAndSortedSameSize_1019) {
    TestRegistry registry;

    for (int i = 0; i < 4; ++i) {
        auto info = makeTestCaseInfo("SizeTest" + std::to_string(i), "",
                                      SourceLineInfo("test.cpp", static_cast<std::size_t>(i + 1)));
        auto invoker = Detail::make_unique<MockTestInvoker>();
        registry.registerTest(std::move(info), std::move(invoker));
    }

    auto const& all = registry.getAllTests();
    auto const& sorted = registry.getAllTestsSorted(*config_);

    EXPECT_EQ(all.size(), sorted.size());
}

// Test: Single test case sorted is same as only element
TEST_F(TestRegistryTest_1019, SingleTestSortedIsSameElement_1019) {
    TestRegistry registry;

    auto info = makeTestCaseInfo("OnlyTest", "", SourceLineInfo("test.cpp", 1));
    auto invoker = Detail::make_unique<MockTestInvoker>();
    registry.registerTest(std::move(info), std::move(invoker));

    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::LexicographicallySorted));

    auto const& sorted = registry.getAllTestsSorted(*config_);
    ASSERT_EQ(sorted.size(), 1u);
    EXPECT_EQ(sorted[0].getTestCaseInfo().name, "OnlyTest");
}

// Test: Randomized with same seed produces same order
TEST_F(TestRegistryTest_1019, RandomizedSameSeedSameOrder_1019) {
    TestRegistry registry;

    for (int i = 0; i < 10; ++i) {
        auto info = makeTestCaseInfo("SeedTest" + std::to_string(i), "",
                                      SourceLineInfo("test.cpp", static_cast<std::size_t>(i + 1)));
        auto invoker = Detail::make_unique<MockTestInvoker>();
        registry.registerTest(std::move(info), std::move(invoker));
    }

    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::Randomized));
    ON_CALL(*config_, rngSeed()).WillByDefault(Return(12345u));

    auto const& sorted1 = registry.getAllTestsSorted(*config_);

    // Collect names
    std::vector<std::string> names1;
    for (auto const& h : sorted1) {
        names1.push_back(std::string(h.getTestCaseInfo().name));
    }

    // Force re-sort by switching and switching back
    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
    registry.getAllTestsSorted(*config_);

    ON_CALL(*config_, runOrder()).WillByDefault(Return(TestRunOrder::Randomized));
    ON_CALL(*config_, rngSeed()).WillByDefault(Return(12345u));
    auto const& sorted2 = registry.getAllTestsSorted(*config_);

    std::vector<std::string> names2;
    for (auto const& h : sorted2) {
        names2.push_back(std::string(h.getTestCaseInfo().name));
    }

    EXPECT_EQ(names1, names2);
}

// Test: Destruction of TestRegistry doesn't cause issues
TEST_F(TestRegistryTest_1019, DestructionAfterRegistration_1019) {
    auto registry = std::make_unique<TestRegistry>();

    for (int i = 0; i < 3; ++i) {
        auto info = makeTestCaseInfo("DestrTest" + std::to_string(i), "",
                                      SourceLineInfo("test.cpp", static_cast<std::size_t>(i + 1)));
        auto invoker = Detail::make_unique<MockTestInvoker>();
        registry->registerTest(std::move(info), std::move(invoker));
    }

    // Should not crash
    EXPECT_NO_THROW(registry.reset());
}
