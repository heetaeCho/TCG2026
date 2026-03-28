#include <gtest/gtest.h>
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/catch_assertion_result.h"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/catch_message.h"
#include "catch2/catch_assertion_info.h"
#include "catch2/internal/catch_result_type.h"
#include "catch2/catch_totals.h"

using namespace Catch;
using namespace Catch::Detail;

namespace {

// Helper to create a minimal AssertionStats
AssertionStats makeAssertionStats() {
    AssertionInfo info;
    info.lineInfo = SourceLineInfo("test.cpp", 1);
    info.macroName = "TEST";
    info.capturedExpression = "true";
    
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    
    AssertionResult result(info, data);
    return AssertionStats(result, std::vector<MessageInfo>{}, Totals{});
}

// Helper to create a minimal BenchmarkStats
BenchmarkStats<> makeBenchmarkStats() {
    Benchmark::BenchmarkInfo benchInfo{
        "test_benchmark",
        1.0,
        1,
        1,
        1,
        1
    };
    
    Benchmark::EstimateStats<> mean{1.0, 1.0, 1.0, 0.95};
    Benchmark::EstimateStats<> stddev{0.1, 0.1, 0.1, 0.95};
    Benchmark::EstimateStats<> outlierVariance{0.0, 0.0, 0.0, 0.95};
    
    return BenchmarkStats<>{
        benchInfo,
        mean,
        stddev,
        outlierVariance,
        0
    };
}

} // anonymous namespace

class AssertionOrBenchmarkResultTest_853 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing with AssertionStats marks it as an assertion
TEST_F(AssertionOrBenchmarkResultTest_853, ConstructWithAssertion_IsAssertion_853) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_TRUE(result.isAssertion());
}

// Test that constructing with AssertionStats does NOT mark it as a benchmark
TEST_F(AssertionOrBenchmarkResultTest_853, ConstructWithAssertion_IsNotBenchmark_853) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_FALSE(result.isBenchmark());
}

// Test that constructing with BenchmarkStats marks it as a benchmark
TEST_F(AssertionOrBenchmarkResultTest_853, ConstructWithBenchmark_IsBenchmark_853) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_TRUE(result.isBenchmark());
}

// Test that constructing with BenchmarkStats does NOT mark it as an assertion
TEST_F(AssertionOrBenchmarkResultTest_853, ConstructWithBenchmark_IsNotAssertion_853) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_FALSE(result.isAssertion());
}

// Test that asAssertion returns valid reference for assertion result
TEST_F(AssertionOrBenchmarkResultTest_853, AsAssertion_ReturnsValidReference_853) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_TRUE(result.isAssertion());
    const AssertionStats& retrieved = result.asAssertion();
    // Just verify we can access it without crashing
    (void)retrieved;
}

// Test that asBenchmark returns valid reference for benchmark result
TEST_F(AssertionOrBenchmarkResultTest_853, AsBenchmark_ReturnsValidReference_853) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_TRUE(result.isBenchmark());
    const BenchmarkStats<>& retrieved = result.asBenchmark();
    // Just verify we can access it without crashing
    (void)retrieved;
}

// Test mutual exclusivity - assertion result should not be benchmark
TEST_F(AssertionOrBenchmarkResultTest_853, MutualExclusivity_Assertion_853) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_TRUE(result.isAssertion());
    EXPECT_FALSE(result.isBenchmark());
}

// Test mutual exclusivity - benchmark result should not be assertion
TEST_F(AssertionOrBenchmarkResultTest_853, MutualExclusivity_Benchmark_853) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_FALSE(result.isAssertion());
    EXPECT_TRUE(result.isBenchmark());
}

// Test copy construction from assertion-based result
TEST_F(AssertionOrBenchmarkResultTest_853, CopyConstruction_Assertion_853) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult copy(original);
    
    EXPECT_TRUE(copy.isAssertion());
    EXPECT_FALSE(copy.isBenchmark());
}

// Test copy construction from benchmark-based result
TEST_F(AssertionOrBenchmarkResultTest_853, CopyConstruction_Benchmark_853) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult copy(original);
    
    EXPECT_TRUE(copy.isBenchmark());
    EXPECT_FALSE(copy.isAssertion());
}

// Test that asAssertion returns consistent data
TEST_F(AssertionOrBenchmarkResultTest_853, AsAssertion_DataConsistency_853) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    const AssertionStats& ref1 = result.asAssertion();
    const AssertionStats& ref2 = result.asAssertion();
    
    // Both should reference the same stored object
    EXPECT_EQ(&ref1, &ref2);
}

// Test that asBenchmark returns consistent data
TEST_F(AssertionOrBenchmarkResultTest_853, AsBenchmark_DataConsistency_853) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    const BenchmarkStats<>& ref1 = result.asBenchmark();
    const BenchmarkStats<>& ref2 = result.asBenchmark();
    
    // Both should reference the same stored object
    EXPECT_EQ(&ref1, &ref2);
}
