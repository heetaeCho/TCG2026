#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_test_macro_impl.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

using namespace Catch;

namespace {

// Mock reporter/listener that does nothing
class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    void testRunStarting(TestRunInfo const&) override {}
    void testRunEnded(TestRunStats const&) override {}
    void testCaseStarting(TestCaseInfo const&) override {}
    void testCaseEnded(TestCaseStats const&) override {}
    void testCasePartialStarting(TestCaseInfo const&, uint64_t) override {}
    void testCasePartialEnded(TestCaseStats const&, uint64_t) override {}
    void sectionStarting(SectionInfo const&) override {}
    void sectionEnded(SectionStats const&) override {}
    void assertionStarting(AssertionInfo const&) override {}
    void assertionEnded(AssertionResult const&) override {}
    void benchmarkPreparing(StringRef) override {}
    void benchmarkStarting(BenchmarkInfo const&) override {}
    void benchmarkEnded(BenchmarkStats<> const&) override {}
    void benchmarkFailed(StringRef) override {}
    void fatalErrorEncountered(StringRef) override {}
    void noMatchingTestCases(StringRef) override {}
    void reportInvalidTestSpec(StringRef) override {}
    void testGroupStarting(GroupInfo const&) override {}
    void testGroupEnded(TestGroupStats const&) override {}
    void listTests(std::vector<TestCaseHandle> const&) override {}
    void listReporters(std::vector<ReporterDescription> const&) override {}
    void listListeners(std::vector<ListenerDescription> const&) override {}
    void listTags(std::vector<TagInfo> const&) override {}
};

// Helper to create a minimal config
class TestConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"; }
    bool includeSuccessfulResults() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::Never; }
    double minDuration() const override { return -1.0; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
};

} // anonymous namespace

class RunContextTest_508 : public ::testing::Test {
protected:
    void SetUp() override {
        config_ = std::make_unique<TestConfig>();
    }

    std::unique_ptr<TestConfig> config_;
};

// Test that getCurrentTestName returns empty string when no active test case
TEST_F(RunContextTest_508, GetCurrentTestName_NoActiveTestCase_ReturnsEmptyString_508) {
    auto reporter = Detail::make_unique<MockReporter>(config_.get());
    IEventListenerPtr reporterPtr(std::move(reporter));
    
    RunContext context(config_.get(), std::move(reporterPtr));
    
    std::string name = context.getCurrentTestName();
    EXPECT_TRUE(name.empty());
    EXPECT_EQ(name, std::string());
}

// Test that lastAssertionPassed returns false initially (no assertions have been made)
TEST_F(RunContextTest_508, LastAssertionPassed_Initially_ReturnsFalse_508) {
    auto reporter = Detail::make_unique<MockReporter>(config_.get());
    IEventListenerPtr reporterPtr(std::move(reporter));
    
    RunContext context(config_.get(), std::move(reporterPtr));
    
    EXPECT_FALSE(context.lastAssertionPassed());
}

// Test that assertionPassed sets last assertion as passed
TEST_F(RunContextTest_508, AssertionPassed_SetsLastAssertionPassedTrue_508) {
    auto reporter = Detail::make_unique<MockReporter>(config_.get());
    IEventListenerPtr reporterPtr(std::move(reporter));
    
    RunContext context(config_.get(), std::move(reporterPtr));
    
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test that getLastResult returns nullptr when no assertions have been made
TEST_F(RunContextTest_508, GetLastResult_NoAssertions_ReturnsNullptr_508) {
    auto reporter = Detail::make_unique<MockReporter>(config_.get());
    IEventListenerPtr reporterPtr(std::move(reporter));
    
    RunContext context(config_.get(), std::move(reporterPtr));
    
    const AssertionResult* result = context.getLastResult();
    EXPECT_EQ(result, nullptr);
}

// Test that aborting returns false initially
TEST_F(RunContextTest_508, Aborting_Initially_ReturnsFalse_508) {
    auto reporter = Detail::make_unique<MockReporter>(config_.get());
    IEventListenerPtr reporterPtr(std::move(reporter));
    
    RunContext context(config_.get(), std::move(reporterPtr));
    
    EXPECT_FALSE(context.aborting());
}

// Test that multiple calls to assertionPassed maintain state
TEST_F(RunContextTest_508, AssertionPassed_MultipleCalls_RemainsPassed_508) {
    auto reporter = Detail::make_unique<MockReporter>(config_.get());
    IEventListenerPtr reporterPtr(std::move(reporter));
    
    RunContext context(config_.get(), std::move(reporterPtr));
    
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
    
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

// Test RunContext can be constructed and destroyed without issues
TEST_F(RunContextTest_508, Construction_ValidParams_DoesNotThrow_508) {
    EXPECT_NO_THROW({
        auto reporter = Detail::make_unique<MockReporter>(config_.get());
        IEventListenerPtr reporterPtr(std::move(reporter));
        RunContext context(config_.get(), std::move(reporterPtr));
    });
}

// Test getCurrentTestName returns empty string consistently when called multiple times with no active test
TEST_F(RunContextTest_508, GetCurrentTestName_CalledMultipleTimes_AlwaysEmpty_508) {
    auto reporter = Detail::make_unique<MockReporter>(config_.get());
    IEventListenerPtr reporterPtr(std::move(reporter));
    
    RunContext context(config_.get(), std::move(reporterPtr));
    
    EXPECT_EQ(context.getCurrentTestName(), "");
    EXPECT_EQ(context.getCurrentTestName(), "");
    EXPECT_EQ(context.getCurrentTestName(), "");
}
