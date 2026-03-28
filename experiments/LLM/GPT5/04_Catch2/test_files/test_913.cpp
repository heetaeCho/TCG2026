#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 amalgamated and interfaces
#include "Catch2/extras/catch_amalgamated.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"
#include "Catch2/src/catch2/internal/catch_context.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::SaveArg;

// ------------------------
// Mocks for external collaborators
// ------------------------

namespace {

class MockConfig : public Catch::IConfig {
public:
    // Only the methods used by run() need observable returns
    // However, we provide safe defaults for all virtuals to avoid undefined behavior
    ~MockConfig() override = default;

    // Minimal safe defaults (unused ones can return trivial values)
    const bool allowThrows() override { return true; }
    const Catch::StringRef name() override { return Catch::StringRef("cfg"); }
    const bool includeSuccessfulResults() override { return true; }
    const bool shouldDebugBreak() override { return false; }
    const bool warnAboutMissingAssertions() override { return false; }
    const bool warnAboutUnmatchedTestSpecs() override { return false; }
    const bool zeroTestsCountAsSuccess() override { return true; }
    const int abortAfter() override { return 0; }
    const bool showInvisibles() override { return false; }
    const Catch::ShowDurations showDurations() override { return Catch::ShowDurations::DefaultForReporter; }
    const double minDuration() override { return 0.0; }
    const Catch::TestSpec& testSpec() override { static Catch::TestSpec s; return s; }
    const bool hasTestFilters() override { return false; }
    const std::vector<std::string>& getTestsOrTags() override { static std::vector<std::string> v; return v; }
    const Catch::TestRunOrder runOrder() override { return Catch::TestRunOrder::Declared; }
    const uint32_t rngSeed() override { return 0; }
    const unsigned int shardCount() override { return 1; }
    const unsigned int shardIndex() override { return 0; }
    const Catch::ColourMode defaultColourMode() override { return Catch::ColourMode::PlatformDefault; }
    const std::vector<std::string>& getSectionsToRun() override { static std::vector<std::string> v; return v; }
    const Catch::Verbosity verbosity() override { return Catch::Verbosity::Normal; }
    const bool skipBenchmarks() override { return false; }

    // These are used by run() when filling BenchmarkInfo
    const bool benchmarkNoAnalysis() override { return false; }

    // Will be configured per-test via ON_CALL/EXPECT_CALL as needed
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (override));
    MOCK_METHOD(double,        benchmarkConfidenceInterval, (), (override));
    MOCK_METHOD(unsigned int,  benchmarkResamples, (), (override));

    const std::chrono::milliseconds benchmarkWarmupTime() override { return std::chrono::milliseconds{0}; }
};

class MockResultCapture : public Catch::IResultCapture {
public:
    ~MockResultCapture() override = default;

    // We only care about the benchmark-related callbacks
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef name), (override));
    MOCK_METHOD(void, benchmarkStarting,  (const Catch::BenchmarkInfo& info), (override));
    MOCK_METHOD(void, benchmarkEnded,     (const Catch::BenchmarkStats<>& stats), (override));
    MOCK_METHOD(void, benchmarkFailed,    (Catch::StringRef error), (override));

    // Stub everything else with inert implementations
    void notifyAssertionStarted (const Catch::AssertionInfo&) override {}
    bool sectionStarted (Catch::StringRef, const Catch::SourceLineInfo&, Catch::Counts&) override { return true; }
    void sectionEnded (Catch::SectionEndInfo&&) override {}
    void sectionEndedEarly (Catch::SectionEndInfo&&) override {}
    Catch::IGeneratorTracker* acquireGeneratorTracker (Catch::StringRef, const Catch::SourceLineInfo&) override { return nullptr; }
    Catch::IGeneratorTracker* createGeneratorTracker (Catch::StringRef, Catch::SourceLineInfo, Catch::Generators::GeneratorBasePtr&&) override { return nullptr; }
    void pushScopedMessage (const Catch::MessageInfo&) override {}
    void popScopedMessage (const Catch::MessageInfo&) override {}
    void emplaceUnscopedMessage (Catch::MessageBuilder&&) override {}
    void handleFatalErrorCondition (Catch::StringRef) override {}
    void handleExpr (const Catch::AssertionInfo&, const Catch::ITransientExpression&, Catch::AssertionReaction&) override {}
    void handleMessage (const Catch::AssertionInfo&, struct Catch::ResultWas::OfType, std::string&&, Catch::AssertionReaction&) override {}
    void handleUnexpectedExceptionNotThrown (const Catch::AssertionInfo&, Catch::AssertionReaction&) override {}
    void handleUnexpectedInflightException (const Catch::AssertionInfo&, std::string&&, Catch::AssertionReaction&) override {}
    void handleIncomplete (const Catch::AssertionInfo&) override {}
    void handleNonExpr (const Catch::AssertionInfo&, struct Catch::ResultWas::OfType, Catch::AssertionReaction&) override {}
    bool lastAssertionPassed () override { return true; }
    void assertionPassed () override {}
    const std::string getCurrentTestName () override { return {}; }
    const Catch::AssertionResult* getLastResult () override { return nullptr; }
    void exceptionEarlyReported () override {}
};

