#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_multi.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::MockFunction;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));

    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));

    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef arg), (override));

    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));

    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo & benchmarkInfo), (override));

    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<> & benchmarkStats), (override));

    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));

    MOCK_METHOD(void, testRunStarting, (const TestRunInfo & testRunInfo), (override));

    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo & testInfo), (override));

    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo & testInfo, uint64_t partNumber), (override));

    MOCK_METHOD(void, sectionStarting, (const SectionInfo & sectionInfo), (override));

    MOCK_METHOD(void, assertionStarting, (const AssertionInfo & assertionInfo), (override));

    MOCK_METHOD(void, assertionEnded, (const AssertionStats & assertionStats), (override));

    MOCK_METHOD(void, sectionEnded, (const SectionStats & sectionStats), (override));

    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats & testStats, uint64_t partNumber), (override));

    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats & testCaseStats), (override));

    MOCK_METHOD(void, testRunEnded, (const TestRunStats & testRunStats), (override));

    MOCK_METHOD(void, skipTest, (const TestCaseInfo & testInfo), (override));

    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription> & descriptions), (override));

    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription> & descriptions), (override));

    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle> & tests), (override));

    MOCK_METHOD(void, listTags, (const std::vector<TagInfo> & tags), (override));



    MockEventListener(IConfig const* config) : IEventListener(config) {}

};



class MultiReporterTest_804 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockEventListener> mockListener;

    NiceMock<MockEventListener> mockReporter;



    MultiReporterTest_804() {

        multiReporter.addListener(IEventListenerPtr(&mockListener, [](IEventListener*){}));

        multiReporter.addReporter(IEventListenerPtr(&mockReporter, [](IEventListener*){}));

    }

};



TEST_F(MultiReporterTest_804, TestRunEnded_ForwardsToAllListenersAndReporters_804) {

    TestRunStats stats(TestRunInfo(), Totals(), false);



    EXPECT_CALL(mockListener, testRunEnded(_)).Times(1);

    EXPECT_CALL(mockReporter, testRunEnded(_)).Times(1);



    multiReporter.testRunEnded(stats);

}



TEST_F(MultiReporterTest_804, NoMatchingTestCases_ForwardsToAllListenersAndReporters_804) {

    StringRef spec("some_spec");



    EXPECT_CALL(mockListener, noMatchingTestCases(spec)).Times(1);

    EXPECT_CALL(mockReporter, noMatchingTestCases(spec)).Times(1);



    multiReporter.noMatchingTestCases(spec);

}



TEST_F(MultiReporterTest_804, FatalErrorEncountered_ForwardsToAllListenersAndReporters_804) {

    StringRef error("fatal_error");



    EXPECT_CALL(mockListener, fatalErrorEncountered(error)).Times(1);

    EXPECT_CALL(mockReporter, fatalErrorEncountered(error)).Times(1);



    multiReporter.fatalErrorEncountered(error);

}



TEST_F(MultiReporterTest_804, ReportInvalidTestSpec_ForwardsToAllListenersAndReporters_804) {

    StringRef arg("invalid_spec");



    EXPECT_CALL(mockListener, reportInvalidTestSpec(arg)).Times(1);

    EXPECT_CALL(mockReporter, reportInvalidTestSpec(arg)).Times(1);



    multiReporter.reportInvalidTestSpec(arg);

}



TEST_F(MultiReporterTest_804, BenchmarkPreparing_ForwardsToAllListenersAndReporters_804) {

    StringRef name("benchmark_name");



    EXPECT_CALL(mockListener, benchmarkPreparing(name)).Times(1);

    EXPECT_CALL(mockReporter, benchmarkPreparing(name)).Times(1);



    multiReporter.benchmarkPreparing(name);

}



TEST_F(MultiReporterTest_804, BenchmarkStarting_ForwardsToAllListenersAndReporters_804) {

    BenchmarkInfo info;



    EXPECT_CALL(mockListener, benchmarkStarting(_)).Times(1);

    EXPECT_CALL(mockReporter, benchmarkStarting(_)).Times(1);



    multiReporter.benchmarkStarting(info);

}



TEST_F(MultiReporterTest_804, BenchmarkEnded_ForwardsToAllListenersAndReporters_804) {

    BenchmarkStats<> stats;



    EXPECT_CALL(mockListener, benchmarkEnded(_)).Times(1);

    EXPECT_CALL(mockReporter, benchmarkEnded(_)).Times(1);



    multiReporter.benchmarkEnded(stats);

}



TEST_F(MultiReporterTest_804, BenchmarkFailed_ForwardsToAllListenersAndReporters_804) {

    StringRef error("benchmark_failed");



    EXPECT_CALL(mockListener, benchmarkFailed(error)).Times(1);

    EXPECT_CALL(mockReporter, benchmarkFailed(error)).Times(1);



    multiReporter.benchmarkFailed(error);

}



