// File: tests/catch_reporter_cumulative_base_test_860.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 public headers you already use in your project.
// (Paths may differ slightly in your tree.)
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// The following helpers create minimal, valid inputs using only public
// types/constructors. They avoid peeking at any internal state.

namespace {

using namespace Catch;

// Minimal helper to construct TestCaseInfo and Totals for TestCaseStats
inline TestCaseInfo MakeDummyTestCaseInfo(const std::string& name = "tc_860") {
    // Use any existing public ctor signature available in your tree.
    // Typical signature: TestCaseInfo(name, className, description, tags, sourceLocation, isHidden)
    // If your Catch2 version differs, adjust the call-site accordingly (still public API).
    return TestCaseInfo(
        NameAndTags{name, {}},                               // name + tags
        SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)}
    );
}

inline Totals MakeZeroTotals() {
    return Totals{};
}

// Convenience wrapper to build TestCaseStats with provided stdout/stderr
inline TestCaseStats MakeTestCaseStats(
    const TestCaseInfo& info,
    const std::string& out,
    const std::string& err,
    bool aborting = false
) {
    return TestCaseStats(
        info,
        MakeZeroTotals(),
        std::string(out),
        std::string(err),
        aborting
    );
}

// A tiny test-double that derives from CumulativeReporterBase to get a concrete
// instance we can call *public* lifecycle methods on. We do NOT access or
// expose any private/internal state. We only override the optional hook
// testRunEndedCumulative() to observe that a full run can finish without
// crashing (observable via a boolean flag).
class TestableCumulativeReporter_860 : public CumulativeReporterBase {
public:
    using CumulativeReporterBase::CumulativeReporterBase;

    void testRunEndedCumulative() override {
        endedCumulativeCalled = true;
    }

    bool endedCumulativeCalled = false;
};

// Factory for a minimal ReporterConfig using only public APIs.
// If your project already provides a helper for reporter construction,
// feel free to replace this with that.
inline std::unique_ptr<IConfig const> MakeMinimalConfig() {
    // Use any concrete config already available in your tree. For Catch2 itself,
    // Config is a public type but may require more parameters. In many setups,
    // tests provide a small custom IConfig implementation for reporters.
    // Here we provide a dummy minimal IConfig implementation via a simple test stub.
    struct MinimalConfig final : IConfig {
        ~MinimalConfig() override = default;

        // Implement only the methods that ReporterBase/ReporterConfig require.
        bool allowThrows() const override { return true; }
        std::ostream& stream() const override {
            // Use a shared stream to satisfy ReporterBase; it must outlive the reporter.
            static std::ostringstream oss;
            return oss;
        }
        // The rest can return defaults appropriate for your build.
        bool shouldDebugBreak() const override { return false; }
        std::string name() const override { return "MinimalConfig_860"; }
        bool includeSuccessfulResults() const override { return true; }
        bool warnAboutMissingAssertions() const override { return false; }
        ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
        double minDuration() const override { return -1; }
        TestSpec const& testSpec() const override { static TestSpec spec; return spec; }
        bool hasTestFilters() const override { return false; }
        std::vector<std::string> const& getTestsOrTags() const override {
            static std::vector<std::string> none; return none;
        }
        RunOrder runOrder() const override { return RunOrder::Declared; }
        unsigned int rngSeed() const override { return 0; }
        UseColour useColour() const override { return UseColour::Auto; }
        bool shouldReportAllAssertions() const override { return false; }
        bool zeroTestsCountAsSuccess() const override { return false; }
        Verbosity verbosity() const override { return Verbosity::Normal; }
        bool benchmarkNoAnalysis() const override { return false; }
        int benchmarkSamples() const override { return 100; }
        double benchmarkConfidenceInterval() const override { return 0.95; }
        unsigned int benchmarkResamples() const override { return 100000; }
        std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
    };

    return std::unique_ptr<IConfig const>(new MinimalConfig{});
}

inline ReporterConfig MakeReporterConfig() {
    // ReporterConfig takes (IConfigPtr, colour, stream)
    auto cfg = MakeMinimalConfig();
    // ReporterConfig expects a shared_ptr-like holder; in Catch2 it is 'IConfigPtr'
    // which is std::shared_ptr<IConfig const>.
    IConfigPtr cfgPtr(cfg.release()); // adopt into shared_ptr
    return ReporterConfig{ cfgPtr };
}

} // namespace

// ------------------------------
// TESTS
// ------------------------------

