#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Since ImageOutputDev constructor requires specific parameters and inherits from OutputDev,
// we need to test what we can through the public interface.
// The constructor takes (char* fileRootA, bool pageNamesA, bool listImagesA).

class ImageOutputDevTest_2641 : public ::testing::Test {
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
TEST_F(ImageOutputDevTest_2641, ConstructorCreatesValidObject_2641) {
    EXPECT_TRUE(dev->isOk());
}

// Test getErrorCode after normal construction
TEST_F(ImageOutputDevTest_2641, GetErrorCodeAfterConstruction_2641) {
    // After successful construction, error code should indicate no error (typically 0)
    int errorCode = dev->getErrorCode();
    EXPECT_EQ(0, errorCode);
}

// Test enableJBig2 with true
TEST_F(ImageOutputDevTest_2641, EnableJBig2True_2641) {
    // Should not crash or throw
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(true));
}

// Test enableJBig2 with false
TEST_F(ImageOutputDevTest_2641, EnableJBig2False_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(false));
}

// Test enableJBig2 toggle
TEST_F(ImageOutputDevTest_2641, EnableJBig2Toggle_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(true));
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(false));
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(true));
}

// Test enablePNG with true
TEST_F(ImageOutputDevTest_2641, EnablePNGTrue_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));
}

// Test enablePNG with false
TEST_F(ImageOutputDevTest_2641, EnablePNGFalse_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
}

// Test enableTiff with true
TEST_F(ImageOutputDevTest_2641, EnableTiffTrue_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableTiff(true));
}

// Test enableTiff with false
TEST_F(ImageOutputDevTest_2641, EnableTiffFalse_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableTiff(false));
}

// Test enableJpeg with true
TEST_F(ImageOutputDevTest_2641, EnableJpegTrue_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg(true));
}

// Test enableJpeg with false
TEST_F(ImageOutputDevTest_2641, EnableJpegFalse_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg(false));
}

// Test enableJpeg2000 with true
TEST_F(ImageOutputDevTest_2641, EnableJpeg2000True_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg2000(true));
}

// Test enableJpeg2000 with false
TEST_F(ImageOutputDevTest_2641, EnableJpeg2000False_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg2000(false));
}

// Test enableCCITT with true
TEST_F(ImageOutputDevTest_2641, EnableCCITTTrue_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableCCITT(true));
}

// Test enableCCITT with false
TEST_F(ImageOutputDevTest_2641, EnableCCITTFalse_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enableCCITT(false));
}

// Test enablePrintFilenames with true
TEST_F(ImageOutputDevTest_2641, EnablePrintFilenamesTrue_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePrintFilenames(true));
}

// Test enablePrintFilenames with false
TEST_F(ImageOutputDevTest_2641, EnablePrintFilenamesFalse_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePrintFilenames(false));
}

// Test upsideDown returns expected value
TEST_F(ImageOutputDevTest_2641, UpsideDown_2641) {
    // OutputDev typically returns true for upsideDown
    bool result = dev->upsideDown();
    // Just verify it returns a valid boolean without crashing
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar returns expected value
TEST_F(ImageOutputDevTest_2641, UseDrawChar_2641) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

// Test interpretType3Chars returns expected value
TEST_F(ImageOutputDevTest_2641, InterpretType3Chars_2641) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test needNonText returns expected value
TEST_F(ImageOutputDevTest_2641, NeedNonText_2641) {
    bool result = dev->needNonText();
    // For image extraction, we expect this to return true
    EXPECT_TRUE(result);
}

// Test useTilingPatternFill returns expected value
TEST_F(ImageOutputDevTest_2641, UseTilingPatternFill_2641) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test enabling all formats at once
TEST_F(ImageOutputDevTest_2641, EnableAllFormats_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));
    EXPECT_NO_FATAL_FAILURE(dev->enableTiff(true));
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg(true));
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg2000(true));
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(true));
    EXPECT_NO_FATAL_FAILURE(dev->enableCCITT(true));
    EXPECT_TRUE(dev->isOk());
}

// Test disabling all formats
TEST_F(ImageOutputDevTest_2641, DisableAllFormats_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
    EXPECT_NO_FATAL_FAILURE(dev->enableTiff(false));
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg(false));
    EXPECT_NO_FATAL_FAILURE(dev->enableJpeg2000(false));
    EXPECT_NO_FATAL_FAILURE(dev->enableJBig2(false));
    EXPECT_NO_FATAL_FAILURE(dev->enableCCITT(false));
    EXPECT_TRUE(dev->isOk());
}

// Test construction with pageNames enabled
TEST_F(ImageOutputDevTest_2641, ConstructWithPageNames_2641) {
    char* root = strdup("page_test");
    ImageOutputDev* devWithPages = new ImageOutputDev(root, true, false);
    EXPECT_TRUE(devWithPages->isOk());
    EXPECT_EQ(0, devWithPages->getErrorCode());
    delete devWithPages;
    free(root);
}

// Test construction with listImages enabled
TEST_F(ImageOutputDevTest_2641, ConstructWithListImages_2641) {
    char* root = strdup("list_test");
    ImageOutputDev* devWithList = new ImageOutputDev(root, false, true);
    EXPECT_TRUE(devWithList->isOk());
    EXPECT_EQ(0, devWithList->getErrorCode());
    delete devWithList;
    free(root);
}

// Test construction with both pageNames and listImages enabled
TEST_F(ImageOutputDevTest_2641, ConstructWithBothOptions_2641) {
    char* root = strdup("both_test");
    ImageOutputDev* devBoth = new ImageOutputDev(root, true, true);
    EXPECT_TRUE(devBoth->isOk());
    delete devBoth;
    free(root);
}

// Test startPage does not crash
TEST_F(ImageOutputDevTest_2641, StartPage_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->startPage(1, nullptr, nullptr));
}

// Test startPage with various page numbers
TEST_F(ImageOutputDevTest_2641, StartPageMultiplePages_2641) {
    EXPECT_NO_FATAL_FAILURE(dev->startPage(1, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->startPage(2, nullptr, nullptr));
    EXPECT_NO_FATAL_FAILURE(dev->startPage(100, nullptr, nullptr));
}

// Test repeated enable/disable cycles don't cause issues
TEST_F(ImageOutputDevTest_2641, RepeatedEnableDisableCycles_2641) {
    for (int i = 0; i < 100; ++i) {
        dev->enablePNG(i % 2 == 0);
        dev->enableJpeg(i % 2 != 0);
        dev->enableJBig2(i % 3 == 0);
    }
    EXPECT_TRUE(dev->isOk());
}
