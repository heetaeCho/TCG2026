// File: tests/AssertionOrBenchmarkResult_isBenchmark_853.cpp

#include <gtest/gtest.h>

// Include the public interface of the class under test.
// (Paths follow your prompt; adjust include paths as they exist in your tree.)
#include "Catch2/src/catch2/reporters/catch_reporter_cumulative_base.hpp"

using Catch::Detail::AssertionOrBenchmarkResult;

//
// NOTE:
// These types are collaborators required only to *construct* the SUT.
// We do not simulate any internal behavior of the SUT; we merely create
// valid instances to satisfy the public constructors.
// If your project exposes the real types, include their headers instead
// and remove these minimal forward declarations.
//
namespace Catch {
// Minimal forward declarations so tests compile if real headers are not included.
// If real definitions are available in your project, prefer including them.
struct AssertionStats { /* intentionally empty for construction only */ };

template <typename T = void>
struct BenchmarkStats { /* intentionally empty for construction only */ };
} // namespace Catch

// -----------------------------
// Test fixture (kept simple)
// -----------------------------
class AssertionOrBenchmarkResultTest_853 : public ::testing::Test {};

// Normal operation: constructing from AssertionStats should report NOT a benchmark.
TEST_F(AssertionOrBenchmarkResultTest_853,
       IsBenchmark_False_WhenConstructedWithAssertion_853) {
    Catch::AssertionStats assertion{};
    AssertionOrBenchmarkResult sut(assertion);

    EXPECT_FALSE(sut.isBenchmark());
}

// Normal operation: constructing from BenchmarkStats should report benchmark.
TEST_F(AssertionOrBenchmarkResultTest_853,
       IsBenchmark_True_WhenConstructedWithBenchmark_853) {
    Catch::BenchmarkStats<> benchmark{};
    AssertionOrBenchmarkResult sut(benchmark);

    EXPECT_TRUE(sut.isBenchmark());
}

// Boundary/consistency: Multiple calls should be stable and side-effect free.
TEST_F(AssertionOrBenchmarkResultTest_853,
       IsBenchmark_MultipleCalls_AreConsistent_853) {
    {
        Catch::AssertionStats assertion{};
        AssertionOrBenchmarkResult sut(assertion);
        EXPECT_FALSE(sut.isBenchmark());
        EXPECT_FALSE(sut.isBenchmark()); // call again to verify stability
    }
    {
        Catch::BenchmarkStats<> benchmark{};
        AssertionOrBenchmarkResult sut(benchmark);
        EXPECT_TRUE(sut.isBenchmark());
        EXPECT_TRUE(sut.isBenchmark()); // call again to verify stability
    }
}

// Independence: Different instances constructed differently should not interfere.
TEST_F(AssertionOrBenchmarkResultTest_853,
       IsBenchmark_InstanceIndependence_853) {
    Catch::AssertionStats assertion{};
    Catch::BenchmarkStats<> benchmark{};

    AssertionOrBenchmarkResult a(assertion);
    AssertionOrBenchmarkResult b(benchmark);

    EXPECT_FALSE(a.isBenchmark());
    EXPECT_TRUE(b.isBenchmark());
}
