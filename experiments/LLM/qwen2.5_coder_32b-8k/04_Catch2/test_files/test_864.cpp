#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_json.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockReporterConfig : public ReporterConfig {

public:

    MockReporterConfig() = default;

};



class JsonReporterTest_864 : public ::testing::Test {

protected:

    NiceMock<MockReporterConfig> mockConfig;

    JsonReporter reporter{std::move(mockConfig)};

};



TEST_F(JsonReporterTest_864, GetDescription_ReturnsCorrectString_864) {

    EXPECT_EQ(reporter.getDescription(), "Outputs listings as JSON. Test listing is Work-in-Progress!");

}



// Assuming ReporterConfig can be constructed and moved without issues

TEST_F(JsonReporterTest_864, Constructor_DoesNotThrow_864) {

    EXPECT_NO_THROW(JsonReporter{std::move(MockReporterConfig{})});

}



// No observable behavior for destructor in this context

// TEST_F(JsonReporterTest_864, Destructor_DoesNotThrow_864) {}



TEST_F(JsonReporterTest_864, TestRunStarting_NoException_864) {

    EXPECT_NO_THROW(reporter.testRunStarting(TestRunInfo{}));

}



TEST_F(JsonReporterTest_864, TestRunEnded_NoException_864) {

    EXPECT_NO_THROW(reporter.testRunEnded(TestRunStats{}));

}



TEST_F(JsonReporterTest_864, TestCaseStarting_NoException_864) {

    EXPECT_NO_THROW(reporter.testCaseStarting(TestCaseInfo{}));

}



TEST_F(JsonReporterTest_864, TestCaseEnded_NoException_864) {

    EXPECT_NO_THROW(reporter.testCaseEnded(TestCaseStats{}));

}



TEST_F(JsonReporterTest_864, TestCasePartialStarting_NoException_864) {

    EXPECT_NO_THROW(reporter.testCasePartialStarting(TestCaseInfo{}, 0));

}



TEST_F(JsonReporterTest_864, TestCasePartialEnded_NoException_864) {

    EXPECT_NO_THROW(reporter.testCasePartialEnded(TestCaseStats{}, 0));

}



TEST_F(JsonReporterTest_864, SectionStarting_NoException_864) {

    EXPECT_NO_THROW(reporter.sectionStarting(SectionInfo{}));

}



TEST_F(JsonReporterTest_864, SectionEnded_NoException_864) {

    EXPECT_NO_THROW(reporter.sectionEnded(SectionStats{}));

}



TEST_F(JsonReporterTest_864, AssertionStarting_NoException_864) {

    EXPECT_NO_THROW(reporter.assertionStarting(AssertionInfo{}));

}



TEST_F(JsonReporterTest_864, AssertionEnded_NoException_864) {

    EXPECT_NO_THROW(reporter.assertionEnded(AssertionStats{}));

}



TEST_F(JsonReporterTest_864, BenchmarkPreparing_NoException_864) {

    EXPECT_NO_THROW(reporter.benchmarkPreparing(StringRef{}));

}



TEST_F(JsonReporterTest_864, BenchmarkStarting_NoException_864) {

    EXPECT_NO_THROW(reporter.benchmarkStarting(BenchmarkInfo{}));

}



TEST_F(JsonReporterTest_864, BenchmarkEnded_NoException_864) {

    EXPECT_NO_THROW(reporter.benchmarkEnded(BenchmarkStats<>::emptyBenchmark()));

}



TEST_F(JsonReporterTest_864, BenchmarkFailed_NoException_864) {

    EXPECT_NO_THROW(reporter.benchmarkFailed(StringRef{}));

}



TEST_F(JsonReporterTest_864, ListReporters_NoException_864) {

    EXPECT_NO_THROW(reporter.listReporters({}));

}



TEST_F(JsonReporterTest_864, ListListeners_NoException_864) {

    EXPECT_NO_THROW(reporter.listListeners({}));

}



TEST_F(JsonReporterTest_864, ListTests_NoException_864) {

    EXPECT_NO_THROW(reporter.listTests({}));

}



TEST_F(JsonReporterTest_864, ListTags_NoException_864) {

    EXPECT_NO_THROW(reporter.listTags({}));

}
