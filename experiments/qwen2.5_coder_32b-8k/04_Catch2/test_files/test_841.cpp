#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_xml.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_streaming_base.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_totals.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"

#include <sstream>



using namespace Catch;



class MockConfig : public IConfig {

public:

    MOCK_METHOD(bool, showDurations, (), (const, override));

};



class XmlReporterTest_841 : public ::testing::Test {

protected:

    std::ostringstream oss;

    MockConfig mockConfig;

    ReporterConfig config{&mockConfig};

    XmlReporter reporter{CATCH_MOVE(config)};

    

    TestCaseStats createTestCaseStats(bool allOk = true, uint64_t skipped = 0,

                                     const std::string& stdOut = "", 

                                     const std::string& stdErr = "") {

        TestCaseInfo testInfo{"Test Case Name", "File.cpp", 123};

        Totals totals;

        totals.assertions.passed = allOk ? 1 : 0;

        totals.assertions.failed = allOk ? 0 : 1;

        totals.assertions.skipped = skipped;

        return TestCaseStats{testInfo, totals, CATCH_MOVE(std::string(stdOut)), 

                            CATCH_MOVE(std::string(stdErr)), false};

    }

};



TEST_F(XmlReporterTest_841, testCaseEnded_SuccessfulTest_841) {

    TestCaseStats stats = createTestCaseStats(true);

    reporter.testCaseEnded(stats);



    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<OverallResult success="true")"));

}



TEST_F(XmlReporterTest_841, testCaseEnded_SkippedAssertions_841) {

    TestCaseStats stats = createTestCaseStats(false, 1);

    reporter.testCaseEnded(stats);



    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<OverallResult skips="1")"));

}



TEST_F(XmlReporterTest_841, testCaseEnded_ShowDurationsAlways_841) {

    EXPECT_CALL(mockConfig, showDurations()).WillOnce(testing::Return(ShowDurations::Always));

    TestCaseStats stats = createTestCaseStats(true);

    reporter.testCaseEnded(stats);



    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<OverallResult success="true")"));

    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(durationInSeconds)"));

}



TEST_F(XmlReporterTest_841, testCaseEnded_ShowDurationsNever_841) {

    EXPECT_CALL(mockConfig, showDurations()).WillOnce(testing::Return(ShowDurations::Never));

    TestCaseStats stats = createTestCaseStats(true);

    reporter.testCaseEnded(stats);



    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<OverallResult success="true")"));

    EXPECT_THAT(oss.str(), ::testing::Not(testing::ContainsRegex(R"(durationInSeconds)")));

}



TEST_F(XmlReporterTest_841, testCaseEnded_NonEmptyStdOut_841) {

    TestCaseStats stats = createTestCaseStats(true, 0, "Standard Output");

    reporter.testCaseEnded(stats);



    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<OverallResult success="true")"));

    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<StdOut>)"));

}



TEST_F(XmlReporterTest_841, testCaseEnded_NonEmptyStdErr_841) {

    TestCaseStats stats = createTestCaseStats(true, 0, "", "Standard Error");

    reporter.testCaseEnded(stats);



    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<OverallResult success="true")"));

    EXPECT_THAT(oss.str(), testing::ContainsRegex(R"(<StdErr>)"));

}
