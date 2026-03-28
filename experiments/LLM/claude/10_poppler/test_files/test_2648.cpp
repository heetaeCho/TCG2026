#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Test fixture for ImageOutputDev
class ImageOutputDevTest_2648 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any created ImageOutputDev instances
    }
};

// Test that needNonText returns true
TEST_F(ImageOutputDevTest_2648, NeedNonTextReturnsTrue_2648) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.needNonText());
}

// Test constructor with basic parameters and isOk
TEST_F(ImageOutputDevTest_2648, ConstructorBasicIsOk_2648) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test constructor with pageNames enabled
TEST_F(ImageOutputDevTest_2648, ConstructorWithPageNames_2648) {
    char fileRoot[] = "test_page_output";
    ImageOutputDev dev(fileRoot, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test constructor with listImages enabled
TEST_F(ImageOutputDevTest_2648, ConstructorWithListImages_2648) {
    char fileRoot[] = "test_list_output";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test constructor with both pageNames and listImages
TEST_F(ImageOutputDevTest_2648, ConstructorWithBothFlags_2648) {
    char fileRoot[] = "test_both_output";
    ImageOutputDev dev(fileRoot, true, true);
    EXPECT_TRUE(dev.isOk());
}

// Test getErrorCode initially returns 0 (no error)
TEST_F(ImageOutputDevTest_2648, GetErrorCodeInitiallyZero_2648) {
    char fileRoot[] = "test_error";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test upsideDown returns expected value
TEST_F(ImageOutputDevTest_2648, UpsideDownReturnValue_2648) {
    char fileRoot[] = "test_upside";
    ImageOutputDev dev(fileRoot, false, false);
    // OutputDev typically returns true for upsideDown
    EXPECT_TRUE(dev.upsideDown());
}

// Test useDrawChar returns expected value
TEST_F(ImageOutputDevTest_2648, UseDrawCharReturnValue_2648) {
    char fileRoot[] = "test_drawchar";
    ImageOutputDev dev(fileRoot, false, false);
    // ImageOutputDev doesn't need to draw characters
    EXPECT_FALSE(dev.useDrawChar());
}

// Test interpretType3Chars returns expected value
TEST_F(ImageOutputDevTest_2648, InterpretType3CharsReturnValue_2648) {
    char fileRoot[] = "test_type3";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test useTilingPatternFill returns expected value
TEST_F(ImageOutputDevTest_2648, UseTilingPatternFillReturnValue_2648) {
    char fileRoot[] = "test_tiling";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test enablePNG
TEST_F(ImageOutputDevTest_2648, EnablePNG_2648) {
    char fileRoot[] = "test_png";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    // No crash, method succeeds
    EXPECT_TRUE(dev.isOk());
}

// Test enablePNG disabled
TEST_F(ImageOutputDevTest_2648, DisablePNG_2648) {
    char fileRoot[] = "test_png_off";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff
TEST_F(ImageOutputDevTest_2648, EnableTiff_2648) {
    char fileRoot[] = "test_tiff";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableTiff(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff disabled
TEST_F(ImageOutputDevTest_2648, DisableTiff_2648) {
    char fileRoot[] = "test_tiff_off";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableTiff(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2648, EnableJpeg_2648) {
    char fileRoot[] = "test_jpeg";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg disabled
TEST_F(ImageOutputDevTest_2648, DisableJpeg_2648) {
    char fileRoot[] = "test_jpeg_off";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2648, EnableJpeg2000_2648) {
    char fileRoot[] = "test_jp2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg2000(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000 disabled
TEST_F(ImageOutputDevTest_2648, DisableJpeg2000_2648) {
    char fileRoot[] = "test_jp2_off";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg2000(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2648, EnableJBig2_2648) {
    char fileRoot[] = "test_jbig2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJBig2(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2 disabled
TEST_F(ImageOutputDevTest_2648, DisableJBig2_2648) {
    char fileRoot[] = "test_jbig2_off";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJBig2(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT
TEST_F(ImageOutputDevTest_2648, EnableCCITT_2648) {
    char fileRoot[] = "test_ccitt";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT disabled
TEST_F(ImageOutputDevTest_2648, DisableCCITT_2648) {
    char fileRoot[] = "test_ccitt_off";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableCCITT(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2648, EnablePrintFilenames_2648) {
    char fileRoot[] = "test_filenames";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames disabled
TEST_F(ImageOutputDevTest_2648, DisablePrintFilenames_2648) {
    char fileRoot[] = "test_filenames_off";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling multiple formats at once
TEST_F(ImageOutputDevTest_2648, EnableMultipleFormats_2648) {
    char fileRoot[] = "test_multi";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enableTiff(true);
    dev.enableJpeg(true);
    dev.enableJpeg2000(true);
    dev.enableJBig2(true);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test that needNonText consistently returns true
TEST_F(ImageOutputDevTest_2648, NeedNonTextConsistent_2648) {
    char fileRoot[] = "test_consistent";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.needNonText());
    EXPECT_TRUE(dev.needNonText());
    EXPECT_TRUE(dev.needNonText());
}

// Test with list images mode - needNonText still returns true
TEST_F(ImageOutputDevTest_2648, NeedNonTextInListMode_2648) {
    char fileRoot[] = "test_list_need";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_TRUE(dev.needNonText());
}

// Test startPage does not crash
TEST_F(ImageOutputDevTest_2648, StartPageDoesNotCrash_2648) {
    char fileRoot[] = "test_startpage";
    ImageOutputDev dev(fileRoot, false, false);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with different page numbers
TEST_F(ImageOutputDevTest_2648, StartPageMultiplePages_2648) {
    char fileRoot[] = "test_multipages";
    ImageOutputDev dev(fileRoot, true, false);
    dev.startPage(1, nullptr, nullptr);
    dev.startPage(2, nullptr, nullptr);
    dev.startPage(100, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with page number 0 (boundary)
TEST_F(ImageOutputDevTest_2648, StartPageZero_2648) {
    char fileRoot[] = "test_pagezero";
    ImageOutputDev dev(fileRoot, false, false);
    dev.startPage(0, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test toggling formats on and off
TEST_F(ImageOutputDevTest_2648, ToggleFormats_2648) {
    char fileRoot[] = "test_toggle";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enablePNG(false);
    dev.enableTiff(true);
    dev.enableTiff(false);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test that error code remains 0 after normal operations
TEST_F(ImageOutputDevTest_2648, ErrorCodeAfterOperations_2648) {
    char fileRoot[] = "test_errcode";
    ImageOutputDev dev(fileRoot, true, false);
    dev.enablePNG(true);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_EQ(0, dev.getErrorCode());
}
