#include <gtest/gtest.h>

#include "GfxState.h"



class GfxImageColorMapTest_540 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> colorSpace;

    Object decode;

    GfxImageColorMap* colorMap;



    void SetUp() override {

        // Assuming a mock or default implementation for GfxColorSpace and Object

        colorSpace = std::make_unique<GfxColorSpace>(); // Replace with actual if needed

        colorMap = new GfxImageColorMap(8, &decode, std::move(colorSpace));

    }



    void TearDown() override {

        delete colorMap;

    }

};



TEST_F(GfxImageColorMapTest_540, GetMatteColor_ReturnsNullptrWhenNotSet_540) {

    EXPECT_EQ(nullptr, colorMap->getMatteColor());

}



TEST_F(GfxImageColorMapTest_540, SetAndGetMatteColor_SetsAndReturnsCorrectValue_540) {

    GfxColor matteColor;

    memset(&matteColor, 0xFF, sizeof(matteColor)); // Example initialization

    colorMap->setMatteColor(&matteColor);

    EXPECT_EQ(&matteColor, colorMap->getMatteColor());

}



TEST_F(GfxImageColorMapTest_540, GetMatteColor_ReturnsNullptrAfterSettingToNull_540) {

    GfxColor matteColor;

    memset(&matteColor, 0xFF, sizeof(matteColor)); // Example initialization

    colorMap->setMatteColor(&matteColor);

    colorMap->setMatteColor(nullptr);

    EXPECT_EQ(nullptr, colorMap->getMatteColor());

}



TEST_F(GfxImageColorMapTest_540, IsOk_ReturnsTrueAfterInitialization_540) {

    EXPECT_TRUE(colorMap->isOk());

}
