#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>
#include <memory>

using namespace Catch;
using namespace testing;

namespace {

// Mock reporter to capture assertions
class MockReporter : public EventListenerBase {
public:
    MockReporter(IConfig const* config) : EventListenerBase(config) {}

    struct CapturedAssertion {
        ResultWas::OfType resultType;
        std::string message;
        std::string macroName;
        std::string expression;
    };

    std::vector<CapturedAssertion> capturedAssertions;

    void assertionEnded(AssertionStats const& stats) override {
        CapturedAssertion captured;
        captured.resultType = stats.assertionResult.getResultType();
        captured.message = std::string(stats.assertionResult.getMessage());
        captured.macroName = std::string(stats.assertionResult.getTestMacroName());
        captured.expression = stats.assertionResult.getExpression();
        capturedAssertions.push_back(captured);
    }

    void testRunStarting(TestRunInfo const&) override {}
    void testRunEnded(TestRunStats const&) override {}
    void testCaseStarting(TestCaseInfo const&) override {}
    void testCaseEnded(TestCaseStats const&) override {}
    void sectionStarting(SectionInfo const&) override {}
    void sectionEnded(SectionStats const&) override {}
};

// A minimal config for testing
class TestConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_catch_sr; }
    bool includeSuccessfulResults() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    bool shouldDebugBreak() const override { return false; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    TestSpec const& testSpec() const override {
        static TestSpec spec;
        return spec;
    }
    std::vector<ReporterSpec> const& getReporterSpecs() const override {
        static std::vector<ReporterSpec> empty;
        return empty;
    }
    std::vector<ProcessedReporterSpec> const& getProcessedReporterSpecs() const override {
        static std::vector<ProcessedReporterSpec> empty;
        return empty;
    }
    IStream const* getReporterOutputStream(std::size_t) const override { return nullptr; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
};

} // anonymous namespace

class RunContextTest_519 : public ::testing::Test {
protected:
    void SetUp() override {
        config_ = std::make_unique<TestConfig>();
        reporter_ = new MockReporter(config_.get());
        // We need a shared reporter pointer
        IEventListenerPtr reporterPtr(reporter_);
        runContext_ = std::make_unique<RunContext>(config_.get(), CATCH_MOVE(reporterPtr));
    }

    void TearDown() override {
        runContext_.reset();
        config_.reset();
    }

    std::unique_ptr<TestConfig> config_;
    MockReporter* reporter_ = nullptr; // owned by runContext_
    std::unique_ptr<RunContext> runContext_;
};

TEST_F(RunContextTest_519, HandleIncompleteUpdatesLastResult_519) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "some_expression"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
}

TEST_F(RunContextTest_519, HandleIncompleteMessageIsCorrect_519) {
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(std::string(lastResult->getMessage()),
              "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE");
}

TEST_F(RunContextTest_519, HandleIncompleteHasMessage_519) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "test"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_TRUE(lastResult->hasMessage());
}

TEST_F(RunContextTest_519, HandleIncompleteResultNotOk_519) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "x == y"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_FALSE(lastResult->isOk());
}

TEST_F(RunContextTest_519, HandleIncompleteResultNotSucceeded_519) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "a > b"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_FALSE(lastResult->succeeded());
}

TEST_F(RunContextTest_519, HandleIncompleteLastAssertionNotPassed_519) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "condition"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    EXPECT_FALSE(runContext_->lastAssertionPassed());
}

TEST_F(RunContextTest_519, HandleIncompleteReportsToReporter_519) {
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "foo()"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    ASSERT_FALSE(reporter_->capturedAssertions.empty());
    EXPECT_EQ(reporter_->capturedAssertions.back().resultType, ResultWas::ThrewException);
    EXPECT_EQ(reporter_->capturedAssertions.back().message,
              "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE");
}

TEST_F(RunContextTest_519, HandleIncompleteWithEmptyMacroName_519) {
    AssertionInfo info;
    info.macroName = StringRef();
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
}

TEST_F(RunContextTest_519, HandleIncompleteWithEmptyExpression_519) {
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = StringRef();
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
    EXPECT_EQ(std::string(lastResult->getMessage()),
              "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE");
}

TEST_F(RunContextTest_519, HandleIncompleteMultipleCalls_519) {
    AssertionInfo info1;
    info1.macroName = "REQUIRE"_catch_sr;
    info1.capturedExpression = "first"_catch_sr;
    info1.resultDisposition = ResultDisposition::Normal;

    AssertionInfo info2;
    info2.macroName = "CHECK"_catch_sr;
    info2.capturedExpression = "second"_catch_sr;
    info2.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info1);
    runContext_->handleIncomplete(info2);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
    // The last result should correspond to the second call
    EXPECT_EQ(std::string(lastResult->getMessage()),
              "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE");
}

TEST_F(RunContextTest_519, HandleIncompleteResetsAssertionInfo_519) {
    // After handleIncomplete, the internal assertion info should be reset.
    // We verify this indirectly: calling getLastResult should still work.
    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "test_expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    runContext_->handleIncomplete(info);

    // The last assertion should not have passed
    EXPECT_FALSE(runContext_->lastAssertionPassed());

    // Verify we can get the last result without issues
    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
}

TEST_F(RunContextTest_519, HandleIncompleteWithContinueOnFailure_519) {
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "val"_catch_sr;
    info.resultDisposition = ResultDisposition::ContinueOnFailure;

    runContext_->handleIncomplete(info);

    const AssertionResult* lastResult = runContext_->getLastResult();
    ASSERT_NE(lastResult, nullptr);
    EXPECT_EQ(lastResult->getResultType(), ResultWas::ThrewException);
    EXPECT_EQ(std::string(lastResult->getMessage()),
              "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE");
}
