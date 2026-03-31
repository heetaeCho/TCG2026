#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_reusable_string_stream.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a given stream
class JsonReporterTestFixture : public ::testing::Test {
protected:
    std::stringstream ss;
    
    std::unique_ptr<JsonReporter> createReporter() {
        auto config = makeReporterConfig(ss);
        return std::make_unique<JsonReporter>(std::move(config));
    }

    // We need to create a ReporterConfig. This typically needs an IConfig and a stream.
    ReporterConfig makeReporterConfig(std::ostream& stream) {
        // Create a minimal config
        static ConfigData configData;
        static Config config(configData);
        return ReporterConfig(&config, stream, ColourMode::None, {});
    }
};

} // anonymous namespace

class JsonReporterTest_865 : public JsonReporterTestFixture {};

TEST_F(JsonReporterTest_865, GetDescription_ReturnsNonEmpty_865) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JsonReporterTest_865, Construction_ProducesValidReporter_865) {
    auto reporter = createReporter();
    EXPECT_NE(reporter, nullptr);
}

TEST_F(JsonReporterTest_865, TestRunStarting_ProducesOutput_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("TestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    std::string output = ss.str();
    // The JSON reporter should produce some output when a test run starts
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, TestRunStartingAndEnding_ProducesValidJson_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("TestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    reporter->testRunEnded(TestRunStats(runInfo, totals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    // Should contain test-run somewhere in the output
    EXPECT_NE(output.find("test-run"), std::string::npos);
}

TEST_F(JsonReporterTest_865, TestRunStarting_ContainsTestCasesArray_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("MySuite"_sr);
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    reporter->testRunEnded(TestRunStats(runInfo, totals, false));
    
    std::string output = ss.str();
    EXPECT_NE(output.find("test-cases"), std::string::npos);
}

TEST_F(JsonReporterTest_865, FullTestCaseLifecycle_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("TestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    // Create test case info
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"TestCase1"_sr, "[tag1]"_sr},
        {"file.cpp", 10}
    );
    
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo({"file.cpp", 10}, "section1"_sr);
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertInfo(
        "expr"_sr,
        {"file.cpp", 11},
        "original_expression"_sr,
        ResultDisposition::Normal
    );
    reporter->assertionStarting(assertInfo);
    
    AssertionResultData resultData(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(assertInfo, std::move(resultData));
    
    Counts counts;
    counts.passed = 1;
    SectionStats sectionStats(sectionInfo, counts, 0.001, false);
    reporter->sectionEnded(sectionStats);
    
    Totals testTotals;
    testTotals.assertions.passed = 1;
    TestCaseStats tcStats(*tcInfo, testTotals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    runTotals.assertions.passed = 1;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, ListReporters_ProducesOutput_865) {
    auto reporter = createReporter();
    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"json", "JSON reporter"});
    descriptions.push_back({"console", "Console reporter"});
    
    reporter->listReporters(descriptions);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, ListTags_ProducesOutput_865) {
    auto reporter = createReporter();
    std::vector<TagInfo> tags;
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, ListTests_EmptyList_865) {
    auto reporter = createReporter();
    std::vector<TestCaseHandle> tests;
    
    reporter->listTests(tests);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, ListListeners_ProducesOutput_865) {
    auto reporter = createReporter();
    std::vector<ListenerDescription> descriptions;
    
    reporter->listListeners(descriptions);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, TestRunEnded_ContainsTotals_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("TestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 2;
    totals.testCases.passed = 3;
    totals.testCases.failed = 1;
    
    reporter->testRunEnded(TestRunStats(runInfo, totals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    // Should contain results/totals information
    EXPECT_NE(output.find("totals"), std::string::npos);
}

TEST_F(JsonReporterTest_865, TestRunWithAbort_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("TestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    totals.assertions.failed = 1;
    
    reporter->testRunEnded(TestRunStats(runInfo, totals, true));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, BenchmarkLifecycle_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("TestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"BenchmarkTest"_sr, "[benchmark]"_sr},
        {"bench.cpp", 1}
    );
    
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo({"bench.cpp", 1}, "benchmark_section"_sr);
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("myBenchmark"_sr);
    
    BenchmarkInfo benchInfo{"myBenchmark", 1.0, 100, 1000, 10, 5};
    reporter->benchmarkStarting(benchInfo);
    
    Catch::Benchmark::Estimate<double> mean{1.0, 0.9, 1.1, 0.95};
    Catch::Benchmark::Estimate<double> standardDeviation{0.1, 0.05, 0.15, 0.95};
    Catch::Benchmark::Estimate<double> outlierVariance{0.01, 0.005, 0.015, 0.95};
    
    BenchmarkStats<> benchStats{benchInfo, mean, standardDeviation, outlierVariance, outlierVariance};
    reporter->benchmarkEnded(benchStats);
    
    Counts counts;
    SectionStats sectionStats(sectionInfo, counts, 0.01, false);
    reporter->sectionEnded(sectionStats);
    
    Totals testTotals;
    TestCaseStats tcStats(*tcInfo, testTotals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, BenchmarkFailed_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("TestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"BenchmarkFail"_sr, "[benchmark]"_sr},
        {"bench.cpp", 1}
    );
    
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo({"bench.cpp", 1}, "benchmark_section"_sr);
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("failBench"_sr);
    reporter->benchmarkFailed("some error"_sr);
    
    Counts counts;
    SectionStats sectionStats(sectionInfo, counts, 0.01, false);
    reporter->sectionEnded(sectionStats);
    
    Totals testTotals;
    TestCaseStats tcStats(*tcInfo, testTotals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, EmptyTestRunName_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo(""_sr);
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    reporter->testRunEnded(TestRunStats(runInfo, totals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, MultipleTestCases_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("MultiTestSuite"_sr);
    reporter->testRunStarting(runInfo);
    
    for (int i = 0; i < 3; ++i) {
        std::string name = "TestCase" + std::to_string(i);
        auto tcInfo = makeTestCaseInfo(
            ""_sr,
            {StringRef(name), ""_sr},
            {"file.cpp", static_cast<std::size_t>(10 + i)}
        );
        
        reporter->testCaseStarting(*tcInfo);
        reporter->testCasePartialStarting(*tcInfo, 0);
        
        SectionInfo sectionInfo({"file.cpp", static_cast<std::size_t>(10 + i)}, StringRef(name));
        reporter->sectionStarting(sectionInfo);
        
        Counts counts;
        counts.passed = 1;
        SectionStats sectionStats(sectionInfo, counts, 0.001, false);
        reporter->sectionEnded(sectionStats);
        
        Totals testTotals;
        testTotals.assertions.passed = 1;
        TestCaseStats tcStats(*tcInfo, testTotals, "", "", false);
        reporter->testCasePartialEnded(tcStats, 0);
        reporter->testCaseEnded(tcStats);
    }
    
    Totals runTotals;
    runTotals.assertions.passed = 3;
    runTotals.testCases.passed = 3;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("test-cases"), std::string::npos);
}

TEST_F(JsonReporterTest_865, NestedSections_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("NestedSections"_sr);
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"NestedTest"_sr, ""_sr},
        {"file.cpp", 10}
    );
    
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo outerSection({"file.cpp", 10}, "outer"_sr);
    reporter->sectionStarting(outerSection);
    
    SectionInfo innerSection({"file.cpp", 20}, "inner"_sr);
    reporter->sectionStarting(innerSection);
    
    Counts innerCounts;
    innerCounts.passed = 1;
    SectionStats innerStats(innerSection, innerCounts, 0.001, false);
    reporter->sectionEnded(innerStats);
    
    Counts outerCounts;
    outerCounts.passed = 1;
    SectionStats outerStats(outerSection, outerCounts, 0.002, false);
    reporter->sectionEnded(outerStats);
    
    Totals testTotals;
    testTotals.assertions.passed = 1;
    TestCaseStats tcStats(*tcInfo, testTotals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, AssertionEnded_WithPassingResult_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("AssertionTest"_sr);
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"AssertTest"_sr, ""_sr},
        {"file.cpp", 1}
    );
    
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo({"file.cpp", 1}, "section"_sr);
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertInfo(
        "x == 1"_sr,
        {"file.cpp", 5},
        "x == 1"_sr,
        ResultDisposition::Normal
    );
    reporter->assertionStarting(assertInfo);
    
    AssertionResultData resultData(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(assertInfo, std::move(resultData));
    
    Counts assertCounts;
    assertCounts.passed = 1;
    AssertionStats assertStats(result, {}, assertCounts);
    reporter->assertionEnded(assertStats);
    
    Counts sectionCounts;
    sectionCounts.passed = 1;
    SectionStats sectionStats(sectionInfo, sectionCounts, 0.001, false);
    reporter->sectionEnded(sectionStats);
    
    Totals testTotals;
    testTotals.assertions.passed = 1;
    TestCaseStats tcStats(*tcInfo, testTotals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    runTotals.assertions.passed = 1;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, AssertionEnded_WithFailingResult_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("FailAssertionTest"_sr);
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"FailTest"_sr, ""_sr},
        {"file.cpp", 1}
    );
    
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo({"file.cpp", 1}, "section"_sr);
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertInfo(
        "x == 2"_sr,
        {"file.cpp", 5},
        "x == 2"_sr,
        ResultDisposition::Normal
    );
    reporter->assertionStarting(assertInfo);
    
    AssertionResultData resultData(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(assertInfo, std::move(resultData));
    
    Counts assertCounts;
    assertCounts.failed = 1;
    AssertionStats assertStats(result, {}, assertCounts);
    reporter->assertionEnded(assertStats);
    
    Counts sectionCounts;
    sectionCounts.failed = 1;
    SectionStats sectionStats(sectionInfo, sectionCounts, 0.001, false);
    reporter->sectionEnded(sectionStats);
    
    Totals testTotals;
    testTotals.assertions.failed = 1;
    TestCaseStats tcStats(*tcInfo, testTotals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    runTotals.assertions.failed = 1;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, TestCaseWithStdOut_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("StdOutTest"_sr);
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"OutputTest"_sr, ""_sr},
        {"file.cpp", 1}
    );
    
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo({"file.cpp", 1}, "section"_sr);
    reporter->sectionStarting(sectionInfo);
    
    Counts counts;
    SectionStats sectionStats(sectionInfo, counts, 0.001, false);
    reporter->sectionEnded(sectionStats);
    
    Totals testTotals;
    TestCaseStats tcStats(*tcInfo, testTotals, "some stdout", "some stderr", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_865, MultiplePartialTestCases_865) {
    auto reporter = createReporter();
    TestRunInfo runInfo("PartialTest"_sr);
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"PartialTestCase"_sr, ""_sr},
        {"file.cpp", 1}
    );
    
    reporter->testCaseStarting(*tcInfo);
    
    // First partial run
    reporter->testCasePartialStarting(*tcInfo, 0);
    SectionInfo sectionInfo1({"file.cpp", 1}, "section1"_sr);
    reporter->sectionStarting(sectionInfo1);
    Counts counts1;
    counts1.passed = 1;
    SectionStats sectionStats1(sectionInfo1, counts1, 0.001, false);
    reporter->sectionEnded(sectionStats1);
    Totals totals1;
    totals1.assertions.passed = 1;
    TestCaseStats tcStats1(*tcInfo, totals1, "", "", false);
    reporter->testCasePartialEnded(tcStats1, 0);
    
    // Second partial run
    reporter->testCasePartialStarting(*tcInfo, 1);
    SectionInfo sectionInfo2({"file.cpp", 1}, "section2"_sr);
    reporter->sectionStarting(sectionInfo2);
    Counts counts2;
    counts2.passed = 1;
    SectionStats sectionStats2(sectionInfo2, counts2, 0.001, false);
    reporter->sectionEnded(sectionStats2);
    Totals totals2;
    totals2.assertions.passed = 2;
    TestCaseStats tcStats2(*tcInfo, totals2, "", "", false);
    reporter->testCasePartialEnded(tcStats2, 1);
    
    reporter->testCaseEnded(tcStats2);
    
    Totals runTotals;
    runTotals.assertions.passed = 2;
    reporter->testRunEnded(TestRunStats(runInfo, runTotals, false));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}
