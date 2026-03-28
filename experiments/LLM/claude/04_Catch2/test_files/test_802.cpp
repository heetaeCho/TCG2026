#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_totals.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace Catch;
using ::testing::_;
using ::testing::Eq;

// Mock for IConfig
class MockConfig : public IConfig {
public:
    // Provide minimal implementation for IConfig interface
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutNoTests, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(RangeGenerator<std::size_t> const&, benchmarkSamples, (), (const, override));
    MOCK_METHOD(unsigned int, rngSeed, (), (const, override));
    MOCK_METHOD(UseColour, defaultColourMode, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode2, (), (const));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis2, (), (const));
};

// Mock for IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config) : IEventListener(config) {}

    // Allow setting preferences for testing
    void setPreferences(ReporterPreferences prefs) {
        m_preferences = prefs;
    }

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, skipTest, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
};

class MultiReporterTest_802 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a config for constructing event listeners and MultiReporter
        config_ = nullptr; // MultiReporter uses IConfig* which can be null for testing
    }

    IConfig const* config_ = nullptr;
};

// Helper to create a MockEventListener with specific preferences
static Detail::unique_ptr<MockEventListener> makeMockListener(
    IConfig const* config, bool shouldRedirect = false) {
    auto mock = Detail::unique_ptr<MockEventListener>(new MockEventListener(config));
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = shouldRedirect;
    prefs.shouldReportAllAssertions = false;
    mock->setPreferences(prefs);
    return mock;
}

// Test: testCasePartialEnded forwards to a single reporter
TEST_F(MultiReporterTest_802, TestCasePartialEndedForwardsToSingleReporter_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testCasePartialEnded(_, Eq(1u))).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    // Create minimal TestCaseStats
    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    multi.testCasePartialEnded(stats, 1);
}

// Test: testCasePartialEnded forwards to multiple reporters
TEST_F(MultiReporterTest_802, TestCasePartialEndedForwardsToMultipleReporters_802) {
    MultiReporter multi(config_);

    auto* rawMock1 = new MockEventListener(config_);
    auto* rawMock2 = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock1->setPreferences(prefs);
    rawMock2->setPreferences(prefs);

    EXPECT_CALL(*rawMock1, testCasePartialEnded(_, Eq(0u))).Times(1);
    EXPECT_CALL(*rawMock2, testCasePartialEnded(_, Eq(0u))).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock2));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    multi.testCasePartialEnded(stats, 0);
}

// Test: testCasePartialEnded with part number boundary (max uint64)
TEST_F(MultiReporterTest_802, TestCasePartialEndedWithMaxPartNumber_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    uint64_t maxPart = UINT64_MAX;
    EXPECT_CALL(*rawMock, testCasePartialEnded(_, Eq(maxPart))).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    multi.testCasePartialEnded(stats, maxPart);
}

// Test: testCasePartialEnded with zero part number
TEST_F(MultiReporterTest_802, TestCasePartialEndedWithZeroPartNumber_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testCasePartialEnded(_, Eq(0u))).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    multi.testCasePartialEnded(stats, 0);
}

// Test: noMatchingTestCases forwards to all reporters
TEST_F(MultiReporterTest_802, NoMatchingTestCasesForwardsToAllReporters_802) {
    MultiReporter multi(config_);

    auto* rawMock1 = new MockEventListener(config_);
    auto* rawMock2 = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock1->setPreferences(prefs);
    rawMock2->setPreferences(prefs);

    EXPECT_CALL(*rawMock1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*rawMock2, noMatchingTestCases(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock2));

    multi.noMatchingTestCases("someSpec"_catch_sr);
}

