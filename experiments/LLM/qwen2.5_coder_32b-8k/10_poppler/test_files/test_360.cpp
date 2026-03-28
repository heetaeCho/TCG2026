#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Function.h"



using ::testing::Test;

using ::testing::Eq;



class SampledFunctionTest_360 : public Test {

protected:

    virtual void SetUp() override {

        // Setup code, if any, goes here.

    }



    virtual void TearDown() override {

        // Teardown code, if any, goes here.

    }

};



TEST_F(SampledFunctionTest_360, IsOkReturnsTrueWhenValid_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_TRUE(sampledFunc.isOk());

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, IsOkReturnsFalseWhenInvalid_360) {

    // Assuming there is a way to create an invalid SampledFunction

    Object* funcObj = new Object();  // Placeholder for actual invalid initialization

    Dict* dict = nullptr;  // Invalid dictionary pointer

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_FALSE(sampledFunc.isOk());

    delete funcObj;

}



TEST_F(SampledFunctionTest_360, GetSampleSizeReturnsCorrectValue_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_GE(sampledFunc.getSampleSize(0), 0);  // Assuming sample size cannot be negative

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, GetEncodeMinReturnsValidValue_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_NO_THROW(sampledFunc.getEncodeMin(0));

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, GetEncodeMaxReturnsValidValue_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_NO_THROW(sampledFunc.getEncodeMax(0));

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, GetDecodeMinReturnsValidValue_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_NO_THROW(sampledFunc.getDecodeMin(0));

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, GetDecodeMaxReturnsValidValue_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_NO_THROW(sampledFunc.getDecodeMax(0));

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, GetSamplesReturnsNonNullPointer_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_NE(sampledFunc.getSamples(), nullptr);

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, GetSampleNumberReturnsNonNegativeValue_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_GE(sampledFunc.getSampleNumber(), 0);  // Assuming sample number cannot be negative

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, CopyReturnsNonNullPointer_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_NE(sampledFunc.copy(), nullptr);

    delete funcObj;

    delete dict;

}



TEST_F(SampledFunctionTest_360, GetTypeReturnsValidType_360) {

    Object* funcObj = new Object();  // Assuming Object is a placeholder and does not require specific initialization

    Dict* dict = new Dict();

    SampledFunction sampledFunc(funcObj, dict);

    EXPECT_NO_THROW(sampledFunc.getType());

    delete funcObj;

    delete dict;

}
