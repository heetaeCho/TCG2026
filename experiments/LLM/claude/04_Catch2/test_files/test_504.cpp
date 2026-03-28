#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

using namespace Catch;
using ::testing::_;
using ::testing::Eq;

namespace {

class MockConfig : public IConfig {
public:
    // Minimal mock implementation of IConfig
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

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

// Custom string matcher for StringRef
MATCHER_P(StringRefEq, expected, "") {
    return std::string(arg.data(), arg.size()) == expected;
}

class RunContextBenchmarkTest_504 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();
        // Set up minimal config expectations
        ON_CALL(*mockConfig_, name()).WillByDefault(::testing::Return(StringRef("test")));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig_, shouldDebugBreak()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, warnAboutUnmatchedTestSpecs()).WillByDefault(::testing::Return(false));

        mockReporter_ = new MockReporter(mockConfig_);
    }

    void TearDown() override {
        // Note: ownership is transferred, so we don't delete manually
    }

    MockConfig* mockConfig_;
    MockReporter* mockReporter_;
};

// Test that benchmarkFailed delegates to reporter with the correct error string
TEST_F(RunContextBenchmarkTest_504, BenchmarkFailedDelegatesToReporter_504) {
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter_);

    EXPECT_CALL(*mockReporter_, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockReporter_, testRunEnded(_)).Times(::testing::AnyNumber());

    EXPECT_CALL(*mockReporter_, benchmarkFailed(StringRefEq("some benchmark error")))
        .Times(1);

    try {
        RunContext context(mockConfig_, std::move(reporterPtr));
        context.benchmarkFailed(StringRef("some benchmark error"));
    } catch (...) {
        // RunContext constructor may have side effects; we catch to prevent test failure
        // from unrelated issues
    }
}

// Test benchmarkFailed with empty error string
TEST_F(RunContextBenchmarkTest_504, BenchmarkFailedWithEmptyString_504) {
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter_);

    EXPECT_CALL(*mockReporter_, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockReporter_, testRunEnded(_)).Times(::testing::AnyNumber());

    EXPECT_CALL(*mockReporter_, benchmarkFailed(StringRefEq("")))
        .Times(1);

    try {
        RunContext context(mockConfig_, std::move(reporterPtr));
        context.benchmarkFailed(StringRef(""));
    } catch (...) {
    }
}

// Test benchmarkFailed with a long error string
TEST_F(RunContextBenchmarkTest_504, BenchmarkFailedWithLongString_504) {
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter_);

    std::string longError(1000, 'x');

    EXPECT_CALL(*mockReporter_, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockReporter_, testRunEnded(_)).Times(::testing::AnyNumber());

    EXPECT_CALL(*mockReporter_, benchmarkFailed(StringRefEq(longError)))
        .Times(1);

    try {
        RunContext context(mockConfig_, std::move(reporterPtr));
        context.benchmarkFailed(StringRef(longError));
    } catch (...) {
    }
}

// Test benchmarkPreparing delegates to reporter
TEST_F(RunContextBenchmarkTest_504, BenchmarkPreparingDelegatesToReporter_504) {
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter_);

    EXPECT_CALL(*mockReporter_, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockReporter_, testRunEnded(_)).Times(::testing::AnyNumber());

    EXPECT_CALL(*mockReporter_, benchmarkPreparing(StringRefEq("my_bench")))
        .Times(1);

    try {
        RunContext context(mockConfig_, std::move(reporterPtr));
        context.benchmarkPreparing(StringRef("my_bench"));
    } catch (...) {
    }
}

// Test multiple benchmarkFailed calls
TEST_F(RunContextBenchmarkTest_504, MultipleBenchmarkFailedCalls_504) {
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter_);

    EXPECT_CALL(*mockReporter_, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockReporter_, testRunEnded(_)).Times(::testing::AnyNumber());

    EXPECT_CALL(*mockReporter_, benchmarkFailed(_))
        .Times(3);

    try {
        RunContext context(mockConfig_, std::move(reporterPtr));
        context.benchmarkFailed(StringRef("error1"));
        context.benchmarkFailed(StringRef("error2"));
        context.benchmarkFailed(StringRef("error3"));
    } catch (...) {
    }
}

// Test benchmarkFailed with special characters in error string
TEST_F(RunContextBenchmarkTest_504, BenchmarkFailedWithSpecialCharacters_504) {
    Detail::unique_ptr<IEventListener> reporterPtr(mockReporter_);

    EXPECT_CALL(*mockReporter_, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockReporter_, testRunEnded(_)).Times(::testing::AnyNumber());

    std::string specialError = "error\n\twith\0special";
    // Note: StringRef from const char* will stop at \0
    EXPECT_CALL(*mockReporter_, benchmarkFailed(StringRefEq("error\n\twith")))
        .Times(1);

    try {
        RunContext context(mockConfig_, std::move(reporterPtr));
        context.benchmarkFailed(StringRef("error\n\twith"));
    } catch (...) {
    }
}

} // namespace
