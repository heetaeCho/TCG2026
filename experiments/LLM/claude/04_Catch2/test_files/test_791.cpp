#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"

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

class MultiReporterTest_791 : public ::testing::Test {
protected:
    void SetUp() override {
        multiReporter = Detail::make_unique<MultiReporter>(nullptr);
    }

    Detail::unique_ptr<MultiReporter> multiReporter;
};

// Test that benchmarkPreparing is forwarded to no listeners when none are added
TEST_F(MultiReporterTest_791, BenchmarkPreparingNoListeners_791) {
    // Should not crash with no reporters
    EXPECT_NO_THROW(multiReporter->benchmarkPreparing("test_benchmark"));
}

// Test that benchmarkPreparing is forwarded to a single reporter
TEST_F(MultiReporterTest_791, BenchmarkPreparingSingleReporter_791) {
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, benchmarkPreparing(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock(mockRaw);
    multiReporter->addReporter(std::move(mock));

    multiReporter->benchmarkPreparing("my_benchmark");
}

// Test that benchmarkPreparing is forwarded to multiple reporters
TEST_F(MultiReporterTest_791, BenchmarkPreparingMultipleReporters_791) {
    auto* mock1Raw = new MockEventListener();
    auto* mock2Raw = new MockEventListener();
    EXPECT_CALL(*mock1Raw, benchmarkPreparing(_)).Times(1);
    EXPECT_CALL(*mock2Raw, benchmarkPreparing(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock1(mock1Raw);
    Detail::unique_ptr<IEventListener> mock2(mock2Raw);
    multiReporter->addReporter(std::move(mock1));
    multiReporter->addReporter(std::move(mock2));

    multiReporter->benchmarkPreparing("bench");
}

// Test that benchmarkPreparing is forwarded to listeners added via addListener
TEST_F(MultiReporterTest_791, BenchmarkPreparingWithListener_791) {
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, benchmarkPreparing(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock(mockRaw);
    multiReporter->addListener(std::move(mock));

    multiReporter->benchmarkPreparing("listener_bench");
}

// Test that benchmarkPreparing is forwarded to both listeners and reporters
TEST_F(MultiReporterTest_791, BenchmarkPreparingListenerAndReporter_791) {
    auto* listenerRaw = new MockEventListener();
    auto* reporterRaw = new MockEventListener();
    EXPECT_CALL(*listenerRaw, benchmarkPreparing(_)).Times(1);
    EXPECT_CALL(*reporterRaw, benchmarkPreparing(_)).Times(1);

    Detail::unique_ptr<IEventListener> listener(listenerRaw);
    Detail::unique_ptr<IEventListener> reporter(reporterRaw);
    multiReporter->addListener(std::move(listener));
    multiReporter->addReporter(std::move(reporter));

    multiReporter->benchmarkPreparing("combined_bench");
}

// Test benchmarkPreparing with empty string
TEST_F(MultiReporterTest_791, BenchmarkPreparingEmptyName_791) {
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, benchmarkPreparing(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock(mockRaw);
    multiReporter->addReporter(std::move(mock));

    multiReporter->benchmarkPreparing("");
}

// Test benchmarkFailed is forwarded to all reporters
TEST_F(MultiReporterTest_791, BenchmarkFailedForwarded_791) {
    auto* mock1Raw = new MockEventListener();
    auto* mock2Raw = new MockEventListener();
    EXPECT_CALL(*mock1Raw, benchmarkFailed(_)).Times(1);
    EXPECT_CALL(*mock2Raw, benchmarkFailed(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock1(mock1Raw);
    Detail::unique_ptr<IEventListener> mock2(mock2Raw);
    multiReporter->addReporter(std::move(mock1));
    multiReporter->addReporter(std::move(mock2));

    multiReporter->benchmarkFailed("error_msg");
}

// Test noMatchingTestCases is forwarded
TEST_F(MultiReporterTest_791, NoMatchingTestCasesForwarded_791) {
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, noMatchingTestCases(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock(mockRaw);
    multiReporter->addReporter(std::move(mock));

    multiReporter->noMatchingTestCases("unmatched_spec");
}

// Test fatalErrorEncountered is forwarded
TEST_F(MultiReporterTest_791, FatalErrorEncounteredForwarded_791) {
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, fatalErrorEncountered(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock(mockRaw);
    multiReporter->addReporter(std::move(mock));

    multiReporter->fatalErrorEncountered("fatal error");
}

// Test reportInvalidTestSpec is forwarded
TEST_F(MultiReporterTest_791, ReportInvalidTestSpecForwarded_791) {
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, reportInvalidTestSpec(_)).Times(1);

    Detail::unique_ptr<IEventListener> mock(mockRaw);
    multiReporter->addReporter(std::move(mock));

    multiReporter->reportInvalidTestSpec("invalid_arg");
}

// Test that multiple calls to benchmarkPreparing invoke each reporter each time
TEST_F(MultiReporterTest_791, BenchmarkPreparingCalledMultipleTimes_791) {
    auto* mockRaw = new MockEventListener();
    EXPECT_CALL(*mockRaw, benchmarkPreparing(_)).Times(3);

    Detail::unique_ptr<IEventListener> mock(mockRaw);
    multiReporter->addReporter(std::move(mock));

    multiReporter->benchmarkPreparing("bench1");
    multiReporter->benchmarkPreparing("bench2");
    multiReporter->benchmarkPreparing("bench3");
}

// Test no crash when calling various methods with no reporters
TEST_F(MultiReporterTest_791, NoReportersNoCrash_791) {
    EXPECT_NO_THROW(multiReporter->benchmarkPreparing("test"));
    EXPECT_NO_THROW(multiReporter->benchmarkFailed("error"));
    EXPECT_NO_THROW(multiReporter->noMatchingTestCases("spec"));
    EXPECT_NO_THROW(multiReporter->fatalErrorEncountered("fatal"));
    EXPECT_NO_THROW(multiReporter->reportInvalidTestSpec("invalid"));
}

// Test adding many reporters and that all receive benchmarkPreparing
TEST_F(MultiReporterTest_791, ManyReportersAllReceiveBenchmarkPreparing_791) {
    constexpr int N = 10;
    std::vector<MockEventListener*> mocks;

    for (int i = 0; i < N; ++i) {
        auto* mockRaw = new MockEventListener();
        EXPECT_CALL(*mockRaw, benchmarkPreparing(_)).Times(1);
        mocks.push_back(mockRaw);
        Detail::unique_ptr<IEventListener> mock(mockRaw);
        multiReporter->addReporter(std::move(mock));
    }

    multiReporter->benchmarkPreparing("mass_bench");
}

// Test adding listeners before reporters; both should get called
TEST_F(MultiReporterTest_791, ListenersBeforeReportersAllCalled_791) {
    auto* listener1Raw = new MockEventListener();
    auto* listener2Raw = new MockEventListener();
    auto* reporter1Raw = new MockEventListener();

    EXPECT_CALL(*listener1Raw, benchmarkPreparing(_)).Times(1);
    EXPECT_CALL(*listener2Raw, benchmarkPreparing(_)).Times(1);
    EXPECT_CALL(*reporter1Raw, benchmarkPreparing(_)).Times(1);

    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener1Raw));
    multiReporter->addListener(Detail::unique_ptr<IEventListener>(listener2Raw));
    multiReporter->addReporter(Detail::unique_ptr<IEventListener>(reporter1Raw));

    multiReporter->benchmarkPreparing("mixed_bench");
}
