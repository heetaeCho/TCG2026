#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <vector>

#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// Test fixture for SplashBitmap tests
class SplashBitmapTest_1122 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with Mono1 mode
TEST_F(SplashBitmapTest_1122, ConstructMono1_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
    EXPECT_EQ(bmp.getMode(), splashModeMono1);
}

// Test basic construction with Mono8 mode
TEST_F(SplashBitmapTest_1122, ConstructMono8_1122) {
    SplashBitmap bmp(20, 30, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 20);
    EXPECT_EQ(bmp.getHeight(), 30);
    EXPECT_EQ(bmp.getMode(), splashModeMono8);
}

// Test basic construction with RGB8 mode
TEST_F(SplashBitmapTest_1122, ConstructRGB8_1122) {
    SplashBitmap bmp(100, 200, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
    EXPECT_EQ(bmp.getMode(), splashModeRGB8);
}

// Test basic construction with XBGR8 mode
TEST_F(SplashBitmapTest_1122, ConstructXBGR8_1122) {
    SplashBitmap bmp(50, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 50);
    EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
}

// Test basic construction with BGR8 mode
TEST_F(SplashBitmapTest_1122, ConstructBGR8_1122) {
    SplashBitmap bmp(64, 64, 1, splashModeBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 64);
    EXPECT_EQ(bmp.getHeight(), 64);
    EXPECT_EQ(bmp.getMode(), splashModeBGR8);
}

// Test construction with alpha enabled
TEST_F(SplashBitmapTest_1122, ConstructWithAlpha_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test construction without alpha
TEST_F(SplashBitmapTest_1122, ConstructWithoutAlpha_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
}

// Test getDataPtr returns non-null for valid bitmap
TEST_F(SplashBitmapTest_1122, GetDataPtrNonNull_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test getRowSize for RGB8 mode
TEST_F(SplashBitmapTest_1122, GetRowSizeRGB8_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // RGB8 should have at least 3 bytes per pixel * width
    EXPECT_GE(bmp.getRowSize(), 10 * 3);
}

// Test getRowSize for Mono8 mode
TEST_F(SplashBitmapTest_1122, GetRowSizeMono8_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 10);
}

// Test getRowSize for XBGR8 mode
TEST_F(SplashBitmapTest_1122, GetRowSizeXBGR8_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // XBGR8 should have 4 bytes per pixel
    EXPECT_GE(bmp.getRowSize(), 10 * 4);
}

// Test getAlphaRowSize
TEST_F(SplashBitmapTest_1122, GetAlphaRowSize_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaRowSize(), 10);
}

// Test getRowPad returns the value passed to constructor
TEST_F(SplashBitmapTest_1122, GetRowPad_1122) {
    SplashBitmap bmp(10, 10, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 4);
}

// Test getPixel retrieves pixel data
TEST_F(SplashBitmapTest_1122, GetPixelRGB8_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Just ensure calling getPixel doesn't crash for valid coordinates
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(9, 9, pixel);
}

// Test getPixel for Mono8
TEST_F(SplashBitmapTest_1122, GetPixelMono8_1122) {
    SplashBitmap bmp(5, 5, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(4, 4, pixel);
}

// Test getAlpha with alpha enabled
TEST_F(SplashBitmapTest_1122, GetAlphaWithAlphaEnabled_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Alpha should be accessible for valid coordinates
    unsigned char alpha = bmp.getAlpha(0, 0);
    // Just verify no crash; initial alpha value is implementation-defined
    (void)alpha;
}

// Test 1x1 bitmap (minimum size)
TEST_F(SplashBitmapTest_1122, MinimumSize_1122) {
    SplashBitmap bmp(1, 1, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    SplashColor pixel;
    bmp.getPixel(0, 0, pixel);
    unsigned char alpha = bmp.getAlpha(0, 0);
    (void)alpha;
}

// Test large bitmap
TEST_F(SplashBitmapTest_1122, LargerBitmap_1122) {
    SplashBitmap bmp(1000, 1000, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1000);
    EXPECT_EQ(bmp.getHeight(), 1000);
}

// Test copy static method
TEST_F(SplashBitmapTest_1122, CopyBitmap_1122) {
    SplashBitmap src(10, 20, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap *copy = SplashBitmap::copy(&src);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getWidth(), src.getWidth());
    EXPECT_EQ(copy->getHeight(), src.getHeight());
    EXPECT_EQ(copy->getMode(), src.getMode());
    EXPECT_EQ(copy->getRowSize(), src.getRowSize());
    delete copy;
}

// Test copy preserves pixel data
TEST_F(SplashBitmapTest_1122, CopyPreservesData_1122) {
    SplashBitmap src(5, 5, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Write a pixel to the source
    SplashColorPtr srcData = src.getDataPtr();
    if (srcData) {
        srcData[0] = 0xAB;
        srcData[1] = 0xCD;
        srcData[2] = 0xEF;
    }
    SplashBitmap *copy = SplashBitmap::copy(&src);
    ASSERT_NE(copy, nullptr);
    SplashColor srcPixel, copyPixel;
    src.getPixel(0, 0, srcPixel);
    copy->getPixel(0, 0, copyPixel);
    EXPECT_EQ(srcPixel[0], copyPixel[0]);
    EXPECT_EQ(srcPixel[1], copyPixel[1]);
    EXPECT_EQ(srcPixel[2], copyPixel[2]);
    delete copy;
}

// Test takeData returns non-null and clears internal pointer
TEST_F(SplashBitmapTest_1122, TakeData_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr data = bmp.takeData();
    EXPECT_NE(data, nullptr);
    // After takeData, the bitmap's internal data should be null
    EXPECT_EQ(bmp.getDataPtr(), nullptr);
    gfree(data);
}

// Test writePNMFile to a FILE*
TEST_F(SplashBitmapTest_1122, WritePNMFileToFile_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile for Mono8
TEST_F(SplashBitmapTest_1122, WritePNMFileMono8_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile for Mono1
TEST_F(SplashBitmapTest_1122, WritePNMFileMono1_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test getRGBLine doesn't crash
TEST_F(SplashBitmapTest_1122, GetRGBLine_1122) {
    SplashBitmap bmp(10, 5, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor line[10 * 3];
    // Should not crash for valid row
    bmp.getRGBLine(0, (SplashColorPtr)line);
    bmp.getRGBLine(4, (SplashColorPtr)line);
}

// Test getXBGRLine doesn't crash
TEST_F(SplashBitmapTest_1122, GetXBGRLine_1122) {
    SplashBitmap bmp(10, 5, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[10 * 4];
    bmp.getXBGRLine(0, line, SplashBitmap::conversionOpaque);
}

// Test rowPad of 1
TEST_F(SplashBitmapTest_1122, RowPad1_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 1);
}

// Test rowPad of 4 (common for alignment)
TEST_F(SplashBitmapTest_1122, RowPad4_1122) {
    SplashBitmap bmp(10, 10, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getRowPad(), 4);
    // RowSize should be padded to multiple of 4
    EXPECT_EQ(bmp.getRowSize() % 4, 0);
}

// Test getMode returns correct mode
TEST_F(SplashBitmapTest_1122, GetModeReturnsCorrectMode_1122) {
    {
        SplashBitmap bmp(10, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
        EXPECT_EQ(bmp.getMode(), splashModeMono1);
    }
    {
        SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
        EXPECT_EQ(bmp.getMode(), splashModeMono8);
    }
    {
        SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
        EXPECT_EQ(bmp.getMode(), splashModeRGB8);
    }
    {
        SplashBitmap bmp(10, 10, 1, splashModeBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
        EXPECT_EQ(bmp.getMode(), splashModeBGR8);
    }
    {
        SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
        EXPECT_EQ(bmp.getMode(), splashModeXBGR8);
    }
}

// Test getSeparationList when no separation list provided
TEST_F(SplashBitmapTest_1122, GetSeparationListNull_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // When null is passed, getSeparationList behavior depends on implementation
    // but it shouldn't crash
    auto *sepList = bmp.getSeparationList();
    (void)sepList;
}

// Test construction with separation list
TEST_F(SplashBitmapTest_1122, ConstructWithSeparationList_1122) {
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepList;
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, &sepList);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
}

// Test topDown false
TEST_F(SplashBitmapTest_1122, TopDownFalse_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, false, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 10);
    // When topDown is false, rowSize should be negative
    EXPECT_LT(bmp.getRowSize(), 0);
}

// Test topDown true
TEST_F(SplashBitmapTest_1122, TopDownTrue_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GT(bmp.getRowSize(), 0);
}

// Test convertToXBGR
TEST_F(SplashBitmapTest_1122, ConvertToXBGR_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    bool result = bmp.convertToXBGR(SplashBitmap::conversionOpaque);
    // The result depends on whether conversion is supported for the mode
    (void)result;
}

// Test Mono1 row size calculation
TEST_F(SplashBitmapTest_1122, Mono1RowSize_1122) {
    // For Mono1, each pixel is 1 bit, so 8 pixels per byte
    SplashBitmap bmp(8, 1, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 1);
}

// Test Mono1 with non-byte-aligned width
TEST_F(SplashBitmapTest_1122, Mono1NonAlignedWidth_1122) {
    SplashBitmap bmp(10, 1, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // 10 bits = 2 bytes needed
    EXPECT_GE(bmp.getRowSize(), 2);
}

// Test writeAlphaPGMFile
TEST_F(SplashBitmapTest_1122, WriteAlphaPGMFile_1122) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    
    char tmpName[] = "/tmp/splashbm_test_alpha_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_GE(fd, 0);
    close(fd);
    
    SplashError err = bmp.writeAlphaPGMFile(tmpName);
    EXPECT_EQ(err, splashOk);
    
    // Clean up
    unlink(tmpName);
}

// Test width and height getters
TEST_F(SplashBitmapTest_1122, WidthHeightGetters_1122) {
    SplashBitmap bmp(123, 456, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 123);
    EXPECT_EQ(bmp.getHeight(), 456);
}

// Test copy of bitmap with alpha
TEST_F(SplashBitmapTest_1122, CopyWithAlpha_1122) {
    SplashBitmap src(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Set some alpha value
    unsigned char *alphaPtr = src.getAlphaPtr();
    if (alphaPtr) {
        alphaPtr[0] = 128;
    }
    
    SplashBitmap *copy = SplashBitmap::copy(&src);
    ASSERT_NE(copy, nullptr);
    
    unsigned char srcAlpha = src.getAlpha(0, 0);
    unsigned char copyAlpha = copy->getAlpha(0, 0);
    EXPECT_EQ(srcAlpha, copyAlpha);
    
    delete copy;
}
