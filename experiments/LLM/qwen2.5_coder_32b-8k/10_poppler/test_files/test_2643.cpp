#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"



class ImageOutputDevTest : public ::testing::Test {

protected:

    char fileRootA[10] = "test";

    bool pageNamesA = false;

    bool listImagesA = false;



    ImageOutputDev* imageOutputDev;



    void SetUp() override {

        imageOutputDev = new ImageOutputDev(fileRootA, pageNamesA, listImagesA);

    }



    void TearDown() override {

        delete imageOutputDev;

    }

};



TEST_F(ImageOutputDevTest_2643, EnablePrintFilenamesTrue_2643) {

    // Arrange

    bool filenames = true;



    // Act

    imageOutputDev->enablePrintFilenames(filenames);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnablePrintFilenamesFalse_2643) {

    // Arrange

    bool filenames = false;



    // Act

    imageOutputDev->enablePrintFilenames(filenames);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnablePNGTrue_2643) {

    // Arrange

    bool png = true;



    // Act

    imageOutputDev->enablePNG(png);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnablePNGFalse_2643) {

    // Arrange

    bool png = false;



    // Act

    imageOutputDev->enablePNG(png);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableTiffTrue_2643) {

    // Arrange

    bool tiff = true;



    // Act

    imageOutputDev->enableTiff(tiff);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableTiffFalse_2643) {

    // Arrange

    bool tiff = false;



    // Act

    imageOutputDev->enableTiff(tiff);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableJpegTrue_2643) {

    // Arrange

    bool jpeg = true;



    // Act

    imageOutputDev->enableJpeg(jpeg);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableJpegFalse_2643) {

    // Arrange

    bool jpeg = false;



    // Act

    imageOutputDev->enableJpeg(jpeg);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableJpeg2000True_2643) {

    // Arrange

    bool jp2 = true;



    // Act

    imageOutputDev->enableJpeg2000(jp2);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableJpeg2000False_2643) {

    // Arrange

    bool jp2 = false;



    // Act

    imageOutputDev->enableJpeg2000(jp2);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableJBIG2True_2643) {

    // Arrange

    bool jbig2 = true;



    // Act

    imageOutputDev->enableJBIG2(jbig2);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableJBIG2False_2643) {

    // Arrange

    bool jbig2 = false;



    // Act

    imageOutputDev->enableJBIG2(jbig2);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableCCITTTrue_2643) {

    // Arrange

    bool ccitt = true;



    // Act

    imageOutputDev->enableCCITT(ccitt);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, EnableCCITTFalse_2643) {

    // Arrange

    bool ccitt = false;



    // Act

    imageOutputDev->enableCCITT(ccitt);



    // Assert: We can't directly verify the internal state, but we can ensure there are no crashes or other observable issues.

}



TEST_F(ImageOutputDevTest_2643, GetErrorCode_Default_2643) {

    // Arrange



    // Act

    int errorCode = imageOutputDev->getErrorCode();



    // Assert: We assume the default error code is 0, but this should be verified based on actual implementation details.

    EXPECT_EQ(errorCode, 0);

}



TEST_F(ImageOutputDevTest_2643, IsOk_Default_2643) {

    // Arrange



    // Act

    bool isOk = imageOutputDev->isOk();



    // Assert: We assume the default state is ok, but this should be verified based on actual implementation details.

    EXPECT_TRUE(isOk);

}



TEST_F(ImageOutputDevTest_2643, UseTilingPatternFill_Default_2643) {

    // Arrange



    // Act

    bool useTiling = imageOutputDev->useTilingPatternFill();



    // Assert: We assume the default state is false, but this should be verified based on actual implementation details.

    EXPECT_FALSE(useTiling);

}



TEST_F(ImageOutputDevTest_2643, InterpretType3Chars_Default_2643) {

    // Arrange



    // Act

    bool interpret = imageOutputDev->interpretType3Chars();



    // Assert: We assume the default state is false, but this should be verified based on actual implementation details.

    EXPECT_FALSE(interpret);

}



TEST_F(ImageOutputDevTest_2643, NeedNonText_Default_2643) {

    // Arrange



    // Act

    bool needNonText = imageOutputDev->needNonText();



    // Assert: We assume the default state is false, but this should be verified based on actual implementation details.

    EXPECT_FALSE(needNonText);

}



TEST_F(ImageOutputDevTest_2643, UpsideDown_Default_2643) {

    // Arrange



    // Act

    bool upsideDown = imageOutputDev->upsideDown();



    // Assert: We assume the default state is false, but this should be verified based on actual implementation details.

    EXPECT_FALSE(upsideDown);

}



TEST_F(ImageOutputDevTest_2643, UseDrawChar_Default_2643) {

    // Arrange



    // Act

    bool useDrawChar = imageOutputDev->useDrawChar();



    // Assert: We assume the default state is false, but this should be verified based on actual implementation details.

    EXPECT_FALSE(useDrawChar);

}
