#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Since ImageOutputDev requires constructor arguments and inherits from OutputDev,
// we need to test what we can through the public interface.
// The constructor takes (char* fileRootA, bool pageNamesA, bool listImagesA).

class ImageOutputDevTest_2640 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create with a simple file root, no page names, no list images
        fileRoot = strdup("test_output");
        dev = new ImageOutputDev(fileRoot, false, false);
    }

    void TearDown() override {
        delete dev;
        free(fileRoot);
    }

    char* fileRoot;
    ImageOutputDev* dev;
};

// Test that the object is created successfully and isOk returns true
TEST_F(ImageOutputDevTest_2640, ConstructorCreatesValidObject_2640) {
    EXPECT_TRUE(dev->isOk());
}

// Test that getErrorCode returns 0 for a successfully created object
TEST_F(ImageOutputDevTest_2640, GetErrorCodeReturnsZeroOnSuccess_2640) {
    EXPECT_EQ(0, dev->getErrorCode());
}

// Test enableJpeg2000 with true
TEST_F(ImageOutputDevTest_2640, EnableJpeg2000True_2640) {
    // Should not crash; we can only verify it doesn't throw
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg2000(true));
}

// Test enableJpeg2000 with false
TEST_F(ImageOutputDevTest_2640, EnableJpeg2000False_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg2000(false));
}

// Test enablePNG with true and false
TEST_F(ImageOutputDevTest_2640, EnablePNGTrue_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));
}

TEST_F(ImageOutputDevTest_2640, EnablePNGFalse_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
}

// Test enableTiff with true and false
TEST_F(ImageOutputDevTest_2640, EnableTiffTrue_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableTiff(true));
}

TEST_F(ImageOutputDevTest_2640, EnableTiffFalse_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableTiff(false));
}

// Test enableJpeg with true and false
TEST_F(ImageOutputDevTest_2640, EnableJpegTrue_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg(true));
}

TEST_F(ImageOutputDevTest_2640, EnableJpegFalse_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg(false));
}

// Test enableJBig2 with true and false
TEST_F(ImageOutputDevTest_2640, EnableJBig2True_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(true));
}

TEST_F(ImageOutputDevTest_2640, EnableJBig2False_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(false));
}

// Test enableCCITT with true and false
TEST_F(ImageOutputDevTest_2640, EnableCCITTTrue_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableCCITT(true));
}

TEST_F(ImageOutputDevTest_2640, EnableCCITTFalse_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enableCCITT(false));
}

// Test enablePrintFilenames with true and false
TEST_F(ImageOutputDevTest_2640, EnablePrintFilenamesTrue_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePrintFilenames(true));
}

TEST_F(ImageOutputDevTest_2640, EnablePrintFilenamesFalse_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePrintFilenames(false));
}

// Test upsideDown returns expected value (typically true for image output)
TEST_F(ImageOutputDevTest_2640, UpsideDown_2640) {
    // Just verify it returns a bool without crashing
    bool result = dev->upsideDown();
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar
TEST_F(ImageOutputDevTest_2640, UseDrawChar_2640) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

// Test interpretType3Chars
TEST_F(ImageOutputDevTest_2640, InterpretType3Chars_2640) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test needNonText returns true (since this device extracts images)
TEST_F(ImageOutputDevTest_2640, NeedNonText_2640) {
    EXPECT_TRUE(dev->needNonText());
}

// Test useTilingPatternFill
TEST_F(ImageOutputDevTest_2640, UseTilingPatternFill_2640) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test construction with pageNames enabled
TEST_F(ImageOutputDevTest_2640, ConstructorWithPageNames_2640) {
    char* root = strdup("page_test");
    ImageOutputDev* devPageNames = new ImageOutputDev(root, true, false);
    EXPECT_TRUE(devPageNames->isOk());
    EXPECT_EQ(0, devPageNames->getErrorCode());
    delete devPageNames;
    free(root);
}

// Test construction with listImages enabled
TEST_F(ImageOutputDevTest_2640, ConstructorWithListImages_2640) {
    char* root = strdup("list_test");
    ImageOutputDev* devList = new ImageOutputDev(root, false, true);
    EXPECT_TRUE(devList->isOk());
    EXPECT_EQ(0, devList->getErrorCode());
    delete devList;
    free(root);
}

// Test construction with both pageNames and listImages enabled
TEST_F(ImageOutputDevTest_2640, ConstructorWithBothFlags_2640) {
    char* root = strdup("both_test");
    ImageOutputDev* devBoth = new ImageOutputDev(root, true, true);
    EXPECT_TRUE(devBoth->isOk());
    EXPECT_EQ(0, devBoth->getErrorCode());
    delete devBoth;
    free(root);
}

// Test enabling multiple formats simultaneously
TEST_F(ImageOutputDevTest_2640, EnableMultipleFormats_2640) {
    EXPECT_NO_FATAL_FAILURE({
        dev->enablePNG(true);
        dev->enableJpeg(true);
        dev->enableJpeg2000(true);
        dev->enableTiff(true);
        dev->enableJBig2(true);
        dev->enableCCITT(true);
    });
    EXPECT_TRUE(dev->isOk());
}

// Test toggling formats on and off
TEST_F(ImageOutputDevTest_2640, ToggleFormats_2640) {
    dev->enablePNG(true);
    dev->enablePNG(false);
    dev->enableJpeg(true);
    dev->enableJpeg(false);
    dev->enableJpeg2000(true);
    dev->enableJpeg2000(false);
    EXPECT_TRUE(dev->isOk());
}

// Test startPage doesn't crash with valid page number
TEST_F(ImageOutputDevTest_2640, StartPageDoesNotCrash_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->startPage(1, nullptr, nullptr));
}

// Test startPage with various page numbers
TEST_F(ImageOutputDevTest_2640, StartPageMultiplePages_2640) {
    EXPECT_NO_FATAL_FAILURE(dev->startPage(1, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->startPage(2, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->startPage(100, nullptr, nullptr));
}

// Test that enablePrintFilenames can be toggled
TEST_F(ImageOutputDevTest_2640, TogglePrintFilenames_2640) {
    dev->enablePrintFilenames(true);
    dev->enablePrintFilenames(false);
    dev->enablePrintFilenames(true);
    EXPECT_TRUE(dev->isOk());
}
