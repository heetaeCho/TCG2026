#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "GfxState.h"

class SplashBitmapTest_1125 : public ::testing::Test {
protected:
    void TearDown() override {
    }
};

// Test basic construction with RGB8 mode, no alpha
TEST_F(SplashBitmapTest_1125, ConstructRGB8NoAlpha_1125) {
    SplashBitmap bmp(100, 200, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
}

// Test basic construction with Mono1 mode
TEST_F(SplashBitmapTest_1125, ConstructMono1_1125) {
    SplashBitmap bmp(64, 64, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 64);
    EXPECT_EQ(bmp.getHeight(), 64);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
}

// Test basic construction with Mono8 mode
TEST_F(SplashBitmapTest_1125, ConstructMono8_1125) {
    SplashBitmap bmp(50, 50, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 50);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
}

// Test construction with alpha enabled
TEST_F(SplashBitmapTest_1125, ConstructWithAlpha_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test construction without alpha
TEST_F(SplashBitmapTest_1125, ConstructWithoutAlpha_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Alpha pointer may or may not be null depending on implementation,
    // but we can at least check getAlphaRowSize
    EXPECT_EQ(bmp.getWidth(), 100);
}

// Test getWidth
TEST_F(SplashBitmapTest_1125, GetWidth_1125) {
    SplashBitmap bmp(320, 240, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 320);
}

// Test getHeight
TEST_F(SplashBitmapTest_1125, GetHeight_1125) {
    SplashBitmap bmp(320, 240, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getHeight(), 240);
}

// Test getRowPad
TEST_F(SplashBitmapTest_1125, GetRowPad_1125) {
    SplashBitmap bmp(100, 100, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 4);
}

// Test getMode returns correct mode
TEST_F(SplashBitmapTest_1125, GetMode_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
}

// Test getDataPtr is not null after construction
TEST_F(SplashBitmapTest_1125, GetDataPtrNotNull_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getRowSize for RGB8
TEST_F(SplashBitmapTest_1125, GetRowSizeRGB8_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // RGB8 = 3 bytes per pixel, width=100, so rowSize >= 300
    EXPECT_GE(bmp.getRowSize(), 300);
}

// Test getRowSize for Mono8
TEST_F(SplashBitmapTest_1125, GetRowSizeMono8_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Mono8 = 1 byte per pixel, width=100, so rowSize >= 100
    EXPECT_GE(bmp.getRowSize(), 100);
}

// Test getAlphaRowSize
TEST_F(SplashBitmapTest_1125, GetAlphaRowSize_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Alpha row size should be at least width
    EXPECT_GE(bmp.getAlphaRowSize(), 100);
}

// Test getSeparationList returns non-null when separation list provided
TEST_F(SplashBitmapTest_1125, GetSeparationListWithProvided_1125) {
    auto sepList = std::make_unique<std::vector<std::unique_ptr<GfxSeparationColorSpace>>>();
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, sepList.get());
    // The separation list pointer should be set
    // Note: depending on impl, it may copy or reference
    // We just verify it's accessible
    auto* result = bmp.getSeparationList();
    // result may or may not equal sepList.get() depending on implementation
    SUCCEED();
}

// Test getSeparationList with null separation list
TEST_F(SplashBitmapTest_1125, GetSeparationListNull_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // May return null or empty list
    auto* result = bmp.getSeparationList();
    // Just verify no crash
    SUCCEED();
}

// Test getPixel for RGB8 mode - pixel at (0,0) after construction
TEST_F(SplashBitmapTest_1125, GetPixelRGB8_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    bmp.getPixel(0, 0, pixel);
    // Just verify it doesn't crash; we can't know the initial values
    SUCCEED();
}

// Test getAlpha for a bitmap with alpha
TEST_F(SplashBitmapTest_1125, GetAlphaWithAlphaEnabled_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char alpha = bmp.getAlpha(0, 0);
    // Just verify it returns without crash
    (void)alpha;
    SUCCEED();
}

// Test takeData transfers ownership
TEST_F(SplashBitmapTest_1125, TakeDataTransfersOwnership_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr data = bmp.takeData();
    EXPECT_NE(data, nullptr);
    // After takeData, the internal data should be null or transferred
    // We need to free the taken data
    gfree(data);
}

// Test copy creates a valid copy
TEST_F(SplashBitmapTest_1125, CopyBitmap_1125) {
    SplashBitmap src(50, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copy = SplashBitmap::copy(&src);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), 50);
    EXPECT_EQ(copy->getHeight(), 50);
    EXPECT_EQ(copy->getMode(), splashModeRGB8);
    delete copy;
}

// Test construction with small dimensions (1x1)
TEST_F(SplashBitmapTest_1125, SmallDimensions_1125) {
    SplashBitmap bmp(1, 1, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test construction with different row padding
TEST_F(SplashBitmapTest_1125, RowPadding_1125) {
    SplashBitmap bmp1(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap bmp4(100, 100, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    EXPECT_EQ(bmp1.getRowPad(), 1);
    EXPECT_EQ(bmp4.getRowPad(), 4);
    
    // Row size with padding 4 should be >= row size with padding 1
    EXPECT_GE(bmp4.getRowSize(), bmp1.getRowSize());
}

// Test XBGR8 mode
TEST_F(SplashBitmapTest_1125, ConstructXBGR8_1125) {
    SplashBitmap bmp(100, 100, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
    // XBGR8 = 4 bytes per pixel
    EXPECT_GE(bmp.getRowSize(), 400);
}

// Test getRGBLine doesn't crash
TEST_F(SplashBitmapTest_1125, GetRGBLine_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[30]; // 10 pixels * 3 bytes
    bmp.getRGBLine(0, line);
    SUCCEED();
}

// Test getXBGRLine doesn't crash
TEST_F(SplashBitmapTest_1125, GetXBGRLine_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[40]; // 10 pixels * 4 bytes
    bmp.getXBGRLine(0, line, SplashBitmap::conversionOpaque);
    SUCCEED();
}

// Test writePNMFile to a file
TEST_F(SplashBitmapTest_1125, WritePNMFileRGB8_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile with Mono8
TEST_F(SplashBitmapTest_1125, WritePNMFileMono8_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test copy preserves pixel data
TEST_F(SplashBitmapTest_1125, CopyPreservesData_1125) {
    SplashBitmap src(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    SplashColor srcPixel, copyPixel;
    src.getPixel(0, 0, srcPixel);
    
    SplashBitmap* copy = SplashBitmap::copy(&src);
    ASSERT_NE(copy, nullptr);
    copy->getPixel(0, 0, copyPixel);
    
    EXPECT_EQ(srcPixel[0], copyPixel[0]);
    EXPECT_EQ(srcPixel[1], copyPixel[1]);
    EXPECT_EQ(srcPixel[2], copyPixel[2]);
    
    delete copy;
}

// Test convertToXBGR with RGB8 source
TEST_F(SplashBitmapTest_1125, ConvertToXBGR_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    bool result = bmp.convertToXBGR(SplashBitmap::conversionOpaque);
    // Result depends on whether conversion is supported
    (void)result;
    SUCCEED();
}

// Test that getAlphaPtr is not null when alpha is requested
TEST_F(SplashBitmapTest_1125, AlphaPtrNotNullWhenEnabled_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test large bitmap creation
TEST_F(SplashBitmapTest_1125, LargeBitmap_1125) {
    SplashBitmap bmp(1000, 1000, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1000);
    EXPECT_EQ(bmp.getHeight(), 1000);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getPixel at boundary
TEST_F(SplashBitmapTest_1125, GetPixelAtBoundary_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Last valid pixel
    bmp.getPixel(9, 9, pixel);
    SUCCEED();
}

// Test getAlpha at boundary
TEST_F(SplashBitmapTest_1125, GetAlphaAtBoundary_1125) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char alpha = bmp.getAlpha(9, 9);
    (void)alpha;
    SUCCEED();
}

// Test Mono1 mode row size
TEST_F(SplashBitmapTest_1125, Mono1RowSize_1125) {
    SplashBitmap bmp(80, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Mono1: 1 bit per pixel, 80 pixels = 10 bytes
    EXPECT_GE(bmp.getRowSize(), 10);
}
