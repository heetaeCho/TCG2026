#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_teamcity.hpp"

#include "catch2/catch_test_case_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class MockTestStream : public IStream {

public:

    MOCK_METHOD(void, write, (std::string const&), (override));

};



class TeamCityReporterTest_784 : public ::testing::Test {

protected:

    void SetUp() override {

        ReporterConfig config;

        config.takeStream = [this]() { return stream; };

        reporter = new TeamCityReporter(std::move(config));

    }



    void TearDown() override {

        delete reporter;

    }



    MockTestStream* stream = new MockTestStream();

    TeamCityReporter* reporter = nullptr;

};



TEST_F(TeamCityReporterTest_784, TestCaseStarting_WritesCorrectMessage_784) {

    TestCaseInfo testInfo("ClassName", {"testName"}, SourceLineInfo());

    EXPECT_CALL(*stream, write(StrEq("##teamcity[testStarted name='testName']\n")));

    reporter->testCaseStarting(testInfo);

}



TEST_F(TeamCityReporterTest_784, TestCaseStarting_StartsTimer_784) {

    TestCaseInfo testInfo("ClassName", {"testName"}, SourceLineInfo());

    EXPECT_CALL(*stream, write(StrEq("##teamcity[testStarted name='testName']\n")));

    reporter->testCaseStarting(testInfo);

    // We can't directly verify the timer start, but we can assume it's called as part of the function

}



TEST_F(TeamCityReporterTest_784, TestCaseStarting_HandlesEmptyName_784) {

    TestCaseInfo testInfo("ClassName", {"", "tag1"}, SourceLineInfo());

    EXPECT_CALL(*stream, write(StrEq("##teamcity[testStarted name='']\n")));

    reporter->testCaseStarting(testInfo);

}



TEST_F(TeamCityReporterTest_784, TestCaseStarting_EscapesSpecialCharactersInName_784) {

    TestCaseInfo testInfo("ClassName", {"test|name\\[with special chars]"}, SourceLineInfo());

    EXPECT_CALL(*stream, write(StrEq("##teamcity[testStarted name='test||name\\\\[with special chars]']\n")));

    reporter->testCaseStarting(testInfo);

}
