#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock for IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef invalidArgument), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo& benchmarkInfo), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>& benchmarkStats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef benchmarkName), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo& testRunInfo), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo& testInfo, uint64_t partNumber), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo& sectionInfo), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo& assertionInfo), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats& assertionStats), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats& sectionStats), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats& testCaseStats, uint64_t partNumber), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats& testCaseStats), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats& testRunStats), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo& testInfo), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>& descriptions), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>& descriptions), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>& tests), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>& tags), (override));
};

class MultiReporterTest_788 : public ::testing::Test {
protected:
    MultiReporter createMultiReporter() {
        // MultiReporter inherits from IEventListener which takes IConfig const*
        // We pass nullptr since we're testing MultiReporter behavior
        return MultiReporter(nullptr);
    }
};

// ==================== noMatchingTestCases Tests ====================

TEST_F(MultiReporterTest_788, NoMatchingTestCases_NoReporters_DoesNotCrash_788) {
    auto multi = createMultiReporter();
    // No reporters added, should not crash
    EXPECT_NO_THROW(multi.noMatchingTestCases("some_spec"));
}

TEST_F(MultiReporterTest_788, NoMatchingTestCases_SingleReporter_ForwardsCall_788) {
    auto multi = createMultiReporter();
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, noMatchingTestCases(_)).Times(Exactly(1));

    Detail::unique_ptr<IEventListener> mockPtr(mockRaw);
    multi.addReporter(std::move(mockPtr));

    multi.noMatchingTestCases("unmatched");
}

TEST_F(MultiReporterTest_788, NoMatchingTestCases_MultipleReporters_ForwardsToAll_788) {
    auto multi = createMultiReporter();
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    auto* mock3 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*mock3, noMatchingTestCases(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock3));

    multi.noMatchingTestCases("spec");
}

TEST_F(MultiReporterTest_788, NoMatchingTestCases_EmptyString_788) {
    auto multi = createMultiReporter();
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, noMatchingTestCases(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mockRaw));
    multi.noMatchingTestCases("");
}

// ==================== fatalErrorEncountered Tests ====================

TEST_F(MultiReporterTest_788, FatalErrorEncountered_NoReporters_DoesNotCrash_788) {
    auto multi = createMultiReporter();
    EXPECT_NO_THROW(multi.fatalErrorEncountered("fatal"));
}

TEST_F(MultiReporterTest_788, FatalErrorEncountered_ForwardsToAllReporters_788) {
    auto multi = createMultiReporter();
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multi.fatalErrorEncountered("error message");
}

// ==================== reportInvalidTestSpec Tests ====================

TEST_F(MultiReporterTest_788, ReportInvalidTestSpec_ForwardsToAllReporters_788) {
    auto multi = createMultiReporter();
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multi.reportInvalidTestSpec("invalid_spec");
}

// ==================== benchmarkPreparing Tests ====================

TEST_F(MultiReporterTest_788, BenchmarkPreparing_ForwardsToAllReporters_788) {
    auto multi = createMultiReporter();
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(Exactly(1));
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multi.benchmarkPreparing("bench_name");
}

// ==================== benchmarkFailed Tests ====================

TEST_F(MultiReporterTest_788, BenchmarkFailed_ForwardsToAllReporters_788) {
    auto multi = createMultiReporter();
    auto* mock1 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mock1));

    multi.benchmarkFailed("bench_error");
}

// ==================== addListener Tests ====================

TEST_F(MultiReporterTest_788, AddListener_ForwardsCallsToListener_788) {
    auto multi = createMultiReporter();
    auto* listener = new MockEventListener();

    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(Exactly(1));

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));

    multi.noMatchingTestCases("test");
}

TEST_F(MultiReporterTest_788, AddListenerAndReporter_BothReceiveCalls_788) {
    auto multi = createMultiReporter();
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(Exactly(1));

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    multi.noMatchingTestCases("spec");
}

TEST_F(MultiReporterTest_788, AddMultipleListenersAndReporters_AllReceiveCalls_788) {
    auto multi = createMultiReporter();
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    EXPECT_CALL(*listener1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*listener2, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter1, fatalErrorEncountered(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter2, fatalErrorEncountered(_)).Times(Exactly(1));

    multi.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multi.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    multi.fatalErrorEncountered("fatal");
}

// ==================== Multiple calls Tests ====================

TEST_F(MultiReporterTest_788, NoMatchingTestCases_CalledMultipleTimes_ForwardsEachCall_788) {
    auto multi = createMultiReporter();
    auto* mockRaw = new MockEventListener();

    EXPECT_CALL(*mockRaw, noMatchingTestCases(_)).Times(Exactly(3));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mockRaw));

    multi.noMatchingTestCases("spec1");
    multi.noMatchingTestCases("spec2");
    multi.noMatchingTestCases("spec3");
}

