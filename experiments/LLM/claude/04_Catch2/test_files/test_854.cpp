#include <gtest/gtest.h>
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/catch_assertion_result.h"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/catch_message.h"
#include "catch2/catch_totals.h"
#include "catch2/interfaces/catch_interfaces_config.h"

using namespace Catch;
using namespace Catch::Detail;

namespace {

// Helper to create a minimal AssertionStats
AssertionStats makeAssertionStats() {
    AssertionInfo info;
    info.lineInfo = SourceLineInfo("test.cpp", 1);
    info.macroName = "REQUIRE"_catch_sr;
    info.capturedExpression = "true"_catch_sr;
    info.resultDisposition = ResultDisposition::Normal;

    AssertionResultData data;
    data.resultType = ResultWas::Ok;

    AssertionResult result(info, std::move(data));
    return AssertionStats(result, std::vector<MessageInfo>{}, Totals{});
}

// Helper to create a minimal BenchmarkStats<>
BenchmarkStats<> makeBenchmarkStats() {
    Benchmark::BenchmarkInfo benchInfo{"test_benchmark", 1.0, 1, 1, 1, 1};
    Benchmark::EstimateStats<Benchmark::FDuration> mean = {Benchmark::FDuration(1.0), Benchmark::FDuration(0.9), Benchmark::FDuration(1.1), 0.95};
    Benchmark::EstimateStats<Benchmark::FDuration> standardDeviation = {Benchmark::FDuration(0.1), Benchmark::FDuration(0.05), Benchmark::FDuration(0.15), 0.95};
    Benchmark::EstimateStats<Benchmark::FDuration> outlierVariance = {Benchmark::FDuration(0.01), Benchmark::FDuration(0.005), Benchmark::FDuration(0.015), 0.95};
    
    return BenchmarkStats<>{
        benchInfo,
        mean,
        standardDeviation,
        outlierVariance,
        {Benchmark::FDuration(1.0), Benchmark::FDuration(1.1), Benchmark::FDuration(0.9)},
        0
    };
}

} // anonymous namespace

class AssertionOrBenchmarkResultTest_854 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test constructing with AssertionStats and verifying isAssertion returns true
TEST_F(AssertionOrBenchmarkResultTest_854, ConstructWithAssertion_IsAssertion_854) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_TRUE(result.isAssertion());
}

// Test constructing with AssertionStats and verifying isBenchmark returns false
TEST_F(AssertionOrBenchmarkResultTest_854, ConstructWithAssertion_IsNotBenchmark_854) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_FALSE(result.isBenchmark());
}

// Test constructing with BenchmarkStats and verifying isBenchmark returns true
TEST_F(AssertionOrBenchmarkResultTest_854, ConstructWithBenchmark_IsBenchmark_854) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_TRUE(result.isBenchmark());
}

// Test constructing with BenchmarkStats and verifying isAssertion returns false
TEST_F(AssertionOrBenchmarkResultTest_854, ConstructWithBenchmark_IsNotAssertion_854) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_FALSE(result.isAssertion());
}

// Test that asAssertion() returns a valid reference when constructed with AssertionStats
TEST_F(AssertionOrBenchmarkResultTest_854, AsAssertionReturnsValidReference_854) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NO_THROW({
        const AssertionStats& ref = result.asAssertion();
        (void)ref;
    });
}

// Test that asBenchmark() returns a valid reference when constructed with BenchmarkStats
TEST_F(AssertionOrBenchmarkResultTest_854, AsBenchmarkReturnsValidReference_854) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NO_THROW({
        const BenchmarkStats<>& ref = result.asBenchmark();
        (void)ref;
    });
}

// Test that asAssertion() returns data consistent with what was passed in
TEST_F(AssertionOrBenchmarkResultTest_854, AsAssertionReturnsConsistentData_854) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    const AssertionStats& ref = result.asAssertion();
    EXPECT_EQ(ref.assertionResult.isOk(), stats.assertionResult.isOk());
}

// Test that asBenchmark() returns data consistent with what was passed in
TEST_F(AssertionOrBenchmarkResultTest_854, AsBenchmarkReturnsConsistentData_854) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    const BenchmarkStats<>& ref = result.asBenchmark();
    EXPECT_EQ(ref.info.name, "test_benchmark");
}

// Test copy semantics - constructing from assertion, copying, and verifying both are assertions
TEST_F(AssertionOrBenchmarkResultTest_854, CopyAssertionResult_854) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    AssertionOrBenchmarkResult copy(result);
    
    EXPECT_TRUE(copy.isAssertion());
    EXPECT_FALSE(copy.isBenchmark());
}

// Test copy semantics - constructing from benchmark, copying, and verifying both are benchmarks
TEST_F(AssertionOrBenchmarkResultTest_854, CopyBenchmarkResult_854) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    AssertionOrBenchmarkResult copy(result);
    
    EXPECT_TRUE(copy.isBenchmark());
    EXPECT_FALSE(copy.isAssertion());
}

// Test that isAssertion and isBenchmark are mutually exclusive for assertion-constructed result
TEST_F(AssertionOrBenchmarkResultTest_854, MutuallyExclusiveForAssertion_854) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NE(result.isAssertion(), result.isBenchmark());
}

// Test that isAssertion and isBenchmark are mutually exclusive for benchmark-constructed result
TEST_F(AssertionOrBenchmarkResultTest_854, MutuallyExclusiveForBenchmark_854) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NE(result.isAssertion(), result.isBenchmark());
}
