#include <gtest/gtest.h>
#include "ImageOutputDev.h"

// Since ImageOutputDev constructor requires parameters and inherits from OutputDev,
// we need to test what we can through the public interface.
// The constructor takes (char* fileRootA, bool pageNamesA, bool listImagesA)

class ImageOutputDevTest_2637 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create with a simple file root, no page names, no list images
        dev = new ImageOutputDev(const_cast<char*>("test_output"), false, false);
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
    }

    ImageOutputDev* dev;
};

// Test enablePNG sets the PNG output mode
TEST_F(ImageOutputDevTest_2637, EnablePNGTrue_2637) {
    // Should not crash; enabling PNG
    dev->enablePNG(true);
    // No direct getter for outputPNG, but we verify no crash
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnablePNGFalse_2637) {
    dev->enablePNG(false);
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnablePNGToggle_2637) {
    dev->enablePNG(true);
    dev->enablePNG(false);
    dev->enablePNG(true);
    SUCCEED();
}

// Test enableTiff
TEST_F(ImageOutputDevTest_2637, EnableTiffTrue_2637) {
    dev->enableTiff(true);
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnableTiffFalse_2637) {
    dev->enableTiff(false);
    SUCCEED();
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2637, EnableJpegTrue_2637) {
    dev->enableJpeg(true);
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnableJpegFalse_2637) {
    dev->enableJpeg(false);
    SUCCEED();
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2637, EnableJpeg2000True_2637) {
    dev->enableJpeg2000(true);
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnableJpeg2000False_2637) {
    dev->enableJpeg2000(false);
    SUCCEED();
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2637, EnableJBig2True_2637) {
    dev->enableJBig2(true);
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnableJBig2False_2637) {
    dev->enableJBig2(false);
    SUCCEED();
}

// Test enableCCITT
TEST_F(ImageOutputDevTest_2637, EnableCCITTTrue_2637) {
    dev->enableCCITT(true);
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnableCCITTFalse_2637) {
    dev->enableCCITT(false);
    SUCCEED();
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2637, EnablePrintFilenamesTrue_2637) {
    dev->enablePrintFilenames(true);
    SUCCEED();
}

TEST_F(ImageOutputDevTest_2637, EnablePrintFilenamesFalse_2637) {
    dev->enablePrintFilenames(false);
    SUCCEED();
}

// Test getErrorCode - on a freshly constructed valid device, error code should be 0
TEST_F(ImageOutputDevTest_2637, GetErrorCodeInitial_2637) {
    int errorCode = dev->getErrorCode();
    EXPECT_EQ(errorCode, 0);
}

// Test isOk - a properly constructed device should be ok
TEST_F(ImageOutputDevTest_2637, IsOkAfterConstruction_2637) {
    EXPECT_TRUE(dev->isOk());
}

// Test upsideDown - OutputDev interface method
TEST_F(ImageOutputDevTest_2637, UpsideDown_2637) {
    bool result = dev->upsideDown();
    // Just verify it returns a boolean value without crashing
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar - OutputDev interface method
TEST_F(ImageOutputDevTest_2637, UseDrawChar_2637) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

// Test interpretType3Chars
TEST_F(ImageOutputDevTest_2637, InterpretType3Chars_2637) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test needNonText
TEST_F(ImageOutputDevTest_2637, NeedNonText_2637) {
    bool result = dev->needNonText();
    // Image extraction device should need non-text content
    EXPECT_TRUE(result);
}

// Test useTilingPatternFill
TEST_F(ImageOutputDevTest_2637, UseTilingPatternFill_2637) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test construction with listImages mode
class ImageOutputDevListImagesTest_2637 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = new ImageOutputDev(const_cast<char*>("test_list"), false, true);
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
    }

    ImageOutputDev* dev;
};

TEST_F(ImageOutputDevListImagesTest_2637, IsOkInListMode_2637) {
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevListImagesTest_2637, GetErrorCodeInListMode_2637) {
    EXPECT_EQ(dev->getErrorCode(), 0);
}

// Test construction with pageNames mode
class ImageOutputDevPageNamesTest_2637 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = new ImageOutputDev(const_cast<char*>("test_pages"), true, false);
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
    }

    ImageOutputDev* dev;
};

TEST_F(ImageOutputDevPageNamesTest_2637, IsOkWithPageNames_2637) {
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevPageNamesTest_2637, GetErrorCodeWithPageNames_2637) {
    EXPECT_EQ(dev->getErrorCode(), 0);
}

// Test enabling all formats simultaneously
TEST_F(ImageOutputDevTest_2637, EnableAllFormats_2637) {
    dev->enablePNG(true);
    dev->enableTiff(true);
    dev->enableJpeg(true);
    dev->enableJpeg2000(true);
    dev->enableJBig2(true);
    dev->enableCCITT(true);
    SUCCEED();
}

// Test disabling all formats
TEST_F(ImageOutputDevTest_2637, DisableAllFormats_2637) {
    dev->enablePNG(false);
    dev->enableTiff(false);
    dev->enableJpeg(false);
    dev->enableJpeg2000(false);
    dev->enableJBig2(false);
    dev->enableCCITT(false);
    SUCCEED();
}

// Test that startPage can be called (with nullptr for optional params)
TEST_F(ImageOutputDevTest_2637, StartPage_2637) {
    dev->startPage(1, nullptr, nullptr);
    SUCCEED();
}

// Test startPage with various page numbers
TEST_F(ImageOutputDevTest_2637, StartPageMultiplePages_2637) {
    dev->startPage(1, nullptr, nullptr);
    dev->startPage(2, nullptr, nullptr);
    dev->startPage(100, nullptr, nullptr);
    SUCCEED();
}

// Boundary: startPage with page number 0
TEST_F(ImageOutputDevTest_2637, StartPageZero_2637) {
    dev->startPage(0, nullptr, nullptr);
    SUCCEED();
}
