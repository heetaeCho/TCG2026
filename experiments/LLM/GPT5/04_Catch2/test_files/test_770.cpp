// File: tests/console_reporter_benchmarkEnded_770_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <limits>

// Catch2 public headers (types used by the public interface)
#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/benchmark/detail/catch_benchmark_stats.hpp>
#include <catch2/benchmark/catch_estimate.hpp>
#include <catch2/benchmark/detail/catch_timing.hpp>   // for FDuration
#include <catch2/internal/catch_stringref.hpp>

using namespace ::testing;

namespace {

// Minimal stub of IConfig that lets us control benchmarkNoAnalysis()
// and otherwise returns benign defaults. This avoids touching any
// private state of ConsoleReporter and keeps tests black-box.
class StubConfig final : public Catch::IConfig {
public:
    explicit StubConfig(bool noAnalysis)
        : m_noAnalysis(noAnalysis) {}

    // ---- Methods exercised by ConsoleReporter::benchmarkEnded ----
    bool benchmarkNoAnalysis() const override { ++m_bnaCalls; return m_noAnalysis; }

    // ---- Benign defaults for the rest of the interface ----
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { return Catch::StringRef{"stub"}; }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }

    Catch::TestSpec const& testSpec() const override {
        static Catch::TestSpec spec;
        return spec;
    }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> v; return v;
    }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0u; }
    unsigned int shardCount() const override { return 1u; }
    unsigned int shardIndex() const override { return 0u; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> v; return v;
    }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100u; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 1000u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }

    // Introspection for tests
    int benchmarkNoAnalysisCallCount() const { return m_bnaCalls; }

private:
    bool m_noAnalysis;
    mutable int m_bnaCalls{0};
};

// Helper to build BenchmarkStats with distinctive values,
// without relying on or asserting about internal formatting.
static Catch::BenchmarkStats<> makeStats(
    double meanPoint, double meanLB, double meanUB,
    double sdPoint,   double sdLB,   double sdUB) {

    using FDur = Catch::Benchmark::FDuration;
    Catch::BenchmarkStats<> s{};

    s.mean.point        = FDur{ meanPoint };
    s.mean.lower_bound  = FDur{ meanLB    };
    s.mean.upper_bound  = FDur{ meanUB    };

    s.standardDeviation.point       = FDur{ sdPoint };
    s.standardDeviation.lower_bound = FDur{ sdLB    };
    s.standardDeviation.upper_bound = FDur{ sdUB    };

    // Other fields are not observed by ConsoleReporter::benchmarkEnded
    return s;
}

// Helper to construct a ConsoleReporter with a controlled stream & config
static std::unique_ptr<Catch::ConsoleReporter> makeReporter(std::ostringstream& out, Catch::IConfig const* cfg) {
    Catch::ReporterConfig rc(out, cfg);
    return std::make_unique<Catch::ConsoleReporter>(std::move(rc));
}

} // anonymous namespace

// ------------------------------------------------------------------
// Tests
// ------------------------------------------------------------------

TEST(ConsoleReporter_BenchmarkEnded_770, NoAnalysis_Produces_Shorter_Output_770) {
    // Arrange
    std::ostringstream outNo;
    StubConfig cfgNo(/*noAnalysis=*/true);
    auto reporterNo = makeReporter(outNo, &cfgNo);

    std::ostringstream outFull;
    StubConfig cfgFull(/*noAnalysis=*/false);
    auto reporterFull = makeReporter(outFull, &cfgFull);

    auto stats = makeStats(
        /*meanPoint*/  1.111,
        /*meanLB*/     2.222,
        /*meanUB*/     3.333,
        /*sdPoint*/    4.444,
        /*sdLB*/       5.555,
        /*sdUB*/       6.666);

    // Act
    ASSERT_NO_THROW(reporterNo->benchmarkEnded(stats));
    ASSERT_NO_THROW(reporterFull->benchmarkEnded(stats));

    const auto lenNo   = outNo.str().size();
    const auto lenFull = outFull.str().size();

    // Assert (observable behavior only):
    // - both variants write something
    // - full analysis writes strictly more than no-analysis branch
    EXPECT_GT(lenNo,   0u);
    EXPECT_GT(lenFull, 0u);
    EXPECT_GT(lenFull, lenNo);

    // Verify interaction with config (observable via stub)
    EXPECT_EQ(cfgNo.benchmarkNoAnalysisCallCount(),   1);
    EXPECT_EQ(cfgFull.benchmarkNoAnalysisCallCount(), 1);
}

TEST(ConsoleReporter_BenchmarkEnded_770, NoThrow_With_Extreme_Values_770) {
    std::ostringstream out;
    StubConfig cfg(/*noAnalysis=*/false);
    auto reporter = makeReporter(out, &cfg);

    // Very large/small values to exercise edge formatting paths,
    // without asserting specific format.
    auto stats = makeStats(
        std::numeric_limits<double>::max()/2.0,
        std::numeric_limits<double>::min(),
        0.0,
        1e308,
        1e-308,
        42.0);

    EXPECT_NO_THROW(reporter->benchmarkEnded(stats));
    EXPECT_FALSE(out.str().empty()); // observable effect: something was printed
    EXPECT_EQ(cfg.benchmarkNoAnalysisCallCount(), 1);
}

TEST(ConsoleReporter_BenchmarkEnded_770, Repeated_Calls_Append_Output_770) {
    std::ostringstream out;
    StubConfig cfg(/*noAnalysis=*/false);
    auto reporter = makeReporter(out, &cfg);

    auto statsA = makeStats(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    auto statsB = makeStats(7.0, 8.0, 9.0, 10.0, 11.0, 12.0);

    reporter->benchmarkEnded(statsA);
    const auto len1 = out.str().size();
    reporter->benchmarkEnded(statsB);
    const auto len2 = out.str().size();

    // Observable behavior: subsequent calls add more table output
    EXPECT_GT(len1, 0u);
    EXPECT_GT(len2, len1);

    // Config should be consulted for each call
    EXPECT_EQ(cfg.benchmarkNoAnalysisCallCount(), 2);
}

TEST(ConsoleReporter_BenchmarkEnded_770, NoAnalysis_Versus_FullAnalysis_Content_Differs_770) {
    // This test checks that toggling the config actually changes output content,
    // without making any formatting assumptions.
    std::ostringstream outA, outB;
    StubConfig cfgA(/*noAnalysis=*/true);
    StubConfig cfgB(/*noAnalysis=*/false);

    auto repA = makeReporter(outA, &cfgA);
    auto repB = makeReporter(outB, &cfgB);

    auto stats = makeStats(3.14, 2.71, 1.61, 0.577, 6.022, 9.81);

    repA->benchmarkEnded(stats);
    repB->benchmarkEnded(stats);

    const auto sA = outA.str();
    const auto sB = outB.str();

    EXPECT_FALSE(sA.empty());
    EXPECT_FALSE(sB.empty());
    EXPECT_NE(sA, sB);  // observable difference due to different branch

    EXPECT_EQ(cfgA.benchmarkNoAnalysisCallCount(), 1);
    EXPECT_EQ(cfgB.benchmarkNoAnalysisCallCount(), 1);
}
