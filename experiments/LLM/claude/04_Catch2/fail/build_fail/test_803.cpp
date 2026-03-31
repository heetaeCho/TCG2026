#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;
using ::testing::StrictMock;

// Mock IEventListener to verify interactions
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef arg), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo& benchmarkInfo), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>& benchmarkStats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo& testRunInfo), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo& testInfo, uint64_t partNumber), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo& sectionInfo), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo& assertionInfo), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats& assertionStats), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats& sectionStats), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats& testStats, uint64_t partNumber), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats& testCaseStats), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats& testRunStats), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>& descriptions), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>& descriptions), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>& tests), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>& tags), (override));
};

class MultiReporterTest_803 : public ::testing::Test {
protected:
    MultiReporter createMultiReporter() {
        // MultiReporter inherits from IEventListener which takes IConfig const*
        // We pass nullptr as config
        return MultiReporter(nullptr);
    }
};

// Helper to create a mock and keep a raw pointer before moving ownership
struct MockAndPtr {
    MockEventListener* raw;
    Detail::unique_ptr<IEventListener> ptr;
};

static MockAndPtr makeMock() {
    auto* raw = new StrictMock<MockEventListener>();
    MockAndPtr result;
    result.raw = raw;
    result.ptr = Detail::unique_ptr<IEventListener>(raw);
    return result;
}

// ===== testCaseEnded Tests =====

TEST_F(MultiReporterTest_803, TestCaseEndedNoReporters_803) {
    // With no reporters added, testCaseEnded should not crash
    auto multi = createMultiReporter();
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    // Should not crash
    multi.testCaseEnded(stats);
}

TEST_F(MultiReporterTest_803, TestCaseEndedSingleReporter_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    multi.testCaseEnded(stats);
}

