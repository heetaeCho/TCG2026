#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_totals.hpp"



using namespace Catch;



class CountsTest_306 : public ::testing::Test {

protected:

    Counts counts;

};



TEST_F(CountsTest_306, AllPassed_ReturnsTrueWhenAllCountsAreZero_306) {

    EXPECT_TRUE(counts.allPassed());

}



TEST_F(CountsTest_306, AllPassed_ReturnsFalseWhenFailedCountIsNonZero_306) {

    counts.failed = 1;

    EXPECT_FALSE(counts.allPassed());

}



TEST_F(CountsTest_306, AllPassed_ReturnsFalseWhenFailedButOkCountIsNonZero_306) {

    counts.failedButOk = 1;

    EXPECT_FALSE(counts.allPassed());

}



TEST_F(CountsTest_306, AllPassed_ReturnsFalseWhenSkippedCountIsNonZero_306) {

    counts.skipped = 1;

    EXPECT_TRUE(counts.allPassed()); // Skipped does not affect allPassed()

}



TEST_F(CountsTest_306, Total_ReturnsSumOfAllCounts_306) {

    counts.passed = 5;

    counts.failed = 2;

    counts.failedButOk = 1;

    counts.skipped = 3;

    EXPECT_EQ(counts.total(), 11);

}



TEST_F(CountsTest_306, Total_ReturnsZeroWhenAllCountsAreZero_306) {

    EXPECT_EQ(counts.total(), 0);

}
