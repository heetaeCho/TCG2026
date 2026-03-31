#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/reporters/catch_reporter_event_listener.hpp"

#include <string>
#include <memory>
#include <vector>

using namespace Catch;
using ::testing::_;

namespace {

// A minimal mock/stub reporter that implements the IEventListener interface
class StubReporter : public EventListenerBase {
public:
    StubReporter(IConfig const* config) : EventListenerBase(config) {}

    void testRunStarting(TestRunInfo const&) override {}
    void testRunEnded(TestRunStats const&) override {}
    void testCaseStarting(TestCaseInfo const&) override {}
    void testCaseEnded(TestCaseStats const&) override {}
    void sectionStarting(SectionInfo const&) override {}
    void sectionEnded(SectionStats const&) override {}
    void assertionStarting(AssertionInfo const&) override {}
    void assertionEnded(AssertionStats const&) override {}
};

// Helper to create a RunContext with minimal configuration
class RunContextTest_497 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a valid IConfig. We'll try to use Catch2's own mechanisms.
        // This requires careful setup.
    }

    void TearDown() override {
    }
};

} // anonymous namespace

// Test that RunContext can be constructed and destroyed without crashing
TEST_F(RunContextTest_497, ConstructAndDestruct_497) {
    // Create a minimal config
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    // Construct RunContext - should not throw
    EXPECT_NO_THROW({
        RunContext context(&config, CATCH_MOVE(reporterPtr));
    });
}

// Test getCurrentTestName returns empty string when no test case is active
TEST_F(RunContextTest_497, GetCurrentTestNameNoActiveTest_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    std::string name = context.getCurrentTestName();
    // When no test case is active, the name should be empty
    EXPECT_TRUE(name.empty());
}

// Test lastAssertionPassed returns false initially
TEST_F(RunContextTest_497, LastAssertionPassedInitiallyFalse_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test assertionPassed sets lastAssertionPassed to true
TEST_F(RunContextTest_497, AssertionPassedSetsFlag_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test aborting returns false by default (no abort threshold configured, no failures)
TEST_F(RunContextTest_497, AbortingReturnsFalseByDefault_497) {
    ConfigData configData;
    configData.name = "TestRun";
    configData.abortAfter = 0; // No abort limit
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    EXPECT_FALSE(context.aborting());
}

// Test getLastResult returns nullptr when no assertions have been made
TEST_F(RunContextTest_497, GetLastResultNullptrInitially_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    const AssertionResult* result = context.getLastResult();
    EXPECT_EQ(result, nullptr);
}

// Test assertionPassed followed by check
TEST_F(RunContextTest_497, AssertionPassedMultipleCalls_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    // Initially false
    EXPECT_FALSE(context.lastAssertionPassed());

    // After assertionPassed
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());

    // Call again - should still be true
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test with includeSuccessfulResults config
TEST_F(RunContextTest_497, ConstructWithShowSuccessConfig_497) {
    ConfigData configData;
    configData.name = "TestRunWithSuccess";
    configData.showSuccessfulTests = true;
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    EXPECT_NO_THROW({
        RunContext context(&config, CATCH_MOVE(reporterPtr));
    });
}

// Test aborting with abort threshold set but no failures
TEST_F(RunContextTest_497, AbortingWithThresholdNoFailures_497) {
    ConfigData configData;
    configData.name = "TestRun";
    configData.abortAfter = 3; // Abort after 3 failures
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    // No failures yet, should not be aborting
    EXPECT_FALSE(context.aborting());
}

// Test exceptionEarlyReported doesn't crash
TEST_F(RunContextTest_497, ExceptionEarlyReportedNoCrash_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    EXPECT_NO_THROW(context.exceptionEarlyReported());
}

// Test notifyAssertionStarted doesn't crash
TEST_F(RunContextTest_497, NotifyAssertionStartedNoCrash_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    EXPECT_NO_THROW(context.notifyAssertionStarted(info));
}

// Test benchmarkPreparing doesn't crash
TEST_F(RunContextTest_497, BenchmarkPreparingNoCrash_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    EXPECT_NO_THROW(context.benchmarkPreparing("BenchmarkTest"));
}

// Test benchmarkFailed doesn't crash
TEST_F(RunContextTest_497, BenchmarkFailedNoCrash_497) {
    ConfigData configData;
    configData.name = "TestRun";
    Config config(configData);

    auto reporter = Catch::Detail::make_unique<StubReporter>(&config);
    IEventListenerPtr reporterPtr(CATCH_MOVE(reporter));

    RunContext context(&config, CATCH_MOVE(reporterPtr));

    EXPECT_NO_THROW(context.benchmarkFailed("some error"));
}
