#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



class GfxFunctionShadingTest_516 : public ::testing::Test {

protected:

    std::vector<std::unique_ptr<Function>> funcs;

    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;

    std::array<double, 6> matrix = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};



    void SetUp() override {

        funcs.push_back(std::make_unique<Function>());

        funcs.push_back(std::make_unique<Function>());

    }



    std::unique_ptr<GfxFunctionShading> createGfxFunctionShading(int numFuncs) {

        if (numFuncs == 1) {

            return std::make_unique<GfxFunctionShading>(x0, y0, x1, y1, matrix, std::vector<std::unique_ptr<Function>>{std::move(funcs[0])});

        } else {

            return std::make_unique<GfxFunctionShading>(x0, y0, x1, y1, matrix, std::move(funcs));

        }

    }

};



TEST_F(GfxFunctionShadingTest_516, GetNFuncs_ReturnsCorrectCount_516) {

    auto shading = createGfxFunctionShading(2);

    EXPECT_EQ(shading->getNFuncs(), 2);

}



TEST_F(GfxFunctionShadingTest_516, GetNFuncs_ReturnsZeroForEmptyFunctions_516) {

    std::vector<std::unique_ptr<Function>> emptyFuncs;

    auto shading = std::make_unique<GfxFunctionShading>(x0, y0, x1, y1, matrix, std::move(emptyFuncs));

    EXPECT_EQ(shading->getNFuncs(), 0);

}



TEST_F(GfxFunctionShadingTest_516, GetNFuncs_ReturnsOneForSingleFunction_516) {

    auto shading = createGfxFunctionShading(1);

    EXPECT_EQ(shading->getNFuncs(), 1);

}
