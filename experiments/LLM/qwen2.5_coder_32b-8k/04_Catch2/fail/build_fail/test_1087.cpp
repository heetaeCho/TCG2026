#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_teamcity.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



namespace Catch {

    class MockIConfig : public IConfig {

    public:

        MOCK_CONST_METHOD0(throwExceptions, bool());

        MOCK_CONST_METHOD1(getBenchmarkSpec, std::vector<std::string>(bool));

        MOCK_CONST_METHOD0(useColour, bool());

        MOCK_CONST_METHOD0(benchmarkNoDefaults, bool());

        MOCK_CONST_METHOD0(getRunTestsIfSuccessfulMatching, std::string());

        MOCK_CONST_METHOD0(getShowInvisibles, bool());

        MOCK_CONST_METHOD0(runWithinMainThread, bool());

        MOCK_CONST_METHOD0(hasUsableColour, bool());

    };

}



class TeamCityReporterTest : public ::testing::Test {

protected:

    NiceMock<Catch::MockIConfig> mockConfig;

    Catch::Detail::unique_ptr<Catch::IStream> stream = nullptr;

    Catch::ColourMode colourMode = Catch::ColourMode::None;

    std::map<std::string, std::string> customOptions;



    Catch::TeamCityReporter reporter{Catch::ReporterConfig(&mockConfig, CATCH_MOVE(stream), colourMode, CATCH_MOVE(customOptions))};

};



TEST_F(TeamCityReporterTest_1087, ConstructorRedirectsStdOut_1087) {

    EXPECT_TRUE(reporter.getPreferences().shouldRedirectStdOut);

}



TEST_F(TeamCityReporterTest_1087, TestRunStarting_CallsBaseClassMethod_1087) {

    Catch::TestRunInfo runInfo{"test name"_sr};

    EXPECT_CALL(*static_cast<Catch::StreamingReporterBase*>(&reporter), testRunStarting(::testing::_));

    reporter.testRunStarting(runInfo);

}



TEST_F(TeamCityReporterTest_1087, TestRunEnded_CallsBaseClassMethod_1087) {

    Catch::TestRunStats runStats;

    EXPECT_CALL(*static_cast<Catch::StreamingReporterBase*>(&reporter), testRunEnded(::testing::_));

    reporter.testRunEnded(runStats);

}



TEST_F(TeamCityReporterTest_1087, AssertionEnded_CallsBaseClassMethod_1087) {

    Catch::AssertionStats assertionStats;

    EXPECT_CALL(*static_cast<Catch::StreamingReporterBase*>(&reporter), assertionEnded(::testing::_));

    reporter.assertionEnded(assertionStats);

}



TEST_F(TeamCityReporterTest_1087, TestCaseStarting_CallsBaseClassMethod_1087) {

    Catch::TestCaseInfo testInfo{"test name"_sr, "description"_sr, Catch::SourceLineInfo{"file.cpp", 42}};

    EXPECT_CALL(*static_cast<Catch::StreamingReporterBase*>(&reporter), testCaseStarting(::testing::_));

    reporter.testCaseStarting(testInfo);

}



TEST_F(TeamCityReporterTest_1087, TestCaseEnded_CallsBaseClassMethod_1087) {

    Catch::TestCaseStats testCaseStats;

    EXPECT_CALL(*static_cast<Catch::StreamingReporterBase*>(&reporter), testCaseEnded(::testing::_));

    reporter.testCaseEnded(testCaseStats);

}



TEST_F(TeamCityReporterTest_1087, SectionStarting_CallsBaseClassMethod_1087) {

    Catch::SectionInfo sectionInfo{"section name"_sr, "description"_sr, Catch::SourceLineInfo{"file.cpp", 42}};

    EXPECT_CALL(*static_cast<Catch::StreamingReporterBase*>(&reporter), sectionStarting(::testing::_));

    reporter.sectionStarting(sectionInfo);

}
