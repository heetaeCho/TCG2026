// File: tests/json_reporter_dtor_863_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Catch2 headers (adjust paths to your tree)
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// If your project exposes a utility to construct ReporterConfig for tests,
// include it here. Otherwise, provide a thin local helper that uses your
// real config & stream plumbing. The important bit is that we do not re-
// implement JsonReporter internals; we only pass a valid ReporterConfig.
using namespace Catch;

// ---- Test wiring helpers (project-specific glue) ---------------------------
// Replace this with your project’s real way to create ReporterConfig
// backed by a std::ostream. This stays within "external collaborator"
// mocking territory and does not simulate JsonReporter internals.
static ReporterConfig MakeReporterConfigForStream(std::ostream& os) {
    // Typical construction in Catch2 v3 codebases is something along:
    // ReporterConfig{ cfg, Detail::make_unique<OutputStream>(os), ColourMode::None, {}, {} }
    // but exact signature varies by version. Adapt this to your repo.
    //
    // NOTE: This function is intentionally left to use your real types;
    // it should *not* fake JsonReporter behavior. Keep it minimal.
    //
    // --- BEGIN PROJECT-SPECIFIC AREA ---
    // You likely have a real config handy; grabbing it from a default or a stub
    // IConfig implementation that is considered an external collaborator is fine.
    struct DummyStream : IStream {
        explicit DummyStream(std::ostream& o) : m(o) {}
        std::ostream& stream() override { return m; }
        std::ostream& m;
    };

    // Minimal, non-intrusive config pointer (external collaborator).
    // Use your real IConfig or a benign stub that does not simulate reporter logic.
    class MinimalConfig : public IConfig {
    public:
        // Implement the pure-virtuals with benign pass-throughs as needed
        // (these are external to the SUT).
        bool allowThrows() const override { return true; }
        // Implement remaining pure-virtual functions to satisfy your version.
        // Keep them neutral; do not simulate reporter behavior.
        // ---- START required shims (add what your tree requires) ----
        bool shouldDebugBreak() const override { return false; }
        int abortAfter() const override { return 0; }
        bool hasTestFilters() const override { return false; }
        ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
        DoublePrecision doublePrecision() const override { return 6; }
        bool warnAboutMissingAssertions() const override { return false; }
        bool warnAboutNoTests() const override { return false; }
        bool allowZeroTests() const override { return true; }
        bool benchmarkNoAnalysis() const override { return false; }
        int benchmarkSamples() const override { return 100; }
        double benchmarkConfidenceInterval() const override { return 0.95; }
        unsigned int benchmarkResamples() const override { return 100000; }
        std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
        std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
        std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
        bool filenamesAsTags() const override { return false; }
        bool listReporters() const override { return false; }
        bool listListeners() const override { return false; }
        bool listTests() const override { return false; }
        bool listTags() const override { return false; }
        std::string getProcessName() const override { return "proc"; }
        std::string const& name() const override { static std::string n = "cfg"; return n; }
        bool hasPath() const override { return false; }
        std::string getReporterName() const override { return "json"; }
        std::vector<std::string> const& getReporterNames() const override { static std::vector<std::string> v; return v; }
        std::vector<std::string> const& getListenerNames() const override { static std::vector<std::string> v; return v; }
        ColourMode colourMode() const override { return ColourMode::None; }
        // ---- END required shims ----
    };

    auto cfg = Detail::make_unique<MinimalConfig>();
    auto out = Detail::unique_ptr<IStream>(new DummyStream(os));

    // Construct ReporterConfig with your version’s ctor.
    // The following matches common Catch2 v3 patterns; adjust if needed.
    return ReporterConfig{ cfg.release(), CATCH_MOVE(out), ColourMode::None, {}, {} };
    // --- END PROJECT-SPECIFIC AREA ---
}

class JsonReporterTest_863 : public ::testing::Test {
protected:
    std::ostringstream oss;

    // Factory method to create the SUT with a stream we control
    std::unique_ptr<JsonReporter> makeReporter() {
        auto rc = MakeReporterConfigForStream(oss);
        return std::unique_ptr<JsonReporter>(new JsonReporter(std::move(rc)));
    }
};

// -------------------- Tests ----------------------------

// TEST_ID = 863
TEST_F(JsonReporterTest_863, DestructorWritesFinalNewline_863) {
    // Normal operation: Start a run so the reporter opens its top-level JSON object.
    {
        auto rep = makeReporter();
        // Drive only through public interface. A minimal "start" call is enough.
        // We do not assume internal effects; we only ensure a typical lifecycle.
        TestRunInfo runInfo{"run"};
        rep->testRunStarting(runInfo);
        // Let rep go out of scope -> ~JsonReporter() runs
    }
    // Observable behavior: the destructor appends '\n'
    const std::string s = oss.str();
    ASSERT_FALSE(s.empty()) << "Expected some output from reporter";
    EXPECT_EQ(s.back(), '\n') << "JsonReporter dtor should write a trailing newline";
}

// TEST_ID = 863
TEST_F(JsonReporterTest_863, DestructorDoesNotCrashAfterTypicalLifecycle_863) {
    // Normal operation: start and end a run (no assumptions about internal state).
    {
        auto rep = makeReporter();
        TestRunInfo runInfo{"run"};
        rep->testRunStarting(runInfo);

        // Provide a minimal, valid end event. We do not rely on internal state,
        // only that this is a public entrypoint and typical lifecycle.
        TestRunStats stats{/* values are opaque for the test; use default/empty */};
        rep->testRunEnded(stats);
        // Scope end -> dtor
    }
    // If we got here, no crash/abort occurred. Also check output ends with newline.
    const std::string s = oss.str();
    ASSERT_FALSE(s.empty());
    EXPECT_EQ(s.back(), '\n');
}

// TEST_ID = 863
TEST_F(JsonReporterTest_863, DestructorAssertsWhenTopLevelNotOpen_DebugOnly_863) {
#ifndef NDEBUG
    // In debug builds, the dtor asserts the writers stack state.
    // If we *do not* drive the lifecycle to open the expected top object,
    // destroying the reporter should trip an assertion (death test).
    EXPECT_DEATH(
        []{
            std::ostringstream local;
            auto rep = std::unique_ptr<JsonReporter>(
                new JsonReporter(MakeReporterConfigForStream(local)));
            // Immediately destroy without starting a run -> violates dtor assert
            rep.reset();
        }(),
        "Only the top level object should be open" // matches the assert message
    );
#else
    GTEST_SKIP() << "Assertion-based death test skipped in release builds (NDEBUG defined).";
#endif
}

