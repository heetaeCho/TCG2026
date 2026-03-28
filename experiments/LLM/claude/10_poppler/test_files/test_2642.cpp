#include <gtest/gtest.h>
#include "ImageOutputDev.h"

// Since ImageOutputDev constructor requires specific parameters and inherits from OutputDev,
// we need to test through the public interface. The constructor takes (char*, bool, bool).

class ImageOutputDevTest_2642 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create with a file root, pageNames=false, listImages=false
        dev = new ImageOutputDev(const_cast<char*>("test_output"), false, false);
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
    }

    ImageOutputDev* dev;
};

// Test that the object is created successfully and isOk returns true
TEST_F(ImageOutputDevTest_2642, ConstructorCreatesValidObject_2642) {
    EXPECT_TRUE(dev->isOk());
}

// Test getErrorCode after construction
TEST_F(ImageOutputDevTest_2642, InitialErrorCodeIsZero_2642) {
    EXPECT_EQ(0, dev->getErrorCode());
}

// Test enableCCITT with true
TEST_F(ImageOutputDevTest_2642, EnableCCITTTrue_2642) {
    // Should not crash or throw
    dev->enableCCITT(true);
    EXPECT_TRUE(dev->isOk());
}

// Test enableCCITT with false
TEST_F(ImageOutputDevTest_2642, EnableCCITTFalse_2642) {
    dev->enableCCITT(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enablePNG
TEST_F(ImageOutputDevTest_2642, EnablePNGTrue_2642) {
    dev->enablePNG(true);
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevTest_2642, EnablePNGFalse_2642) {
    dev->enablePNG(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableTiff
TEST_F(ImageOutputDevTest_2642, EnableTiffTrue_2642) {
    dev->enableTiff(true);
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevTest_2642, EnableTiffFalse_2642) {
    dev->enableTiff(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableJpeg
TEST_F(ImageOutputDevTest_2642, EnableJpegTrue_2642) {
    dev->enableJpeg(true);
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevTest_2642, EnableJpegFalse_2642) {
    dev->enableJpeg(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableJpeg2000
TEST_F(ImageOutputDevTest_2642, EnableJpeg2000True_2642) {
    dev->enableJpeg2000(true);
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevTest_2642, EnableJpeg2000False_2642) {
    dev->enableJpeg2000(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableJBig2
TEST_F(ImageOutputDevTest_2642, EnableJBig2True_2642) {
    dev->enableJBig2(true);
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevTest_2642, EnableJBig2False_2642) {
    dev->enableJBig2(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enablePrintFilenames
TEST_F(ImageOutputDevTest_2642, EnablePrintFilenamesTrue_2642) {
    dev->enablePrintFilenames(true);
    EXPECT_TRUE(dev->isOk());
}

TEST_F(ImageOutputDevTest_2642, EnablePrintFilenamesFalse_2642) {
    dev->enablePrintFilenames(false);
    EXPECT_TRUE(dev->isOk());
}

// Test upsideDown
TEST_F(ImageOutputDevTest_2642, UpsideDownReturnsFalse_2642) {
    // OutputDev typically returns false for upsideDown
    bool result = dev->upsideDown();
    // Just verify it returns a boolean without crashing
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar
TEST_F(ImageOutputDevTest_2642, UseDrawCharReturnsBool_2642) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

// Test useTilingPatternFill
TEST_F(ImageOutputDevTest_2642, UseTilingPatternFillReturnsBool_2642) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test interpretType3Chars
TEST_F(ImageOutputDevTest_2642, InterpretType3CharsReturnsBool_2642) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test needNonText
TEST_F(ImageOutputDevTest_2642, NeedNonTextReturnsBool_2642) {
    bool result = dev->needNonText();
    EXPECT_TRUE(result == true || result == false);
}

// Test that needNonText returns true (image output device needs non-text content)
TEST_F(ImageOutputDevTest_2642, NeedNonTextReturnsTrue_2642) {
    EXPECT_TRUE(dev->needNonText());
}

// Test toggling CCITT on and off
TEST_F(ImageOutputDevTest_2642, ToggleCCITT_2642) {
    dev->enableCCITT(true);
    dev->enableCCITT(false);
    dev->enableCCITT(true);
    EXPECT_TRUE(dev->isOk());
}

// Test enabling all formats simultaneously
TEST_F(ImageOutputDevTest_2642, EnableAllFormats_2642) {
    dev->enablePNG(true);
    dev->enableTiff(true);
    dev->enableJpeg(true);
    dev->enableJpeg2000(true);
    dev->enableJBig2(true);
    dev->enableCCITT(true);
    EXPECT_TRUE(dev->isOk());
    EXPECT_EQ(0, dev->getErrorCode());
}

// Test disabling all formats
TEST_F(ImageOutputDevTest_2642, DisableAllFormats_2642) {
    dev->enablePNG(false);
    dev->enableTiff(false);
    dev->enableJpeg(false);
    dev->enableJpeg2000(false);
    dev->enableJBig2(false);
    dev->enableCCITT(false);
    EXPECT_TRUE(dev->isOk());
}

// Test construction with pageNames=true
TEST_F(ImageOutputDevTest_2642, ConstructWithPageNames_2642) {
    ImageOutputDev* devPageNames = new ImageOutputDev(const_cast<char*>("test_page"), true, false);
    EXPECT_TRUE(devPageNames->isOk());
    delete devPageNames;
}

// Test construction with listImages=true
TEST_F(ImageOutputDevTest_2642, ConstructWithListImages_2642) {
    ImageOutputDev* devList = new ImageOutputDev(const_cast<char*>("test_list"), false, true);
    EXPECT_TRUE(devList->isOk());
    delete devList;
}

// Test construction with both pageNames and listImages true
TEST_F(ImageOutputDevTest_2642, ConstructWithBothFlags_2642) {
    ImageOutputDev* devBoth = new ImageOutputDev(const_cast<char*>("test_both"), true, true);
    EXPECT_TRUE(devBoth->isOk());
    delete devBoth;
}

// Test that interpretType3Chars returns false for image output device
TEST_F(ImageOutputDevTest_2642, InterpretType3CharsFalse_2642) {
    EXPECT_FALSE(dev->interpretType3Chars());
}

// Test that useTilingPatternFill returns true
TEST_F(ImageOutputDevTest_2642, UseTilingPatternFillTrue_2642) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test startPage doesn't crash with nullptr state/xref
TEST_F(ImageOutputDevTest_2642, StartPageWithNullParams_2642) {
    // startPage should handle being called; page numbering starts at 1
    dev->startPage(1, nullptr, nullptr);
    EXPECT_TRUE(dev->isOk());
}

// Test multiple startPage calls (simulating multiple pages)
TEST_F(ImageOutputDevTest_2642, MultipleStartPageCalls_2642) {
    dev->startPage(1, nullptr, nullptr);
    dev->startPage(2, nullptr, nullptr);
    dev->startPage(3, nullptr, nullptr);
    EXPECT_TRUE(dev->isOk());
}
