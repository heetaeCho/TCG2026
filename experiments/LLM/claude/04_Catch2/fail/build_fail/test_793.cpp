#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_test_run_info.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

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

class MultiReporterTest_793 : public ::testing::Test {
protected:
    MultiReporter createMultiReporter() {
        // MultiReporter inherits from IEventListener which requires IConfig*
        // Passing nullptr as config
        return MultiReporter(nullptr);
    }

    Detail::unique_ptr<IEventListener> makeMockReporter() {
        auto* raw = new MockEventListener();
        mockPtrs_.push_back(raw);
        return Detail::unique_ptr<IEventListener>(raw);
    }

    Detail::unique_ptr<IEventListener> makeMockListener() {
        auto* raw = new MockEventListener();
        mockPtrs_.push_back(raw);
        return Detail::unique_ptr<IEventListener>(raw);
    }

    MockEventListener* lastMock() {
        return mockPtrs_.back();
    }

    MockEventListener* getMock(size_t index) {
        return mockPtrs_[index];
    }

    std::vector<MockEventListener*> mockPtrs_;
};

// Test: benchmarkEnded is forwarded to a single reporter
TEST_F(MultiReporterTest_793, BenchmarkEndedForwardedToSingleReporter_793) {
    auto multi = createMultiReporter();

    auto reporter = makeMockReporter();
    auto* mock = lastMock();
    multi.addReporter(std::move(reporter));

    BenchmarkStats<> stats{};
    EXPECT_CALL(*mock, benchmarkEnded(_)).Times(Exactly(1));

    multi.benchmarkEnded(stats);
}

// Test: benchmarkEnded is forwarded to multiple reporters
TEST_F(MultiReporterTest_793, BenchmarkEndedForwardedToMultipleReporters_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();
    auto r2 = makeMockReporter();
    auto* mock2 = lastMock();

    multi.addReporter(std::move(r1));
    multi.addReporter(std::move(r2));

    BenchmarkStats<> stats{};
    EXPECT_CALL(*mock1, benchmarkEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkEnded(_)).Times(Exactly(1));

    multi.benchmarkEnded(stats);
}

// Test: benchmarkEnded with no reporters does not crash
TEST_F(MultiReporterTest_793, BenchmarkEndedWithNoReportersDoesNotCrash_793) {
    auto multi = createMultiReporter();
    BenchmarkStats<> stats{};
    EXPECT_NO_THROW(multi.benchmarkEnded(stats));
}

// Test: benchmarkEnded forwards to both listeners and reporters
TEST_F(MultiReporterTest_793, BenchmarkEndedForwardedToListenersAndReporters_793) {
    auto multi = createMultiReporter();

    auto listener = makeMockListener();
    auto* mockListener = lastMock();
    auto reporter = makeMockReporter();
    auto* mockReporter = lastMock();

    multi.addListener(std::move(listener));
    multi.addReporter(std::move(reporter));

    BenchmarkStats<> stats{};
    EXPECT_CALL(*mockListener, benchmarkEnded(_)).Times(Exactly(1));
    EXPECT_CALL(*mockReporter, benchmarkEnded(_)).Times(Exactly(1));

    multi.benchmarkEnded(stats);
}

// Test: noMatchingTestCases is forwarded to all reporters
TEST_F(MultiReporterTest_793, NoMatchingTestCasesForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();
    auto r2 = makeMockReporter();
    auto* mock2 = lastMock();

    multi.addReporter(std::move(r1));
    multi.addReporter(std::move(r2));

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));

    multi.noMatchingTestCases("someSpec"_catch_sr);
}

// Test: fatalErrorEncountered is forwarded
TEST_F(MultiReporterTest_793, FatalErrorEncounteredForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(Exactly(1));

    multi.fatalErrorEncountered("some error"_catch_sr);
}

// Test: reportInvalidTestSpec is forwarded
TEST_F(MultiReporterTest_793, ReportInvalidTestSpecForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(Exactly(1));

    multi.reportInvalidTestSpec("invalid"_catch_sr);
}

// Test: benchmarkPreparing is forwarded
TEST_F(MultiReporterTest_793, BenchmarkPreparingForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(Exactly(1));

    multi.benchmarkPreparing("bench"_catch_sr);
}

// Test: benchmarkStarting is forwarded
TEST_F(MultiReporterTest_793, BenchmarkStartingForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    BenchmarkInfo info{"benchName", 1.0, 100, 10, 1000, 500};
    EXPECT_CALL(*mock1, benchmarkStarting(_)).Times(Exactly(1));

    multi.benchmarkStarting(info);
}

// Test: benchmarkFailed is forwarded
TEST_F(MultiReporterTest_793, BenchmarkFailedForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(Exactly(1));

    multi.benchmarkFailed("error"_catch_sr);
}

