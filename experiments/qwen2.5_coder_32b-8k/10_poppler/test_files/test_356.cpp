#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Function.h"



using namespace testing;



class IdentityFunctionTest : public ::testing::Test {

protected:

    std::unique_ptr<IdentityFunction> identityFunction;



    void SetUp() override {

        identityFunction = std::make_unique<IdentityFunction>();

    }

};



TEST_F(IdentityFunctionTest_PutIncreasesCount_356, GetTypeReturnsIdentity_356) {

    EXPECT_EQ(identityFunction->getType(), Type::Identity);

}



TEST_F(IdentityFunctionTest_TransformBehavior_356, TransformCopiesInputsToOutputs_356) {

    double input[] = {1.0, 2.0, 3.0};

    double output[3];

    identityFunction->transform(input, output);

    for (size_t i = 0; i < 3; ++i) {

        EXPECT_DOUBLE_EQ(output[i], input[i]);

    }

}



TEST_F(IdentityFunctionTest_TransformBehavior_356, TransformHandlesZeroInputs_356) {

    double input[] = {0.0, 0.0, 0.0};

    double output[3];

    identityFunction->transform(input, output);

    for (size_t i = 0; i < 3; ++i) {

        EXPECT_DOUBLE_EQ(output[i], input[i]);

    }

}



TEST_F(IdentityFunctionTest_CopyBehavior_356, CopyCreatesNewInstance_356) {

    auto copy = identityFunction->copy();

    EXPECT_NE(copy.get(), identityFunction.get());

    EXPECT_EQ(copy->getType(), Type::Identity);

}



TEST_F(IdentityFunctionTest_IsOkBehavior_356, IsOkReturnsTrue_356) {

    EXPECT_TRUE(identityFunction->isOk());

}
