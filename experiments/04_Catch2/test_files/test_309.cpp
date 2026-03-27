#include <gtest/gtest.h>

#include "catch_totals.hpp"



using namespace Catch;



class TotalsTest : public ::testing::Test {

protected:

    Totals totals1;

    Totals totals2;

    Totals totals3;



    void SetUp() override {

        totals1.assertions = {1, 0, 0, 0};

        totals1.testCases = {5, 0, 0, 0};



        totals2.assertions = {2, 1, 1, 1};

        totals2.testCases = {3, 1, 1, 1};



        totals3.assertions = {0, 0, 0, 0};

        totals3.testCases = {0, 0, 0, 0};

    }

};



TEST_F(TotalsTest_309, OperatorPlusEqualsUpdatesAssertionsAndTestCases_309) {

    Totals result = totals1;

    result += totals2;



    EXPECT_EQ(result.assertions.passed, 3);

    EXPECT_EQ(result.assertions.failed, 1);

    EXPECT_EQ(result.assertions.failedButOk, 1);

    EXPECT_EQ(result.assertions.skipped, 1);



    EXPECT_EQ(result.testCases.passed, 8);

    EXPECT_EQ(result.testCases.failed, 1);

    EXPECT_EQ(result.testCases.failedButOk, 1);

    EXPECT_EQ(result.testCases.skipped, 1);

}



TEST_F(TotalsTest_309, OperatorPlusEqualsWithZeroDoesNotChangeValues_309) {

    Totals result = totals1;

    result += totals3;



    EXPECT_EQ(result.assertions.passed, 1);

    EXPECT_EQ(result.assertions.failed, 0);

    EXPECT_EQ(result.assertions.failedButOk, 0);

    EXPECT_EQ(result.assertions.skipped, 0);



    EXPECT_EQ(result.testCases.passed, 5);

    EXPECT_EQ(result.testCases.failed, 0);

    EXPECT_EQ(result.testCases.failedButOk, 0);

    EXPECT_EQ(result.testCases.skipped, 0);

}



TEST_F(TotalsTest_309, OperatorPlusEqualsWithSelfDoublesValues_309) {

    Totals result = totals1;

    result += totals1;



    EXPECT_EQ(result.assertions.passed, 2);

    EXPECT_EQ(result.assertions.failed, 0);

    EXPECT_EQ(result.assertions.failedButOk, 0);

    EXPECT_EQ(result.assertions.skipped, 0);



    EXPECT_EQ(result.testCases.passed, 10);

    EXPECT_EQ(result.testCases.failed, 0);

    EXPECT_EQ(result.testCases.failedButOk, 0);

    EXPECT_EQ(result.testCases.skipped, 0);

}



TEST_F(TotalsTest_309, DeltaCalculatesDifferenceInAssertionsAndTestCases_309) {

    Totals result = totals1 - totals2;



    EXPECT_EQ(result.assertions.passed, static_cast<std::uint64_t>(-1));

    EXPECT_EQ(result.assertions.failed, static_cast<std::uint64_t>(-1));

    EXPECT_EQ(result.assertions.failedButOk, static_cast<std::uint64_t>(-1));

    EXPECT_EQ(result.assertions.skipped, static_cast<std::uint64_t>(-1));



    EXPECT_EQ(result.testCases.passed, 2);

    EXPECT_EQ(result.testCases.failed, static_cast<std::uint64_t>(-1));

    EXPECT_EQ(result.testCases.failedButOk, static_cast<std::uint64_t>(-1));

    EXPECT_EQ(result.testCases.skipped, static_cast<std::uint64_t>(-1));

}



TEST_F(TotalsTest_309, DeltaWithSelfResultsInZeroValues_309) {

    Totals result = totals1 - totals1;



    EXPECT_EQ(result.assertions.passed, 0);

    EXPECT_EQ(result.assertions.failed, 0);

    EXPECT_EQ(result.assertions.failedButOk, 0);

    EXPECT_EQ(result.assertions.skipped, 0);



    EXPECT_EQ(result.testCases.passed, 0);

    EXPECT_EQ(result.testCases.failed, 0);

    EXPECT_EQ(result.testCases.failedButOk, 0);

    EXPECT_EQ(result.testCases.skipped, 0);

}



TEST_F(TotalsTest_309, DeltaWithZeroResultsInOriginalValues_309) {

    Totals result = totals1 - totals3;



    EXPECT_EQ(result.assertions.passed, 1);

    EXPECT_EQ(result.assertions.failed, 0);

    EXPECT_EQ(result.assertions.failedButOk, 0);

    EXPECT_EQ(result.assertions.skipped, 0);



    EXPECT_EQ(result.testCases.passed, 5);

    EXPECT_EQ(result.testCases.failed, 0);

    EXPECT_EQ(result.testCases.failedButOk, 0);

    EXPECT_EQ(result.testCases.skipped, 0);

}
