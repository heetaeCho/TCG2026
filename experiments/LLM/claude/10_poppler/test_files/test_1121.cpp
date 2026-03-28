#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// Test fixture for SplashBitmap tests
class SplashBitmapTest_1121 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test basic construction with splashModeMono1
TEST_F(SplashBitmapTest_1121, ConstructMono1_1121) {
    SplashBitmap bmp(100, 200, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
    EXPECT_EQ(bmp.getRowPad(), 1);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
}

// Test basic construction with splashModeMono8
TEST_F(SplashBitmapTest_1121, ConstructMono8_1121) {
    SplashBitmap bmp(50, 75, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 75);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
}

// Test basic construction with splashModeRGB8
TEST_F(SplashBitmapTest_1121, ConstructRGB8_1121) {
    SplashBitmap bmp(320, 240, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 320);
    EXPECT_EQ(bmp.getHeight(), 240);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
}

// Test construction with splashModeXBGR8
TEST_F(SplashBitmapTest_1121, ConstructXBGR8_1121) {
    SplashBitmap bmp(640, 480, 1, splashModeXBGR8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 640);
    EXPECT_EQ(bmp.getHeight(), 480);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
}

// Test construction with splashModeBGR8
TEST_F(SplashBitmapTest_1121, ConstructBGR8_1121) {
    SplashBitmap bmp(10, 20, 1, splashModeBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 20);
    EXPECT_EQ(bmp.getMode(), splashModeBGR8);
}

// Test getRowPad returns the value passed during construction
TEST_F(SplashBitmapTest_1121, GetRowPadReturnsConstructedValue_1121) {
    SplashBitmap bmp1(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp1.getRowPad(), 1);

    SplashBitmap bmp4(10, 10, 4, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp4.getRowPad(), 4);
}

// Test getDataPtr returns non-null for valid bitmap
TEST_F(SplashBitmapTest_1121, GetDataPtrNotNull_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getAlphaPtr when alpha is enabled
TEST_F(SplashBitmapTest_1121, GetAlphaPtrWithAlpha_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test getAlphaPtr when alpha is disabled
TEST_F(SplashBitmapTest_1121, GetAlphaPtrWithoutAlpha_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test getRowSize returns positive value for valid bitmap
TEST_F(SplashBitmapTest_1121, GetRowSizePositive_1121) {
    SplashBitmap bmp(100, 100, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GT(bmp.getRowSize(), 0);
}

// Test getRowSize for Mono8 mode
TEST_F(SplashBitmapTest_1121, GetRowSizeMono8_1121) {
    SplashBitmap bmp(100, 50, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Mono8 should have rowSize >= width (1 byte per pixel)
    EXPECT_GE(bmp.getRowSize(), 100);
}

// Test getRowSize for RGB8 mode
TEST_F(SplashBitmapTest_1121, GetRowSizeRGB8_1121) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // RGB8 should have rowSize >= width * 3
    EXPECT_GE(bmp.getRowSize(), 300);
}

// Test getAlphaRowSize
TEST_F(SplashBitmapTest_1121, GetAlphaRowSize_1121) {
    SplashBitmap bmp(100, 50, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Alpha row size should be >= width (1 byte per pixel)
    EXPECT_GE(bmp.getAlphaRowSize(), 100);
}

// Test getPixel on valid coordinates
TEST_F(SplashBitmapTest_1121, GetPixelValidCoords_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Should not crash
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(5, 5, pixel);
    bmp.getPixel(9, 9, pixel);
}

// Test getAlpha returns value for valid coordinates with alpha enabled
TEST_F(SplashBitmapTest_1121, GetAlphaValidCoords_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char alpha = bmp.getAlpha(0, 0);
    // Alpha value should be in valid range [0, 255]
    EXPECT_GE(alpha, 0);
    EXPECT_LE(alpha, 255);
}

// Test 1x1 bitmap (minimum size)
TEST_F(SplashBitmapTest_1121, MinimumSizeBitmap_1121) {
    SplashBitmap bmp(1, 1, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test copy function
TEST_F(SplashBitmapTest_1121, CopyBitmap_1121) {
    SplashBitmap original(50, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copyPtr = SplashBitmap::copy(&original);
    ASSERT_NE(copyPtr, nullptr);
    EXPECT_EQ(copyPtr->getWidth(), original.getWidth());
    EXPECT_EQ(copyPtr->getHeight(), original.getHeight());
    EXPECT_EQ(copyPtr->getMode(), original.getMode());
    EXPECT_EQ(copyPtr->getRowPad(), original.getRowPad());
    EXPECT_EQ(copyPtr->getRowSize(), original.getRowSize());
    delete copyPtr;
}

// Test takeData returns non-null and subsequent call returns null
TEST_F(SplashBitmapTest_1121, TakeDataReturnsData_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr data = bmp.takeData();
    EXPECT_NE(data, nullptr);
    // After takeData, internal data should be taken away
    SplashColorPtr data2 = bmp.takeData();
    EXPECT_EQ(data2, nullptr);
    gfree(data);
}

// Test getRGBLine doesn't crash for valid y
TEST_F(SplashBitmapTest_1121, GetRGBLineValid_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor line[10 * 3];
    // Should not crash
    bmp.getRGBLine(0, (SplashColorPtr)line);
    bmp.getRGBLine(9, (SplashColorPtr)line);
}

// Test getXBGRLine doesn't crash for XBGR8 mode
TEST_F(SplashBitmapTest_1121, GetXBGRLineValid_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[10 * 4];
    bmp.getXBGRLine(0, (SplashColorPtr)line, SplashBitmap::conversionOpaque);
}

// Test getRowSize for XBGR8 mode (4 bytes per pixel)
TEST_F(SplashBitmapTest_1121, GetRowSizeXBGR8_1121) {
    SplashBitmap bmp(100, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // XBGR8 should have rowSize >= width * 4
    EXPECT_GE(bmp.getRowSize(), 400);
}

// Test with different row pad values
TEST_F(SplashBitmapTest_1121, DifferentRowPadValues_1121) {
    SplashBitmap bmp1(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap bmp4(10, 10, 4, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);

    EXPECT_EQ(bmp1.getRowPad(), 1);
    EXPECT_EQ(bmp4.getRowPad(), 4);

    // With pad 4, row size should be a multiple of 4
    EXPECT_EQ(bmp4.getRowSize() % 4, 0);
}

// Test Mono1 getRowSize
TEST_F(SplashBitmapTest_1121, GetRowSizeMono1_1121) {
    SplashBitmap bmp(15, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Mono1: 15 pixels = 2 bytes (ceil(15/8))
    EXPECT_GE(bmp.getRowSize(), 2);
}

// Test getSeparationList returns a list (may be null if not provided)
TEST_F(SplashBitmapTest_1121, GetSeparationListDefault_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // When nullptr is passed, separation list behavior depends on implementation
    // At minimum this should not crash
    auto* sepList = bmp.getSeparationList();
    (void)sepList;
}

// Test with separation list provided
TEST_F(SplashBitmapTest_1121, WithSeparationList_1121) {
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepList;
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, &sepList);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
}

// Test large bitmap dimensions
TEST_F(SplashBitmapTest_1121, LargerBitmap_1121) {
    SplashBitmap bmp(1000, 1000, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1000);
    EXPECT_EQ(bmp.getHeight(), 1000);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
    EXPECT_GE(bmp.getRowSize(), 3000);
}

// Test writePNMFile to a FILE pointer (use tmpfile)
TEST_F(SplashBitmapTest_1121, WritePNMFileToFILE_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile with RGB8 mode
TEST_F(SplashBitmapTest_1121, WritePNMFileRGB8_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test topDown parameter (false)
TEST_F(SplashBitmapTest_1121, TopDownFalse_1121) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, false, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test copy preserves pixel data
TEST_F(SplashBitmapTest_1121, CopyPreservesPixelData_1121) {
    SplashBitmap original(5, 5, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    // Get a pixel from original
    SplashColor origPixel;
    original.getPixel(0, 0, origPixel);
    
    SplashBitmap* copyPtr = SplashBitmap::copy(&original);
    ASSERT_NE(copyPtr, nullptr);
    
    SplashColor copyPixel;
    copyPtr->getPixel(0, 0, copyPixel);
    
    EXPECT_EQ(origPixel[0], copyPixel[0]);
    delete copyPtr;
}

// Test that copy data pointers are different (deep copy)
TEST_F(SplashBitmapTest_1121, CopyIsDeepCopy_1121) {
    SplashBitmap original(10, 10, 1, splashModeMono8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copyPtr = SplashBitmap::copy(&original);
    ASSERT_NE(copyPtr, nullptr);
    
    EXPECT_NE(copyPtr->getDataPtr(), original.getDataPtr());
    EXPECT_NE(copyPtr->getAlphaPtr(), original.getAlphaPtr());
    
    delete copyPtr;
}
