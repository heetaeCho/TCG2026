#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Test fixture for ImageOutputDev
class ImageOutputDevTest_2647 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup any created ImageOutputDev instances
    }
};

// Test that interpretType3Chars returns false
TEST_F(ImageOutputDevTest_2647, InterpretType3CharsReturnsFalse_2647) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test that needNonText returns true (image output device needs non-text content)
TEST_F(ImageOutputDevTest_2647, NeedNonTextReturnsTrue_2647) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.needNonText());
}

// Test that useDrawChar returns false
TEST_F(ImageOutputDevTest_2647, UseDrawCharReturnsFalse_2647) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.useDrawChar());
}

// Test that upsideDown returns true
TEST_F(ImageOutputDevTest_2647, UpsideDownReturnsTrue_2647) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test that useTilingPatternFill returns true
TEST_F(ImageOutputDevTest_2647, UseTilingPatternFillReturnsTrue_2647) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test that isOk returns true after proper construction
TEST_F(ImageOutputDevTest_2647, IsOkAfterConstruction_2647) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test getErrorCode returns 0 initially (no errors)
TEST_F(ImageOutputDevTest_2647, GetErrorCodeInitiallyZero_2647) {
    char fileRoot[] = "test_output";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test construction with pageNames = true
TEST_F(ImageOutputDevTest_2647, ConstructWithPageNamesTrue_2647) {
    char fileRoot[] = "test_page";
    ImageOutputDev dev(fileRoot, true, false);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test construction with listImages = true
TEST_F(ImageOutputDevTest_2647, ConstructWithListImagesTrue_2647) {
    char fileRoot[] = "test_list";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test construction with both pageNames and listImages true
TEST_F(ImageOutputDevTest_2647, ConstructWithBothPageNamesAndListImages_2647) {
    char fileRoot[] = "test_both";
    ImageOutputDev dev(fileRoot, true, true);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePNG
TEST_F(ImageOutputDevTest_2647, EnablePNG_2647) {
    char fileRoot[] = "test_png";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff
TEST_F(ImageOutputDevTest_2647, EnableTiff_2647) {
    char fileRoot[] = "test_tiff";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableTiff(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2647, EnableJpeg_2647) {
    char fileRoot[] = "test_jpeg";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2647, EnableJpeg2000_2647) {
    char fileRoot[] = "test_jp2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg2000(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2647, EnableJBig2_2647) {
    char fileRoot[] = "test_jbig2";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJBig2(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT
TEST_F(ImageOutputDevTest_2647, EnableCCITT_2647) {
    char fileRoot[] = "test_ccitt";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2647, EnablePrintFilenames_2647) {
    char fileRoot[] = "test_filenames";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
}

// Test disabling formats after enabling
TEST_F(ImageOutputDevTest_2647, DisableFormatsAfterEnabling_2647) {
    char fileRoot[] = "test_disable";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enablePNG(false);
    dev.enableTiff(true);
    dev.enableTiff(false);
    dev.enableJpeg(true);
    dev.enableJpeg(false);
    dev.enableJpeg2000(true);
    dev.enableJpeg2000(false);
    dev.enableJBig2(true);
    dev.enableJBig2(false);
    dev.enableCCITT(true);
    dev.enableCCITT(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling all formats simultaneously
TEST_F(ImageOutputDevTest_2647, EnableAllFormats_2647) {
    char fileRoot[] = "test_all";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enableTiff(true);
    dev.enableJpeg(true);
    dev.enableJpeg2000(true);
    dev.enableJBig2(true);
    dev.enableCCITT(true);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test startPage does not cause errors
TEST_F(ImageOutputDevTest_2647, StartPageNoError_2647) {
    char fileRoot[] = "test_startpage";
    ImageOutputDev dev(fileRoot, false, false);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test startPage with various page numbers
TEST_F(ImageOutputDevTest_2647, StartPageVariousPageNumbers_2647) {
    char fileRoot[] = "test_pages";
    ImageOutputDev dev(fileRoot, true, false);
    dev.startPage(1, nullptr, nullptr);
    dev.startPage(2, nullptr, nullptr);
    dev.startPage(100, nullptr, nullptr);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test interpretType3Chars consistency across calls
TEST_F(ImageOutputDevTest_2647, InterpretType3CharsConsistent_2647) {
    char fileRoot[] = "test_consistent";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test that enablePrintFilenames with false works
TEST_F(ImageOutputDevTest_2647, DisablePrintFilenames_2647) {
    char fileRoot[] = "test_noprint";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(false);
    EXPECT_TRUE(dev.isOk());
}
