#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Eq;

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

class MultiReporterTest_794 : public ::testing::Test {
protected:
    MultiReporter multiReporter{nullptr};
};

// ==================== benchmarkFailed tests ====================

TEST_F(MultiReporterTest_794, BenchmarkFailedNoReporters_794) {
    // Should not crash when there are no reporters
    EXPECT_NO_THROW(multiReporter.benchmarkFailed("some error"));
}

TEST_F(MultiReporterTest_794, BenchmarkFailedSingleReporter_794) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter.benchmarkFailed("benchmark error");
}

TEST_F(MultiReporterTest_794, BenchmarkFailedMultipleReporters_794) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    auto* mock3 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*mock3, benchmarkFailed(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock3));

    multiReporter.benchmarkFailed("benchmark error");
}

TEST_F(MultiReporterTest_794, BenchmarkFailedWithEmptyErrorString_794) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter.benchmarkFailed(StringRef());
}

TEST_F(MultiReporterTest_794, BenchmarkFailedWithListener_794) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    EXPECT_CALL(*listener, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*reporter, benchmarkFailed(_)).Times(1);

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    multiReporter.benchmarkFailed("error");
}

TEST_F(MultiReporterTest_794, BenchmarkFailedCalledMultipleTimes_794) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(3);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter.benchmarkFailed("error1");
    multiReporter.benchmarkFailed("error2");
    multiReporter.benchmarkFailed("error3");
}

// ==================== noMatchingTestCases tests ====================

TEST_F(MultiReporterTest_794, NoMatchingTestCasesForwardsToAllReporters_794) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.noMatchingTestCases("some spec");
}

TEST_F(MultiReporterTest_794, NoMatchingTestCasesNoReporters_794) {
    EXPECT_NO_THROW(multiReporter.noMatchingTestCases("spec"));
}

// ==================== fatalErrorEncountered tests ====================

TEST_F(MultiReporterTest_794, FatalErrorEncounteredForwardsToAll_794) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.fatalErrorEncountered("fatal!");
}

TEST_F(MultiReporterTest_794, FatalErrorEncounteredNoReporters_794) {
    EXPECT_NO_THROW(multiReporter.fatalErrorEncountered("fatal!"));
}

// ==================== reportInvalidTestSpec tests ====================

TEST_F(MultiReporterTest_794, ReportInvalidTestSpecForwardsToAll_794) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(1);
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.reportInvalidTestSpec("bad spec");
}

// ==================== benchmarkPreparing tests ====================

TEST_F(MultiReporterTest_794, BenchmarkPreparingForwardsToAll_794) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkPreparing(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.benchmarkPreparing("my benchmark");
}

TEST_F(MultiReporterTest_794, BenchmarkPreparingNoReporters_794) {
    EXPECT_NO_THROW(multiReporter.benchmarkPreparing("my benchmark"));
}

// ==================== addListener and addReporter ordering ====================

TEST_F(MultiReporterTest_794, ListenersAndReportersBothReceiveEvents_794) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter1 = new MockEventListener();
    auto* reporter2 = new MockEventListener();

    EXPECT_CALL(*listener1, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*listener2, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*reporter1, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*reporter2, benchmarkFailed(_)).Times(1);

    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multiReporter.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    multiReporter.benchmarkFailed("error");
}

// ==================== skipTest tests ====================

TEST_F(MultiReporterTest_794, SkipTestForwardsToAll_794) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, skipTest(_)).Times(1);
    EXPECT_CALL(*mock2, skipTest(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    // We need a TestCaseInfo to pass; create a minimal one
    // This depends on the actual constructor available
    TestCaseInfo info("", {"", 0}, "", "", SourceLineInfo("", 0), {}, {});
    multiReporter.skipTest(info);
}

TEST_F(MultiReporterTest_794, SkipTestNoReporters_794) {
    TestCaseInfo info("", {"", 0}, "", "", SourceLineInfo("", 0), {}, {});
    EXPECT_NO_THROW(multiReporter.skipTest(info));
}

// ==================== Multiple method calls with multiple reporters ====================

TEST_F(MultiReporterTest_794, MultipleMethodCallsOnMultipleReporters_794) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(2);
    EXPECT_CALL(*mock2, benchmarkFailed(_)).Times(2);
    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock1));
    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock2));

    multiReporter.benchmarkFailed("err1");
    multiReporter.fatalErrorEncountered("fatal");
    multiReporter.noMatchingTestCases("spec");
    multiReporter.benchmarkFailed("err2");
}

// ==================== benchmarkFailed with long error string ====================

TEST_F(MultiReporterTest_794, BenchmarkFailedWithLongErrorString_794) {
    auto* mock = new MockEventListener();
    std::string longError(10000, 'x');
    EXPECT_CALL(*mock, benchmarkFailed(_)).Times(1);

    multiReporter.addReporter(Detail::unique_ptr<IEventListener>(mock));
    multiReporter.benchmarkFailed(StringRef(longError));
}
