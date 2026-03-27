#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_totals.hpp"



using namespace Catch;



class CountsTest_305 : public ::testing::Test {

protected:

    Counts counts;

};



TEST_F(CountsTest_305, TotalReturnsSumOfAllCounts_305) {

    counts.passed = 1;

    counts.failed = 2;

    counts.failedButOk = 3;

    counts.skipped = 4;

    EXPECT_EQ(counts.total(), 10);

}



TEST_F(CountsTest_305, TotalReturnsZeroWhenAllCountsAreZero_305) {

    EXPECT_EQ(counts.total(), 0);

}



TEST_F(CountsTest_305, AllPassedReturnsTrueWhenOnlyPassedIsNonZero_305) {

    counts.passed = 1;

    EXPECT_TRUE(counts.allPassed());

}



TEST_F(CountsTest_305, AllPassedReturnsFalseWhenFailedIsNonZero_305) {

    counts.failed = 1;

    EXPECT_FALSE(counts.allPassed());

}



TEST_F(CountsTest_305, AllPassedReturnsFalseWhenSkippedIsNonZero_305) {

    counts.skipped = 1;

    EXPECT_FALSE(counts.allPassed());

}



TEST_F(CountsTest_305, AllOkReturnsTrueWhenOnlyPassedAndFailedButOkAreNonZero_305) {

    counts.passed = 1;

    counts.failedButOk = 2;

    EXPECT_TRUE(counts.allOk());

}



TEST_F(CountsTest_305, AllOkReturnsFalseWhenFailedIsNonZero_305) {

    counts.failed = 1;

    EXPECT_FALSE(counts.allOk());

}



TEST_F(CountsTest_305, OperatorMinusSubtractsEachCountCorrectly_305) {

    Counts other;

    counts.passed = 4;

    counts.failed = 3;

    counts.failedButOk = 2;

    counts.skipped = 1;



    other.passed = 1;

    other.failed = 1;

    other.failedButOk = 1;

    other.skipped = 1;



    Counts result = counts - other;

    EXPECT_EQ(result.passed, 3);

    EXPECT_EQ(result.failed, 2);

    EXPECT_EQ(result.failedButOk, 1);

    EXPECT_EQ(result.skipped, 0);

}



TEST_F(CountsTest_305, OperatorPlusEqualsAddsEachCountCorrectly_305) {

    Counts other;

    counts.passed = 1;

    counts.failed = 2;

    counts.failedButOk = 3;

    counts.skipped = 4;



    other.passed = 4;

    other.failed = 3;

    other.failedButOk = 2;

    other.skipped = 1;



    counts += other;

    EXPECT_EQ(counts.passed, 5);

    EXPECT_EQ(counts.failed, 5);

    EXPECT_EQ(counts.failedButOk, 5);

    EXPECT_EQ(counts.skipped, 5);

}
