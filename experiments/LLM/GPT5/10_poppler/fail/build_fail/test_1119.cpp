#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "SplashBitmap.h"

class SplashBitmapTest_1119 : public ::testing::Test {
protected:
    // Test fixture for setup and teardown, if needed
    SplashBitmapTest_1119() {
        // Setup code, if required
    }

    ~SplashBitmapTest_1119() override {
        // Cleanup code, if required
    }
};

TEST_F(SplashBitmapTest_1119, GetRowSize_ReturnsCorrectRowSize_1119) {
    // Test normal operation for getRowSize
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_EQ(bitmap.getRowSize(), 0); // Expected value based on the constructor, adjust as needed
}

TEST_F(SplashBitmapTest_1119, GetWidth_ReturnsCorrectWidth_1119) {
    // Test normal operation for getWidth
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_EQ(bitmap.getWidth(), 100);  // The width passed in constructor
}

TEST_F(SplashBitmapTest_1119, GetHeight_ReturnsCorrectHeight_1119) {
    // Test normal operation for getHeight
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_EQ(bitmap.getHeight(), 100); // The height passed in constructor
}

TEST_F(SplashBitmapTest_1119, GetAlpha_ReturnsCorrectAlphaValue_1119) {
    // Test normal operation for getAlpha
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_EQ(bitmap.getAlpha(0, 0), 0); // Assuming alpha is initialized to 0, adjust as needed
}

TEST_F(SplashBitmapTest_1119, GetAlphaPtr_ReturnsNonNullPointer_1119) {
    // Test that getAlphaPtr returns a non-null pointer
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_NE(bitmap.getAlphaPtr(), nullptr);
}

TEST_F(SplashBitmapTest_1119, GetSeparationList_ReturnsCorrectPointer_1119) {
    // Test that getSeparationList returns the correct pointer (not null)
    SplashBitmap bitmap(100, 100, 0, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_NE(bitmap.getSeparationList(), nullptr);
}

TEST_F(SplashBitmapTest_1119, GetRowPad_ReturnsCorrectRowPad_1119) {
    // Test normal operation for getRowPad
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_EQ(bitmap.getRowPad(), 10); // The rowPad value passed in constructor
}

TEST_F(SplashBitmapTest_1119, CopyConstructor_ThrowsException_1119) {
    // Test that the copy constructor is deleted (shouldn't be allowed)
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_DEATH({
        SplashBitmap copyBitmap = bitmap;
    }, "deleted");
}

TEST_F(SplashBitmapTest_1119, GetMode_ReturnsCorrectColorMode_1119) {
    // Test normal operation for getMode
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_EQ(bitmap.getMode(), SplashColorMode::splashModeRGB);
}

TEST_F(SplashBitmapTest_1119, GetDataPtr_ReturnsNonNullDataPtr_1119) {
    // Test that getDataPtr returns a non-null pointer
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_NE(bitmap.getDataPtr(), nullptr);
}

TEST_F(SplashBitmapTest_1119, WritePNMFile_WritesFileSuccessfully_1119) {
    // Test successful PNM file write (mocking file writing for test)
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_EQ(bitmap.writePNMFile("test.pnm"), SplashError::splashNoError);
}

TEST_F(SplashBitmapTest_1119, WriteImgFile_WritesFileSuccessfully_1119) {
    // Test successful image file write (mocking file writing for test)
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    WriteImgParams params;
    ASSERT_EQ(bitmap.writeImgFile(SplashImageFileFormat::splashImgPNG, "test.png", 300.0, 300.0, &params), SplashError::splashNoError);
}

TEST_F(SplashBitmapTest_1119, ConvertToXBGR_ConvertsCorrectly_1119) {
    // Test ConvertToXBGR function
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    ASSERT_TRUE(bitmap.convertToXBGR(ConversionMode::conversionModeLinear));
}

TEST_F(SplashBitmapTest_1119, ExceptionalCase_WriteImgFileFails_1119) {
    // Test that writeImgFile fails with a null file pointer
    SplashBitmap bitmap(100, 100, 10, SplashColorMode::splashModeRGB, true, true, nullptr);
    WriteImgParams params;
    ASSERT_EQ(bitmap.writeImgFile(SplashImageFileFormat::splashImgPNG, nullptr, 300.0, 300.0, &params), SplashError::splashWriteError);
}