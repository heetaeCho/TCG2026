#include <gtest/gtest.h>

#include "catch2/catch_totals.hpp"



using namespace Catch;



class TotalsTest_308 : public ::testing::Test {

protected:

    Totals totals1;

    Totals totals2;



    void SetUp() override {

        totals1.assertions = {5, 0, 0, 0};

        totals1.testCases = {3, 0, 0, 0};



        totals2.assertions = {2, 0, 0, 0};

        totals2.testCases = {1, 0, 0, 0};

    }

};



TEST_F(TotalsTest_308, OperatorMinus_NormalOperation_308) {

    Totals result = totals1 - totals2;

    EXPECT_EQ(result.assertions.passed, 3);

    EXPECT_EQ(result.testCases.passed, 2);

}



TEST_F(TotalsTest_308, OperatorMinus_BoundaryConditions_308) {

    Totals boundary_totals1;

    Totals boundary_totals2;



    Totals result = boundary_totals1 - boundary_totals2;

    EXPECT_EQ(result.assertions.total(), 0);

    EXPECT_EQ(result.testCases.total(), 0);



    boundary_totals1.assertions.passed = 1;

    result = boundary_totals1 - boundary_totals2;

    EXPECT_EQ(result.assertions.total(), 1);

}



TEST_F(TotalsTest_308, OperatorMinus_ExceptionalCases_308) {

    Totals large_totals1;

    Totals large_totals2;



    large_totals1.assertions.passed = UINT64_MAX;

    large_totals2.assertions.passed = 1;



    // Subtracting should wrap around due to unsigned integer underflow

    Totals result = large_totals1 - large_totals2;

    EXPECT_EQ(result.assertions.passed, UINT64_MAX - 1);

}



TEST_F(TotalsTest_308, Delta_NormalOperation_308) {

    Totals prevTotals;

    prevTotals.assertions = {3, 0, 0, 0};

    prevTotals.testCases = {1, 0, 0, 0};



    Totals result = totals1.delta(prevTotals);

    EXPECT_EQ(result.assertions.passed, 2);

    EXPECT_EQ(result.testCases.passed, 2);

}



TEST_F(TotalsTest_308, Delta_BoundaryConditions_308) {

    Totals initial_totals;

    Totals prev_totals;



    Totals result = initial_totals.delta(prev_totals);

    EXPECT_EQ(result.assertions.total(), 0);

    EXPECT_EQ(result.testCases.total(), 0);



    prev_totals.assertions.passed = 1;

    result = initial_totals.delta(prev_totals);

    EXPECT_EQ(result.assertions.total(), static_cast<std::uint64_t>(-1)); // Wrap around due to unsigned integer underflow

}



TEST_F(TotalsTest_308, Delta_ExceptionalCases_308) {

    Totals large_totals1;

    Totals large_totals2;



    large_totals1.assertions.passed = UINT64_MAX;

    large_totals2.assertions.passed = 1;



    // Subtracting should wrap around due to unsigned integer underflow

    Totals result = large_totals1.delta(large_totals2);

    EXPECT_EQ(result.assertions.passed, UINT64_MAX - 1);

}
