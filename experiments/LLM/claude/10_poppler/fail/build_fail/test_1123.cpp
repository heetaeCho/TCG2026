#include <gtest/gtest.h>
#include <cstring>
#include <memory>
#include <vector>

#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// Test fixture for SplashBitmap tests
class SplashBitmapTest_1123 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with splashModeMono1
TEST_F(SplashBitmapTest_1123, ConstructMono1_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
}

// Test basic construction with splashModeMono8
TEST_F(SplashBitmapTest_1123, ConstructMono8_1123) {
    SplashBitmap bmp(20, 30, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 20);
    EXPECT_EQ(bmp.getHeight(), 30);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
}

// Test basic construction with splashModeRGB8
TEST_F(SplashBitmapTest_1123, ConstructRGB8_1123) {
    SplashBitmap bmp(100, 200, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
}

// Test basic construction with splashModeXBGR8
TEST_F(SplashBitmapTest_1123, ConstructXBGR8_1123) {
    SplashBitmap bmp(50, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 50);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
}

// Test basic construction with splashModeBGR8
TEST_F(SplashBitmapTest_1123, ConstructBGR8_1123) {
    SplashBitmap bmp(64, 64, 1, splashModeBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 64);
    EXPECT_EQ(bmp.getHeight(), 64);
    EXPECT_EQ(bmp.getMode(), splashModeBGR8);
}

// Test getDataPtr returns non-null
TEST_F(SplashBitmapTest_1123, GetDataPtrNotNull_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test alpha pointer when alpha is enabled
TEST_F(SplashBitmapTest_1123, GetAlphaPtrWithAlpha_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test alpha pointer when alpha is disabled
TEST_F(SplashBitmapTest_1123, GetAlphaPtrWithoutAlpha_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test getWidth
TEST_F(SplashBitmapTest_1123, GetWidth_1123) {
    SplashBitmap bmp(123, 456, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 123);
}

// Test getHeight
TEST_F(SplashBitmapTest_1123, GetHeight_1123) {
    SplashBitmap bmp(123, 456, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getHeight(), 456);
}

// Test getRowPad
TEST_F(SplashBitmapTest_1123, GetRowPad_1123) {
    SplashBitmap bmp(10, 10, 4, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 4);
}

// Test getRowSize for Mono8 mode
TEST_F(SplashBitmapTest_1123, GetRowSizeMono8_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 10);
}

// Test getRowSize for RGB8 mode
TEST_F(SplashBitmapTest_1123, GetRowSizeRGB8_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 30); // at least 10 * 3 bytes
}

// Test getRowSize for XBGR8 mode
TEST_F(SplashBitmapTest_1123, GetRowSizeXBGR8_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 40); // at least 10 * 4 bytes
}

// Test getAlphaRowSize
TEST_F(SplashBitmapTest_1123, GetAlphaRowSize_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getAlphaRowSize(), 10);
}

