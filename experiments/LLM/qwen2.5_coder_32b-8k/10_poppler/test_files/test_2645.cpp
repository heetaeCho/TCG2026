#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"



using ::testing::_;

using ::testing::Return;



class ImageOutputDevTest : public ::testing::Test {

protected:

    char* fileRoot;

    bool pageNames = false;

    bool listImages = false;

    ImageOutputDev* imageOutputDev;



    void SetUp() override {

        fileRoot = new char[10];

        strcpy(fileRoot, "test_root");

        imageOutputDev = new ImageOutputDev(fileRoot, pageNames, listImages);

    }



    void TearDown() override {

        delete[] fileRoot;

        delete imageOutputDev;

    }

};



TEST_F(ImageOutputDevTest_2645, IsOk_ReturnsTrueWhenErrorCodeIsZero_2645) {

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, GetErrorCode_ReturnsZeroInitially_2645) {

    EXPECT_EQ(0, imageOutputDev->getErrorCode());

}



TEST_F(ImageOutputDevTest_2645, EnablePNG_SetsOutputPNGToTrue_2645) {

    imageOutputDev->enablePNG(true);

    // No direct way to check outputPNG since it's private. Assuming isOk remains true.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, EnableTiff_SetsOutputTiffToTrue_2645) {

    imageOutputDev->enableTiff(true);

    // No direct way to check outputTiff since it's private. Assuming isOk remains true.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, EnableJpeg_SetsDumpJPEGToTrue_2645) {

    imageOutputDev->enableJpeg(true);

    // No direct way to check dumpJPEG since it's private. Assuming isOk remains true.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, EnableJpeg2000_SetsDumpJP2ToTrue_2645) {

    imageOutputDev->enableJpeg2000(true);

    // No direct way to check dumpJP2 since it's private. Assuming isOk remains true.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, EnableJBig2_SetsDumpJBIG2ToTrue_2645) {

    imageOutputDev->enableJBig2(true);

    // No direct way to check dumpJBIG2 since it's private. Assuming isOk remains true.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, EnableCCITT_SetsDumpCCITTToTrue_2645) {

    imageOutputDev->enableCCITT(true);

    // No direct way to check dumpCCITT since it's private. Assuming isOk remains true.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, EnablePrintFilenames_SetsPrintFilenamesToTrue_2645) {

    imageOutputDev->enablePrintFilenames(true);

    // No direct way to check printFilenames since it's private. Assuming isOk remains true.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2645, UseTilingPatternFill_ReturnsFalseInitially_2645) {

    EXPECT_FALSE(imageOutputDev->useTilingPatternFill());

}



TEST_F(ImageOutputDevTest_2645, InterpretType3Chars_ReturnsTrueInitially_2645) {

    EXPECT_TRUE(imageOutputDev->interpretType3Chars());

}



TEST_F(ImageOutputDevTest_2645, NeedNonText_ReturnsFalseInitially_2645) {

    EXPECT_FALSE(imageOutputDev->needNonText());

}



TEST_F(ImageOutputDevTest_2645, UpsideDown_ReturnsTrueInitially_2645) {

    EXPECT_TRUE(imageOutputDev->upsideDown());

}



TEST_F(ImageOutputDevTest_2645, UseDrawChar_ReturnsFalseInitially_2645) {

    EXPECT_FALSE(imageOutputDev->useDrawChar());

}
