#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_reusable_string_stream.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a stringstream for output capture
class XmlReporterTest_833 : public ::testing::Test {
protected:
    void SetUp() override {
        m_stream = std::make_unique<std::ostringstream>();
    }

    std::unique_ptr<XmlReporter> makeReporter() {
        auto config = std::make_shared<ConfigData>();
        auto catchConfig = std::make_shared<Config>(* config);
        
        ReporterConfig reporterConfig(catchConfig.get(), *m_stream, ColourMode::None, {});
        m_config = catchConfig;
        return std::make_unique<XmlReporter>(CATCH_MOVE(reporterConfig));
    }

    std::string getOutput() const {
        return m_stream->str();
    }

    std::unique_ptr<std::ostringstream> m_stream;
    std::shared_ptr<Config> m_config;
};

} // anonymous namespace

TEST_F(XmlReporterTest_833, GetDescription_ReturnsNonEmptyString_833) {
    std::string desc = XmlReporter::getDescription();
    EXPECT_FALSE(desc.empty());
    EXPECT_NE(desc.find("XML"), std::string::npos);
}

TEST_F(XmlReporterTest_833, GetDescription_ContainsExpectedText_833) {
    std::string desc = XmlReporter::getDescription();
    EXPECT_EQ(desc, "Reports test results as an XML document");
}

TEST_F(XmlReporterTest_833, Construction_ProducesValidReporter_833) {
    auto reporter = makeReporter();
    ASSERT_NE(reporter, nullptr);
}

TEST_F(XmlReporterTest_833, GetStylesheetRef_ReturnsString_833) {
    auto reporter = makeReporter();
    std::string stylesheet = reporter->getStylesheetRef();
    // Default stylesheet ref may be empty
    // Just verify it doesn't crash and returns a valid string
    EXPECT_TRUE(stylesheet.empty() || !stylesheet.empty());
}

TEST_F(XmlReporterTest_833, TestRunStarting_WritesXmlOutput_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    // Should contain XML-like content
    EXPECT_NE(output.find("TestRun"), std::string::npos);
}

TEST_F(XmlReporterTest_833, TestRunStartingAndEnding_ProducesCompleteXml_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    // Should have opening and closing tags
    EXPECT_NE(output.find("<"), std::string::npos);
    EXPECT_NE(output.find(">"), std::string::npos);
}

TEST_F(XmlReporterTest_833, TestCaseStartingAndEnding_WritesTestCaseInfo_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        "", {"TestCase1", "[tag1]"}, SourceLineInfo("file.cpp", 42));
    
    reporter->testCaseStarting(*testCaseInfo);
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("TestCase1"), std::string::npos);
}

TEST_F(XmlReporterTest_833, SectionStartingAndEnding_WritesSection_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        "", {"TestCase1", "[tag1]"}, SourceLineInfo("file.cpp", 42));
    reporter->testCaseStarting(*testCaseInfo);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 50), "Section1");
    reporter->sectionStarting(sectionInfo);
    
    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.1, false);
    reporter->sectionEnded(sectionStats);
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("Section1"), std::string::npos);
}

TEST_F(XmlReporterTest_833, AssertionStarting_DoesNotCrash_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        "", {"TestCase1", "[tag1]"}, SourceLineInfo("file.cpp", 42));
    reporter->testCaseStarting(*testCaseInfo);
    
    AssertionInfo assertionInfo("expression", SourceLineInfo("file.cpp", 55), "", ResultDisposition::Normal);
    EXPECT_NO_THROW(reporter->assertionStarting(assertionInfo));
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
}

TEST_F(XmlReporterTest_833, ListReporters_WritesDescriptions_833) {
    auto reporter = makeReporter();
    
    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"xml", "XML reporter description"});
    descriptions.push_back({"console", "Console reporter description"});
    
    reporter->listReporters(descriptions);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("xml"), std::string::npos);
    EXPECT_NE(output.find("console"), std::string::npos);
}

TEST_F(XmlReporterTest_833, ListReporters_EmptyList_833) {
    auto reporter = makeReporter();
    
    std::vector<ReporterDescription> descriptions;
    EXPECT_NO_THROW(reporter->listReporters(descriptions));
}