// Test: testRunStarting forwarded to multiple
TEST_F(MultiReporterTest_793, TestRunStartingForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();
    auto r2 = makeMockReporter();
    auto* mock2 = lastMock();

    multi.addReporter(std::move(r1));
    multi.addReporter(std::move(r2));

    TestRunInfo runInfo("test group");
    EXPECT_CALL(*mock1, testRunStarting(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(Exactly(1));

    multi.testRunStarting(runInfo);
}

// Test: skipTest is forwarded
TEST_F(MultiReporterTest_793, SkipTestForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    // We need a TestCaseInfo - create a minimal one
    // Since we treat as black box, just verify forwarding
    EXPECT_CALL(*mock1, skipTest(_)).Times(Exactly(1));

    // Create a minimal TestCaseInfo
    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_catch_sr, {"test", "[tag]"}, {""_catch_sr, 0});
    multi.skipTest(*testCaseInfo);
}

// Test: addListener followed by addReporter - listener events come first
TEST_F(MultiReporterTest_793, ListenerCalledBeforeReporter_793) {
    auto multi = createMultiReporter();

    auto listener = makeMockListener();
    auto* mockListener = lastMock();
    auto reporter = makeMockReporter();
    auto* mockReporter = lastMock();

    multi.addListener(std::move(listener));
    multi.addReporter(std::move(reporter));

    ::testing::InSequence seq;
    EXPECT_CALL(*mockListener, benchmarkEnded(_)).Times(1);
    EXPECT_CALL(*mockReporter, benchmarkEnded(_)).Times(1);

    BenchmarkStats<> stats{};
    multi.benchmarkEnded(stats);
}

// Test: Multiple listeners and reporters, all called
TEST_F(MultiReporterTest_793, MultipleListenersAndReportersAllCalled_793) {
    auto multi = createMultiReporter();

    auto l1 = makeMockListener();
    auto* mockL1 = lastMock();
    auto l2 = makeMockListener();
    auto* mockL2 = lastMock();
    auto r1 = makeMockReporter();
    auto* mockR1 = lastMock();
    auto r2 = makeMockReporter();
    auto* mockR2 = lastMock();

    multi.addListener(std::move(l1));
    multi.addListener(std::move(l2));
    multi.addReporter(std::move(r1));
    multi.addReporter(std::move(r2));

    EXPECT_CALL(*mockL1, benchmarkEnded(_)).Times(1);
    EXPECT_CALL(*mockL2, benchmarkEnded(_)).Times(1);
    EXPECT_CALL(*mockR1, benchmarkEnded(_)).Times(1);
    EXPECT_CALL(*mockR2, benchmarkEnded(_)).Times(1);

    BenchmarkStats<> stats{};
    multi.benchmarkEnded(stats);
}

// Test: Calling benchmarkEnded multiple times
TEST_F(MultiReporterTest_793, BenchmarkEndedCalledMultipleTimes_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    BenchmarkStats<> stats{};
    EXPECT_CALL(*mock1, benchmarkEnded(_)).Times(Exactly(3));

    multi.benchmarkEnded(stats);
    multi.benchmarkEnded(stats);
    multi.benchmarkEnded(stats);
}

// Test: listReporters is forwarded
TEST_F(MultiReporterTest_793, ListReportersForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    std::vector<ReporterDescription> descriptions;
    EXPECT_CALL(*mock1, listReporters(_)).Times(Exactly(1));

    multi.listReporters(descriptions);
}

// Test: listListeners is forwarded
TEST_F(MultiReporterTest_793, ListListenersForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    std::vector<ListenerDescription> descriptions;
    EXPECT_CALL(*mock1, listListeners(_)).Times(Exactly(1));

    multi.listListeners(descriptions);
}

// Test: listTests is forwarded
TEST_F(MultiReporterTest_793, ListTestsForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    std::vector<TestCaseHandle> tests;
    EXPECT_CALL(*mock1, listTests(_)).Times(Exactly(1));

    multi.listTests(tests);
}

// Test: listTags is forwarded
TEST_F(MultiReporterTest_793, ListTagsForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    std::vector<TagInfo> tags;
    EXPECT_CALL(*mock1, listTags(_)).Times(Exactly(1));

    multi.listTags(tags);
}

// Test: assertionStarting is forwarded
TEST_F(MultiReporterTest_793, AssertionStartingForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    EXPECT_CALL(*mock1, assertionStarting(_)).Times(Exactly(1));

    AssertionInfo info{"test", {"file", 1}, "expr", ResultDisposition::Normal};
    multi.assertionStarting(info);
}

// Test: sectionStarting is forwarded
TEST_F(MultiReporterTest_793, SectionStartingForwarded_793) {
    auto multi = createMultiReporter();

    auto r1 = makeMockReporter();
    auto* mock1 = lastMock();

    multi.addReporter(std::move(r1));

    EXPECT_CALL(*mock1, sectionStarting(_)).Times(Exactly(1));

    SectionInfo info{{"file", 1}, "section name"};
    multi.sectionStarting(info);
}
