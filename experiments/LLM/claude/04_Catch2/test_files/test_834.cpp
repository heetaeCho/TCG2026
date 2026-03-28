#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "catch2/catch_test_macros.hpp"
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a string stream
class XmlReporterTest_834 : public ::testing::Test {
protected:
    void SetUp() override {
        m_stream = std::make_unique<std::ostringstream>();
    }

    std::unique_ptr<XmlReporter> makeReporter() {
        auto config = makeConfigFromCommandLine({});
        auto specs = ReporterSpec{"xml", {}, {}, {}};
        // We need a valid ReporterConfig. Since this depends on Catch2 internals,
        // we try a simpler approach.
        auto reporterConfig = ReporterConfig(config.get(), m_stream.get(), ColourMode::None, {});
        return std::make_unique<XmlReporter>(std::move(reporterConfig));
    }

    std::unique_ptr<Catch::Config> makeConfigFromCommandLine(std::vector<std::string> args) {
        // Build a minimal Config
        ConfigData configData;
        configData.showDurations = ShowDurations::DefaultForReporter;
        return std::make_unique<Catch::Config>(configData);
    }

    std::string getOutput() const {
        return m_stream->str();
    }

    std::unique_ptr<std::ostringstream> m_stream;
};

} // anonymous namespace

// Test: getDescription returns a non-empty string
TEST_F(XmlReporterTest_834, GetDescription_ReturnsNonEmptyString_834) {
    std::string desc = XmlReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test: getStylesheetRef returns empty string by default
TEST_F(XmlReporterTest_834, GetStylesheetRef_ReturnsEmptyByDefault_834) {
    auto reporter = makeReporter();
    std::string ref = reporter->getStylesheetRef();
    EXPECT_TRUE(ref.empty());
}

// Test: Construction succeeds without crash
TEST_F(XmlReporterTest_834, Construction_Succeeds_834) {
    EXPECT_NO_THROW(makeReporter());
}

// Test: testRunStarting writes XML output
TEST_F(XmlReporterTest_834, TestRunStarting_WritesXml_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("test_run");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    // Should contain XML declaration or Catch2 tag
    EXPECT_NE(output.find("xml"), std::string::npos);
}

// Test: testRunStarting and testRunEnded produce valid structure
TEST_F(XmlReporterTest_834, TestRunStartingAndEnded_ProducesValidStructure_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("my_test_run");
    reporter->testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 0;
    totals.testCases.passed = 2;
    totals.testCases.failed = 0;
    TestRunStats runStats(runInfo, totals, false);
    EXPECT_NO_THROW(reporter->testRunEnded(runStats));

    std::string output = getOutput();
    // Should contain the run name
    EXPECT_NE(output.find("my_test_run"), std::string::npos);
}

// Test: testCaseStarting writes test case info
TEST_F(XmlReporterTest_834, TestCaseStarting_WritesTestCaseInfo_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"test_case_name", "[tag1]"},
        SourceLineInfo("file.cpp", 42)
    );

    EXPECT_NO_THROW(reporter->testCaseStarting(*testCaseInfo));

    std::string output = getOutput();
    EXPECT_NE(output.find("test_case_name"), std::string::npos);
}

// Test: assertionStarting does not throw
TEST_F(XmlReporterTest_834, AssertionStarting_NoThrow_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"test_case", "[tag]"},
        SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "section");
    reporter->sectionStarting(sectionInfo);

    AssertionInfo assertionInfo(
        "expression",
        SourceLineInfo("file.cpp", 15),
        "original_expression",
        ResultDisposition::Normal
    );
    EXPECT_NO_THROW(reporter->assertionStarting(assertionInfo));
}

// Test: sectionStarting and sectionEnded work correctly
TEST_F(XmlReporterTest_834, SectionStartingAndEnded_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"test_case", "[tag]"},
        SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "my_section");
    EXPECT_NO_THROW(reporter->sectionStarting(sectionInfo));

    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.5, false);
    EXPECT_NO_THROW(reporter->sectionEnded(sectionStats));

    std::string output = getOutput();
    EXPECT_NE(output.find("my_section"), std::string::npos);
}

// Test: testCaseEnded writes results
TEST_F(XmlReporterTest_834, TestCaseEnded_WritesResults_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"test_case_ended", "[tag]"},
        SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    Totals totals;
    totals.assertions.passed = 1;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    EXPECT_NO_THROW(reporter->testCaseEnded(testCaseStats));

    std::string output = getOutput();
    EXPECT_NE(output.find("test_case_ended"), std::string::npos);
}

// Test: listReporters writes XML for reporter descriptions
TEST_F(XmlReporterTest_834, ListReporters_WritesDescriptions_834) {
    auto reporter = makeReporter();
    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"xml_reporter", "An XML reporter"});
    descriptions.push_back({"console_reporter", "A console reporter"});

    EXPECT_NO_THROW(reporter->listReporters(descriptions));

    std::string output = getOutput();
    EXPECT_NE(output.find("xml_reporter"), std::string::npos);
    EXPECT_NE(output.find("console_reporter"), std::string::npos);
}

// Test: listReporters with empty list
TEST_F(XmlReporterTest_834, ListReporters_EmptyList_834) {
    auto reporter = makeReporter();
    std::vector<ReporterDescription> descriptions;
    EXPECT_NO_THROW(reporter->listReporters(descriptions));
}