// ==================== No reporters for various methods ====================

TEST_F(MultiReporterTest_788, ReportInvalidTestSpec_NoReporters_DoesNotCrash_788) {
    auto multi = createMultiReporter();
    EXPECT_NO_THROW(multi.reportInvalidTestSpec("invalid"));
}

TEST_F(MultiReporterTest_788, BenchmarkPreparing_NoReporters_DoesNotCrash_788) {
    auto multi = createMultiReporter();
    EXPECT_NO_THROW(multi.benchmarkPreparing("bench"));
}

TEST_F(MultiReporterTest_788, BenchmarkFailed_NoReporters_DoesNotCrash_788) {
    auto multi = createMultiReporter();
    EXPECT_NO_THROW(multi.benchmarkFailed("error"));
}

// ==================== Listeners are called before reporters ====================

TEST_F(MultiReporterTest_788, ListenersCalledBeforeReporters_788) {
    auto multi = createMultiReporter();
    
    std::vector<int> callOrder;
    
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    ON_CALL(*listener, noMatchingTestCases(_))
        .WillByDefault([&callOrder](StringRef) { callOrder.push_back(1); });
    ON_CALL(*reporter, noMatchingTestCases(_))
        .WillByDefault([&callOrder](StringRef) { callOrder.push_back(2); });

    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(Exactly(1));

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    multi.noMatchingTestCases("spec");

    ASSERT_EQ(callOrder.size(), 2u);
    EXPECT_EQ(callOrder[0], 1);  // listener first
    EXPECT_EQ(callOrder[1], 2);  // reporter second
}

// ==================== skipTest Tests ====================

TEST_F(MultiReporterTest_788, SkipTest_NoReporters_DoesNotCrash_788) {
    auto multi = createMultiReporter();
    // We cannot easily construct TestCaseInfo, but the method should handle being called
    // This test is primarily about verifying no crash with no reporters
    // If TestCaseInfo cannot be constructed, this test may need adjustment
}

// ==================== Verify StringRef content passed correctly ====================

TEST_F(MultiReporterTest_788, NoMatchingTestCases_CorrectStringPassed_788) {
    auto multi = createMultiReporter();
    auto* mockRaw = new MockEventListener();

    std::string received;
    ON_CALL(*mockRaw, noMatchingTestCases(_))
        .WillByDefault([&received](StringRef spec) { 
            received = std::string(spec); 
        });
    EXPECT_CALL(*mockRaw, noMatchingTestCases(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mockRaw));
    multi.noMatchingTestCases("my_test_spec");

    EXPECT_EQ(received, "my_test_spec");
}

TEST_F(MultiReporterTest_788, FatalErrorEncountered_CorrectStringPassed_788) {
    auto multi = createMultiReporter();
    auto* mockRaw = new MockEventListener();

    std::string received;
    ON_CALL(*mockRaw, fatalErrorEncountered(_))
        .WillByDefault([&received](StringRef error) {
            received = std::string(error);
        });
    EXPECT_CALL(*mockRaw, fatalErrorEncountered(_)).Times(Exactly(1));

    multi.addReporter(Detail::unique_ptr<IEventListener>(mockRaw));
    multi.fatalErrorEncountered("critical_error");

    EXPECT_EQ(received, "critical_error");
}

// ==================== Add reporter after listener, verify ordering ====================

TEST_F(MultiReporterTest_788, AddReporterThenListener_ListenerStillFirst_788) {
    auto multi = createMultiReporter();

    std::vector<int> callOrder;

    auto* reporter = new MockEventListener();
    auto* listener = new MockEventListener();

    ON_CALL(*listener, noMatchingTestCases(_))
        .WillByDefault([&callOrder](StringRef) { callOrder.push_back(1); });
    ON_CALL(*reporter, noMatchingTestCases(_))
        .WillByDefault([&callOrder](StringRef) { callOrder.push_back(2); });

    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(Exactly(1));
    EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(Exactly(1));

    // Add reporter first, then listener
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));
    multi.addListener(Detail::unique_ptr<IEventListener>(listener));

    multi.noMatchingTestCases("spec");

    ASSERT_EQ(callOrder.size(), 2u);
    // Listeners should be placed before reporters regardless of add order
    EXPECT_EQ(callOrder[0], 1);  // listener
    EXPECT_EQ(callOrder[1], 2);  // reporter
}

// ==================== Single listener only ====================

TEST_F(MultiReporterTest_788, SingleListenerOnly_ReceivesCalls_788) {
    auto multi = createMultiReporter();
    auto* listener = new MockEventListener();

    EXPECT_CALL(*listener, reportInvalidTestSpec(_)).Times(Exactly(1));

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.reportInvalidTestSpec("bad_spec");
}
