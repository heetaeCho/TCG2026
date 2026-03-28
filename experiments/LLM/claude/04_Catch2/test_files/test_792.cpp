#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"

using namespace Catch;

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

class MultiReporterTest_792 : public ::testing::Test {
protected:
    MultiReporter makeMultiReporter() {
        // MultiReporter derives from IEventListener which takes IConfig const*
        return MultiReporter(nullptr);
    }
};

// ==================== benchmarkStarting tests ====================

TEST_F(MultiReporterTest_792, BenchmarkStartingForwardsToSingleReporter_792) {
    auto multi = makeMultiReporter();
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, benchmarkStarting(::testing::_)).Times(1);

    Detail::unique_ptr<IEventListener> mockPtr(mockRaw);
    multi.addReporter(std::move(mockPtr));

    BenchmarkInfo info{1.0, 100, 10, 1000, 0.001, 0.01};
    multi.benchmarkStarting(info);
}

TEST_F(MultiReporterTest_792, BenchmarkStartingForwardsToMultipleReporters_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    auto* mock3 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkStarting(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkStarting(::testing::_)).Times(1);
    EXPECT_CALL(*mock3, benchmarkStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock3));

    BenchmarkInfo info{2.0, 200, 20, 2000, 0.002, 0.02};
    multi.benchmarkStarting(info);
}

TEST_F(MultiReporterTest_792, BenchmarkStartingWithNoReportersDoesNotCrash_792) {
    auto multi = makeMultiReporter();

    BenchmarkInfo info{1.0, 100, 10, 1000, 0.001, 0.01};
    EXPECT_NO_THROW(multi.benchmarkStarting(info));
}

TEST_F(MultiReporterTest_792, BenchmarkStartingForwardsToListenersAndReporters_792) {
    auto multi = makeMultiReporter();

    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    EXPECT_CALL(*listener, benchmarkStarting(::testing::_)).Times(1);
    EXPECT_CALL(*reporter, benchmarkStarting(::testing::_)).Times(1);

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    BenchmarkInfo info{1.0, 100, 10, 1000, 0.001, 0.01};
    multi.benchmarkStarting(info);
}

// ==================== benchmarkPreparing tests ====================

