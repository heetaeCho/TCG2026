#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSeparationColorSpaceTest_475 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> name = std::make_unique<GooString>("TestName");

    std::unique_ptr<GfxColorSpace> alt = std::make_unique<GfxDeviceGray>();

    std::unique_ptr<Function> func = nullptr;

    bool nonMarking = false;

    unsigned int overprintMask = 0;

    std::vector<int> mapping;



    GfxSeparationColorSpace* separationColorSpace;



    void SetUp() override {

        separationColorSpace = new GfxSeparationColorSpace(std::move(name), std::move(alt), std::move(func));

    }



    void TearDown() override {

        delete separationColorSpace;

    }

};



TEST_F(GfxSeparationColorSpaceTest_475, GetMode_ReturnsCsSeparation_475) {

    EXPECT_EQ(separationColorSpace->getMode(), csSeparation);

}



TEST_F(GfxSeparationColorSpaceTest_475, Copy_ReturnsNonNullPointer_475) {

    auto copy = separationColorSpace->copy();

    EXPECT_NE(copy.get(), nullptr);

}



TEST_F(GfxSeparationColorSpaceTest_475, CopyAsOwnType_ReturnsNonNullPointer_475) {

    auto copy = separationColorSpace->copyAsOwnType();

    EXPECT_NE(copy.get(), nullptr);

}



TEST_F(GfxSeparationColorSpaceTest_475, IsNonMarking_ReturnsFalseByDefault_475) {

    EXPECT_FALSE(separationColorSpace->isNonMarking());

}



TEST_F(GfxSeparationColorSpaceTest_475, GetName_ReturnsNonNullPointer_475) {

    const GooString* name = separationColorSpace->getName();

    EXPECT_NE(name, nullptr);

}



TEST_F(GfxSeparationColorSpaceTest_475, GetAlt_ReturnsNonNullPointer_475) {

    GfxColorSpace* alt = separationColorSpace->getAlt();

    EXPECT_NE(alt, nullptr);

}



TEST_F(GfxSeparationColorSpaceTest_475, GetFunc_ReturnsNullPointer_475) {

    const Function* func = separationColorSpace->getFunc();

    EXPECT_EQ(func, nullptr);

}
