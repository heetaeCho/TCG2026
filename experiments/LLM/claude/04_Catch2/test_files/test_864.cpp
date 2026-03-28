#include <catch2/reporters/catch_reporter_json.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_reporter_registry.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_context.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_test_case_info_hasher.hpp>
#include <catch2/benchmark/catch_benchmark_stats.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <vector>
#include <string>

using namespace Catch;

namespace {

// Helper to create a minimal ReporterConfig
class JsonReporterTestFixture : public ::testing::Test {
protected:
    std::stringstream ss;
    std::unique_ptr<JsonReporter> reporter;

    void SetUp() override {
        // We need to create a ReporterConfig. This requires an IConfig and an ostream.
        // We'll create a minimal config for testing.
        auto configData = std::make_shared<ConfigData>();
        auto config = std::make_shared<Config>(std::move(*configData));
        
        ReporterConfig reporterConfig(config.get(), ss, ColourMode::None, {});
        reporter = std::make_unique<JsonReporter>(std::move(reporterConfig));
        
        // Store config to keep it alive
        storedConfig = config;
    }

    void TearDown() override {
        reporter.reset();
    }

    std::shared_ptr<Config> storedConfig;
};

} // anonymous namespace

// Test getDescription returns expected string
TEST_F(JsonReporterTestFixture, GetDescription_ReturnsExpectedString_864) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
    EXPECT_NE(desc.find("JSON"), std::string::npos);
}

// Test that testRunStarting produces JSON output
TEST_F(JsonReporterTestFixture, TestRunStarting_ProducesOutput_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    // After starting a test run, some JSON should be written to the stream
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test full test run lifecycle (start + end)
TEST_F(JsonReporterTestFixture, TestRunLifecycle_ProducesValidOutput_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    // Should contain JSON-like content
    EXPECT_NE(output.find("{"), std::string::npos);
}

// Test testCaseStarting within a test run
TEST_F(JsonReporterTestFixture, TestCaseStarting_WithinRun_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test full test case lifecycle
TEST_F(JsonReporterTestFixture, TestCaseLifecycle_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    
    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test sectionStarting and sectionEnded
TEST_F(JsonReporterTestFixture, SectionLifecycle_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "section_name");
    reporter->sectionStarting(sectionInfo);
    
    Assertions::Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.5, false);
    reporter->sectionEnded(sectionStats);
    
    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("section_name"), std::string::npos);
}

// Test assertionStarting (should be callable without crash)
TEST_F(JsonReporterTestFixture, AssertionStarting_NoThrow_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "root");
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertionInfo("expr", SourceLineInfo("file.cpp", 20), "", ResultDisposition::Normal);
    EXPECT_NO_THROW(reporter->assertionStarting(assertionInfo));
}

// Test assertionEnded
TEST_F(JsonReporterTestFixture, AssertionEnded_ProducesOutput_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "root");
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertionInfo("expr", SourceLineInfo("file.cpp", 20), "", ResultDisposition::Normal);
    
    AssertionResultData resultData(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(assertionInfo, std::move(resultData));
    
    std::vector<MessageInfo> infoMessages;
    Counts counts;
    counts.passed = 1;
    AssertionStats assertionStats(result, infoMessages, counts);
    
    EXPECT_NO_THROW(reporter->assertionEnded(assertionStats));
}

// Test listReporters
TEST_F(JsonReporterTestFixture, ListReporters_ProducesJsonOutput_864) {
    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"json", "JSON reporter"});
    descriptions.push_back({"console", "Console reporter"});
    
    reporter->listReporters(descriptions);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("json"), std::string::npos);
    EXPECT_NE(output.find("console"), std::string::npos);
}

// Test listReporters with empty list
TEST_F(JsonReporterTestFixture, ListReporters_EmptyList_864) {
    std::vector<ReporterDescription> descriptions;
    
    EXPECT_NO_THROW(reporter->listReporters(descriptions));
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test listListeners
TEST_F(JsonReporterTestFixture, ListListeners_ProducesOutput_864) {
    std::vector<ListenerDescription> descriptions;
    descriptions.push_back({"listener1", "A test listener"});
    
    reporter->listListeners(descriptions);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("listener1"), std::string::npos);
}

