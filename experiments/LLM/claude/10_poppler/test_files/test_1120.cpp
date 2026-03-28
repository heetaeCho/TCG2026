#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <cstdio>

#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// We need to figure out what headers provide the necessary types
// SplashColorMode, SplashColorPtr, SplashError, etc.

class SplashBitmapTest_1120 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with splashModeMono1
TEST_F(SplashBitmapTest_1120, ConstructMono1_1120) {
    SplashBitmap bmp(100, 200, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
}

// Test basic construction with splashModeMono8
TEST_F(SplashBitmapTest_1120, ConstructMono8_1120) {
    SplashBitmap bmp(50, 75, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 75);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
}

// Test basic construction with splashModeRGB8
TEST_F(SplashBitmapTest_1120, ConstructRGB8_1120) {
    SplashBitmap bmp(640, 480, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 640);
    EXPECT_EQ(bmp.getHeight(), 480);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
}

// Test basic construction with splashModeXBGR8
TEST_F(SplashBitmapTest_1120, ConstructXBGR8_1120) {
    SplashBitmap bmp(320, 240, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 320);
    EXPECT_EQ(bmp.getHeight(), 240);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
}

// Test basic construction with splashModeBGR8
TEST_F(SplashBitmapTest_1120, ConstructBGR8_1120) {
    SplashBitmap bmp(256, 256, 1, splashModeBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 256);
    EXPECT_EQ(bmp.getHeight(), 256);
    EXPECT_EQ(bmp.getMode(), splashModeBGR8);
}

#ifdef SPLASH_CMYK
// Test construction with splashModeCMYK8
TEST_F(SplashBitmapTest_1120, ConstructCMYK8_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeCMYK8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 100);
    EXPECT_EQ(bmp.getMode(), splashModeCMYK8);
}
#endif

// Test getAlphaRowSize returns width
TEST_F(SplashBitmapTest_1120, GetAlphaRowSizeEqualsWidth_1120) {
    SplashBitmap bmp(123, 456, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaRowSize(), 123);
}

// Test getAlphaRowSize with different width
TEST_F(SplashBitmapTest_1120, GetAlphaRowSizeDifferentWidth_1120) {
    SplashBitmap bmp(999, 100, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaRowSize(), 999);
}

// Test alpha pointer is non-null when alpha is enabled
TEST_F(SplashBitmapTest_1120, AlphaEnabledReturnsNonNull_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test alpha pointer is null when alpha is disabled
TEST_F(SplashBitmapTest_1120, AlphaDisabledReturnsNull_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test data pointer is non-null
TEST_F(SplashBitmapTest_1120, DataPtrNonNull_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getRowPad returns the value passed in constructor
TEST_F(SplashBitmapTest_1120, GetRowPad_1120) {
    SplashBitmap bmp(100, 100, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 4);
}

// Test getRowPad with value 1
TEST_F(SplashBitmapTest_1120, GetRowPadOne_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 1);
}

// Test getRowSize for RGB8 mode
TEST_F(SplashBitmapTest_1120, GetRowSizeRGB8_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // RGB8 is 3 bytes per pixel, so rowSize should be at least 300
    EXPECT_GE(bmp.getRowSize(), 300);
}

// Test getRowSize for Mono8 mode
TEST_F(SplashBitmapTest_1120, GetRowSizeMono8_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 100);
}

// Test getRowSize for XBGR8 mode (4 bytes per pixel)
TEST_F(SplashBitmapTest_1120, GetRowSizeXBGR8_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 400);
}

// Test width of 1 pixel
TEST_F(SplashBitmapTest_1120, MinimalWidth_1120) {
    SplashBitmap bmp(1, 1, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_EQ(bmp.getAlphaRowSize(), 1);
}

// Test getAlpha on a bitmap with alpha enabled
TEST_F(SplashBitmapTest_1120, GetAlphaValue_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Alpha values should be accessible without crashing
    unsigned char alphaVal = bmp.getAlpha(0, 0);
    // We just verify it doesn't crash; the initial value is implementation-defined
    (void)alphaVal;
}

// Test getPixel on a bitmap
TEST_F(SplashBitmapTest_1120, GetPixelNocrash_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    bmp.getPixel(0, 0, pixel);
    // Just verify it doesn't crash
}

// Test getPixel at boundary
TEST_F(SplashBitmapTest_1120, GetPixelBoundary_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    bmp.getPixel(9, 9, pixel);
    // Just verify it doesn't crash at max valid coordinates
}

// Test getRGBLine
TEST_F(SplashBitmapTest_1120, GetRGBLineNocrash_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[30]; // 10 pixels * 3 bytes
    bmp.getRGBLine(0, line);
    // Just verify no crash
}

// Test getXBGRLine
TEST_F(SplashBitmapTest_1120, GetXBGRLineNocrash_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[40]; // 10 pixels * 4 bytes
    bmp.getXBGRLine(0, line, SplashBitmap::conversionOpaque);
    // Just verify no crash
}

// Test takeData returns non-null and subsequent call returns null
TEST_F(SplashBitmapTest_1120, TakeDataReturnsDataAndNullsIt_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr data = bmp.takeData();
    EXPECT_NE(data, nullptr);
    // After takeData, the internal data should be null
    SplashColorPtr data2 = bmp.takeData();
    EXPECT_EQ(data2, nullptr);
    // We need to free the taken data
    gfree(data);
}

// Test copy static method
TEST_F(SplashBitmapTest_1120, CopyBitmap_1120) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copy = SplashBitmap::copy(&bmp);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), 50);
    EXPECT_EQ(copy->getHeight(), 50);
    EXPECT_EQ(copy->getMode(), splashModeRGB8);
    EXPECT_EQ(copy->getAlphaRowSize(), 50);
    EXPECT_NE(copy->getAlphaPtr(), nullptr);
    delete copy;
}

