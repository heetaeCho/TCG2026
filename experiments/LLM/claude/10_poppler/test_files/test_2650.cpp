#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Test fixture for ImageOutputDev
class ImageOutputDevTest_2650 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a basic ImageOutputDev with a file root
        // Using non-list mode, no page names
    }

    void TearDown() override {
    }
};

// Test constructor with basic parameters and isOk
TEST_F(ImageOutputDevTest_2650, ConstructorBasic_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test constructor with pageNames enabled
TEST_F(ImageOutputDevTest_2650, ConstructorWithPageNames_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, true, false);
    EXPECT_TRUE(dev.isOk());
}

// Test constructor with listImages enabled
TEST_F(ImageOutputDevTest_2650, ConstructorWithListImages_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_TRUE(dev.isOk());
}

// Test constructor with both pageNames and listImages
TEST_F(ImageOutputDevTest_2650, ConstructorWithBothFlags_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, true, true);
    EXPECT_TRUE(dev.isOk());
}

// Test useDrawChar returns false
TEST_F(ImageOutputDevTest_2650, UseDrawCharReturnsFalse_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.useDrawChar());
}

// Test upsideDown returns true
TEST_F(ImageOutputDevTest_2650, UpsideDownReturnsTrue_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test interpretType3Chars returns false
TEST_F(ImageOutputDevTest_2650, InterpretType3CharsReturnsFalse_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test needNonText returns true
TEST_F(ImageOutputDevTest_2650, NeedNonTextReturnsTrue_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.needNonText());
}

// Test useTilingPatternFill returns true
TEST_F(ImageOutputDevTest_2650, UseTilingPatternFillReturnsTrue_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test getErrorCode initially returns 0 (no error)
TEST_F(ImageOutputDevTest_2650, GetErrorCodeInitiallyZero_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test enablePNG
TEST_F(ImageOutputDevTest_2650, EnablePNG_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    // No observable state change directly, but should not crash
    EXPECT_TRUE(dev.isOk());
}

// Test enablePNG disabled
TEST_F(ImageOutputDevTest_2650, DisablePNG_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff
TEST_F(ImageOutputDevTest_2650, EnableTiff_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableTiff(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff disabled
TEST_F(ImageOutputDevTest_2650, DisableTiff_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableTiff(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2650, EnableJpeg_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg disabled
TEST_F(ImageOutputDevTest_2650, DisableJpeg_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2650, EnableJpeg2000_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg2000(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000 disabled
TEST_F(ImageOutputDevTest_2650, DisableJpeg2000_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJpeg2000(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2650, EnableJBig2_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJBig2(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2 disabled
TEST_F(ImageOutputDevTest_2650, DisableJBig2_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableJBig2(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT
TEST_F(ImageOutputDevTest_2650, EnableCCITT_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT disabled
TEST_F(ImageOutputDevTest_2650, DisableCCITT_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enableCCITT(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2650, EnablePrintFilenames_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames disabled
TEST_F(ImageOutputDevTest_2650, DisablePrintFilenames_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePrintFilenames(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling multiple formats simultaneously
TEST_F(ImageOutputDevTest_2650, EnableMultipleFormats_2650) {
    char fileRoot[] = "/tmp/test_image";
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

// Test startPage does not crash
TEST_F(ImageOutputDevTest_2650, StartPageDoesNotCrash_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with different page numbers
TEST_F(ImageOutputDevTest_2650, StartPageMultiplePages_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, true, false);
    dev.startPage(1, nullptr, nullptr);
    dev.startPage(2, nullptr, nullptr);
    dev.startPage(3, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with page number 0 (boundary)
TEST_F(ImageOutputDevTest_2650, StartPageZero_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.startPage(0, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with negative page number (boundary)
TEST_F(ImageOutputDevTest_2650, StartPageNegative_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.startPage(-1, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test that error code remains 0 after enabling formats
TEST_F(ImageOutputDevTest_2650, ErrorCodeAfterEnableFormats_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enableJpeg(true);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test toggle enable formats
TEST_F(ImageOutputDevTest_2650, ToggleEnableFormats_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, false);
    dev.enablePNG(true);
    dev.enablePNG(false);
    dev.enablePNG(true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test that list images mode doesn't affect basic interface queries
TEST_F(ImageOutputDevTest_2650, ListImagesModeInterfaceQueries_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_FALSE(dev.useDrawChar());
    EXPECT_TRUE(dev.upsideDown());
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_TRUE(dev.needNonText());
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test with pageNames mode interface queries
TEST_F(ImageOutputDevTest_2650, PageNamesModeInterfaceQueries_2650) {
    char fileRoot[] = "/tmp/test_image";
    ImageOutputDev dev(fileRoot, true, false);
    EXPECT_FALSE(dev.useDrawChar());
    EXPECT_TRUE(dev.upsideDown());
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_TRUE(dev.needNonText());
    EXPECT_TRUE(dev.useTilingPatternFill());
}
