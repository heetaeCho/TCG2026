#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxUnivariateShadingTest_511 : public ::testing::Test {

protected:

    std::vector<std::unique_ptr<Function>> funcs;

    GfxUnivariateShading shading;



    GfxUnivariateShadingTest_511()

        : shading(1, 0.0, 1.0, std::move(funcs), true, false) {}

};



TEST_F(GfxUnivariateShadingTest_511, GetExtend1_ReturnsCorrectValue_NormalOperation_511) {

    EXPECT_FALSE(shading.getExtend1());

}



TEST_F(GfxUnivariateShadingTest_511, GetDomain0_ReturnsExpectedValue_BoundaryConditions_511) {

    EXPECT_DOUBLE_EQ(0.0, shading.getDomain0());

}



TEST_F(GfxUnivariateShadingTest_511, GetDomain1_ReturnsExpectedValue_BoundaryConditions_511) {

    EXPECT_DOUBLE_EQ(1.0, shading.getDomain1());

}



TEST_F(GfxUnivariateShadingTest_511, GetExtend0_ReturnsCorrectValue_NormalOperation_511) {

    EXPECT_TRUE(shading.getExtend0());

}



// Assuming getNFuncs and getFunc are observable through some means

TEST_F(GfxUnivariateShadingTest_511, GetNFuncs_ReturnsZeroWhenNoFunctionsProvided_BoundaryConditions_511) {

    EXPECT_EQ(0, shading.getNFuncs());

}
