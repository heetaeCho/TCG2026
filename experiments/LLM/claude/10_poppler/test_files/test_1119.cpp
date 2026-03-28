#include <gtest/gtest.h>
#include <memory>
#include <cstdio>
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// Helper to compute expected row size based on mode and width
// We treat the implementation as a black box, but we can verify consistency

class SplashBitmapTest_1119 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with splashModeMono1
TEST_F(SplashBitmapTest_1119, ConstructMono1_1119) {
    SplashBitmap bmp(100, 200, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
    EXPECT_EQ(bmp.getRowPad(), 1);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_GT(bmp.getRowSize(), 0);
}

// Test basic construction with splashModeMono8
TEST_F(SplashBitmapTest_1119, ConstructMono8_1119) {
    SplashBitmap bmp(50, 75, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 75);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
    // For Mono8, rowSize should be at least width
    EXPECT_GE(bmp.getRowSize(), 50);
}

// Test construction with splashModeRGB8
TEST_F(SplashBitmapTest_1119, ConstructRGB8_1119) {
    SplashBitmap bmp(320, 240, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 320);
    EXPECT_EQ(bmp.getHeight(), 240);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
    // For RGB8, rowSize should be at least width * 3
    EXPECT_GE(bmp.getRowSize(), 320 * 3);
}

// Test construction with splashModeXBGR8
TEST_F(SplashBitmapTest_1119, ConstructXBGR8_1119) {
    SplashBitmap bmp(640, 480, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 640);
    EXPECT_EQ(bmp.getHeight(), 480);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
    // For XBGR8, rowSize should be at least width * 4
    EXPECT_GE(bmp.getRowSize(), 640 * 4);
}

// Test construction with alpha
TEST_F(SplashBitmapTest_1119, ConstructWithAlpha_1119) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
    EXPECT_EQ(bmp.getAlphaRowSize(), 100);
}

// Test construction without alpha
TEST_F(SplashBitmapTest_1119, ConstructWithoutAlpha_1119) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Without alpha, alpha pointer may be null
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test getRowSize for Mono1 - should be ceil(width/8)
TEST_F(SplashBitmapTest_1119, GetRowSizeMono1_1119) {
    SplashBitmap bmp(17, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // 17 bits -> at least 3 bytes
    EXPECT_GE(bmp.getRowSize(), 3);
}

// Test getAlphaRowSize matches width
TEST_F(SplashBitmapTest_1119, GetAlphaRowSize_1119) {
    SplashBitmap bmp(256, 128, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaRowSize(), 256);
}

// Test getPixel retrieves a pixel without crashing
TEST_F(SplashBitmapTest_1119, GetPixelBasic_1119) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Should not crash
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(9, 9, pixel);
}

// Test getAlpha retrieves alpha value
TEST_F(SplashBitmapTest_1119, GetAlphaBasic_1119) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Should not crash; alpha is valid since we requested it
    unsigned char a = bmp.getAlpha(0, 0);
    // Just verify it returns without error (value depends on initialization)
    (void)a;
}

