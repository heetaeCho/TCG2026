#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// We need to include enough Catch2 headers to get the types used
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock for IConfig
class MockConfig : public IConfig {
public:
    // Provide minimal implementation needed
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "mock"; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::Never; }
    double minDuration() const override { return 0.0; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
};

// Mock for IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));
};

class MultiReporterTest_808 : public ::testing::Test {
protected:
    MockConfig config;
    
    Detail::unique_ptr<MockEventListener> createMockListener() {
        auto* raw = new MockEventListener(&config);
        return Detail::unique_ptr<MockEventListener>(raw);
    }

    MultiReporter createMultiReporter() {
        // MultiReporter inherits from IEventListener which needs config
        // We need to construct it properly
        return MultiReporter(Detail::unique_ptr<IConfig const>(), nullptr);
    }
};

// Since MultiReporter's constructor requires IConfig, we need a fixture that properly constructs it.
// Let's try a different approach - create MultiReporter on the heap with the config pointer.

class MultiReporterFixture_808 : public ::testing::Test {
protected:
    MockConfig config_;
    std::unique_ptr<MultiReporter> multi_;

    void SetUp() override {
        multi_ = std::make_unique<MultiReporter>(&config_);
    }

    MockEventListener* addMockReporter() {
        auto* mock = new MockEventListener(&config_);
        multi_->addReporter(Detail::unique_ptr<IEventListener>(mock));
        return mock;
    }

    MockEventListener* addMockListener() {
        auto* mock = new MockEventListener(&config_);
        multi_->addListener(Detail::unique_ptr<IEventListener>(mock));
        return mock;
    }
};

// Test: listTests delegates to all reporters
TEST_F(MultiReporterFixture_808, ListTestsDelegatesToAllReporters_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    std::vector<TestCaseHandle> tests;
    EXPECT_CALL(*mock1, listTests(::testing::Ref(tests))).Times(1);
    EXPECT_CALL(*mock2, listTests(::testing::Ref(tests))).Times(1);

    multi_->listTests(tests);
}

// Test: listTests with no reporters does nothing
TEST_F(MultiReporterFixture_808, ListTestsWithNoReporters_808) {
    std::vector<TestCaseHandle> tests;
    // Should not crash
    multi_->listTests(tests);
}

// Test: listTests with single reporter
TEST_F(MultiReporterFixture_808, ListTestsWithSingleReporter_808) {
    auto* mock = addMockReporter();

    std::vector<TestCaseHandle> tests;
    EXPECT_CALL(*mock, listTests(::testing::Ref(tests))).Times(1);

    multi_->listTests(tests);
}

// Test: noMatchingTestCases delegates to all reporters
TEST_F(MultiReporterFixture_808, NoMatchingTestCasesDelegatesToAll_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    EXPECT_CALL(*mock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(_)).Times(1);

    multi_->noMatchingTestCases("some spec");
}

// Test: fatalErrorEncountered delegates
TEST_F(MultiReporterFixture_808, FatalErrorEncounteredDelegates_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    EXPECT_CALL(*mock1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(_)).Times(1);

    multi_->fatalErrorEncountered("fatal error");
}

// Test: reportInvalidTestSpec delegates
TEST_F(MultiReporterFixture_808, ReportInvalidTestSpecDelegates_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    EXPECT_CALL(*mock1, reportInvalidTestSpec(_)).Times(1);
    EXPECT_CALL(*mock2, reportInvalidTestSpec(_)).Times(1);

    multi_->reportInvalidTestSpec("invalid");
}

// Test: benchmarkPreparing delegates
TEST_F(MultiReporterFixture_808, BenchmarkPreparingDelegates_808) {
    auto* mock1 = addMockReporter();

    EXPECT_CALL(*mock1, benchmarkPreparing(_)).Times(1);

    multi_->benchmarkPreparing("bench1");
}

// Test: benchmarkFailed delegates
TEST_F(MultiReporterFixture_808, BenchmarkFailedDelegates_808) {
    auto* mock1 = addMockReporter();

    EXPECT_CALL(*mock1, benchmarkFailed(_)).Times(1);

    multi_->benchmarkFailed("bench error");
}

// Test: testRunStarting delegates to all reporters
TEST_F(MultiReporterFixture_808, TestRunStartingDelegates_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    EXPECT_CALL(*mock1, testRunStarting(_)).Times(1);
    EXPECT_CALL(*mock2, testRunStarting(_)).Times(1);

    TestRunInfo runInfo("test run");
    multi_->testRunStarting(runInfo);
}

// Test: skipTest delegates
TEST_F(MultiReporterFixture_808, SkipTestDelegates_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    EXPECT_CALL(*mock1, skipTest(_)).Times(1);
    EXPECT_CALL(*mock2, skipTest(_)).Times(1);

    // We need a TestCaseInfo - create a minimal one
    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    multi_->skipTest(*info);
}

