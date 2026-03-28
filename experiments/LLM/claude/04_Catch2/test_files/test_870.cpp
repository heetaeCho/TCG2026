#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/internal/catch_istream.hpp"

using namespace Catch;

namespace {

// Helper to create a minimal IConfig mock or use a real config
class MockConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1; }
    TestSpec const& testSpec() const override { return m_testSpec; }
    bool hasTestFilters() const override { return false; }
    std::vector<ReporterSpec> const& getReporterSpecs() const override { return m_reporterSpecs; }
    std::vector<std::string> const& getSectionsToRun() const override { return m_sections; }
    unsigned int rngSeed() const override { return 0; }
    UseColour colourMode() const override { return UseColour::Auto; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    bool shouldDebugBreak() const override { return false; }
    int shardCount() const override { return 1; }
    int shardIndex() const override { return 0; }
    
private:
    TestSpec m_testSpec;
    std::vector<ReporterSpec> m_reporterSpecs;
    std::vector<std::string> m_sections;
};

class JsonReporterTest_870 : public ::testing::Test {
protected:
    void SetUp() override {
        m_config = std::make_shared<MockConfig>();
        m_stream = std::make_unique<std::ostringstream>();
        m_streamPtr = m_stream.get();
    }

    std::unique_ptr<JsonReporter> createReporter() {
        // Create ReporterConfig with the stream and config
        auto config = ReporterConfig(m_config.get(), Detail::make_unique<std::ostream>(m_streamPtr), ColourMode::None, {});
        return std::make_unique<JsonReporter>(CATCH_MOVE(config));
    }

    std::string getOutput() const {
        return m_streamPtr->str();
    }

    std::shared_ptr<MockConfig> m_config;
    std::unique_ptr<std::ostringstream> m_stream;
    std::ostringstream* m_streamPtr;
};

} // anonymous namespace

TEST(JsonReporterStaticTest_870, GetDescription_870) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JsonReporterTest_870, TestRunStartingProducesOutput_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
    
    std::string output = getOutput();
    // Should produce some JSON output containing the run name
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_870, TestRunStartingAndEnding_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 0;
    totals.testCases.passed = 1;
    totals.testCases.failed = 0;
    
    TestRunStats runStats(runInfo, totals, false);
    EXPECT_NO_THROW(reporter->testRunEnded(runStats));
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_870, TestCaseLifecycle_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    
    EXPECT_NO_THROW(reporter->testCaseStarting(*tcInfo));
    
    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    EXPECT_NO_THROW(reporter->testCaseEnded(tcStats));
}

TEST_F(JsonReporterTest_870, SectionStartingAndEnding_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "test section");
    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));
    
    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.1, false);
    EXPECT_NO_THROW(reporter->sectionEnded(sectionStats));
}

TEST_F(JsonReporterTest_870, SectionOutputContainsName_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "my_unique_section_name");
    reporter->sectionStarting(sectionInfo);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("my_unique_section_name"), std::string::npos);
}

TEST_F(JsonReporterTest_870, SectionOutputContainsSectionKind_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "test section");
    reporter->sectionStarting(sectionInfo);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("section"), std::string::npos);
}

TEST_F(JsonReporterTest_870, SectionOutputContainsSourceInfo_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("source_file.cpp", 42), "test section");
    reporter->sectionStarting(sectionInfo);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("source_file.cpp"), std::string::npos);
}

TEST_F(JsonReporterTest_870, AssertionStartingDoesNotThrow_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "test section");
    reporter->sectionStarting(sectionInfo);
    
    AssertionInfo assertionInfo(
        "test",
        SourceLineInfo("file.cpp", 25),
        "expression",
        ResultDisposition::Normal
    );
    EXPECT_NO_THROW(reporter->assertionStarting(assertionInfo));
}

TEST_F(JsonReporterTest_870, NestedSections_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo1(SourceLineInfo("file.cpp", 20), "outer section");
    reporter->sectionStarting(sectionInfo1);
    
    SectionInfo sectionInfo2(SourceLineInfo("file.cpp", 30), "inner section");
    reporter->sectionStarting(sectionInfo2);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("outer section"), std::string::npos);
    EXPECT_NE(output.find("inner section"), std::string::npos);
    
    Counts assertions;
    SectionStats sectionStats2(sectionInfo2, assertions, 0.01, false);
    EXPECT_NO_THROW(reporter->sectionEnded(sectionStats2));
    
    SectionStats sectionStats1(sectionInfo1, assertions, 0.02, false);
    EXPECT_NO_THROW(reporter->sectionEnded(sectionStats1));
}

