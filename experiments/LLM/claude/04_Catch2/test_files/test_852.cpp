#include <gtest/gtest.h>

// Include necessary Catch2 headers
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/catch_totals.hpp"

using namespace Catch;
using namespace Catch::Detail;

namespace {

// Helper to create a minimal AssertionStats
AssertionStats makeAssertionStats() {
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    AssertionResult result(AssertionInfo(), CATCH_MOVE(data));
    return AssertionStats(CATCH_MOVE(result), {}, {});
}

// Helper to create a minimal BenchmarkStats
BenchmarkStats<> makeBenchmarkStats() {
    Benchmark::BenchmarkInfo info{"test_benchmark", 0.0, 1, 1, 1, 1};
    Benchmark::BenchmarkStats<> stats{
        CATCH_MOVE(info),
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0.0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0.0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0.0}},
        {0.0, 0.0, 0.0, {0.0, 0.0, 0.0, 0.0}}
    };
    return stats;
}

} // anonymous namespace

class AssertionOrBenchmarkResultTest_852 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing with AssertionStats makes isAssertion() return true
TEST_F(AssertionOrBenchmarkResultTest_852, ConstructWithAssertion_IsAssertion_852) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_TRUE(result.isAssertion());
}

// Test that constructing with AssertionStats makes isBenchmark() return false
TEST_F(AssertionOrBenchmarkResultTest_852, ConstructWithAssertion_IsNotBenchmark_852) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_FALSE(result.isBenchmark());
}

// Test that constructing with BenchmarkStats makes isBenchmark() return true
TEST_F(AssertionOrBenchmarkResultTest_852, ConstructWithBenchmark_IsBenchmark_852) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_TRUE(result.isBenchmark());
}

// Test that constructing with BenchmarkStats makes isAssertion() return false
TEST_F(AssertionOrBenchmarkResultTest_852, ConstructWithBenchmark_IsNotAssertion_852) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_FALSE(result.isAssertion());
}

// Test that asAssertion() returns a valid reference when constructed with AssertionStats
TEST_F(AssertionOrBenchmarkResultTest_852, AsAssertionReturnsValidReference_852) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_NO_THROW({
        const auto& ref = result.asAssertion();
        (void)ref;
    });
}

// Test that asBenchmark() returns a valid reference when constructed with BenchmarkStats
TEST_F(AssertionOrBenchmarkResultTest_852, AsBenchmarkReturnsValidReference_852) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_NO_THROW({
        const auto& ref = result.asBenchmark();
        (void)ref;
    });
}

// Test copy construction with assertion-based result
TEST_F(AssertionOrBenchmarkResultTest_852, CopyConstructionAssertion_852) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult copy(original);
    EXPECT_TRUE(copy.isAssertion());
    EXPECT_FALSE(copy.isBenchmark());
}

// Test copy construction with benchmark-based result
TEST_F(AssertionOrBenchmarkResultTest_852, CopyConstructionBenchmark_852) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult copy(original);
    EXPECT_TRUE(copy.isBenchmark());
    EXPECT_FALSE(copy.isAssertion());
}

// Test move construction with assertion-based result
TEST_F(AssertionOrBenchmarkResultTest_852, MoveConstructionAssertion_852) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult moved(std::move(original));
    EXPECT_TRUE(moved.isAssertion());
    EXPECT_FALSE(moved.isBenchmark());
}

// Test move construction with benchmark-based result
TEST_F(AssertionOrBenchmarkResultTest_852, MoveConstructionBenchmark_852) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult original(stats);
    AssertionOrBenchmarkResult moved(std::move(original));
    EXPECT_TRUE(moved.isBenchmark());
    EXPECT_FALSE(moved.isAssertion());
}

// Test that isAssertion and isBenchmark are mutually exclusive for assertion construction
TEST_F(AssertionOrBenchmarkResultTest_852, MutualExclusivityAssertion_852) {
    auto stats = makeAssertionStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_NE(result.isAssertion(), result.isBenchmark());
}

// Test that isAssertion and isBenchmark are mutually exclusive for benchmark construction
TEST_F(AssertionOrBenchmarkResultTest_852, MutualExclusivityBenchmark_852) {
    auto stats = makeBenchmarkStats();
    AssertionOrBenchmarkResult result(stats);
    EXPECT_NE(result.isAssertion(), result.isBenchmark());
}
