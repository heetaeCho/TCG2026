#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



class GfxUnivariateShadingTest : public ::testing::Test {

protected:

    std::vector<std::unique_ptr<Function>> funcs;

    GfxUnivariateShading* shading;



    void SetUp() override {

        funcs = {std::make_unique<Function>(), std::make_unique<Function>()}; // Assuming Function is a valid class

        shading = new GfxUnivariateShading(1, 0.0, 1.0, std::move(funcs), true, false);

    }



    void TearDown() override {

        delete shading;

    }

};



TEST_F(GfxUnivariateShadingTest_510, GetExtend0_ReturnsTrue_510) {

    EXPECT_TRUE(shading->getExtend0());

}



TEST_F(GfxUnivariateShadingTest_510, GetExtend0_ReturnsFalse_510) {

    GfxUnivariateShading* shadingFalse = new GfxUnivariateShading(1, 0.0, 1.0, std::move(funcs), false, true);

    EXPECT_FALSE(shadingFalse->getExtend0());

    delete shadingFalse;

}



TEST_F(GfxUnivariateShadingTest_510, GetExtend1_ReturnsTrue_510) {

    GfxUnivariateShading* shadingTrue = new GfxUnivariateShading(1, 0.0, 1.0, std::move(funcs), false, true);

    EXPECT_TRUE(shadingTrue->getExtend1());

    delete shadingTrue;

}



TEST_F(GfxUnivariateShadingTest_510, GetExtend1_ReturnsFalse_510) {

    EXPECT_FALSE(shading->getExtend1());

}