// Test: fatalErrorEncountered forwards to all reporters
TEST_F(MultiReporterTest_802, FatalErrorEncounteredForwardsToAll_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, fatalErrorEncountered(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    multi.fatalErrorEncountered("fatal error"_catch_sr);
}

// Test: testRunStarting forwards to all reporters
TEST_F(MultiReporterTest_802, TestRunStartingForwardsToAllReporters_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testRunStarting(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestRunInfo runInfo("test run");
    multi.testRunStarting(runInfo);
}

// Test: testCaseStarting forwards to all reporters
TEST_F(MultiReporterTest_802, TestCaseStartingForwardsToAllReporters_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testCaseStarting(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    multi.testCaseStarting(testInfo);
}

// Test: addListener places listeners before reporters
TEST_F(MultiReporterTest_802, AddListenerAndReporterBothReceiveEvents_802) {
    MultiReporter multi(config_);

    auto* listener = new MockEventListener(config_);
    auto* reporter = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    listener->setPreferences(prefs);
    reporter->setPreferences(prefs);

    EXPECT_CALL(*listener, testCasePartialEnded(_, _)).Times(1);
    EXPECT_CALL(*reporter, testCasePartialEnded(_, _)).Times(1);

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    multi.testCasePartialEnded(stats, 0);
}

// Test: No reporters added - should not crash
TEST_F(MultiReporterTest_802, NoReportersAddedDoesNotCrash_802) {
    MultiReporter multi(config_);

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    // Should not crash with no reporters
    EXPECT_NO_THROW(multi.testCasePartialEnded(stats, 0));
}

// Test: testCaseEnded forwards to all reporters
TEST_F(MultiReporterTest_802, TestCaseEndedForwardsToAllReporters_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testCaseEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    multi.testCaseEnded(stats);
}

// Test: testRunEnded forwards to all reporters
TEST_F(MultiReporterTest_802, TestRunEndedForwardsToAllReporters_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testRunEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestRunInfo runInfo("test run");
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);

    multi.testRunEnded(runStats);
}

// Test: skipTest forwards to all reporters
TEST_F(MultiReporterTest_802, SkipTestForwardsToAllReporters_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, skipTest(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    multi.skipTest(testInfo);
}

// Test: Multiple listeners and reporters all receive events
TEST_F(MultiReporterTest_802, MultipleListenersAndReportersAllReceiveEvents_802) {
    MultiReporter multi(config_);

    auto* listener1 = new MockEventListener(config_);
    auto* listener2 = new MockEventListener(config_);
    auto* reporter1 = new MockEventListener(config_);
    auto* reporter2 = new MockEventListener(config_);

    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    listener1->setPreferences(prefs);
    listener2->setPreferences(prefs);
    reporter1->setPreferences(prefs);
    reporter2->setPreferences(prefs);

    EXPECT_CALL(*listener1, testCasePartialEnded(_, _)).Times(1);
    EXPECT_CALL(*listener2, testCasePartialEnded(_, _)).Times(1);
    EXPECT_CALL(*reporter1, testCasePartialEnded(_, _)).Times(1);
    EXPECT_CALL(*reporter2, testCasePartialEnded(_, _)).Times(1);

    multi.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multi.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter2));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), false);

    multi.testCasePartialEnded(stats, 5);
}

// Test: reportInvalidTestSpec forwards to all
TEST_F(MultiReporterTest_802, ReportInvalidTestSpecForwards_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, reportInvalidTestSpec(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    multi.reportInvalidTestSpec("invalid"_catch_sr);
}

// Test: sectionStarting and sectionEnded forward correctly
TEST_F(MultiReporterTest_802, SectionStartingAndEndedForward_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, sectionStarting(_)).Times(1);
    EXPECT_CALL(*rawMock, sectionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    SectionInfo sectionInfo("file.cpp", 1, "section", "description");
    multi.sectionStarting(sectionInfo);

    Counts assertions;
    double duration = 0.0;
    SectionStats sectionStats(SectionInfo("file.cpp", 1, "section"), assertions, duration, false);
    multi.sectionEnded(sectionStats);
}

// Test: testCasePartialEnded with aborting flag true
TEST_F(MultiReporterTest_802, TestCasePartialEndedWithAbortingTrue_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testCasePartialEnded(_, Eq(42u))).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    Totals totals;
    TestCaseStats stats(testInfo, totals, std::string(""), std::string(""), true);

    multi.testCasePartialEnded(stats, 42);
}

// Test: testCasePartialStarting forwards correctly
TEST_F(MultiReporterTest_802, TestCasePartialStartingForwards_802) {
    MultiReporter multi(config_);

    auto* rawMock = new MockEventListener(config_);
    ReporterPreferences prefs;
    prefs.shouldRedirectStdOut = false;
    rawMock->setPreferences(prefs);

    EXPECT_CALL(*rawMock, testCasePartialStarting(_, Eq(7u))).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(rawMock));

    TestCaseInfo testInfo("", {"test_name", "[tag]"}, SourceLineInfo("file.cpp", 1));
    multi.testCasePartialStarting(testInfo, 7);
}
