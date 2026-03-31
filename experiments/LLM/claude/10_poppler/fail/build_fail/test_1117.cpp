#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// Helper to safely create SplashBitmap instances for testing
class SplashBitmapTest_1117 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getWidth for RGB8 mode
TEST_F(SplashBitmapTest_1117, GetWidth_ReturnsCorrectWidth_1117) {
    SplashBitmap bmp(100, 200, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
}

// Test basic construction and getHeight
TEST_F(SplashBitmapTest_1117, GetHeight_ReturnsCorrectHeight_1117) {
    SplashBitmap bmp(100, 200, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getHeight(), 200);
}

// Test getMode returns the mode passed to constructor
TEST_F(SplashBitmapTest_1117, GetMode_ReturnsCorrectMode_RGB8_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
}

TEST_F(SplashBitmapTest_1117, GetMode_ReturnsCorrectMode_Mono8_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
}

TEST_F(SplashBitmapTest_1117, GetMode_ReturnsCorrectMode_Mono1_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
}

TEST_F(SplashBitmapTest_1117, GetMode_ReturnsCorrectMode_XBGR8_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
}

// Test getRowPad returns the pad value passed to constructor
TEST_F(SplashBitmapTest_1117, GetRowPad_ReturnsCorrectPad_1117) {
    SplashBitmap bmp(50, 50, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 4);
}

TEST_F(SplashBitmapTest_1117, GetRowPad_ReturnsOne_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 1);
}

// Test that data pointer is not null after construction
TEST_F(SplashBitmapTest_1117, GetDataPtr_IsNotNull_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test alpha pointer when alpha is enabled
TEST_F(SplashBitmapTest_1117, GetAlphaPtr_WithAlphaEnabled_IsNotNull_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test alpha pointer when alpha is disabled
TEST_F(SplashBitmapTest_1117, GetAlphaPtr_WithAlphaDisabled_IsNull_1117) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test getRowSize for RGB8 mode (3 bytes per pixel)
TEST_F(SplashBitmapTest_1117, GetRowSize_RGB8_CorrectSize_1117) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // RGB8 = 3 bytes per pixel, row size should be >= 300
    EXPECT_GE(bmp.getRowSize(), 300);
}

// Test getRowSize for Mono8 mode (1 byte per pixel)
TEST_F(SplashBitmapTest_1117, GetRowSize_Mono8_CorrectSize_1117) {
    SplashBitmap bmp(100, 50, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 100);
}

// Test getRowSize for XBGR8 mode (4 bytes per pixel)
TEST_F(SplashBitmapTest_1117, GetRowSize_XBGR8_CorrectSize_1117) {
    SplashBitmap bmp(100, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 400);
}

// Test getAlphaRowSize
TEST_F(SplashBitmapTest_1117, GetAlphaRowSize_EqualsWidth_1117) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaRowSize(), 100);
}