//
// TEST 1 (Normal operation): Calling testCaseEnded after a well-formed
// start/end of a single section should not crash and the run can be
// ended successfully. We also check that the public virtual hook
// testRunEndedCumulative() is invoked when we end the run, which is
// an observable effect.
// 
TEST(CumulativeReporterBase_860, TestCaseEnded_Normal_NoCrash_860) {
    auto rc = MakeReporterConfig();
    TestableCumulativeReporter_860 rep{ ReporterConfig{rc} };

    // Begin a run and a test case through public API
    rep.testRunStarting( TestRunInfo{"run_860"} );
    const auto tci = MakeDummyTestCaseInfo("tc_ok_860");
    rep.testCaseStarting( tci );

    // Open & close a single section to ensure the base has a "deepest section"
    rep.sectionStarting( SectionInfo{ tci.name, SourceLineInfo{__FILE__, __LINE__}} );
    rep.sectionEnded( SectionStats{ SectionInfo{ tci.name, SourceLineInfo{__FILE__, __LINE__}}, Counts{}, false } );

    // Now end the test case — this must not assert/crash
    const auto stats = MakeTestCaseStats(tci, "stdout_860", "stderr_860", /*aborting*/ false);
    rep.testCaseEnded( stats );

    // Finish the run — observable: our override is called
    rep.testRunEnded( TestRunStats{ TestRunInfo{"run_860"}, Totals{} , false } );
    EXPECT_TRUE(rep.endedCumulativeCalled);
}

//
// TEST 2 (Boundary/Precondition): If there is an *unclosed* section,
// base implementation asserts that the internal section stack is empty.
// We verify the assertion via a death test (observable behavior).
//
#ifndef NDEBUG
TEST(CumulativeReporterBase_860, TestCaseEnded_AssertFailsWithOpenSection_860) {
    auto rc = MakeReporterConfig();
    TestableCumulativeReporter_860 rep{ ReporterConfig{rc} };

    rep.testRunStarting( TestRunInfo{"run_860"} );
    const auto tci = MakeDummyTestCaseInfo("tc_open_section_860");
    rep.testCaseStarting( tci );

    // Start a section but DO NOT end it — this should leave the internal
    // "section stack" non-empty, triggering the assert in testCaseEnded.
    rep.sectionStarting( SectionInfo{ tci.name, SourceLineInfo{__FILE__, __LINE__}} );

    const auto stats = MakeTestCaseStats(tci, "out", "err", false);

    // Expect an assertion failure (death) due to non-empty section stack.
    ASSERT_DEATH(
        {
            rep.testCaseEnded(stats);
        },
        ".*" // death message pattern depends on your assert handler; accept anything
    );
}
#endif

//
// TEST 3 (Exceptional/Precondition): If the reporter never established a
// deepest section (e.g., no sections at all), base implementation asserts
// that m_deepestSection is non-null. We verify via a death test.
//
#ifndef NDEBUG
TEST(CumulativeReporterBase_860, TestCaseEnded_AssertFailsWithNoSections_860) {
    auto rc = MakeReporterConfig();
    TestableCumulativeReporter_860 rep{ ReporterConfig{rc} };

    rep.testRunStarting( TestRunInfo{"run_860"} );
    const auto tci = MakeDummyTestCaseInfo("tc_no_section_860");
    rep.testCaseStarting( tci );

    // No sectionStarting/sectionEnded called — no "deepest section".
    const auto stats = MakeTestCaseStats(tci, "o", "e", false);

    // Expect an assertion failure (death) due to missing deepest section.
    ASSERT_DEATH(
        {
            rep.testCaseEnded(stats);
        },
        ".*"
    );
}
#endif

//
// TEST 4 (Boundary: stdOut/stdErr presence): With a valid deepest section,
// calling testCaseEnded should succeed regardless of whether stdOut/stdErr
// are empty or large. We cannot peek into private state, so we assert only
// on the absence of crashes across edge sizes.
//
TEST(CumulativeReporterBase_860, TestCaseEnded_EmptyAndLargeStdStreams_NoCrash_860) {
    auto rc = MakeReporterConfig();
    TestableCumulativeReporter_860 rep{ ReporterConfig{rc} };

    rep.testRunStarting( TestRunInfo{"run_860"} );
    const auto tci = MakeDummyTestCaseInfo("tc_streams_860");
    rep.testCaseStarting( tci );

    // Create deepest section
    rep.sectionStarting( SectionInfo{ tci.name, SourceLineInfo{__FILE__, __LINE__}} );
    rep.sectionEnded( SectionStats{ SectionInfo{ tci.name, SourceLineInfo{__FILE__, __LINE__}}, Counts{}, false } );

    // Empty streams
    rep.testCaseEnded( MakeTestCaseStats(tci, "", "", false) );

    // Large-ish streams (observable = still no crash)
    std::string big(64 * 1024, 'x');
    rep.testCaseEnded( MakeTestCaseStats(tci, big, big, false) );

    // End run cleanly
    rep.testRunEnded( TestRunStats{ TestRunInfo{"run_860"}, Totals{} , false } );
    EXPECT_TRUE(rep.endedCumulativeCalled);
}
