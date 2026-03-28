// File: tests/XmlReporter_benchmarkEnded_845.tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <chrono>

// Catch2 public headers you already use across reporter tests
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"

// If your tree uses different paths/namespaces, include the right ones.
// The tests only rely on public types & methods as per the prompt.

using namespace Catch;

// --- Small helper that creates an XmlReporter writing to provided ostream ---
// Adapt this to your existing test harness if you already have a util.
static std::unique_ptr<XmlReporter> makeXmlReporterTo(std::ostream& os) {
    // ReporterConfig is part of Catch2 reporters infra. The exact ctor can vary
    // between Catch2 versions; this helper is intentionally isolated so you can
    // adjust it without touching test bodies.
    //
    // Common pattern in Catch2 v3:
    //   Catch::IConfig const* cfg = ... (minimal stub or real config)
    //   Catch::ReporterConfig rc{ *cfg, os };
    //   return std::make_unique<Catch::XmlReporter>(std::move(rc));
    //
    // For these tests we assume a minimal config that defaults everything except the stream.
    struct MinimalConfig : Catch::IConfig {
        // Provide the bare minimum overrides used by reporters; return safe defaults.
        bool allowThrows() const override { return true; }
        std::ostream& stream() const override {
            // Not used — the reporter uses the stream from ReporterConfig.
            static std::ostream* s = nullptr; return *s;
        }
        // Other pure virtuals: provide harmless defaults.
        // (Keep them trivial; reporters typically don't consult them here.)
        bool shouldDebugBreak() const override { return false; }
        bool warnAboutMissingAssertions() const override { return false; }
        bool warnAboutNoTests() const override { return false; }
        ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
        double minDuration() const override { return -1; }
        TestSpec const& testSpec() const override { static TestSpec s; return s; }
        bool hasTestFilters() const override { return false; }
        std::vector<std::string> const& getTestsOrTags() const override {
            static std::vector<std::string> empty; return empty;
        }
        RunOrder runOrder() const override { return RunOrder::Declared; }
        unsigned int rngSeed() const override { return 0; }
        UseColour useColour() const override { return UseColour::No; }
        bool shouldShowSuccessfulTests() const override { return false; }
        bool shouldSkipBenchmarks() const override { return false; }
        bool isBenchmarking() const override { return true; }
        bool benchmarksForApprovalTests() const override { return false; }
        bool zeroTestsCountAsSuccess() const override { return false; }
        int abortAfter() const override { return 0; }
        bool benchmarkNoAnalysis() const override { return false; }
        bool benchmarkWarmupTime() const override { return false; }
        bool benchmarkSamples() const override { return false; }
        bool benchmarkResamples() const override { return false; }
        std::chrono::milliseconds shardDurations() const override { return std::chrono::milliseconds{0}; }
        std::string name() const override { static std::string n{"cfg"}; return n; }
        std::vector<std::string> const& getReporterNames() const override {
            static std::vector<std::string> v; return v;
        }
        std::vector<std::string> const& getListeners() const override {
            static std::vector<std::string> v; return v;
        }
        bool includeSuccessfulResultsOnly() const override { return false; }
        // Newer Catch2 versions might add more virtuals; add trivial impls if your build complains.
    };

    static MinimalConfig cfg; // lifetime for the reporter duration

    Catch::ReporterConfig rc{ cfg, os };
    return std::make_unique<Catch::XmlReporter>(std::move(rc));
}

// Convenience: build a BenchmarkStats with integer-friendly values to stabilize output
static Catch::BenchmarkStats<> makeStats(
    double meanValue, double meanLo, double meanHi, double meanCI,
    double sdValue,   double sdLo,   double sdHi,   double sdCI,
    int lowMild, int lowSevere, int highMild, int highSevere,
    double outlierVar
) {
    Catch::BenchmarkStats<> s{};
    using D = Catch::Benchmark::FDuration;

    s.mean.point         = D(meanValue);
    s.mean.lower_bound   = D(meanLo);
    s.mean.upper_bound   = D(meanHi);
    s.mean.confidence_interval = meanCI;

    s.standardDeviation.point       = D(sdValue);
    s.standardDeviation.lower_bound = D(sdLo);
    s.standardDeviation.upper_bound = D(sdHi);
    s.standardDeviation.confidence_interval = sdCI;

    s.outliers.low_mild   = lowMild;
    s.outliers.low_severe = lowSevere;
    s.outliers.high_mild  = highMild;
    s.outliers.high_severe= highSevere;

    s.outlierVariance = outlierVar;

    return s;
}

class XmlReporter_BenchmarkEnded_845 : public ::testing::Test {
protected:
    std::ostringstream os_;
    std::unique_ptr<XmlReporter> reporter_;