// Test listListeners with empty list
TEST_F(JsonReporterTestFixture, ListListeners_EmptyList_864) {
    std::vector<ListenerDescription> descriptions;
    
    EXPECT_NO_THROW(reporter->listListeners(descriptions));
}

// Test listTags
TEST_F(JsonReporterTestFixture, ListTags_ProducesOutput_864) {
    std::vector<TagInfo> tags;
    TagInfo tag;
    tag.add("[tag1]"_catch_sr);
    tag.count = 5;
    tags.push_back(tag);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test listTags with empty list
TEST_F(JsonReporterTestFixture, ListTags_EmptyList_864) {
    std::vector<TagInfo> tags;
    
    EXPECT_NO_THROW(reporter->listTags(tags));
}

// Test benchmarkPreparing
TEST_F(JsonReporterTestFixture, BenchmarkPreparing_NoThrow_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"bench_test"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "root");
    reporter->sectionStarting(sectionInfo);
    
    EXPECT_NO_THROW(reporter->benchmarkPreparing("bench_name"_catch_sr));
}

// Test benchmarkFailed
TEST_F(JsonReporterTestFixture, BenchmarkFailed_ProducesOutput_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"bench_test"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "root");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("bench_name"_catch_sr);
    EXPECT_NO_THROW(reporter->benchmarkFailed("some error"_catch_sr));
    
    std::string output = ss.str();
    EXPECT_NE(output.find("some error"), std::string::npos);
}

// Test testCasePartialStarting and testCasePartialEnded
TEST_F(JsonReporterTestFixture, TestCasePartialLifecycle_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    
    EXPECT_NO_THROW(reporter->testCasePartialStarting(*tcInfo, 0));
    
    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    EXPECT_NO_THROW(reporter->testCasePartialEnded(tcStats, 0));
    
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);
}

// Test multiple partial runs
TEST_F(JsonReporterTestFixture, MultiplePartialRuns_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    
    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    
    // First partial
    reporter->testCasePartialStarting(*tcInfo, 0);
    reporter->testCasePartialEnded(tcStats, 0);
    
    // Second partial
    reporter->testCasePartialStarting(*tcInfo, 1);
    reporter->testCasePartialEnded(tcStats, 1);
    
    reporter->testCaseEnded(tcStats);
    
    Totals runTotals;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// Test getDescription is a static method returning non-empty string
TEST(JsonReporterStaticTest_864, GetDescription_NonEmpty_864) {
    std::string desc = Catch::JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
    EXPECT_NE(desc.find("JSON"), std::string::npos);
}

// Test that output contains run name
TEST_F(JsonReporterTestFixture, TestRunOutput_ContainsRunName_864) {
    TestRunInfo runInfo("my_unique_run_name");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = ss.str();
    EXPECT_NE(output.find("my_unique_run_name"), std::string::npos);
}

// Test that failed assertion is captured
TEST_F(JsonReporterTestFixture, FailedAssertion_CapturedInOutput_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo("", {"test_case"}, SourceLineInfo("file.cpp", 1));
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "root");
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertionInfo("1 == 2", SourceLineInfo("file.cpp", 20), "", ResultDisposition::Normal);
    
    AssertionResultData resultData(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(assertionInfo, std::move(resultData));
    
    std::vector<MessageInfo> infoMessages;
    Counts counts;
    counts.failed = 1;
    AssertionStats assertionStats(result, infoMessages, counts);
    
    reporter->assertionEnded(assertionStats);
    
    std::string output = ss.str();
    // Failed assertions should appear in output
    EXPECT_NE(output.find("1 == 2"), std::string::npos);
}

// Test that test run with aborting flag works
TEST_F(JsonReporterTestFixture, TestRunEnded_WithAborting_864) {
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, true); // aborting = true
    EXPECT_NO_THROW(reporter->testRunEnded(runStats));
}
