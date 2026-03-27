#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_teamcity.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;

using namespace testing;



class TeamCityReporterTest_785 : public Test {

protected:

    class MockStream : public IStream {

    public:

        MOCK_METHOD(void, write, (std::string const& str), (override));

        MOCK_METHOD(void, flush, (), (override));

    };



    MockStream mockStream;

    ReporterConfig config{Detail::unique_ptr<IStream>(new NiceMock<MockStream>()), ColourMode::None};

    TeamCityReporter reporter{CATCH_MOVE(config)};



    TestCaseInfo testCaseInfo{"ClassName", {"TestName"}, SourceLineInfo{"file.cpp", 10}};

    Totals totals{};

    TestCaseStats testCaseStats{testCaseInfo, totals, "", "", false};

};



TEST_F(TeamCityReporterTest_785, StdOutPresent_785) {

    testCaseStats.stdOut = "Standard Output";

    EXPECT_CALL(mockStream, write(StrEq("##teamcity[testStdOut name='TestName' out='Standard Output']\n")));

    reporter.testCaseEnded(testCaseStats);

}



TEST_F(TeamCityReporterTest_785, StdErrPresent_785) {

    testCaseStats.stdErr = "Standard Error";

    EXPECT_CALL(mockStream, write(StrEq("##teamcity[testStdErr name='TestName' out='Standard Error']\n")));

    reporter.testCaseEnded(testCaseStats);

}



TEST_F(TeamCityReporterTest_785, BothStdOutAndStdErrPresent_785) {

    testCaseStats.stdOut = "Standard Output";

    testCaseStats.stdErr = "Standard Error";

    EXPECT_CALL(mockStream, write(StrEq("##teamcity[testStdOut name='TestName' out='Standard Output']\n")));

    EXPECT_CALL(mockStream, write(StrEq("##teamcity[testStdErr name='TestName' out='Standard Error']\n")));

    reporter.testCaseEnded(testCaseStats);

}



TEST_F(TeamCityReporterTest_785, NoOutput_785) {

    EXPECT_CALL(mockStream, write(_)).Times(0);

    reporter.testCaseEnded(testCaseStats);

}



TEST_F(TeamCityReporterTest_785, TestFinishedMessage_785) {

    EXPECT_CALL(mockStream, write(StrEq("##teamcity[testFinished name='TestName' duration=0]\n")));

    reporter.testCaseEnded(testCaseStats);

}
