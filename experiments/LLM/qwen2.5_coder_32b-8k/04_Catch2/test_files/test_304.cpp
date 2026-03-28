#include <gtest/gtest.h>

#include "catch2/catch_totals.hpp"



using namespace Catch;



class CountsTest : public ::testing::Test {

protected:

    Counts counts;

};



TEST_F(CountsTest_304, DefaultConstructorInitializesZero_304) {

    EXPECT_EQ(counts.passed, 0);

    EXPECT_EQ(counts.failed, 0);

    EXPECT_EQ(counts.failedButOk, 0);

    EXPECT_EQ(counts.skipped, 0);

}



TEST_F(CountsTest_304, TotalReturnsSumOfAllCounts_304) {

    counts.passed = 1;

    counts.failed = 2;

    counts.failedButOk = 3;

    counts.skipped = 4;



    EXPECT_EQ(counts.total(), 10);

}



TEST_F(CountsTest_304, AllPassedReturnsTrueWhenOnlyPassedIsNonZero_304) {

    counts.passed = 5;

    EXPECT_TRUE(counts.allPassed());

}



TEST_F(CountsTest_304, AllPassedReturnsFalseWhenFailedOrSkippedIsNonZero_304) {

    counts.failed = 1;

    EXPECT_FALSE(counts.allPassed());



    counts.reset();

    counts.skipped = 1;

    EXPECT_FALSE(counts.allPassed());

}



TEST_F(CountsTest_304, AllOkReturnsTrueWhenNoFailedTests_304) {

    counts.passed = 5;

    counts.failedButOk = 2;

    EXPECT_TRUE(counts.allOk());

}



TEST_F(CountsTest_304, AllOkReturnsFalseWhenFailedIsNonZero_304) {

    counts.failed = 1;

    EXPECT_FALSE(counts.allOk());

}



TEST_F(CountsTest_304, OperatorPlusEqualAddsCountsCorrectly_304) {

    Counts other;

    other.passed = 1;

    other.failed = 2;

    other.failedButOk = 3;

    other.skipped = 4;



    counts += other;



    EXPECT_EQ(counts.passed, 1);

    EXPECT_EQ(counts.failed, 2);

    EXPECT_EQ(counts.failedButOk, 3);

    EXPECT_EQ(counts.skipped, 4);

}



TEST_F(CountsTest_304, OperatorMinusSubtractsCountsCorrectly_304) {

    Counts other;

    other.passed = 1;

    other.failed = 2;

    other.failedButOk = 3;

    other.skipped = 4;



    counts.passed = 5;

    counts.failed = 6;

    counts.failedButOk = 7;

    counts.skipped = 8;



    Counts result = counts - other;



    EXPECT_EQ(result.passed, 4);

    EXPECT_EQ(result.failed, 4);

    EXPECT_EQ(result.failedButOk, 4);

    EXPECT_EQ(result.skipped, 4);

}
