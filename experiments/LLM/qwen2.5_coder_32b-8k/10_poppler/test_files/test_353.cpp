#include <gtest/gtest.h>

#include "Function.h"



// Mock classes and dependencies (if needed) can be defined here.

// For this particular class, there are no external collaborators to mock.



class FunctionTest_353 : public ::testing::Test {

protected:

    // Setup and teardown if necessary can be done here.

    std::unique_ptr<Function> function;



    void SetUp() override {

        // Initialize the Function object before each test

        function = std::make_unique<Function>();

    }



    void TearDown() override {

        // Clean up after each test if necessary

    }

};



// Test cases for normal operation



TEST_F(FunctionTest_353, GetHasRange_ReturnsFalseByDefault_353) {

    EXPECT_FALSE(function->getHasRange());

}



// Test cases for boundary conditions



// No specific boundary conditions are applicable to bool getHasRange() const.



// Test cases for exceptional or error cases



// No observable error conditions through the interface for bool getHasRange() const.



// Verification of external interactions



// No external interactions to verify for bool getHasRange() const.
