#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

// Helper to safely create a SplashBitmap for testing
// Using the constructor: SplashBitmap(int widthA, int heightA, int rowPad, SplashColorMode modeA, bool alphaA, bool topDown, const std::vector<std::unique_ptr<GfxSeparationColorSpace>>* separationList)

class SplashBitmapTest_1118 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and dimension getters with splashModeMono1
TEST_F(SplashBitmapTest_1118, ConstructMono1_GetDimensions_1118) {
    SplashBitmap bmp(100, 200, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 100);
    EXPECT_EQ(bmp.getHeight(), 200);
}

// Test basic construction with splashModeMono8
TEST_F(SplashBitmapTest_1118, ConstructMono8_GetDimensions_1118) {
    SplashBitmap bmp(50, 75, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 75);
}

// Test construction with splashModeRGB8
TEST_F(SplashBitmapTest_1118, ConstructRGB8_GetDimensions_1118) {
    SplashBitmap bmp(320, 240, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 320);
    EXPECT_EQ(bmp.getHeight(), 240);
}

// Test construction with splashModeXBGR8
TEST_F(SplashBitmapTest_1118, ConstructXBGR8_GetDimensions_1118) {
    SplashBitmap bmp(640, 480, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 640);
    EXPECT_EQ(bmp.getHeight(), 480);
}

// Test getMode returns correct mode
TEST_F(SplashBitmapTest_1118, GetModeReturnsCorrectMode_1118) {
    SplashBitmap bmpMono1(10, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmpMono1.getMode(), splashModeMono1);

    SplashBitmap bmpMono8(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmpMono8.getMode(), splashModeMono8);

    SplashBitmap bmpRGB8(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmpRGB8.getMode(), splashModeRGB8);

    SplashBitmap bmpXBGR8(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmpXBGR8.getMode(), splashModeXBGR8);
}

// Test getRowPad returns correct padding
TEST_F(SplashBitmapTest_1118, GetRowPadReturnsCorrectPad_1118) {
    SplashBitmap bmp1(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp1.getRowPad(), 1);

    SplashBitmap bmp4(10, 10, 4, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp4.getRowPad(), 4);
}

// Test getRowSize is positive and reasonable for RGB8
TEST_F(SplashBitmapTest_1118, GetRowSizePositiveRGB8_1118) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 100 * 3); // At least width * 3 bytes for RGB
}

// Test getRowSize for Mono8
TEST_F(SplashBitmapTest_1118, GetRowSizePositiveMono8_1118) {
    SplashBitmap bmp(100, 50, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 100); // At least width bytes for Mono8
}

// Test getRowSize for XBGR8
TEST_F(SplashBitmapTest_1118, GetRowSizePositiveXBGR8_1118) {
    SplashBitmap bmp(100, 50, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getRowSize(), 100 * 4); // At least width * 4 bytes for XBGR8
}

// Test getDataPtr returns non-null
TEST_F(SplashBitmapTest_1118, GetDataPtrNonNull_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test alpha pointer is non-null when alpha is enabled
TEST_F(SplashBitmapTest_1118, AlphaEnabledGetAlphaPtrNonNull_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
}

// Test alpha pointer is null when alpha is disabled
TEST_F(SplashBitmapTest_1118, AlphaDisabledGetAlphaPtrNull_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getAlphaPtr(), nullptr);
}

// Test getAlphaRowSize with alpha enabled
TEST_F(SplashBitmapTest_1118, AlphaRowSizeWithAlpha_1118) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_GE(bmp.getAlphaRowSize(), 100); // At least width for alpha
}

