#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::StrictMock;

// Mock for IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef invalidArgument), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo& testRunInfo), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo& testInfo, uint64_t partNumber), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo& sectionInfo), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo& benchmarkInfo), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>& benchmarkStats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo& assertionInfo), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats& assertionStats), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats& sectionStats), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats& testCaseStats, uint64_t partNumber), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats& testCaseStats), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats& testRunStats), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>& descriptions), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>& descriptions), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>& tests), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>& tags), (override));
};

class MultiReporterTest_804 : public ::testing::Test {
protected:
    MultiReporter createMultiReporter() {
        // MultiReporter inherits IEventListener which takes IConfig*
        // We pass nullptr as config
        return MultiReporter(nullptr);
    }

    // Helper: create a mock and keep a raw pointer for expectations, 
    // then wrap in Detail::unique_ptr for ownership transfer
    std::pair<MockEventListener*, Detail::unique_ptr<IEventListener>> createMockReporter() {
        auto* raw = new StrictMock<MockEventListener>();
        Detail::unique_ptr<IEventListener> ptr(raw);
        return {raw, std::move(ptr)};
    }
};

// Test that testRunEnded is forwarded to a single reporter
TEST_F(MultiReporterTest_804, TestRunEndedForwardedToSingleReporter_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, testRunEnded(_)).Times(1);

    multi.addReporter(std::move(ptr));

    TestRunInfo runInfo("test");
    Totals totals;
    TestRunStats stats(runInfo, totals, false);
    multi.testRunEnded(stats);
}

// Test that testRunEnded is forwarded to multiple reporters
TEST_F(MultiReporterTest_804, TestRunEndedForwardedToMultipleReporters_804) {
    auto multi = createMultiReporter();

    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();
    auto [mock3, ptr3] = createMockReporter();

    EXPECT_CALL(*mock1, testRunEnded(_)).Times(1);
    EXPECT_CALL(*mock2, testRunEnded(_)).Times(1);
    EXPECT_CALL(*mock3, testRunEnded(_)).Times(1);

    multi.addReporter(std::move(ptr1));
    multi.addReporter(std::move(ptr2));
    multi.addReporter(std::move(ptr3));

    TestRunInfo runInfo("test");
    Totals totals;
    TestRunStats stats(runInfo, totals, false);
    multi.testRunEnded(stats);
}

// Test that testRunEnded with no reporters does not crash
TEST_F(MultiReporterTest_804, TestRunEndedWithNoReportersDoesNotCrash_804) {
    auto multi = createMultiReporter();

    TestRunInfo runInfo("test");
    Totals totals;
    TestRunStats stats(runInfo, totals, false);
    EXPECT_NO_THROW(multi.testRunEnded(stats));
}

// Test that listeners also receive testRunEnded
TEST_F(MultiReporterTest_804, TestRunEndedForwardedToListeners_804) {
    auto multi = createMultiReporter();

    auto [mockListener, listenerPtr] = createMockReporter();
    auto [mockReporter, reporterPtr] = createMockReporter();

    EXPECT_CALL(*mockListener, testRunEnded(_)).Times(1);
    EXPECT_CALL(*mockReporter, testRunEnded(_)).Times(1);

    multi.addListener(std::move(listenerPtr));
    multi.addReporter(std::move(reporterPtr));

    TestRunInfo runInfo("test");
    Totals totals;
    TestRunStats stats(runInfo, totals, false);
    multi.testRunEnded(stats);
}

// Test testRunStarting is forwarded
TEST_F(MultiReporterTest_804, TestRunStartingForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, testRunStarting(_)).Times(1);

    multi.addReporter(std::move(ptr));

    TestRunInfo runInfo("test");
    multi.testRunStarting(runInfo);
}

// Test testCaseStarting is forwarded
TEST_F(MultiReporterTest_804, TestCaseStartingForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, testCaseStarting(_)).Times(1);

    multi.addReporter(std::move(ptr));

    TestCaseInfo testInfo("", {"test", "tag"}, {"file", 1});
    multi.testCaseStarting(testInfo);
}

