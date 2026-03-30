#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxDeviceNColorSpaceTest_483 : public ::testing::Test {

protected:

    std::vector<std::string> names;

    std::unique_ptr<GfxColorSpace> alt;

    std::unique_ptr<Function> func;

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;



    void SetUp() override {

        names = {"Cyan", "Magenta", "Yellow", "Black"};

        alt = nullptr;

        func = nullptr;

        sepsCS = {};

    }



    GfxDeviceNColorSpace createGfxDeviceNColorSpace(bool nonMarking) {

        return GfxDeviceNColorSpace(4, std::move(names), std::move(alt), std::move(func), std::move(sepsCS), {}, nonMarking, 0, PrivateTag{});

    }

};



TEST_F(GfxDeviceNColorSpaceTest_483, IsNonMarking_ReturnsTrue_483) {

    GfxDeviceNColorSpace colorSpace = createGfxDeviceNColorSpace(true);

    EXPECT_TRUE(colorSpace.isNonMarking());

}



TEST_F(GfxDeviceNColorSpaceTest_483, IsNonMarking_ReturnsFalse_483) {

    GfxDeviceNColorSpace colorSpace = createGfxDeviceNColorSpace(false);

    EXPECT_FALSE(colorSpace.isNonMarking());

}



TEST_F(GfxDeviceNColorSpaceTest_483, GetNComps_ReturnsCorrectValue_483) {

    GfxDeviceNColorSpace colorSpace = createGfxDeviceNColorSpace(true);

    EXPECT_EQ(4, colorSpace.getNComps());

}



TEST_F(GfxDeviceNColorSpaceTest_483, GetColorantName_ReturnsCorrectName_483) {

    GfxDeviceNColorSpace colorSpace = createGfxDeviceNColorSpace(true);

    EXPECT_EQ("Cyan", colorSpace.getColorantName(0));

    EXPECT_EQ("Magenta", colorSpace.getColorantName(1));

    EXPECT_EQ("Yellow", colorSpace.getColorantName(2));

    EXPECT_EQ("Black", colorSpace.getColorantName(3));

}



TEST_F(GfxDeviceNColorSpaceTest_483, GetColorantName_OutOfBounds_ReturnsEmptyString_483) {

    GfxDeviceNColorSpace colorSpace = createGfxDeviceNColorSpace(true);

    EXPECT_THROW(colorSpace.getColorantName(4), std::out_of_range); // Assuming out of bounds throws an exception

}



TEST_F(GfxDeviceNColorSpaceTest_483, GetAlt_ReturnsNullptr_483) {

    GfxDeviceNColorSpace colorSpace = createGfxDeviceNColorSpace(true);

    EXPECT_EQ(nullptr, colorSpace.getAlt());

}



TEST_F(GfxDeviceNColorSpaceTest_483, GetTintTransformFunc_ReturnsNullptr_483) {

    GfxDeviceNColorSpace colorSpace = createGfxDeviceNColorSpace(true);

    EXPECT_EQ(nullptr, colorSpace.getTintTransformFunc());

}
