#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_info.hpp"
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

class MultiReporterTest_799 : public ::testing::Test {
protected:
    MultiReporter multiReporter{ nullptr };
};

// ==================== assertionStarting tests ====================

TEST_F(MultiReporterTest_799, AssertionStartingForwardsToSingleReporter_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, assertionStarting(_)).Times(Exactly(1));

    Detail::unique_ptr<IEventListener> ptr(mock);
    multiReporter.addReporter(std::move(ptr));

    AssertionInfo info;
    info.macroName = "TEST_CASE"_catch_sr;
    info.capturedExpression = "expr"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    multiReporter.assertionStarting(info);
}

TEST_F(MultiReporterTest_799, AssertionStartingForwardsToMultipleReporters_799) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, assertionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, assertionStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "a == b"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    multiReporter.assertionStarting(info);
}

TEST_F(MultiReporterTest_799, AssertionStartingWithNoReportersDoesNotCrash_799) {
    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "x > 0"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    EXPECT_NO_THROW(multiReporter.assertionStarting(info));
}

TEST_F(MultiReporterTest_799, AssertionStartingForwardsToListenersAndReporters_799) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();
    EXPECT_CALL(*listener, assertionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter, assertionStarting(_)).Times(Exactly(1));

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "val"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    multiReporter.assertionStarting(info);
}

// ==================== noMatchingTestCases tests ====================

TEST_F(MultiReporterTest_799, NoMatchingTestCasesForwardsToAllReporters_799) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.noMatchingTestCases("some spec"_catch_sr);
}

TEST_F(MultiReporterTest_799, NoMatchingTestCasesWithNoReporters_799) {
    EXPECT_NO_THROW(multiReporter.noMatchingTestCases("spec"_catch_sr));
}

// ==================== fatalErrorEncountered tests ====================

TEST_F(MultiReporterTest_799, FatalErrorEncounteredForwardsToAll_799) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.fatalErrorEncountered("fatal error"_catch_sr);
}

TEST_F(MultiReporterTest_799, FatalErrorEncounteredWithNoReporters_799) {
    EXPECT_NO_THROW(multiReporter.fatalErrorEncountered("error"_catch_sr));
}

// ==================== reportInvalidTestSpec tests ====================

TEST_F(MultiReporterTest_799, ReportInvalidTestSpecForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter.reportInvalidTestSpec("bad spec"_catch_sr);
}

// ==================== benchmarkPreparing tests ====================

TEST_F(MultiReporterTest_799, BenchmarkPreparingForwardsToAll_799) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.benchmarkPreparing("bench"_catch_sr);
}

// ==================== benchmarkFailed tests ====================

TEST_F(MultiReporterTest_799, BenchmarkFailedForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter.benchmarkFailed("bench error"_catch_sr);
}

// ==================== skipTest tests ====================

TEST_F(MultiReporterTest_799, SkipTestForwardsToAll_799) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, skipTest(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    TestCaseInfo testInfo{"", {"test", "tag"}, {"test", 0, 0}, "", {}, false};
    multiReporter.skipTest(testInfo);
}

// ==================== addListener / addReporter ordering ====================

TEST_F(MultiReporterTest_799, ListenersAreCalledBeforeReporters_799) {
    // Verify both listeners and reporters are called (ordering is internal,
    // but we verify both get called)
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    {
        ::testing::InSequence seq;
        // Listeners should be called before reporters
        EXPECT_CALL(*listener1, assertionStarting(_)).Times(1);
        EXPECT_CALL(*listener2, assertionStarting(_)).Times(1);
        EXPECT_CALL(*reporter1, assertionStarting(_)).Times(1);
        EXPECT_CALL(*reporter2, assertionStarting(_)).Times(1);
    }

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "val"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    multiReporter.assertionStarting(info);
}

TEST_F(MultiReporterTest_799, ListenerAddedAfterReporterStillCalledInOrder_799) {
    auto* reporter = new MockEventListener();
    auto* listener = new MockEventListener();

    {
        ::testing::InSequence seq;
        EXPECT_CALL(*listener, assertionStarting(_)).Times(1);
        EXPECT_CALL(*reporter, assertionStarting(_)).Times(1);
    }

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter));
    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "val"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    multiReporter.assertionStarting(info);
}

// ==================== Multiple calls ====================

TEST_F(MultiReporterTest_799, AssertionStartingCalledMultipleTimes_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, assertionStarting(_)).Times(Exactly(3));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "x"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    multiReporter.assertionStarting(info);
    multiReporter.assertionStarting(info);
    multiReporter.assertionStarting(info);
}

// ==================== testRunStarting / testRunEnded ====================

