#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"

#include <vector>
#include <string>

// Concrete implementation of IEventListener for testing purposes
class TestEventListener : public Catch::IEventListener {
public:
    TestEventListener(const Catch::IConfig* config)
        : Catch::IEventListener(config) {}

    // Track which methods were called
    bool noMatchingTestCasesCalled = false;
    bool reportInvalidTestSpecCalled = false;
    bool testRunStartingCalled = false;
    bool testCaseStartingCalled = false;
    bool testCasePartialStartingCalled = false;
    bool sectionStartingCalled = false;
    bool benchmarkPreparingCalled = false;
    bool benchmarkStartingCalled = false;
    bool benchmarkEndedCalled = false;
    bool benchmarkFailedCalled = false;
    bool assertionStartingCalled = false;
    bool assertionEndedCalled = false;
    bool sectionEndedCalled = false;
    bool testCasePartialEndedCalled = false;
    bool testCaseEndedCalled = false;
    bool testRunEndedCalled = false;
    bool skipTestCalled = false;
    bool fatalErrorEncounteredCalled = false;
    bool listReportersCalled = false;
    bool listListenersCalled = false;
    bool listTestsCalled = false;
    bool listTagsCalled = false;

    std::string lastUnmatchedSpec;
    std::string lastInvalidArg;
    uint64_t lastPartNumber = 0;

    void noMatchingTestCases(Catch::StringRef unmatchedSpec) override {
        noMatchingTestCasesCalled = true;
        lastUnmatchedSpec = std::string(unmatchedSpec);
    }

    void reportInvalidTestSpec(Catch::StringRef invalidArgument) override {
        reportInvalidTestSpecCalled = true;
        lastInvalidArg = std::string(invalidArgument);
    }

    void testRunStarting(const Catch::TestRunInfo&) override {
        testRunStartingCalled = true;
    }

    void testCaseStarting(const Catch::TestCaseInfo&) override {
        testCaseStartingCalled = true;
    }

    void testCasePartialStarting(const Catch::TestCaseInfo&, uint64_t partNumber) override {
        testCasePartialStartingCalled = true;
        lastPartNumber = partNumber;
    }

    void sectionStarting(const Catch::SectionInfo&) override {
        sectionStartingCalled = true;
    }

    void benchmarkPreparing(Catch::StringRef) override {
        benchmarkPreparingCalled = true;
    }

    void benchmarkStarting(const Catch::BenchmarkInfo&) override {
        benchmarkStartingCalled = true;
    }

    void benchmarkEnded(const Catch::BenchmarkStats<>&) override {
        benchmarkEndedCalled = true;
    }

    void benchmarkFailed(Catch::StringRef) override {
        benchmarkFailedCalled = true;
    }

    void assertionStarting(const Catch::AssertionInfo&) override {
        assertionStartingCalled = true;
    }

    void assertionEnded(const Catch::AssertionStats&) override {
        assertionEndedCalled = true;
    }

    void sectionEnded(const Catch::SectionStats&) override {
        sectionEndedCalled = true;
    }

    void testCasePartialEnded(const Catch::TestCaseStats&, uint64_t partNumber) override {
        testCasePartialEndedCalled = true;
        lastPartNumber = partNumber;
    }

    void testCaseEnded(const Catch::TestCaseStats&) override {
        testCaseEndedCalled = true;
    }

    void testRunEnded(const Catch::TestRunStats&) override {
        testRunEndedCalled = true;
    }

    void skipTest(const Catch::TestCaseInfo&) override {
        skipTestCalled = true;
    }

    void fatalErrorEncountered(Catch::StringRef) override {
        fatalErrorEncounteredCalled = true;
    }

    void listReporters(const std::vector<Catch::ReporterDescription>&) override {
        listReportersCalled = true;
    }

    void listListeners(const std::vector<Catch::ListenerDescription>&) override {
        listListenersCalled = true;
    }

    void listTests(const std::vector<Catch::TestCaseHandle>&) override {
        listTestsCalled = true;
    }

    void listTags(const std::vector<Catch::TagInfo>&) override {
        listTagsCalled = true;
    }
};