// Test: listeners and reporters both receive events
TEST_F(MultiReporterFixture_808, ListenersAndReportersBothReceiveEvents_808) {
    auto* listener = addMockListener();
    auto* reporter = addMockReporter();

    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(1);

    multi_->noMatchingTestCases("spec");
}

// Test: listReporters delegates
TEST_F(MultiReporterFixture_808, ListReportersDelegates_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    std::vector<ReporterDescription> descriptions;
    EXPECT_CALL(*mock1, listReporters(::testing::Ref(descriptions))).Times(1);
    EXPECT_CALL(*mock2, listReporters(::testing::Ref(descriptions))).Times(1);

    multi_->listReporters(descriptions);
}

// Test: listListeners delegates
TEST_F(MultiReporterFixture_808, ListListenersDelegates_808) {
    auto* mock1 = addMockReporter();

    std::vector<ListenerDescription> descriptions;
    EXPECT_CALL(*mock1, listListeners(::testing::Ref(descriptions))).Times(1);

    multi_->listListeners(descriptions);
}

// Test: listTags delegates
TEST_F(MultiReporterFixture_808, ListTagsDelegates_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    std::vector<TagInfo> tags;
    EXPECT_CALL(*mock1, listTags(::testing::Ref(tags))).Times(1);
    EXPECT_CALL(*mock2, listTags(::testing::Ref(tags))).Times(1);

    multi_->listTags(tags);
}

// Test: assertionStarting delegates
TEST_F(MultiReporterFixture_808, AssertionStartingDelegates_808) {
    auto* mock1 = addMockReporter();
    auto* mock2 = addMockReporter();

    EXPECT_CALL(*mock1, assertionStarting(_)).Times(1);
    EXPECT_CALL(*mock2, assertionStarting(_)).Times(1);

    AssertionInfo info{"", SourceLineInfo("file", 1), "", ResultDisposition::Normal};
    multi_->assertionStarting(info);
}

// Test: sectionStarting delegates
TEST_F(MultiReporterFixture_808, SectionStartingDelegates_808) {
    auto* mock1 = addMockReporter();

    EXPECT_CALL(*mock1, sectionStarting(_)).Times(1);

    SectionInfo sectionInfo(SourceLineInfo("file", 1), "section");
    multi_->sectionStarting(sectionInfo);
}

// Test: addListener places listener before reporters
TEST_F(MultiReporterFixture_808, ListenerCalledBeforeReporter_808) {
    auto* reporter = addMockReporter();
    auto* listener = addMockListener();

    ::testing::InSequence seq;
    EXPECT_CALL(*listener, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*reporter, noMatchingTestCases(_)).Times(1);

    multi_->noMatchingTestCases("spec");
}

// Test: Multiple listeners maintain order
TEST_F(MultiReporterFixture_808, MultipleListenersMaintainOrder_808) {
    auto* listener1 = addMockListener();
    auto* listener2 = addMockListener();
    auto* reporter = addMockReporter();

    ::testing::InSequence seq;
    EXPECT_CALL(*listener1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*listener2, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*reporter, fatalErrorEncountered(_)).Times(1);

    multi_->fatalErrorEncountered("error");
}

// Test: testCasePartialStarting delegates with part number
TEST_F(MultiReporterFixture_808, TestCasePartialStartingDelegates_808) {
    auto* mock1 = addMockReporter();

    EXPECT_CALL(*mock1, testCasePartialStarting(_, 42)).Times(1);

    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    multi_->testCasePartialStarting(*info, 42);
}

// Test: testCasePartialEnded delegates with part number
TEST_F(MultiReporterFixture_808, TestCasePartialEndedDelegates_808) {
    auto* mock1 = addMockReporter();

    EXPECT_CALL(*mock1, testCasePartialEnded(_, 7)).Times(1);

    auto info = makeTestCaseInfo("", {"test", "[tag]"}, {});
    TestCaseStats stats(*info, Totals(), "", "", false);
    multi_->testCasePartialEnded(stats, 7);
}

// Test: empty multi reporter handles all events without crashing
TEST_F(MultiReporterFixture_808, EmptyMultiReporterHandlesAllEvents_808) {
    // No reporters or listeners added - should not crash
    multi_->noMatchingTestCases("spec");
    multi_->fatalErrorEncountered("error");
    multi_->reportInvalidTestSpec("invalid");
    multi_->benchmarkPreparing("bench");
    multi_->benchmarkFailed("fail");

    TestRunInfo runInfo("run");
    multi_->testRunStarting(runInfo);

    std::vector<ReporterDescription> reporterDescs;
    multi_->listReporters(reporterDescs);

    std::vector<ListenerDescription> listenerDescs;
    multi_->listListeners(listenerDescs);

    std::vector<TestCaseHandle> tests;
    multi_->listTests(tests);

    std::vector<TagInfo> tags;
    multi_->listTags(tags);
}
