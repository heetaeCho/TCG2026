#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch;



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

};



class MultiReporterTest_786 : public ::testing::Test {

protected:

    MultiReporter multi_reporter;

    std::shared_ptr<MockEventListener> mock_listener = std::make_shared<MockEventListener>();

};



TEST_F(MultiReporterTest_786, AddListener_NormalOperation_786) {

    EXPECT_CALL(*mock_listener, noMatchingTestCases(_)).Times(0);

    EXPECT_CALL(*mock_listener, fatalErrorEncountered(_)).Times(0);



    multi_reporter.addListener(CATCH_MOVE(mock_listener));



    // No way to directly verify the internal state, but we can ensure that adding doesn't cause immediate issues

}



TEST_F(MultiReporterTest_786, AddListener_MultipleListeners_786) {

    auto mock_listener2 = std::make_shared<MockEventListener>();

    

    EXPECT_CALL(*mock_listener, noMatchingTestCases(_)).Times(0);

    EXPECT_CALL(*mock_listener2, noMatchingTestCases(_)).Times(0);



    multi_reporter.addListener(CATCH_MOVE(mock_listener));

    multi_reporter.addListener(CATCH_MOVE(mock_listener2));



    // Ensure adding multiple listeners doesn't cause issues

}



TEST_F(MultiReporterTest_786, AddListener_ExceptionHandling_786) {

    // Since the function signatures don't indicate any exception handling, we assume it's safe to add a listener.

    // If exceptions were possible, they would need to be specified in the interface or documentation.

    EXPECT_NO_THROW(multi_reporter.addListener(CATCH_MOVE(mock_listener)));

}



TEST_F(MultiReporterTest_786, AddReporter_NormalOperation_786) {

    EXPECT_CALL(*mock_listener, noMatchingTestCases(_)).Times(0);

    EXPECT_CALL(*mock_listener, fatalErrorEncountered(_)).Times(0);



    multi_reporter.addReporter(CATCH_MOVE(mock_listener));



    // No way to directly verify the internal state, but we can ensure that adding doesn't cause immediate issues

}



TEST_F(MultiReporterTest_786, AddReporter_MultipleReporters_786) {

    auto mock_listener2 = std::make_shared<MockEventListener>();

    

    EXPECT_CALL(*mock_listener, noMatchingTestCases(_)).Times(0);

    EXPECT_CALL(*mock_listener2, noMatchingTestCases(_)).Times(0);



    multi_reporter.addReporter(CATCH_MOVE(mock_listener));

    multi_reporter.addReporter(CATCH_MOVE(mock_listener2));



    // Ensure adding multiple reporters doesn't cause issues

}



TEST_F(MultiReporterTest_786, AddReporter_ExceptionHandling_786) {

    // Since the function signatures don't indicate any exception handling, we assume it's safe to add a reporter.

    // If exceptions were possible, they would need to be specified in the interface or documentation.

    EXPECT_NO_THROW(multi_reporter.addReporter(CATCH_MOVE(mock_listener)));

}
