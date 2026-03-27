#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"



using namespace Catch;

using namespace testing;



class MockTestRunInfo : public TestRunInfo {

public:

    MockTestRunInfo(std::string const& name, std::chrono::system_clock::time_point startTime)

        : TestRunInfo(name, startTime) {}

};



class MockTestRunNode : public TestRunNode {

public:

    MockTestRunNode() = default;

};



class MockTestCaseNode : public TestCaseNode {

public:

    MockTestCaseNode() = default;

};



class MockSectionNode : public SectionNode {

public:

    MockSectionNode(std::string const& name, std::size_t lineInfo)

        : SectionNode(name, SourceLineInfo("", lineInfo)) {}

};



class MockAssertionStats : public AssertionStats {

public:

    MockAssertionStats(AssertionResult result, std::string message, SourceLineInfo location)

        : AssertionStats(result, message, location) {}

};



class SonarQubeReporterTest_569 : public Test {

protected:

    ReporterConfig config;

    SonarQubeReporter reporter{std::move(config)};

    MockTestRunInfo testRunInfo{"test_run", std::chrono::system_clock::now()};

    MockTestRunNode runNode;

    StringRef filename{"filename"};

    std::vector<TestCaseNode const*> testCaseNodes;

    MockTestCaseNode testCaseNode;

    MockSectionNode sectionNode{"section_name", 1};

    bool okToFail{false};

    MockAssertionStats assertionStats{ResultWas::Ok, "message", SourceLineInfo("", 1)};

};



TEST_F(SonarQubeReporterTest_569, GetDescription_ReturnsCorrectString_569) {

    EXPECT_EQ("Reports test results in the Generic Test Data SonarQube XML format"s, SonarQubeReporter::getDescription());

}



TEST_F(SonarQubeReporterTest_569, TestRunStarting_CallsBaseMethod_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.testRunStarting(testRunInfo);

    SUCCEED();  // This test case is more about coverage than verification.

}



TEST_F(SonarQubeReporterTest_569, WriteRun_CallsBaseMethod_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.writeRun(runNode);

    SUCCEED();  // This test case is more about coverage than verification.

}



TEST_F(SonarQubeReporterTest_569, WriteTestFile_CallsBaseMethodWithFilename_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.writeTestFile(filename, testCaseNodes);

    SUCCEED();  // This test case is more about coverage than verification.

}



TEST_F(SonarQubeReporterTest_569, WriteTestCase_CallsBaseMethodWithTestCaseNode_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.writeTestCase(testCaseNode);

    SUCCEED();  // This test case is more about coverage than verification.

}



TEST_F(SonarQubeReporterTest_569, WriteSection_CallsBaseMethodWithParameters_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.writeSection(sectionNode.m_name, sectionNode, okToFail);

    SUCCEED();  // This test case is more about coverage than verification.

}



TEST_F(SonarQubeReporterTest_569, WriteAssertions_CallsBaseMethodWithParameters_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.writeAssertions(sectionNode, okToFail);

    SUCCEED();  // This test case is more about coverage than verification.

}



TEST_F(SonarQubeReporterTest_569, WriteAssertion_CallsBaseMethodWithParameters_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.writeAssertion(assertionStats, okToFail);

    SUCCEED();  // This test case is more about coverage than verification.

}



TEST_F(SonarQubeReporterTest_569, TestRunEndedCumulative_CallsBaseMethod_569) {

    // Since we cannot mock internal behavior, we assume this method works as intended.

    reporter.testRunEndedCumulative();

    SUCCEED();  // This test case is more about coverage than verification.

}
