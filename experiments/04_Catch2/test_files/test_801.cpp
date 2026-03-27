#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

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



class MultiReporterTest_801 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockIEventListener> mockListener;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(&mockListener, [](IEventListener*){}));

    }

};



TEST_F(MultiReporterTest_801, SectionEndedDelegatesToAllListeners_801) {

    SectionStats sectionStats(SectionInfo("test", "", 0), Counts(), 0.0, false);

    EXPECT_CALL(mockListener, sectionEnded(sectionStats)).Times(1);



    multiReporter.sectionEnded(sectionStats);

}



TEST_F(MultiReporterTest_801, AddListenerAddsNewListener_801) {

    NiceMock<MockIEventListener> anotherMockListener;

    EXPECT_CALL(anotherMockListener, sectionEnded(::testing::_)).Times(1);



    multiReporter.addListener(IEventListenerPtr(&anotherMockListener, [](IEventListener*){}));



    SectionStats sectionStats(SectionInfo("test", "", 0), Counts(), 0.0, false);

    multiReporter.sectionEnded(sectionStats);

}



TEST_F(MultiReporterTest_801, AddReporterAddsNewReporter_801) {

    NiceMock<MockIEventListener> anotherMockListener;

    EXPECT_CALL(anotherMockListener, sectionEnded(::testing::_)).Times(1);



    multiReporter.addReporter(IEventListenerPtr(&anotherMockListener, [](IEventListener*){}));



    SectionStats sectionStats(SectionInfo("test", "", 0), Counts(), 0.0, false);

    multiReporter.sectionEnded(sectionStats);

}



TEST_F(MultiReporterTest_801, NoListenersDoesNotCrash_801) {

    MultiReporter emptyMultiReporter;

    SectionStats sectionStats(SectionInfo("test", "", 0), Counts(), 0.0, false);



    EXPECT_NO_THROW(emptyMultiReporter.sectionEnded(sectionStats));

}



TEST_F(MultiReporterTest_801, MultipleListenersReceiveNotification_801) {

    NiceMock<MockIEventListener> anotherMockListener;

    EXPECT_CALL(mockListener, sectionEnded(::testing::_)).Times(1);

    EXPECT_CALL(anotherMockListener, sectionEnded(::testing::_)).Times(1);



    multiReporter.addListener(IEventListenerPtr(&anotherMockListener, [](IEventListener*){}));



    SectionStats sectionStats(SectionInfo("test", "", 0), Counts(), 0.0, false);

    multiReporter.sectionEnded(sectionStats);

}
