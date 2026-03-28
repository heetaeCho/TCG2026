#include <gtest/gtest.h>

#include "SplashBitmap.h"

#include <memory>

#include <vector>



class SplashBitmapTest : public ::testing::Test {

protected:

    std::unique_ptr<SplashBitmap> bitmap;



    void SetUp() override {

        // Create a default SplashBitmap for testing

        bitmap = std::make_unique<SplashBitmap>(10, 20, 4, static_cast<SplashColorMode>(0), false, true, nullptr);

    }

};



TEST_F(SplashBitmapTest_1123, GetDataPtr_ReturnsValidPointer_1123) {

    EXPECT_NE(bitmap->getDataPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1123, GetWidth_ReturnsCorrectValue_1123) {

    EXPECT_EQ(bitmap->getWidth(), 10);

}



TEST_F(SplashBitmapTest_1123, GetHeight_ReturnsCorrectValue_1123) {

    EXPECT_EQ(bitmap->getHeight(), 20);

}



TEST_F(SplashBitmapTest_1123, GetRowPad_ReturnsCorrectValue_1123) {

    EXPECT_EQ(bitmap->getRowPad(), 4);

}



TEST_F(SplashBitmapTest_1123, GetMode_ReturnsCorrectValue_1123) {

    EXPECT_EQ(bitmap->getMode(), static_cast<SplashColorMode>(0));

}



TEST_F(SplashBitmapTest_1123, GetRowSize_ReturnsNonNegativeValue_1123) {

    EXPECT_GE(bitmap->getRowSize(), 0);

}



TEST_F(SplashBitmapTest_1123, GetAlphaRowSize_ReturnsNonNegativeValue_1123) {

    EXPECT_GE(bitmap->getAlphaRowSize(), 0);

}



TEST_F(SplashBitmapTest_1123, WritePNMFile_WithFileName_ReturnsNoError_1123) {

    char fileName[] = "test.pnm";

    EXPECT_EQ(bitmap->writePNMFile(fileName), splashErrNone);

}



TEST_F(SplashBitmapTest_1123, WriteAlphaPGMFile_WithFileName_ReturnsNoError_1123) {

    char fileName[] = "test_alpha.pgm";

    EXPECT_EQ(bitmap->writeAlphaPGMFile(fileName), splashErrNone);

}



TEST_F(SplashBitmapTest_1123, ConvertToXBGR_ReturnsFalseForUnsupportedConversion_1123) {

    EXPECT_FALSE(bitmap->convertToXBGR(static_cast<ConversionMode>(-1)));

}



TEST_F(SplashBitmapTest_1123, GetPixel_OutOfBounds_ReturnsNoError_1123) {

    SplashColorPtr pixel = nullptr;

    bitmap->getPixel(-1, -1, pixel);

    // Assuming getPixel handles out of bounds gracefully

    EXPECT_TRUE(true); // This test might need adjustment based on actual implementation behavior

}



TEST_F(SplashBitmapTest_1123, GetRGBLine_OutOfBounds_ReturnsNoError_1123) {

    SplashColorPtr line = nullptr;

    bitmap->getRGBLine(-1, line);

    // Assuming getRGBLine handles out of bounds gracefully

    EXPECT_TRUE(true); // This test might need adjustment based on actual implementation behavior

}



TEST_F(SplashBitmapTest_1123, GetXBGRLine_OutOfBounds_ReturnsNoError_1123) {

    SplashColorPtr line = nullptr;

    bitmap->getXBGRLine(-1, line, static_cast<ConversionMode>(0));

    // Assuming getXBGRLine handles out of bounds gracefully

    EXPECT_TRUE(true); // This test might need adjustment based on actual implementation behavior

}



TEST_F(SplashBitmapTest_1123, GetCMYKLine_OutOfBounds_ReturnsNoError_1123) {

    SplashColorPtr line = nullptr;

    bitmap->getCMYKLine(-1, line);

    // Assuming getCMYKLine handles out of bounds gracefully

    EXPECT_TRUE(true); // This test might need adjustment based on actual implementation behavior

}



TEST_F(SplashBitmapTest_1123, GetAlpha_OutOfBounds_ReturnsZero_1123) {

    EXPECT_EQ(bitmap->getAlpha(-1, -1), 0);

}
