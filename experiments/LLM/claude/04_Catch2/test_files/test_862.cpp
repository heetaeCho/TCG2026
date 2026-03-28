#include "gtest/gtest.h"
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_totals.hpp"

#include <vector>
#include <string>

using namespace Catch;

namespace {

// Helper to create a minimal SectionStats
SectionStats makeSectionStats() {
    SectionInfo info("", "test section");
    Counts assertions;
    double durationInSeconds = 0.0;
    bool missingAssertions = false;
    return SectionStats(info, assertions, durationInSeconds, missingAssertions);
}

// Helper to create a minimal AssertionStats
AssertionStats makeAssertionStats() {
    AssertionInfo info;
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    AssertionResult result(info, std::move(data));
    return AssertionStats(result, std::vector<MessageInfo>{}, Totals{});
}

// Helper to create a minimal BenchmarkStats
BenchmarkStats<> makeBenchmarkStats() {
    Benchmark::BenchmarkInfo benchInfo{"bench", 0.0, 1, 1, 1, 1};
    Benchmark::EstimateInfo mean{0.0, 0.0, 0.0, 0.0};
    Benchmark::EstimateInfo stddev{0.0, 0.0, 0.0, 0.0};
    Benchmark::OutlierClassification outliers{0, 0, 0, 0};
    std::vector<Benchmark::SampleTimes<>> samples;
    return BenchmarkStats<>{benchInfo, mean, mean, stddev, outliers, 0.0};
}

} // namespace

class SectionNodeTest_862 : public ::testing::Test {
protected:
    SectionStats stats = makeSectionStats();
};

// Test that an empty SectionNode has no assertions
TEST_F(SectionNodeTest_862, EmptyNode_HasNoAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    EXPECT_FALSE(node.hasAnyAssertions());
}

// Test that a SectionNode with only benchmark results has no assertions
TEST_F(SectionNodeTest_862, OnlyBenchmarks_HasNoAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    EXPECT_FALSE(node.hasAnyAssertions());
}

// Test that a SectionNode with one assertion returns true
TEST_F(SectionNodeTest_862, OneAssertion_HasAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks.emplace_back(makeAssertionStats());
    EXPECT_TRUE(node.hasAnyAssertions());
}

// Test that a SectionNode with multiple assertions returns true
TEST_F(SectionNodeTest_862, MultipleAssertions_HasAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks.emplace_back(makeAssertionStats());
    node.assertionsAndBenchmarks.emplace_back(makeAssertionStats());
    node.assertionsAndBenchmarks.emplace_back(makeAssertionStats());
    EXPECT_TRUE(node.hasAnyAssertions());
}

// Test that a SectionNode with mixed benchmarks and assertions returns true
TEST_F(SectionNodeTest_862, MixedBenchmarksAndAssertions_HasAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    node.assertionsAndBenchmarks.emplace_back(makeAssertionStats());
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    EXPECT_TRUE(node.hasAnyAssertions());
}

// Test that a SectionNode with multiple benchmarks and no assertions returns false
TEST_F(SectionNodeTest_862, MultipleBenchmarksOnly_HasNoAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    EXPECT_FALSE(node.hasAnyAssertions());
}

// Test that assertion at the beginning of the list is detected
TEST_F(SectionNodeTest_862, AssertionAtBeginning_HasAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks.emplace_back(makeAssertionStats());
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    EXPECT_TRUE(node.hasAnyAssertions());
}

// Test that assertion at the end of the list is detected
TEST_F(SectionNodeTest_862, AssertionAtEnd_HasAssertions_862) {
    CumulativeReporterBase::SectionNode node(stats);
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    node.assertionsAndBenchmarks.emplace_back(makeBenchmarkStats());
    node.assertionsAndBenchmarks.emplace_back(makeAssertionStats());
    EXPECT_TRUE(node.hasAnyAssertions());
}

// Test AssertionOrBenchmarkResult isAssertion and isBenchmark
TEST_F(SectionNodeTest_862, AssertionOrBenchmarkResult_IsAssertion_862) {
    Detail::AssertionOrBenchmarkResult result(makeAssertionStats());
    EXPECT_TRUE(result.isAssertion());
    EXPECT_FALSE(result.isBenchmark());
}

TEST_F(SectionNodeTest_862, AssertionOrBenchmarkResult_IsBenchmark_862) {
    Detail::AssertionOrBenchmarkResult result(makeBenchmarkStats());
    EXPECT_FALSE(result.isAssertion());
    EXPECT_TRUE(result.isBenchmark());
}
