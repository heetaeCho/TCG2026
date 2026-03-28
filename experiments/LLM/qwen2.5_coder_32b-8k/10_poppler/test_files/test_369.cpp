#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Function.h"



using namespace testing;



class ExponentialFunctionTest : public ::testing::Test {

protected:

    Dict* dict;

    ExponentialFunction* expFunc;



    void SetUp() override {

        dict = new Dict(); // Assuming Dict constructor does not throw for simplicity

        expFunc = new ExponentialFunction(dict);

    }



    void TearDown() override {

        delete expFunc;

        delete dict;

    }

};



TEST_F(ExponentialFunctionTest_369, GetTypeReturnsExponential_369) {

    EXPECT_EQ(expFunc->getType(), Type::Exponential);

}



TEST_F(ExponentialFunctionTest_369, IsOkInitiallyTrue_369) {

    EXPECT_TRUE(expFunc->isOk());

}



TEST_F(ExponentialFunctionTest_369, GetC0ReturnsValidPointer_369) {

    EXPECT_NE(expFunc->getC0(), nullptr);

}



TEST_F(ExponentialFunctionTest_369, GetC1ReturnsValidPointer_369) {

    EXPECT_NE(expFunc->getC1(), nullptr);

}



TEST_F(ExponentialFunctionTest_369, GetEReturnsDefaultValue_369) {

    // Assuming default value of e is 1.0 if not specified in the Dict

    EXPECT_EQ(expFunc->getE(), 1.0);

}



TEST_F(ExponentialFunctionTest_369, TransformWithValidInputOutputsCorrectly_369) {

    double input[1] = {1.0};

    double output[1];

    expFunc->transform(input, output);

    // Assuming the transformation is y = e^x when c0 and c1 are default

    EXPECT_DOUBLE_EQ(output[0], std::exp(1.0));

}



TEST_F(ExponentialFunctionTest_369, CopyReturnsNewInstance_369) {

    auto copyFunc = expFunc->copy();

    EXPECT_NE(copyFunc.get(), expFunc);

    EXPECT_EQ(copyFunc->getType(), Type::Exponential);

    EXPECT_TRUE(copyFunc->isOk());

}



// Assuming exceptional cases or boundary conditions are not observable through the interface without additional context.

```


