// File: tests/test_assertion_or_benchmark_result_asBenchmark_855.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Headers under test
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"

using Catch::Detail::AssertionOrBenchmarkResult;

// If these live in Catch2 namespaces/headers as usual:
using Catch::BenchmarkStats;
using Catch::AssertionStats;

class AssertionOrBenchmarkResultTest_855 : public ::testing::Test {};

// --- Normal operation: constructed from Benchmark -> asBenchmark ok, type queries consistent
TEST_F(AssertionOrBenchmarkResultTest_855, AsBenchmarkReturnsReferenceAndTypeQueries_855) {
    BenchmarkStats<> input{};                     // treat as value per public interface
    AssertionOrBenchmarkResult aobr(input);       // construct with a benchmark result

    // Observable, interface-level behavior
    EXPECT_TRUE(aobr.isBenchmark());
    EXPECT_FALSE(aobr.isAssertion());

    // Should return a const reference and not crash
    BenchmarkStats<> const& ref1 = aobr.asBenchmark();
    BenchmarkStats<> const& ref2 = aobr.asBenchmark();

    // Observable: reference identity from repeated calls is stable
    EXPECT_EQ(&ref1, &ref2);
    (void)ref1;
    (void)ref2;
}

// --- Const-correctness: asBenchmark callable on const instance
TEST_F(AssertionOrBenchmarkResultTest_855, AsBenchmarkOnConstInstance_855) {
    BenchmarkStats<> input{};
    const AssertionOrBenchmarkResult aobr(input);

    EXPECT_TRUE(aobr.isBenchmark());
    EXPECT_FALSE(aobr.isAssertion());

    BenchmarkStats<> const& ref = aobr.asBenchmark();
    (void)ref; // No further assumptions about internal storage/copy semantics
}

// --- Boundary/error: constructed from Assertion -> asBenchmark must assert (debug)
// Guard with death-test availability & NDEBUG
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST_F(AssertionOrBenchmarkResultTest_855, AsBenchmarkOnAssertionDiesWithAssertInDebug_855) {
    AssertionStats assertion_input{};
    AssertionOrBenchmarkResult aobr(assertion_input);

    // Type queries reflect assertion mode
    EXPECT_TRUE(aobr.isAssertion());
    EXPECT_FALSE(aobr.isBenchmark());

    // asBenchmark is documented/implemented to assert when no benchmark is present.
    // We do not depend on the exact message; just that it aborts due to the assert.
    EXPECT_DEATH_IF_SUPPORTED(
        (void)aobr.asBenchmark(),
        "");  // empty regex: don't assume assert text
}
#endif
