#include <gtest/gtest.h>

#include "GfxState.h"



class GfxUnivariateShadingTest : public ::testing::Test {

protected:

    std::vector<std::unique_ptr<Function>> funcs;

    bool extend0 = true;

    bool extend1 = false;

    double t0 = 0.0;

    double t1 = 1.0;



    GfxUnivariateShading shading{5, t0, t1, std::move(funcs), extend0, extend1};



public:

    GfxUnivariateShadingTest() {

        // Initialize any necessary state before each test

    }



    ~GfxUnivariateShadingTest() override {

        // Clean up any state after each test if needed

    }

};



TEST_F(GfxUnivariateShadingTest_508, GetDomain0_ReturnsCorrectValue_508) {

    EXPECT_DOUBLE_EQ(shading.getDomain0(), t0);

}



TEST_F(GfxUnivariateShadingTest_508, GetDomain1_ReturnsCorrectValue_508) {

    EXPECT_DOUBLE_EQ(shading.getDomain1(), t1);

}



TEST_F(GfxUnivariateShadingTest_508, GetExtend0_ReturnsCorrectValue_508) {

    EXPECT_EQ(shading.getExtend0(), extend0);

}



TEST_F(GfxUnivariateShadingTest_508, GetExtend1_ReturnsCorrectValue_508) {

    EXPECT_EQ(shading.getExtend1(), extend1);

}
