// File: tests/AssertionOrBenchmarkResult_854_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the interface under test
#include "Catch2/src/catch2/reporters/catch_reporter_cumulative_base.hpp"

// If your project uses separate headers for these types, include them as needed:
// #include "Catch2/src/catch2/reporters/catch_reporter_helpers.hpp"
// #include "Catch2/src/catch2/benchmark/catch_benchmark_stats.hpp"
// #include "Catch2/src/catch2/reporters/catch_reporter_helpers.hpp"

using namespace Catch;
using Catch::Detail::AssertionOrBenchmarkResult;

// -------- Minimal helpers (replace bodies if your types require non-default construction) --------
namespace {
    // Adjust these to construct minimally valid instances in your codebase.
    // The idea is to avoid depending on any private/internal state or inferred logic.
    AssertionStats makeAssertion() {
        // If AssertionStats is not default-constructible in your tree,
        // provide the simplest valid construction here using public constructors.
        return AssertionStats{};
    }

    BenchmarkStats<> makeBenchmark() {
        // If BenchmarkStats<> is not default-constructible, provide a minimal valid build here.
        return BenchmarkStats<>{};
    }
} // namespace

// ------------------------------------------------------------------------------------------------
// Normal operation: Construct with AssertionStats -> isAssertion true, isBenchmark false
// ------------------------------------------------------------------------------------------------
TEST(AssertionOrBenchmarkResult_854, ConstructWithAssertion_SetsFlags_854) {
    auto as = makeAssertion();
    AssertionOrBenchmarkResult aorb{as};

    EXPECT_TRUE(aorb.isAssertion()) << "Object constructed from AssertionStats should report isAssertion() == true";
    EXPECT_FALSE(aorb.isBenchmark()) << "Object constructed from AssertionStats should report isBenchmark() == false";
}

// ------------------------------------------------------------------------------------------------
// Normal operation: Construct with BenchmarkStats -> isBenchmark true, isAssertion false
// ------------------------------------------------------------------------------------------------
TEST(AssertionOrBenchmarkResult_854, ConstructWithBenchmark_SetsFlags_854) {
    auto bs = makeBenchmark();
    AssertionOrBenchmarkResult aorb{bs};

    EXPECT_TRUE(aorb.isBenchmark()) << "Object constructed from BenchmarkStats should report isBenchmark() == true";
    EXPECT_FALSE(aorb.isAssertion()) << "Object constructed from BenchmarkStats should report isAssertion() == false";
}

// ------------------------------------------------------------------------------------------------
// Accessor success path: asAssertion() should be valid when constructed from AssertionStats
// We only verify it does not crash and returns a reference; we don't assert on internals.
// ------------------------------------------------------------------------------------------------
TEST(AssertionOrBenchmarkResult_854, AsAssertion_SucceedsWhenHoldingAssertion_854) {
    auto as = makeAssertion();
    AssertionOrBenchmarkResult aorb{as};

    // Should not assert/abort; return type is const AssertionStats&
    const AssertionStats& ref = aorb.asAssertion();
    (void)ref; // silence unused warning; we don't rely on internal contents
}

// ------------------------------------------------------------------------------------------------
// Accessor success path: asBenchmark() should be valid when constructed from BenchmarkStats
// ------------------------------------------------------------------------------------------------
TEST(AssertionOrBenchmarkResult_854, AsBenchmark_SucceedsWhenHoldingBenchmark_854) {
    auto bs = makeBenchmark();
    AssertionOrBenchmarkResult aorb{bs};

    // Should not assert/abort; return type is const BenchmarkStats<>&
    const BenchmarkStats<>& ref = aorb.asBenchmark();
    (void)ref;
}

// ------------------------------------------------------------------------------------------------
// Exceptional/error cases (observable via debug-assert):
// Calling asAssertion() when holding a Benchmark should trigger an assert.
// Calling asBenchmark() when holding an Assertion should trigger an assert.
// These are verified via death tests (assert -> abnormal termination in debug builds).
// ------------------------------------------------------------------------------------------------
#if !defined(NDEBUG) // Only meaningful when `assert` is active
TEST(AssertionOrBenchmarkResult_854, AsAssertion_DeathWhenHoldingBenchmark_854) {
    auto bs = makeBenchmark();
    AssertionOrBenchmarkResult aorb{bs};

    // ASSERT_DEATH expects a regex for stderr. We don't depend on the message; accept anything.
    EXPECT_DEATH({ (void)aorb.asAssertion(); }, ".*");
}

TEST(AssertionOrBenchmarkResult_854, AsBenchmark_DeathWhenHoldingAssertion_854) {
    auto as = makeAssertion();
    AssertionOrBenchmarkResult aorb{as};

    EXPECT_DEATH({ (void)aorb.asBenchmark(); }, ".*");
}
#else
// In release builds, asserts are compiled out, so we cannot observe the failure mode.
// Provide no-op placeholders so the suite remains green under NDEBUG.
TEST(AssertionOrBenchmarkResult_854, AsAssertion_NoDeathCheckInRelease_854) { SUCCEED(); }
TEST(AssertionOrBenchmarkResult_854, AsBenchmark_NoDeathCheckInRelease_854) { SUCCEED(); }
#endif

// ------------------------------------------------------------------------------------------------
// Consistency check: Flags are mutually exclusive in observable behavior.
// (We do not assert on internal state; just verify what public methods report.)
// ------------------------------------------------------------------------------------------------
TEST(AssertionOrBenchmarkResult_854, FlagsAreMutuallyExclusive_854) {
    {
        auto as = makeAssertion();
        AssertionOrBenchmarkResult aorb{as};
        EXPECT_EQ(aorb.isAssertion(), !aorb.isBenchmark());
    }
    {
        auto bs = makeBenchmark();
        AssertionOrBenchmarkResult aorb{bs};
        EXPECT_EQ(aorb.isAssertion(), !aorb.isBenchmark());
    }
}
