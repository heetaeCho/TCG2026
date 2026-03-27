// File: tests/CumulativeReporterBase_benchmarkEnded_856.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "catch2/benchmark/catch_optimizer.hpp"
#include "catch2/catch_tostring.hpp"

using namespace Catch;

// A small test reporter that exposes ONLY observable aggregate info
// via the protected tree the base builds. We do not touch private fields.
class TestableCumulativeReporter : public CumulativeReporterBase {
public:
    explicit TestableCumulativeReporter( ReporterConfig&& cfg )
        : CumulativeReporterBase( CATCH_MOVE(cfg) ) {}

    // Will be filled when the run ends
    size_t totalSections = 0;
    size_t totalAssertionOrBenchmarkResults = 0;

    // We do not override other behavior; we only read the protected tree
    // after the run finishes, which is when the base has finished building it.
    void testRunEndedCumulative() override {
        // m_testRun is protected in CumulativeReporterBase's interface
        if (!m_testRun) return;

        // Walk the test run -> test cases -> sections recursively.
        std::function<void(const Detail::unique_ptr<SectionNode>&)> walkSection;
        walkSection = [&](const Detail::unique_ptr<SectionNode>& nodePtr) {
            if (!nodePtr) return;
            const SectionNode& node = *nodePtr;
            ++totalSections;
            // Public member assertionsAndBenchmarks is an observable container
            totalAssertionOrBenchmarkResults += node.assertionsAndBenchmarks.size();
            for (auto const& child : node.childSections) {
                walkSection(child);
            }
        };

        // TestRunNode/TestCaseNode are part of the cumulative reporter tree;
        // we only iterate via public containers exposed on those nodes.
        for (auto const& tc : m_testRun->children) {                // Test cases
            for (auto const& sec : tc->children) {                  // Top-level sections
                walkSection(sec);
            }
        }
    }
};

// --- Test helpers (create minimal, valid “dummy” infos) ---

static TestRunInfo makeRunInfo(const std::string& name = "run_856") {
    return TestRunInfo(name);
}

static TestCaseInfo makeCaseInfo(const std::string& name = "tc_856") {
    // Minimal TestCaseInfo: generator-less and with defaults
    return TestCaseInfo(
        NameAndTags{name, {}},
        SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)},
        {},  // className
        {},  // description
        0,   // testCaseThrows?
        false, // okToFail
        {},    // expectedToFail
        {}
    );
}

static SectionInfo makeSectionInfo(const std::string& name = "sec_856") {
    return SectionInfo{
        NameAndTags{name, {}},
        SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)}
    };
}

static BenchmarkStats<> makeBenchmark(const std::string& name, double ms0 = 1.0, double ms1 = 2.0) {
    BenchmarkStats<> s;
    s.info.name = name;
    s.samples = {
        Benchmark::FDuration{std::chrono::duration<double, std::milli>(ms0)},
        Benchmark::FDuration{std::chrono::duration<double, std::milli>(ms1)},
    };
    // The rest can be default-initialized (we are not asserting internal math)
    return s;
}

// A minimal sink to satisfy ReporterBase’s config requirement
struct StringStreamSink : IEventListener {
    std::ostringstream out;
    void fatalErrorEncountered( StringRef ) override {}
};

// =============== TESTS ===============

class CumulativeReporterBase_BenchmarkEnded_856 : public ::testing::Test {
protected:
    // Creates a reporter with a stringstream sink; we will NOT verify the bytes,
    // only the resulting cumulative tree via testRunEndedCumulative.
    TestableCumulativeReporter* makeReporter(std::unique_ptr<IEventListener>& holder) {
        auto sink = std::make_unique<StringStreamSink>();
        holder = std::move(sink);
        auto* asSink = static_cast<StringStreamSink*>(holder.get());

        // ReporterConfig requires a stream + preferences; we keep defaults
        auto cfg = ReporterConfig(asSink->out, {}, {});
        auto* rep = new TestableCumulativeReporter(CATCH_MOVE(cfg));
        return rep;
    }
};