TEST_F(MultiReporterTest_792, BenchmarkPreparingForwardsToAllReporters_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkPreparing(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkPreparing(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multi.benchmarkPreparing("test_benchmark"_catch_sr);
}

TEST_F(MultiReporterTest_792, BenchmarkPreparingWithNoReportersDoesNotCrash_792) {
    auto multi = makeMultiReporter();
    EXPECT_NO_THROW(multi.benchmarkPreparing("test"_catch_sr));
}

// ==================== benchmarkEnded tests ====================

TEST_F(MultiReporterTest_792, BenchmarkEndedForwardsToAllReporters_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkEnded(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkEnded(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    BenchmarkInfo info{1.0, 100, 10, 1000, 0.001, 0.01};
    BenchmarkStats<> stats{info, {}, {}, {}, {}};
    multi.benchmarkEnded(stats);
}

// ==================== benchmarkFailed tests ====================

TEST_F(MultiReporterTest_792, BenchmarkFailedForwardsToAllReporters_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkFailed(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkFailed(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multi.benchmarkFailed("some error"_catch_sr);
}

// ==================== noMatchingTestCases tests ====================

TEST_F(MultiReporterTest_792, NoMatchingTestCasesForwardsToAllReporters_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multi.noMatchingTestCases("unmatched"_catch_sr);
}

// ==================== fatalErrorEncountered tests ====================

TEST_F(MultiReporterTest_792, FatalErrorEncounteredForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, fatalErrorEncountered(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multi.fatalErrorEncountered("fatal"_catch_sr);
}

// ==================== reportInvalidTestSpec tests ====================

TEST_F(MultiReporterTest_792, ReportInvalidTestSpecForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, reportInvalidTestSpec(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, reportInvalidTestSpec(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multi.reportInvalidTestSpec("invalid"_catch_sr);
}

// ==================== testRunStarting tests ====================

TEST_F(MultiReporterTest_792, TestRunStartingForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, testRunStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    TestRunInfo runInfo("test run");
    multi.testRunStarting(runInfo);
}

// ==================== testCaseStarting tests ====================

TEST_F(MultiReporterTest_792, TestCaseStartingForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, testCaseStarting(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, testCaseStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    TestCaseInfo testInfo{"", {"test", "tag"}, SourceLineInfo("file", 1)};
    multi.testCaseStarting(testInfo);
}

// ==================== testCaseEnded tests ====================

TEST_F(MultiReporterTest_792, TestCaseEndedForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, testCaseEnded(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    TestCaseInfo testInfo{"", {"test", "tag"}, SourceLineInfo("file", 1)};
    Totals totals;
    TestCaseStats stats{testInfo, totals, "", "", false};
    multi.testCaseEnded(stats);
}

// ==================== testRunEnded tests ====================

TEST_F(MultiReporterTest_792, TestRunEndedForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, testRunEnded(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    TestRunInfo runInfo("test run");
    Totals totals;
    TestRunStats runStats{runInfo, totals, false};
    multi.testRunEnded(runStats);
}

// ==================== skipTest tests ====================

TEST_F(MultiReporterTest_792, SkipTestForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, skipTest(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    TestCaseInfo testInfo{"", {"test", "tag"}, SourceLineInfo("file", 1)};
    multi.skipTest(testInfo);
}

// ==================== addListener ordering tests ====================

TEST_F(MultiReporterTest_792, ListenerAddedBeforeReporterReceivesCalls_792) {
    auto multi = makeMultiReporter();

    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    {
        ::testing::InSequence seq;
        EXPECT_CALL(*listener, benchmarkStarting(::testing::_)).Times(1);
        EXPECT_CALL(*reporter, benchmarkStarting(::testing::_)).Times(1);
    }

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    BenchmarkInfo info{1.0, 100, 10, 1000, 0.001, 0.01};
    multi.benchmarkStarting(info);
}

// ==================== Multiple listeners tests ====================

TEST_F(MultiReporterTest_792, MultipleListenersAllReceiveCalls_792) {
    auto multi = makeMultiReporter();

    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();

    EXPECT_CALL(*listener1, benchmarkStarting(::testing::_)).Times(1);
    EXPECT_CALL(*listener2, benchmarkStarting(::testing::_)).Times(1);
    EXPECT_CALL(*reporter1, benchmarkStarting(::testing::_)).Times(1);

    multi.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multi.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter1));

    BenchmarkInfo info{1.0, 100, 10, 1000, 0.001, 0.01};
    multi.benchmarkStarting(info);
}

// ==================== sectionStarting/sectionEnded tests ====================

TEST_F(MultiReporterTest_792, SectionStartingForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, sectionStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    SectionInfo sectionInfo{SourceLineInfo("file", 1), "section"};
    multi.sectionStarting(sectionInfo);
}

TEST_F(MultiReporterTest_792, SectionEndedForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, sectionEnded(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    SectionInfo sectionInfo{SourceLineInfo("file", 1), "section"};
    Counts assertions;
    SectionStats stats{sectionInfo, assertions, 0.0, false};
    multi.sectionEnded(stats);
}

// ==================== assertionStarting/assertionEnded tests ====================

TEST_F(MultiReporterTest_792, AssertionStartingForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, assertionStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    AssertionInfo assertionInfo{"", SourceLineInfo("file", 1), "", ResultDisposition::Normal};
    multi.assertionStarting(assertionInfo);
}

TEST_F(MultiReporterTest_792, AssertionEndedForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, assertionEnded(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    AssertionInfo assertionInfo{"", SourceLineInfo("file", 1), "", ResultDisposition::Normal};
    AssertionResultData data{ResultWas::Ok, LazyExpression(false)};
    AssertionResult result{assertionInfo, std::move(data)};
    AssertionStats stats{result, {}, {}, Totals(), false};
    multi.assertionEnded(stats);
}

// ==================== testCasePartialStarting/testCasePartialEnded tests ====================

TEST_F(MultiReporterTest_792, TestCasePartialStartingForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, testCasePartialStarting(::testing::_, 42)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    TestCaseInfo testInfo{"", {"test", "tag"}, SourceLineInfo("file", 1)};
    multi.testCasePartialStarting(testInfo, 42);
}

TEST_F(MultiReporterTest_792, TestCasePartialEndedForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, testCasePartialEnded(::testing::_, 7)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    TestCaseInfo testInfo{"", {"test", "tag"}, SourceLineInfo("file", 1)};
    Totals totals;
    TestCaseStats stats{testInfo, totals, "", "", false};
    multi.testCasePartialEnded(stats, 7);
}

// ==================== Multiple calls tests ====================

TEST_F(MultiReporterTest_792, BenchmarkStartingCalledMultipleTimes_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkStarting(::testing::_)).Times(3);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    BenchmarkInfo info{1.0, 100, 10, 1000, 0.001, 0.01};
    multi.benchmarkStarting(info);
    multi.benchmarkStarting(info);
    multi.benchmarkStarting(info);
}

// ==================== list* methods tests ====================

TEST_F(MultiReporterTest_792, ListReportersForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, listReporters(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    std::vector<ReporterDescription> descriptions;
    multi.listReporters(descriptions);
}

TEST_F(MultiReporterTest_792, ListListenersForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, listListeners(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    std::vector<ListenerDescription> descriptions;
    multi.listListeners(descriptions);
}

TEST_F(MultiReporterTest_792, ListTestsForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, listTests(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    std::vector<TestCaseHandle> tests;
    multi.listTests(tests);
}

TEST_F(MultiReporterTest_792, ListTagsForwardsToAll_792) {
    auto multi = makeMultiReporter();

    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, listTags(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    std::vector<TagInfo> tags;
    multi.listTags(tags);
}
