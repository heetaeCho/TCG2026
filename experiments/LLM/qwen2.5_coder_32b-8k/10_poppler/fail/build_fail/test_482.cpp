#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxDeviceNColorSpaceTest : public ::testing::Test {

protected:

    std::vector<std::string> names = {"Cyan", "Magenta", "Yellow"};

    std::unique_ptr<GfxSeparationColorSpace> sep1 = nullptr;

    std::unique_ptr<GfxSeparationColorSpace> sep2 = nullptr;

    std::unique_ptr<GfxSeparationColorSpace> sep3 = nullptr;

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS = {std::move(sep1), std::move(sep2), std::move(sep3)};

    std::unique_ptr<GfxColorSpace> alt = nullptr;

    std::unique_ptr<Function> func = nullptr;



    GfxDeviceNColorSpace colorSpace;



    GfxDeviceNColorSpaceTest()

        : colorSpace(3, std::move(names), std::move(alt), std::move(func), std::move(sepsCS)) {}

};



TEST_F(GfxDeviceNColorSpaceTest_482, GetNComps_ReturnsCorrectNumberOfComponents_482) {

    EXPECT_EQ(colorSpace.getNComps(), 3);

}



TEST_F(GfxDeviceNColorSpaceTest_482, GetColorantName_ReturnsCorrectNamesForValidIndices_482) {

    EXPECT_EQ(colorSpace.getColorantName(0), "Cyan");

    EXPECT_EQ(colorSpace.getColorantName(1), "Magenta");

    EXPECT_EQ(colorSpace.getColorantName(2), "Yellow");

}



TEST_F(GfxDeviceNColorSpaceTest_482, GetColorantName_OutOfBoundsIndex_ReturnsEmptyString_482) {

    EXPECT_TRUE(colorSpace.getColorantName(-1).empty());

    EXPECT_TRUE(colorSpace.getColorantName(3).empty());

}
