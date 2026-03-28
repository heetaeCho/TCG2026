#include <catch2/reporters/catch_reporter_cumulative_base.hpp>
#include <catch2/benchmark/detail/catch_benchmark_stats.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_istream.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <string>

using namespace Catch;

// A concrete subclass of CumulativeReporterBase to enable testing
class TestCumulativeReporter : public CumulativeReporterBase {
public:
    using CumulativeReporterBase::CumulativeReporterBase;

    void testRunEndedCumulative() override {
        // No-op for testing
    }

    static std::string getDescription() {
        return "Test cumulative reporter";
    }

    // Expose section stack state through public interface by checking
    // the test run node after testRunEnded
    Detail::unique_ptr<TestRunNode>& getTestRun() {
        return m_testRun;
    }
};

class CumulativeReporterBaseTest_856 : public ::testing::Test {
protected:
    std::unique_ptr<std::ostringstream> stream;
    std::unique_ptr<TestCumulativeReporter> reporter;

    void SetUp() override {
        stream = std::make_unique<std::ostringstream>();
    }

    ReporterConfig makeConfig() {
        // Create a minimal config for the reporter
        auto streamPtr = Catch::Detail::make_unique<Catch::StringifiedStream>();
        // We need a valid ReporterConfig. This is tricky without a full Catch2 session.
        // We'll try to construct one with minimal setup.
        return ReporterConfig(nullptr, CATCH_MOVE(streamPtr), ColourMode::None, {});
    }

    TestCumulativeReporter* createReporter() {
        auto config = makeConfig();
        reporter = std::make_unique<TestCumulativeReporter>(CATCH_MOVE(config));
        return reporter.get();
    }

    BenchmarkStats<> makeBenchmarkStats(const std::string& name) {
        BenchmarkStats<> stats;
        stats.info.name = name;
        stats.info.samples = 100;
        stats.info.iterations = 1;
        stats.info.estimatedDuration = 1.0;
        stats.outlierVariance = 0.5;
        return stats;
    }

    // Helper to set up the reporter into a state where benchmarkEnded can be called
    // (i.e., there must be a section on the stack)
    void setupSectionStack(TestCumulativeReporter* rep) {
        // Start a test run
        TestRunInfo runInfo("test_group");
        rep->testRunStarting(runInfo);

        // Start a test case
        auto tcInfo = makeTestCaseInfo();
        rep->testCaseStarting(*tcInfo);
        rep->testCasePartialStarting(*tcInfo, 0);

        // Start a section to get something on the section stack
        SectionInfo sectionInfo(SourceLineInfo("file.cpp", 1), "test_section");
        rep->sectionStarting(sectionInfo);
    }

    void teardownSectionStack(TestCumulativeReporter* rep) {
        // End the section
        SectionStats sectionStats(SectionInfo(SourceLineInfo("file.cpp", 1), "test_section"),
                                  Counts(), 0.0, false);
        rep->sectionEnded(sectionStats);

        // End test case partial
        TestCaseStats tcStats(makeTestCaseInfo(), Totals(), "", "", false);
        rep->testCasePartialEnded(tcStats, 0);

        // End test case
        rep->testCaseEnded(tcStats);

        // End test run
        TestRunStats runStats(TestRunInfo("test_group"), Totals(), false);
        rep->testRunEnded(runStats);
    }

