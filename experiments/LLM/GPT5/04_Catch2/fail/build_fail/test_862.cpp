// File: tests/section_node_hasAnyAssertions_862.tests.cpp

#include <gtest/gtest.h>

// Include the public interface under test.
// Adjust include paths as appropriate for your project layout.
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"

using Catch::CumulativeReporterBase;
using Catch::Detail::AssertionOrBenchmarkResult;

namespace {

// Small helpers to keep tests readable without touching internal logic.
static AssertionOrBenchmarkResult makeAssertion(const Catch::AssertionStats& s) {
    return AssertionOrBenchmarkResult(s);
}
static AssertionOrBenchmarkResult makeBenchmark(const Catch::BenchmarkStats<>& s) {
    return AssertionOrBenchmarkResult(s);
}

} // namespace

// Test fixture kept minimal; no internal state assumptions.
class SectionNodeHasAnyAssertionsTest_862 : public ::testing::Test {
protected:
    // Create a SectionNode with default-constructed SectionStats (public type).
    CumulativeReporterBase::SectionNode makeNode() {
        Catch::SectionStats stats{}; // rely on public, default-constructible interface
        return CumulativeReporterBase::SectionNode(stats);
    }
};

// [Normal] Empty container => false
TEST_F(SectionNodeHasAnyAssertionsTest_862, EmptyReturnsFalse_862) {
    auto node = makeNode();
    EXPECT_FALSE(node.hasAnyAssertions());
}

// [Boundary] Only benchmarks present => false
TEST_F(SectionNodeHasAnyAssertionsTest_862, AllBenchmarksReturnsFalse_862) {
    auto node = makeNode();

    Catch::BenchmarkStats<> b1{};
    Catch::BenchmarkStats<> b2{};

    node.assertionsAndBenchmarks.push_back(makeBenchmark(b1));
    node.assertionsAndBenchmarks.push_back(makeBenchmark(b2));

    EXPECT_FALSE(node.hasAnyAssertions());
}

// [Normal] Single assertion present => true
TEST_F(SectionNodeHasAnyAssertionsTest_862, SingleAssertionReturnsTrue_862) {
    auto node = makeNode();

    Catch::AssertionStats a{};
    node.assertionsAndBenchmarks.push_back(makeAssertion(a));

    EXPECT_TRUE(node.hasAnyAssertions());
}

// [Normal] Mixed (benchmarks + assertions) => true
TEST_F(SectionNodeHasAnyAssertionsTest_862, MixedEntriesReturnsTrue_862) {
    auto node = makeNode();

    Catch::BenchmarkStats<> b{};
    Catch::AssertionStats a{};

    node.assertionsAndBenchmarks.push_back(makeBenchmark(b));
    node.assertionsAndBenchmarks.push_back(makeAssertion(a));
    node.assertionsAndBenchmarks.push_back(makeBenchmark(b));

    EXPECT_TRUE(node.hasAnyAssertions());
}

// [Additional sanity] Multiple assertions => true
TEST_F(SectionNodeHasAnyAssertionsTest_862, MultipleAssertionsReturnsTrue_862) {
    auto node = makeNode();

    Catch::AssertionStats a1{};
    Catch::AssertionStats a2{};

    node.assertionsAndBenchmarks.push_back(makeAssertion(a1));
    node.assertionsAndBenchmarks.push_back(makeAssertion(a2));

    EXPECT_TRUE(node.hasAnyAssertions());
}
