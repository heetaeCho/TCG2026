#include <gtest/gtest.h>

#include "catch_reporter_cumulative_base.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;



class CumulativeReporterBaseTest_859 : public ::testing::Test {

protected:

    ReporterConfig config;

    CumulativeReporterBase reporter{CATCH_MOVE(config)};

};



TEST_F(CumulativeReporterBaseTest_859, SectionEndedUpdatesNodeStats_859) {

    // Arrange

    SectionInfo sectionInfo{"SectionName", "", 1, 2};

    Counts assertions{0, 1, 0, 0, 0, 0};

    double durationInSeconds = 0.0;

    bool missingAssertions = false;

    SectionStats sectionStats{CATCH_MOVE(sectionInfo), assertions, durationInSeconds, missingAssertions};



    reporter.m_sectionStack.push_back(std::make_unique<SectionNode>(sectionStats));



    // Act

    reporter.sectionEnded(sectionStats);



    // Assert

    EXPECT_TRUE(reporter.m_sectionStack.empty());

}



TEST_F(CumulativeReporterBaseTest_859, SectionEndedAssertsWhenStackEmpty_859) {

    // Arrange

    SectionInfo sectionInfo{"SectionName", "", 1, 2};

    Counts assertions{0, 1, 0, 0, 0, 0};

    double durationInSeconds = 0.0;

    bool missingAssertions = false;

    SectionStats sectionStats{CATCH_MOVE(sectionInfo), assertions, durationInSeconds, missingAssertions};



    // Act & Assert

    EXPECT_DEATH(reporter.sectionEnded(sectionStats), ".*assert.*");

}



TEST_F(CumulativeReporterBaseTest_859, SectionEndedUpdatesNodeWithNewStats_859) {

    // Arrange

    SectionInfo sectionInfo{"SectionName", "", 1, 2};

    Counts assertions{0, 1, 0, 0, 0, 0};

    double durationInSeconds = 0.0;

    bool missingAssertions = false;

    SectionStats initialStats{CATCH_MOVE(sectionInfo), assertions, durationInSeconds, missingAssertions};



    reporter.m_sectionStack.push_back(std::make_unique<SectionNode>(initialStats));



    SectionInfo updatedSectionInfo{"UpdatedSectionName", "", 1, 2};

    Counts updatedAssertions{0, 2, 0, 0, 0, 0};

    double updatedDurationInSeconds = 0.5;

    bool updatedMissingAssertions = true;

    SectionStats updatedStats{CATCH_MOVE(updatedSectionInfo), updatedAssertions, updatedDurationInSeconds, updatedMissingAssertions};



    // Act

    reporter.sectionEnded(updatedStats);



    // Assert

    EXPECT_TRUE(reporter.m_sectionStack.empty());

}
