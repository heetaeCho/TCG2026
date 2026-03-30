// File: console_reporter_benchmarkStarting_769_tests.cpp

#include <gtest/gtest.h>
#include <sstream>

// Catch2 reporter under test
#include <catch2/reporters/catch_reporter_console.hpp>

// These headers are typically pulled transitively by the console reporter header,
// but we include interfaces explicitly for clarity.
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/benchmark/detail/catch_benchmark_stats.hpp>

using namespace Catch;

namespace {

// Minimal stub config that satisfies IConfig and lets us control/observe
// benchmarkNoAnalysis() calls without relying on internal state.
class StubConfig final : public IConfig {
public:
    // Toggle this to simulate CLI/config behavior.
    bool noAnalysis = false;

    // Count how many times benchmarkNoAnalysis() is consulted.
    mutable int benchmarkNoAnalysisCalls = 0;

    // ---- IConfig interface (trivial defaults where not relevant) ----
    ~StubConfig() override = default;

    bool allowThrows() const override { return true; }
    StringRef name() const override { static StringRef n("stub"); return n; }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return true; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }

    ShowDurations showDurations() const override {
        return ShowDurations::DefaultForReporter;
    }

    double minDuration() const override { return 0.0; }

    TestSpec const& testSpec() const override {
        static TestSpec spec;
        return spec;
    }

    bool hasTestFilters() const override { return false; }

    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }

    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0u; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    ColourMode defaultColourMode() const override { return ColourMode::PlatformDefault; }

    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }

    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }

    bool benchmarkNoAnalysis() const override {
        ++benchmarkNoAnalysisCalls;
        return noAnalysis;
    }

    unsigned int benchmarkSamples() const override { return 0u; }
    double benchmarkConfidenceInterval() const override { return 0.0; }
    unsigned int benchmarkResamples() const override { return 0u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override {
        return std::chrono::milliseconds{0};
    }
};

// Helper to build a ConsoleReporter with a given config & stream.
// We keep this tiny and rely solely on public construction & behavior.
static std::unique_ptr<ConsoleReporter> makeReporter(IConfig const* cfg, std::ostream& os) {
    // ReporterConfig is movable; the ConsoleReporter takes it by rvalue.
    ReporterConfig rcfg{cfg, os};
    return std::make_unique<ConsoleReporter>(std::move(rcfg));
}

// Common fixture
class ConsoleReporterBenchmarkStartingTest_769 : public ::testing::Test {
protected:
    BenchmarkInfo makeInfo(unsigned samples,
                           int iterations,
                           double estimatedSeconds) {
        BenchmarkInfo info{};
        info.samples = samples;
        info.iterations = iterations;
        info.estimatedDuration = estimatedSeconds;
        // Unused fields can be left as default for black-box testing.
        return info;
    }
};

} // namespace

// --- Tests ---

TEST_F(ConsoleReporterBenchmarkStartingTest_769,
       FlushesAndPrintsSamplesAndIterations_WhenAnalysisEnabled_769) {
    StubConfig cfg;
    cfg.noAnalysis = false; // analysis ENABLED

    std::ostringstream out;
    auto reporter = makeReporter(&cfg, out);

    auto info = makeInfo(/*samples*/7u, /*iterations*/100, /*estimatedSeconds*/0.123);
    reporter->benchmarkStarting(info);

    const std::string s = out.str();
    // Observable effects:
    // 1) Output flushed -> some content
    EXPECT_FALSE(s.empty());

    // 2) The simple numbers we pushed (samples & iterations) appear somewhere
    //    in the stream. We do not assert any specific formatting.
    EXPECT_NE(s.find("7"), std::string::npos);
    EXPECT_NE(s.find("100"), std::string::npos);

    // 3) External interaction: config consulted exactly once (per call)
    EXPECT_EQ(cfg.benchmarkNoAnalysisCalls, 1);
}

TEST_F(ConsoleReporterBenchmarkStartingTest_769,
       OutputIsShorterWithoutDuration_WhenNoAnalysis_769) {
    // Prepare identical info, run with/without analysis and compare sizes.
    auto info = makeInfo(/*samples*/5u, /*iterations*/42, /*estimatedSeconds*/0.50);

    // With analysis (duration column included)
    StubConfig cfgWith;
    cfgWith.noAnalysis = false;
    std::ostringstream outWith;
    auto repWith = makeReporter(&cfgWith, outWith);
    repWith->benchmarkStarting(info);
    const std::string sWith = outWith.str();
    ASSERT_FALSE(sWith.empty());
    EXPECT_EQ(cfgWith.benchmarkNoAnalysisCalls, 1);

    // Without analysis (duration column omitted)
    StubConfig cfgWithout;
    cfgWithout.noAnalysis = true;
    std::ostringstream outWithout;
    auto repWithout = makeReporter(&cfgWithout, outWithout);
    repWithout->benchmarkStarting(info);
    const std::string sWithout = outWithout.str();
    ASSERT_FALSE(sWithout.empty());
    EXPECT_EQ(cfgWithout.benchmarkNoAnalysisCalls, 1);

    // Adding the duration column should strictly increase output size.
    EXPECT_GT(sWith.size(), sWithout.size());
}

TEST_F(ConsoleReporterBenchmarkStartingTest_769,
       HandlesZeroValuesAndStillFlushes_769) {
    StubConfig cfg;
    // Try both modes to ensure no crashes and both flush.
    auto info = makeInfo(/*samples*/0u, /*iterations*/0, /*estimatedSeconds*/0.0);

    // analysis ON
    cfg.noAnalysis = false;
    std::ostringstream outA;
    auto repA = makeReporter(&cfg, outA);
    repA->benchmarkStarting(info);
    const std::string a = outA.str();
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(cfg.benchmarkNoAnalysisCalls, 1);

    // analysis OFF
    cfg.benchmarkNoAnalysisCalls = 0;
    cfg.noAnalysis = true;
    std::ostringstream outB;
    auto repB = makeReporter(&cfg, outB);
    repB->benchmarkStarting(info);
    const std::string b = outB.str();
    EXPECT_FALSE(b.empty());
    EXPECT_EQ(cfg.benchmarkNoAnalysisCalls, 1);

    // Different column set => outputs should differ (we avoid assuming exact size delta).
    EXPECT_NE(a, b);
}

TEST_F(ConsoleReporterBenchmarkStartingTest_769,
       LargeValuesDoNotCrashAndAreVisible_769) {
    StubConfig cfg;
    cfg.noAnalysis = false; // include duration

    std::ostringstream out;
    auto rep = makeReporter(&cfg, out);

    auto info = makeInfo(/*samples*/1000000u,
                         /*iterations*/2147483647,
                         /*estimatedSeconds*/12.75);
    rep->benchmarkStarting(info);

    const std::string s = out.str();
    EXPECT_FALSE(s.empty());
    // The raw integers should appear somewhere in the flushed output
    // regardless of formatting.
    EXPECT_NE(s.find("1000000"), std::string::npos);
    EXPECT_NE(s.find("2147483647"), std::string::npos);
    EXPECT_EQ(cfg.benchmarkNoAnalysisCalls, 1);
}
