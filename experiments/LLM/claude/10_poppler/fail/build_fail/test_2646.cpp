#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Test fixture for ImageOutputDev
class ImageOutputDevTest_2646 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any created ImageOutputDev instances
    }
};

// Test that useTilingPatternFill returns true
TEST_F(ImageOutputDevTest_2646, UseTilingPatternFillReturnsTrue_2646) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test that needNonText returns true (image output device needs non-text content)
TEST_F(ImageOutputDevTest_2646, NeedNonTextReturnsTrue_2646) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.needNonText());
}

// Test that interpretType3Chars returns false (we don't need to interpret Type3 chars for image extraction)
TEST_F(ImageOutputDevTest_2646, InterpretType3CharsReturnsFalse_2646) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test that useDrawChar returns false
TEST_F(ImageOutputDevTest_2646, UseDrawCharReturnsFalse_2646) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.useDrawChar());
}

// Test that upsideDown returns true
TEST_F(ImageOutputDevTest_2646, UpsideDownReturnsTrue_2646) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test construction with listImages mode
TEST_F(ImageOutputDevTest_2646, ConstructWithListImagesMode_2646) {
    char fileRoot[] = "test_list";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with pageNames enabled
TEST_F(ImageOutputDevTest_2646, ConstructWithPageNames_2646) {
    char fileRoot[] = "test_pages";
    ImageOutputDev dev(fileRoot, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test that isOk returns true after successful construction
TEST_F(ImageOutputDevTest_2646, IsOkAfterConstruction_2646) {
    char fileRoot[] = "test_ok";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test getErrorCode returns 0 (no error) initially
TEST_F(ImageOutputDevTest_2646, GetErrorCodeInitiallyZero_2646) {
    char fileRoot[] = "test_error";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test enablePNG
TEST_F(ImageOutputDevTest_2646, EnablePNG_2646) {
    char fileRoot[] = "test_png";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    // No crash, method executes successfully
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff
TEST_F(ImageOutputDevTest_2646, EnableTiff_2646) {
    char fileRoot[] = "test_tiff";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableTiff(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2646, EnableJpeg_2646) {
    char fileRoot[] = "test_jpeg";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2646, EnableJpeg2000_2646) {
    char fileRoot[] = "test_jp2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg2000(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2646, EnableJBig2_2646) {
    char fileRoot[] = "test_jbig2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJBig2(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT
TEST_F(ImageOutputDevTest_2646, EnableCCITT_2646) {
    char fileRoot[] = "test_ccitt";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2646, EnablePrintFilenames_2646) {
    char fileRoot[] = "test_filenames";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
}

// Test disabling formats after enabling
TEST_F(ImageOutputDevTest_2646, DisablePNGAfterEnable_2646) {
    char fileRoot[] = "test_disable";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enablePNG(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling multiple formats simultaneously
TEST_F(ImageOutputDevTest_2646, EnableMultipleFormats_2646) {
    char fileRoot[] = "test_multi";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enableTiff(true);
    dev.enableJpeg(true);
    dev.enableJpeg2000(true);
    dev.enableJBig2(true);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage doesn't crash with valid page number
TEST_F(ImageOutputDevTest_2646, StartPageDoesNotCrash_2646) {
    char fileRoot[] = "test_startpage";
    ImageOutputDev dev(fileRoot, false, false);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with page names enabled
TEST_F(ImageOutputDevTest_2646, StartPageWithPageNames_2646) {
    char fileRoot[] = "test_startpage_names";
    ImageOutputDev dev(fileRoot, true, false);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with different page numbers
TEST_F(ImageOutputDevTest_2646, StartPageMultiplePages_2646) {
    char fileRoot[] = "test_multipages";
    ImageOutputDev dev(fileRoot, true, false);
    dev.startPage(1, nullptr, nullptr);
    dev.startPage(2, nullptr, nullptr);
    dev.startPage(100, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test construction with both pageNames and listImages
TEST_F(ImageOutputDevTest_2646, ConstructWithBothPageNamesAndListImages_2646) {
    char fileRoot[] = "test_both";
    ImageOutputDev dev(fileRoot, true, true);
    EXPECT_TRUE(dev.isOk());
}

// Test that error code remains 0 after enabling formats
TEST_F(ImageOutputDevTest_2646, ErrorCodeZeroAfterEnablingFormats_2646) {
    char fileRoot[] = "test_errcode";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enableJpeg(true);
    EXPECT_EQ(0, dev.getErrorCode());
}
