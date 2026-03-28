#include <gtest/gtest.h>

#include "catch_totals.hpp"



class CountsTest_303 : public ::testing::Test {

protected:

    Catch::Counts counts1;

    Catch::Counts counts2;



    void SetUp() override {

        counts1.passed = 5;

        counts1.failed = 2;

        counts1.failedButOk = 1;

        counts1.skipped = 0;



        counts2.passed = 3;

        counts2.failed = 1;

        counts2.failedButOk = 0;

        counts2.skipped = 1;

    }

};



TEST_F(CountsTest_303, OperatorMinus_NormalOperation_303) {

    Catch::Counts result = counts1 - counts2;



    EXPECT_EQ(result.passed, 2);

    EXPECT_EQ(result.failed, 1);

    EXPECT_EQ(result.failedButOk, 1);

    EXPECT_EQ(result.skipped, -1); // Assuming unsigned subtraction behavior

}



TEST_F(CountsTest_303, OperatorMinus_BoundaryCondition_303) {

    Catch::Counts zeroCounts;

    Catch::Counts result = counts1 - zeroCounts;



    EXPECT_EQ(result.passed, counts1.passed);

    EXPECT_EQ(result.failed, counts1.failed);

    EXPECT_EQ(result.failedButOk, counts1.failedButOk);

    EXPECT_EQ(result.skipped, counts1.skipped);



    result = zeroCounts - counts1;

    EXPECT_EQ(result.passed, 0); // Assuming underflow results in 0 for unsigned

    EXPECT_EQ(result.failed, 0);

    EXPECT_EQ(result.failedButOk, 0);

    EXPECT_EQ(result.skipped, 0);

}



TEST_F(CountsTest_303, OperatorPlusEqual_NormalOperation_303) {

    counts1 += counts2;



    EXPECT_EQ(counts1.passed, 8);

    EXPECT_EQ(counts1.failed, 3);

    EXPECT_EQ(counts1.failedButOk, 1);

    EXPECT_EQ(counts1.skipped, 1);

}



TEST_F(CountsTest_303, Total_NormalOperation_303) {

    EXPECT_EQ(counts1.total(), 8);

}



TEST_F(CountsTest_303, AllPassed_AllTestsPass_303) {

    counts1.failed = 0;

    counts1.failedButOk = 0;



    EXPECT_TRUE(counts1.allPassed());

}



TEST_F(CountsTest_303, AllPassed_SomeTestsFail_303) {

    EXPECT_FALSE(counts1.allPassed());



    counts1.failed = 0;

    counts1.failedButOk = 1;

    EXPECT_FALSE(counts1.allPassed());

}



TEST_F(CountsTest_303, AllOk_AllTestsPassOrAreFailedButOk_303) {

    counts1.failed = 0;



    EXPECT_TRUE(counts1.allOk());



    counts1.failedButOk = 2;

    EXPECT_TRUE(counts1.allOk());

}



TEST_F(CountsTest_303, AllOk_SomeTestsFail_303) {

    counts1.failedButOk = 0;

    EXPECT_FALSE(counts1.allOk());



    counts1.failedButOk = 1;

    counts1.failed = 1;

    EXPECT_FALSE(counts1.allOk());

}
