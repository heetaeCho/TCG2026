#include <gtest/gtest.h>

#include "GfxState.h"



class ColorMapTest_1928 : public ::testing::Test {

protected:

    std::unique_ptr<GfxImageColorMap> colorMap;



    void SetUp() override {

        // Assuming Object* decode is nullptr for simplicity, as it's not used in the function under test

        colorMap = std::make_unique<GfxImageColorMap>(8, nullptr, std::make_unique<GfxColorSpace>());

    }

};



TEST_F(ColorMapTest_1928, SingleComponentIdentityDecodeMap_1928) {

    colorMap->decodeLow[0] = 0.0;

    colorMap->decodeRange[0] = 1.0; // decodeHigh = decodeLow + decodeRange



    EXPECT_TRUE(colorMapHasIdentityDecodeMap(colorMap.get()));

}



TEST_F(ColorMapTest_1928, SingleComponentNonIdentityDecodeMapLow_1928) {

    colorMap->decodeLow[0] = 0.5;

    colorMap->decodeRange[0] = 0.5;



    EXPECT_FALSE(colorMapHasIdentityDecodeMap(colorMap.get()));

}



TEST_F(ColorMapTest_1928, SingleComponentNonIdentityDecodeMapHigh_1928) {

    colorMap->decodeLow[0] = 0.0;

    colorMap->decodeRange[0] = 0.5;



    EXPECT_FALSE(colorMapHasIdentityDecodeMap(colorMap.get()));

}



TEST_F(ColorMapTest_1928, MultipleComponentsAllIdentityDecodeMap_1928) {

    int numComps = 3; // Assuming a 3-component color map for this test

    colorMap->nComps2 = numComps;

    for (int i = 0; i < numComps; ++i) {

        colorMap->decodeLow[i] = 0.0;

        colorMap->decodeRange[i] = 1.0;

    }



    EXPECT_TRUE(colorMapHasIdentityDecodeMap(colorMap.get()));

}



TEST_F(ColorMapTest_1928, MultipleComponentsOneNonIdentityDecodeMap_1928) {

    int numComps = 3; // Assuming a 3-component color map for this test

    colorMap->nComps2 = numComps;

    for (int i = 0; i < numComps; ++i) {

        colorMap->decodeLow[i] = 0.0;

        colorMap->decodeRange[i] = 1.0;

    }

    colorMap->decodeLow[1] = 0.5;



    EXPECT_FALSE(colorMapHasIdentityDecodeMap(colorMap.get()));

}



TEST_F(ColorMapTest_1928, ZeroComponents_1928) {

    colorMap->nComps2 = 0;



    EXPECT_TRUE(colorMapHasIdentityDecodeMap(colorMap.get()));

}
