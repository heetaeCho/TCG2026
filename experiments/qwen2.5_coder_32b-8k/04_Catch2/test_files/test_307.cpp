#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_totals.hpp"



class CountsTest_307 : public ::testing::Test {

protected:

    Catch::Counts counts;

};



TEST_F(CountsTest_307, AllOk_ReturnsTrueWhenNoFailedTests_307) {

    EXPECT_TRUE(counts.allOk());

}



TEST_F(CountsTest_307, AllOk_ReturnsFalseWhenThereAreFailedTests_307) {

    counts.failed = 1;

    EXPECT_FALSE(counts.allOk());

}



TEST_F(CountsTest_307, Total_ReturnsSumOfAllCounts_307) {

    counts.passed = 5;

    counts.failed = 2;

    counts.failedButOk = 1;

    counts.skipped = 3;

    EXPECT_EQ(counts.total(), 11);

}



TEST_F(CountsTest_307, Total_ReturnsZeroWhenAllCountsAreZero_307) {

    EXPECT_EQ(counts.total(), 0);

}



TEST_F(CountsTest_307, AllPassed_ReturnsTrueWhenNoFailedOrFailedButOkTests_307) {

    counts.passed = 5;

    counts.skipped = 3;

    EXPECT_TRUE(counts.allPassed());

}



TEST_F(CountsTest_307, AllPassed_ReturnsFalseWhenThereAreFailedTests_307) {

    counts.failed = 1;

    EXPECT_FALSE(counts.allPassed());

}



TEST_F(CountsTest_307, AllPassed_ReturnsFalseWhenThereAreFailedButOkTests_307) {

    counts.failedButOk = 1;

    EXPECT_FALSE(counts.allPassed());

}
