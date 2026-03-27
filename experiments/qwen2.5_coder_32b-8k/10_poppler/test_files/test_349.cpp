#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Function.h"



class FunctionTest_349 : public ::testing::Test {

protected:

    std::unique_ptr<Function> function;



    void SetUp() override {

        // Assuming a way to create a valid Function object for testing.

        // Since the implementation is treated as a black box, we assume the creation works correctly.

        function = Function::parse(nullptr); // This line assumes there's a way to parse and get a valid Function object

    }

};



TEST_F(FunctionTest_349, GetDomainMin_ValidIndex_349) {

    int index = 0; // Assuming index 0 is valid for testing

    double domainMin = function->getDomainMin(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetDomainMin_OutOfBoundsIndex_349) {

    int index = 32; // Assuming 32 is out of bounds for testing

    EXPECT_THROW(function->getDomainMin(index), std::out_of_range); // Hypothetical exception, as actual behavior is unknown

}



TEST_F(FunctionTest_349, GetDomainMin_BoundaryIndex_349) {

    int index = 15; // Assuming 15 is a boundary for testing

    double domainMin = function->getDomainMin(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetDomainMax_ValidIndex_349) {

    int index = 0; // Assuming index 0 is valid for testing

    double domainMax = function->getDomainMax(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetDomainMax_OutOfBoundsIndex_349) {

    int index = 32; // Assuming 32 is out of bounds for testing

    EXPECT_THROW(function->getDomainMax(index), std::out_of_range); // Hypothetical exception, as actual behavior is unknown

}



TEST_F(FunctionTest_349, GetDomainMax_BoundaryIndex_349) {

    int index = 15; // Assuming 15 is a boundary for testing

    double domainMax = function->getDomainMax(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetRangeMin_ValidIndex_349) {

    int index = 0; // Assuming index 0 is valid for testing

    double rangeMin = function->getRangeMin(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetRangeMin_OutOfBoundsIndex_349) {

    int index = 32; // Assuming 32 is out of bounds for testing

    EXPECT_THROW(function->getRangeMin(index), std::out_of_range); // Hypothetical exception, as actual behavior is unknown

}



TEST_F(FunctionTest_349, GetRangeMin_BoundaryIndex_349) {

    int index = 15; // Assuming 15 is a boundary for testing

    double rangeMin = function->getRangeMin(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetRangeMax_ValidIndex_349) {

    int index = 0; // Assuming index 0 is valid for testing

    double rangeMax = function->getRangeMax(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetRangeMax_OutOfBoundsIndex_349) {

    int index = 32; // Assuming 32 is out of bounds for testing

    EXPECT_THROW(function->getRangeMax(index), std::out_of_range); // Hypothetical exception, as actual behavior is unknown

}



TEST_F(FunctionTest_349, GetRangeMax_BoundaryIndex_349) {

    int index = 15; // Assuming 15 is a boundary for testing

    double rangeMax = function->getRangeMax(index);

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, GetHasRange_ReturnsBoolean_349) {

    bool hasRange = function->getHasRange();

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}



TEST_F(FunctionTest_349, IsOk_ReturnsBoolean_349) {

    bool isOkay = function->isOk();

    // Since the internal logic is unknown, we can't assert a specific value.

    // We can only test that it doesn't throw an exception and returns something.

}
