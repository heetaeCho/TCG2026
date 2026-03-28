#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;

// Mock for IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, hasTests, (), (const, override));
};

// Mock for IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config, bool shouldRedirect, bool shouldReportAll)
        : IEventListener(config) {
        m_preferences.shouldRedirectStdOut = shouldRedirect;
        m_preferences.shouldReportAllAssertions = shouldReportAll;
    }

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

class MultiReporterTest_787 : public ::testing::Test {
protected:
    MockConfig config;

    Detail::unique_ptr<MockEventListener> makeMockListener(bool shouldRedirect = false, bool shouldReportAll = false) {
        return Detail::unique_ptr<MockEventListener>(
            new MockEventListener(&config, shouldRedirect, shouldReportAll));
    }

    MultiReporter makeMultiReporter() {
        return MultiReporter(static_cast<IConfig const*>(&config));
    }
};

// Test: Adding a single reporter does not crash
TEST_F(MultiReporterTest_787, AddSingleReporter_787) {
    auto multi = makeMultiReporter();
    auto mock = makeMockListener(false, false);
    EXPECT_NO_THROW(multi.addReporter(CATCH_MOVE(mock)));
}

// Test: Adding multiple reporters does not crash
TEST_F(MultiReporterTest_787, AddMultipleReporters_787) {
    auto multi = makeMultiReporter();
    auto mock1 = makeMockListener(false, false);
    auto mock2 = makeMockListener(true, false);
    EXPECT_NO_THROW(multi.addReporter(CATCH_MOVE(mock1)));
    EXPECT_NO_THROW(multi.addReporter(CATCH_MOVE(mock2)));
}

// Test: Adding a single listener does not crash
TEST_F(MultiReporterTest_787, AddSingleListener_787) {
    auto multi = makeMultiReporter();
    auto mock = makeMockListener(false, false);
    EXPECT_NO_THROW(multi.addListener(CATCH_MOVE(mock)));
}

// Test: Adding listeners and reporters together
TEST_F(MultiReporterTest_787, AddListenersAndReporters_787) {
    auto multi = makeMultiReporter();
    auto listener = makeMockListener(false, false);
    auto reporter = makeMockListener(true, false);
    EXPECT_NO_THROW(multi.addListener(CATCH_MOVE(listener)));
    EXPECT_NO_THROW(multi.addReporter(CATCH_MOVE(reporter)));
}

// Test: noMatchingTestCases is forwarded to all reporters
TEST_F(MultiReporterTest_787, NoMatchingTestCasesForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);
    auto* raw2 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, noMatchingTestCases(::testing::_)).Times(1);
    EXPECT_CALL(*raw2, noMatchingTestCases(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw2));

    multi.noMatchingTestCases("some_spec"_catch_sr);
}

// Test: fatalErrorEncountered is forwarded to all reporters
TEST_F(MultiReporterTest_787, FatalErrorEncounteredForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);
    auto* raw2 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, fatalErrorEncountered(::testing::_)).Times(1);
    EXPECT_CALL(*raw2, fatalErrorEncountered(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw2));

    multi.fatalErrorEncountered("fatal error"_catch_sr);
}

// Test: testRunStarting is forwarded to all reporters
TEST_F(MultiReporterTest_787, TestRunStartingForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);
    auto* raw2 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, testRunStarting(::testing::_)).Times(1);
    EXPECT_CALL(*raw2, testRunStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw2));

    TestRunInfo runInfo("test_run");
    multi.testRunStarting(runInfo);
}

// Test: testCaseStarting is forwarded
TEST_F(MultiReporterTest_787, TestCaseStartingForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, testCaseStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    // We need a TestCaseInfo - create a minimal one
    auto tcInfo = Catch::makeTestCaseInfo("", {"test_case", "[tag]"}, {""_catch_sr, 0});
    multi.testCaseStarting(*tcInfo);
}

// Test: sectionStarting is forwarded
TEST_F(MultiReporterTest_787, SectionStartingForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, sectionStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    SectionInfo sectionInfo{""_catch_sr, "section_name"};
    multi.sectionStarting(sectionInfo);
}

// Test: assertionStarting is forwarded
TEST_F(MultiReporterTest_787, AssertionStartingForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, assertionStarting(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    AssertionInfo info{"", {"", 0}, "", ResultDisposition::Normal};
    multi.assertionStarting(info);
}

// Test: skipTest is forwarded
TEST_F(MultiReporterTest_787, SkipTestForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);
    auto* raw2 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, skipTest(::testing::_)).Times(1);
    EXPECT_CALL(*raw2, skipTest(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw2));

    auto tcInfo = Catch::makeTestCaseInfo("", {"test_case", "[tag]"}, {""_catch_sr, 0});
    multi.skipTest(*tcInfo);
}

