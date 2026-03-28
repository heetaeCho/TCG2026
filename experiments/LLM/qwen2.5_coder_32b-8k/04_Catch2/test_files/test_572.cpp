#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_teamcity.hpp"



using namespace Catch;



class TeamCityReporterTest_572 : public ::testing::Test {

protected:

    ReporterConfig config;

    TeamCityReporter reporter;

    

    TeamCityReporterTest_572() : reporter(std::move(config)) {}

};



TEST_F(TeamCityReporterTest_572, GetDescriptionReturnsCorrectString_572) {

    EXPECT_EQ("Reports test results as TeamCity service messages", TeamCityReporter::getDescription());

}



// Mocking the output stream for printSectionHeader

class MockOutputStream : public std::ostream {

public:

    using std::ostream::ostream;

};



TEST_F(TeamCityReporterTest_572, PrintSectionHeaderDoesNotThrow_572) {

    MockOutputStream mockOs;

    EXPECT_NO_THROW(reporter.printSectionHeader(mockOs));

}



// Mocking the TestRunInfo and TestRunStats for testRunStarting and testRunEnded

class MockTestRunInfo : public TestRunInfo {

public:

    MockTestRunInfo() : TestRunInfo("MockRun", "MockName") {}

};



class MockTestRunStats : public TestRunStats {

public:

    MockTestRunStats(const TestRunInfo& runInfo) : TestRunStats(runInfo, std::vector<TestCaseStats>()) {}

};



TEST_F(TeamCityReporterTest_572, TestRunStartingDoesNotThrow_572) {

    MockTestRunInfo mockRunInfo;

    EXPECT_NO_THROW(reporter.testRunStarting(mockRunInfo));

}



TEST_F(TeamCityReporterTest_572, TestRunEndedDoesNotThrow_572) {

    MockTestRunInfo mockRunInfo;

    MockTestRunStats mockRunStats(mockRunInfo);

    EXPECT_NO_THROW(reporter.testRunEnded(mockRunStats));

}



// Mocking the AssertionStats for assertionEnded

class MockAssertionStats : public AssertionStats {

public:

    MockAssertionStats() : AssertionStats(AssertionResult(), "", "", 0) {}

};



TEST_F(TeamCityReporterTest_572, AssertionEndedDoesNotThrow_572) {

    MockAssertionStats mockAssertionStats;

    EXPECT_NO_THROW(reporter.assertionEnded(mockAssertionStats));

}



// Mocking the TestCaseInfo and TestCaseStats for testCaseStarting and testCaseEnded

class MockTestCaseInfo : public TestCaseInfo {

public:

    MockTestCaseInfo() : TestCaseInfo("MockName", "MockDescription", SourceLineInfo("", 0), Tags()) {}

};



class MockTestCaseStats : public TestCaseStats {

public:

    MockTestCaseStats(const TestCaseInfo& testInfo) : TestCaseStats(testInfo, std::vector<AssertionResult>()) {}

};



TEST_F(TeamCityReporterTest_572, TestCaseStartingDoesNotThrow_572) {

    MockTestCaseInfo mockCaseInfo;

    EXPECT_NO_THROW(reporter.testCaseStarting(mockCaseInfo));

}



TEST_F(TeamCityReporterTest_572, TestCaseEndedDoesNotThrow_572) {

    MockTestCaseInfo mockCaseInfo;

    MockTestCaseStats mockCaseStats(mockCaseInfo);

    EXPECT_NO_THROW(reporter.testCaseEnded(mockCaseStats));

}



// Mocking the SectionInfo for sectionStarting

class MockSectionInfo : public SectionInfo {

public:

    MockSectionInfo() : SectionInfo("MockName", "MockDescription", SourceLineInfo("", 0)) {}

};



TEST_F(TeamCityReporterTest_572, SectionStartingDoesNotThrow_572) {

    MockSectionInfo mockSectionInfo;

    EXPECT_NO_THROW(reporter.sectionStarting(mockSectionInfo));

}