TEST_F(MultiReporterTest_799, TestRunStartingForwardsToAll_799) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testRunStarting(_)).Times(1);
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    TestRunInfo runInfo("test run");
    multiReporter.testRunStarting(runInfo);
}

TEST_F(MultiReporterTest_799, TestRunEndingForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testRunEnded(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    Totals totals;
    TestRunStats runStats(TestRunInfo("run"), totals, false);
    multiReporter.testRunEnded(runStats);
}

// ==================== testCaseStarting / testCaseEnded ====================

TEST_F(MultiReporterTest_799, TestCaseStartingForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCaseStarting(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    TestCaseInfo testInfo{"", {"test", "tag"}, {"test", 0, 0}, "", {}, false};
    multiReporter.testCaseStarting(testInfo);
}

TEST_F(MultiReporterTest_799, TestCaseEndedForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCaseEnded(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    TestCaseInfo testInfo{"", {"test", "tag"}, {"test", 0, 0}, "", {}, false};
    Totals totals;
    TestCaseStats stats(testInfo, totals, "", "", false, false);
    multiReporter.testCaseEnded(stats);
}

// ==================== sectionStarting / sectionEnded ====================

TEST_F(MultiReporterTest_799, SectionStartingForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, sectionStarting(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    SectionInfo sectionInfo{"", "section"};
    multiReporter.sectionStarting(sectionInfo);
}

TEST_F(MultiReporterTest_799, SectionEndedForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, sectionEnded(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    Counts assertions;
    SectionInfo sectionInfo{"", "section"};
    SectionStats sectionStats(sectionInfo, assertions, 0.0, false);
    multiReporter.sectionEnded(sectionStats);
}

// ==================== testCasePartialStarting / testCasePartialEnded ====================

TEST_F(MultiReporterTest_799, TestCasePartialStartingForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCasePartialStarting(_, 42)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    TestCaseInfo testInfo{"", {"test", "tag"}, {"test", 0, 0}, "", {}, false};
    multiReporter.testCasePartialStarting(testInfo, 42);
}

TEST_F(MultiReporterTest_799, TestCasePartialEndedForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCasePartialEnded(_, 7)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    TestCaseInfo testInfo{"", {"test", "tag"}, {"test", 0, 0}, "", {}, false};
    Totals totals;
    TestCaseStats stats(testInfo, totals, "", "", false, false);
    multiReporter.testCasePartialEnded(stats, 7);
}

// ==================== assertionEnded ====================

TEST_F(MultiReporterTest_799, AssertionEndedForwardsToAll_799) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, assertionEnded(_)).Times(1);
    EXPECT_CALL(*mock2, assertionEnded(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    AssertionInfo info;
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "x == 1"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(info, std::move(data));
    AssertionStats stats(result, {}, {}, 0.0);
    multiReporter.assertionEnded(stats);
}

// ==================== list methods ====================

TEST_F(MultiReporterTest_799, ListReportersForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listReporters(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<ReporterDescription> descriptions;
    multiReporter.listReporters(descriptions);
}

TEST_F(MultiReporterTest_799, ListListenersForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listListeners(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<ListenerDescription> descriptions;
    multiReporter.listListeners(descriptions);
}

TEST_F(MultiReporterTest_799, ListTestsForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listTests(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<TestCaseHandle> tests;
    multiReporter.listTests(tests);
}

TEST_F(MultiReporterTest_799, ListTagsForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listTags(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<TagInfo> tags;
    multiReporter.listTags(tags);
}

// ==================== Benchmark start/end ====================

TEST_F(MultiReporterTest_799, BenchmarkStartingForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkStarting(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    BenchmarkInfo benchInfo{"bench", 1.0, 100, 10, 0.0, 0.0, 0.0};
    multiReporter.benchmarkStarting(benchInfo);
}

TEST_F(MultiReporterTest_799, BenchmarkEndedForwardsToAll_799) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkEnded(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    BenchmarkInfo benchInfo{"bench", 1.0, 100, 10, 0.0, 0.0, 0.0};
    BenchmarkStats<> stats{benchInfo, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, 0};
    multiReporter.benchmarkEnded(stats);
}

// ==================== Many reporters ====================

TEST_F(MultiReporterTest_799, ManyReportersAllReceiveEvents_799) {
    constexpr int N = 10;
    std::vector<MockEventListener*> mocks;
    for (int i = 0; i < N; ++i) {
        auto* mock = new MockEventListener();
        EXPECT_CALL(*mock, assertionStarting(_)).Times(1);
        mocks.push_back(mock);
        multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    }

    AssertionInfo info;
    info.macroName = "CHECK"_catch_sr;
    info.capturedExpression = "val"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;
    multiReporter.assertionStarting(info);
}