// Test: reportInvalidTestSpec is forwarded
TEST_F(MultiReporterTest_787, ReportInvalidTestSpecForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, reportInvalidTestSpec(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    multi.reportInvalidTestSpec("bad_spec"_catch_sr);
}

// Test: benchmarkPreparing is forwarded
TEST_F(MultiReporterTest_787, BenchmarkPreparingForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, benchmarkPreparing(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    multi.benchmarkPreparing("bench"_catch_sr);
}

// Test: benchmarkFailed is forwarded
TEST_F(MultiReporterTest_787, BenchmarkFailedForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, benchmarkFailed(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    multi.benchmarkFailed("bench_error"_catch_sr);
}

// Test: Preferences - shouldRedirectStdOut is updated based on reporters
TEST_F(MultiReporterTest_787, PreferencesRedirectStdOut_787) {
    auto multi = makeMultiReporter();

    // Add a reporter that wants redirect
    auto* raw1 = new MockEventListener(&config, true, false);
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    // The multi reporter's preferences should reflect aggregated preferences
    // After adding a reporter with shouldRedirectStdOut=true, if no noncapturing reporters,
    // the multi should allow redirect
    auto prefs = multi.getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
}

// Test: Preferences - shouldRedirectStdOut becomes false when a noncapturing reporter is added
TEST_F(MultiReporterTest_787, PreferencesNoncapturingReporter_787) {
    auto multi = makeMultiReporter();

    // Add a reporter that does NOT want redirect (shouldRedirectStdOut=false)
    auto* raw1 = new MockEventListener(&config, false, false);
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    auto prefs = multi.getPreferences();
    // With a noncapturing reporter, redirect should be false
    EXPECT_FALSE(prefs.shouldRedirectStdOut);
}

// Test: Preferences - shouldReportAllAssertions updated
TEST_F(MultiReporterTest_787, PreferencesShouldReportAllAssertions_787) {
    auto multi = makeMultiReporter();

    auto* raw1 = new MockEventListener(&config, false, true);
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    auto prefs = multi.getPreferences();
    EXPECT_TRUE(prefs.shouldReportAllAssertions);
}

// Test: Listeners are placed before reporters in forwarding
TEST_F(MultiReporterTest_787, ListenersBeforeReporters_787) {
    auto multi = makeMultiReporter();

    auto* listener = new MockEventListener(&config, false, false);
    auto* reporter = new MockEventListener(&config, false, false);

    ::testing::InSequence seq;
    EXPECT_CALL(*listener, noMatchingTestCases(::testing::_)).Times(1);
    EXPECT_CALL(*reporter, noMatchingTestCases(::testing::_)).Times(1);

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    multi.noMatchingTestCases("spec"_catch_sr);
}

// Test: Empty multi reporter - calling methods without any reporters doesn't crash
TEST_F(MultiReporterTest_787, EmptyMultiReporterNoMatchingTestCases_787) {
    auto multi = makeMultiReporter();
    EXPECT_NO_THROW(multi.noMatchingTestCases("spec"_catch_sr));
}

// Test: Empty multi reporter - fatalErrorEncountered
TEST_F(MultiReporterTest_787, EmptyMultiReporterFatalError_787) {
    auto multi = makeMultiReporter();
    EXPECT_NO_THROW(multi.fatalErrorEncountered("error"_catch_sr));
}

// Test: listReporters forwarded
TEST_F(MultiReporterTest_787, ListReportersForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, listReporters(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    std::vector<ReporterDescription> descriptions;
    multi.listReporters(descriptions);
}

// Test: listListeners forwarded
TEST_F(MultiReporterTest_787, ListListenersForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, listListeners(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    std::vector<ListenerDescription> descriptions;
    multi.listListeners(descriptions);
}

// Test: listTests forwarded
TEST_F(MultiReporterTest_787, ListTestsForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, listTests(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    std::vector<TestCaseHandle> tests;
    multi.listTests(tests);
}

// Test: listTags forwarded
TEST_F(MultiReporterTest_787, ListTagsForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, listTags(::testing::_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    std::vector<TagInfo> tags;
    multi.listTags(tags);
}

// Test: Multiple listeners added before reporter
TEST_F(MultiReporterTest_787, MultipleListenersOrderPreserved_787) {
    auto multi = makeMultiReporter();

    auto* listener1 = new MockEventListener(&config, false, false);
    auto* listener2 = new MockEventListener(&config, false, false);
    auto* reporter1 = new MockEventListener(&config, false, false);

    ::testing::InSequence seq;
    EXPECT_CALL(*listener1, fatalErrorEncountered(::testing::_)).Times(1);
    EXPECT_CALL(*listener2, fatalErrorEncountered(::testing::_)).Times(1);
    EXPECT_CALL(*reporter1, fatalErrorEncountered(::testing::_)).Times(1);

    multi.addListener(Detail::unique_ptr<IEventListener>(listener1));
    multi.addListener(Detail::unique_ptr<IEventListener>(listener2));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter1));

    multi.fatalErrorEncountered("error"_catch_sr);
}

// Test: Adding reporter with redirect true then one with false
TEST_F(MultiReporterTest_787, MixedRedirectPreferences_787) {
    auto multi = makeMultiReporter();

    auto* raw1 = new MockEventListener(&config, true, false);
    auto* raw2 = new MockEventListener(&config, false, false);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(raw2));

    // Once a noncapturing reporter is added, shouldRedirectStdOut should be false
    auto prefs = multi.getPreferences();
    EXPECT_FALSE(prefs.shouldRedirectStdOut);
}

// Test: testCasePartialStarting forwarded
TEST_F(MultiReporterTest_787, TestCasePartialStartingForwarded_787) {
    auto multi = makeMultiReporter();
    auto* raw1 = new MockEventListener(&config, false, false);

    EXPECT_CALL(*raw1, testCasePartialStarting(::testing::_, 42)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(raw1));

    auto tcInfo = Catch::makeTestCaseInfo("", {"test_case", "[tag]"}, {""_catch_sr, 0});
    multi.testCasePartialStarting(*tcInfo, 42);
}
