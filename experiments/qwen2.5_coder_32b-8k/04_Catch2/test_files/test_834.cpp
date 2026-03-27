#include <gtest/gtest.h>

#include "catch_reporter_xml.hpp"



using namespace Catch;



class XmlReporterTest_834 : public ::testing::Test {

protected:

    ReporterConfig config;

    XmlReporter reporter{CATCH_MOVE(config)};

};



TEST_F(XmlReporterTest_834, GetStylesheetRef_ReturnsEmptyString_834) {

    EXPECT_EQ(reporter.getStylesheetRef(), "");

}



TEST_F(XmlReporterTest_834, WriteSourceInfo_NoExceptionOnValidInput_834) {

    SourceLineInfo sourceInfo{"file.cpp", 10};

    EXPECT_NO_THROW(reporter.writeSourceInfo(sourceInfo));

}



TEST_F(XmlReporterTest_834, TestRunStarting_NoExceptionOnValidInput_834) {

    TestRunInfo testInfo{nullptr, "test run name"};

    EXPECT_NO_THROW(reporter.testRunStarting(testInfo));

}



TEST_F(XmlReporterTest_834, TestCaseStarting_NoExceptionOnValidInput_834) {

    TestCaseInfo testInfo{"test case", "file.cpp", 10, "", nullptr};

    EXPECT_NO_THROW(reporter.testCaseStarting(testInfo));

}



TEST_F(XmlReporterTest_834, SectionStarting_NoExceptionOnValidInput_834) {

    SectionInfo sectionInfo{nullptr, "section name", "file.cpp", 10, false};

    EXPECT_NO_THROW(reporter.sectionStarting(sectionInfo));

}



TEST_F(XmlReporterTest_834, AssertionStarting_NoExceptionOnValidInput_834) {

    AssertionInfo assertionInfo{nullptr, "", "file.cpp", 10, ""};

    EXPECT_NO_THROW(reporter.assertionStarting(assertionInfo));

}



TEST_F(XmlReporterTest_834, AssertionEnded_NoExceptionOnValidInput_834) {

    AssertionStats assertionStats;

    EXPECT_NO_THROW(reporter.assertionEnded(assertionStats));

}



TEST_F(XmlReporterTest_834, SectionEnded_NoExceptionOnValidInput_834) {

    SectionStats sectionStats{nullptr};

    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats));

}



TEST_F(XmlReporterTest_834, TestCaseEnded_NoExceptionOnValidInput_834) {

    TestCaseStats testCaseStats;

    EXPECT_NO_THROW(reporter.testCaseEnded(testCaseStats));

}



TEST_F(XmlReporterTest_834, TestRunEnded_NoExceptionOnValidInput_834) {

    TestRunStats testRunStats{};

    EXPECT_NO_THROW(reporter.testRunEnded(testRunStats));

}



TEST_F(XmlReporterTest_834, BenchmarkPreparing_NoExceptionOnValidInput_834) {

    StringRef name{"benchmark"};

    EXPECT_NO_THROW(reporter.benchmarkPreparing(name));

}



TEST_F(XmlReporterTest_834, BenchmarkStarting_NoExceptionOnValidInput_834) {

    BenchmarkInfo info{};

    EXPECT_NO_THROW(reporter.benchmarkStarting(info));

}



TEST_F(XmlReporterTest_834, BenchmarkEnded_NoExceptionOnValidInput_834) {

    BenchmarkStats<> stats;

    EXPECT_NO_THROW(reporter.benchmarkEnded(stats));

}



TEST_F(XmlReporterTest_834, BenchmarkFailed_NoExceptionOnValidInput_834) {

    StringRef error{"error message"};

    EXPECT_NO_THROW(reporter.benchmarkFailed(error));

}



TEST_F(XmlReporterTest_834, ListReporters_NoExceptionOnValidInput_834) {

    std::vector<ReporterDescription> descriptions;

    EXPECT_NO_THROW(reporter.listReporters(descriptions));

}



TEST_F(XmlReporterTest_834, ListListeners_NoExceptionOnValidInput_834) {

    std::vector<ListenerDescription> descriptions;

    EXPECT_NO_THROW(reporter.listListeners(descriptions));

}



TEST_F(XmlReporterTest_834, ListTests_NoExceptionOnValidInput_834) {

    std::vector<TestCaseHandle> tests;

    EXPECT_NO_THROW(reporter.listTests(tests));

}



TEST_F(XmlReporterTest_834, ListTags_NoExceptionOnValidInput_834) {

    std::vector<TagInfo> tags;

    EXPECT_NO_THROW(reporter.listTags(tags));

}
