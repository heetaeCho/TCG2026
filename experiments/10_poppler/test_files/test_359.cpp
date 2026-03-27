#include <gtest/gtest.h>

#include "Function.h"

#include <memory>



using namespace poppler;



class SampledFunctionTest_359 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup any common objects or state here if necessary.

        // Since we cannot access internal state, this will be minimal.

    }



    virtual void TearDown() {

        // Cleanup any common objects or state here if necessary.

    }

};



TEST_F(SampledFunctionTest_359, GetType_ReturnsSampled_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    EXPECT_EQ(sampledFunc.getType(), Type::Sampled);

}



TEST_F(SampledFunctionTest_359, IsOk_ReturnsTrueForValidFunction_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    EXPECT_TRUE(sampledFunc.isOk());

}



TEST_F(SampledFunctionTest_359, Copy_ReturnsNewInstance_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    auto copiedFunc = sampledFunc.copy();

    EXPECT_NE(nullptr, copiedFunc.get());

}



TEST_F(SampledFunctionTest_359, GetSampleSize_ReturnsValidValue_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    int index = 0;  // Assuming valid index for sample size array

    EXPECT_GE(sampledFunc.getSampleSize(index), 1);  // Sample sizes should be positive

}



TEST_F(SampledFunctionTest_359, GetEncodeMin_ReturnsValidValue_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    int index = 0;  // Assuming valid index for encode array

    EXPECT_DOUBLE_EQ(sampledFunc.getEncodeMin(index), 0);  // Default or expected value

}



TEST_F(SampledFunctionTest_359, GetEncodeMax_ReturnsValidValue_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    int index = 0;  // Assuming valid index for encode array

    EXPECT_DOUBLE_EQ(sampledFunc.getEncodeMax(index), 1);  // Default or expected value

}



TEST_F(SampledFunctionTest_359, GetDecodeMin_ReturnsValidValue_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    int index = 0;  // Assuming valid index for decode array

    EXPECT_DOUBLE_EQ(sampledFunc.getDecodeMin(index), 0);  // Default or expected value

}



TEST_F(SampledFunctionTest_359, GetDecodeMax_ReturnsValidValue_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    int index = 0;  // Assuming valid index for decode array

    EXPECT_DOUBLE_EQ(sampledFunc.getDecodeMax(index), 1);  // Default or expected value

}



TEST_F(SampledFunctionTest_359, GetSamples_ReturnsNonnullptr_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    EXPECT_NE(sampledFunc.getSamples(), nullptr);

}



TEST_F(SampledFunctionTest_359, GetSampleNumber_ReturnsPositiveValue_359) {

    Object funcObj;  // Assuming Object and Dict are defined somewhere

    Dict dict;

    SampledFunction sampledFunc(&funcObj, &dict);

    EXPECT_GT(sampledFunc.getSampleNumber(), 0);  // Number of samples should be positive

}
