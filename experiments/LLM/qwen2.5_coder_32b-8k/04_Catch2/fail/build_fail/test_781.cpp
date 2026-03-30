#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_teamcity.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_run_info.hpp"



using namespace Catch;



class MockIStream : public IStream {

public:

    MOCK_METHOD(void, write, (std::string const& str), (override));

};



class TeamCityReporterTest_781 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ReporterConfig config{Detail::unique_ptr<IStream>(new MockIStream()), ColourMode::None};

    TeamCityReporter reporter{CATCH_MOVE(config)};

    TestRunInfo runInfo{"testSuiteName"};

};



TEST_F(TeamCityReporterTest_781, TestRunStartingWritesCorrectOutput_781) {

    EXPECT_CALL(*static_cast<MockIStream*>(reporter.m_wrapped_stream.get()), write("##teamcity[testSuiteStarted name='testSuiteName']\n"));

    reporter.testRunStarting(runInfo);

}



TEST_F(TeamCityReporterTest_781, TestRunStartingHandlesEmptyName_781) {

    TestRunInfo emptyRunInfo{StringRef("")};

    EXPECT_CALL(*static_cast<MockIStream*>(reporter.m_wrapped_stream.get()), write("##teamcity[testSuiteStarted name='']\n"));

    reporter.testRunStarting(emptyRunInfo);

}



TEST_F(TeamCityReporterTest_781, TestRunStartingHandlesLongName_781) {

    std::string longName(256, 'a'); // A very long test suite name

    TestRunInfo longRunInfo{StringRef(longName)};

    EXPECT_CALL(*static_cast<MockIStream*>(reporter.m_wrapped_stream.get()), write("##teamcity[testSuiteStarted name='aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa']\n"));

    reporter.testRunStarting(longRunInfo);

}
