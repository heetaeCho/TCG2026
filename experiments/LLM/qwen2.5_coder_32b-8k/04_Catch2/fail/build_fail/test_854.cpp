#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"

#include "catch2/internal/catch_optional.hpp"



namespace Catch {

    struct AssertionStats {};

    template<typename> struct BenchmarkStats {};

}



using namespace Catch;

using namespace Catch::Detail;



class AssertionOrBenchmarkResultTest_854 : public ::testing::Test {

protected:

    AssertionStats testAssertionStats;

    BenchmarkStats<> testBenchmarkStats;

};



TEST_F(AssertionOrBenchmarkResultTest_854, IsAssertion_ReturnsTrueWhenInitializedWithAssertionStats_854) {

    AssertionOrBenchmarkResult result(testAssertionStats);

    EXPECT_TRUE(result.isAssertion());

}



TEST_F(AssertionOrBenchmarkResultTest_854, IsBenchmark_ReturnsFalseWhenInitializedWithAssertionStats_854) {

    AssertionOrBenchmarkResult result(testAssertionStats);

    EXPECT_FALSE(result.isBenchmark());

}



TEST_F(AssertionOrBenchmarkResultTest_854, AsAssertion_ReturnsValidAssertionStatsReference_854) {

    AssertionOrBenchmarkResult result(testAssertionStats);

    const AssertionStats& assertion = result.asAssertion();

    (void)assertion; // Just to ensure it compiles and returns a reference

}



TEST_F(AssertionOrBenchmarkResultTest_854, IsAssertion_ReturnsFalseWhenInitializedWithBenchmarkStats_854) {

    AssertionOrBenchmarkResult result(testBenchmarkStats);

    EXPECT_FALSE(result.isAssertion());

}



TEST_F(AssertionOrBenchmarkResultTest_854, IsBenchmark_ReturnsTrueWhenInitializedWithBenchmarkStats_854) {

    AssertionOrBenchmarkResult result(testBenchmarkStats);

    EXPECT_TRUE(result.isBenchmark());

}



TEST_F(AssertionOrBenchmarkResultTest_854, AsBenchmark_ReturnsValidBenchmarkStatsReference_854) {

    AssertionOrBenchmarkResult result(testBenchmarkStats);

    const BenchmarkStats<>& benchmark = result.asBenchmark();

    (void)benchmark; // Just to ensure it compiles and returns a reference

}
