#include <gtest/gtest.h>

#include "GfxState.h"



class GfxColorTransformTest : public ::testing::Test {

protected:

    void* transformA = nullptr;

    int cmsIntent = 1;

    unsigned int inputPixelType = 24;

    unsigned int transformPixelType = 32;



    GfxColorTransform* gfxColorTransform;



    virtual void SetUp() {

        gfxColorTransform = new GfxColorTransform(transformA, cmsIntent, inputPixelType, transformPixelType);

    }



    virtual void TearDown() {

        delete gfxColorTransform;

    }

};



TEST_F(GfxColorTransformTest_399, GetTransformPixelType_ReturnsCorrectValue_399) {

    EXPECT_EQ(gfxColorTransform->getTransformPixelType(), 32);

}



TEST_F(GfxColorTransformTest_399, GetIntent_ReturnsCorrectValue_399) {

    EXPECT_EQ(gfxColorTransform->getIntent(), 1);

}



TEST_F(GfxColorTransformTest_399, GetInputPixelType_ReturnsCorrectValue_399) {

    EXPECT_EQ(gfxColorTransform->getInputPixelType(), 24);

}



TEST_F(GfxColorTransformTest_399, DoTransform_DoesNotThrowOnNormalUsage_399) {

    unsigned int size = 10;

    void* inBuffer = malloc(size);

    void* outBuffer = malloc(size);



    EXPECT_NO_THROW(gfxColorTransform->doTransform(inBuffer, outBuffer, size));



    free(inBuffer);

    free(outBuffer);

}



TEST_F(GfxColorTransformTest_399, DoTransform_HandlesZeroSizeGracefully_399) {

    unsigned int size = 0;

    void* inBuffer = nullptr;

    void* outBuffer = nullptr;



    EXPECT_NO_THROW(gfxColorTransform->doTransform(inBuffer, outBuffer, size));

}
