// File: tests/XmlReporter_benchmarkStarting_844.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Catch2 public headers you use in your project:
#include <catch2/reporters/catch_reporter_xml.hpp>
#include <catch2/benchmark/detail/catch_benchmark_stats.hpp>

// If your project uses a different header path for ReporterConfig/StreamingReporterBase,
// include that here instead:
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/internal/catch_config.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>

using namespace Catch;

// --- Small helper to construct XmlReporter that writes into a provided stream ---
// Adjust in one place if your reporter config wiring differs in your tree.
static std::unique_ptr<XmlReporter> MakeXmlReporter(std::ostream& os) {
    // Minimal preferences: we only care that reporter writes to `os`.
    ReporterConfig rconf{ os, nullptr };
    return std::make_unique<XmlReporter>(ReporterConfig{ std::move(rconf) });
}

// --- Utility: substring presence in stream (formatting-agnostic) ---
static bool containsAll(const std::string& haystack,
                        std::initializer_list<std::string> needles) {
    for (const auto& n : needles) {
        if (haystack.find(n) == std::string::npos) return false;
    }
    return true;
}

// Fixture provides a fresh reporter + output buffer per test.
class XmlReporterBenchmarkStarting_844 : public ::testing::Test {
protected:
    std::ostringstream oss;
    std::unique_ptr<XmlReporter> reporter;

    void SetUp() override {
        reporter = MakeXmlReporter(oss);
    }
};

// Normal operation: writes expected attributes & comment
TEST_F(XmlReporterBenchmarkStarting_844, WritesAllExpectedAttributesAndComment_844) {
    BenchmarkInfo info{};
    info.samples           = 8u;
    info.resamples         = 100u;
    info.iterations        = 123;
    info.clockResolution   = 50.0;
    info.estimatedDuration = 4'200'000.0; // ns

    // Precondition for many reporters is that a benchmark scope was prepared.
    // We call benchmarkPreparing to put reporter into a sensible state without
    // asserting on its outputs (black-box).
    reporter->benchmarkPreparing(StringRef("bench_name"));

    // Call the function under test
    ASSERT_NO_THROW(reporter->benchmarkStarting(info));

    const std::string out = oss.str();

    // Check that the *attribute names* and the comment string appear.
    // We do not assert on exact formatting or values serialization.
    EXPECT_TRUE(containsAll(out, {
        "samples",
        "resamples",
        "iterations",
        "clockResolution",
        "estimatedDuration",
        "All values in nano seconds"
    })) << "Output was:\n" << out;
}

// Boundary-ish values: zeroes should still be written as attributes,
// and the comment should still appear.
TEST_F(XmlReporterBenchmarkStarting_844, WritesAttributesWhenValuesAreZero_844) {
    BenchmarkInfo info{};
    info.samples           = 0u;
    info.resamples         = 0u;
    info.iterations        = 0;
    info.clockResolution   = 0.0;
    info.estimatedDuration = 0.0;

    reporter->benchmarkPreparing(StringRef("zero_bench"));
    ASSERT_NO_THROW(reporter->benchmarkStarting(info));

    const std::string out = oss.str();

    // Names + comment presence (format independent)
    EXPECT_TRUE(containsAll(out, {
        "samples",
        "resamples",
        "iterations",
        "clockResolution",
        "estimatedDuration",
        "All values in nano seconds"
    })) << "Output was:\n" << out;
}

// Large values: verify attribute presence remains stable and does not throw.
TEST_F(XmlReporterBenchmarkStarting_844, HandlesLargeValuesWithoutThrowing_844) {
    BenchmarkInfo info{};
    info.samples           = std::numeric_limits<unsigned int>::max();
    info.resamples         = std::numeric_limits<unsigned int>::max();
    info.iterations        = std::numeric_limits<int>::max();
    info.clockResolution   = std::numeric_limits<double>::max() / 2; // avoid inf in some libcs
    info.estimatedDuration = std::numeric_limits<double>::max() / 2;

    reporter->benchmarkPreparing(StringRef("huge_bench"));
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    const std::string out = oss.str();

    EXPECT_TRUE(containsAll(out, {
        "samples",
        "resamples",
        "iterations",
        "clockResolution",
        "estimatedDuration",
        "All values in nano seconds"
    })) << "Output was:\n" << out;
}

// Negative-ish iteration count (if a signed field is provided).
// We don't assume reporter clamps/validates; we only verify black-box safety
// and that attribute names + comment are still emitted.
TEST_F(XmlReporterBenchmarkStarting_844, AcceptsNonPositiveIterations_844) {
    BenchmarkInfo info{};
    info.samples           = 3u;
    info.resamples         = 2u;
    info.iterations        = -1;   // signed per decl
    info.clockResolution   = 10.0;
    info.estimatedDuration = 1.0;

    reporter->benchmarkPreparing(StringRef("neg_iter_bench"));
    EXPECT_NO_THROW(reporter->benchmarkStarting(info));

    const std::string out = oss.str();

    EXPECT_TRUE(containsAll(out, {
        "iterations",
        "All values in nano seconds"
    })) << "Output was:\n" << out;
}