// Test width = 1, height = 1 boundary
TEST_F(SplashBitmapTest_1123, MinimumSize_1123) {
    SplashBitmap bmp(1, 1, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getPixel for Mono8
TEST_F(SplashBitmapTest_1123, GetPixelMono8_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Should not crash; pixel is just read from data
    bmp.getPixel(0, 0, pixel);
}

// Test getPixel for RGB8
TEST_F(SplashBitmapTest_1123, GetPixelRGB8_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(9, 9, pixel);
}

// Test getAlpha when alpha is enabled
TEST_F(SplashBitmapTest_1123, GetAlphaEnabled_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Should not crash
    unsigned char a = bmp.getAlpha(0, 0);
    (void)a;
}

// Test takeData transfers ownership and nullifies internal pointer
TEST_F(SplashBitmapTest_1123, TakeData_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr ptr = bmp.getDataPtr();
    EXPECT_NE(ptr, nullptr);
    SplashColorPtr takenData = bmp.takeData();
    EXPECT_NE(takenData, nullptr);
    // After takeData, getDataPtr should return nullptr
    EXPECT_EQ(bmp.getDataPtr(), nullptr);
    // Clean up taken data
    gfree(takenData);
}

// Test copy creates a valid copy
TEST_F(SplashBitmapTest_1123, CopyBitmap_1123) {
    SplashBitmap original(15, 25, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copy = SplashBitmap::copy(&original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), original.getWidth());
    EXPECT_EQ(copy->getHeight(), original.getHeight());
    EXPECT_EQ(copy->getMode(), original.getMode());
    EXPECT_EQ(copy->getRowSize(), original.getRowSize());
    // Data pointers should be different (independent copy)
    EXPECT_NE(copy->getDataPtr(), original.getDataPtr());
    delete copy;
}

// Test getRGBLine doesn't crash
TEST_F(SplashBitmapTest_1123, GetRGBLine_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[30]; // 10 pixels * 3 bytes
    bmp.getRGBLine(0, line);
    bmp.getRGBLine(9, line);
}

// Test getXBGRLine doesn't crash
TEST_F(SplashBitmapTest_1123, GetXBGRLine_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[40]; // 10 pixels * 4 bytes
    bmp.getXBGRLine(0, line, SplashBitmap::conversionOpaque);
}

// Test with rowPad = 1
TEST_F(SplashBitmapTest_1123, RowPadOne_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 1);
    EXPECT_GE(bmp.getRowSize(), 10);
}

// Test with larger rowPad
TEST_F(SplashBitmapTest_1123, RowPadLarger_1123) {
    SplashBitmap bmp(10, 10, 8, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 8);
    // Row size should be padded to multiple of 8
    EXPECT_EQ(bmp.getRowSize() % 8, 0);
}

// Test Mono1 row size calculation
TEST_F(SplashBitmapTest_1123, Mono1RowSize_1123) {
    SplashBitmap bmp(17, 5, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 17);
    // Mono1: ceil(17/8) = 3 bytes per row minimum
    EXPECT_GE(bmp.getRowSize(), 3);
}

// Test topDown = false construction
TEST_F(SplashBitmapTest_1123, BottomUpConstruction_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, false, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    // Bottom-up bitmaps typically have negative row size
    EXPECT_LT(bmp.getRowSize(), 0);
}

// Test getSeparationList returns a pointer (may be null if no separation list)
TEST_F(SplashBitmapTest_1123, GetSeparationList_1123) {
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepList;
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, &sepList);
    auto *sl = bmp.getSeparationList();
    EXPECT_NE(sl, nullptr);
}

// Test writePNMFile to a FILE
TEST_F(SplashBitmapTest_1123, WritePNMFileToStream_1123) {
    SplashBitmap bmp(5, 5, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile for RGB8
TEST_F(SplashBitmapTest_1123, WritePNMFileRGB8_1123) {
    SplashBitmap bmp(5, 5, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile for Mono1
TEST_F(SplashBitmapTest_1123, WritePNMFileMono1_1123) {
    SplashBitmap bmp(8, 4, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writeAlphaPGMFile with no alpha returns error
TEST_F(SplashBitmapTest_1123, WriteAlphaPGMNoAlpha_1123) {
    SplashBitmap bmp(5, 5, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Without alpha, writing alpha PGM should fail or produce an error
    // We create a temp file name
    char tmpName[] = "/tmp/splashtest_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        close(fd);
        SplashError err = bmp.writeAlphaPGMFile(tmpName);
        EXPECT_NE(err, splashOk);
        unlink(tmpName);
    }
}

// Test large bitmap
TEST_F(SplashBitmapTest_1123, LargerBitmap_1123) {
    SplashBitmap bmp(1000, 1000, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1000);
    EXPECT_EQ(bmp.getHeight(), 1000);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test getPixel at boundary coordinates
TEST_F(SplashBitmapTest_1123, GetPixelBoundary_1123) {
    SplashBitmap bmp(5, 5, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Top-left
    bmp.getPixel(0, 0, pixel);
    // Bottom-right
    bmp.getPixel(4, 4, pixel);
}

// Test getAlpha at boundary
TEST_F(SplashBitmapTest_1123, GetAlphaBoundary_1123) {
    SplashBitmap bmp(5, 5, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char a0 = bmp.getAlpha(0, 0);
    unsigned char a1 = bmp.getAlpha(4, 4);
    (void)a0;
    (void)a1;
}

// Test copy with alpha
TEST_F(SplashBitmapTest_1123, CopyBitmapWithAlpha_1123) {
    SplashBitmap original(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copy = SplashBitmap::copy(&original);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy->getAlphaPtr(), nullptr);
    EXPECT_NE(copy->getAlphaPtr(), original.getAlphaPtr());
    delete copy;
}

// Test convertToXBGR from RGB8
TEST_F(SplashBitmapTest_1123, ConvertToXBGRFromRGB8_1123) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    bool result = bmp.convertToXBGR(SplashBitmap::conversionOpaque);
    // Conversion from RGB8 to XBGR8 should succeed
    if (result) {
        EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
    }
}
