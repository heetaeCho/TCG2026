#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_teamcity.hpp"

#include "catch2/catch_section_info.hpp"



using namespace Catch;



class TeamCityReporterTest_573 : public ::testing::Test {

protected:

    ReporterConfig config;

    TeamCityReporter reporter{CATCH_MOVE(config)};

};



TEST_F(TeamCityReporterTest_573, SectionStartingResetsHeaderFlag_573) {

    SectionInfo sectionInfo(SourceLineInfo{"file.cpp", 10}, "sectionName");

    reporter.sectionStarting(sectionInfo);

    EXPECT_FALSE(reporter.m_headerPrintedForThisSection);

}



TEST_F(TeamCityReporterTest_573, SectionStartingCallsBaseClassMethod_573) {

    testing::StrictMock< ::testing::NiceMock<class MockStreamingReporterBase>> mockBase;

    TeamCityReporter reporterWithMock(CATCH_MOVE(config));

    SectionInfo sectionInfo(SourceLineInfo{"file.cpp", 10}, "sectionName");



    EXPECT_CALL(mockBase, sectionStarting(::testing::_)).Times(1);

    reporterWithMock.sectionStarting(sectionInfo);

}
