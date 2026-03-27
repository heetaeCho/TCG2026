#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



using namespace testing;



class GfxSeparationColorSpaceTest_480 : public Test {

protected:

    std::unique_ptr<GooString> name;

    std::unique_ptr<GfxColorSpace> alt;

    std::unique_ptr<Function> func;



    void SetUp() override {

        name = std::make_unique<GooString>("TestName");

        alt = std::make_unique<GfxColorSpace>();

        func = std::make_unique<Function>();

    }

};



TEST_F(GfxSeparationColorSpaceTest_480, GetFuncReturnsCorrectPointer_480) {

    GfxSeparationColorSpace separation(std::move(name), std::move(alt), std::move(func));

    EXPECT_EQ(separation.getFunc(), func.get());

}



TEST_F(GfxSeparationColorSpaceTest_480, GetFuncReturnsNullptrIfNoFunction_480) {

    name = std::make_unique<GooString>("TestName");

    alt = std::make_unique<GfxColorSpace>();

    GfxSeparationColorSpace separation(std::move(name), std::move(alt), nullptr);

    EXPECT_EQ(separation.getFunc(), nullptr);

}



TEST_F(GfxSeparationColorSpaceTest_480, GetFuncDoesNotChangeAfterCreation_480) {

    GfxSeparationColorSpace separation(std::move(name), std::move(alt), std::move(func));

    const Function* initialFunc = separation.getFunc();

    EXPECT_EQ(separation.getFunc(), initialFunc);

}
