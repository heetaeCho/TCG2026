#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_config.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock implementation of IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}
    explicit MockEventListener(IConfig const* config) : IEventListener(config) {}

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

class MultiReporterTest_809 : public ::testing::Test {
protected:
    void SetUp() override {
        multiReporter = Detail::make_unique<MultiReporter>(nullptr);
    }

    Detail::unique_ptr<MultiReporter> multiReporter;
};

// ============================================================
// listTags tests
// ============================================================

TEST_F(MultiReporterTest_809, ListTagsWithNoReportersDoesNotCrash_809) {
    std::vector<TagInfo> tags;
    // Should not crash when no reporters are added
    multiReporter->listTags(tags);
}

TEST_F(MultiReporterTest_809, ListTagsForwardsToSingleReporter_809) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listTags(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

TEST_F(MultiReporterTest_809, ListTagsForwardsToMultipleReporters_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listTags(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, listTags(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

TEST_F(MultiReporterTest_809, ListTagsForwardsToListenersAndReporters_809) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();
    EXPECT_CALL(*listener, listTags(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter, listTags(_)).Times(Exactly(1));

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter));

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

// ============================================================
// noMatchingTestCases tests
// ============================================================

TEST_F(MultiReporterTest_809, NoMatchingTestCasesForwardsToAllReporters_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->noMatchingTestCases("test_spec"_catch_sr);
}

TEST_F(MultiReporterTest_809, NoMatchingTestCasesWithNoReporters_809) {
    // Should not crash
    multiReporter->noMatchingTestCases("test_spec"_catch_sr);
}

// ============================================================
// fatalErrorEncountered tests
// ============================================================

TEST_F(MultiReporterTest_809, FatalErrorEncounteredForwardsToAllReporters_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->fatalErrorEncountered("fatal error"_catch_sr);
}

// ============================================================
// reportInvalidTestSpec tests
// ============================================================

TEST_F(MultiReporterTest_809, ReportInvalidTestSpecForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->reportInvalidTestSpec("bad spec"_catch_sr);
}

// ============================================================
// benchmarkPreparing tests
// ============================================================

TEST_F(MultiReporterTest_809, BenchmarkPreparingForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->benchmarkPreparing("bench"_catch_sr);
}

// ============================================================
// benchmarkFailed tests
// ============================================================

TEST_F(MultiReporterTest_809, BenchmarkFailedForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkFailed(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter->benchmarkFailed("bench error"_catch_sr);
}

// ============================================================
// testRunStarting tests
// ============================================================

TEST_F(MultiReporterTest_809, TestRunStartingForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, testRunStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    TestRunInfo info("test run");
    multiReporter->testRunStarting(info);
}

// ============================================================
// skipTest tests
// ============================================================

TEST_F(MultiReporterTest_809, SkipTestForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, skipTest(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, skipTest(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    auto testCaseInfo = Catch::makeTestCaseInfo(
        "className", {"test", "[tag]"}, {""_catch_sr, 0});
    multiReporter->skipTest(*testCaseInfo);
}

// ============================================================
// listReporters tests
// ============================================================

TEST_F(MultiReporterTest_809, ListReportersForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listReporters(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, listReporters(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<ReporterDescription> descriptions;
    multiReporter->listReporters(descriptions);
}

// ============================================================
// listListeners tests
// ============================================================

TEST_F(MultiReporterTest_809, ListListenersForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listListeners(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, listListeners(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<ListenerDescription> descriptions;
    multiReporter->listListeners(descriptions);
}

// ============================================================
// listTests tests
// ============================================================

TEST_F(MultiReporterTest_809, ListTestsForwardsToAll_809) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    EXPECT_CALL(*mock1, listTests(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, listTests(_)).Times(Exactly(1));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock2));

    std::vector<TestCaseHandle> tests;
    multiReporter->listTests(tests);
}

// ============================================================
// addListener and addReporter ordering tests
// ============================================================

TEST_F(MultiReporterTest_809, ListenersAndReportersBothReceiveEvents_809) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    EXPECT_CALL(*listener1, listTags(_)).Times(Exactly(1));
    EXPECT_CALL(*listener2, listTags(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter1, listTags(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter2, listTags(_)).Times(Exactly(1));

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

// ============================================================
// Multiple calls
// ============================================================

TEST_F(MultiReporterTest_809, MultipleCallsForwardEachTime_809) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, listTags(_)).Times(Exactly(3));

    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
    multiReporter->listTags(tags);
    multiReporter->listTags(tags);
}

// ============================================================
// Empty reporter list for various methods
// ============================================================

TEST_F(MultiReporterTest_809, NoReportersDoesNotCrashForAnyMethod_809) {
    // None of these should crash with no reporters
    multiReporter->noMatchingTestCases("spec"_catch_sr);
    multiReporter->fatalErrorEncountered("error"_catch_sr);
    multiReporter->reportInvalidTestSpec("arg"_catch_sr);
    multiReporter->benchmarkPreparing("bench"_catch_sr);
    multiReporter->benchmarkFailed("error"_catch_sr);

    std::vector<ReporterDescription> repDescs;
    multiReporter->listReporters(repDescs);

    std::vector<ListenerDescription> listDescs;
    multiReporter->listListeners(listDescs);

    std::vector<TestCaseHandle> tests;
    multiReporter->listTests(tests);

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

// ============================================================
// Single listener, no reporter
// ============================================================

TEST_F(MultiReporterTest_809, SingleListenerReceivesEvents_809) {
    auto* listener = new MockEventListener();
    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*listener, fatalErrorEncountered(_)).Times(Exactly(1));

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener));

    multiReporter->noMatchingTestCases("spec"_catch_sr);
    multiReporter->fatalErrorEncountered("error"_catch_sr);
}

// ============================================================
// Many reporters stress test
// ============================================================

TEST_F(MultiReporterTest_809, ManyReportersAllReceiveEvents_809) {
    constexpr int NUM_REPORTERS = 10;
    std::vector<MockEventListener*> mocks;
    for (int i = 0; i < NUM_REPORTERS; ++i) {
        auto* mock = new MockEventListener();
        EXPECT_CALL(*mock, listTags(_)).Times(Exactly(1));
        mocks.push_back(mock);
        multiReporter->addReporter(Detail::unique_ptr<IEventListener>(mock));
    }

    std::vector<TagInfo> tags;
    multiReporter->listTags(tags);
}

// ============================================================
// Interleaved listeners and reporters
// ============================================================

TEST_F(MultiReporterTest_809, InterleavedListenersAndReporters_809) {
    auto* listener1 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    EXPECT_CALL(*listener1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*listener2, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter2, noMatchingTestCases(_)).Times(Exactly(1));

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    multiReporter->noMatchingTestCases("spec"_catch_sr);
}
