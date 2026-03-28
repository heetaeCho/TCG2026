#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_teamcity.hpp"

#include "catch2/internal/catch_test_run_info.hpp"



using namespace Catch;

using namespace ::testing;



class TeamCityReporterTest : public Test {

protected:

    class MockStream : public IStream {

    public:

        MOCK_METHOD(void, write, (std::string const&), (override));

    };



    MockStream mockStream;

    ReporterConfig config{Detail::unique_ptr<IStream>{&mockStream}, ColourMode::None};

    TeamCityReporter reporter{CATCH_MOVE(config)};

};



TEST_F(TeamCityReporterTest_782, TestRunEnded_EmptyName_782) {

    TestRunInfo runInfo{StringRef("")};

    Totals totals{};

    bool aborting = false;

    TestRunStats runStats{runInfo, totals, aborting};



    EXPECT_CALL(mockStream, write("##teamcity[testSuiteFinished name='']\n")).Times(1);

    reporter.testRunEnded(runStats);

}



TEST_F(TeamCityReporterTest_782, TestRunEnded_NonEmptyName_782) {

    TestRunInfo runInfo{StringRef("MyTestSuite")};

    Totals totals{};

    bool aborting = false;

    TestRunStats runStats{runInfo, totals, aborting};



    EXPECT_CALL(mockStream, write("##teamcity[testSuiteFinished name='MyTestSuite']\n")).Times(1);

    reporter.testRunEnded(runStats);

}



TEST_F(TeamCityReporterTest_782, TestRunEnded_NameWithSpaces_782) {

    TestRunInfo runInfo{StringRef("My Test Suite")};

    Totals totals{};

    bool aborting = false;

    TestRunStats runStats{runInfo, totals, aborting};



    EXPECT_CALL(mockStream, write("##teamcity[testSuiteFinished name='My Test Suite']\n")).Times(1);

    reporter.testRunEnded(runStats);

}



TEST_F(TeamCityReporterTest_782, TestRunEnded_NameWithSpecialChars_782) {

    TestRunInfo runInfo{StringRef("My@Test|Suite")};

    Totals totals{};

    bool aborting = false;

    TestRunStats runStats{runInfo, totals, aborting};



    EXPECT_CALL(mockStream, write("##teamcity[testSuiteFinished name='My\\|Test\\|Suite']\n")).Times(1);

    reporter.testRunEnded(runStats);

}
