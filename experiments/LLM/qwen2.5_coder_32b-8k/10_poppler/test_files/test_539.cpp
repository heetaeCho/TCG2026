#include <gtest/gtest.h>

#include "GfxState.h"



class GfxImageColorMapTest_539 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> colorSpace;

    Object decode;

    int bits = 8;



    void SetUp() override {

        // Assuming some setup for colorSpace and decode if needed

        colorSpace = std::make_unique<GfxColorSpace>();

        // For the sake of this test, we assume decode is properly initialized

    }



    GfxImageColorMap createGfxImageColorMap() {

        return GfxImageColorMap(bits, &decode, std::move(colorSpace));

    }

};



TEST_F(GfxImageColorMapTest_539, SetMatteColorAndGetMatteColor_NormalOperation_539) {

    GfxImageColorMap colorMap = createGfxImageColorMap();

    GfxColor matteColor;

    matteColor.c[0] = 1.0; // Assuming the first component is set to 1.0 for test

    colorMap.setMatteColor(&matteColor);



    const GfxColor *retrievedMatteColor = colorMap.getMatteColor();

    ASSERT_NE(retrievedMatteColor, nullptr);

    EXPECT_EQ(retrievedMatteColor->c[0], matteColor.c[0]);

}



TEST_F(GfxImageColorMapTest_539, GetMatteColor_DefaultValue_539) {

    GfxImageColorMap colorMap = createGfxImageColorMap();

    const GfxColor *matteColor = colorMap.getMatteColor();

    EXPECT_EQ(matteColor, nullptr);

}



TEST_F(GfxImageColorMapTest_539, SetMatteColor_MultipleTimes_539) {

    GfxImageColorMap colorMap = createGfxImageColorMap();

    GfxColor matteColor1;

    GfxColor matteColor2;

    matteColor1.c[0] = 1.0; // Assuming the first component is set to 1.0 for test

    matteColor2.c[0] = 0.5; // Assuming the first component is set to 0.5 for test



    colorMap.setMatteColor(&matteColor1);

    const GfxColor *retrievedMatteColor1 = colorMap.getMatteColor();

    ASSERT_NE(retrievedMatteColor1, nullptr);

    EXPECT_EQ(retrievedMatteColor1->c[0], matteColor1.c[0]);



    colorMap.setMatteColor(&matteColor2);

    const GfxColor *retrievedMatteColor2 = colorMap.getMatteColor();

    ASSERT_NE(retrievedMatteColor2, nullptr);

    EXPECT_EQ(retrievedMatteColor2->c[0], matteColor2.c[0]);

}
