#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Test fixture for ImageOutputDev
class ImageOutputDevTest_2649 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that upsideDown returns true
TEST_F(ImageOutputDevTest_2649, UpsideDownReturnsTrue_2649) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test that useDrawChar returns false (OutputDev typically returns false for image extraction)
TEST_F(ImageOutputDevTest_2649, UseDrawCharReturnsFalse_2649) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.useDrawChar());
}

// Test that interpretType3Chars returns false
TEST_F(ImageOutputDevTest_2649, InterpretType3CharsReturnsFalse_2649) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test that needNonText returns true (image output device needs non-text content)
TEST_F(ImageOutputDevTest_2649, NeedNonTextReturnsTrue_2649) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.needNonText());
}

// Test that useTilingPatternFill returns true
TEST_F(ImageOutputDevTest_2649, UseTilingPatternFillReturnsTrue_2649) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test construction with listImages mode
TEST_F(ImageOutputDevTest_2649, ConstructWithListImagesMode_2649) {
    char fileRoot[] = "test_list";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with pageNames enabled
TEST_F(ImageOutputDevTest_2649, ConstructWithPageNames_2649) {
    char fileRoot[] = "test_pagenames";
    ImageOutputDev dev(fileRoot, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with both pageNames and listImages
TEST_F(ImageOutputDevTest_2649, ConstructWithPageNamesAndListImages_2649) {
    char fileRoot[] = "test_both";
    ImageOutputDev dev(fileRoot, true, true);
    EXPECT_TRUE(dev.isOk());
}

// Test isOk after normal construction
TEST_F(ImageOutputDevTest_2649, IsOkAfterConstruction_2649) {
    char fileRoot[] = "test_ok";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test getErrorCode returns 0 initially (no errors)
TEST_F(ImageOutputDevTest_2649, GetErrorCodeInitiallyZero_2649) {
    char fileRoot[] = "test_errcode";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_EQ(dev.getErrorCode(), 0);
}

// Test enablePNG
TEST_F(ImageOutputDevTest_2649, EnablePNG_2649) {
    char fileRoot[] = "test_png";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    // No crash, device still ok
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff
TEST_F(ImageOutputDevTest_2649, EnableTiff_2649) {
    char fileRoot[] = "test_tiff";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableTiff(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2649, EnableJpeg_2649) {
    char fileRoot[] = "test_jpeg";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2649, EnableJpeg2000_2649) {
    char fileRoot[] = "test_jp2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg2000(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2649, EnableJBig2_2649) {
    char fileRoot[] = "test_jbig2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJBig2(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT
TEST_F(ImageOutputDevTest_2649, EnableCCITT_2649) {
    char fileRoot[] = "test_ccitt";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2649, EnablePrintFilenames_2649) {
    char fileRoot[] = "test_filenames";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
}

// Test disabling all formats
TEST_F(ImageOutputDevTest_2649, DisableAllFormats_2649) {
    char fileRoot[] = "test_disable";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(false);
    dev.enableTiff(false);
    dev.enableJpeg(false);
    dev.enableJpeg2000(false);
    dev.enableJBig2(false);
    dev.enableCCITT(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling multiple formats simultaneously
TEST_F(ImageOutputDevTest_2649, EnableMultipleFormats_2649) {
    char fileRoot[] = "test_multi";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enableJpeg(true);
    dev.enableTiff(true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(dev.getErrorCode(), 0);
}

// Test startPage doesn't crash with nullptr state and xref
TEST_F(ImageOutputDevTest_2649, StartPageWithNullParams_2649) {
    char fileRoot[] = "test_startpage";
    ImageOutputDev dev(fileRoot, true, false);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with various page numbers
TEST_F(ImageOutputDevTest_2649, StartPageVariousPageNumbers_2649) {
    char fileRoot[] = "test_pages";
    ImageOutputDev dev(fileRoot, true, false);
    dev.startPage(1, nullptr, nullptr);
    dev.startPage(2, nullptr, nullptr);
    dev.startPage(100, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test that toggling enablePrintFilenames works
TEST_F(ImageOutputDevTest_2649, TogglePrintFilenames_2649) {
    char fileRoot[] = "test_toggle";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(true);
    dev.enablePrintFilenames(false);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with empty file root
TEST_F(ImageOutputDevTest_2649, ConstructWithEmptyFileRoot_2649) {
    char fileRoot[] = "";
    ImageOutputDev dev(fileRoot, false, false);
    // Device should still construct, behavior depends on implementation
    // Just verify no crash
    EXPECT_GE(dev.getErrorCode(), 0);
}
