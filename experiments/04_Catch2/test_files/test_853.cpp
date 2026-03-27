#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"



using namespace Catch;

using namespace Catch::Detail;



class AssertionOrBenchmarkResultTest_853 : public ::testing::Test {

protected:

    AssertionStats assertionStats;

    BenchmarkStats<> benchmarkStats;

};



TEST_F(AssertionOrBenchmarkResultTest_853, isAssertion_ReturnsTrueForAssertion_853) {

    AssertionOrBenchmarkResult result(assertionStats);

    EXPECT_TRUE(result.isAssertion());

}



TEST_F(AssertionOrBenchmarkResultTest_853, isAssertion_ReturnsFalseForBenchmark_853) {

    AssertionOrBenchmarkResult result(benchmarkStats);

    EXPECT_FALSE(result.isAssertion());

}



TEST_F(AssertionOrBenchmarkResultTest_853, isBenchmark_ReturnsTrueForBenchmark_853) {

    AssertionOrBenchmarkResult result(benchmarkStats);

    EXPECT_TRUE(result.isBenchmark());

}



TEST_F(AssertionOrBenchmarkResultTest_853, isBenchmark_ReturnsFalseForAssertion_853) {

    AssertionOrBenchmarkResult result(assertionStats);

    EXPECT_FALSE(result.isBenchmark());

}



TEST_F(AssertionOrBenchmarkResultTest_853, asAssertion_ThrowsForBenchmark_853) {

    AssertionOrBenchmarkResult result(benchmarkStats);

    EXPECT_THROW(result.asAssertion(), std::logic_error);

}



TEST_F(AssertionOrBenchmarkResultTest_853, asBenchmark_ThrowsForAssertion_853) {

    AssertionOrBenchmarkResult result(assertionStats);

    EXPECT_THROW(result.asBenchmark(), std::logic_error);

}