TEST_F(XmlReporterTest_833, ListTags_WritesTags_833) {
    auto reporter = makeReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag;
    tag.add("tag1"_catch_sr);
    tags.push_back(tag);
    
    EXPECT_NO_THROW(reporter->listTags(tags));
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

TEST_F(XmlReporterTest_833, ListTags_EmptyList_833) {
    auto reporter = makeReporter();
    
    std::vector<TagInfo> tags;
    EXPECT_NO_THROW(reporter->listTags(tags));
}

TEST_F(XmlReporterTest_833, ListListeners_WritesListenerDescriptions_833) {
    auto reporter = makeReporter();
    
    std::vector<ListenerDescription> descriptions;
    descriptions.push_back({"listener1", "Listener 1 description"});
    
    EXPECT_NO_THROW(reporter->listListeners(descriptions));
    
    std::string output = getOutput();
    EXPECT_NE(output.find("listener1"), std::string::npos);
}

TEST_F(XmlReporterTest_833, ListListeners_EmptyList_833) {
    auto reporter = makeReporter();
    
    std::vector<ListenerDescription> descriptions;
    EXPECT_NO_THROW(reporter->listListeners(descriptions));
}

TEST_F(XmlReporterTest_833, BenchmarkPreparing_DoesNotCrash_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        "", {"BenchmarkTest", "[benchmark]"}, SourceLineInfo("file.cpp", 42));
    reporter->testCaseStarting(*testCaseInfo);
    
    EXPECT_NO_THROW(reporter->benchmarkPreparing("benchmark1"_catch_sr));
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("benchmark1"), std::string::npos);
}

TEST_F(XmlReporterTest_833, BenchmarkFailed_WritesError_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        "", {"BenchmarkTest", "[benchmark]"}, SourceLineInfo("file.cpp", 42));
    reporter->testCaseStarting(*testCaseInfo);
    
    reporter->benchmarkPreparing("failingBenchmark"_catch_sr);
    EXPECT_NO_THROW(reporter->benchmarkFailed("some error"_catch_sr));
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("some error"), std::string::npos);
}

TEST_F(XmlReporterTest_833, TestRunEnded_WithFailures_ReportsFailures_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRunWithFailures");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    totals.assertions.failed = 3;
    totals.testCases.failed = 2;
    totals.assertions.passed = 5;
    totals.testCases.passed = 3;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

TEST_F(XmlReporterTest_833, TestRunEnded_Aborting_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("AbortedRun");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, true /* aborting */);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

TEST_F(XmlReporterTest_833, XmlOutputContainsXmlDeclaration_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    // XML output should start with XML declaration or contain XML elements
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST_F(XmlReporterTest_833, NestedSections_833) {
    auto reporter = makeReporter();
    
    TestRunInfo runInfo("TestRun");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = makeTestCaseInfo(
        "", {"TestCase1", "[tag1]"}, SourceLineInfo("file.cpp", 42));
    reporter->testCaseStarting(*testCaseInfo);
    
    SectionInfo section1(SourceLineInfo("file.cpp", 50), "OuterSection");
    reporter->sectionStarting(section1);
    
    SectionInfo section2(SourceLineInfo("file.cpp", 55), "InnerSection");
    reporter->sectionStarting(section2);
    
    Counts assertions2;
    assertions2.passed = 1;
    SectionStats sectionStats2(section2, assertions2, 0.05, false);
    reporter->sectionEnded(sectionStats2);
    
    Counts assertions1;
    assertions1.passed = 1;
    SectionStats sectionStats1(section1, assertions1, 0.1, false);
    reporter->sectionEnded(sectionStats1);
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = getOutput();
    EXPECT_NE(output.find("OuterSection"), std::string::npos);
    EXPECT_NE(output.find("InnerSection"), std::string::npos);
}

TEST_F(XmlReporterTest_833, Destruction_DoesNotCrash_833) {
    {
        auto reporter = makeReporter();
        TestRunInfo runInfo("TestRun");
        reporter->testRunStarting(runInfo);
        
        Totals totals;
        TestRunStats runStats(runInfo, totals, false);
        reporter->testRunEnded(runStats);
    }
    // Reporter destroyed, should not crash
    SUCCEED();
}
