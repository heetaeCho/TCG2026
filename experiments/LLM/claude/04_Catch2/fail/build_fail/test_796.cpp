#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_reporter_registrars.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock for IEventListener
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

class MultiReporterTest_796 : public ::testing::Test {
protected:
    void SetUp() override {
        multiReporter = Detail::make_unique<MultiReporter>(nullptr);
    }

    Detail::unique_ptr<MultiReporter> multiReporter;
};

// Helper to create a mock and keep a raw pointer while moving ownership
struct MockHolder {
    MockEventListener* raw;
    Detail::unique_ptr<IEventListener> ptr;

    MockHolder() {
        raw = new MockEventListener();
        ptr = Detail::unique_ptr<IEventListener>(raw);
    }
};

// ===== Normal operation tests =====

TEST_F(MultiReporterTest_796, TestCaseStartingForwardsToSingleReporter_796) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCaseStarting(_)).Times(1);
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->testCaseStarting(info);
}

TEST_F(MultiReporterTest_796, TestCaseStartingForwardsToMultipleReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testCaseStarting(_)).Times(1);
    EXPECT_CALL(*mock2, testCaseStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->testCaseStarting(info);
}

TEST_F(MultiReporterTest_796, TestRunStartingForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testRunStarting(_)).Times(1);
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    TestRunInfo runInfo("test run");
    multiReporter->testRunStarting(runInfo);
}