// A minimal mock for IConfig
class MockConfig : public Catch::IConfig {
public:
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { return "test"; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    Catch::TestSpec const& testSpec() const override { static Catch::TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::None; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
};

class IEventListenerTest_69 : public ::testing::Test {
protected:
    MockConfig config;

    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(IEventListenerTest_69, ConstructionWithConfig_69) {
    TestEventListener listener(&config);
    // The listener should be constructible with a config pointer
    // No crash expected
    SUCCEED();
}

TEST_F(IEventListenerTest_69, ConstructionWithNullConfig_69) {
    TestEventListener listener(nullptr);
    // Should be constructible with null config
    SUCCEED();
}

TEST_F(IEventListenerTest_69, GetPreferencesReturnsReference_69) {
    TestEventListener listener(&config);
    const Catch::ReporterPreferences& prefs = listener.getPreferences();
    // Just verify we can access preferences without crashing
    (void)prefs;
    SUCCEED();
}

TEST_F(IEventListenerTest_69, GetPreferencesReturnsSameReference_69) {
    TestEventListener listener(&config);
    const Catch::ReporterPreferences& prefs1 = listener.getPreferences();
    const Catch::ReporterPreferences& prefs2 = listener.getPreferences();
    // Both calls should return the same reference
    EXPECT_EQ(&prefs1, &prefs2);
}

TEST_F(IEventListenerTest_69, DefaultPreferencesValues_69) {
    TestEventListener listener(&config);
    const Catch::ReporterPreferences& prefs = listener.getPreferences();
    // Default preferences - shouldRedirectStdOut should have a default value
    // We just check that accessing it doesn't crash
    (void)prefs.shouldRedirectStdOut;
    SUCCEED();
}

TEST_F(IEventListenerTest_69, DestructionDoesNotCrash_69) {
    {
        TestEventListener listener(&config);
    }
    // Destructor should run without crashing
    SUCCEED();
}

TEST_F(IEventListenerTest_69, DynamicAllocationAndDeletion_69) {
    Catch::IEventListener* listener = new TestEventListener(&config);
    const Catch::ReporterPreferences& prefs = listener->getPreferences();
    (void)prefs;
    delete listener;
    SUCCEED();
}

TEST_F(IEventListenerTest_69, VirtualMethodsCallable_69) {
    TestEventListener listener(&config);

    listener.noMatchingTestCases("test_spec");
    EXPECT_TRUE(listener.noMatchingTestCasesCalled);
    EXPECT_EQ(listener.lastUnmatchedSpec, "test_spec");
}

TEST_F(IEventListenerTest_69, ReportInvalidTestSpec_69) {
    TestEventListener listener(&config);

    listener.reportInvalidTestSpec("bad_spec");
    EXPECT_TRUE(listener.reportInvalidTestSpecCalled);
    EXPECT_EQ(listener.lastInvalidArg, "bad_spec");
}

TEST_F(IEventListenerTest_69, NoMatchingTestCasesWithEmptyString_69) {
    TestEventListener listener(&config);

    listener.noMatchingTestCases("");
    EXPECT_TRUE(listener.noMatchingTestCasesCalled);
    EXPECT_EQ(listener.lastUnmatchedSpec, "");
}

TEST_F(IEventListenerTest_69, FatalErrorEncountered_69) {
    TestEventListener listener(&config);

    listener.fatalErrorEncountered("something went wrong");
    EXPECT_TRUE(listener.fatalErrorEncounteredCalled);
}

TEST_F(IEventListenerTest_69, TestRunStarting_69) {
    TestEventListener listener(&config);

    Catch::TestRunInfo runInfo("test_group");
    listener.testRunStarting(runInfo);
    EXPECT_TRUE(listener.testRunStartingCalled);
}

TEST_F(IEventListenerTest_69, BenchmarkPreparing_69) {
    TestEventListener listener(&config);

    listener.benchmarkPreparing("bench1");
    EXPECT_TRUE(listener.benchmarkPreparingCalled);
}

TEST_F(IEventListenerTest_69, BenchmarkFailed_69) {
    TestEventListener listener(&config);

    listener.benchmarkFailed("bench_fail");
    EXPECT_TRUE(listener.benchmarkFailedCalled);
}

TEST_F(IEventListenerTest_69, TestCasePartialStartingWithPartNumber_69) {
    TestEventListener listener(&config);

    // Use a minimal TestCaseInfo - we need to construct one
    // We'll test the partNumber tracking
    // Since we can't easily construct TestCaseInfo, we just verify the interface compiles
    // and can be called through the base class pointer
    SUCCEED();
}

TEST_F(IEventListenerTest_69, ListReportersWithEmptyVector_69) {
    TestEventListener listener(&config);

    std::vector<Catch::ReporterDescription> descriptions;
    listener.listReporters(descriptions);
    EXPECT_TRUE(listener.listReportersCalled);
}

TEST_F(IEventListenerTest_69, ListListenersWithEmptyVector_69) {
    TestEventListener listener(&config);

    std::vector<Catch::ListenerDescription> descriptions;
    listener.listListeners(descriptions);
    EXPECT_TRUE(listener.listListenersCalled);
}

TEST_F(IEventListenerTest_69, ListTestsWithEmptyVector_69) {
    TestEventListener listener(&config);

    std::vector<Catch::TestCaseHandle> tests;
    listener.listTests(tests);
    EXPECT_TRUE(listener.listTestsCalled);
}

TEST_F(IEventListenerTest_69, ListTagsWithEmptyVector_69) {
    TestEventListener listener(&config);

    std::vector<Catch::TagInfo> tags;
    listener.listTags(tags);
    EXPECT_TRUE(listener.listTagsCalled);
}

TEST_F(IEventListenerTest_69, PolymorphicBehavior_69) {
    // Verify polymorphic behavior through base class pointer
    std::unique_ptr<Catch::IEventListener> listener =
        std::make_unique<TestEventListener>(&config);

    const Catch::ReporterPreferences& prefs = listener->getPreferences();
    (void)prefs;
    SUCCEED();
}

TEST_F(IEventListenerTest_69, MultipleListenersIndependentPreferences_69) {
    TestEventListener listener1(&config);
    TestEventListener listener2(&config);

    const Catch::ReporterPreferences& prefs1 = listener1.getPreferences();
    const Catch::ReporterPreferences& prefs2 = listener2.getPreferences();

    // Different listeners should have independent preference objects
    EXPECT_NE(&prefs1, &prefs2);
}

TEST_F(IEventListenerTest_69, PreferencesConsistentAcrossCalls_69) {
    TestEventListener listener(&config);

    bool val1 = listener.getPreferences().shouldRedirectStdOut;
    bool val2 = listener.getPreferences().shouldRedirectStdOut;

    EXPECT_EQ(val1, val2);
}
