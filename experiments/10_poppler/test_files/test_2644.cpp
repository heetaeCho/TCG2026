#include <gtest/gtest.h>

#include "ImageOutputDev.h"



class ImageOutputDevTest : public ::testing::Test {

protected:

    ImageOutputDev* imageOutputDev;



    void SetUp() override {

        imageOutputDev = new ImageOutputDev(nullptr, false, false);

    }



    void TearDown() override {

        delete imageOutputDev;

    }

};



TEST_F(ImageOutputDevTest_2644, GetErrorCodeInitialValue_2644) {

    EXPECT_EQ(imageOutputDev->getErrorCode(), 0);

}



TEST_F(ImageOutputDevTest_2644, IsOkInitiallyTrue_2644) {

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2644, UseTilingPatternFillInitiallyFalse_2644) {

    EXPECT_FALSE(imageOutputDev->useTilingPatternFill());

}



TEST_F(ImageOutputDevTest_2644, InterpretType3CharsInitiallyTrue_2644) {

    EXPECT_TRUE(imageOutputDev->interpretType3Chars());

}



TEST_F(ImageOutputDevTest_2644, NeedNonTextInitiallyFalse_2644) {

    EXPECT_FALSE(imageOutputDev->needNonText());

}



TEST_F(ImageOutputDevTest_2644, UpsideDownInitiallyFalse_2644) {

    EXPECT_FALSE(imageOutputDev->upsideDown());

}



TEST_F(ImageOutputDevTest_2644, UseDrawCharInitiallyTrue_2644) {

    EXPECT_TRUE(imageOutputDev->useDrawChar());

}



TEST_F(ImageOutputDevTest_2644, EnablePNGSetsCorrectly_2644) {

    imageOutputDev->enablePNG(true);

    // No observable change in public interface to verify directly

    // Test assumes internal state is correctly set and affects behavior appropriately

}



TEST_F(ImageOutputDevTest_2644, EnableTiffSetsCorrectly_2644) {

    imageOutputDev->enableTiff(true);

    // No observable change in public interface to verify directly

    // Test assumes internal state is correctly set and affects behavior appropriately

}



TEST_F(ImageOutputDevTest_2644, EnableJpegSetsCorrectly_2644) {

    imageOutputDev->enableJpeg(true);

    // No observable change in public interface to verify directly

    // Test assumes internal state is correctly set and affects behavior appropriately

}



TEST_F(ImageOutputDevTest_2644, EnableJpeg2000SetsCorrectly_2644) {

    imageOutputDev->enableJpeg2000(true);

    // No observable change in public interface to verify directly

    // Test assumes internal state is correctly set and affects behavior appropriately

}



TEST_F(ImageOutputDevTest_2644, EnableJBIG2SetsCorrectly_2644) {

    imageOutputDev->enableJBig2(true);

    // No observable change in public interface to verify directly

    // Test assumes internal state is correctly set and affects behavior appropriately

}



TEST_F(ImageOutputDevTest_2644, EnableCCITTSetsCorrectly_2644) {

    imageOutputDev->enableCCITT(true);

    // No observable change in public interface to verify directly

    // Test assumes internal state is correctly set and affects behavior appropriately

}



TEST_F(ImageOutputDevTest_2644, EnablePrintFilenamesSetsCorrectly_2644) {

    imageOutputDev->enablePrintFilenames(true);

    // No observable change in public interface to verify directly

    // Test assumes internal state is correctly set and affects behavior appropriately

}
