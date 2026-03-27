#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_interfaces_config.hpp"

#include "catch_test_case_info.hpp"

#include "catch_timer.hpp"



using namespace Catch;

using namespace testing;



class MockConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const, override));

    MOCK_METHOD(StringRef, name, (), (const, override));

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));

    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));

    MOCK_METHOD(int, abortAfter, (), (const, override));

    MOCK_METHOD(bool, showInvisibles, (), (const, override));

    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));

    MOCK_METHOD(double, minDuration, (), (const, override));

    MOCK_METHOD(const TestSpec &, testSpec, (), (const, override));

    MOCK_METHOD(bool, hasTestFilters, (), (const, override));

    MOCK_METHOD(const std::vector<std::string> &, getTestsOrTags, (), (const, override));

    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));

    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));

    MOCK_METHOD(unsigned int, shardCount, (), (const, override));

    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));

    MOCK_METHOD(const std::vector<std::string> &, getSectionsToRun, (), (const, override));

    MOCK_METHOD(Verbosity, verbosity, (), (const, override));

    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));

};



class XmlReporterTest : public Test {

protected:

    MockConfig mockConfig;

    std::ostringstream oss;

    ReporterConfig config{oss};

    XmlReporter xmlReporter{CATCH_MOVE(config)};



    TestCaseInfo testInfo = TestCaseInfo{"ClassName"_sr, {"TestName", "Tag1 Tag2"}, SourceLineInfo{"file.cpp", 42}};



    void SetUp() override {

        EXPECT_CALL(mockConfig, showDurations())

            .WillRepeatedly(Return(ShowDurations::Always));

        xmlReporter.m_config = &mockConfig;

    }

};



TEST_F(XmlReporterTest_837, TestCaseStartingWritesCorrectXml_837) {

    xmlReporter.testCaseStarting(testInfo);



    EXPECT_EQ(oss.str(), "<TestCase name=\"TestName\" tags=\"Tag1 Tag2\" line=\"42\"></TestCase>");

}



TEST_F(XmlReporterTest_837, TestCaseStartingWithNoTagsWritesCorrectXml_837) {

    TestCaseInfo testInfoWithoutTags{"ClassName"_sr, {"TestName", ""}, SourceLineInfo{"file.cpp", 42}};

    xmlReporter.testCaseStarting(testInfoWithoutTags);



    EXPECT_EQ(oss.str(), "<TestCase name=\"TestName\" tags=\"\" line=\"42\"></TestCase>");

}



TEST_F(XmlReporterTest_837, TestCaseStartingWithNoShowDurationsWritesCorrectXml_837) {

    EXPECT_CALL(mockConfig, showDurations())

        .WillOnce(Return(ShowDurations::Never));

    

    xmlReporter.testCaseStarting(testInfo);



    EXPECT_EQ(oss.str(), "<TestCase name=\"TestName\" tags=\"Tag1 Tag2\" line=\"42\"></TestCase>");

}



TEST_F(XmlReporterTest_837, TestCaseStartingWithWhitespaceTrimsCorrectly_837) {

    TestCaseInfo testInfoWithSpaces{"ClassName"_sr, {" TestName ", "Tag1 Tag2"}, SourceLineInfo{"file.cpp", 42}};

    xmlReporter.testCaseStarting(testInfoWithSpaces);



    EXPECT_EQ(oss.str(), "<TestCase name=\"TestName\" tags=\"Tag1 Tag2\" line=\"42\"></TestCase>");

}