    Detail::unique_ptr<TestCaseInfo> makeTestCaseInfo() {
        return Detail::make_unique<TestCaseInfo>(
            "", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    }
};

// Test that benchmarkEnded can be called after proper setup without crashing
TEST_F(CumulativeReporterBaseTest_856, BenchmarkEndedDoesNotCrash_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupSectionStack(rep);

    auto stats = makeBenchmarkStats("bench1");
    EXPECT_NO_THROW(rep->benchmarkEnded(stats));

    teardownSectionStack(rep);
}

// Test that multiple benchmarkEnded calls work
TEST_F(CumulativeReporterBaseTest_856, MultipleBenchmarkEndedCalls_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupSectionStack(rep);

    auto stats1 = makeBenchmarkStats("bench1");
    auto stats2 = makeBenchmarkStats("bench2");
    auto stats3 = makeBenchmarkStats("bench3");

    EXPECT_NO_THROW(rep->benchmarkEnded(stats1));
    EXPECT_NO_THROW(rep->benchmarkEnded(stats2));
    EXPECT_NO_THROW(rep->benchmarkEnded(stats3));

    teardownSectionStack(rep);
}

// Test sectionStarting creates section nodes
TEST_F(CumulativeReporterBaseTest_856, SectionStartingDoesNotCrash_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    TestRunInfo runInfo("test_group");
    rep->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo();
    rep->testCaseStarting(*tcInfo);
    rep->testCasePartialStarting(*tcInfo, 0);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 1), "section1");
    EXPECT_NO_THROW(rep->sectionStarting(sectionInfo));

    // Clean up
    SectionStats sectionStats(SectionInfo(SourceLineInfo("file.cpp", 1), "section1"),
                              Counts(), 0.0, false);
    rep->sectionEnded(sectionStats);

    TestCaseStats tcStats(*tcInfo, Totals(), "", "", false);
    rep->testCasePartialEnded(tcStats, 0);
    rep->testCaseEnded(tcStats);

    TestRunStats runStats(TestRunInfo("test_group"), Totals(), false);
    rep->testRunEnded(runStats);
}

// Test nested sections
TEST_F(CumulativeReporterBaseTest_856, NestedSectionsWork_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    TestRunInfo runInfo("test_group");
    rep->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo();
    rep->testCaseStarting(*tcInfo);
    rep->testCasePartialStarting(*tcInfo, 0);

    SectionInfo section1(SourceLineInfo("file.cpp", 1), "outer");
    rep->sectionStarting(section1);

    SectionInfo section2(SourceLineInfo("file.cpp", 2), "inner");
    rep->sectionStarting(section2);

    auto stats = makeBenchmarkStats("nested_bench");
    EXPECT_NO_THROW(rep->benchmarkEnded(stats));

    SectionStats innerStats(SectionInfo(SourceLineInfo("file.cpp", 2), "inner"),
                            Counts(), 0.0, false);
    rep->sectionEnded(innerStats);

    SectionStats outerStats(SectionInfo(SourceLineInfo("file.cpp", 1), "outer"),
                            Counts(), 0.0, false);
    rep->sectionEnded(outerStats);

    TestCaseStats tcStats(*tcInfo, Totals(), "", "", false);
    rep->testCasePartialEnded(tcStats, 0);
    rep->testCaseEnded(tcStats);

    TestRunStats runStats(TestRunInfo("test_group"), Totals(), false);
    rep->testRunEnded(runStats);
}

// Test no-op methods don't crash
TEST_F(CumulativeReporterBaseTest_856, NoOpMethodsDoNotCrash_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    EXPECT_NO_THROW(rep->benchmarkPreparing("bench_prep"_catch_sr));
    BenchmarkInfo bInfo{"bench_start", 100, 1, 1.0};
    EXPECT_NO_THROW(rep->benchmarkStarting(bInfo));
    EXPECT_NO_THROW(rep->benchmarkFailed("failure reason"_catch_sr));
    EXPECT_NO_THROW(rep->noMatchingTestCases("pattern"_catch_sr));
    EXPECT_NO_THROW(rep->reportInvalidTestSpec("bad spec"_catch_sr));
    EXPECT_NO_THROW(rep->fatalErrorEncountered("fatal error"_catch_sr));
}

// Test the full lifecycle: testRunStarting -> testCaseStarting -> section -> assertion -> end
TEST_F(CumulativeReporterBaseTest_856, FullLifecycleDoesNotCrash_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    TestRunInfo runInfo("full_lifecycle");
    rep->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo();
    rep->testCaseStarting(*tcInfo);
    rep->testCasePartialStarting(*tcInfo, 0);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "main_section");
    rep->sectionStarting(sectionInfo);

    // Add a benchmark
    auto benchStats = makeBenchmarkStats("perf_test");
    rep->benchmarkEnded(benchStats);

    // End section
    SectionStats sStats(SectionInfo(SourceLineInfo("file.cpp", 10), "main_section"),
                        Counts(), 0.1, false);
    rep->sectionEnded(sStats);

    TestCaseStats tcStats(*tcInfo, Totals(), "", "", false);
    rep->testCasePartialEnded(tcStats, 0);
    rep->testCaseEnded(tcStats);

    TestRunStats runStats(TestRunInfo("full_lifecycle"), Totals(), false);
    EXPECT_NO_THROW(rep->testRunEnded(runStats));
}

