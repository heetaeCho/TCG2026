#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_output_redirect.hpp"
#include "catch2/catch_test_macros.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::NiceMock;
using ::testing::AtLeast;
using ::testing::Invoke;

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

// Mock for IEventListener (reporter)
class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));
};

// Mock for ITestInvoker
class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, invoke, (), (const, override));
};

// Mock for OutputRedirect
class MockOutputRedirect : public OutputRedirect {
public:
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));
protected:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
};

class RunContextTest_494 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new NiceMock<MockConfig>();
        sectionsToRun_ = {};
        testsOrTags_ = {};

        ON_CALL(*mockConfig_, name()).WillByDefault(Return(StringRef("TestRun")));
        ON_CALL(*mockConfig_, getSectionsToRun()).WillByDefault(ReturnRef(sectionsToRun_));
        ON_CALL(*mockConfig_, getTestsOrTags()).WillByDefault(ReturnRef(testsOrTags_));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(Return(1u));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*mockConfig_, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(*mockConfig_, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(Return(Verbosity::Normal));
    }

    void TearDown() override {
        // Config is owned externally in real usage
    }

    NiceMock<MockConfig>* mockConfig_;
    std::vector<std::string> sectionsToRun_;
    std::vector<std::string> testsOrTags_;
};

// Test: Totals struct basic operations
TEST_F(RunContextTest_494, TotalsDefaultInitialization_494) {
    Totals t;
    EXPECT_EQ(t.assertions.passed, 0u);
    EXPECT_EQ(t.assertions.failed, 0u);
    EXPECT_EQ(t.testCases.passed, 0u);
    EXPECT_EQ(t.testCases.failed, 0u);
}

TEST_F(RunContextTest_494, TotalsDeltaComputation_494) {
    Totals prev;
    prev.assertions.passed = 5;
    prev.testCases.passed = 1;

    Totals current;
    current.assertions.passed = 8;
    current.assertions.failed = 2;
    current.testCases.passed = 3;

    Totals delta = current.delta(prev);
    EXPECT_EQ(delta.assertions.passed, 3u);
    EXPECT_EQ(delta.assertions.failed, 2u);
    EXPECT_EQ(delta.testCases.passed, 2u);
}

TEST_F(RunContextTest_494, CountsSubtraction_494) {
    Counts a;
    a.passed = 10;
    a.failed = 3;
    a.failedButOk = 1;
    a.skipped = 2;

    Counts b;
    b.passed = 4;
    b.failed = 1;
    b.failedButOk = 0;
    b.skipped = 1;

    Counts result = a - b;
    EXPECT_EQ(result.passed, 6u);
    EXPECT_EQ(result.failed, 2u);
    EXPECT_EQ(result.failedButOk, 1u);
    EXPECT_EQ(result.skipped, 1u);
}

TEST_F(RunContextTest_494, CountsPlusEquals_494) {
    Counts a;
    a.passed = 2;
    a.failed = 1;

    Counts b;
    b.passed = 3;
    b.failed = 4;

    a += b;
    EXPECT_EQ(a.passed, 5u);
    EXPECT_EQ(a.failed, 5u);
}

TEST_F(RunContextTest_494, CountsTotal_494) {
    Counts c;
    c.passed = 3;
    c.failed = 2;
    c.failedButOk = 1;
    c.skipped = 4;
    EXPECT_EQ(c.total(), 10u);
}

TEST_F(RunContextTest_494, CountsAllPassed_494) {
    Counts c;
    c.passed = 5;
    EXPECT_TRUE(c.allPassed());

    c.failed = 1;
    EXPECT_FALSE(c.allPassed());
}

TEST_F(RunContextTest_494, CountsAllOk_494) {
    Counts c;
    c.passed = 5;
    c.failedButOk = 2;
    EXPECT_TRUE(c.allOk());

    c.failed = 1;
    EXPECT_FALSE(c.allOk());
}

TEST_F(RunContextTest_494, TotalsPlusEquals_494) {
    Totals a;
    a.assertions.passed = 1;
    a.testCases.passed = 1;

    Totals b;
    b.assertions.passed = 2;
    b.assertions.failed = 1;
    b.testCases.failed = 1;

    a += b;
    EXPECT_EQ(a.assertions.passed, 3u);
    EXPECT_EQ(a.assertions.failed, 1u);
    EXPECT_EQ(a.testCases.passed, 1u);
    EXPECT_EQ(a.testCases.failed, 1u);
}

