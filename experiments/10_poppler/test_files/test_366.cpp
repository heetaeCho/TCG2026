#include <gtest/gtest.h>

#include "Function.h"

#include <memory>



class SampledFunctionTest_366 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a SampledFunction object for testing

        // Since we can't access the constructor parameters directly, this is a placeholder.

        // In practice, you would need a way to create a valid SampledFunction instance.

        // For the sake of this exercise, assume `createSampledFunction` is a function that returns a valid SampledFunction.

        sampleFunc = std::make_unique<SampledFunction>(/* appropriate parameters */);

    }



    void TearDown() override {

        sampleFunc.reset();

    }



    std::unique_ptr<SampledFunction> sampleFunc;

};



TEST_F(SampledFunctionTest_366, GetSamples_ReturnsValidPointer_366) {

    const double* samples = sampleFunc->getSamples();

    EXPECT_NE(samples, nullptr);

}



TEST_F(SampledFunctionTest_366, GetSampleSize_ReturnsNonNegativeValue_366) {

    for (int i = 0; i < funcMaxInputs; ++i) {

        int size = sampleFunc->getSampleSize(i);

        EXPECT_GE(size, 0);

    }

}



TEST_F(SampledFunctionTest_366, GetEncodeMin_ReturnsValidValue_366) {

    for (int i = 0; i < funcMaxInputs; ++i) {

        double min = sampleFunc->getEncodeMin(i);

        EXPECT_TRUE(std::isfinite(min));

    }

}



TEST_F(SampledFunctionTest_366, GetEncodeMax_ReturnsValidValue_366) {

    for (int i = 0; i < funcMaxInputs; ++i) {

        double max = sampleFunc->getEncodeMax(i);

        EXPECT_TRUE(std::isfinite(max));

    }

}



TEST_F(SampledFunctionTest_366, GetDecodeMin_ReturnsValidValue_366) {

    for (int i = 0; i < funcMaxOutputs; ++i) {

        double min = sampleFunc->getDecodeMin(i);

        EXPECT_TRUE(std::isfinite(min));

    }

}



TEST_F(SampledFunctionTest_366, GetDecodeMax_ReturnsValidValue_366) {

    for (int i = 0; i < funcMaxOutputs; ++i) {

        double max = sampleFunc->getDecodeMax(i);

        EXPECT_TRUE(std::isfinite(max));

    }

}



TEST_F(SampledFunctionTest_366, GetSampleNumber_ReturnsNonNegativeValue_366) {

    int nSamples = sampleFunc->getSampleNumber();

    EXPECT_GE(nSamples, 0);

}
