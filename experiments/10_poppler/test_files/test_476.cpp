#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



using namespace std;



class GfxSeparationColorSpaceTest_476 : public ::testing::Test {

protected:

    unique_ptr<GooString> nameA = make_unique<GooString>("TestName");

    unique_ptr<GfxColorSpace> altA = nullptr; // Assuming default initialization for simplicity

    unique_ptr<Function> funcA = nullptr; // Assuming default initialization for simplicity



    unique_ptr<GfxSeparationColorSpace> separationColorSpace;



    void SetUp() override {

        separationColorSpace = make_unique<GfxSeparationColorSpace>(move(nameA), move(altA), move(funcA));

    }

};



TEST_F(GfxSeparationColorSpaceTest_476, GetNComps_ReturnsOne_476) {

    EXPECT_EQ(separationColorSpace->getNComps(), 1);

}



TEST_F(GfxSeparationColorSpaceTest_476, IsNonMarking_DefaultValueFalse_476) {

    EXPECT_FALSE(separationColorSpace->isNonMarking());

}



TEST_F(GfxSeparationColorSpaceTest_476, GetName_ReturnsProvidedName_476) {

    const GooString* name = separationColorSpace->getName();

    ASSERT_NE(name, nullptr);

    EXPECT_STREQ(name->getCString(), "TestName");

}



TEST_F(GfxSeparationColorSpaceTest_476, GetAlt_ReturnsProvidedAlt_476) {

    GfxColorSpace* alt = separationColorSpace->getAlt();

    EXPECT_EQ(alt, nullptr); // Since altA is initialized to nullptr

}



TEST_F(GfxSeparationColorSpaceTest_476, GetFunc_ReturnsProvidedFunc_476) {

    const Function* func = separationColorSpace->getFunc();

    EXPECT_EQ(func, nullptr); // Since funcA is initialized to nullptr

}
