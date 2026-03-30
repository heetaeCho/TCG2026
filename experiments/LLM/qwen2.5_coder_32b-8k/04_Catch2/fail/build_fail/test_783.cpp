#include <gtest/gtest.h>

#include "catch_reporter_teamcity.hpp"

#include "catch_assertion_result.hpp"

#include "catch_message_info.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;



class TeamCityReporterTest : public ::testing::Test {

protected:

    ReporterConfig config;

    TeamCityReporter reporter{CATCH_MOVE(config)};

    AssertionResult assertionResult;

    TestCaseInfo testCaseInfo{"ClassName", {"TestName", ""}, SourceLineInfo{"filename.cpp", 10}};

    Totals totals;

    std::vector<MessageInfo> infoMessages;



    void SetUp() override {

        currentTestCaseInfo = &testCaseInfo;

    }



    AssertionStats createAssertionStats(ResultWas::OfType resultType, bool isOk) {

        assertionResult = AssertionResult{AssertionInfo{}, AssertionResultData{}};

        assertionResult.m_resultData.resultType = resultType;

        assertionResult.m_resultData.ok = isOk;



        return AssertionStats(assertionResult, infoMessages, totals);

    }

};



TEST_F(TeamCityReporterTest_783, ExpressionFailedReportsCorrectly_783) {

    auto stats = createAssertionStats(ResultWas::ExpressionFailed, false);

    reporter.assertionEnded(stats);



    // Assuming that m_stream has some way to capture output for verification

    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nexpression failed']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, ThrewExceptionReportsCorrectly_783) {

    auto stats = createAssertionStats(ResultWas::ThrewException, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nunexpected exception']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, FatalErrorConditionReportsCorrectly_783) {

    auto stats = createAssertionStats(ResultWas::FatalErrorCondition, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nfatal error condition']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, DidntThrowExceptionReportsCorrectly_783) {

    auto stats = createAssertionStats(ResultWas::DidntThrowException, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nno exception was thrown where one was expected']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, ExplicitFailureReportsCorrectly_783) {

    auto stats = createAssertionStats(ResultWas::ExplicitFailure, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nexplicit failure']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, ExplicitSkipReportsCorrectly_783) {

    auto stats = createAssertionStats(ResultWas::ExplicitSkip, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testIgnored name='TestName']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, OkResultDoesNotReportFailure_783) {

    auto stats = createAssertionStats(ResultWas::Ok, true);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, TestMarkedAsOkToFailReportsIgnored_783) {

    testCaseInfo.properties.okToFail = true;

    auto stats = createAssertionStats(ResultWas::ExpressionFailed, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testIgnored name='TestName']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, InfoMessageIncludedInReport_783) {

    infoMessages.emplace_back(StringRef{"InfoMacro"}, SourceLineInfo{"filename.cpp", 10}, ResultWas::Info);

    auto stats = createAssertionStats(ResultWas::ExpressionFailed, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nexpression failed with message:\n \"\"\n']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, MultipleInfoMessagesIncludedInReport_783) {

    infoMessages.emplace_back(StringRef{"InfoMacro"}, SourceLineInfo{"filename.cpp", 10}, ResultWas::Info);

    infoMessages.emplace_back(StringRef{"InfoMacro2"}, SourceLineInfo{"filename.cpp", 15}, ResultWas::Info);

    auto stats = createAssertionStats(ResultWas::ExpressionFailed, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nexpression failed with messages:\n \"\"\n \"\"\n']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}



TEST_F(TeamCityReporterTest_783, ExpressionAndExpansionIncludedInReport_783) {

    assertionResult.m_resultData.expression = "x == y";

    assertionResult.m_resultData.expandedExpression = "1 == 2";

    auto stats = createAssertionStats(ResultWas::ExpressionFailed, false);

    reporter.assertionEnded(stats);



    std::string expectedOutput = "##teamcity[testFailed name='TestName' message='filename.cpp:10\nexpression failed with messages:\n \"\"\n x == y\nwith expansion:\n 1 == 2\n']\n";

    EXPECT_EQ(reporter.m_stream.str(), expectedOutput);

}