// Test that testRunEndedCumulative is called via testRunEnded
TEST_F(CumulativeReporterBaseTest_856, TestRunEndedTriggersTestRunEndedCumulative_856) {
    // Use a mock-like approach
    class MockCumulativeReporter : public CumulativeReporterBase {
    public:
        using CumulativeReporterBase::CumulativeReporterBase;
        bool cumulativeEndCalled = false;

        void testRunEndedCumulative() override {
            cumulativeEndCalled = true;
        }

        static std::string getDescription() { return "Mock"; }
    };

    auto streamPtr = Catch::Detail::make_unique<Catch::StringifiedStream>();
    ReporterConfig config(nullptr, CATCH_MOVE(streamPtr), ColourMode::None, {});
    MockCumulativeReporter mockRep(CATCH_MOVE(config));

    TestRunInfo runInfo("test");
    mockRep.testRunStarting(runInfo);

    auto tcInfo = Detail::make_unique<TestCaseInfo>(
        "", {"tc", "[t]"}, SourceLineInfo("f.cpp", 1));
    mockRep.testCaseStarting(*tcInfo);
    mockRep.testCasePartialStarting(*tcInfo, 0);

    SectionInfo si(SourceLineInfo("f.cpp", 1), "s");
    mockRep.sectionStarting(si);
    SectionStats ss(SectionInfo(SourceLineInfo("f.cpp", 1), "s"), Counts(), 0.0, false);
    mockRep.sectionEnded(ss);

    TestCaseStats tcs(*tcInfo, Totals(), "", "", false);
    mockRep.testCasePartialEnded(tcs, 0);
    mockRep.testCaseEnded(tcs);

    EXPECT_FALSE(mockRep.cumulativeEndCalled);

    TestRunStats runStats(TestRunInfo("test"), Totals(), false);
    mockRep.testRunEnded(runStats);

    EXPECT_TRUE(mockRep.cumulativeEndCalled);
}

// Test SectionNode::hasAnyAssertions returns false for empty node
TEST_F(CumulativeReporterBaseTest_856, SectionNodeHasNoAssertionsWhenEmpty_856) {
    SectionStats stats(SectionInfo(SourceLineInfo("file.cpp", 1), "empty_section"),
                       Counts(), 0.0, false);
    CumulativeReporterBase::SectionNode node(stats);

    EXPECT_FALSE(node.hasAnyAssertions());
}

// Test SectionNode equality
TEST_F(CumulativeReporterBaseTest_856, SectionNodeEquality_856) {
    SectionStats stats1(SectionInfo(SourceLineInfo("file.cpp", 1), "section_a"),
                        Counts(), 0.0, false);
    SectionStats stats2(SectionInfo(SourceLineInfo("file.cpp", 1), "section_a"),
                        Counts(), 0.0, false);
    SectionStats stats3(SectionInfo(SourceLineInfo("file.cpp", 2), "section_b"),
                        Counts(), 0.0, false);

    CumulativeReporterBase::SectionNode node1(stats1);
    CumulativeReporterBase::SectionNode node2(stats2);
    CumulativeReporterBase::SectionNode node3(stats3);

    EXPECT_TRUE(node1 == node2);
    EXPECT_FALSE(node1 == node3);
}

// Test skipTest doesn't crash
TEST_F(CumulativeReporterBaseTest_856, SkipTestDoesNotCrash_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    auto tcInfo = makeTestCaseInfo();
    EXPECT_NO_THROW(rep->skipTest(*tcInfo));
}

// Test benchmarkEnded with default/empty BenchmarkStats
TEST_F(CumulativeReporterBaseTest_856, BenchmarkEndedWithDefaultStats_856) {
    auto* rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupSectionStack(rep);

    BenchmarkStats<> emptyStats{};
    EXPECT_NO_THROW(rep->benchmarkEnded(emptyStats));

    teardownSectionStack(rep);
}