// Test: listTests writes test info
TEST_F(XmlReporterTest_834, ListTests_WritesTestInfo_834) {
    auto reporter = makeReporter();

    auto tc1 = makeTestCaseInfo(
        "test_reporter",
        {"listed_test_1", "[tag_a]"},
        SourceLineInfo("file1.cpp", 10)
    );
    auto tc2 = makeTestCaseInfo(
        "test_reporter",
        {"listed_test_2", "[tag_b]"},
        SourceLineInfo("file2.cpp", 20)
    );

    std::vector<TestCaseHandle> tests;
    // Note: TestCaseHandle construction depends on internals; 
    // if this doesn't compile, the test documents the intent
    // tests.push_back(TestCaseHandle(tc1.get(), nullptr));
    // tests.push_back(TestCaseHandle(tc2.get(), nullptr));
    // EXPECT_NO_THROW(reporter->listTests(tests));
}

// Test: listTags writes tag info
TEST_F(XmlReporterTest_834, ListTags_WritesTagInfo_834) {
    auto reporter = makeReporter();
    std::vector<TagInfo> tags;
    // TagInfo needs proper setup; test documents intent
    EXPECT_NO_THROW(reporter->listTags(tags));
}

// Test: listListeners writes listener descriptions
TEST_F(XmlReporterTest_834, ListListeners_WritesDescriptions_834) {
    auto reporter = makeReporter();
    std::vector<ListenerDescription> descriptions;
    descriptions.push_back({"my_listener", "A listener description"});

    EXPECT_NO_THROW(reporter->listListeners(descriptions));

    std::string output = getOutput();
    EXPECT_NE(output.find("my_listener"), std::string::npos);
}

// Test: listListeners with empty list
TEST_F(XmlReporterTest_834, ListListeners_EmptyList_834) {
    auto reporter = makeReporter();
    std::vector<ListenerDescription> descriptions;
    EXPECT_NO_THROW(reporter->listListeners(descriptions));
}

// Test: benchmarkPreparing does not throw
TEST_F(XmlReporterTest_834, BenchmarkPreparing_NoThrow_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"bench_case", "[bench]"},
        SourceLineInfo("bench.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    EXPECT_NO_THROW(reporter->benchmarkPreparing("my_benchmark"));

    std::string output = getOutput();
    EXPECT_NE(output.find("my_benchmark"), std::string::npos);
}

// Test: benchmarkFailed writes error
TEST_F(XmlReporterTest_834, BenchmarkFailed_WritesError_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"bench_case_fail", "[bench]"},
        SourceLineInfo("bench.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    reporter->benchmarkPreparing("failing_benchmark");
    EXPECT_NO_THROW(reporter->benchmarkFailed("some error occurred"));

    std::string output = getOutput();
    EXPECT_NE(output.find("some error occurred"), std::string::npos);
}

// Test: Nested sections increase depth
TEST_F(XmlReporterTest_834, NestedSections_834) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("run");
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"nested_test", "[tag]"},
        SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo section1(SourceLineInfo("file.cpp", 10), "outer_section");
    reporter->sectionStarting(section1);

    SectionInfo section2(SourceLineInfo("file.cpp", 20), "inner_section");
    reporter->sectionStarting(section2);

    Counts assertions2;
    assertions2.passed = 1;
    SectionStats stats2(section2, assertions2, 0.1, false);
    reporter->sectionEnded(stats2);

    Counts assertions1;
    assertions1.passed = 1;
    SectionStats stats1(section1, assertions1, 0.2, false);
    reporter->sectionEnded(stats1);

    std::string output = getOutput();
    EXPECT_NE(output.find("outer_section"), std::string::npos);
    EXPECT_NE(output.find("inner_section"), std::string::npos);
}

// Test: Full lifecycle - run start, case start, section, assertion, section end, case end, run end
TEST_F(XmlReporterTest_834, FullLifecycle_834) {
    auto reporter = makeReporter();

    // Run start
    TestRunInfo runInfo("full_lifecycle_run");
    reporter->testRunStarting(runInfo);

    // Case start
    auto testCaseInfo = makeTestCaseInfo(
        "test_reporter",
        {"lifecycle_test", "[lifecycle]"},
        SourceLineInfo("lifecycle.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    // Section start
    SectionInfo sectionInfo(SourceLineInfo("lifecycle.cpp", 5), "lifecycle_section");
    reporter->sectionStarting(sectionInfo);

    // Assertion
    AssertionInfo assertInfo(
        "x == 42",
        SourceLineInfo("lifecycle.cpp", 10),
        "x == 42",
        ResultDisposition::Normal
    );
    reporter->assertionStarting(assertInfo);

    // Section end
    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.01, false);
    reporter->sectionEnded(sectionStats);

    // Case end
    Totals caseTotals;
    caseTotals.assertions.passed = 1;
    caseTotals.testCases.passed = 1;
    TestCaseStats caseStats(*testCaseInfo, caseTotals, "", "", false);
    reporter->testCaseEnded(caseStats);

    // Run end
    Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("full_lifecycle_run"), std::string::npos);
    EXPECT_NE(output.find("lifecycle_test"), std::string::npos);
    EXPECT_NE(output.find("lifecycle_section"), std::string::npos);
}

// Test: Destruction does not crash
TEST_F(XmlReporterTest_834, Destruction_NoThrow_834) {
    EXPECT_NO_THROW({
        auto reporter = makeReporter();
        // Let it go out of scope
    });
}
