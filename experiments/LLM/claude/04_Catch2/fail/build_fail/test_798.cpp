#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_test_run_info.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock class for IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));
};

class MultiReporterTest_798 : public ::testing::Test {
protected:
    MultiReporter multiReporter{nullptr};

    // Helper to create a mock and keep a raw pointer to it
    std::pair<Detail::unique_ptr<IEventListener>, MockEventListener*> createMock() {
        auto raw = new MockEventListener();
        MockEventListener* rawPtr = raw;
        Detail::unique_ptr<IEventListener> ptr(raw);
        return {std::move(ptr), rawPtr};
    }
};

// Test: sectionStarting is forwarded to a single reporter
TEST_F(MultiReporterTest_798, SectionStartingForwardedToSingleReporter_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    SectionInfo info(SourceLineInfo("file.cpp", 1), "TestSection");
    EXPECT_CALL(*mock, sectionStarting(_)).Times(Exactly(1));
    multiReporter.sectionStarting(info);
}

// Test: sectionStarting is forwarded to multiple reporters
TEST_F(MultiReporterTest_798, SectionStartingForwardedToMultipleReporters_798) {
    auto [ptr1, mock1] = createMock();
    auto [ptr2, mock2] = createMock();
    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    SectionInfo info(SourceLineInfo("file.cpp", 1), "TestSection");
    EXPECT_CALL(*mock1, sectionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, sectionStarting(_)).Times(Exactly(1));
    multiReporter.sectionStarting(info);
}

// Test: sectionStarting with no reporters does not crash
TEST_F(MultiReporterTest_798, SectionStartingWithNoReporters_798) {
    SectionInfo info(SourceLineInfo("file.cpp", 1), "TestSection");
    EXPECT_NO_THROW(multiReporter.sectionStarting(info));
}

// Test: sectionStarting is forwarded to listeners and reporters
TEST_F(MultiReporterTest_798, SectionStartingForwardedToListenersAndReporters_798) {
    auto [listenerPtr, listenerMock] = createMock();
    auto [reporterPtr, reporterMock] = createMock();
    multiReporter.addListener(std::move(listenerPtr));
    multiReporter.addReporter(std::move(reporterPtr));

    SectionInfo info(SourceLineInfo("file.cpp", 1), "TestSection");
    EXPECT_CALL(*listenerMock, sectionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*reporterMock, sectionStarting(_)).Times(Exactly(1));
    multiReporter.sectionStarting(info);
}

// Test: noMatchingTestCases is forwarded to all reporters
TEST_F(MultiReporterTest_798, NoMatchingTestCasesForwarded_798) {
    auto [ptr1, mock1] = createMock();
    auto [ptr2, mock2] = createMock();
    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));
    multiReporter.noMatchingTestCases("someSpec"_catch_sr);
}

// Test: fatalErrorEncountered is forwarded
TEST_F(MultiReporterTest_798, FatalErrorEncounteredForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(Exactly(1));
    multiReporter.fatalErrorEncountered("fatal error"_catch_sr);
}

// Test: reportInvalidTestSpec is forwarded
TEST_F(MultiReporterTest_798, ReportInvalidTestSpecForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(Exactly(1));
    multiReporter.reportInvalidTestSpec("invalid"_catch_sr);
}

// Test: benchmarkPreparing is forwarded
TEST_F(MultiReporterTest_798, BenchmarkPreparingForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    EXPECT_CALL(*mock, benchmarkPreparing(_)).Times(Exactly(1));
    multiReporter.benchmarkPreparing("bench"_catch_sr);
}

// Test: benchmarkFailed is forwarded
TEST_F(MultiReporterTest_798, BenchmarkFailedForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(Exactly(1));
    multiReporter.benchmarkFailed("bench error"_catch_sr);
}

// Test: skipTest is forwarded to all
TEST_F(MultiReporterTest_798, SkipTestForwarded_798) {
    auto [ptr1, mock1] = createMock();
    auto [ptr2, mock2] = createMock();
    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    EXPECT_CALL(*mock1, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, skipTest(_)).Times(Exactly(1));

    // We need a TestCaseInfo - create a minimal one
    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_catch_sr, {"test", "[tag]"}, SourceLineInfo("file.cpp", 1));
    multiReporter.skipTest(*testCaseInfo);
}

