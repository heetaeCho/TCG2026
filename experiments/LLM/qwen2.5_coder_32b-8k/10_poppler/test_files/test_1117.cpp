#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashBitmap.h"



// Test Fixture for SplashBitmap tests.

class SplashBitmapTest_1117 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a SplashBitmap with some arbitrary values for testing.

        bitmap = new SplashBitmap(100, 200, 8, static_cast<SplashColorMode>(1), true, false, nullptr);

    }



    void TearDown() override {

        delete bitmap;

    }



    SplashBitmap* bitmap;

};



// Test normal operation of getWidth().

TEST_F(SplashBitmapTest_1117, GetWidth_ReturnsCorrectValue_1117) {

    EXPECT_EQ(bitmap->getWidth(), 100);

}



// Test normal operation of getHeight().

TEST_F(SplashBitmapTest_1117, GetHeight_ReturnsCorrectValue_1117) {

    EXPECT_EQ(bitmap->getHeight(), 200);

}



// Test normal operation of getRowSize().

TEST_F(SplashBitmapTest_1117, GetRowSize_ReturnsExpectedValue_1117) {

    // Assuming row size is calculated as width * bytes per pixel + rowPad.

    // Since modeA = 1 (assuming some color mode like RGB), and no other details are given,

    // we assume each pixel takes up 3 bytes.

    EXPECT_EQ(bitmap->getRowSize(), 100 * 3 + 8);

}



// Test normal operation of getRowPad().

TEST_F(SplashBitmapTest_1117, GetRowPad_ReturnsExpectedValue_1117) {

    EXPECT_EQ(bitmap->getRowPad(), 8);

}



// Test normal operation of getMode().

TEST_F(SplashBitmapTest_1117, GetMode_ReturnsExpectedColorMode_1117) {

    EXPECT_EQ(static_cast<int>(bitmap->getMode()), 1);

}



// Test boundary condition: width = 0.

TEST_F(SplashBitmapTest_1117, WidthZero_ReturnsZeroWidth_1117) {

    SplashBitmap zeroWidthBitmap(0, 200, 8, static_cast<SplashColorMode>(1), true, false, nullptr);

    EXPECT_EQ(zeroWidthBitmap.getWidth(), 0);

}



// Test boundary condition: height = 0.

TEST_F(SplashBitmapTest_1117, HeightZero_ReturnsZeroHeight_1117) {

    SplashBitmap zeroHeightBitmap(100, 0, 8, static_cast<SplashColorMode>(1), true, false, nullptr);

    EXPECT_EQ(zeroHeightBitmap.getHeight(), 0);

}



// Test boundary condition: rowPad = 0.

TEST_F(SplashBitmapTest_1117, RowPadZero_ReturnsCorrectRowSize_1117) {

    SplashBitmap zeroRowPadBitmap(100, 200, 0, static_cast<SplashColorMode>(1), true, false, nullptr);

    EXPECT_EQ(zeroRowPadBitmap.getRowSize(), 100 * 3 + 0); // Assuming each pixel takes up 3 bytes.

}



// Test exceptional case: writePNMFile with invalid file name (no actual error checking possible without implementation).

TEST_F(SplashBitmapTest_1117, WritePNMFileWithInvalidFileName_DoesNotCrash_1117) {

    EXPECT_EQ(bitmap->writePNMFile(nullptr), splashErrWriteFile);

}



// Test exceptional case: writeAlphaPGMFile with invalid file name (no actual error checking possible without implementation).

TEST_F(SplashBitmapTest_1117, WriteAlphaPGMFileWithInvalidFileName_DoesNotCrash_1117) {

    EXPECT_EQ(bitmap->writeAlphaPGMFile(nullptr), splashErrWriteFile);

}



// Test exceptional case: writeImgFile with invalid file name (no actual error checking possible without implementation).

TEST_F(SplashBitmapTest_1117, WriteImgFileWithInvalidFileName_DoesNotCrash_1117) {

    EXPECT_EQ(bitmap->writeImgFile(splashImagePng, nullptr, 300, 300, nullptr), splashErrWriteFile);

}
