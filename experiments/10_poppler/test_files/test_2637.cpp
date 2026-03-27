#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"



class ImageOutputDevTest_2637 : public ::testing::Test {

protected:

    char fileRootA[10] = "test";

    bool pageNamesA = true;

    bool listImagesA = false;



    ImageOutputDev* imageOutputDev;



    void SetUp() override {

        imageOutputDev = new ImageOutputDev(fileRootA, pageNamesA, listImagesA);

    }



    void TearDown() override {

        delete imageOutputDev;

    }

};



TEST_F(ImageOutputDevTest_2637, EnablePNG_DefaultValueIsFalse_2637) {

    // By default outputPNG should be false

    EXPECT_FALSE(imageOutputDev->enablePNG(false));

}



TEST_F(ImageOutputDevTest_2637, EnablePNG_SetTrueAndGetTrue_2637) {

    imageOutputDev->enablePNG(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2637, EnablePNG_SetFalseAndGetFalse_2637) {

    imageOutputDev->enablePNG(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2637, EnableTiff_DefaultValueIsFalse_2637) {

    // Assuming enableTiff follows the same pattern as enablePNG

    EXPECT_FALSE(imageOutputDev->enableTiff(false));

}



TEST_F(ImageOutputDevTest_2637, EnableJpeg_DefaultValueIsFalse_2637) {

    // Assuming enableJpeg follows the same pattern as enablePNG

    EXPECT_FALSE(imageOutputDev->enableJpeg(false));

}



TEST_F(ImageOutputDevTest_2637, EnableJpeg2000_DefaultValueIsFalse_2637) {

    // Assuming enableJpeg2000 follows the same pattern as enablePNG

    EXPECT_FALSE(imageOutputDev->enableJpeg2000(false));

}



TEST_F(ImageOutputDevTest_2637, EnableJBIG2_DefaultValueIsFalse_2637) {

    // Assuming enableJBIG2 follows the same pattern as enablePNG

    EXPECT_FALSE(imageOutputDev->enableJBIG2(false));

}



TEST_F(ImageOutputDevTest_2637, EnableCCITT_DefaultValueIsFalse_2637) {

    // Assuming enableCCITT follows the same pattern as enablePNG

    EXPECT_FALSE(imageOutputDev->enableCCITT(false));

}



TEST_F(ImageOutputDevTest_2637, EnablePrintFilenames_DefaultValueIsFalse_2637) {

    // Assuming enablePrintFilenames follows the same pattern as enablePNG

    EXPECT_FALSE(imageOutputDev->enablePrintFilenames(false));

}



TEST_F(ImageOutputDevTest_2637, IsOk_ReturnsTrue_2637) {

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2637, UseTilingPatternFill_DefaultValueIsFalse_2637) {

    EXPECT_FALSE(imageOutputDev->useTilingPatternFill());

}



TEST_F(ImageOutputDevTest_2637, InterpretType3Chars_ReturnsTrue_2637) {

    EXPECT_TRUE(imageOutputDev->interpretType3Chars());

}



TEST_F(ImageOutputDevTest_2637, NeedNonText_DefaultValueIsFalse_2637) {

    EXPECT_FALSE(imageOutputDev->needNonText());

}



TEST_F(ImageOutputDevTest_2637, UpsideDown_ReturnsFalse_2637) {

    EXPECT_FALSE(imageOutputDev->upsideDown());

}



TEST_F(ImageOutputDevTest_2637, UseDrawChar_ReturnsTrue_2637) {

    EXPECT_TRUE(imageOutputDev->useDrawChar());

}
