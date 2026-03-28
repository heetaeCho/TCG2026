#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Since ImageOutputDev requires constructor arguments and inherits from OutputDev,
// we need to create instances carefully. The constructor takes (char*, bool, bool).
// We'll test the public interface methods that are accessible.

class ImageOutputDevTest_2638 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create with a file root, pageNames=false, listImages=false
        char fileRoot[] = "test_output";
        dev = new ImageOutputDev(fileRoot, false, false);
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
    }

    ImageOutputDev *dev = nullptr;
};

// Test that enableTiff sets the tiff output mode
TEST_F(ImageOutputDevTest_2638, EnableTiffTrue_2638) {
    // Should not crash or throw when enabling tiff
    EXPECT_NO_THROW(dev->enableTiff(true));
}

TEST_F(ImageOutputDevTest_2638, EnableTiffFalse_2638) {
    EXPECT_NO_THROW(dev->enableTiff(false));
}

TEST_F(ImageOutputDevTest_2638, EnableTiffToggle_2638) {
    dev->enableTiff(true);
    dev->enableTiff(false);
    dev->enableTiff(true);
    // No crash means success for toggle
}

// Test enablePNG
TEST_F(ImageOutputDevTest_2638, EnablePNGTrue_2638) {
    EXPECT_NO_THROW(dev->enablePNG(true));
}

TEST_F(ImageOutputDevTest_2638, EnablePNGFalse_2638) {
    EXPECT_NO_THROW(dev->enablePNG(false));
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2638, EnableJpegTrue_2638) {
    EXPECT_NO_THROW(dev->enableJpeg(true));
}

TEST_F(ImageOutputDevTest_2638, EnableJpegFalse_2638) {
    EXPECT_NO_THROW(dev->enableJpeg(false));
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2638, EnableJpeg2000True_2638) {
    EXPECT_NO_THROW(dev->enableJpeg2000(true));
}

TEST_F(ImageOutputDevTest_2638, EnableJpeg2000False_2638) {
    EXPECT_NO_THROW(dev->enableJpeg2000(false));
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2638, EnableJBig2True_2638) {
    EXPECT_NO_THROW(dev->enableJBig2(true));
}

TEST_F(ImageOutputDevTest_2638, EnableJBig2False_2638) {
    EXPECT_NO_THROW(dev->enableJBig2(false));
}

// Test enableCCITT
TEST_F(ImageOutputDevTest_2638, EnableCCITTTrue_2638) {
    EXPECT_NO_THROW(dev->enableCCITT(true));
}

TEST_F(ImageOutputDevTest_2638, EnableCCITTFalse_2638) {
    EXPECT_NO_THROW(dev->enableCCITT(false));
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2638, EnablePrintFilenamesTrue_2638) {
    EXPECT_NO_THROW(dev->enablePrintFilenames(true));
}

TEST_F(ImageOutputDevTest_2638, EnablePrintFilenamesFalse_2638) {
    EXPECT_NO_THROW(dev->enablePrintFilenames(false));
}

// Test isOk - freshly constructed device should be ok
TEST_F(ImageOutputDevTest_2638, IsOkAfterConstruction_2638) {
    EXPECT_TRUE(dev->isOk());
}

// Test getErrorCode - freshly constructed device should have no error
TEST_F(ImageOutputDevTest_2638, GetErrorCodeAfterConstruction_2638) {
    // Expecting 0 (no error) for a properly constructed device
    EXPECT_EQ(dev->getErrorCode(), 0);
}

// Test upsideDown
TEST_F(ImageOutputDevTest_2638, UpsideDown_2638) {
    // ImageOutputDev typically returns true for upsideDown
    bool result = dev->upsideDown();
    EXPECT_TRUE(result);
}

// Test useDrawChar
TEST_F(ImageOutputDevTest_2638, UseDrawChar_2638) {
    // ImageOutputDev typically returns false for useDrawChar
    bool result = dev->useDrawChar();
    EXPECT_FALSE(result);
}

// Test interpretType3Chars
TEST_F(ImageOutputDevTest_2638, InterpretType3Chars_2638) {
    // ImageOutputDev typically returns false
    bool result = dev->interpretType3Chars();
    EXPECT_FALSE(result);
}

// Test needNonText
TEST_F(ImageOutputDevTest_2638, NeedNonText_2638) {
    // ImageOutputDev should return true since it processes images
    bool result = dev->needNonText();
    EXPECT_TRUE(result);
}

// Test useTilingPatternFill
TEST_F(ImageOutputDevTest_2638, UseTilingPatternFill_2638) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);
}

// Test construction with listImages mode
TEST_F(ImageOutputDevTest_2638, ConstructWithListImagesMode_2638) {
    char fileRoot[] = "list_test";
    ImageOutputDev *listDev = new ImageOutputDev(fileRoot, false, true);
    EXPECT_TRUE(listDev->isOk());
    delete listDev;
}

// Test construction with pageNames mode
TEST_F(ImageOutputDevTest_2638, ConstructWithPageNamesMode_2638) {
    char fileRoot[] = "page_test";
    ImageOutputDev *pageNamesDev = new ImageOutputDev(fileRoot, true, false);
    EXPECT_TRUE(pageNamesDev->isOk());
    delete pageNamesDev;
}

// Test construction with both pageNames and listImages
TEST_F(ImageOutputDevTest_2638, ConstructWithBothModes_2638) {
    char fileRoot[] = "both_test";
    ImageOutputDev *bothDev = new ImageOutputDev(fileRoot, true, true);
    EXPECT_TRUE(bothDev->isOk());
    delete bothDev;
}

// Test enabling all formats simultaneously
TEST_F(ImageOutputDevTest_2638, EnableAllFormats_2638) {
    EXPECT_NO_THROW({
        dev->enablePNG(true);
        dev->enableTiff(true);
        dev->enableJpeg(true);
        dev->enableJpeg2000(true);
        dev->enableJBig2(true);
        dev->enableCCITT(true);
    });
    // Device should still be ok
    EXPECT_TRUE(dev->isOk());
}

// Test disabling all formats
TEST_F(ImageOutputDevTest_2638, DisableAllFormats_2638) {
    EXPECT_NO_THROW({
        dev->enablePNG(false);
        dev->enableTiff(false);
        dev->enableJpeg(false);
        dev->enableJpeg2000(false);
        dev->enableJBig2(false);
        dev->enableCCITT(false);
    });
}

// Test startPage doesn't crash with valid page number
TEST_F(ImageOutputDevTest_2638, StartPageValidPageNum_2638) {
    EXPECT_NO_THROW(dev->startPage(1, nullptr, nullptr));
}

// Test startPage with page number 0 (boundary)
TEST_F(ImageOutputDevTest_2638, StartPageZero_2638) {
    EXPECT_NO_THROW(dev->startPage(0, nullptr, nullptr));
}

// Test startPage with large page number
TEST_F(ImageOutputDevTest_2638, StartPageLargeNumber_2638) {
    EXPECT_NO_THROW(dev->startPage(99999, nullptr, nullptr));
}

// Test multiple startPage calls (simulating page progression)
TEST_F(ImageOutputDevTest_2638, MultipleStartPages_2638) {
    EXPECT_NO_THROW({
        dev->startPage(1, nullptr, nullptr);
        dev->startPage(2, nullptr, nullptr);
        dev->startPage(3, nullptr, nullptr);
    });
}
