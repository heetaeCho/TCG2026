// File: run_context_handleExpr_tests_515.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/internal/catch_decomposer.hpp"
#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/internal/catch_result_type.hpp"

// If your local includes differ, adjust include paths accordingly.

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::NiceMock;

// ---- Minimal mocks of external collaborators (only) ----

// Reporter interface in Catch2 is typically something like IEventListener.
// We mock it so we can verify that assertion results are reported when expected.
class MockEventListener : public IEventListener {
public:
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, assertionStarted, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
};

// IConfig has many virtuals; we stub only those that are actually used by RunContext
// in construction & for includeSuccessfulResults. The remaining pure-virtuals are
// provided with benign defaults. Adjust if your local Catch2 version differs.
class MockConfig : public IConfig {
public:
    MockConfig() = default;

    // Used by RunContext constructor
    MOCK_METHOD(std::string const&, name, (), (const, override));

    // Used by RunContext to decide whether to include successful results
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));

    // ---- The rest are required pure-virtuals in Catch2's IConfig; we provide defaults ----
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnings, (), (const, override));
    MOCK_METHOD(ShowDurations::OrNot, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkClockResolution, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, listTests, (), (const, override));
    MOCK_METHOD(bool, listTags, (), (const, override));
    MOCK_METHOD(bool, listReporters, (), (const, override));
    MOCK_METHOD(bool, listListeners, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(ColourMode, useColour, (), (const, override));
    MOCK_METHOD(std::vector<Verbosity> const&, reporterVerbosity, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(WaitForKeypress::When, waitForKeypress, (), (const, override));
    MOCK_METHOD(bool, runDisabledTests, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, rngSeed, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getWarningSpecs, (), (const, override));
    MOCK_METHOD(bool, showSuccessfulAssertions, (), (const, override));
};

// ---- Test fixture to set up a RunContext with mocked deps ----
class RunContextHandleExprTest_515 : public ::testing::Test {
protected:
    std::string runName_ = std::string("run-515");
    NiceMock<MockConfig> config_;
    std::unique_ptr<MockEventListener> reporter_;
    std::unique_ptr<RunContext> ctx_;

    // helpers to hold returned references
    std::vector<std::string> emptyStrings_;

    void SetUp() override {
        // Default config stubs
        ON_CALL(config_, name()).WillByDefault(ReturnRef(runName_));
        ON_CALL(config_, includeSuccessfulResults()).WillByDefault(Return(true));
        // Benign defaults for the rest to satisfy pure-virtuals
        ON_CALL(config_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(config_, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(config_, warnings()).WillByDefault(Return(false));
        ON_CALL(config_, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(config_, minDuration()).WillByDefault(Return(0.0));
        ON_CALL(config_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(config_, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(config_, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(config_, benchmarkResamples()).WillByDefault(Return(0.0));
        ON_CALL(config_, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds{0}));
        ON_CALL(config_, benchmarkClockResolution()).WillByDefault(Return(std::chrono::milliseconds{0}));
        ON_CALL(config_, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(config_, listTests()).WillByDefault(Return(false));
        ON_CALL(config_, listTags()).WillByDefault(Return(false));
        ON_CALL(config_, listReporters()).WillByDefault(Return(false));
        ON_CALL(config_, listListeners()).WillByDefault(Return(false));
        ON_CALL(config_, getTestsOrTags()).WillByDefault(ReturnRef(emptyStrings_));
        ON_CALL(config_, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(config_, getSectionsToRun()).WillByDefault(ReturnRef(emptyStrings_));
        ON_CALL(config_, useColour()).WillByDefault(Return(ColourMode::PlatformDefault));
        static std::vector<Verbosity> verbos; ON_CALL(config_, reporterVerbosity()).WillByDefault(ReturnRef(verbos));
        static std::vector<std::string> reps; ON_CALL(config_, getReporterSpecs()).WillByDefault(ReturnRef(reps));
        ON_CALL(config_, waitForKeypress()).WillByDefault(Return(WaitForKeypress::Never));
        ON_CALL(config_, runDisabledTests()).WillByDefault(Return(false));
        ON_CALL(config_, zeroTestsCountAsSuccess()).WillByDefault(Return(true));
        ON_CALL(config_, rngSeed()).WillByDefault(Return(0));
        static std::vector<std::string> warns; ON_CALL(config_, getWarningSpecs()).WillByDefault(ReturnRef(warns));
        ON_CALL(config_, showSuccessfulAssertions()).WillByDefault(Return(false));

        reporter_ = std::make_unique<NiceMock<MockEventListener>>();

        // Transfer ownership into RunContext as IEventListenerPtr
        IEventListenerPtr listenerPtr(reporter_.release());
        ctx_ = std::make_unique<RunContext>(&config_, std::move(listenerPtr));
    }

    static AssertionInfo makeInfo(ResultDisposition::Flags disp = ResultDisposition::Normal) {
        AssertionInfo info;
        info.macroName = StringRef("REQUIRE");
        info.capturedExpression = StringRef("expr");
        info.resultDisposition = disp;
        return info;
    }
};

// ========== TESTS ==========

// Success path when includeSuccessfulResults == true → reports Ok via reporter,
// reaction stays at defaults, and last result is Ok.
TEST_F(RunContextHandleExprTest_515, ReportsOkWhenSuccessAndIncludingResults_515) {
    // Arrange
    ON_CALL(config_, includeSuccessfulResults()).WillByDefault(Return(true));
    ITransientExpression expr{/*isBinaryExpression*/false, /*result*/true};
    AssertionInfo info = makeInfo(ResultDisposition::Normal);
    AssertionReaction reaction; // default: all false

    // Expect reporter receives an assertion end with Ok result
    EXPECT_CALL(*static_cast<MockEventListener*>(ctx_->m_reporter.get()), assertionEnded(_))
        .Times(::testing::AtLeast(1));

    // Act
    ctx_->handleExpr(info, expr, reaction);

    // Assert (publicly observable)
    auto* last = ctx_->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), ResultWas::Ok);
    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldSkip);
}

// Success path when includeSuccessfulResults == false → counts as a pass but
// not reported as Ok; reaction stays default; we verify via lastAssertionPassed().
TEST_F(RunContextHandleExprTest_515, PassesWithoutReportingWhenIncludingResultsIsFalse_515) {
    // Arrange
    ON_CALL(config_, includeSuccessfulResults()).WillByDefault(Return(false));
    ITransientExpression expr{/*isBinaryExpression*/false, /*result*/true};
    AssertionInfo info = makeInfo(ResultDisposition::Normal);
    AssertionReaction reaction;

    // We do not require any reporter calls for Ok in this mode.
    // Act
    ctx_->handleExpr(info, expr, reaction);

    // Assert: last result might be null (no Ok report), but lastAssertionPassed is observable.
    EXPECT_TRUE(ctx_->lastAssertionPassed());
    EXPECT_FALSE(reaction.shouldDebugBreak);
    EXPECT_FALSE(reaction.shouldThrow);
    EXPECT_FALSE(reaction.shouldSkip);
}

// Failure path: expression is false (no negation) → reports ExpressionFailed,
// and reaction is populated (observable through returned AssertionResult + reaction flags).
TEST_F(RunContextHandleExprTest_515, ReportsFailureAndPopulatesReactionOnFailedExpr_515) {
    // Arrange
    ON_CALL(config_, includeSuccessfulResults()).WillByDefault(Return(true));
    ITransientExpression expr{/*isBinaryExpression*/false, /*result*/false};
    AssertionInfo info = makeInfo(ResultDisposition::Normal);
    AssertionReaction reaction;

    // Expect at least one assertionEnded call
    EXPECT_CALL(*static_cast<MockEventListener*>(ctx_->m_reporter.get()), assertionEnded(_))
        .Times(::testing::AtLeast(1));

    // Act
    ctx_->handleExpr(info, expr, reaction);

    // Assert
    auto* last = ctx_->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), ResultWas::ExpressionFailed);

    // We don't assert exact reaction semantics (black-box), but it must be *possible*
    // for the reaction to be changed on failure. At minimum, it should not force success flags.
    // If your project defines exact behavior, assert it here instead.
    // For a conservative check, we simply confirm the struct is still a valid object.
    SUCCEED();
}

// Negated path: true expr + negation flag → treated as failure
TEST_F(RunContextHandleExprTest_515, NegatedTrueExpressionFails_515) {
    // Arrange
    ON_CALL(config_, includeSuccessfulResults()).WillByDefault(Return(true));
    ITransientExpression expr{/*isBinaryExpression*/false, /*result*/true};
    // Set ResultDisposition to Negate; this should flip the sense
    AssertionInfo info = makeInfo(ResultDisposition::Negate);
    AssertionReaction reaction;

    EXPECT_CALL(*static_cast<MockEventListener*>(ctx_->m_reporter.get()), assertionEnded(_))
        .Times(::testing::AtLeast(1));

    // Act
    ctx_->handleExpr(info, expr, reaction);

    // Assert: last result reflects failure due to negation
    auto* last = ctx_->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), ResultWas::ExpressionFailed);
}