    void SetUp() override {
        reporter_ = makeXmlReporterTo(os_);
        // In real runs, <benchmarkResults> (or similar) could be opened earlier.
        // We exercise only benchmarkEnded's observable writes here.
    }

    std::string str() const { return os_.str(); }

    // Helpers that assert for presence of expected fragments without depending
    // on attribute order or whitespace details.
    static void expectContains(const std::string& haystack, const std::string& needle) {
        ASSERT_NE(haystack.find(needle), std::string::npos) << "Missing fragment: " << needle
                                                            << "\nOutput was:\n" << haystack;
    }
};

// Normal operation: all attributes emitted on mean, standardDeviation, outliers, and a final endElement
TEST_F(XmlReporter_BenchmarkEnded_845, WritesAllExpectedElementsAndAttributes_845) {
    auto stats = makeStats(
        /*mean*/100, 90, 110, 0.95,
        /*sd*/  12,  10,  15,  0.95,
        /*outliers*/ 1, 0, 2, 0,
        /*var*/ 0.12
    );

    reporter_->benchmarkEnded(stats);

    const auto out = str();

    // Mean block
    expectContains(out, "<mean");
    expectContains(out, "value=\"100\"");
    expectContains(out, "lowerBound=\"90\"");
    expectContains(out, "upperBound=\"110\"");
    expectContains(out, "ci=\"0.95\"");

    // Standard deviation block
    expectContains(out, "<standardDeviation");
    expectContains(out, "value=\"12\"");
    expectContains(out, "lowerBound=\"10\"");
    expectContains(out, "upperBound=\"15\"");
    expectContains(out, "ci=\"0.95\"");

    // Outliers block
    expectContains(out, "<outliers");
    expectContains(out, "variance=\"0.12\"");
    expectContains(out, "lowMild=\"1\"");
    expectContains(out, "lowSevere=\"0\"");
    expectContains(out, "highMild=\"2\"");
    expectContains(out, "highSevere=\"0\"");
}

// Boundary case: zeros everywhere should still serialize as attributes (no crashes, complete tags)
TEST_F(XmlReporter_BenchmarkEnded_845, HandlesZeroValuesAndNoOutliers_845) {
    auto stats = makeStats(
        /*mean*/0, 0, 0, 1.0,
        /*sd*/  0, 0, 0, 1.0,
        /*outliers*/ 0, 0, 0, 0,
        /*var*/ 0.0
    );

    reporter_->benchmarkEnded(stats);

    const auto out = str();

    // Mean & SD blocks with zeros
    expectContains(out, "<mean");
    expectContains(out, "value=\"0\"");
    expectContains(out, "lowerBound=\"0\"");
    expectContains(out, "upperBound=\"0\"");
    expectContains(out, "ci=\"1\""); // integer-friendly 1.0 may render as "1"

    expectContains(out, "<standardDeviation");
    expectContains(out, "value=\"0\"");
    expectContains(out, "lowerBound=\"0\"");
    expectContains(out, "upperBound=\"0\"");
    expectContains(out, "ci=\"1\"");

    // Outliers all zero
    expectContains(out, "<outliers");
    expectContains(out, "variance=\"0\"");
    expectContains(out, "lowMild=\"0\"");
    expectContains(out, "lowSevere=\"0\"");
    expectContains(out, "highMild=\"0\"");
    expectContains(out, "highSevere=\"0\"");
}

// Large/extreme numbers: makes sure big magnitudes and different CI serialize
TEST_F(XmlReporter_BenchmarkEnded_845, SerializesLargeValuesAndDifferentCI_845) {
    auto stats = makeStats(
        /*mean*/1000000, 999000, 1001000, 0.99,
        /*sd*/  50000,   49000,  51000,   0.90,
        /*outliers*/ 123, 45, 67, 89,
        /*var*/ 123.456
    );

    reporter_->benchmarkEnded(stats);

    const auto out = str();

    expectContains(out, "<mean");
    expectContains(out, "value=\"1000000\"");
    expectContains(out, "lowerBound=\"999000\"");
    expectContains(out, "upperBound=\"1001000\"");
    expectContains(out, "ci=\"0.99\"");

    expectContains(out, "<standardDeviation");
    expectContains(out, "value=\"50000\"");
    expectContains(out, "lowerBound=\"49000\"");
    expectContains(out, "upperBound=\"51000\"");
    expectContains(out, "ci=\"0.9\""); // 0.90 may format as "0.9"

    expectContains(out, "<outliers");
    expectContains(out, "variance=\"123.456\"");
    expectContains(out, "lowMild=\"123\"");
    expectContains(out, "lowSevere=\"45\"");
    expectContains(out, "highMild=\"67\"");
    expectContains(out, "highSevere=\"89\"");
}
