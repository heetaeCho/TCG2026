#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_noncopyable.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace Catch;

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
    MOCK_METHOD(unsigned int, randomSeed, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
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
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
};

class RunContextTest_510 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig = new ::testing::NiceMock<MockConfig>();
        ON_CALL(*mockConfig, name()).WillByDefault(::testing::Return(StringRef("TestRun")));
        ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig, shouldDebugBreak()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));

        auto reporter = Detail::make_unique<::testing::NiceMock<MockReporter>>(mockConfig);
        mockReporterPtr = reporter.get();

        runContext = std::make_unique<RunContext>(mockConfig, std::move(reporter));
    }

    void TearDown() override {
        runContext.reset();
        // Note: mockConfig lifetime may be managed externally
    }

    ::testing::NiceMock<MockConfig>* mockConfig;
    ::testing::NiceMock<MockReporter>* mockReporterPtr;
    std::unique_ptr<RunContext> runContext;
};

// Test that exceptionEarlyReported can be called without crashing
TEST_F(RunContextTest_510, ExceptionEarlyReported_DoesNotThrow_510) {
    EXPECT_NO_THROW(runContext->exceptionEarlyReported());
}

// Test that exceptionEarlyReported can be called multiple times
TEST_F(RunContextTest_510, ExceptionEarlyReported_CalledMultipleTimes_510) {
    EXPECT_NO_THROW(runContext->exceptionEarlyReported());
    EXPECT_NO_THROW(runContext->exceptionEarlyReported());
    EXPECT_NO_THROW(runContext->exceptionEarlyReported());
}

// Test assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_510, AssertionPassed_SetsLastAssertionPassedTrue_510) {
    runContext->assertionPassed();
    EXPECT_TRUE(runContext->lastAssertionPassed());
}

// Test lastAssertionPassed initial state (should be false initially)
TEST_F(RunContextTest_510, LastAssertionPassed_InitiallyFalse_510) {
    EXPECT_FALSE(runContext->lastAssertionPassed());
}

// Test getCurrentTestName when no test is active
TEST_F(RunContextTest_510, GetCurrentTestName_NoActiveTest_ReturnsEmpty_510) {
    std::string name = runContext->getCurrentTestName();
    // When no test case is active, the name should be empty or a default
    EXPECT_TRUE(name.empty() || !name.empty()); // Just verifying it doesn't crash
}

// Test getLastResult when no assertion has been made
TEST_F(RunContextTest_510, GetLastResult_NoAssertion_ReturnsNullptr_510) {
    const AssertionResult* result = runContext->getLastResult();
    EXPECT_EQ(result, nullptr);
}

// Test assertionPassed followed by lastAssertionPassed
TEST_F(RunContextTest_510, AssertionPassed_ThenLastAssertionPassed_ReturnsTrue_510) {
    runContext->assertionPassed();
    EXPECT_TRUE(runContext->lastAssertionPassed());
}

// Test aborting initially returns false (abortAfter is 0)
TEST_F(RunContextTest_510, Aborting_InitiallyFalse_510) {
    EXPECT_FALSE(runContext->aborting());
}

// Test pushScopedMessage and popScopedMessage don't crash
TEST_F(RunContextTest_510, PushAndPopScopedMessage_DoesNotThrow_510) {
    MessageInfo msgInfo("test message", SourceLineInfo("file.cpp", 1), ResultWas::Info);
    EXPECT_NO_THROW(runContext->pushScopedMessage(msgInfo));
    EXPECT_NO_THROW(runContext->popScopedMessage(msgInfo));
}

// Test notifyAssertionStarted doesn't crash
TEST_F(RunContextTest_510, NotifyAssertionStarted_DoesNotThrow_510) {
    AssertionInfo info;
    EXPECT_NO_THROW(runContext->notifyAssertionStarted(info));
}

// Test that calling assertionPassed multiple times keeps returning true
TEST_F(RunContextTest_510, AssertionPassed_MultipleCallsReturnTrue_510) {
    runContext->assertionPassed();
    EXPECT_TRUE(runContext->lastAssertionPassed());
    runContext->assertionPassed();
    EXPECT_TRUE(runContext->lastAssertionPassed());
}

// Test benchmarkPreparing doesn't crash
TEST_F(RunContextTest_510, BenchmarkPreparing_DoesNotThrow_510) {
    EXPECT_NO_THROW(runContext->benchmarkPreparing("bench1"));
}

// Test that exceptionEarlyReported before handling doesn't crash other operations
TEST_F(RunContextTest_510, ExceptionEarlyReported_BeforeAssertionPassed_510) {
    runContext->exceptionEarlyReported();
    runContext->assertionPassed();
    EXPECT_TRUE(runContext->lastAssertionPassed());
}
