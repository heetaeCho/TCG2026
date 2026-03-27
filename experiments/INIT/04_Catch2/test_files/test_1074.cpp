// File: tests/run_context_ctor_1074_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AtLeast;

namespace Catch {

// Minimal mocks based strictly on the provided interfaces

class MockConfig : public IConfig {
public:
    MOCK_METHOD(StringRef, name, (), (override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (override));

    // The rest are not used here; provide stubs to satisfy vtable if needed.
    MOCK_METHOD(bool, allowThrows, (), (override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (override));
    MOCK_METHOD(int, abortAfter, (), (override));
    MOCK_METHOD(bool, showInvisibles, (), (override));
    MOCK_METHOD(ShowDurations, showDurations, (), (override));
    MOCK_METHOD(double, minDuration, (), (override));
    MOCK_METHOD((TestSpec const&), testSpec, (), (override));
    MOCK_METHOD(bool, hasTestFilters, (), (override));
    MOCK_METHOD((const std::vector<std::string>&), getTestsOrTags, (), (override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (override));
    MOCK_METHOD(uint32_t, rngSeed, (), (override));
    MOCK_METHOD(unsigned int, shardCount, (), (override));
    MOCK_METHOD(unsigned int, shardIndex, (), (override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (override));
    MOCK_METHOD((const std::vector<std::string>&), getSectionsToRun, (), (override));
    MOCK_METHOD(Verbosity, verbosity, (), (override));
    MOCK_METHOD(bool, skipBenchmarks, (), (override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (override));
    MOCK_METHOD((std::chrono::milliseconds), benchmarkWarmupTime, (), (override));
    // Virtual dtor provided by base interface
};

class MockListener : public IEventListener {
public:
    explicit MockListener(IConfig const* cfg) : IEventListener(cfg) {
        // Let tests tweak m_preferences via setter below
        m_preferences = ReporterPreferences{};
    }

    // Expose a lightweight way to configure preferences for observable behavior decisions
    void setPreferences(const ReporterPreferences& prefs) { m_preferences = prefs; }

    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    // Other virtuals (unused here) can be left unmocked.
};

} // namespace Catch

// ---------- Test Fixture ----------

class RunContextCtorTest_1074 : public ::testing::Test {
protected:
    Catch::MockConfig cfg_;
    std::unique_ptr<Catch::MockListener> rawListener_; // keep raw for expectations
    Catch::Detail::unique_ptr<Catch::IEventListener> listenerPtr_; // what RunContext takes

    void SetUp() override {
        using namespace Catch;

        // Reasonable defaults for calls made by RunContext's ctor
        ON_CALL(cfg_, name()).WillByDefault(Return(StringRef("SuiteName_1074")));
        ON_CALL(cfg_, includeSuccessfulResults()).WillByDefault(Return(false));

        // Many pure virtuals are not touched; give benign defaults
        ON_CALL(cfg_, allowThrows()).WillByDefault(Return(true));
        ON_CALL(cfg_, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(cfg_, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(cfg_, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(cfg_, zeroTestsCountAsSuccess()).WillByDefault(Return(false));
        ON_CALL(cfg_, abortAfter()).WillByDefault(Return(0));
        ON_CALL(cfg_, showInvisibles()).WillByDefault(Return(false));
        ON_CALL(cfg_, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(cfg_, minDuration()).WillByDefault(Return(0.0));
        // The rest of cfg_ methods won't be invoked by these tests; no need to set expectations.

        rawListener_ = std::make_unique<Catch::MockListener>(&cfg_);
        // default preferences: both flags false
        Catch::ReporterPreferences prefs;
        prefs.shouldRedirectStdOut = false;
        prefs.shouldReportAllAssertions = false;
        rawListener_->setPreferences(prefs);

        // Wrap in Catch's unique_ptr
        listenerPtr_ = Catch::Detail::unique_ptr<Catch::IEventListener>(rawListener_.release());
    }

    void TearDown() override {
        // RunContext destructor will NOT delete our listener (it owns via unique_ptr),
        // so nothing to do here.
    }
};

// ---------- Tests ----------

// Verifies that constructing RunContext:
// 1) invokes reporter->testRunStarting once,
// 2) passes a TestRunInfo whose name originates from IConfig::name(),
// 3) registers itself as the current IResultCapture in the global Context.
TEST_F(RunContextCtorTest_1074, CallsReporterAndRegistersResultCapture_1074) {
    using namespace Catch;

    // We expect the ctor to consult config.name()
    EXPECT_CALL(cfg_, name())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(StringRef("SuiteName_1074")));

    // Expect testRunStarting exactly once and verify the run name if accessible
    EXPECT_CALL(*static_cast<MockListener*>(listenerPtr_.get()),
                testRunStarting(::testing::Property(&TestRunInfo::name, ::testing::StrEq("SuiteName_1074"))))
        .Times(1);

    // Also expect includeSuccessfulResults to be queried (used to compute internal flag)
    EXPECT_CALL(cfg_, includeSuccessfulResults())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(false));

    // Construct the SUT (this should trigger all expectations)
    RunContext rc(&cfg_, std::move(listenerPtr_));

    // After construction, the current Context should point to this result-capture object
    // Observable via the public Context accessor
    auto* current = Catch::getCurrentContext().getResultCapture();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current, static_cast<IResultCapture*>(&rc));
}

// A second scenario toggling the listener’s preferences to ensure that the ctor
// still starts the run and registers itself, regardless of redirection/report-all flags.
TEST_F(RunContextCtorTest_1074, HonorsListenerPreferencesButStillStartsAndRegisters_1074) {
    using namespace Catch;

    // Recreate a listener with different preferences (true/true)
    auto alt = std::make_unique<MockListener>(&cfg_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = true;
    prefs.shouldReportAllAssertions = true;
    alt->setPreferences(prefs);

    // Swap the listener pointer used for construction
    listenerPtr_ = Catch::Detail::unique_ptr<IEventListener>(alt.release());

    EXPECT_CALL(cfg_, name())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(StringRef("SuiteName_1074_B")));

    EXPECT_CALL(*static_cast<MockListener*>(listenerPtr_.get()),
                testRunStarting(::testing::Property(&TestRunInfo::name, ::testing::StrEq("SuiteName_1074_B"))))
        .Times(1);

    // Even if report-all is true, the code path still may consult includeSuccessfulResults().
    EXPECT_CALL(cfg_, includeSuccessfulResults())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(true));

    RunContext rc(&cfg_, std::move(listenerPtr_));

    auto* current = Catch::getCurrentContext().getResultCapture();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current, static_cast<IResultCapture*>(&rc));
}
