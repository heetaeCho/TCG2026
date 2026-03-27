#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Function.h"



class SampledFunctionTest_363 : public ::testing::Test {

protected:

    std::unique_ptr<SampledFunction> sampledFunction;



    void SetUp() override {

        // Assuming a mock or some way to create a valid SampledFunction object

        // Since we cannot access internal state, we assume proper initialization.

        // For the sake of this example, let's assume there is a constructor that initializes it properly.

        sampledFunction = std::make_unique<SampledFunction>(/* appropriate arguments */);

    }

};



TEST_F(SampledFunctionTest_363, GetEncodeMax_NormalOperation_363) {

    // Assuming we know some valid index for which the encode max value is defined

    int i = 0;

    double expectedValue = 1.0; // This value should be known from the setup or context

    EXPECT_DOUBLE_EQ(sampledFunction->getEncodeMax(i), expectedValue);

}



TEST_F(SampledFunctionTest_363, GetEncodeMax_BoundaryCondition_MinIndex_363) {

    int i = 0;

    double expectedValue = 1.0; // This value should be known from the setup or context

    EXPECT_DOUBLE_EQ(sampledFunction->getEncodeMax(i), expectedValue);

}



TEST_F(SampledFunctionTest_363, GetEncodeMax_BoundaryCondition_MaxIndex_363) {

    int i = 31; // Assuming funcMaxInputs is 32 and zero-indexed

    double expectedValue = 1.0; // This value should be known from the setup or context

    EXPECT_DOUBLE_EQ(sampledFunction->getEncodeMax(i), expectedValue);

}



TEST_F(SampledFunctionTest_363, GetEncodeMax_ExceptionalCase_OutOfBoundsIndex_363) {

    int i = 32; // Out of bounds index for funcMaxInputs which is 32

    EXPECT_THROW(sampledFunction->getEncodeMax(i), std::out_of_range); // Assuming it throws out_of_range or similar

}



// Additional tests can be added for other functions in the interface if required



TEST_F(SampledFunctionTest_363, GetEncodeMin_NormalOperation_363) {

    int i = 0;

    double expectedValue = 0.0; // This value should be known from the setup or context

    EXPECT_DOUBLE_EQ(sampledFunction->getEncodeMin(i), expectedValue);

}



TEST_F(SampledFunctionTest_363, GetSampleSize_NormalOperation_363) {

    int i = 0;

    int expectedValue = 1; // This value should be known from the setup or context

    EXPECT_EQ(sampledFunction->getSampleSize(i), expectedValue);

}



TEST_F(SampledFunctionTest_363, GetDecodeMin_NormalOperation_363) {

    int i = 0;

    double expectedValue = 0.0; // This value should be known from the setup or context

    EXPECT_DOUBLE_EQ(sampledFunction->getDecodeMin(i), expectedValue);

}



TEST_F(SampledFunctionTest_363, GetDecodeMax_NormalOperation_363) {

    int i = 0;

    double expectedValue = 1.0; // This value should be known from the setup or context

    EXPECT_DOUBLE_EQ(sampledFunction->getDecodeMax(i), expectedValue);

}



TEST_F(SampledFunctionTest_363, GetSamples_NormalOperation_363) {

    const double* samples = sampledFunction->getSamples();

    ASSERT_NE(samples, nullptr); // Assuming getSamples() should not return null if object is properly initialized

}



TEST_F(SampledFunctionTest_363, GetSampleNumber_NormalOperation_363) {

    int expectedValue = 1; // This value should be known from the setup or context

    EXPECT_EQ(sampledFunction->getSampleNumber(), expectedValue);

}

```


