#include <gtest/gtest.h>

#include "catch_reporter_xml.hpp"



using namespace Catch;



class XmlReporterTest_833 : public ::testing::Test {

protected:

    ReporterConfig config;

    XmlReporter reporter;



    XmlReporterTest_833() : reporter(CATCH_MOVE(config)) {}

};



TEST_F(XmlReporterTest_833, GetDescription_ReturnsExpectedString_833) {

    EXPECT_EQ(reporter.getDescription(), "Reports test results as an XML document");

}



TEST_F(XmlReporterTest_833, GetStylesheetRef_ReturnsEmptyStringByDefault_833) {

    EXPECT_EQ(reporter.getStylesheetRef(), "");

}



TEST_F(XmlReporterTest_833, WriteSourceInfo_DoesNotThrow_833) {

    SourceLineInfo sourceInfo("file.cpp", 10);

    EXPECT_NO_THROW(reporter.writeSourceInfo(sourceInfo));

}



TEST_F(XmlReporterTest_833, TestRunStarting_DoesNotThrow_833) {

    TestRunInfo testInfo;

    EXPECT_NO_THROW(reporter.testRunStarting(testInfo));

}



TEST_F(XmlReporterTest_833, TestCaseStarting_DoesNotThrow_833) {

    TestCaseInfo testInfo;

    EXPECT_NO_THROW(reporter.testCaseStarting(testInfo));

}



TEST_F(XmlReporterTest_833, SectionStarting_DoesNotThrow_833) {

    SectionInfo sectionInfo;

    EXPECT_NO_THROW(reporter.sectionStarting(sectionInfo));

}



TEST_F(XmlReporterTest_833, AssertionStarting_DoesNotThrow_833) {

    AssertionInfo assertionInfo;

    EXPECT_NO_THROW(reporter.assertionStarting(assertionInfo));

}



TEST_F(XmlReporterTest_833, AssertionEnded_DoesNotThrow_833) {

    AssertionStats assertionStats;

    EXPECT_NO_THROW(reporter.assertionEnded(assertionStats));

}



TEST_F(XmlReporterTest_833, SectionEnded_DoesNotThrow_833) {

    SectionStats sectionStats;

    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats));

}



TEST_F(XmlReporterTest_833, TestCaseEnded_DoesNotThrow_833) {

    TestCaseStats testCaseStats;

    EXPECT_NO_THROW(reporter.testCaseEnded(testCaseStats));

}



TEST_F(XmlReporterTest_833, TestRunEnded_DoesNotThrow_833) {

    TestRunStats testRunStats;

    EXPECT_NO_THROW(reporter.testRunEnded(testRunStats));

}



TEST_F(XmlReporterTest_833, BenchmarkPreparing_DoesNotThrow_833) {

    StringRef name("BenchmarkName");

    EXPECT_NO_THROW(reporter.benchmarkPreparing(name));

}



TEST_F(XmlReporterTest_833, BenchmarkStarting_DoesNotThrow_833) {

    BenchmarkInfo benchmarkInfo;

    EXPECT_NO_THROW(reporter.benchmarkStarting(benchmarkInfo));

}



TEST_F(XmlReporterTest_833, BenchmarkEnded_DoesNotThrow_833) {

    BenchmarkStats<> benchmarkStats;

    EXPECT_NO_THROW(reporter.benchmarkEnded(benchmarkStats));

}



TEST_F(XmlReporterTest_833, BenchmarkFailed_DoesNotThrow_833) {

    StringRef error("Error");

    EXPECT_NO_THROW(reporter.benchmarkFailed(error));

}



TEST_F(XmlReporterTest_833, ListReporters_DoesNotThrow_833) {

    std::vector<ReporterDescription> descriptions;

    EXPECT_NO_THROW(reporter.listReporters(descriptions));

}



TEST_F(XmlReporterTest_833, ListListeners_DoesNotThrow_833) {

    std::vector<ListenerDescription> descriptions;

    EXPECT_NO_THROW(reporter.listListeners(descriptions));

}



TEST_F(XmlReporterTest_833, ListTests_DoesNotThrow_833) {

    std::vector<TestCaseHandle> tests;

    EXPECT_NO_THROW(reporter.listTests(tests));

}



TEST_F(XmlReporterTest_833, ListTags_DoesNotThrow_833) {

    std::vector<TagInfo> tags;

    EXPECT_NO_THROW(reporter.listTags(tags));

}
