#include <gtest/gtest.h>

#include "catch_totals.hpp"



using namespace Catch;



class TotalsTest_310 : public ::testing::Test {

protected:

    Totals currentTotals;

    Totals prevTotals;

};



TEST_F(TotalsTest_310, DeltaNoChangeInAssertions_310) {

    // Arrange

    prevTotals.assertions = {0, 0, 0, 0};

    currentTotals.assertions = {0, 0, 0, 0};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.passed, 1);

}



TEST_F(TotalsTest_310, DeltaFailedAssertions_310) {

    // Arrange

    prevTotals.assertions = {0, 0, 0, 0};

    currentTotals.assertions = {0, 1, 0, 0};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.failed, 1);

}



TEST_F(TotalsTest_310, DeltaFailedButOkAssertions_310) {

    // Arrange

    prevTotals.assertions = {0, 0, 0, 0};

    currentTotals.assertions = {0, 0, 1, 0};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.failedButOk, 1);

}



TEST_F(TotalsTest_310, DeltaSkippedAssertions_310) {

    // Arrange

    prevTotals.assertions = {0, 0, 0, 0};

    currentTotals.assertions = {0, 0, 0, 1};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.skipped, 1);

}



TEST_F(TotalsTest_310, DeltaMixedAssertions_310) {

    // Arrange

    prevTotals.assertions = {0, 0, 0, 0};

    currentTotals.assertions = {1, 1, 1, 1};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.failed, 1);

}



TEST_F(TotalsTest_310, DeltaPrevHasMoreAssertions_310) {

    // Arrange

    prevTotals.assertions = {0, 2, 0, 0};

    currentTotals.assertions = {0, 1, 0, 0};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.failed, 1);

}



TEST_F(TotalsTest_310, DeltaOnlyPassedAssertions_310) {

    // Arrange

    prevTotals.assertions = {0, 0, 0, 0};

    currentTotals.assertions = {1, 0, 0, 0};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.passed, 1);

}



TEST_F(TotalsTest_310, DeltaBoundaryConditions_310) {

    // Arrange

    prevTotals.assertions = {0, 0, 0, 0};

    currentTotals.assertions = {std::numeric_limits<std::uint64_t>::max(), 0, 0, 0};



    // Act

    Totals diff = currentTotals.delta(prevTotals);



    // Assert

    EXPECT_EQ(diff.testCases.passed, 1);

}