TEST_F(MultiReporterTest_804, TestRunStarting_ForwardsToAllListenersAndReporters_804) {

    TestRunInfo info;



    EXPECT_CALL(mockListener, testRunStarting(_)).Times(1);

    EXPECT_CALL(mockReporter, testRunStarting(_)).Times(1);



    multiReporter.testRunStarting(info);

}



TEST_F(MultiReporterTest_804, TestCaseStarting_ForwardsToAllListenersAndReporters_804) {

    TestCaseInfo info;



    EXPECT_CALL(mockListener, testCaseStarting(_)).Times(1);

    EXPECT_CALL(mockReporter, testCaseStarting(_)).Times(1);



    multiReporter.testCaseStarting(info);

}



TEST_F(MultiReporterTest_804, TestCasePartialStarting_ForwardsToAllListenersAndReporters_804) {

    TestCaseInfo info;

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener, testCasePartialStarting(_, partNumber)).Times(1);

    EXPECT_CALL(mockReporter, testCasePartialStarting(_, partNumber)).Times(1);



    multiReporter.testCasePartialStarting(info, partNumber);

}



TEST_F(MultiReporterTest_804, SectionStarting_ForwardsToAllListenersAndReporters_804) {

    SectionInfo info;



    EXPECT_CALL(mockListener, sectionStarting(_)).Times(1);

    EXPECT_CALL(mockReporter, sectionStarting(_)).Times(1);



    multiReporter.sectionStarting(info);

}



TEST_F(MultiReporterTest_804, AssertionStarting_ForwardsToAllListenersAndReporters_804) {

    AssertionInfo info;



    EXPECT_CALL(mockListener, assertionStarting(_)).Times(1);

    EXPECT_CALL(mockReporter, assertionStarting(_)).Times(1);



    multiReporter.assertionStarting(info);

}



TEST_F(MultiReporterTest_804, AssertionEnded_ForwardsToAllListenersAndReporters_804) {

    AssertionStats stats;



    EXPECT_CALL(mockListener, assertionEnded(_)).Times(1);

    EXPECT_CALL(mockReporter, assertionEnded(_)).Times(1);



    multiReporter.assertionEnded(stats);

}



TEST_F(MultiReporterTest_804, SectionEnded_ForwardsToAllListenersAndReporters_804) {

    SectionStats stats;



    EXPECT_CALL(mockListener, sectionEnded(_)).Times(1);

    EXPECT_CALL(mockReporter, sectionEnded(_)).Times(1);



    multiReporter.sectionEnded(stats);

}



TEST_F(MultiReporterTest_804, TestCasePartialEnded_ForwardsToAllListenersAndReporters_804) {

    TestCaseStats stats;

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener, testCasePartialEnded(_, partNumber)).Times(1);

    EXPECT_CALL(mockReporter, testCasePartialEnded(_, partNumber)).Times(1);



    multiReporter.testCasePartialEnded(stats, partNumber);

}



TEST_F(MultiReporterTest_804, TestCaseEnded_ForwardsToAllListenersAndReporters_804) {

    TestCaseStats stats;



    EXPECT_CALL(mockListener, testCaseEnded(_)).Times(1);

    EXPECT_CALL(mockReporter, testCaseEnded(_)).Times(1);



    multiReporter.testCaseEnded(stats);

}



TEST_F(MultiReporterTest_804, SkipTest_ForwardsToAllListenersAndReporters_804) {

    TestCaseInfo info;



    EXPECT_CALL(mockListener, skipTest(_)).Times(1);

    EXPECT_CALL(mockReporter, skipTest(_)).Times(1);



    multiReporter.skipTest(info);

}



TEST_F(MultiReporterTest_804, ListReporters_ForwardsToAllListenersAndReporters_804) {

    std::vector<ReporterDescription> descriptions;



    EXPECT_CALL(mockListener, listReporters(descriptions)).Times(1);

    EXPECT_CALL(mockReporter, listReporters(descriptions)).Times(1);



    multiReporter.listReporters(descriptions);

}



TEST_F(MultiReporterTest_804, ListListeners_ForwardsToAllListenersAndReporters_804) {

    std::vector<ListenerDescription> descriptions;



    EXPECT_CALL(mockListener, listListeners(descriptions)).Times(1);

    EXPECT_CALL(mockReporter, listListeners(descriptions)).Times(1);



    multiReporter.listListeners(descriptions);

}



TEST_F(MultiReporterTest_804, ListTests_ForwardsToAllListenersAndReporters_804) {

    std::vector<TestCaseHandle> tests;



    EXPECT_CALL(mockListener, listTests(tests)).Times(1);

    EXPECT_CALL(mockReporter, listTests(tests)).Times(1);



    multiReporter.listTests(tests);

}



TEST_F(MultiReporterTest_804, ListTags_ForwardsToAllListenersAndReporters_804) {

    std::vector<TagInfo> tags;



    EXPECT_CALL(mockListener, listTags(tags)).Times(1);

    EXPECT_CALL(mockReporter, listTags(tags)).Times(1);



    multiReporter.listTags(tags);

}
