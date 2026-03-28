#include <gtest/gtest.h>

#include "Function.h"

#include <memory>



// Mock class for Object if needed

class MockObject {

    // Define necessary mock methods if any

};



// Mock class for Dict if needed

class MockDict {

    // Define necessary mock methods if any

};



class FunctionTest_352 : public ::testing::Test {

protected:

    std::unique_ptr<Function> function;



    void SetUp() override {

        // Initialize the function object with necessary setup

        function = std::make_unique<Function>();

    }

};



TEST_F(FunctionTest_352, GetRangeMax_NormalOperation_352) {

    // Setup: Assume function is initialized with some range values

    double expectedMax = 10.0;

    int index = 0; // Assuming the first element for simplicity



    // Mocking or setup if necessary

    // For now, assume internal state is set correctly



    // Exercise

    double result = function->getRangeMax(index);



    // Verify

    EXPECT_EQ(result, expectedMax);

}



TEST_F(FunctionTest_352, GetRangeMax_BoundaryCondition_ZeroIndex_352) {

    // Setup: Assume function is initialized with some range values

    double expectedMax = 10.0;

    int index = 0; // Boundary condition - zero index



    // Exercise

    double result = function->getRangeMax(index);



    // Verify

    EXPECT_EQ(result, expectedMax);

}



TEST_F(FunctionTest_352, GetRangeMax_BoundaryCondition_MaxIndex_352) {

    // Setup: Assume function is initialized with some range values

    double expectedMax = 20.0;

    int index = funcMaxOutputs - 1; // Boundary condition - max valid index



    // Exercise

    double result = function->getRangeMax(index);



    // Verify

    EXPECT_EQ(result, expectedMax);

}



TEST_F(FunctionTest_352, GetRangeMax_ExceptionalCase_OutOfBoundsIndex_352) {

    // Setup: Assume function is initialized with some range values

    int index = funcMaxOutputs; // Out of bounds index



    // Exercise and Verify

    EXPECT_THROW(function->getRangeMax(index), std::out_of_range);

}
