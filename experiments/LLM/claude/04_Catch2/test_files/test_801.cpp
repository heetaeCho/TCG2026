#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

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

class MultiReporterTest_801 : public ::testing::Test {
protected:
    MultiReporter multiReporter{ nullptr };
};

// Test: sectionEnded is forwarded to a single reporter
TEST_F(MultiReporterTest_801, SectionEndedForwardedToSingleReporter_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, sectionEnded(_)).Times(Exactly(1));

    Detail::unique_ptr<IEventListener> ptr(mock);
    multiReporter.addReporter(std::move(ptr));

    SectionStats stats(SectionInfo("", "test_section"), Counts(), 0.0, false);
    multiReporter.sectionEnded(stats);
}

// Test: sectionEnded is forwarded to multiple reporters
TEST_F(MultiReporterTest_801, SectionEndedForwardedToMultipleReporters_801) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    auto* mock3 = new MockEventListener();

    EXPECT_CALL(*mock1, sectionEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, sectionEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*mock3, sectionEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock3));

    SectionStats stats(SectionInfo("", "test_section"), Counts(), 0.0, false);
    multiReporter.sectionEnded(stats);
}

// Test: sectionEnded with no reporters does not crash
TEST_F(MultiReporterTest_801, SectionEndedWithNoReportersDoesNotCrash_801) {
    SectionStats stats(SectionInfo("", "test_section"), Counts(), 0.0, false);
    EXPECT_NO_THROW(multiReporter.sectionEnded(stats));
}

// Test: sectionEnded is forwarded to listeners as well as reporters
TEST_F(MultiReporterTest_801, SectionEndedForwardedToListenersAndReporters_801) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    EXPECT_CALL(*listener, sectionEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter, sectionEnded(_)).Times(Exactly(1));

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    SectionStats stats(SectionInfo("", "test_section"), Counts(), 0.0, false);
    multiReporter.sectionEnded(stats);
}

// Test: sectionEnded called multiple times forwards each call
TEST_F(MultiReporterTest_801, SectionEndedCalledMultipleTimes_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, sectionEnded(_)).Times(Exactly(3));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    SectionStats stats(SectionInfo("", "section1"), Counts(), 0.0, false);
    multiReporter.sectionEnded(stats);

    SectionStats stats2(SectionInfo("", "section2"), Counts(), 1.0, true);
    multiReporter.sectionEnded(stats2);

    SectionStats stats3(SectionInfo("", "section3"), Counts(), 2.5, false);
    multiReporter.sectionEnded(stats3);
}

// Test: noMatchingTestCases is forwarded to all reporters
TEST_F(MultiReporterTest_801, NoMatchingTestCasesForwarded_801) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.noMatchingTestCases("some spec"_catch_sr);
}

// Test: fatalErrorEncountered is forwarded to all reporters
TEST_F(MultiReporterTest_801, FatalErrorEncounteredForwarded_801) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.fatalErrorEncountered("fatal error"_catch_sr);
}

// Test: reportInvalidTestSpec is forwarded
TEST_F(MultiReporterTest_801, ReportInvalidTestSpecForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter.reportInvalidTestSpec("bad spec"_catch_sr);
}

// Test: testRunStarting is forwarded
TEST_F(MultiReporterTest_801, TestRunStartingForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testRunStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    TestRunInfo runInfo("test_group");
    multiReporter.testRunStarting(runInfo);
}

// Test: testCaseStarting is forwarded
TEST_F(MultiReporterTest_801, TestCaseStartingForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCaseStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    // We need a TestCaseInfo; use a minimal construction
    auto testCaseInfo = Catch::makeTestCaseInfo("", {"test_case", "[tag]"}, CATCH_INTERNAL_LINEINFO);
    multiReporter.testCaseStarting(*testCaseInfo);
}

// Test: testRunEnded is forwarded
TEST_F(MultiReporterTest_801, TestRunEndedForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testRunEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    TestRunInfo runInfo("test_group");
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    multiReporter.testRunEnded(runStats);
}

// Test: skipTest is forwarded
TEST_F(MultiReporterTest_801, SkipTestForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, skipTest(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    auto testCaseInfo = Catch::makeTestCaseInfo("", {"skipped_test", "[skip]"}, CATCH_INTERNAL_LINEINFO);
    multiReporter.skipTest(*testCaseInfo);
}

// Test: sectionStarting is forwarded
TEST_F(MultiReporterTest_801, SectionStartingForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, sectionStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    SectionInfo sectionInfo("", "test_section");
    multiReporter.sectionStarting(sectionInfo);
}

// Test: benchmarkPreparing is forwarded
TEST_F(MultiReporterTest_801, BenchmarkPreparingForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkPreparing(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    multiReporter.benchmarkPreparing("benchmark1"_catch_sr);
}

// Test: benchmarkFailed is forwarded
TEST_F(MultiReporterTest_801, BenchmarkFailedForwarded_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    multiReporter.benchmarkFailed("benchmark_error"_catch_sr);
}

// Test: addListener places listeners before reporters - both receive sectionEnded
TEST_F(MultiReporterTest_801, ListenersAndReportersBothReceiveSectionEnded_801) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    EXPECT_CALL(*listener1, sectionEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*listener2, sectionEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter1, sectionEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter2, sectionEnded(_)).Times(Exactly(1));

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    SectionStats stats(SectionInfo("", "section"), Counts(), 0.0, false);
    multiReporter.sectionEnded(stats);
}

// Test: sectionEnded with missingAssertions true
TEST_F(MultiReporterTest_801, SectionEndedWithMissingAssertions_801) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, sectionEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    SectionStats stats(SectionInfo("", "section_missing"), Counts(), 5.0, true);
    multiReporter.sectionEnded(stats);
}

// Test: testCaseEnded is forwarded to multiple reporters
TEST_F(MultiReporterTest_801, TestCaseEndedForwarded_801) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testCaseEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    auto testCaseInfo = Catch::makeTestCaseInfo("", {"test", "[tag]"}, CATCH_INTERNAL_LINEINFO);
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    multiReporter.testCaseEnded(testCaseStats);
}

// Test: adding only listeners (no reporters) still works for sectionEnded
TEST_F(MultiReporterTest_801, OnlyListenersReceiveSectionEnded_801) {
    auto* listener = new MockEventListener();
    EXPECT_CALL(*listener, sectionEnded(_)).Times(Exactly(1));

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));

    SectionStats stats(SectionInfo("", "section"), Counts(), 0.0, false);
    multiReporter.sectionEnded(stats);
}
