#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_multi.hpp"

#include "catch_interfaces_reporter.hpp"

#include "catch_assertion_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));

    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));

    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef arg), (override));

    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));

    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo &benchmarkInfo), (override));

    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<> &benchmarkStats), (override));

    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));

    MOCK_METHOD(void, testRunStarting, (const TestRunInfo &testRunInfo), (override));

    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo &testInfo), (override));

    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo &testInfo, uint64_t partNumber), (override));

    MOCK_METHOD(void, sectionStarting, (const SectionInfo &sectionInfo), (override));

    MOCK_METHOD(void, assertionStarting, (const AssertionInfo &assertionInfo), (override));

    MOCK_METHOD(void, assertionEnded, (const AssertionStats &assertionStats), (override));

    MOCK_METHOD(void, sectionEnded, (const SectionStats &sectionStats), (override));

    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats &testStats, uint64_t partNumber), (override));

    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats &testCaseStats), (override));

    MOCK_METHOD(void, testRunEnded, (const TestRunStats &testRunStats), (override));

    MOCK_METHOD(void, skipTest, (const TestCaseInfo &testInfo), (override));

    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription> &descriptions), (override));

    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription> &descriptions), (override));

    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle> &tests), (override));

    MOCK_METHOD(void, listTags, (const std::vector<TagInfo> &tags), (override));

};



class MultiReporterTest_799 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockIEventListener> mockListener1;

    NiceMock<MockIEventListener> mockListener2;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(&mockListener1, [](IEventListener*){}));

        multiReporter.addListener(IEventListenerPtr(&mockListener2, [](IEventListener*){}));

    }

};



TEST_F(MultiReporterTest_799, AssertionStarting_CallsAllListeners_799) {

    AssertionInfo assertionInfo;

    EXPECT_CALL(mockListener1, assertionStarting(_)).Times(1);

    EXPECT_CALL(mockListener2, assertionStarting(_)).Times(1);



    multiReporter.assertionStarting(assertionInfo);

}



