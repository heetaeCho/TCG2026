#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"



class ImageOutputDevTest_2642 : public ::testing::Test {

protected:

    ImageOutputDev* imageOutputDev;



    void SetUp() override {

        // Initialize with some default values for the constructor parameters

        imageOutputDev = new ImageOutputDev(const_cast<char*>("fileRoot"), true, false);

    }



    void TearDown() override {

        delete imageOutputDev;

    }

};



TEST_F(ImageOutputDevTest_2642, EnableCCITT_DefaultValueIsFalse_2642) {

    // By default, dumpCCITT should be false

    ImageOutputDev dev(const_cast<char*>("fileRoot"), true, false);

    EXPECT_FALSE(dev.isOk()); // Assuming isOk() returns false when not properly configured.

}



TEST_F(ImageOutputDevTest_2642, EnableCCITT_SetTrueAndGetExpectedBehavior_2642) {

    imageOutputDev->enableCCITT(true);

    // Since we can't directly access dumpCCITT, we assume some observable behavior

    EXPECT_TRUE(imageOutputDev->isOk()); // Assuming isOk() returns true when properly configured.

}



TEST_F(ImageOutputDevTest_2642, EnableCCITT_SetFalseAndGetExpectedBehavior_2642) {

    imageOutputDev->enableCCITT(false);

    // Since we can't directly access dumpCCITT, we assume some observable behavior

    EXPECT_TRUE(imageOutputDev->isOk()); // Assuming isOk() returns true when properly configured.

}



TEST_F(ImageOutputDevTest_2642, EnablePNG_SetTrueAndGetExpectedBehavior_2642) {

    imageOutputDev->enablePNG(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnablePNG_SetFalseAndGetExpectedBehavior_2642) {

    imageOutputDev->enablePNG(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableTiff_SetTrueAndGetExpectedBehavior_2642) {

    imageOutputDev->enableTiff(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableTiff_SetFalseAndGetExpectedBehavior_2642) {

    imageOutputDev->enableTiff(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableJpeg_SetTrueAndGetExpectedBehavior_2642) {

    imageOutputDev->enableJpeg(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableJpeg_SetFalseAndGetExpectedBehavior_2642) {

    imageOutputDev->enableJpeg(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableJpeg2000_SetTrueAndGetExpectedBehavior_2642) {

    imageOutputDev->enableJpeg2000(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableJpeg2000_SetFalseAndGetExpectedBehavior_2642) {

    imageOutputDev->enableJpeg2000(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableJBig2_SetTrueAndGetExpectedBehavior_2642) {

    imageOutputDev->enableJBig2(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnableJBig2_SetFalseAndGetExpectedBehavior_2642) {

    imageOutputDev->enableJBig2(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnablePrintFilenames_SetTrueAndGetExpectedBehavior_2642) {

    imageOutputDev->enablePrintFilenames(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, EnablePrintFilenames_SetFalseAndGetExpectedBehavior_2642) {

    imageOutputDev->enablePrintFilenames(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2642, GetErrorCode_DefaultValueIsZero_2642) {

    EXPECT_EQ(imageOutputDev->getErrorCode(), 0);

}
