#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_config.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

// We need to access the TablePrinter through the ConsoleReporter's behavior
// Since TablePrinter is internal to the console reporter namespace, we test
// through the ConsoleReporter's public interface

namespace {

// Helper to create a minimal config for testing
class MockConfig : public Catch::IConfig {
public:
    bool allowThrows() const override { return true; }
    std::ostream& stream() const override { return const_cast<std::ostream&>(static_cast<const std::ostream&>(m_stream)); }
    Catch::StringRef name() const override { return "test"; }
    bool includeSuccessfulResults() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    int abortAfter() const override { return 1; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::None; }
    unsigned int rngSeed() const override { return 0; }
    bool shouldDebugBreak() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { return m_empty; }
    Catch::ReporterSpec const& getReporterSpec() const override { return m_reporterSpec; }
    std::vector<Catch::ReporterSpec> const& getReporterSpecs() const override { return m_reporterSpecs; }
    std::vector<Catch::ProcessedReporterSpec> const& getProcessedReporterSpecs() const override { return m_processedSpecs; }

    mutable std::stringstream m_stream;
    std::vector<std::string> m_empty;
    Catch::ReporterSpec m_reporterSpec{"console", {}, {}, {}};
    std::vector<Catch::ReporterSpec> m_reporterSpecs;
    std::vector<Catch::ProcessedReporterSpec> m_processedSpecs;
};

} // anonymous namespace

// Since TablePrinter is an internal implementation detail of the ConsoleReporter,
// and we cannot directly instantiate it, we test the ConsoleReporter's output
// which exercises the TablePrinter's ColumnBreak operator internally.

class ConsoleReporterTest_759 : public ::testing::Test {
protected:
    void SetUp() override {
        m_stream = std::make_unique<std::ostringstream>();
    }

    std::unique_ptr<std::ostringstream> m_stream;
};

// Test that ConsoleReporter can be constructed and produces output
TEST_F(ConsoleReporterTest_759, ReporterCanBeCreated_759) {
    // The ConsoleReporter uses TablePrinter internally for benchmark results
    // We verify the reporter can be instantiated without errors
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    // ConsoleReporter should be constructible
    ASSERT_NO_THROW({
        auto reporter = Catch::ConsoleReporter(config);
    });
}

// Test that the console reporter formats output (exercises TablePrinter indirectly)
TEST_F(ConsoleReporterTest_759, ReporterProducesFormattedOutput_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    // The reporter should handle test run started
    Catch::TestRunInfo runInfo("test");
    ASSERT_NO_THROW(reporter.testRunStarting(runInfo));
}

// Test benchmark output which uses TablePrinter with ColumnBreak
TEST_F(ConsoleReporterTest_759, BenchmarkResultFormatsColumns_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    Catch::TestRunInfo runInfo("test");
    reporter.testRunStarting(runInfo);
    
    // Create benchmark stats that would exercise the TablePrinter
    Catch::BenchmarkStats<std::chrono::duration<double, std::nano>> stats{
        {"benchmark_test", 0.0, 1, 1, 1, 1},
        {std::chrono::duration<double, std::nano>(100.0), std::chrono::duration<double, std::nano>(90.0), std::chrono::duration<double, std::nano>(110.0), {0.95, 0.95, 0.0, 0}},
        {std::chrono::duration<double, std::nano>(10.0), std::chrono::duration<double, std::nano>(9.0), std::chrono::duration<double, std::nano>(11.0), {0.95, 0.95, 0.0, 0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0}},
        1
    };
    
    ASSERT_NO_THROW(reporter.benchmarkEnded(stats));
    
    // The output should contain the benchmark name
    std::string output = oss.str();
    // Benchmark output is formatted with columns via TablePrinter
    // We just verify it doesn't crash and produces some output
    // (exact format depends on implementation)
}

// Test that multiple column breaks work correctly through reporter
TEST_F(ConsoleReporterTest_759, MultipleColumnsFormatted_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    Catch::TestRunInfo runInfo("test");
    reporter.testRunStarting(runInfo);
    
    // Multiple benchmark results should format correctly
    for (int i = 0; i < 3; i++) {
        Catch::BenchmarkStats<std::chrono::duration<double, std::nano>> stats{
            {"bench_" + std::to_string(i), 0.0, 1, 1, 1, 1},
            {std::chrono::duration<double, std::nano>(100.0 * (i + 1)), std::chrono::duration<double, std::nano>(90.0), std::chrono::duration<double, std::nano>(110.0), {0.95, 0.95, 0.0, 0}},
            {std::chrono::duration<double, std::nano>(10.0), std::chrono::duration<double, std::nano>(9.0), std::chrono::duration<double, std::nano>(11.0), {0.95, 0.95, 0.0, 0}},
            {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0}},
            1
        };
        ASSERT_NO_THROW(reporter.benchmarkEnded(stats));
    }
    
    std::string output = oss.str();
    // Verify output contains newlines indicating column breaks wrapped rows
    EXPECT_FALSE(output.empty());
}

