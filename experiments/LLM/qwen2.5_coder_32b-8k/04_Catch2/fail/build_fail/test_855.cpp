#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"

#include "catch2/internal/catch_optional.hpp"



using namespace Catch::Detail;

using ::testing::_;



class AssertionOrBenchmarkResultTest : public ::testing::Test {

protected:

    AssertionStats mockAssertionStats;

    BenchmarkStats<> mockBenchmarkStats;

};



TEST_F(AssertionOrBenchmarkResultTest_855, IsAssertionReturnsTrueForAssertion_855) {

    AssertionOrBenchmarkResult result(mockAssertionStats);

    EXPECT_TRUE(result.isAssertion());

}



TEST_F(AssertionOrBenchmarkResultTest_855, IsAssertionReturnsFalseForBenchmark_855) {

    AssertionOrBenchmarkResult result(mockBenchmarkStats);

    EXPECT_FALSE(result.isAssertion());

}



TEST_F(AssertionOrBenchmarkResultTest_855, IsBenchmarkReturnsTrueForBenchmark_855) {

    AssertionOrBenchmarkResult result(mockBenchmarkStats);

    EXPECT_TRUE(result.isBenchmark());

}



TEST_F(AssertionOrBenchmarkResultTest_855, IsBenchmarkReturnsFalseForAssertion_855) {

    AssertionOrBenchmarkResult result(mockAssertionStats);

    EXPECT_FALSE(result.isBenchmark());

}



TEST_F(AssertionOrBenchmarkResultTest_855, AsAssertionThrowsForBenchmark_855) {

    AssertionOrBenchmarkResult result(mockBenchmarkStats);

    EXPECT_THROW(result.asAssertion(), std::logic_error); // Assuming assertion would throw if accessed incorrectly

}



TEST_F(AssertionOrBenchmarkResultTest_855, AsBenchmarkThrowsForAssertion_855) {

    AssertionOrBenchmarkResult result(mockAssertionStats);

    EXPECT_THROW(result.asBenchmark(), std::logic_error); // Assuming benchmark would throw if accessed incorrectly

}



TEST_F(AssertionOrBenchmarkResultTest_855, AsAssertionReturnsCorrectValue_855) {

    AssertionOrBenchmarkResult result(mockAssertionStats);

    ASSERT_EQ(&result.asAssertion(), &mockAssertionStats);

}



TEST_F(AssertionOrBenchmarkResultTest_855, AsBenchmarkReturnsCorrectValue_855) {

    AssertionOrBenchmarkResult result(mockBenchmarkStats);

    ASSERT_EQ(&result.asBenchmark(), &mockBenchmarkStats);

}
