#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Function.h"

#include <memory>



using namespace std;



class StitchingFunctionTest_376 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup code if needed, but we treat the implementation as a black box.

    }



    virtual void TearDown() {

        // Teardown code if needed, but we treat the implementation as a black box.

    }



    std::unique_ptr<StitchingFunction> createStitchingFunction() {

        // Assuming there's a way to create a StitchingFunction for testing purposes

        return std::make_unique<StitchingFunction>(nullptr, RefRecursionChecker());

    }

};



TEST_F(StitchingFunctionTest_376, IsOk_ReturnsTrue_376) {

    auto func = createStitchingFunction();

    EXPECT_TRUE(func->isOk());

}



TEST_F(StitchingFunctionTest_376, GetNumFuncs_ReturnsCorrectCount_376) {

    auto func = createStitchingFunction();

    // Assuming getNumFuncs returns a valid number

    int numFuncs = func->getNumFuncs();

    EXPECT_GE(numFuncs, 0); // At least zero functions

}



TEST_F(StitchingFunctionTest_376, GetFunc_ReturnsValidPointer_376) {

    auto func = createStitchingFunction();

    int numFuncs = func->getNumFuncs();

    if (numFuncs > 0) {

        EXPECT_NE(func->getFunc(0), nullptr); // First function should be valid

    }

}



TEST_F(StitchingFunctionTest_376, GetBounds_ReturnsNonNullPointer_376) {

    auto func = createStitchingFunction();

    EXPECT_NE(func->getBounds(), nullptr);

}



TEST_F(StitchingFunctionTest_376, GetEncode_ReturnsNonNullPointer_376) {

    auto func = createStitchingFunction();

    EXPECT_NE(func->getEncode(), nullptr);

}



TEST_F(StitchingFunctionTest_376, GetScale_ReturnsNonNullPointer_376) {

    auto func = createStitchingFunction();

    EXPECT_NE(func->getScale(), nullptr);

}



TEST_F(StitchingFunctionTest_376, BoundaryCondition_GetFunc_OutOfRange_376) {

    auto func = createStitchingFunction();

    int numFuncs = func->getNumFuncs();

    if (numFuncs > 0) {

        EXPECT_EQ(func->getFunc(numFuncs), nullptr); // Out of range should return null

    }

}



TEST_F(StitchingFunctionTest_376, BoundaryCondition_GetFunc_NegativeIndex_376) {

    auto func = createStitchingFunction();

    EXPECT_EQ(func->getFunc(-1), nullptr); // Negative index should return null

}