// Test: Multiple listeners are added before reporters (ordering)
TEST_F(MultiReporterTest_798, ListenersBeforeReporters_798) {
    auto [listener1Ptr, listener1Mock] = createMock();
    auto [listener2Ptr, listener2Mock] = createMock();
    auto [reporterPtr, reporterMock] = createMock();

    multiReporter.addListener(std::move(listener1Ptr));
    multiReporter.addReporter(std::move(reporterPtr));
    multiReporter.addListener(std::move(listener2Ptr));

    // All three should receive the call
    SectionInfo info(SourceLineInfo("file.cpp", 1), "TestSection");
    EXPECT_CALL(*listener1Mock, sectionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*listener2Mock, sectionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*reporterMock, sectionStarting(_)).Times(Exactly(1));
    multiReporter.sectionStarting(info);
}

// Test: noMatchingTestCases with no reporters
TEST_F(MultiReporterTest_798, NoMatchingTestCasesWithNoReporters_798) {
    EXPECT_NO_THROW(multiReporter.noMatchingTestCases("spec"_catch_sr));
}

// Test: fatalErrorEncountered with no reporters
TEST_F(MultiReporterTest_798, FatalErrorWithNoReporters_798) {
    EXPECT_NO_THROW(multiReporter.fatalErrorEncountered("error"_catch_sr));
}

// Test: calling sectionStarting multiple times
TEST_F(MultiReporterTest_798, SectionStartingCalledMultipleTimes_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    SectionInfo info1(SourceLineInfo("file.cpp", 1), "Section1");
    SectionInfo info2(SourceLineInfo("file.cpp", 2), "Section2");

    EXPECT_CALL(*mock, sectionStarting(_)).Times(Exactly(2));
    multiReporter.sectionStarting(info1);
    multiReporter.sectionStarting(info2);
}

// Test: assertionStarting is forwarded
TEST_F(MultiReporterTest_798, AssertionStartingForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    EXPECT_CALL(*mock, assertionStarting(_)).Times(Exactly(1));

    AssertionInfo assertionInfo{"macro", SourceLineInfo("file.cpp", 10), "expression", ResultDisposition::Normal};
    multiReporter.assertionStarting(assertionInfo);
}

// Test: listReporters forwarded to all
TEST_F(MultiReporterTest_798, ListReportersForwarded_798) {
    auto [ptr1, mock1] = createMock();
    auto [ptr2, mock2] = createMock();
    multiReporter.addReporter(std::move(ptr1));
    multiReporter.addReporter(std::move(ptr2));

    std::vector<ReporterDescription> descriptions;
    EXPECT_CALL(*mock1, listReporters(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, listReporters(_)).Times(Exactly(1));
    multiReporter.listReporters(descriptions);
}

// Test: listListeners forwarded
TEST_F(MultiReporterTest_798, ListListenersForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    std::vector<ListenerDescription> descriptions;
    EXPECT_CALL(*mock, listListeners(_)).Times(Exactly(1));
    multiReporter.listListeners(descriptions);
}

// Test: listTests forwarded
TEST_F(MultiReporterTest_798, ListTestsForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    std::vector<TestCaseHandle> tests;
    EXPECT_CALL(*mock, listTests(_)).Times(Exactly(1));
    multiReporter.listTests(tests);
}

// Test: listTags forwarded
TEST_F(MultiReporterTest_798, ListTagsForwarded_798) {
    auto [ptr, mock] = createMock();
    multiReporter.addReporter(std::move(ptr));

    std::vector<TagInfo> tags;
    EXPECT_CALL(*mock, listTags(_)).Times(Exactly(1));
    multiReporter.listTags(tags);
}

// Test: benchmarkPreparing with no reporters
TEST_F(MultiReporterTest_798, BenchmarkPreparingNoReporters_798) {
    EXPECT_NO_THROW(multiReporter.benchmarkPreparing("bench"_catch_sr));
}

// Test: multiple listeners receiving the same event
TEST_F(MultiReporterTest_798, MultipleListenersReceiveSameEvent_798) {
    auto [l1Ptr, l1Mock] = createMock();
    auto [l2Ptr, l2Mock] = createMock();
    auto [l3Ptr, l3Mock] = createMock();

    multiReporter.addListener(std::move(l1Ptr));
    multiReporter.addListener(std::move(l2Ptr));
    multiReporter.addListener(std::move(l3Ptr));

    EXPECT_CALL(*l1Mock, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*l2Mock, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*l3Mock, fatalErrorEncountered(_)).Times(Exactly(1));

    multiReporter.fatalErrorEncountered("error"_catch_sr);
}
