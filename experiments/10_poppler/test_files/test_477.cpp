#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxSeparationColorSpaceTest_477 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> name = std::make_unique<GooString>("testName");

    std::unique_ptr<GfxColorSpace> alt = nullptr;

    std::unique_ptr<Function> func = nullptr;

    bool nonMarking = false;



    GfxSeparationColorSpaceTest_477() : colorSpace(std::make_unique<GfxSeparationColorSpace>(std::move(name), std::move(alt), std::move(func), nonMarking, 0, std::vector<int>(), PrivateTag())) {}



    std::unique_ptr<GfxSeparationColorSpace> colorSpace;

};



TEST_F(GfxSeparationColorSpaceTest_477, IsNonMarking_ReturnsFalse_477) {

    EXPECT_FALSE(colorSpace->isNonMarking());

}



TEST_F(GfxSeparationColorSpaceTest_477, IsNonMarking_ReturnsTrue_477) {

    GfxSeparationColorSpace colorSpaceWithNonMarking(std::make_unique<GooString>("testName"), nullptr, nullptr, true, 0, std::vector<int>(), PrivateTag());

    EXPECT_TRUE(colorSpaceWithNonMarking.isNonMarking());

}



TEST_F(GfxSeparationColorSpaceTest_477, GetName_ReturnsValidName_477) {

    const GooString* name = colorSpace->getName();

    EXPECT_EQ("testName", name->getCString());

}



TEST_F(GfxSeparationColorSpaceTest_477, GetAlt_ReturnsNullptr_477) {

    EXPECT_EQ(nullptr, colorSpace->getAlt());

}



TEST_F(GfxSeparationColorSpaceTest_477, GetFunc_ReturnsNullptr_477) {

    EXPECT_EQ(nullptr, colorSpace->getFunc());

}
