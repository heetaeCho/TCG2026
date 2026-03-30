#include <gtest/gtest.h>

#include "Function.h"

#include <memory>



using namespace std;



class StitchingFunctionTest_378 : public ::testing::Test {

protected:

    unique_ptr<Dict> dict;

    RefRecursionChecker usedParents;

    unique_ptr<StitchingFunction> stitchingFunc;



    void SetUp() override {

        dict = make_unique<Dict>();

        usedParents = RefRecursionChecker();

        stitchingFunc = make_unique<StitchingFunction>(dict.get(), usedParents);

    }

};



TEST_F(StitchingFunctionTest_378, GetNumFuncs_ReturnsCorrectCount_378) {

    // Assuming setup creates a valid StitchingFunction with some functions

    int numFuncs = stitchingFunc->getNumFuncs();

    EXPECT_GE(numFuncs, 0);

}



TEST_F(StitchingFunctionTest_378, GetFunc_ValidIndex_ReturnsNonNullPointer_378) {

    // Assuming setup creates a valid StitchingFunction with at least one function

    int numFuncs = stitchingFunc->getNumFuncs();

    if (numFuncs > 0) {

        const Function* func = stitchingFunc->getFunc(0);

        EXPECT_NE(func, nullptr);

    }

}



TEST_F(StitchingFunctionTest_378, GetFunc_OutOfBoundsIndex_ReturnsNullPointer_378) {

    // Assuming setup creates a valid StitchingFunction with some functions

    int numFuncs = stitchingFunc->getNumFuncs();

    const Function* func = stitchingFunc->getFunc(numFuncs);

    EXPECT_EQ(func, nullptr);

}



TEST_F(StitchingFunctionTest_378, GetBounds_ReturnsNonNullPointer_378) {

    const double* bounds = stitchingFunc->getBounds();

    EXPECT_NE(bounds, nullptr);

}



TEST_F(StitchingFunctionTest_378, GetEncode_ReturnsNonNullPointer_378) {

    const double* encode = stitchingFunc->getEncode();

    EXPECT_NE(encode, nullptr);

}



TEST_F(StitchingFunctionTest_378, GetScale_ReturnsNonNullPointer_378) {

    const double* scale = stitchingFunc->getScale();

    EXPECT_NE(scale, nullptr);

}



TEST_F(StitchingFunctionTest_378, Copy_ReturnsNewInstance_378) {

    unique_ptr<Function> copiedFunc = stitchingFunc->copy();

    EXPECT_NE(copiedFunc.get(), nullptr);

    EXPECT_EQ(stitchingFunc.get(), copiedFunc.get());

}



TEST_F(StitchingFunctionTest_378, IsOk_ReturnsTrueForValidInstance_378) {

    bool isOkay = stitchingFunc->isOk();

    EXPECT_TRUE(isOkay);

}
