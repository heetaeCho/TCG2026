#include <gtest/gtest.h>
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_assertion_info.hpp"

using namespace Catch;
using namespace Catch::Detail;

namespace {

// Helper to create a minimal AssertionStats
AssertionStats makeAssertionStats() {
    AssertionInfo info;
    info.lineInfo = SourceLineInfo("test.cpp", 1);
    info.macroName = "TEST_CASE";
    info.capturedExpression = "true";
    
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    
    AssertionResult result(info, data);
    return AssertionStats(result, std::vector<MessageInfo>{}, Totals{});
}

// Helper to create a minimal BenchmarkStats<>
BenchmarkStats<> makeBenchmarkStats() {
    BenchmarkInfo benchInfo{ "test_benchmark", 0.0, 1, 1, 1, 1 };
    
    Benchmark::EstimateInfo<> mean = { {}, {}, {}, 0.0 };
    Benchmark::EstimateInfo<> stddev = { {}, {}, {}, 0.0 };
    Benchmark::OutlierClassification outliers = { 0, 0, 0, 0 };
    
    return BenchmarkStats<>{ benchInfo, mean, mean, stddev, outliers, 0.0 };
}

} // anonymous namespace

class AssertionOrBenchmarkResultTest_855 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing with AssertionStats marks it as assertion
TEST_F(AssertionOrBenchmarkResultTest_855, ConstructWithAssertion_IsAssertion_855) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_TRUE(result.isAssertion());
}

// Test that constructing with AssertionStats marks it as not benchmark
TEST_F(AssertionOrBenchmarkResultTest_855, ConstructWithAssertion_IsNotBenchmark_855) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_FALSE(result.isBenchmark());
}

// Test that constructing with BenchmarkStats marks it as benchmark
TEST_F(AssertionOrBenchmarkResultTest_855, ConstructWithBenchmark_IsBenchmark_855) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_TRUE(result.isBenchmark());
}

// Test that constructing with BenchmarkStats marks it as not assertion
TEST_F(AssertionOrBenchmarkResultTest_855, ConstructWithBenchmark_IsNotAssertion_855) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_FALSE(result.isAssertion());
}

// Test that asAssertion returns a valid reference when constructed with AssertionStats
TEST_F(AssertionOrBenchmarkResultTest_855, AsAssertionReturnsValidReference_855) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NO_THROW({
        const AssertionStats& ref = result.asAssertion();
        (void)ref;
    });
}

// Test that asBenchmark returns a valid reference when constructed with BenchmarkStats
TEST_F(AssertionOrBenchmarkResultTest_855, AsBenchmarkReturnsValidReference_855) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NO_THROW({
        const BenchmarkStats<>& ref = result.asBenchmark();
        (void)ref;
    });
}

// Test that isAssertion and isBenchmark are mutually exclusive for assertion construction
TEST_F(AssertionOrBenchmarkResultTest_855, MutuallyExclusiveForAssertion_855) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NE(result.isAssertion(), result.isBenchmark());
}

// Test that isAssertion and isBenchmark are mutually exclusive for benchmark construction
TEST_F(AssertionOrBenchmarkResultTest_855, MutuallyExclusiveForBenchmark_855) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    EXPECT_NE(result.isAssertion(), result.isBenchmark());
}

// Test copy semantics - constructing from assertion and copying
TEST_F(AssertionOrBenchmarkResultTest_855, CopyConstructionFromAssertion_855) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult copy(original);
    
    EXPECT_TRUE(copy.isAssertion());
    EXPECT_FALSE(copy.isBenchmark());
}

// Test copy semantics - constructing from benchmark and copying
TEST_F(AssertionOrBenchmarkResultTest_855, CopyConstructionFromBenchmark_855) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult copy(original);
    
    EXPECT_TRUE(copy.isBenchmark());
    EXPECT_FALSE(copy.isAssertion());
}

// Test that asBenchmark on assertion-constructed object would fail (death test)
TEST_F(AssertionOrBenchmarkResultTest_855, AsBenchmarkOnAssertionDies_855) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    
    // The implementation uses assert(), which should abort when calling asBenchmark on an assertion result
    EXPECT_DEATH({
        result.asBenchmark();
    }, "");
}

// Test that asAssertion on benchmark-constructed object would fail (death test)
TEST_F(AssertionOrBenchmarkResultTest_855, AsAssertionOnBenchmarkDies_855) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    
    // The implementation uses assert(), which should abort when calling asAssertion on a benchmark result
    EXPECT_DEATH({
        result.asAssertion();
    }, "");
}
