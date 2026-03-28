#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_compact.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::NiceMock;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD1(shouldShowDuration, bool(const double&));

};



class CompactReporterTest_815 : public testing::Test {

protected:

    NiceMock<MockConfig> mockConfig;

    std::ostringstream oss;

    ReporterConfig config{ &mockConfig, Detail::unique_ptr<IStream>(new OstreamRaii{oss}) };

    CompactReporter reporter{ CATCH_MOVE(config) };



    SectionStats createSectionStats(double durationInSeconds = 0.1, bool missingAssertions = false) {

        SourceLineInfo lineInfo("dummy_file", 123);

        SectionInfo sectionInfo(lineInfo, "TestSection");

        Counts assertions;

        return SectionStats(CATCH_MOVE(sectionInfo), assertions, durationInSeconds, missingAssertions);

    }

};



TEST_F(CompactReporterTest_815, SectionEnded_ShouldShowDuration_815) {

    EXPECT_CALL(mockConfig, shouldShowDuration(testing::_)).WillOnce(testing::Return(true));

    

    SectionStats sectionStats = createSectionStats();

    reporter.sectionEnded(sectionStats);

    

    EXPECT_THAT(oss.str(), testing::HasSubstr("TestSection"));

}



TEST_F(CompactReporterTest_815, SectionEnded_ShouldNotShowDuration_815) {

    EXPECT_CALL(mockConfig, shouldShowDuration(testing::_)).WillOnce(testing::Return(false));

    

    SectionStats sectionStats = createSectionStats();

    reporter.sectionEnded(sectionStats);

    

    EXPECT_EQ(oss.str(), "");

}



TEST_F(CompactReporterTest_815, SectionEnded_ZeroDuration_815) {

    EXPECT_CALL(mockConfig, shouldShowDuration(testing::_)).WillOnce(testing::Return(true));

    

    SectionStats sectionStats = createSectionStats(0.0);

    reporter.sectionEnded(sectionStats);

    

    EXPECT_THAT(oss.str(), testing::HasSubstr("TestSection"));

}



TEST_F(CompactReporterTest_815, SectionEnded_LargeDuration_815) {

    EXPECT_CALL(mockConfig, shouldShowDuration(testing::_)).WillOnce(testing::Return(true));

    

    SectionStats sectionStats = createSectionStats(3600.0);

    reporter.sectionEnded(sectionStats);

    

    EXPECT_THAT(oss.str(), testing::HasSubstr("TestSection"));

}



TEST_F(CompactReporterTest_815, SectionEnded_MissingAssertions_815) {

    EXPECT_CALL(mockConfig, shouldShowDuration(testing::_)).WillOnce(testing::Return(true));

    

    SectionStats sectionStats = createSectionStats(0.1, true);

    reporter.sectionEnded(sectionStats);

    

    EXPECT_THAT(oss.str(), testing::HasSubstr("TestSection"));

}