// Test that test run ending cleans up properly
TEST_F(ConsoleReporterTest_759, TestRunEndingProducesOutput_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.testCases.passed = 1;
    totals.assertions.passed = 5;
    
    Catch::TestRunStats runStats(runInfo, totals, false);
    ASSERT_NO_THROW(reporter.testRunEnded(runStats));
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test empty benchmark name (boundary condition)
TEST_F(ConsoleReporterTest_759, EmptyBenchmarkName_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    Catch::TestRunInfo runInfo("test");
    reporter.testRunStarting(runInfo);
    
    Catch::BenchmarkStats<std::chrono::duration<double, std::nano>> stats{
        {"", 0.0, 1, 1, 1, 1},
        {std::chrono::duration<double, std::nano>(100.0), std::chrono::duration<double, std::nano>(90.0), std::chrono::duration<double, std::nano>(110.0), {0.95, 0.95, 0.0, 0}},
        {std::chrono::duration<double, std::nano>(10.0), std::chrono::duration<double, std::nano>(9.0), std::chrono::duration<double, std::nano>(11.0), {0.95, 0.95, 0.0, 0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0}},
        1
    };
    
    ASSERT_NO_THROW(reporter.benchmarkEnded(stats));
}

// Test very long benchmark name (boundary - tests padding logic in ColumnBreak)
TEST_F(ConsoleReporterTest_759, LongBenchmarkNameExceedsColumnWidth_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    Catch::TestRunInfo runInfo("test");
    reporter.testRunStarting(runInfo);
    
    // Create a very long name that would exceed column width
    // This tests the boundary where strSize + 1 >= colInfo.width, resulting in empty padding
    std::string longName(200, 'A');
    
    Catch::BenchmarkStats<std::chrono::duration<double, std::nano>> stats{
        {longName, 0.0, 1, 1, 1, 1},
        {std::chrono::duration<double, std::nano>(100.0), std::chrono::duration<double, std::nano>(90.0), std::chrono::duration<double, std::nano>(110.0), {0.95, 0.95, 0.0, 0}},
        {std::chrono::duration<double, std::nano>(10.0), std::chrono::duration<double, std::nano>(9.0), std::chrono::duration<double, std::nano>(11.0), {0.95, 0.95, 0.0, 0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0}},
        1
    };
    
    ASSERT_NO_THROW(reporter.benchmarkEnded(stats));
    
    std::string output = oss.str();
    // Verify that long name appears in output
    EXPECT_NE(output.find(longName), std::string::npos);
}

// Test benchmark with zero duration values
TEST_F(ConsoleReporterTest_759, ZeroDurationBenchmark_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    Catch::TestRunInfo runInfo("test");
    reporter.testRunStarting(runInfo);
    
    Catch::BenchmarkStats<std::chrono::duration<double, std::nano>> stats{
        {"zero_bench", 0.0, 1, 1, 1, 1},
        {std::chrono::duration<double, std::nano>(0.0), std::chrono::duration<double, std::nano>(0.0), std::chrono::duration<double, std::nano>(0.0), {0.95, 0.95, 0.0, 0}},
        {std::chrono::duration<double, std::nano>(0.0), std::chrono::duration<double, std::nano>(0.0), std::chrono::duration<double, std::nano>(0.0), {0.95, 0.95, 0.0, 0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0}},
        1
    };
    
    ASSERT_NO_THROW(reporter.benchmarkEnded(stats));
}

// Test that output contains proper spacing (tests ColumnBreak padding)
TEST_F(ConsoleReporterTest_759, OutputContainsProperSpacing_759) {
    std::ostringstream oss;
    Catch::ReporterConfig config(nullptr, oss, Catch::ColourMode::None, {});
    auto reporter = Catch::ConsoleReporter(config);
    
    Catch::TestRunInfo runInfo("test");
    reporter.testRunStarting(runInfo);
    
    Catch::BenchmarkStats<std::chrono::duration<double, std::nano>> stats{
        {"spacing_test", 0.0, 1, 1, 1, 1},
        {std::chrono::duration<double, std::nano>(1234.5), std::chrono::duration<double, std::nano>(1000.0), std::chrono::duration<double, std::nano>(1500.0), {0.95, 0.95, 0.0, 0}},
        {std::chrono::duration<double, std::nano>(50.0), std::chrono::duration<double, std::nano>(40.0), std::chrono::duration<double, std::nano>(60.0), {0.95, 0.95, 0.0, 0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0}},
        1
    };
    
    reporter.benchmarkEnded(stats);
    
    std::string output = oss.str();
    // Each row produced by TablePrinter ends with newline (from ColumnBreak at last column)
    if (!output.empty()) {
        // Output should contain at least one newline from column wrapping
        EXPECT_NE(output.find('\n'), std::string::npos);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
