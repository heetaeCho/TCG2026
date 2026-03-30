#include <gtest/gtest.h>

#include "GfxState.h"



class GfxDeviceRGBAColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxDeviceRGBAColorSpace> color_space;



    void SetUp() override {

        color_space = std::make_unique<GfxDeviceRGBAColorSpace>();

    }

};



TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeReturnsCorrectValue_428) {

    EXPECT_EQ(color_space->getMode(), csDeviceRGBA);

}



TEST_F(GfxDeviceRGBAColorSpaceTest_428, CopyCreatesNewInstance_428) {

    auto copy = color_space->copy();

    EXPECT_NE(copy.get(), color_space.get());

    EXPECT_EQ(copy->getMode(), csDeviceRGBA);

}



TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetNCompsReturnsFour_428) {

    EXPECT_EQ(color_space->getNComps(), 4);

}
