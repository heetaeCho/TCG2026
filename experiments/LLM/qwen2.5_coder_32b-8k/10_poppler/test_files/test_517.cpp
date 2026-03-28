#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



class GfxFunctionShadingTest : public ::testing::Test {

protected:

    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading;



    GfxFunctionShadingTest()

        : funcs(3),  // Assuming there are at least 3 functions for testing

          shading(0.0, 0.0, 1.0, 1.0, {0, 1, 0, 1, 0, 1}, std::move(funcs)) {

        // Initialize mock functions or any necessary setup

    }

};



TEST_F(GfxFunctionShadingTest_517, GetFuncValidIndex_517) {

    EXPECT_NE(shading.getFunc(0), nullptr);

    EXPECT_NE(shading.getFunc(1), nullptr);

    EXPECT_NE(shading.getFunc(2), nullptr);

}



TEST_F(GfxFunctionShadingTest_517, GetFuncBoundaryIndex_517) {

    int nFuncs = shading.getNFuncs();

    if (nFuncs > 0) {

        EXPECT_NE(shading.getFunc(0), nullptr);

        EXPECT_NE(shading.getFunc(nFuncs - 1), nullptr);

    }

}



TEST_F(GfxFunctionShadingTest_517, GetFuncOutOfRangeIndex_517) {

    int nFuncs = shading.getNFuncs();

    EXPECT_EQ(shading.getFunc(-1), nullptr);

    EXPECT_EQ(shading.getFunc(nFuncs), nullptr);

}