TEST_F(MultiReporterTest_799, NoMatchingTestCases_CallsAllListeners_799) {

    StringRef unmatchedSpec("spec");

    EXPECT_CALL(mockListener1, noMatchingTestCases(_)).Times(1);

    EXPECT_CALL(mockListener2, noMatchingTestCases(_)).Times(1);



    multiReporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(MultiReporterTest_799, FatalErrorEncountered_CallsAllListeners_799) {

    StringRef error("error");

    EXPECT_CALL(mockListener1, fatalErrorEncountered(_)).Times(1);

    EXPECT_CALL(mockListener2, fatalErrorEncountered(_)).Times(1);



    multiReporter.fatalErrorEncountered(error);

}



TEST_F(MultiReporterTest_799, ReportInvalidTestSpec_CallsAllListeners_799) {

    StringRef arg("invalid");

    EXPECT_CALL(mockListener1, reportInvalidTestSpec(_)).Times(1);

    EXPECT_CALL(mockListener2, reportInvalidTestSpec(_)).Times(1);



    multiReporter.reportInvalidTestSpec(arg);

}



TEST_F(MultiReporterTest_799, BenchmarkPreparing_CallsAllListeners_799) {

    StringRef name("benchmark");

    EXPECT_CALL(mockListener1, benchmarkPreparing(_)).Times(1);

    EXPECT_CALL(mockListener2, benchmarkPreparing(_)).Times(1);



    multiReporter.benchmarkPreparing(name);

}



TEST_F(MultiReporterTest_799, BenchmarkStarting_CallsAllListeners_799) {

    BenchmarkInfo benchmarkInfo;

    EXPECT_CALL(mockListener1, benchmarkStarting(_)).Times(1);

    EXPECT_CALL(mockListener2, benchmarkStarting(_)).Times(1);



    multiReporter.benchmarkStarting(benchmarkInfo);

}



TEST_F(MultiReporterTest_799, BenchmarkEnded_CallsAllListeners_799) {

    BenchmarkStats<> benchmarkStats;

    EXPECT_CALL(mockListener1, benchmarkEnded(_)).Times(1);

    EXPECT_CALL(mockListener2, benchmarkEnded(_)).Times(1);



    multiReporter.benchmarkEnded(benchmarkStats);

}



TEST_F(MultiReporterTest_799, BenchmarkFailed_CallsAllListeners_799) {

    StringRef error("failed");

    EXPECT_CALL(mockListener1, benchmarkFailed(_)).Times(1);

    EXPECT_CALL(mockListener2, benchmarkFailed(_)).Times(1);



    multiReporter.benchmarkFailed(error);

}



TEST_F(MultiReporterTest_799, TestRunStarting_CallsAllListeners_799) {

    TestRunInfo testRunInfo;

    EXPECT_CALL(mockListener1, testRunStarting(_)).Times(1);

    EXPECT_CALL(mockListener2, testRunStarting(_)).Times(1);



    multiReporter.testRunStarting(testRunInfo);

}



TEST_F(MultiReporterTest_799, TestCaseStarting_CallsAllListeners_799) {

    TestCaseInfo testCaseInfo;

    EXPECT_CALL(mockListener1, testCaseStarting(_)).Times(1);

    EXPECT_CALL(mockListener2, testCaseStarting(_)).Times(1);



    multiReporter.testCaseStarting(testCaseInfo);

}



TEST_F(MultiReporterTest_799, TestCasePartialStarting_CallsAllListeners_799) {

    TestCaseInfo testCaseInfo;

    uint64_t partNumber = 1;

    EXPECT_CALL(mockListener1, testCasePartialStarting(_, _)).Times(1);

    EXPECT_CALL(mockListener2, testCasePartialStarting(_, _)).Times(1);



    multiReporter.testCasePartialStarting(testCaseInfo, partNumber);

}



TEST_F(MultiReporterTest_799, SectionStarting_CallsAllListeners_799) {

    SectionInfo sectionInfo;

    EXPECT_CALL(mockListener1, sectionStarting(_)).Times(1);

    EXPECT_CALL(mockListener2, sectionStarting(_)).Times(1);



    multiReporter.sectionStarting(sectionInfo);

}



TEST_F(MultiReporterTest_799, AssertionEnded_CallsAllListeners_799) {

    AssertionStats assertionStats;

    EXPECT_CALL(mockListener1, assertionEnded(_)).Times(1);

    EXPECT_CALL(mockListener2, assertionEnded(_)).Times(1);



    multiReporter.assertionEnded(assertionStats);

}



TEST_F(MultiReporterTest_799, SectionEnded_CallsAllListeners_799) {

    SectionStats sectionStats;

    EXPECT_CALL(mockListener1, sectionEnded(_)).Times(1);

    EXPECT_CALL(mockListener2, sectionEnded(_)).Times(1);



    multiReporter.sectionEnded(sectionStats);

}



TEST_F(MultiReporterTest_799, TestCasePartialEnded_CallsAllListeners_799) {

    TestCaseStats testCaseStats;

    uint64_t partNumber = 1;

    EXPECT_CALL(mockListener1, testCasePartialEnded(_, _)).Times(1);

    EXPECT_CALL(mockListener2, testCasePartialEnded(_, _)).Times(1);



    multiReporter.testCasePartialEnded(testCaseStats, partNumber);

}



TEST_F(MultiReporterTest_799, TestCaseEnded_CallsAllListeners_799) {

    TestCaseStats testCaseStats;

    EXPECT_CALL(mockListener1, testCaseEnded(_)).Times(1);

    EXPECT_CALL(mockListener2, testCaseEnded(_)).Times(1);



    multiReporter.testCaseEnded(testCaseStats);

}



TEST_F(MultiReporterTest_799, TestRunEnded_CallsAllListeners_799) {

    TestRunStats testRunStats;

    EXPECT_CALL(mockListener1, testRunEnded(_)).Times(1);

    EXPECT_CALL(mockListener2, testRunEnded(_)).Times(1);



    multiReporter.testRunEnded(testRunStats);

}



TEST_F(MultiReporterTest_799, SkipTest_CallsAllListeners_799) {

    TestCaseInfo testCaseInfo;

    EXPECT_CALL(mockListener1, skipTest(_)).Times(1);

    EXPECT_CALL(mockListener2, skipTest(_)).Times(1);



    multiReporter.skipTest(testCaseInfo);

}



TEST_F(MultiReporterTest_799, ListReporters_CallsAllListeners_799) {

    std::vector<ReporterDescription> descriptions;

    EXPECT_CALL(mockListener1, listReporters(_)).Times(1);

    EXPECT_CALL(mockListener2, listReporters(_)).Times(1);



    multiReporter.listReporters(descriptions);

}



TEST_F(MultiReporterTest_799, ListListeners_CallsAllListeners_799) {

    std::vector<ListenerDescription> descriptions;

    EXPECT_CALL(mockListener1, listListeners(_)).Times(1);

    EXPECT_CALL(mockListener2, listListeners(_)).Times(1);



    multiReporter.listListeners(descriptions);

}



TEST_F(MultiReporterTest_799, ListTests_CallsAllListeners_799) {

    std::vector<TestCaseHandle> tests;

    EXPECT_CALL(mockListener1, listTests(_)).Times(1);

    EXPECT_CALL(mockListener2, listTests(_)).Times(1);



    multiReporter.listTests(tests);

}



TEST_F(MultiReporterTest_799, ListTags_CallsAllListeners_799) {

    std::vector<TagInfo> tags;

    EXPECT_CALL(mockListener1, listTags(_)).Times(1);

    EXPECT_CALL(mockListener2, listTags(_)).Times(1);



    multiReporter.listTags(tags);

}
