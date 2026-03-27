#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD(std::string, getConfigData, (), (const));

};



class MockIStream : public Detail::unique_ptr<IStream> {

public:

    MOCK_METHOD(void, write, (std::string_view), ());

};



class XmlReporterTest_1103 : public ::testing::Test {

protected:

    NiceMock<MockIConfig> mockConfig;

    std::map<std::string, std::string> customOptions;

    ReporterConfig config{&mockConfig, std::make_unique<MockIStream>(), ColourMode::None, customOptions};

    XmlReporter reporter{std::move(config)};

};



TEST_F(XmlReporterTest_1103, ConstructorRedirectsStdOutAndReportsAllAssertions_1103) {

    EXPECT_TRUE(reporter.getPreferences().shouldRedirectStdOut);

    EXPECT_TRUE(reporter.getPreferences().shouldReportAllAssertions);

}



TEST_F(XmlReporterTest_1103, GetDescriptionReturnsNonEmptyString_1103) {

    EXPECT_FALSE(reporter.getDescription().empty());

}



TEST_F(XmlReporterTest_1103, GetStylesheetRefReturnsNonEmptyString_1103) {

    EXPECT_FALSE(reporter.getStylesheetRef().empty());

}



TEST_F(XmlReporterTest_1103, WriteSourceInfoDoesNotThrow_1103) {

    SourceLineInfo sourceInfo{"test.cpp", 42};

    EXPECT_NO_THROW(reporter.writeSourceInfo(sourceInfo));

}



TEST_F(XmlReporterTest_1103, TestRunStartingDoesNotThrow_1103) {

    TestRunInfo testInfo{};

    EXPECT_NO_THROW(reporter.testRunStarting(testInfo));

}



TEST_F(XmlReporterTest_1103, TestCaseStartingDoesNotThrow_1103) {

    TestCaseInfo testCaseInfo{};

    EXPECT_NO_THROW(reporter.testCaseStarting(testCaseInfo));

}



TEST_F(XmlReporterTest_1103, SectionStartingDoesNotThrow_1103) {

    SectionInfo sectionInfo{};

    EXPECT_NO_THROW(reporter.sectionStarting(sectionInfo));

}



TEST_F(XmlReporterTest_1103, AssertionStartingDoesNotThrow_1103) {

    AssertionInfo assertionInfo{};

    EXPECT_NO_THROW(reporter.assertionStarting(assertionInfo));

}



TEST_F(XmlReporterTest_1103, AssertionEndedDoesNotThrow_1103) {

    AssertionStats assertionStats{};

    EXPECT_NO_THROW(reporter.assertionEnded(assertionStats));

}



TEST_F(XmlReporterTest_1103, SectionEndedDoesNotThrow_1103) {

    SectionStats sectionStats{};

    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats));

}



TEST_F(XmlReporterTest_1103, TestCaseEndedDoesNotThrow_1103) {

    TestCaseStats testCaseStats{};

    EXPECT_NO_THROW(reporter.testCaseEnded(testCaseStats));

}



TEST_F(XmlReporterTest_1103, TestRunEndedDoesNotThrow_1103) {

    TestRunStats testRunStats{};

    EXPECT_NO_THROW(reporter.testRunEnded(testRunStats));

}



TEST_F(XmlReporterTest_1103, BenchmarkPreparingDoesNotThrow_1103) {

    StringRef name{"benchmark"};

    EXPECT_NO_THROW(reporter.benchmarkPreparing(name));

}



TEST_F(XmlReporterTest_1103, BenchmarkStartingDoesNotThrow_1103) {

    BenchmarkInfo benchmarkInfo{};

    EXPECT_NO_THROW(reporter.benchmarkStarting(benchmarkInfo));

}



TEST_F(XmlReporterTest_1103, BenchmarkEndedDoesNotThrow_1103) {

    BenchmarkStats<> benchmarkStats{};

    EXPECT_NO_THROW(reporter.benchmarkEnded(benchmarkStats));

}



TEST_F(XmlReporterTest_1103, BenchmarkFailedDoesNotThrow_1103) {

    StringRef error{"error"};

    EXPECT_NO_THROW(reporter.benchmarkFailed(error));

}



TEST_F(XmlReporterTest_1103, ListReportersDoesNotThrow_1103) {

    std::vector<ReporterDescription> descriptions{};

    EXPECT_NO_THROW(reporter.listReporters(descriptions));

}



TEST_F(XmlReporterTest_1103, ListListenersDoesNotThrow_1103) {

    std::vector<ListenerDescription> descriptions{};

    EXPECT_NO_THROW(reporter.listListeners(descriptions));

}



TEST_F(XmlReporterTest_1103, ListTestsDoesNotThrow_1103) {

    std::vector<TestCaseHandle> tests{};

    EXPECT_NO_THROW(reporter.listTests(tests));

}



TEST_F(XmlReporterTest_1103, ListTagsDoesNotThrow_1103) {

    std::vector<TagInfo> tags{};

    EXPECT_NO_THROW(reporter.listTags(tags));

}
