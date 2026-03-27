#include <gtest/gtest.h>

#include "Function.h"



class FunctionTest : public ::testing::Test {

protected:

    std::unique_ptr<Function> function;



    void SetUp() override {

        // Assuming a way to create a valid Function object for testing.

        // This is a placeholder as the actual creation logic is not provided.

        function = std::make_unique<Function>();

    }

};



TEST_F(FunctionTest_350, GetDomainMax_ValidIndex_ReturnsCorrectValue_350) {

    // Assuming domain values are set appropriately for testing.

    int index = 0;

    double expectedMax = 10.0; // Example value

    function->domain[index][1] = expectedMax;



    EXPECT_EQ(function->getDomainMax(index), expectedMax);

}



TEST_F(FunctionTest_350, GetDomainMax_OutOfBoundsIndex_ReturnsDefaultOrError_350) {

    int index = 32; // Out of bounds for a domain array of size 32



    // Assuming getDomainMax handles out-of-bounds gracefully.

    EXPECT_THROW(function->getDomainMax(index), std::out_of_range); // Example expectation

}



TEST_F(FunctionTest_350, GetDomainMax_ZeroIndex_ReturnsCorrectValue_350) {

    int index = 0;

    double expectedMax = 20.0; // Example value

    function->domain[index][1] = expectedMax;



    EXPECT_EQ(function->getDomainMax(index), expectedMax);

}



TEST_F(FunctionTest_350, GetDomainMax_LastIndex_ReturnsCorrectValue_350) {

    int index = 31;

    double expectedMax = 30.0; // Example value

    function->domain[index][1] = expectedMax;



    EXPECT_EQ(function->getDomainMax(index), expectedMax);

}
