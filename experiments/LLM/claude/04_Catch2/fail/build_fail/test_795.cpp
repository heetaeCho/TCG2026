#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;
using ::testing::InSequence;

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

class MultiReporterTest_795 : public ::testing::Test {
protected:
    MultiReporter multiReporter{nullptr};
};

// --- testRunStarting ---

TEST_F(MultiReporterTest_795, TestRunStartingForwardsToSingleReporter_795) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testRunStarting(_)).Times(Exactly(1));

    Detail::unique_ptr<IEventListener> ptr(mock);
    multiReporter.addReporter(std::move(ptr));

    TestRunInfo info("test run");
    multiReporter.testRunStarting(info);
}

TEST_F(MultiReporterTest_795, TestRunStartingForwardsToMultipleReporters_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    auto* mock3 = new MockEventListener();

    EXPECT_CALL(*mock1, testRunStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock3, testRunStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock3));

    TestRunInfo info("test run");
    multiReporter.testRunStarting(info);
}

TEST_F(MultiReporterTest_795, TestRunStartingWithNoReporters_795) {
    // Should not crash when no reporters are registered
    TestRunInfo info("test run");
    EXPECT_NO_THROW(multiReporter.testRunStarting(info));
}

TEST_F(MultiReporterTest_795, TestRunStartingForwardsToListenersAndReporters_795) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    EXPECT_CALL(*listener, testRunStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter, testRunStarting(_)).Times(Exactly(1));

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    TestRunInfo info("test run");
    multiReporter.testRunStarting(info);
}

// --- testRunEnded ---

TEST_F(MultiReporterTest_795, TestRunEndedForwardsToAllReporters_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, testRunEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testRunEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    Totals totals;
    TestRunStats stats(TestRunInfo("run"), totals, false);
    multiReporter.testRunEnded(stats);
}

TEST_F(MultiReporterTest_795, TestRunEndedWithNoReporters_795) {
    Totals totals;
    TestRunStats stats(TestRunInfo("run"), totals, false);
    EXPECT_NO_THROW(multiReporter.testRunEnded(stats));
}

// --- noMatchingTestCases ---

TEST_F(MultiReporterTest_795, NoMatchingTestCasesForwardsToAll_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.noMatchingTestCases("some spec");
}

TEST_F(MultiReporterTest_795, NoMatchingTestCasesWithNoReporters_795) {
    EXPECT_NO_THROW(multiReporter.noMatchingTestCases("spec"));
}

// --- fatalErrorEncountered ---

TEST_F(MultiReporterTest_795, FatalErrorEncounteredForwardsToAll_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.fatalErrorEncountered("fatal error");
}

// --- reportInvalidTestSpec ---

TEST_F(MultiReporterTest_795, ReportInvalidTestSpecForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    multiReporter.reportInvalidTestSpec("invalid spec");
}

// --- testCaseStarting ---

TEST_F(MultiReporterTest_795, TestCaseStartingForwardsToAll_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, testCaseStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testCaseStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    auto tc = Catch::makeTestCaseInfo("", {"test", "[tag]"}, {""_catch_sr, 0});
    multiReporter.testCaseStarting(*tc);
}

// --- testCaseEnded ---

TEST_F(MultiReporterTest_795, TestCaseEndedForwardsToAll_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testCaseEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    auto tc = Catch::makeTestCaseInfo("", {"test", "[tag]"}, {""_catch_sr, 0});
    Totals totals;
    TestCaseStats stats(*tc, totals, "", "", false);
    multiReporter.testCaseEnded(stats);
}

// --- sectionStarting ---

TEST_F(MultiReporterTest_795, SectionStartingForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, sectionStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    SectionInfo info("", "section name");
    multiReporter.sectionStarting(info);
}

// --- sectionEnded ---

TEST_F(MultiReporterTest_795, SectionEndedForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, sectionEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    Counts assertions;
    SectionInfo sInfo("", "section");
    SectionStats stats(sInfo, assertions, 0.0, false);
    multiReporter.sectionEnded(stats);
}

// --- benchmarkPreparing ---

TEST_F(MultiReporterTest_795, BenchmarkPreparingForwardsToAll_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.benchmarkPreparing("bench");
}

// --- benchmarkFailed ---

TEST_F(MultiReporterTest_795, BenchmarkFailedForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    multiReporter.benchmarkFailed("bench failure");
}

// --- skipTest ---