// Test getAlphaRowSize without alpha
TEST_F(SplashBitmapTest_1118, AlphaRowSizeWithoutAlpha_1118) {
    SplashBitmap bmp(100, 50, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // Without alpha, the row size might be 0 or the width; just check it's non-negative
    EXPECT_GE(bmp.getAlphaRowSize(), 0);
}

// Test getPixel returns a value for valid coordinates
TEST_F(SplashBitmapTest_1118, GetPixelValidCoordinates_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColor pixel;
    // Should not crash for valid coordinates
    bmp.getPixel(0, 0, pixel);
    bmp.getPixel(9, 9, pixel);
    bmp.getPixel(5, 5, pixel);
}

// Test getAlpha returns a value when alpha is enabled
TEST_F(SplashBitmapTest_1118, GetAlphaValidCoordinates_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char alpha = bmp.getAlpha(0, 0);
    // Just check it returns without crashing; value is implementation-defined
    (void)alpha;
    alpha = bmp.getAlpha(9, 9);
    (void)alpha;
}

// Test takeData returns non-null and subsequent call to getDataPtr might differ
TEST_F(SplashBitmapTest_1118, TakeDataReturnsNonNull_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashColorPtr data = bmp.takeData();
    EXPECT_NE(data, nullptr);
    // The caller takes ownership, need to free
    gfree(data);
}

// Test copy creates a valid copy with same dimensions
TEST_F(SplashBitmapTest_1118, CopyCreatesSameDimensions_1118) {
    SplashBitmap original(100, 200, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copyBmp = SplashBitmap::copy(&original);
    ASSERT_NE(copyBmp, nullptr);
    EXPECT_EQ(copyBmp->getWidth(), original.getWidth());
    EXPECT_EQ(copyBmp->getHeight(), original.getHeight());
    EXPECT_EQ(copyBmp->getMode(), original.getMode());
    EXPECT_EQ(copyBmp->getRowSize(), original.getRowSize());
    EXPECT_EQ(copyBmp->getRowPad(), original.getRowPad());
    delete copyBmp;
}

// Test small bitmap (1x1)
TEST_F(SplashBitmapTest_1118, SmallBitmap1x1_1118) {
    SplashBitmap bmp(1, 1, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1);
    EXPECT_EQ(bmp.getHeight(), 1);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);

    SplashColor pixel;
    bmp.getPixel(0, 0, pixel);
    unsigned char alpha = bmp.getAlpha(0, 0);
    (void)alpha;
}

// Test with different rowPad values
TEST_F(SplashBitmapTest_1118, DifferentRowPadValues_1118) {
    for (int pad : {1, 2, 4, 8, 16}) {
        SplashBitmap bmp(100, 100, pad, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
        EXPECT_EQ(bmp.getRowPad(), pad);
        EXPECT_EQ(bmp.getWidth(), 100);
        EXPECT_EQ(bmp.getHeight(), 100);
        // Row size should be aligned to pad
        if (pad > 1) {
            EXPECT_EQ(bmp.getRowSize() % pad, 0);
        }
    }
}

// Test getRGBLine does not crash
TEST_F(SplashBitmapTest_1118, GetRGBLineNoCrash_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[10 * 3];
    bmp.getRGBLine(0, line);
    bmp.getRGBLine(9, line);
}

// Test getXBGRLine does not crash
TEST_F(SplashBitmapTest_1118, GetXBGRLineNoCrash_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    unsigned char line[10 * 4];
    bmp.getXBGRLine(0, line, SplashBitmap::conversionOpaque);
}

// Test writePNMFile to a temporary file with Mono8
TEST_F(SplashBitmapTest_1118, WritePNMFileMono8_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeMono8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writePNMFile to a temporary file with RGB8
TEST_F(SplashBitmapTest_1118, WritePNMFileRGB8_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    FILE* f = tmpfile();
    ASSERT_NE(f, nullptr);
    SplashError err = bmp.writePNMFile(f);
    EXPECT_EQ(err, splashOk);
    fclose(f);
}

// Test writeAlphaPGMFile
TEST_F(SplashBitmapTest_1118, WriteAlphaPGMFile_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    char tmpName[] = "/tmp/splash_test_alpha_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    close(fd);
    SplashError err = bmp.writeAlphaPGMFile(tmpName);
    EXPECT_EQ(err, splashOk);
    unlink(tmpName);
}

// Test topDown parameter (false) - should still construct properly
TEST_F(SplashBitmapTest_1118, ConstructBottomUp_1118) {
    SplashBitmap bmp(50, 50, 1, splashModeRGB8, false, false, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 50);
    EXPECT_EQ(bmp.getHeight(), 50);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
}

// Test that Mono1 row size accounts for bit packing
TEST_F(SplashBitmapTest_1118, Mono1RowSize_1118) {
    SplashBitmap bmp(17, 10, 1, splashModeMono1, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // 17 bits = at least 3 bytes
    EXPECT_GE(bmp.getRowSize(), 3);
}

// Test getSeparationList returns a valid pointer (or nullptr depending on construction)
TEST_F(SplashBitmapTest_1118, GetSeparationListNullConstruction_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeRGB8, false, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    // May or may not be null depending on implementation
    auto* sepList = bmp.getSeparationList();
    // Just ensure no crash; the result depends on implementation
    (void)sepList;
}

// Test copy with alpha
TEST_F(SplashBitmapTest_1118, CopyWithAlpha_1118) {
    SplashBitmap original(50, 50, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    SplashBitmap* copyBmp = SplashBitmap::copy(&original);
    ASSERT_NE(copyBmp, nullptr);
    EXPECT_NE(copyBmp->getAlphaPtr(), nullptr);
    EXPECT_EQ(copyBmp->getAlphaRowSize(), original.getAlphaRowSize());
    delete copyBmp;
}

// Test larger bitmap dimensions
TEST_F(SplashBitmapTest_1118, LargeBitmap_1118) {
    SplashBitmap bmp(1920, 1080, 1, splashModeRGB8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    EXPECT_EQ(bmp.getWidth(), 1920);
    EXPECT_EQ(bmp.getHeight(), 1080);
    EXPECT_NE(bmp.getDataPtr(), nullptr);
    EXPECT_NE(bmp.getAlphaPtr(), nullptr);
    EXPECT_GE(bmp.getRowSize(), 1920 * 3);
}

// Test convertToXBGR on an XBGR bitmap
TEST_F(SplashBitmapTest_1118, ConvertToXBGR_1118) {
    SplashBitmap bmp(10, 10, 1, splashModeXBGR8, true, true, (std::vector<std::unique_ptr<GfxSeparationColorSpace>>*)nullptr);
    bool result = bmp.convertToXBGR(SplashBitmap::conversionOpaque);
    // Result depends on implementation but should not crash
    (void)result;
}
