#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockEventListener : public IEventListener {

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



    MockEventListener(IConfig const* config) : IEventListener(config) {}

};



class MultiReporterTest_795 : public ::testing::Test {

protected:

    MultiReporter multiReporter{nullptr};

    NiceMock<MockEventListener>* mockListener1;

    NiceMock<MockEventListener>* mockListener2;



    void SetUp() override {

        mockListener1 = new NiceMock<MockEventListener>(nullptr);

        mockListener2 = new NiceMock<MockEventListener>(nullptr);



        multiReporter.addListener(IEventListenerPtr(mockListener1));

        multiReporter.addListener(IEventListenerPtr(mockListener2));

    }



    void TearDown() override {

        delete mockListener1;

        delete mockListener2;

    }

};



TEST_F(MultiReporterTest_795, TestRunStarting_DelegatesToAllListeners_795) {

    TestRunInfo testRunInfo("TestSuite");

    EXPECT_CALL(*mockListener1, testRunStarting(testRunInfo));

    EXPECT_CALL(*mockListener2, testRunStarting(testRunInfo));



    multiReporter.testRunStarting(testRunInfo);

}



TEST_F(MultiReporterTest_795, NoMatchingTestCases_DelegatesToAllListeners_795) {

    StringRef unmatchedSpec("unmatched_spec");

    EXPECT_CALL(*mockListener1, noMatchingTestCases(unmatchedSpec));

    EXPECT_CALL(*mockListener2, noMatchingTestCases(unmatchedSpec));



    multiReporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(MultiReporterTest_795, FatalErrorEncountered_DelegatesToAllListeners_795) {

    StringRef error("fatal_error");

    EXPECT_CALL(*mockListener1, fatalErrorEncountered(error));

    EXPECT_CALL(*mockListener2, fatalErrorEncountered(error));



    multiReporter.fatalErrorEncountered(error);

}



TEST_F(MultiReporterTest_795, ReportInvalidTestSpec_DelegatesToAllListeners_795) {

    StringRef invalidArgument("invalid_arg");

    EXPECT_CALL(*mockListener1, reportInvalidTestSpec(invalidArgument));

    EXPECT_CALL(*mockListener2, reportInvalidTestSpec(invalidArgument));



    multiReporter.reportInvalidTestSpec(invalidArgument);

}



TEST_F(MultiReporterTest_795, BenchmarkPreparing_DelegatesToAllListeners_795) {

    StringRef benchmarkName("benchmark_name");

    EXPECT_CALL(*mockListener1, benchmarkPreparing(benchmarkName));

    EXPECT_CALL(*mockListener2, benchmarkPreparing(benchmarkName));



    multiReporter.benchmarkPreparing(benchmarkName);

}



TEST_F(MultiReporterTest_795, BenchmarkStarting_DelegatesToAllListeners_795) {

    BenchmarkInfo benchmarkInfo{"benchmark_name", "source_file.cpp"};

    EXPECT_CALL(*mockListener1, benchmarkStarting(_));

    EXPECT_CALL(*mockListener2, benchmarkStarting(_));



    multiReporter.benchmarkStarting(benchmarkInfo);

}



TEST_F(MultiReporterTest_795, BenchmarkEnded_DelegatesToAllListeners_795) {

    BenchmarkStats<> benchmarkStats;

    EXPECT_CALL(*mockListener1, benchmarkEnded(_));

    EXPECT_CALL(*mockListener2, benchmarkEnded(_));



    multiReporter.benchmarkEnded(benchmarkStats);

}



TEST_F(MultiReporterTest_795, BenchmarkFailed_DelegatesToAllListeners_795) {

    StringRef error("benchmark_error");

    EXPECT_CALL(*mockListener1, benchmarkFailed(error));

    EXPECT_CALL(*mockListener2, benchmarkFailed(error));



    multiReporter.benchmarkFailed(error);

}



TEST_F(MultiReporterTest_795, TestCaseStarting_DelegatesToAllListeners_795) {

    TestCaseInfo testCaseInfo{"test_case_name", "source_file.cpp"};

    EXPECT_CALL(*mockListener1, testCaseStarting(testCaseInfo));

    EXPECT_CALL(*mockListener2, testCaseStarting(testCaseInfo));



    multiReporter.testCaseStarting(testCaseInfo);

}



TEST_F(MultiReporterTest_795, TestCasePartialStarting_DelegatesToAllListeners_795) {

    TestCaseInfo testCaseInfo{"test_case_name", "source_file.cpp"};

    uint64_t partNumber = 1;

    EXPECT_CALL(*mockListener1, testCasePartialStarting(testCaseInfo, partNumber));

    EXPECT_CALL(*mockListener2, testCasePartialStarting(testCaseInfo, partNumber));



    multiReporter.testCasePartialStarting(testCaseInfo, partNumber);

}



TEST_F(MultiReporterTest_795, SectionStarting_DelegatesToAllListeners_795) {

    SectionInfo sectionInfo{"section_name", "source_file.cpp"};

    EXPECT_CALL(*mockListener1, sectionStarting(sectionInfo));

    EXPECT_CALL(*mockListener2, sectionStarting(sectionInfo));



    multiReporter.sectionStarting(sectionInfo);

}



TEST_F(MultiReporterTest_795, AssertionStarting_DelegatesToAllListeners_795) {

    AssertionInfo assertionInfo{"assertion_desc", "source_file.cpp"};

    EXPECT_CALL(*mockListener1, assertionStarting(assertionInfo));

    EXPECT_CALL(*mockListener2, assertionStarting(assertionInfo));



    multiReporter.assertionStarting(assertionInfo);

}



TEST_F(MultiReporterTest_795, AssertionEnded_DelegatesToAllListeners_795) {

    AssertionStats assertionStats;

    EXPECT_CALL(*mockListener1, assertionEnded(_));

    EXPECT_CALL(*mockListener2, assertionEnded(_));



    multiReporter.assertionEnded(assertionStats);

}



TEST_F(MultiReporterTest_795, SectionEnded_DelegatesToAllListeners_795) {

    SectionStats sectionStats;

    EXPECT_CALL(*mockListener1, sectionEnded(sectionStats));

    EXPECT_CALL(*mockListener2, sectionEnded(sectionStats));



    multiReporter.sectionEnded(sectionStats);

}



TEST_F(MultiReporterTest_795, TestCasePartialEnded_DelegatesToAllListeners_795) {

    TestCaseStats testCaseStats;

    uint64_t partNumber = 1;

    EXPECT_CALL(*mockListener1, testCasePartialEnded(testCaseStats, partNumber));

    EXPECT_CALL(*mockListener2, testCasePartialEnded(testCaseStats, partNumber));



    multiReporter.testCasePartialEnded(testCaseStats, partNumber);

}



TEST_F(MultiReporterTest_795, TestCaseEnded_DelegatesToAllListeners_795) {

    TestCaseStats testCaseStats;

    EXPECT_CALL(*mockListener1, testCaseEnded(testCaseStats));

    EXPECT_CALL(*mockListener2, testCaseEnded(testCaseStats));



    multiReporter.testCaseEnded(testCaseStats);

}



TEST_F(MultiReporterTest_795, TestRunEnded_DelegatesToAllListeners_795) {

    TestRunStats testRunStats;

    EXPECT_CALL(*mockListener1, testRunEnded(testRunStats));

    EXPECT_CALL(*mockListener2, testRunEnded(testRunStats));



    multiReporter.testRunEnded(testRunStats);

}



TEST_F(MultiReporterTest_795, SkipTest_DelegatesToAllListeners_795) {

    TestCaseInfo testCaseInfo{"test_case_name", "source_file.cpp"};

    EXPECT_CALL(*mockListener1, skipTest(testCaseInfo));

    EXPECT_CALL(*mockListener2, skipTest(testCaseInfo));



    multiReporter.skipTest(testCaseInfo);

}



TEST_F(MultiReporterTest_795, ListReporters_DelegatesToAllListeners_795) {

    std::vector<ReporterDescription> descriptions;

    EXPECT_CALL(*mockListener1, listReporters(descriptions));

    EXPECT_CALL(*mockListener2, listReporters(descriptions));



    multiReporter.listReporters(descriptions);

}



TEST_F(MultiReporterTest_795, ListListeners_DelegatesToAllListeners_795) {

    std::vector<ListenerDescription> descriptions;

    EXPECT_CALL(*mockListener1, listListeners(descriptions));

    EXPECT_CALL(*mockListener2, listListeners(descriptions));



    multiReporter.listListeners(descriptions);

}



TEST_F(MultiReporterTest_795, ListTests_DelegatesToAllListeners_795) {

    std::vector<TestCaseHandle> tests;

    EXPECT_CALL(*mockListener1, listTests(tests));

    EXPECT_CALL(*mockListener2, listTests(tests));



    multiReporter.listTests(tests);

}



TEST_F(MultiReporterTest_795, ListTags_DelegatesToAllListeners_795) {

    std::vector<TagInfo> tags;

    EXPECT_CALL(*mockListener1, listTags(tags));

    EXPECT_CALL(*mockListener2, listTags(tags));



    multiReporter.listTags(tags);

}