TEST_F(MultiReporterTest_795, SkipTestForwardsToAll_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, skipTest(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    auto tc = Catch::makeTestCaseInfo("", {"test", "[tag]"}, {""_catch_sr, 0});
    multiReporter.skipTest(*tc);
}

// --- addListener places listeners before reporters ---

TEST_F(MultiReporterTest_795, ListenerCalledBeforeReporter_795) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    {
        InSequence seq;
        EXPECT_CALL(*listener, testRunStarting(_)).Times(1);
        EXPECT_CALL(*reporter, testRunStarting(_)).Times(1);
    }

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    TestRunInfo info("run");
    multiReporter.testRunStarting(info);
}

TEST_F(MultiReporterTest_795, MultipleListenersCalledBeforeReporters_795) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    {
        InSequence seq;
        EXPECT_CALL(*listener1, testRunStarting(_)).Times(1);
        EXPECT_CALL(*listener2, testRunStarting(_)).Times(1);
        EXPECT_CALL(*reporter1, testRunStarting(_)).Times(1);
        EXPECT_CALL(*reporter2, testRunStarting(_)).Times(1);
    }

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    TestRunInfo info("run");
    multiReporter.testRunStarting(info);
}

// --- Listener added after reporter still comes before reporters ---

TEST_F(MultiReporterTest_795, ListenerAddedAfterReporterStillCalledFirst_795) {
    auto* reporter = new MockEventListener();
    auto* listener = new MockEventListener();

    {
        InSequence seq;
        EXPECT_CALL(*listener, testRunStarting(_)).Times(1);
        EXPECT_CALL(*reporter, testRunStarting(_)).Times(1);
    }

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter));
    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));

    TestRunInfo info("run");
    multiReporter.testRunStarting(info);
}

// --- testCasePartialStarting ---

TEST_F(MultiReporterTest_795, TestCasePartialStartingForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, testCasePartialStarting(_, 42)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    auto tc = Catch::makeTestCaseInfo("", {"test", "[tag]"}, {""_catch_sr, 0});
    multiReporter.testCasePartialStarting(*tc, 42);
}

// --- testCasePartialEnded ---

TEST_F(MultiReporterTest_795, TestCasePartialEndedForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, testCasePartialEnded(_, 7)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    auto tc = Catch::makeTestCaseInfo("", {"test", "[tag]"}, {""_catch_sr, 0});
    Totals totals;
    TestCaseStats stats(*tc, totals, "", "", false);
    multiReporter.testCasePartialEnded(stats, 7);
}

// --- Multiple calls ---

TEST_F(MultiReporterTest_795, MultipleCallsAreAllForwarded_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, testRunStarting(_)).Times(Exactly(3));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    TestRunInfo info("run");
    multiReporter.testRunStarting(info);
    multiReporter.testRunStarting(info);
    multiReporter.testRunStarting(info);
}

// --- listReporters ---

TEST_F(MultiReporterTest_795, ListReportersForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, listReporters(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<ReporterDescription> descriptions;
    multiReporter.listReporters(descriptions);
}

// --- listListeners ---

TEST_F(MultiReporterTest_795, ListListenersForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, listListeners(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<ListenerDescription> descriptions;
    multiReporter.listListeners(descriptions);
}

// --- listTests ---

TEST_F(MultiReporterTest_795, ListTestsForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, listTests(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<TestCaseHandle> tests;
    multiReporter.listTests(tests);
}

// --- listTags ---

TEST_F(MultiReporterTest_795, ListTagsForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, listTags(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<TagInfo> tags;
    multiReporter.listTags(tags);
}

// --- assertionStarting ---

TEST_F(MultiReporterTest_795, AssertionStartingForwardsToAll_795) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, assertionStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, assertionStarting(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    AssertionInfo info("", {"", 0}, "", ResultDisposition::Normal);
    multiReporter.assertionStarting(info);
}

// --- assertionEnded ---

TEST_F(MultiReporterTest_795, AssertionEndedForwardsToAll_795) {
    auto* mock = new MockEventListener();

    EXPECT_CALL(*mock, assertionEnded(_)).Times(Exactly(1));

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));

    AssertionInfo aInfo("", {"", 0}, "", ResultDisposition::Normal);
    AssertionResultData data(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(aInfo, std::move(data));
    std::vector<MessageInfo> msgs;
    Counts counts;
    AssertionStats stats(result, msgs, counts);
    multiReporter.assertionEnded(stats);
}