TEST_F(MultiReporterTest_803, TestCaseEndedMultipleReporters_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    auto [mock2, ptr2] = makeMock();
    auto [mock3, ptr3] = makeMock();
    
    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*mock2, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*mock3, testCaseEnded(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    multi.addReporter(std::move(ptr2));
    multi.addReporter(std::move(ptr3));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    multi.testCaseEnded(stats);
}

TEST_F(MultiReporterTest_803, TestCaseEndedWithListenerAndReporter_803) {
    auto multi = createMultiReporter();
    
    auto [listener, lPtr] = makeMock();
    auto [reporter, rPtr] = makeMock();
    
    EXPECT_CALL(*listener, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*reporter, testCaseEnded(_)).Times(1);
    
    multi.addListener(std::move(lPtr));
    multi.addReporter(std::move(rPtr));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    multi.testCaseEnded(stats);
}

TEST_F(MultiReporterTest_803, TestCaseEndedCalledMultipleTimes_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(3);
    
    multi.addReporter(std::move(ptr1));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    multi.testCaseEnded(stats);
    multi.testCaseEnded(stats);
    multi.testCaseEnded(stats);
}

// ===== Other forwarding method tests =====

TEST_F(MultiReporterTest_803, NoMatchingTestCasesForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    auto [mock2, ptr2] = makeMock();
    
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    multi.addReporter(std::move(ptr2));
    
    multi.noMatchingTestCases("some spec");
}

TEST_F(MultiReporterTest_803, FatalErrorEncounteredForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    multi.fatalErrorEncountered("fatal error");
}

TEST_F(MultiReporterTest_803, ReportInvalidTestSpecForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    multi.reportInvalidTestSpec("invalid spec");
}

TEST_F(MultiReporterTest_803, TestRunStartingForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testRunStarting(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestRunInfo runInfo("test group");
    multi.testRunStarting(runInfo);
}

TEST_F(MultiReporterTest_803, TestCaseStartingForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testCaseStarting(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    multi.testCaseStarting(testInfo);
}

TEST_F(MultiReporterTest_803, SectionStartingForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, sectionStarting(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    SectionInfo sectionInfo("file", "section");
    multi.sectionStarting(sectionInfo);
}

TEST_F(MultiReporterTest_803, SectionEndedForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, sectionEnded(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    SectionInfo sectionInfo("file", "section");
    Counts counts;
    SectionStats sectionStats(sectionInfo, {}, 0.0, false);
    multi.sectionEnded(sectionStats);
}

TEST_F(MultiReporterTest_803, TestRunEndedForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testRunEnded(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestRunInfo runInfo("test group");
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    multi.testRunEnded(runStats);
}

TEST_F(MultiReporterTest_803, SkipTestForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, skipTest(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    multi.skipTest(testInfo);
}

TEST_F(MultiReporterTest_803, BenchmarkPreparingForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    multi.benchmarkPreparing("bench");
}

TEST_F(MultiReporterTest_803, BenchmarkFailedForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    multi.benchmarkFailed("bench error");
}

TEST_F(MultiReporterTest_803, TestCasePartialStartingForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testCasePartialStarting(_, 42)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    multi.testCasePartialStarting(testInfo, 42);
}

TEST_F(MultiReporterTest_803, TestCasePartialEndedForwarded_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testCasePartialEnded(_, 7)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    multi.testCasePartialEnded(stats, 7);
}

// ===== Listener ordering tests =====

TEST_F(MultiReporterTest_803, ListenersReceiveEventsBeforeReporters_803) {
    auto multi = createMultiReporter();
    
    // We use InSequence to verify listeners are called before reporters
    auto [listener, lPtr] = makeMock();
    auto [reporter, rPtr] = makeMock();
    
    {
        ::testing::InSequence seq;
        EXPECT_CALL(*listener, testCaseEnded(_)).Times(1);
        EXPECT_CALL(*reporter, testCaseEnded(_)).Times(1);
    }
    
    multi.addListener(std::move(lPtr));
    multi.addReporter(std::move(rPtr));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    multi.testCaseEnded(stats);
}

TEST_F(MultiReporterTest_803, MultipleListenersAndMultipleReporters_803) {
    auto multi = createMultiReporter();
    
    auto [listener1, lPtr1] = makeMock();
    auto [listener2, lPtr2] = makeMock();
    auto [reporter1, rPtr1] = makeMock();
    auto [reporter2, rPtr2] = makeMock();
    
    EXPECT_CALL(*listener1, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*listener2, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*reporter1, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*reporter2, testCaseEnded(_)).Times(1);
    
    multi.addListener(std::move(lPtr1));
    multi.addListener(std::move(lPtr2));
    multi.addReporter(std::move(rPtr1));
    multi.addReporter(std::move(rPtr2));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    multi.testCaseEnded(stats);
}

// ===== Edge case: adding listener after reporter =====

TEST_F(MultiReporterTest_803, AddListenerAfterReporter_803) {
    auto multi = createMultiReporter();
    
    auto [reporter, rPtr] = makeMock();
    auto [listener, lPtr] = makeMock();
    
    // Listeners should still be called, regardless of add order
    EXPECT_CALL(*reporter, testCaseEnded(_)).Times(1);
    EXPECT_CALL(*listener, testCaseEnded(_)).Times(1);
    
    multi.addReporter(std::move(rPtr));
    multi.addListener(std::move(lPtr));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);
    
    multi.testCaseEnded(stats);
}

// ===== Testing with aborting flag =====

TEST_F(MultiReporterTest_803, TestCaseEndedWithAbortingTrue_803) {
    auto multi = createMultiReporter();
    
    auto [mock1, ptr1] = makeMock();
    EXPECT_CALL(*mock1, testCaseEnded(_)).Times(1);
    
    multi.addReporter(std::move(ptr1));
    
    TestCaseInfo testInfo("", {"test", "[tag]"}, {});
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string("stdout output"), std::string("stderr output"), true);
    
    multi.testCaseEnded(stats);
}
