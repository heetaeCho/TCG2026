#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;

namespace {

// Helper to create a minimal ReporterConfig pointing to a given stream
class SonarQubeReporterTest_827 : public ::testing::Test {
protected:
    std::stringstream stream;
    
    std::unique_ptr<SonarQubeReporter> createReporter() {
        // We need a ReporterConfig with a stream
        // This depends on the actual Catch2 infrastructure
        auto config = Catch::Detail::make_unique<Catch::Config>(Catch::ConfigData{});
        ReporterConfig rconfig(config.get(), stream);
        return std::make_unique<SonarQubeReporter>(std::move(rconfig));
    }

    // Helper to build a TestRunNode with test cases in specified files
    using TestRunNode = CumulativeReporterBase::TestRunNode;
    using TestCaseNode = CumulativeReporterBase::TestCaseNode;
    using SectionNode = CumulativeReporterBase::SectionNode;

    struct TestFixtureData {
        std::vector<std::unique_ptr<TestCaseInfo>> testInfos;
        std::vector<std::unique_ptr<TestCaseNode>> testCaseNodes;
    };

    TestCaseNode* addTestCase(TestFixtureData& data,
                               TestRunNode& runNode,
                               const char* file,
                               std::size_t line,
                               const std::string& name) {
        SourceLineInfo sli(file, line);
        NameAndTags nat(name, "");
        auto info = std::make_unique<TestCaseInfo>(""_sr, nat, sli);
        
        Totals totals;
        TestCaseStats stats(*info, totals, "", "", false);
        
        auto node = std::make_unique<TestCaseNode>(stats);
        auto* nodePtr = node.get();
        
        data.testInfos.push_back(std::move(info));
        runNode.children.push_back(std::move(node));
        
        return nodePtr;
    }
};

// Test: writeRun with empty run (no children)
TEST_F(SonarQubeReporterTest_827, WriteRunEmptyChildren_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("empty_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    TestRunNode runNode(runStats);
    
    // Should not crash with no children
    EXPECT_NO_THROW(reporter->writeRun(runNode));
    
    // Stream should contain XML but no <file> elements
    std::string output = stream.str();
    EXPECT_EQ(output.find("<file"), std::string::npos);
}

// Test: writeRun with single test case in single file
TEST_F(SonarQubeReporterTest_827, WriteRunSingleTestSingleFile_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("single_test_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    TestRunNode runNode(runStats);
    
    TestFixtureData fixtureData;
    addTestCase(fixtureData, runNode, "test_file.cpp", 10, "TestCase1");
    
    EXPECT_NO_THROW(reporter->writeRun(runNode));
    
    std::string output = stream.str();
    // Should contain a reference to the file
    EXPECT_NE(output.find("test_file.cpp"), std::string::npos);
}

// Test: writeRun with multiple test cases in same file
TEST_F(SonarQubeReporterTest_827, WriteRunMultipleTestsSameFile_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("multi_test_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    TestRunNode runNode(runStats);
    
    TestFixtureData fixtureData;
    addTestCase(fixtureData, runNode, "common_file.cpp", 10, "TestA");
    addTestCase(fixtureData, runNode, "common_file.cpp", 20, "TestB");
    addTestCase(fixtureData, runNode, "common_file.cpp", 30, "TestC");
    
    EXPECT_NO_THROW(reporter->writeRun(runNode));
    
    std::string output = stream.str();
    // File should appear in output
    EXPECT_NE(output.find("common_file.cpp"), std::string::npos);
    
    // The file element should appear only once (tests grouped under one file)
    std::size_t firstPos = output.find("common_file.cpp");
    // There might be multiple occurrences due to testCase elements, but the file tag should group them
}

// Test: writeRun with test cases across multiple files
TEST_F(SonarQubeReporterTest_827, WriteRunMultipleFiles_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("multi_file_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    TestRunNode runNode(runStats);
    
    TestFixtureData fixtureData;
    addTestCase(fixtureData, runNode, "file_a.cpp", 10, "TestInFileA");
    addTestCase(fixtureData, runNode, "file_b.cpp", 20, "TestInFileB");
    addTestCase(fixtureData, runNode, "file_a.cpp", 30, "AnotherTestInFileA");
    
    EXPECT_NO_THROW(reporter->writeRun(runNode));
    
    std::string output = stream.str();
    // Both files should appear in output
    EXPECT_NE(output.find("file_a.cpp"), std::string::npos);
    EXPECT_NE(output.find("file_b.cpp"), std::string::npos);
}

// Test: writeRun groups tests correctly by file
TEST_F(SonarQubeReporterTest_827, WriteRunGroupsByFile_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("grouping_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    TestRunNode runNode(runStats);
    
    TestFixtureData fixtureData;
    addTestCase(fixtureData, runNode, "alpha.cpp", 1, "Test1");
    addTestCase(fixtureData, runNode, "beta.cpp", 2, "Test2");
    addTestCase(fixtureData, runNode, "gamma.cpp", 3, "Test3");
    addTestCase(fixtureData, runNode, "alpha.cpp", 4, "Test4");
    addTestCase(fixtureData, runNode, "beta.cpp", 5, "Test5");
    
    EXPECT_NO_THROW(reporter->writeRun(runNode));
    
    std::string output = stream.str();
    // All three files should be present
    EXPECT_NE(output.find("alpha.cpp"), std::string::npos);
    EXPECT_NE(output.find("beta.cpp"), std::string::npos);
    EXPECT_NE(output.find("gamma.cpp"), std::string::npos);
}

// Test: getDescription returns a non-empty string
TEST_F(SonarQubeReporterTest_827, GetDescriptionReturnsNonEmpty_827) {
    std::string desc = SonarQubeReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test: writeRun output contains valid XML structure elements
TEST_F(SonarQubeReporterTest_827, WriteRunProducesXmlOutput_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("xml_test_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    TestRunNode runNode(runStats);
    
    TestFixtureData fixtureData;
    addTestCase(fixtureData, runNode, "mytest.cpp", 42, "MyTest");
    
    reporter->writeRun(runNode);
    
    std::string output = stream.str();
    // SonarQube format should contain <testExecutions> and <file> elements
    EXPECT_NE(output.find("testExecutions"), std::string::npos);
    EXPECT_NE(output.find("file"), std::string::npos);
}

// Test: writeRun with a single file containing a single test produces testCase element
TEST_F(SonarQubeReporterTest_827, WriteRunProducesTestCaseElement_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("testcase_element_run");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    TestRunNode runNode(runStats);
    
    TestFixtureData fixtureData;
    addTestCase(fixtureData, runNode, "example.cpp", 100, "ExampleTest");
    
    reporter->writeRun(runNode);
    
    std::string output = stream.str();
    // Should contain testCase element with the test name
    EXPECT_NE(output.find("testCase"), std::string::npos);
    EXPECT_NE(output.find("ExampleTest"), std::string::npos);
}

// Test: testRunEndedCumulative produces output
TEST_F(SonarQubeReporterTest_827, TestRunEndedCumulativeProducesOutput_827) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("cumulative_run");
    reporter->testRunStarting(runInfo);
    
    // After ending, the stream should have some content
    // testRunEndedCumulative is called by the framework
    reporter->testRunEndedCumulative();
    
    std::string output = stream.str();
    // Should produce some XML output (at minimum the root element)
    EXPECT_FALSE(output.empty());
}

} // anonymous namespace
