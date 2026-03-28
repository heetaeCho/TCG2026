#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// Test fixture for SplashBitmap tests
class SplashBitmapTest_1124 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with RGB8 mode, no alpha
TEST_F(SplashBitmapTest_1124, ConstructRGB8NoAlpha_1124) {
    SplashBitmap bmp(100, 200, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test basic construction with RGB8 mode, with alpha
TEST_F(SplashBitmapTest_1124, ConstructRGB8WithAlpha_1124) {
    SplashBitmap bmp(50, 75, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 75);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test construction with Mono1 mode
TEST_F(SplashBitmapTest_1124, ConstructMono1_1124) {
    SplashBitmap bmp(32, 32, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 32);
    EXPECT_EQ(bmp.getHeight(), 32);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
}

// Test construction with Mono8 mode
TEST_F(SplashBitmapTest_1124, ConstructMono8_1124) {
    SplashBitmap bmp(64, 64, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 64);
    EXPECT_EQ(bmp.getHeight(), 64);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test construction with XBGR8 mode
TEST_F(SplashBitmapTest_1124, ConstructXBGR8_1124) {
    SplashBitmap bmp(128, 128, 1, splashModeXBGR8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 128);
    EXPECT_EQ(bmp.getHeight(), 128);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test getAlphaPtr returns null when alpha not requested
TEST_F(SplashBitmapTest_1124, GetAlphaPtrNullWhenNoAlpha_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test getAlphaPtr returns non-null when alpha requested
TEST_F(SplashBitmapTest_1124, GetAlphaPtrNonNullWhenAlpha_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test getDataPtr returns non-null
TEST_F(SplashBitmapTest_1124, GetDataPtrNonNull_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getRowSize for RGB8
TEST_F(SplashBitmapTest_1124, GetRowSizeRGB8_1124) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // RGB8 has 3 bytes per pixel, so rowSize should be at least 300
    EXPECT_GE(bmp.getRowSize(), 300);
}

// Test getRowSize for Mono8
TEST_F(SplashBitmapTest_1124, GetRowSizeMono8_1124) {
    SplashBitmap bmp(100, 50, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Mono8 has 1 byte per pixel, so rowSize should be at least 100
    EXPECT_GE(bmp.getRowSize(), 100);
}

// Test getAlphaRowSize
TEST_F(SplashBitmapTest_1124, GetAlphaRowSize_1124) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Alpha row size should be at least the width
    EXPECT_GE(bmp.getAlphaRowSize(), 100);
}

// Test getRowPad
TEST_F(SplashBitmapTest_1124, GetRowPad_1124) {
    SplashBitmap bmp(100, 50, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 4);
}

// Test small bitmap (1x1)
TEST_F(SplashBitmapTest_1124, SmallBitmap1x1_1124) {
    SplashBitmap bmp(1, 1, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test getPixel on a basic bitmap
TEST_F(SplashBitmapTest_1124, GetPixelBasic_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Just verify it doesn't crash; pixel values depend on initialization
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(9, 9, pixel);
}

// Test getAlpha on a bitmap with alpha
TEST_F(SplashBitmapTest_1124, GetAlphaBasic_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Just verify it doesn't crash
    unsigned char alphaVal = bmp.getAlpha(0, 0);
    (void)alphaVal;
}

// Test takeData removes data ownership
TEST_F(SplashBitmapTest_1124, TakeDataReturnsNonNull_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr data = bmp.takeData();
    EXPECT_NE(data, nullptr);
    // After takeData, the internal data pointer should be null
    EXPECT_EQ(bmp.getDataPtr(), nullptr);
    // Clean up since we took ownership
    gfree(data);
}

// Test copy creates an independent copy
TEST_F(SplashBitmapTest_1124, CopyBitmap_1124) {
    SplashBitmap original(20, 30, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copy = SplashBitmap::copy(&original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), 20);
    EXPECT_EQ(copy->getHeight(), 30);
    EXPECT_EQ(copy->getMode(), splashModeRGB8);
    EXPECT_NE(copy->getAlphaPtr(), nullptr);
    EXPECT_NE(copy->getDataPtr(), nullptr);
    // Data pointers should be different (independent copy)
    EXPECT_NE(copy->getDataPtr(), original.getDataPtr());
    delete copy;
}

// Test getSeparationList returns something
TEST_F(SplashBitmapTest_1124, GetSeparationListNullInput_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // When nullptr was passed for separation list, returned list should be empty or null
    auto *sepList = bmp.getSeparationList();
    if (sepList != nullptr) {
        EXPECT_TRUE(sepList->empty());
    }
}

// Test construction with different rowPad values
TEST_F(SplashBitmapTest_1124, DifferentRowPadValues_1124) {
    SplashBitmap bmp1(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap bmp4(10, 10, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp1.getRowPad(), 1);
    EXPECT_EQ(bmp4.getRowPad(), 4);
    // Row size with pad 4 should be >= row size with pad 1
    EXPECT_GE(bmp4.getRowSize(), bmp1.getRowSize());
}

// Test XBGR8 row size (4 bytes per pixel)
TEST_F(SplashBitmapTest_1124, GetRowSizeXBGR8_1124) {
    SplashBitmap bmp(100, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // XBGR8 has 4 bytes per pixel
    EXPECT_GE(bmp.getRowSize(), 400);
}

// Test Mono1 row size calculation
TEST_F(SplashBitmapTest_1124, GetRowSizeMono1_1124) {
    SplashBitmap bmp(16, 16, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Mono1: 1 bit per pixel, 16 pixels = 2 bytes minimum
    EXPECT_GE(bmp.getRowSize(), 2);
}

// Test writePNMFile to a FILE pointer
TEST_F(SplashBitmapTest_1124, WritePNMFileToStream_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writeAlphaPGMFile
TEST_F(SplashBitmapTest_1124, WriteAlphaPGMFileNoAlpha_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Writing alpha PGM without alpha should result in an error
    char filename[] = "/tmp/test_alpha_1124.pgm";
    SplashError err = bmp.writeAlphaPGMFile(filename);
    // Behavior depends on whether alpha exists; without alpha it may return error
    // We just check it doesn't crash
    (void)err;
}

// Test topDown parameter - construction with topDown false
TEST_F(SplashBitmapTest_1124, ConstructTopDownFalse_1124) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, true, false, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 50);
    // When topDown is false, rowSize may be negative
    // But width and height should still be correct
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getRGBLine doesn't crash
TEST_F(SplashBitmapTest_1124, GetRGBLineBasic_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[30]; // 10 pixels * 3 bytes
    bmp.getRGBLine(0, line);
    bmp.getRGBLine(9, line);
}

// Test getXBGRLine doesn't crash
TEST_F(SplashBitmapTest_1124, GetXBGRLineBasic_1124) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[40]; // 10 pixels * 4 bytes
    bmp.getXBGRLine(0, line, SplashBitmap::conversionOpaque);
}

// Test copy of a bitmap with no alpha
TEST_F(SplashBitmapTest_1124, CopyBitmapNoAlpha_1124) {
    SplashBitmap original(15, 25, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copy = SplashBitmap::copy(&original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), 15);
    EXPECT_EQ(copy->getHeight(), 25);
    EXPECT_EQ(copy->getMode(), splashModeMono8);
    EXPECT_EQ(copy->getAlphaPtr(), nullptr);
    delete copy;
}

// Test width and height are correctly stored
TEST_F(SplashBitmapTest_1124, WidthHeightConsistency_1124) {
    const int width = 257;
    const int height = 513;
    SplashBitmap bmp(width, height, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), width);
    EXPECT_EQ(bmp.getHeight(), height);
}
