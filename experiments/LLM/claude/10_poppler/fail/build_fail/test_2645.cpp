#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Include necessary headers
#include "ImageOutputDev.h"

class ImageOutputDevTest_2645 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary directory/file root for testing
        tmpFileRoot = strdup("/tmp/test_imageoutput_2645");
    }

    void TearDown() override {
        free(tmpFileRoot);
    }

    char *tmpFileRoot;
};

// Test that a successfully constructed ImageOutputDev reports isOk() == true
TEST_F(ImageOutputDevTest_2645, ConstructionWithValidParams_IsOk_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    EXPECT_TRUE(dev.isOk());
}

// Test that getErrorCode returns 0 on successful construction
TEST_F(ImageOutputDevTest_2645, ConstructionWithValidParams_ErrorCodeZero_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test construction with listImages = true
TEST_F(ImageOutputDevTest_2645, ConstructionWithListImages_IsOk_2645) {
    ImageOutputDev dev(tmpFileRoot, false, true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test construction with pageNames = true
TEST_F(ImageOutputDevTest_2645, ConstructionWithPageNames_IsOk_2645) {
    ImageOutputDev dev(tmpFileRoot, true, false);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test construction with both pageNames and listImages = true
TEST_F(ImageOutputDevTest_2645, ConstructionWithBothFlags_IsOk_2645) {
    ImageOutputDev dev(tmpFileRoot, true, true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test upsideDown returns expected value
TEST_F(ImageOutputDevTest_2645, UpsideDown_ReturnsFalse_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    EXPECT_FALSE(dev.upsideDown());
}

// Test useDrawChar returns expected value
TEST_F(ImageOutputDevTest_2645, UseDrawChar_ReturnsFalse_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    EXPECT_FALSE(dev.useDrawChar());
}

// Test interpretType3Chars returns expected value
TEST_F(ImageOutputDevTest_2645, InterpretType3Chars_ReturnsFalse_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test needNonText returns expected value (should be true since this device processes images)
TEST_F(ImageOutputDevTest_2645, NeedNonText_ReturnsTrue_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    EXPECT_TRUE(dev.needNonText());
}

// Test useTilingPatternFill returns expected value
TEST_F(ImageOutputDevTest_2645, UseTilingPatternFill_ReturnsTrue_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    // TilingPatternFill should be supported
    EXPECT_TRUE(dev.useTilingPatternFill());
}

// Test enablePNG method does not cause errors
TEST_F(ImageOutputDevTest_2645, EnablePNG_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enablePNG(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableTiff method does not cause errors
TEST_F(ImageOutputDevTest_2645, EnableTiff_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enableTiff(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg method does not cause errors
TEST_F(ImageOutputDevTest_2645, EnableJpeg_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enableJpeg(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJpeg2000 method does not cause errors
TEST_F(ImageOutputDevTest_2645, EnableJpeg2000_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enableJpeg2000(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableJBig2 method does not cause errors
TEST_F(ImageOutputDevTest_2645, EnableJBig2_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enableJBig2(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enableCCITT method does not cause errors
TEST_F(ImageOutputDevTest_2645, EnableCCITT_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enablePrintFilenames method does not cause errors
TEST_F(ImageOutputDevTest_2645, EnablePrintFilenames_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling and then disabling PNG
TEST_F(ImageOutputDevTest_2645, EnableThenDisablePNG_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enablePNG(true);
    dev.enablePNG(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling and then disabling Tiff
TEST_F(ImageOutputDevTest_2645, EnableThenDisableTiff_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enableTiff(true);
    dev.enableTiff(false);
    EXPECT_TRUE(dev.isOk());
}

// Test enabling multiple output formats simultaneously
TEST_F(ImageOutputDevTest_2645, EnableMultipleFormats_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enablePNG(true);
    dev.enableTiff(true);
    dev.enableJpeg(true);
    dev.enableJpeg2000(true);
    dev.enableJBig2(true);
    dev.enableCCITT(true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(0, dev.getErrorCode());
}

// Test that startPage can be called without crashing
TEST_F(ImageOutputDevTest_2645, StartPage_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.startPage(1, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with page number 0 (boundary)
TEST_F(ImageOutputDevTest_2645, StartPage_PageZero_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.startPage(0, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test startPage with a large page number
TEST_F(ImageOutputDevTest_2645, StartPage_LargePageNumber_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.startPage(999999, nullptr, nullptr);
    EXPECT_TRUE(dev.isOk());
}

// Test calling startPage multiple times (simulating multiple pages)
TEST_F(ImageOutputDevTest_2645, StartPageMultipleTimes_NoError_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    for (int i = 1; i <= 10; i++) {
        dev.startPage(i, nullptr, nullptr);
    }
    EXPECT_TRUE(dev.isOk());
}

// Test that isOk and getErrorCode are consistent
TEST_F(ImageOutputDevTest_2645, IsOkConsistentWithErrorCode_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    if (dev.isOk()) {
        EXPECT_EQ(0, dev.getErrorCode());
    } else {
        EXPECT_NE(0, dev.getErrorCode());
    }
}

// Test construction with nullptr fileRoot - error case
TEST_F(ImageOutputDevTest_2645, ConstructionWithNullFileRoot_ListImages_2645) {
    // When listImages is true, fileRoot may not be needed for file creation
    ImageOutputDev dev(nullptr, false, true);
    // The behavior depends on implementation; with listImages=true it might be ok
    // We just verify no crash and check isOk
    // This is observable behavior testing
    (void)dev.isOk();
    (void)dev.getErrorCode();
}

// Test enablePrintFilenames toggle
TEST_F(ImageOutputDevTest_2645, EnablePrintFilenamesToggle_2645) {
    ImageOutputDev dev(tmpFileRoot, false, false);
    dev.enablePrintFilenames(true);
    EXPECT_TRUE(dev.isOk());
    dev.enablePrintFilenames(false);
    EXPECT_TRUE(dev.isOk());
}