// Test testCaseEnded is forwarded
TEST_F(MultiReporterTest_804, TestCaseEndedForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, testCaseEnded(_)).Times(1);

    multi.addReporter(std::move(ptr));

    TestCaseInfo testInfo("", {"test", "tag"}, {"file", 1});
    Totals totals;
    TestCaseStats stats(testInfo, totals, "", "", false);
    multi.testCaseEnded(stats);
}

// Test sectionStarting is forwarded
TEST_F(MultiReporterTest_804, SectionStartingForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, sectionStarting(_)).Times(1);

    multi.addReporter(std::move(ptr));

    SectionInfo sectionInfo("file", 1, "section");
    multi.sectionStarting(sectionInfo);
}

// Test sectionEnded is forwarded
TEST_F(MultiReporterTest_804, SectionEndedForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, sectionEnded(_)).Times(1);

    multi.addReporter(std::move(ptr));

    SectionInfo sectionInfo("file", 1, "section");
    Counts assertions;
    SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    multi.sectionEnded(sectionStats);
}

// Test noMatchingTestCases is forwarded
TEST_F(MultiReporterTest_804, NoMatchingTestCasesForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, noMatchingTestCases(_)).Times(1);

    multi.addReporter(std::move(ptr));
    multi.noMatchingTestCases("someSpec");
}

// Test fatalErrorEncountered is forwarded
TEST_F(MultiReporterTest_804, FatalErrorEncounteredForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(1);

    multi.addReporter(std::move(ptr));
    multi.fatalErrorEncountered("fatal error");
}

// Test reportInvalidTestSpec is forwarded
TEST_F(MultiReporterTest_804, ReportInvalidTestSpecForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(1);

    multi.addReporter(std::move(ptr));
    multi.reportInvalidTestSpec("invalid");
}

// Test skipTest is forwarded
TEST_F(MultiReporterTest_804, SkipTestForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, skipTest(_)).Times(1);

    multi.addReporter(std::move(ptr));

    TestCaseInfo testInfo("", {"test", "tag"}, {"file", 1});
    multi.skipTest(testInfo);
}

// Test benchmarkPreparing is forwarded
TEST_F(MultiReporterTest_804, BenchmarkPreparingForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, benchmarkPreparing(_)).Times(1);

    multi.addReporter(std::move(ptr));
    multi.benchmarkPreparing("bench");
}

// Test benchmarkFailed is forwarded
TEST_F(MultiReporterTest_804, BenchmarkFailedForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(1);

    multi.addReporter(std::move(ptr));
    multi.benchmarkFailed("error");
}

// Test that listeners are placed before reporters (listener receives call before reporter)
TEST_F(MultiReporterTest_804, ListenersCalledBeforeReporters_804) {
    auto multi = createMultiReporter();

    auto [mockReporter, reporterPtr] = createMockReporter();
    auto [mockListener, listenerPtr] = createMockReporter();

    // Add reporter first, then listener
    // The multi reporter should still call listener before reporter
    {
        ::testing::InSequence seq;
        EXPECT_CALL(*mockListener, testRunEnded(_)).Times(1);
        EXPECT_CALL(*mockReporter, testRunEnded(_)).Times(1);
    }

    multi.addReporter(std::move(reporterPtr));
    multi.addListener(std::move(listenerPtr));

    TestRunInfo runInfo("test");
    Totals totals;
    TestRunStats stats(runInfo, totals, false);
    multi.testRunEnded(stats);
}

// Test assertionStarting is forwarded
TEST_F(MultiReporterTest_804, AssertionStartingForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, assertionStarting(_)).Times(1);

    multi.addReporter(std::move(ptr));

    AssertionInfo info("", {"file", 1}, "", ResultDisposition::Normal);
    multi.assertionStarting(info);
}

