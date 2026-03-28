#include <gtest/gtest.h>

#include "GfxState.h"



class GfxColorTransformTest : public ::testing::Test {

protected:

    void* transformA = nullptr;

    int cmsIntent = 1; // Example intent value

    unsigned int inputPixelType = 24; // Example pixel type

    unsigned int transformPixelType = 32; // Example pixel type



    GfxColorTransform* colorTransform;



    virtual void SetUp() {

        colorTransform = new GfxColorTransform(transformA, cmsIntent, inputPixelType, transformPixelType);

    }



    virtual void TearDown() {

        delete colorTransform;

    }

};



TEST_F(GfxColorTransformTest_397, GetIntentReturnsCorrectValue_397) {

    EXPECT_EQ(colorTransform->getIntent(), cmsIntent);

}



TEST_F(GfxColorTransformTest_397, GetInputPixelTypeReturnsCorrectValue_397) {

    EXPECT_EQ(colorTransform->getInputPixelType(), inputPixelType);

}



TEST_F(GfxColorTransformTest_397, GetTransformPixelTypeReturnsCorrectValue_397) {

    EXPECT_EQ(colorTransform->getTransformPixelType(), transformPixelType);

}
