// File: tests/console_reporter_benchmarkPreparing_768_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 reporter under test
#include "catch2/reporters/catch_reporter_console.hpp"
#include "catch2/internal/catch_stringref.hpp"

// If your project exposes ReporterConfig from a different header, adjust include:
#include "catch2/reporters/catch_reporter_helpers.hpp"

using ::testing::HasSubstr;

// ------------------------------
// Test fixture
// ------------------------------
class ConsoleReporterBenchmarkPreparingTest_768 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to construct ConsoleReporter with output bound to `os`.
    // Adjust this to match your project's ReporterConfig constructor if needed.
    Catch::ConsoleReporter makeReporter_() {
        // Many Catch2 setups provide ReporterConfig like:
        //   Catch::ReporterConfig rc{ &cfg, os /*, ... optional args ... */ };
        //
        // For strict black-boxing, we avoid pulling in IConfig details.
        // If your ReporterConfig needs an IConfig, pass your existing mock/stub.
        //
        // Below is a minimal pattern that works in typical Catch2 v3 trees.
        Catch::ReporterConfig rc{ /* fullConfig = */ nullptr, os };
        return Catch::ConsoleReporter{ std::move(rc) };
    }

    // Convenience to call the SUT and return the stream content
    std::string runAndGrab_(const std::string& name) {
        auto reporter = makeReporter_();
        reporter.benchmarkPreparing(Catch::StringRef{name});
        return os.str();
    }
};

// ------------------------------
// Tests
// ------------------------------

// Normal case: single short line should appear in the output at least once.
TEST_F(ConsoleReporterBenchmarkPreparingTest_768, ShortName_AppearsInOutput_768) {
    const std::string name = "quick-bench";
    const auto out = runAndGrab_(name);

    // Observable behavior: the name is printed somewhere.
    EXPECT_THAT(out, HasSubstr(name));
}

// Boundary case: empty name should not crash and should produce *some* output
// (table structure / column break) without assuming internal formatting.
TEST_F(ConsoleReporterBenchmarkPreparingTest_768, EmptyName_DoesNotCrash_ProducesOutput_768) {
    const std::string name; // empty
    const auto out = runAndGrab_(name);

    // We only assert that *something* was produced (e.g., column movement).
    // Exact formatting is intentionally not assumed.
    EXPECT_FALSE(out.empty());
}

// Long/wrapping case: a long tokenized name likely wraps or spans multiple
// table cells/lines. We do not assert the exact wrap; we only verify that
// both the start and the end fragments are present, implying multi-segment output.
TEST_F(ConsoleReporterBenchmarkPreparingTest_768, LongName_ContainsStartAndEndFragments_768) {
    const std::string longName =
        "this-is-a-very-long-benchmark-name-intended-to-exercise-wrapping-behavior";
    const auto out = runAndGrab_(longName);

    // Observable-only checks: beginning and ending fragments show up somewhere.
    EXPECT_THAT(out, HasSubstr("this-is-a-very-long"));
    EXPECT_THAT(out, HasSubstr("wrapping-behavior"));
}

// Repeated calls: output should append (monotonic growth). This also covers the
// case where the method emits the necessary ColumnBreaks between subsequent lines.
TEST_F(ConsoleReporterBenchmarkPreparingTest_768, MultipleCalls_AppendsToOutput_768) {
    auto reporter = makeReporter_();

    const auto before = os.str().size();
    reporter.benchmarkPreparing(Catch::StringRef{"bench-A"});
    const auto afterFirst = os.str().size();
    reporter.benchmarkPreparing(Catch::StringRef{"bench-B"});
    const auto afterSecond = os.str().size();

    ASSERT_GE(afterFirst, before);
    EXPECT_GT(afterSecond, afterFirst);

    const auto out = os.str();
    EXPECT_THAT(out, HasSubstr("bench-A"));
    EXPECT_THAT(out, HasSubstr("bench-B"));
}

// Unicode / multibyte: ensure it accepts and prints UTF-8 names without
// crashing, treating them as opaque text.
TEST_F(ConsoleReporterBenchmarkPreparingTest_768, Utf8Name_PrintsWithoutCrash_768) {
    const std::string name = u8"성능-벤치마크-테스트";
    const auto out = runAndGrab_(name);
    EXPECT_THAT(out, HasSubstr(name));
}