TEST_F(MultiReporterTest_796, TestCaseEndedForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*mock2, testCaseEnded(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    Totals totals;
    TestCaseStats stats(info, totals, "", "", false);
    multiReporter->testCaseEnded(stats);
}

TEST_F(MultiReporterTest_796, TestRunEndedForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testRunEnded(_)).Times(1);
    EXPECT_CALL(*mock2, testRunEnded(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    TestRunInfo runInfo("test run");
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    multiReporter->testRunEnded(runStats);
}

TEST_F(MultiReporterTest_796, SectionStartingForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, sectionStarting(_)).Times(1);
    EXPECT_CALL(*mock2, sectionStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    SectionInfo sectionInfo("file.cpp", 1, "section");
    multiReporter->sectionStarting(sectionInfo);
}

TEST_F(MultiReporterTest_796, SectionEndedForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, sectionEnded(_)).Times(1);
    EXPECT_CALL(*mock2, sectionEnded(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    SectionInfo sectionInfo("file.cpp", 1, "section");
    Counts assertions;
    double duration = 0.0;
    SectionStats sectionStats(sectionInfo, assertions, duration, false);
    multiReporter->sectionEnded(sectionStats);
}

TEST_F(MultiReporterTest_796, AssertionStartingForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, assertionStarting(_)).Times(1);
    EXPECT_CALL(*mock2, assertionStarting(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    SourceLineInfo lineInfo("file.cpp", 1);
    AssertionInfo assertionInfo("macro", lineInfo, "", ResultDisposition::Normal);
    multiReporter->assertionStarting(assertionInfo);
}

TEST_F(MultiReporterTest_796, NoMatchingTestCasesForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->noMatchingTestCases("unmatched");
}

TEST_F(MultiReporterTest_796, FatalErrorEncounteredForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->fatalErrorEncountered("fatal error");
}

TEST_F(MultiReporterTest_796, ReportInvalidTestSpecForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(1);
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->reportInvalidTestSpec("invalid");
}

TEST_F(MultiReporterTest_796, SkipTestForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, skipTest(_)).Times(1);
    EXPECT_CALL(*mock2, skipTest(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->skipTest(info);
}

TEST_F(MultiReporterTest_796, BenchmarkPreparingForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->benchmarkPreparing("bench");
}

TEST_F(MultiReporterTest_796, BenchmarkFailedForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkFailed(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->benchmarkFailed("error");
}

TEST_F(MultiReporterTest_796, TestCasePartialStartingForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testCasePartialStarting(_, 42)).Times(1);
    EXPECT_CALL(*mock2, testCasePartialStarting(_, 42)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->testCasePartialStarting(info, 42);
}

TEST_F(MultiReporterTest_796, TestCasePartialEndedForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testCasePartialEnded(_, 7)).Times(1);
    EXPECT_CALL(*mock2, testCasePartialEnded(_, 7)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    Totals totals;
    TestCaseStats stats(info, totals, "", "", false);
    multiReporter->testCasePartialEnded(stats, 7);
}

// ===== Boundary condition tests =====

TEST_F(MultiReporterTest_796, NoReportersDoesNotCrashOnTestCaseStarting_796) {
    // No reporters added — should not crash
    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    EXPECT_NO_THROW(multiReporter->testCaseStarting(info));
}

TEST_F(MultiReporterTest_796, NoReportersDoesNotCrashOnTestRunStarting_796) {
    TestRunInfo runInfo("test run");
    EXPECT_NO_THROW(multiReporter->testRunStarting(runInfo));
}

TEST_F(MultiReporterTest_796, NoReportersDoesNotCrashOnNoMatchingTestCases_796) {
    EXPECT_NO_THROW(multiReporter->noMatchingTestCases("spec"));
}

TEST_F(MultiReporterTest_796, NoReportersDoesNotCrashOnFatalError_796) {
    EXPECT_NO_THROW(multiReporter->fatalErrorEncountered("error"));
}

TEST_F(MultiReporterTest_796, SingleReporterReceivesAllEvents_796) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, testCaseStarting(_)).Times(3);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->testCaseStarting(info);
    multiReporter->testCaseStarting(info);
    multiReporter->testCaseStarting(info);
}

// ===== Listener + Reporter ordering tests =====

TEST_F(MultiReporterTest_796, ListenerAndReporterBothReceiveEvents_796) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();
    EXPECT_CALL(*listener, testCaseStarting(_)).Times(1);
    EXPECT_CALL(*reporter, testCaseStarting(_)).Times(1);

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->testCaseStarting(info);
}

TEST_F(MultiReporterTest_796, MultipleListenersAndReportersAllReceiveEvents_796) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    EXPECT_CALL(*listener1, testCaseStarting(_)).Times(1);
    EXPECT_CALL(*listener2, testCaseStarting(_)).Times(1);
    EXPECT_CALL(*reporter1, testCaseStarting(_)).Times(1);
    EXPECT_CALL(*reporter2, testCaseStarting(_)).Times(1);

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->testCaseStarting(info);
}

// ===== List methods tests =====

TEST_F(MultiReporterTest_796, ListReportersForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listReporters(_)).Times(1);
    EXPECT_CALL(*mock2, listReporters(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<ReporterDescription> descriptions;
    multiReporter->listReporters(descriptions);
}

TEST_F(MultiReporterTest_796, ListTestsForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listTests(_)).Times(1);
    EXPECT_CALL(*mock2, listTests(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<TestCaseHandle> tests;
    multiReporter->listTests(tests);
}

TEST_F(MultiReporterTest_796, ListTagsForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listTags(_)).Times(1);
    EXPECT_CALL(*mock2, listTags(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

TEST_F(MultiReporterTest_796, ListListenersForwardsToAllReporters_796) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listListeners(_)).Times(1);
    EXPECT_CALL(*mock2, listListeners(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<ListenerDescription> descriptions;
    multiReporter->listListeners(descriptions);
}

// ===== Empty string edge cases =====

TEST_F(MultiReporterTest_796, NoMatchingTestCasesWithEmptyString_796) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, noMatchingTestCases(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->noMatchingTestCases("");
}

TEST_F(MultiReporterTest_796, FatalErrorWithEmptyString_796) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, fatalErrorEncountered(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->fatalErrorEncountered("");
}

TEST_F(MultiReporterTest_796, ReportInvalidTestSpecWithEmptyString_796) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(_)).Times(1);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter->reportInvalidTestSpec("");
}

// ===== Many reporters stress test =====

TEST_F(MultiReporterTest_796, ManyReportersAllReceiveTestCaseStarting_796) {
    constexpr int NUM_REPORTERS = 10;
    std::vector<MockEventListener*> mocks;

    for (int i = 0; i < NUM_REPORTERS; ++i) {
        auto* mock = new MockEventListener();
        EXPECT_CALL(*mock, testCaseStarting(_)).Times(1);
        mocks.push_back(mock);
        multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    }

    NameAndTags nameAndTags("test", "[tag]");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo info("", nameAndTags, lineInfo);
    multiReporter->testCaseStarting(info);
}

// ===== Verify no calls when no event dispatched =====

TEST_F(MultiReporterTest_796, ReporterNotCalledWithoutEvent_796) {
    auto* mock = new MockEventListener();
    // Expect no calls at all
    EXPECT_CALL(*mock, testCaseStarting(_)).Times(0);
    EXPECT_CALL(*mock, testRunStarting(_)).Times(0);
    EXPECT_CALL(*mock, noMatchingTestCases(_)).Times(0);

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    // Don't dispatch any events
}
