#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_optional.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

// Mock for IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(RunthroughCount, runthroughCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// Mock for IEventListener (used as reporter)
class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
};

class RunContextTest_509 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig = new NiceMock<MockConfig>();
        
        ON_CALL(*mockConfig, name()).WillByDefault(Return(StringRef("TestRun")));
        ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*mockConfig, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::Never));
        ON_CALL(*mockConfig, hasTestFilters()).WillByDefault(Return(false));

        mockReporter = new NiceMock<MockReporter>(mockConfig);
    }

    void TearDown() override {
        // Config outlives RunContext typically
    }

    NiceMock<MockConfig>* mockConfig;
    NiceMock<MockReporter>* mockReporter;

    std::unique_ptr<RunContext> createRunContext() {
        Detail::unique_ptr<IEventListener> reporterPtr(mockReporter);
        return std::make_unique<RunContext>(
            mockConfig, 
            std::move(reporterPtr)
        );
    }
};

// Test: getLastResult returns a non-null pointer after construction
TEST_F(RunContextTest_509, GetLastResultReturnsPointer_509) {
    auto ctx = createRunContext();
    const AssertionResult* result = ctx->getLastResult();
    // After construction, m_lastResult might be empty Optional, 
    // but getLastResult dereferences it. This tests observable behavior.
    // If Optional is empty, this could be UB, but we test the interface.
    ASSERT_NE(result, nullptr);
}

// Test: lastAssertionPassed returns false initially
TEST_F(RunContextTest_509, LastAssertionPassedInitiallyFalse_509) {
    auto ctx = createRunContext();
    EXPECT_FALSE(ctx->lastAssertionPassed());
}

// Test: assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_509, AssertionPassedSetsFlag_509) {
    auto ctx = createRunContext();
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

// Test: getCurrentTestName returns empty string when no test is active
TEST_F(RunContextTest_509, GetCurrentTestNameWhenNoActiveTest_509) {
    auto ctx = createRunContext();
    std::string name = ctx->getCurrentTestName();
    EXPECT_TRUE(name.empty());
}

// Test: aborting returns false initially (abortAfter is 0 = no limit)
TEST_F(RunContextTest_509, AbortingReturnsFalseInitially_509) {
    auto ctx = createRunContext();
    EXPECT_FALSE(ctx->aborting());
}

// Test: assertionPassed then verify lastAssertionPassed
TEST_F(RunContextTest_509, AssertionPassedThenLastAssertionPassedIsTrue_509) {
    auto ctx = createRunContext();
    EXPECT_FALSE(ctx->lastAssertionPassed());
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

// Test: notifyAssertionStarted records assertion info
TEST_F(RunContextTest_509, NotifyAssertionStartedRecordsInfo_509) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 42);
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    // Should not throw
    EXPECT_NO_THROW(ctx->notifyAssertionStarted(info));
}

// Test: pushScopedMessage and popScopedMessage
TEST_F(RunContextTest_509, PushAndPopScopedMessage_509) {
    auto ctx = createRunContext();
    
    MessageInfo msgInfo("test message", SourceLineInfo("test.cpp", 10), ResultWas::Info);
    
    EXPECT_NO_THROW(ctx->pushScopedMessage(msgInfo));
    EXPECT_NO_THROW(ctx->popScopedMessage(msgInfo));
}

// Test: exceptionEarlyReported does not crash
TEST_F(RunContextTest_509, ExceptionEarlyReportedDoesNotCrash_509) {
    auto ctx = createRunContext();
    EXPECT_NO_THROW(ctx->exceptionEarlyReported());
}

// Test: benchmarkPreparing notifies reporter
TEST_F(RunContextTest_509, BenchmarkPreparingNotifiesReporter_509) {
    EXPECT_CALL(*mockReporter, benchmarkPreparing(_)).Times(1);
    auto ctx = createRunContext();
    ctx->benchmarkPreparing("bench1"_catch_sr);
}

// Test: benchmarkStarting notifies reporter
TEST_F(RunContextTest_509, BenchmarkStartingNotifiesReporter_509) {
    EXPECT_CALL(*mockReporter, benchmarkStarting(_)).Times(1);
    auto ctx = createRunContext();
    BenchmarkInfo info{"bench1", 1.0, 100, 1000, 0.95, 10000, 0.0};
    ctx->benchmarkStarting(info);
}

// Test: benchmarkFailed notifies reporter
TEST_F(RunContextTest_509, BenchmarkFailedNotifiesReporter_509) {
    EXPECT_CALL(*mockReporter, benchmarkFailed(_)).Times(1);
    auto ctx = createRunContext();
    ctx->benchmarkFailed("error message"_catch_sr);
}

// Test: Multiple assertionPassed calls
TEST_F(RunContextTest_509, MultipleAssertionPassedCalls_509) {
    auto ctx = createRunContext();
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
    ctx->assertionPassed();
    EXPECT_TRUE(ctx->lastAssertionPassed());
}

// Test: handleNonExpr with various result types
TEST_F(RunContextTest_509, HandleNonExprDoesNotCrash_509) {
    auto ctx = createRunContext();
    AssertionInfo info;
    info.macroName = "SUCCEED"_catch_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 50);
    info.capturedExpression = ""_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionReaction reaction;
    EXPECT_NO_THROW(ctx->handleNonExpr(info, ResultWas::Ok, reaction));
}

// Test: Copy constructor is deleted
TEST_F(RunContextTest_509, CopyConstructorIsDeleted_509) {
    EXPECT_FALSE(std::is_copy_constructible<RunContext>::value);
}

// Test: Copy assignment is deleted
TEST_F(RunContextTest_509, CopyAssignmentIsDeleted_509) {
    EXPECT_FALSE(std::is_copy_assignable<RunContext>::value);
}