// Normal flow: 1 section, 1 benchmark -> exactly 1 result stored in that section
TEST_F(CumulativeReporterBase_BenchmarkEnded_856, StoresOneBenchmarkInCurrentSection_856) {
    std::unique_ptr<IEventListener> holder;
    std::unique_ptr<TestableCumulativeReporter> rep(makeReporter(holder));

    rep->testRunStarting(makeRunInfo());
    rep->testCaseStarting(makeCaseInfo("case_1"));
    rep->sectionStarting(makeSectionInfo("S1"));

    rep->benchmarkEnded(makeBenchmark("bm1"));

    // Close the hierarchy in the usual order
    rep->sectionEnded(SectionStats{});
    rep->testCaseEnded(TestCaseStats{});
    rep->testRunEnded(TestRunStats{});

    // Observable effect: cumulative tree contains 1 result
    EXPECT_EQ(rep->totalSections, 1u);
    EXPECT_EQ(rep->totalAssertionOrBenchmarkResults, 1u);
}

// Multiple benchmarks in a single section -> all are stored
TEST_F(CumulativeReporterBase_BenchmarkEnded_856, StoresMultipleBenchmarksInSingleSection_856) {
    std::unique_ptr<IEventListener> holder;
    std::unique_ptr<TestableCumulativeReporter> rep(makeReporter(holder));

    rep->testRunStarting(makeRunInfo());
    rep->testCaseStarting(makeCaseInfo("case_multi"));
    rep->sectionStarting(makeSectionInfo("S_multi"));

    rep->benchmarkEnded(makeBenchmark("bm1"));
    rep->benchmarkEnded(makeBenchmark("bm2"));
    rep->benchmarkEnded(makeBenchmark("bm3"));

    rep->sectionEnded(SectionStats{});
    rep->testCaseEnded(TestCaseStats{});
    rep->testRunEnded(TestRunStats{});

    EXPECT_EQ(rep->totalSections, 1u);
    EXPECT_EQ(rep->totalAssertionOrBenchmarkResults, 3u);
}

// Benchmarks go to the *current* (deepest) section only
TEST_F(CumulativeReporterBase_BenchmarkEnded_856, AppendsToDeepestActiveSection_856) {
    std::unique_ptr<IEventListener> holder;
    std::unique_ptr<TestableCumulativeReporter> rep(makeReporter(holder));

    rep->testRunStarting(makeRunInfo());
    rep->testCaseStarting(makeCaseInfo("case_nested"));
    // S1
    rep->sectionStarting(makeSectionInfo("S1"));
      rep->benchmarkEnded(makeBenchmark("bm_at_S1_before_S2"));

      // S2 (nested)
      rep->sectionStarting(makeSectionInfo("S2"));
        rep->benchmarkEnded(makeBenchmark("bm_at_S2_only"));
      rep->sectionEnded(SectionStats{}); // end S2

      rep->benchmarkEnded(makeBenchmark("bm_at_S1_after_S2"));
    rep->sectionEnded(SectionStats{}); // end S1

    rep->testCaseEnded(TestCaseStats{});
    rep->testRunEnded(TestRunStats{});

    // We created 2 sections; there should be 3 total results across them.
    // Specifically: S1 has 2, S2 has 1. We only assert the total as an observable aggregate.
    EXPECT_EQ(rep->totalSections, 2u);
    EXPECT_EQ(rep->totalAssertionOrBenchmarkResults, 3u);
}

// Boundary-ish behavior: calling benchmarkEnded is a no-op for output,
// but it must be safe during an active section (no throws/crash).
TEST_F(CumulativeReporterBase_BenchmarkEnded_856, SafeDuringActiveSection_856) {
    std::unique_ptr<IEventListener> holder;
    std::unique_ptr<TestableCumulativeReporter> rep(makeReporter(holder));

    rep->testRunStarting(makeRunInfo());
    rep->testCaseStarting(makeCaseInfo("case_safe"));
    rep->sectionStarting(makeSectionInfo("S"));

    EXPECT_NO_THROW({
        rep->benchmarkEnded(makeBenchmark("bm"));
    });

    rep->sectionEnded(SectionStats{});
    rep->testCaseEnded(TestCaseStats{});
    rep->testRunEnded(TestRunStats{});

    EXPECT_EQ(rep->totalAssertionOrBenchmarkResults, 1u);
}

// Note on exceptional/error case coverage:
// The base implementation uses m_sectionStack.back() internally.
// Calling benchmarkEnded() without an active section would be undefined behavior;
// we do NOT write a death/UB test. Instead, we verify correct use (active section)
// and observable accumulation behavior as above.