// Test with width = 1 (boundary)
TEST_F(SplashBitmapTest_1117, BoundaryWidth1_1117) {
    SplashBitmap bmp(1, 1, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test with larger dimensions
TEST_F(SplashBitmapTest_1117, LargeDimensions_1117) {
    SplashBitmap bmp(1000, 1000, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1000);
    EXPECT_EQ(bmp.getHeight(), 1000);
}

// Test getPixel basic operation (no crash, reads something)
TEST_F(SplashBitmapTest_1117, GetPixel_NoSegfault_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Just verify it doesn't crash
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(9, 9, pixel);
}

// Test getAlpha when alpha is enabled
TEST_F(SplashBitmapTest_1117, GetAlpha_WithAlphaEnabled_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Should not crash; value is whatever was initialized
    unsigned char alpha = bmp.getAlpha(0, 0);
    (void)alpha; // Just verify no crash
}

// Test takeData transfers ownership
TEST_F(SplashBitmapTest_1117, TakeData_ReturnsNonNull_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr data = bmp.takeData();
    EXPECT_NE(data, nullptr);
    // After takeData, the caller owns the memory
    gfree(data);
}

// Test copy static method
TEST_F(SplashBitmapTest_1117, Copy_ProducesSameDimensions_1117) {
    SplashBitmap original(50, 30, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copied = SplashBitmap::copy(&original);
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getWidth(), original.getWidth());
    EXPECT_EQ(copied->getHeight(), original.getHeight());
    EXPECT_EQ(copied->getMode(), original.getMode());
    EXPECT_EQ(copied->getRowPad(), original.getRowPad());
    delete copied;
}

// Test copy preserves alpha
TEST_F(SplashBitmapTest_1117, Copy_PreservesAlphaPresence_1117) {
    SplashBitmap original(20, 20, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copied = SplashBitmap::copy(&original);
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied->getAlphaPtr(), nullptr);
    delete copied;
}

// Test Mono1 mode
TEST_F(SplashBitmapTest_1117, Mono1Mode_BasicProperties_1117) {
    SplashBitmap bmp(80, 40, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 80);
    EXPECT_EQ(bmp.getHeight(), 40);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
    // Mono1: row size should be >= ceil(80/8) = 10
    EXPECT_GE(bmp.getRowSize(), 10);
}

// Test with row padding
TEST_F(SplashBitmapTest_1117, RowPadding_AffectsRowSize_1117) {
    SplashBitmap bmp1(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap bmp4(10, 10, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Row size with padding 4 should be >= row size with padding 1
    EXPECT_GE(bmp4.getRowSize(), bmp1.getRowSize());
}

// Test writePNMFile to a temporary file
TEST_F(SplashBitmapTest_1117, WritePNMFile_ToFile_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile for Mono8
TEST_F(SplashBitmapTest_1117, WritePNMFile_Mono8_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writeAlphaPGMFile with alpha
TEST_F(SplashBitmapTest_1117, WriteAlphaPGMFile_WithAlpha_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    char tmpName[] = "/tmp/splashtest_alpha_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        close(fd);
        SplashError err = bmp.writeAlphaPGMFile(tmpName);
        EXPECT_EQ(err, splashOk);
        unlink(tmpName);
    }
}

// Test getRGBLine doesn't crash
TEST_F(SplashBitmapTest_1117, GetRGBLine_NoCrash_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[10 * 3];
    bmp.getRGBLine(0, line);
    bmp.getRGBLine(9, line);
}

// Test getXBGRLine doesn't crash
TEST_F(SplashBitmapTest_1117, GetXBGRLine_NoCrash_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[10 * 4];
    bmp.getXBGRLine(0, line, SplashBitmap::conversionOpaque);
}

// Test getSeparationList returns non-null when provided
TEST_F(SplashBitmapTest_1117, GetSeparationList_ReturnsPointer_1117) {
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepList;
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, &sepList);
    EXPECT_NE(bmp.getSeparationList(), nullptr);
}

// Test that copy is deleted (can't copy-construct)
// This is a compile-time check, so we just verify the class behaves correctly
TEST_F(SplashBitmapTest_1117, CopyConstructorDeleted_StaticCopy_1117) {
    SplashBitmap original(5, 5, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copied = SplashBitmap::copy(&original);
    ASSERT_NE(copied, nullptr);
    // Verify independent data
    EXPECT_EQ(copied->getWidth(), 5);
    EXPECT_EQ(copied->getHeight(), 5);
    EXPECT_NE(copied->getDataPtr(), original.getDataPtr());
    delete copied;
}

// Test topDown parameter (both true and false) - verify no crash
TEST_F(SplashBitmapTest_1117, TopDownFalse_NoCrash_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, false, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test convertToXBGR
TEST_F(SplashBitmapTest_1117, ConvertToXBGR_FromRGB8_1117) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    bool result = bmp.convertToXBGR(SplashBitmap::conversionOpaque);
    // Should succeed for RGB8
    EXPECT_TRUE(result);
    // After conversion, mode should be XBGR8
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
}

// Test getPixel at boundary coordinates
TEST_F(SplashBitmapTest_1117, GetPixel_BoundaryCoordinates_1117) {
    SplashBitmap bmp(5, 5, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Top-left corner
    bmp.getPixel(0, 0, pixel);
    // Bottom-right corner
    bmp.getPixel(4, 4, pixel);
}