// Test assertionEnded is forwarded
TEST_F(MultiReporterTest_804, AssertionEndedForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, assertionEnded(_)).Times(1);

    multi.addReporter(std::move(ptr));

    AssertionInfo info("", {"file", 1}, "", ResultDisposition::Normal);
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));
    std::vector<MessageInfo> infoMessages;
    Counts counts;
    AssertionStats assertionStats(result, infoMessages, counts);
    multi.assertionEnded(assertionStats);
}

// Test testCasePartialStarting is forwarded
TEST_F(MultiReporterTest_804, TestCasePartialStartingForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, testCasePartialStarting(_, 42)).Times(1);

    multi.addReporter(std::move(ptr));

    TestCaseInfo testInfo("", {"test", "tag"}, {"file", 1});
    multi.testCasePartialStarting(testInfo, 42);
}

// Test testCasePartialEnded is forwarded
TEST_F(MultiReporterTest_804, TestCasePartialEndedForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, testCasePartialEnded(_, 7)).Times(1);

    multi.addReporter(std::move(ptr));

    TestCaseInfo testInfo("", {"test", "tag"}, {"file", 1});
    Totals totals;
    TestCaseStats stats(testInfo, totals, "", "", false);
    multi.testCasePartialEnded(stats, 7);
}

// Test with aborting flag set to true in testRunStats
TEST_F(MultiReporterTest_804, TestRunEndedWithAbortingFlag_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, testRunEnded(_)).Times(1);

    multi.addReporter(std::move(ptr));

    TestRunInfo runInfo("aborted_test");
    Totals totals;
    TestRunStats stats(runInfo, totals, true);
    multi.testRunEnded(stats);
}

// Test listReporters forwarded
TEST_F(MultiReporterTest_804, ListReportersForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, listReporters(_)).Times(1);

    multi.addReporter(std::move(ptr));

    std::vector<ReporterDescription> descriptions;
    multi.listReporters(descriptions);
}

// Test listListeners forwarded
TEST_F(MultiReporterTest_804, ListListenersForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, listListeners(_)).Times(1);

    multi.addReporter(std::move(ptr));

    std::vector<ListenerDescription> descriptions;
    multi.listListeners(descriptions);
}

// Test listTests forwarded
TEST_F(MultiReporterTest_804, ListTestsForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, listTests(_)).Times(1);

    multi.addReporter(std::move(ptr));

    std::vector<TestCaseHandle> tests;
    multi.listTests(tests);
}

// Test listTags forwarded
TEST_F(MultiReporterTest_804, ListTagsForwarded_804) {
    auto multi = createMultiReporter();
    auto [mock, ptr] = createMockReporter();

    EXPECT_CALL(*mock, listTags(_)).Times(1);

    multi.addReporter(std::move(ptr));

    std::vector<TagInfo> tags;
    multi.listTags(tags);
}

// Test multiple listeners receive the same event
TEST_F(MultiReporterTest_804, MultipleListenersReceiveEvent_804) {
    auto multi = createMultiReporter();

    auto [mock1, ptr1] = createMockReporter();
    auto [mock2, ptr2] = createMockReporter();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multi.addListener(std::move(ptr1));
    multi.addListener(std::move(ptr2));

    multi.noMatchingTestCases("spec");
}

// Test mixed listeners and reporters all receive events
TEST_F(MultiReporterTest_804, MixedListenersAndReportersAllReceiveEvents_804) {
    auto multi = createMultiReporter();

    auto [mockL1, ptrL1] = createMockReporter();
    auto [mockL2, ptrL2] = createMockReporter();
    auto [mockR1, ptrR1] = createMockReporter();
    auto [mockR2, ptrR2] = createMockReporter();

    EXPECT_CALL(*mockL1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mockL2, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mockR1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mockR2, fatalErrorEncountered(_)).Times(1);

    multi.addListener(std::move(ptrL1));
    multi.addReporter(std::move(ptrR1));
    multi.addListener(std::move(ptrL2));
    multi.addReporter(std::move(ptrR2));

    multi.fatalErrorEncountered("error");
}
