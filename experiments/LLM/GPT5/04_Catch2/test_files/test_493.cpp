// File: run_context_dtor_tests_493.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

using ::testing::_;
using ::testing::SaveArg;
using ::testing::StrictMock;

namespace Catch {

// ---- Minimal concrete IConfig for constructing RunContext ----
// NOTE: We only rely on the public interface; default trivial
// implementations are provided for members we do not use in these tests.
class MinimalConfig_493 : public IConfig {
public:
    explicit MinimalConfig_493(std::string name) : m_name(std::move(name)) {}

    // Only the name is used by RunContext's constructor to build TestRunInfo.
    std::string const& name() const override { return m_name; }

    // ---- Trivial implementations to satisfy the interface contract ----
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    bool allowThrows() const override { return true; }
    bool showDurations() const override { return false; }
    double minDuration() const override { return 0.0; }
    TestSpec const& testSpec() const override {
        static TestSpec dummy;
        return dummy;
    }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> none;
        return none;
    }
    bool listTestNamesOnly() const override { return false; }
    ColourMode colourMode() const override { return ColourMode::Auto; }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    int abortAfter() const override { return 0; }
    bool showHelp() const override { return false; }
    bool showInvisibles() const override { return false; }
    ShowDurations::OrNot showDurations() const override { return ShowDurations::DefaultForReporter; }
    double rngSeed() const override { return 0.0; }
    bool benchmarkNoAnalysis() const override { return false; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{100}; }
    bool includeSuccessfulResults() const override { return false; }
    std::ostream& stream() const override { return std::cout; }
    std::string getProcessName() const override { return "proc"; }
    bool alsoRunDisabledTests() const override { return false; }
    bool includeIters() const override { return false; }
    bool bddMode() const override { return false; }
    bool noThrow() const override { return false; }
    bool reportInvocation() const override { return false; }
    bool rotationEnabled() const override { return false; }
    bool filenamesAsTags() const override { return false; }

private:
    std::string m_name;
};

// ---- Mock event listener to observe RunContext's destructor call ----
class MockEventListener_493 : public IEventListener {
public:
    // We pass nullptr here; the listener’s config is not used by the tests.
    MockEventListener_493() : IEventListener(nullptr) {}

    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
};

// ---- Test fixture (empty, used for consistent naming) ----
class RunContextDtorTest_493 : public ::testing::Test {};

TEST_F(RunContextDtorTest_493, CallsTestRunEndedOnDestruction_493) {
    MinimalConfig_493 cfg("UT_Run_493");

    // Create reporter and keep raw pointer for EXPECT_CALL.
    auto* rawReporter = new StrictMock<MockEventListener_493>();
    IEventListenerPtr reporter(static_cast<IEventListener*>(rawReporter));

    TestRunStats receivedStats{ TestRunInfo{""}, Totals{}, false };

    EXPECT_CALL(*rawReporter, testRunEnded(_))
        .WillOnce(SaveArg<0>(&receivedStats));

    {
        // Create and immediately destroy RunContext (scope end triggers dtor).
        RunContext ctx(&cfg, std::move(reporter));
        // no further interaction
    }

    // Verify observable facts only:
    // - destructor called reporter->testRunEnded once (checked by EXPECT_CALL)
    // - run name propagated from IConfig into TestRunStats
    EXPECT_EQ(receivedStats.runInfo.name, "UT_Run_493");
}

TEST_F(RunContextDtorTest_493, PropagatesAbortingFlagToReporter_493) {
    MinimalConfig_493 cfg("Abort_Run_493");

    auto* rawReporter = new StrictMock<MockEventListener_493>();
    IEventListenerPtr reporter(static_cast<IEventListener*>(rawReporter));

    TestRunStats receivedStats{ TestRunInfo{""}, Totals{}, false };

    EXPECT_CALL(*rawReporter, testRunEnded(_))
        .WillOnce(SaveArg<0>(&receivedStats));

    {
        RunContext ctx(&cfg, std::move(reporter));

        // Use only the public interface; do not assume internals.
        // If a fatal condition is reported, the context may enter "aborting" state.
        ctx.handleFatalErrorCondition(StringRef("boom"));
        // Destructor will be invoked at scope end.
    }

    // The destructor passes aborting() into TestRunStats; verify it propagated.
    EXPECT_TRUE(receivedStats.aborting);
}

} // namespace Catch