/// Helper steady clock that satisfies the static_assert in run()
struct SteadyFakeClock {
    using rep        = long long;
    using period     = std::nano;
    using duration   = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<SteadyFakeClock>;
    static constexpr bool is_steady = true;
    static time_point now() noexcept { return time_point(duration(0)); }
};

/// Test fixture wires mocks into global Catch context (observable interface).
class BenchmarkRunTest_913 : public ::testing::Test {
protected:
    StrictMock<MockResultCapture> result_;
    NiceMock<MockConfig>          config_;

    void SetUp() override {
        // Provide safe defaults for config used by run()
        ON_CALL(config_, benchmarkSamples()).WillByDefault(Return(3u));
        ON_CALL(config_, benchmarkResamples()).WillByDefault(Return(100u));
        ON_CALL(config_, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));

        // Wire mocks into Catch's global context via the public setters
        auto& ctx = Catch::Context().getCurrentMutableContext();
        ctx.setResultCapture(&result_);
        ctx.setConfig(&config_);
    }

    void TearDown() override {
        // Detach to avoid leaking pointers between tests
        auto& ctx = Catch::Context().getCurrentMutableContext();
        ctx.setResultCapture(nullptr);
        ctx.setConfig(nullptr);
    }
};

} // namespace

// ------------------------------------------------------------
// TESTS
// ------------------------------------------------------------

// Normal operation (happy path): observe that run() announces preparing, starting, and ended.
// We cannot assume exact numeric values inside BenchmarkInfo/BenchmarkStats, only that the callbacks happen.
TEST_F(BenchmarkRunTest_913, Run_EmitsPreparingStartingEnded_913) {
    using Catch::Benchmark::Benchmark;

    // A well-behaved functor; actual work is a black box.
    auto noop = []() {};

    Benchmark bench{"happy-path", noop};

    {
        InSequence seq;
        EXPECT_CALL(result_, benchmarkPreparing(_)).Times(1);
        EXPECT_CALL(result_, benchmarkStarting(_)).Times(1);
        EXPECT_CALL(result_, benchmarkEnded(_)).Times(1);
        // No failure expected on the happy path
        EXPECT_CALL(result_, benchmarkFailed(_)).Times(0);
    }

    // We use a steady fake clock to satisfy the constraint.
    // The rest of the pipeline (prepare/run/analyse) is treated as a black box.
    bench.run<SteadyFakeClock>();
}

// Error/exception path: if user code throws a generic exception, run() should report benchmarkFailed,
// and (per code) rethrow. We assert failure is reported; we also catch to keep the test running.
TEST_F(BenchmarkRunTest_913, Run_WhenGenericException_FailsAndRethrows_913) {
    using Catch::Benchmark::Benchmark;

    auto throwing = []() -> void {
        throw std::runtime_error("boom");
    };

    Benchmark bench{"generic-throw", throwing};

    EXPECT_CALL(result_, benchmarkPreparing(_)).Times(1);
    // On generic exception, we expect a failure to be reported.
    EXPECT_CALL(result_, benchmarkFailed(_)).Times(1);
    // Starting/Ended might or might not be called before the throw depending on where it happens;
    // we make no assertion about those to avoid assuming internal sequencing.

    EXPECT_ANY_THROW(bench.run<SteadyFakeClock>());
}

// Assertion-style failure path: if a Catch-style test failure exception is thrown, run() reports a specific message.
// We don't rely on the type existing in this TU; instead, we verify behavior by name if available.
// If TestFailureException is not linkable in your build, you may SKIP this test (left enabled by default).
TEST_F(BenchmarkRunTest_913, Run_WhenTestFailureException_ReportsStandardMessage_913) {
    using Catch::Benchmark::Benchmark;

    // We attempt to throw Catch's assertion exception type if present.
    // This uses a weakly-typed throw via a function pointer to avoid requiring the type symbol here.
    // If your environment exposes Catch::TestFailureException, this will engage the dedicated catch branch.
    auto failLikeCatch = []() -> void {
        // We only declare the type; the actual symbol/type must come from your Catch2 linkage.
        struct LocalThrow {
            [[noreturn]] static void throwNow() {
                // If this fails to compile in your environment because the type is not visible,
                // you can disable this test, or replace with a helper that throws that exact type.
                throw Catch::TestFailureException();
            }
        };
        LocalThrow::throwNow();
    };

    Benchmark bench{"assert-failure", failLikeCatch};

    EXPECT_CALL(result_, benchmarkPreparing(_)).Times(1);
    // The code path reports a fixed message: "Benchmark failed due to failed assertion"
    EXPECT_CALL(result_, benchmarkFailed(::testing::Property(&Catch::StringRef::size, ::testing::Gt(0u)))).Times(1);

    // The dedicated branch does not rethrow; run() should *not* throw on this path per provided snippet.
    // If your integrated Catch2 version differs and rethrows, adjust to EXPECT_ANY_THROW.
    EXPECT_NO_THROW(bench.run<SteadyFakeClock>());
}