// Test copy preserves row pad
TEST_F(SplashBitmapTest_1120, CopyPreservesRowPad_1120) {
    SplashBitmap bmp(40, 30, 4, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copy = SplashBitmap::copy(&bmp);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), 40);
    EXPECT_EQ(copy->getHeight(), 30);
    EXPECT_EQ(copy->getRowPad(), bmp.getRowPad());
    delete copy;
}

// Test construction with topDown false
TEST_F(SplashBitmapTest_1120, ConstructTopDownFalse_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, false, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 100);
    // When topDown is false, rowSize should be negative
    EXPECT_LT(bmp.getRowSize(), 0);
}

// Test construction with topDown true yields positive rowSize
TEST_F(SplashBitmapTest_1120, ConstructTopDownTruePositiveRowSize_1120) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GT(bmp.getRowSize(), 0);
}

// Test writePNMFile to a file pointer
TEST_F(SplashBitmapTest_1120, WritePNMFileToFilePtr_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile for RGB8
TEST_F(SplashBitmapTest_1120, WritePNMFileRGB8_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test getSeparationList returns non-null when separation list is provided
TEST_F(SplashBitmapTest_1120, SeparationListNullWhenNotProvided_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // When nullptr is passed, getSeparationList behavior depends on implementation
    // Just ensure it doesn't crash
    auto* sepList = bmp.getSeparationList();
    (void)sepList;
}

// Test large dimensions
TEST_F(SplashBitmapTest_1120, LargeDimensions_1120) {
    SplashBitmap bmp(1000, 1000, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1000);
    EXPECT_EQ(bmp.getHeight(), 1000);
    EXPECT_EQ(bmp.getAlphaRowSize(), 1000);
}

// Test Mono1 row size (should be ceil(width/8))
TEST_F(SplashBitmapTest_1120, Mono1RowSize_1120) {
    SplashBitmap bmp(17, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Mono1: 17 bits = 3 bytes (ceil(17/8) = 3)
    EXPECT_GE(bmp.getRowSize(), 3);
}

// Test that copy operation is deleted (compile-time, but verify copy static works)
TEST_F(SplashBitmapTest_1120, StaticCopyMethod_1120) {
    SplashBitmap bmp(20, 20, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copied = SplashBitmap::copy(&bmp);
    ASSERT_NE(copied, nullptr);
    
    // Verify data pointers are different (deep copy)
    EXPECT_NE(copied->getDataPtr(), bmp.getDataPtr());
    if (bmp.getAlphaPtr() != nullptr) {
        EXPECT_NE(copied->getAlphaPtr(), bmp.getAlphaPtr());
    }
    delete copied;
}

// Test getAlpha at different positions
TEST_F(SplashBitmapTest_1120, GetAlphaMultiplePositions_1120) {
    SplashBitmap bmp(5, 5, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Access alpha at various valid positions
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            // Should not crash
            unsigned char a = bmp.getAlpha(x, y);
            (void)a;
        }
    }
}

// Test getPixel for RGB8 mode
TEST_F(SplashBitmapTest_1120, GetPixelRGB8_1120) {
    SplashBitmap bmp(5, 5, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            bmp.getPixel(x, y, pixel);
        }
    }
}

// Test writeAlphaPGMFile
TEST_F(SplashBitmapTest_1120, WriteAlphaPGMFile_1120) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    // Create a temporary file name
    char tmpName[] = "/tmp/splashbitmaptest_1120_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_GE(fd, 0);
    close(fd);
    
    SplashError err = bmp.writeAlphaPGMFile(tmpName);
    EXPECT_EQ(err, splashOk);
    
    // Clean up
    unlink(tmpName);
}

// Test row padding effect on row size
TEST_F(SplashBitmapTest_1120, RowPaddingAffectsRowSize_1120) {
    SplashBitmap bmp1(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap bmp4(10, 10, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    // Row size with padding 4 should be >= row size with padding 1
    EXPECT_GE(bmp4.getRowSize(), bmp1.getRowSize());
}