TEST_F(JsonReporterTest_870, FullTestRunLifecycle_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("full_lifecycle_test");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "main section");
    reporter->sectionStarting(sectionInfo);
    
    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.01, false);
    reporter->sectionEnded(sectionStats);
    
    Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;
    
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);
    
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("full_lifecycle_test"), std::string::npos);
}

TEST_F(JsonReporterTest_870, EmptySectionName_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "");
    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));
}

TEST_F(JsonReporterTest_870, SectionWithSpecialCharactersInName_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "section with \"quotes\" and \\backslash");
    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));
    
    std::string output = getOutput();
    // The JSON writer should properly escape special characters
    EXPECT_NE(output.find("section"), std::string::npos);
}

TEST_F(JsonReporterTest_870, BenchmarkPreparing_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"benchmark test", "[benchmark]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "benchmark section");
    reporter->sectionStarting(sectionInfo);
    
    EXPECT_NO_THROW(reporter->benchmarkPreparing("bench1"_sr));
}

TEST_F(JsonReporterTest_870, BenchmarkFailed_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"benchmark test", "[benchmark]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "benchmark section");
    reporter->sectionStarting(sectionInfo);
    
    reporter->benchmarkPreparing("bench1"_sr);
    
    EXPECT_NO_THROW(reporter->benchmarkFailed("some error"_sr));
    
    std::string output = getOutput();
    EXPECT_NE(output.find("some error"), std::string::npos);
}

TEST_F(JsonReporterTest_870, TestCasePartialStartingAndEnding_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag1]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    
    EXPECT_NO_THROW(reporter->testCasePartialStarting(*tcInfo, 0));
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "section");
    reporter->sectionStarting(sectionInfo);
    
    Counts assertions;
    SectionStats sectionStats(sectionInfo, assertions, 0.01, false);
    reporter->sectionEnded(sectionStats);
    
    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    EXPECT_NO_THROW(reporter->testCasePartialEnded(tcStats, 0));
}

TEST_F(JsonReporterTest_870, MultipleTestCases_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    for (int i = 0; i < 3; ++i) {
        std::string name = "test case " + std::to_string(i);
        auto tcInfo = makeTestCaseInfo(
            "test_reporter",
            {name, "[tag1]"},
            SourceLineInfo("file.cpp", 10 + i * 10)
        );
        reporter->testCaseStarting(*tcInfo);
        reporter->testCasePartialStarting(*tcInfo, 0);
        
        SectionInfo sectionInfo(SourceLineInfo("file.cpp", 15 + i * 10), "section " + std::to_string(i));
        reporter->sectionStarting(sectionInfo);
        
        Counts assertions;
        assertions.passed = 1;
        SectionStats sectionStats(sectionInfo, assertions, 0.01, false);
        reporter->sectionEnded(sectionStats);
        
        Totals totals;
        totals.assertions.passed = 1;
        TestCaseStats tcStats(*tcInfo, totals, "", "", false);
        reporter->testCasePartialEnded(tcStats, 0);
        reporter->testCaseEnded(tcStats);
    }
    
    Totals totals;
    totals.assertions.passed = 3;
    totals.testCases.passed = 3;
    TestRunStats runStats(runInfo, totals, false);
    EXPECT_NO_THROW(reporter->testRunEnded(runStats));
    
    std::string output = getOutput();
    EXPECT_NE(output.find("test case 0"), std::string::npos);
    EXPECT_NE(output.find("test case 1"), std::string::npos);
    EXPECT_NE(output.find("test case 2"), std::string::npos);
}

TEST_F(JsonReporterTest_870, OutputContainsKindField_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case", "[tag]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "my section");
    reporter->sectionStarting(sectionInfo);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("kind"), std::string::npos);
    EXPECT_NE(output.find("section"), std::string::npos);
}

TEST_F(JsonReporterTest_870, OutputContainsNameField_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case", "[tag]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "unique_section_xyz");
    reporter->sectionStarting(sectionInfo);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("unique_section_xyz"), std::string::npos);
}

TEST_F(JsonReporterTest_870, OutputContainsPathArray_870) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case", "[tag]"},
        SourceLineInfo("file.cpp", 10)
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 20), "section");
    reporter->sectionStarting(sectionInfo);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("path"), std::string::npos);
}