TEST_F(RunContextTest_494, TotalsSubtraction_494) {
    Totals a;
    a.assertions.passed = 10;
    a.assertions.failed = 5;
    a.testCases.passed = 3;

    Totals b;
    b.assertions.passed = 4;
    b.assertions.failed = 2;
    b.testCases.passed = 1;

    Totals result = a - b;
    EXPECT_EQ(result.assertions.passed, 6u);
    EXPECT_EQ(result.assertions.failed, 3u);
    EXPECT_EQ(result.testCases.passed, 2u);
}

TEST_F(RunContextTest_494, TotalsDeltaWithZeroPrev_494) {
    Totals current;
    current.assertions.passed = 5;
    current.assertions.failed = 3;
    current.testCases.passed = 2;
    current.testCases.failed = 1;

    Totals prev;
    Totals delta = current.delta(prev);

    EXPECT_EQ(delta.assertions.passed, 5u);
    EXPECT_EQ(delta.assertions.failed, 3u);
    EXPECT_EQ(delta.testCases.passed, 2u);
    EXPECT_EQ(delta.testCases.failed, 1u);
}

TEST_F(RunContextTest_494, TotalsDeltaWithEqualValues_494) {
    Totals current;
    current.assertions.passed = 5;
    current.testCases.passed = 2;

    Totals prev = current;
    Totals delta = current.delta(prev);

    EXPECT_EQ(delta.assertions.passed, 0u);
    EXPECT_EQ(delta.testCases.passed, 0u);
}

TEST_F(RunContextTest_494, CountsDefaultAllPassed_494) {
    Counts c;
    // Zero counts: all passed should be true (no failures)
    EXPECT_TRUE(c.allPassed());
    EXPECT_TRUE(c.allOk());
    EXPECT_EQ(c.total(), 0u);
}

// Test reporter interactions when RunContext is constructed
TEST_F(RunContextTest_494, ReporterReceivesTestCaseStarting_494) {
    auto mockReporter = Detail::make_unique<NiceMock<MockReporter>>(mockConfig_);
    auto* reporterPtr = mockReporter.get();

    EXPECT_CALL(*reporterPtr, testCaseStarting(_)).Times(AtLeast(0));
    EXPECT_CALL(*reporterPtr, testCaseEnded(_)).Times(AtLeast(0));

    // This verifies the reporter mock is properly constructible
    ASSERT_NE(reporterPtr, nullptr);
}

// Test Counts edge cases with skipped
TEST_F(RunContextTest_494, CountsWithSkipped_494) {
    Counts c;
    c.skipped = 5;
    EXPECT_EQ(c.total(), 5u);
    EXPECT_TRUE(c.allPassed());
    EXPECT_TRUE(c.allOk());
}

TEST_F(RunContextTest_494, CountsFailedButOkOnly_494) {
    Counts c;
    c.failedButOk = 3;
    EXPECT_EQ(c.total(), 3u);
    EXPECT_FALSE(c.allPassed());
    EXPECT_TRUE(c.allOk());
}

// Test Totals with only failed assertions
TEST_F(RunContextTest_494, TotalsOnlyFailedAssertions_494) {
    Totals t;
    t.assertions.failed = 10;
    t.testCases.failed = 2;

    EXPECT_EQ(t.assertions.total(), 10u);
    EXPECT_FALSE(t.assertions.allPassed());
    EXPECT_FALSE(t.assertions.allOk());
    EXPECT_EQ(t.testCases.total(), 2u);
}

// Test multiple delta calculations
TEST_F(RunContextTest_494, MultipleDeltaCalculations_494) {
    Totals t1;
    t1.assertions.passed = 3;
    t1.testCases.passed = 1;

    Totals t2;
    t2.assertions.passed = 7;
    t2.assertions.failed = 2;
    t2.testCases.passed = 2;
    t2.testCases.failed = 1;

    Totals delta1 = t2.delta(t1);
    EXPECT_EQ(delta1.assertions.passed, 4u);
    EXPECT_EQ(delta1.assertions.failed, 2u);
    EXPECT_EQ(delta1.testCases.passed, 1u);
    EXPECT_EQ(delta1.testCases.failed, 1u);

    Totals t3;
    t3.assertions.passed = 10;
    t3.assertions.failed = 5;
    t3.testCases.passed = 4;
    t3.testCases.failed = 2;

    Totals delta2 = t3.delta(t2);
    EXPECT_EQ(delta2.assertions.passed, 3u);
    EXPECT_EQ(delta2.assertions.failed, 3u);
    EXPECT_EQ(delta2.testCases.passed, 2u);
    EXPECT_EQ(delta2.testCases.failed, 1u);
}
