#include <gtest/gtest.h>

#include "Function.h"



class StitchingFunctionTest_379 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup code if needed

    }



    virtual void TearDown() {

        // Teardown code if needed

    }

};



TEST_F(StitchingFunctionTest_379, GetBoundsReturnsNonNullPointer_379) {

    Dict dict;

    RefRecursionChecker usedParents;

    StitchingFunction function(&dict, usedParents);

    const double* bounds = function.getBounds();

    EXPECT_NE(bounds, nullptr);

}



TEST_F(StitchingFunctionTest_379, GetNumFuncsReturnsNonNegativeValue_379) {

    Dict dict;

    RefRecursionChecker usedParents;

    StitchingFunction function(&dict, usedParents);

    int numFuncs = function.getNumFuncs();

    EXPECT_GE(numFuncs, 0);

}



TEST_F(StitchingFunctionTest_379, GetFuncReturnsNonNullPointerForValidIndex_379) {

    Dict dict;

    RefRecursionChecker usedParents;

    StitchingFunction function(&dict, usedParents);

    int numFuncs = function.getNumFuncs();

    if (numFuncs > 0) {

        const Function* func = function.getFunc(0);

        EXPECT_NE(func, nullptr);

    }

}



TEST_F(StitchingFunctionTest_379, GetFuncReturnsNullPointerForInvalidIndex_379) {

    Dict dict;

    RefRecursionChecker usedParents;

    StitchingFunction function(&dict, usedParents);

    int numFuncs = function.getNumFuncs();

    const Function* func = function.getFunc(numFuncs);

    EXPECT_EQ(func, nullptr);

}



TEST_F(StitchingFunctionTest_379, GetEncodeReturnsNonNullPointer_379) {

    Dict dict;

    RefRecursionChecker usedParents;

    StitchingFunction function(&dict, usedParents);

    const double* encode = function.getEncode();

    EXPECT_NE(encode, nullptr);

}



TEST_F(StitchingFunctionTest_379, GetScaleReturnsNonNullPointer_379) {

    Dict dict;

    RefRecursionChecker usedParents;

    StitchingFunction function(&dict, usedParents);

    const double* scale = function.getScale();

    EXPECT_NE(scale, nullptr);

}
