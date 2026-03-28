#include <gtest/gtest.h>

#include "GfxState.h"



class GfxFunctionShadingTest_515 : public ::testing::Test {

protected:

    std::array<double, 6> matrix = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

    double x0 = 0.0;

    double y0 = 0.0;

    double x1 = 10.0;

    double y1 = 10.0;

    std::vector<std::unique_ptr<Function>> funcs;



    GfxFunctionShading shading{x0, y0, x1, y1, matrix, std::move(funcs)};



public:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(GfxFunctionShadingTest_515, GetMatrix_ReturnsCorrectMatrix_515) {

    const std::array<double, 6>& result = shading.getMatrix();

    EXPECT_EQ(result, matrix);

}



TEST_F(GfxFunctionShadingTest_515, GetDomain_ReturnsCorrectValues_515) {

    double x0A, y0A, x1A, y1A;

    shading.getDomain(&x0A, &y0A, &x1A, &y1A);

    EXPECT_EQ(x0A, x0);

    EXPECT_EQ(y0A, y0);

    EXPECT_EQ(x1A, x1);

    EXPECT_EQ(y1A, y1);

}



TEST_F(GfxFunctionShadingTest_515, GetNFuncs_ReturnsZeroWhenNoFunctions_515) {

    int nFuncs = shading.getNFuncs();

    EXPECT_EQ(nFuncs, 0);

}



TEST_F(GfxFunctionShadingTest_515, GetFunc_OutOfBounds_ReturnsNullptr_515) {

    const Function* func = shading.getFunc(0); // Index out of bounds since no functions are added

    EXPECT_EQ(func, nullptr);

}
