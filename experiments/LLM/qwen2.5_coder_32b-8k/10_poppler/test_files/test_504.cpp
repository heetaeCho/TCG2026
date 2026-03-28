#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxShadingTest_504 : public ::testing::Test {

protected:

    std::unique_ptr<GfxShading> shading;



    void SetUp() override {

        shading = std::make_unique<GfxShading>(1); // Assuming 1 is a valid ShadingType

    }

};



TEST_F(GfxShadingTest_504, GetBackground_ReturnsNonNullPointer_504) {

    const GfxColor* background = shading->getBackground();

    EXPECT_NE(background, nullptr);

}



TEST_F(GfxShadingTest_504, GetHasBackground_DefaultValueIsFalse_504) {

    bool hasBackground = shading->getHasBackground();

    EXPECT_FALSE(hasBackground);

}



TEST_F(GfxShadingTest_504, GetColorSpace_ReturnsNonNullPointer_504) {

    GfxColorSpace* colorSpace = shading->getColorSpace();

    EXPECT_NE(colorSpace, nullptr);

}



TEST_F(GfxShadingTest_504, GetType_ReturnsConstructedType_504) {

    ShadingType type = shading->getType();

    EXPECT_EQ(type, 1); // Assuming the constructed type is 1

}



TEST_F(GfxShadingTest_504, GetHasBBox_DefaultValueIsFalse_504) {

    bool hasBBox = shading->getHasBBox();

    EXPECT_FALSE(hasBBox);

}



TEST_F(GfxShadingTest_504, GetBBox_SetsValuesCorrectly_504) {

    double xMin, yMin, xMax, yMax;

    shading->getBBox(&xMin, &yMin, &xMax, &yMax);

    // Since we don't know the actual default values, we can only check if they are set

    EXPECT_TRUE(xMin <= xMax && yMin <= yMax); // Basic boundary check

}



TEST_F(GfxShadingTest_504, Copy_ReturnsNewInstance_504) {

    std::unique_ptr<GfxShading> copy = shading->copy();

    EXPECT_NE(copy.get(), shading.get());

    EXPECT_EQ(copy->getType(), shading->getType()); // Check if the type is copied correctly

}



TEST_F(GfxShadingTest_504, Destructor_DoesNotThrowException_504) {

    // The destructor should not throw exceptions, so just deleting it tests this

    // This test case implicitly checks the destructor through the unique_ptr going out of scope.

}
