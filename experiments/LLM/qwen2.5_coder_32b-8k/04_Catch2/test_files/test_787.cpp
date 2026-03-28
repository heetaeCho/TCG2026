#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::NiceMock;

using ::testing::_;



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



    ReporterPreferences getPreferences() const override {

        return m_preferences;

    }

};



class MultiReporterTest_787 : public ::testing::Test {

protected:

    NiceMock<MockEventListener>* mockListener1;

    NiceMock<MockEventListener>* mockListener2;

    IEventListenerPtr listener1;

    IEventListenerPtr listener2;



    void SetUp() override {

        mockListener1 = new NiceMock<MockEventListener>(nullptr);

        mockListener2 = new NiceMock<MockEventListener>(nullptr);

        listener1.reset(mockListener1);

        listener2.reset(mockListener2);

    }



    void TearDown() override {

        delete mockListener1;

        delete mockListener2;

    }

};



TEST_F(MultiReporterTest_787, AddReporterIncreasesNonCapturingReportersCount_787) {

    MultiReporter multiReporter;

    EXPECT_CALL(*mockListener1, getPreferences())

        .WillOnce(::testing::Return(ReporterPreferences{.shouldRedirectStdOut = false}));



    multiReporter.addReporter(std::move(listener1));

    EXPECT_TRUE(multiReporter.m_haveNoncapturingReporters);

}



TEST_F(MultiReporterTest_787, AddCapturingReporterDoesNotIncreaseNonCapturingReportersCount_787) {

    MultiReporter multiReporter;

    EXPECT_CALL(*mockListener1, getPreferences())

        .WillOnce(::testing::Return(ReporterPreferences{.shouldRedirectStdOut = true}));



    multiReporter.addReporter(std::move(listener1));

    EXPECT_FALSE(multiReporter.m_haveNoncapturingReporters);

}



TEST_F(MultiReporterTest_787, AddMultipleListeners_787) {

    MultiReporter multiReporter;

    EXPECT_CALL(*mockListener1, getPreferences())

        .WillOnce(::testing::Return(ReporterPreferences{.shouldRedirectStdOut = false}));

    EXPECT_CALL(*mockListener2, getPreferences())

        .WillOnce(::testing::Return(ReporterPreferences{.shouldRedirectStdOut = true}));



    multiReporter.addReporter(std::move(listener1));

    multiReporter.addReporter(std::move(listener2));



    EXPECT_TRUE(multiReporter.m_haveNoncapturingReporters);

}



TEST_F(MultiReporterTest_787, AddNullptrListenerDoesNotCrash_787) {

    MultiReporter multiReporter;

    IEventListenerPtr nullListener(nullptr);



    multiReporter.addReporter(std::move(nullListener));

    EXPECT_FALSE(multiReporter.m_haveNoncapturingReporters);

}



TEST_F(MultiReporterTest_787, DispatchToMultipleListeners_787) {

    MultiReporter multiReporter;

    EXPECT_CALL(*mockListener1, getPreferences())

        .WillOnce(::testing::Return(ReporterPreferences{.shouldRedirectStdOut = false}));

    EXPECT_CALL(*mockListener2, getPreferences())

        .WillOnce(::testing::Return(ReporterPreferences{.shouldRedirectStdOut = true}));



    multiReporter.addReporter(std::move(listener1));

    multiReporter.addReporter(std::move(listener2));



    StringRef unmatchedSpec("unmatched");

    EXPECT_CALL(*mockListener1, noMatchingTestCases(unmatchedSpec));

    EXPECT_CALL(*mockListener2, noMatchingTestCases(unmatchedSpec));



    multiReporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(MultiReporterTest_787, AddListenerIncreasesInsertedListenersCount_787) {

    MultiReporter multiReporter;

    EXPECT_CALL(*mockListener1, getPreferences())

        .WillOnce(::testing::Return(ReporterPreferences{.shouldRedirectStdOut = false}));



    multiReporter.addListener(std::move(listener1));

    EXPECT_EQ(multiReporter.m_insertedListeners, 1);

}
