#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include <memory>



using namespace testing;



class GfxUnivariateShadingTest : public ::testing::Test {

protected:

    std::vector<std::unique_ptr<Function>> funcs;

    double t0 = 0.0;

    double t1 = 1.0;

    bool extend0 = true;

    bool extend1 = false;



    void SetUp() override {

        // Setting up a mock function for testing purposes

        auto funcMock1 = std::make_unique<Function>();

        auto funcMock2 = std::make_unique<Function>();

        funcs.push_back(std::move(funcMock1));

        funcs.push_back(std::move(funcMock2));



        shading = std::make_unique<GfxUnivariateShading>(0, t0, t1, std::move(funcs), extend0, extend1);

    }



    std::unique_ptr<GfxUnivariateShading> shading;

};



TEST_F(GfxUnivariateShadingTest_513, GetFunc_ReturnsCorrectFunctionPointer_513) {

    const Function* func = shading->getFunc(0);

    EXPECT_NE(func, nullptr);



    func = shading->getFunc(1);

    EXPECT_NE(func, nullptr);

}



TEST_F(GfxUnivariateShadingTest_513, GetFunc_OutOfBounds_ReturnsNullptr_513) {

    const Function* func = shading->getFunc(-1);

    EXPECT_EQ(func, nullptr);



    func = shading->getFunc(2); // Assuming only 2 functions are added

    EXPECT_EQ(func, nullptr);

}



TEST_F(GfxUnivariateShadingTest_513, GetNFuncs_ReturnsCorrectCount_513) {

    int count = shading->getNFuncs();

    EXPECT_EQ(count, 2);

}



TEST_F(GfxUnivariateShadingTest_513, GetDomain0_ReturnsCorrectValue_513) {

    double domain0 = shading->getDomain0();

    EXPECT_DOUBLE_EQ(domain0, t0);

}



TEST_F(GfxUnivariateShadingTest_513, GetDomain1_ReturnsCorrectValue_513) {

    double domain1 = shading->getDomain1();

    EXPECT_DOUBLE_EQ(domain1, t1);

}



TEST_F(GfxUnivariateShadingTest_513, GetExtend0_ReturnsCorrectValue_513) {

    bool extend = shading->getExtend0();

    EXPECT_EQ(extend, extend0);

}



TEST_F(GfxUnivariateShadingTest_513, GetExtend1_ReturnsCorrectValue_513) {

    bool extend = shading->getExtend1();

    EXPECT_EQ(extend, extend1);

}