// Test width of 1
TEST_F(SplashBitmapTest_1119, MinimalWidth_1119) {
    SplashBitmap bmp(1, 1, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_GE(bmp.getRowSize(), 3);
}

// Test rowPad effect
TEST_F(SplashBitmapTest_1119, RowPadEffect_1119) {
    SplashBitmap bmp1(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap bmp4(10, 10, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    EXPECT_EQ(bmp1.getRowPad(), 1);
    EXPECT_EQ(bmp4.getRowPad(), 4);
    
    // With rowPad=4, rowSize should be a multiple of 4
    EXPECT_EQ(bmp4.getRowSize() % 4, 0);
}

// Test copy function
TEST_F(SplashBitmapTest_1119, CopyBitmap_1119) {
    SplashBitmap src(50, 30, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copy = SplashBitmap::copy(&src);
    
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), src.getWidth());
    EXPECT_EQ(copy->getHeight(), src.getHeight());
    EXPECT_EQ(copy->getRowSize(), src.getRowSize());
    EXPECT_EQ(copy->getMode(), src.getMode());
    EXPECT_EQ(copy->getRowPad(), src.getRowPad());
    
    // Data pointers should be different (deep copy)
    EXPECT_NE(copy->getDataPtr(), src.getDataPtr());
    
    delete copy;
}

// Test takeData transfers ownership
TEST_F(SplashBitmapTest_1119, TakeData_1119) {
    SplashBitmap bmp(20, 20, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr origData = bmp.getDataPtr();
    EXPECT_NE(origData, nullptr);
    
    SplashColorPtr takenData = bmp.takeData();
    EXPECT_EQ(takenData, origData);
    
    // After takeData, the internal data pointer should be null
    EXPECT_EQ(bmp.getDataPtr(), nullptr);
    
    // Clean up the taken data
    gfree(takenData);
}

// Test getRGBLine doesn't crash
TEST_F(SplashBitmapTest_1119, GetRGBLine_1119) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor line[100 * 3];
    // Should not crash
    bmp.getRGBLine(0, (SplashColorPtr)line);
    bmp.getRGBLine(49, (SplashColorPtr)line);
}

// Test getXBGRLine doesn't crash
TEST_F(SplashBitmapTest_1119, GetXBGRLine_1119) {
    SplashBitmap bmp(100, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[100 * 4];
    bmp.getXBGRLine(0, (SplashColorPtr)line, SplashBitmap::conversionOpaque);
}

// Test getSeparationList returns a valid pointer when separation list was provided
TEST_F(SplashBitmapTest_1119, GetSeparationList_1119) {
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepList;
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, &sepList);
    auto* result = bmp.getSeparationList();
    EXPECT_NE(result, nullptr);
}

// Test Mono8 rowSize equals width (with rowPad=1)
TEST_F(SplashBitmapTest_1119, Mono8RowSizeEqualsWidth_1119) {
    SplashBitmap bmp(123, 50, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowSize(), 123);
}

// Test large bitmap dimensions
TEST_F(SplashBitmapTest_1119, LargeDimensions_1119) {
    SplashBitmap bmp(2000, 2000, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 2000);
    EXPECT_EQ(bmp.getHeight(), 2000);
    EXPECT_GE(bmp.getRowSize(), 2000);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test writePNMFile to a FILE pointer (valid case for Mono8)
TEST_F(SplashBitmapTest_1119, WritePNMFileToFILE_1119) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    
    // Check that something was written
    long sz = ftell(f);
    EXPECT_GT(sz, 0);
    
    fclose(f);
}

// Test writePNMFile for RGB8
TEST_F(SplashBitmapTest_1119, WritePNMFileRGB8_1119) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    
    fclose(f);
}

// Test writeAlphaPGMFile with alpha enabled
TEST_F(SplashBitmapTest_1119, WriteAlphaPGMFile_1119) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    char tmpName[] = "/tmp/splashbmp_test_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    close(fd);
    
    SplashError err = bmp.writeAlphaPGMFile(tmpName);
    EXPECT_EQ(err, splashOk);
    
    unlink(tmpName);
}

// Test that rowPad=8 aligns rowSize
TEST_F(SplashBitmapTest_1119, RowPad8Alignment_1119) {
    SplashBitmap bmp(13, 10, 8, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowSize() % 8, 0);
}

// Test getPixel at boundary positions
TEST_F(SplashBitmapTest_1119, GetPixelBoundary_1119) {
    SplashBitmap bmp(5, 5, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    
    // Top-left corner
    bmp.getPixel(0, 0, pixel);
    // Bottom-right corner
    bmp.getPixel(4, 4, pixel);
    // Top-right corner
    bmp.getPixel(4, 0, pixel);
    // Bottom-left corner
    bmp.getPixel(0, 4, pixel);
}

// Test convertToXBGR
TEST_F(SplashBitmapTest_1119, ConvertToXBGR_1119) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    bool result = bmp.convertToXBGR(SplashBitmap::conversionOpaque);
    // After conversion, mode should be XBGR8 if successful
    if (result) {
        EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
    }
}

// Test that copy preserves pixel data
TEST_F(SplashBitmapTest_1119, CopyPreservesPixelData_1119) {
    SplashBitmap src(5, 5, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    SplashBitmap* copy = SplashBitmap::copy(&src);
    ASSERT_NE(copy, nullptr);
    
    // Verify that pixel data is the same
    SplashColor srcPixel, copyPixel;
    src.getPixel(0, 0, srcPixel);
    copy->getPixel(0, 0, copyPixel);
    EXPECT_EQ(srcPixel[0], copyPixel[0]);
    EXPECT_EQ(srcPixel[1], copyPixel[1]);
    EXPECT_EQ(srcPixel[2], copyPixel[2]);
    
    // Verify alpha is the same
    unsigned char srcAlpha = src.getAlpha(0, 0);
    unsigned char copyAlpha = copy->getAlpha(0, 0);
    EXPECT_EQ(srcAlpha, copyAlpha);
    
    delete copy;
}
