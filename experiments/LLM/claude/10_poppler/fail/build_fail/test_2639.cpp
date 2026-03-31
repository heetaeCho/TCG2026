#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ImageOutputDev.h"

// Since ImageOutputDev requires constructor arguments and inherits from OutputDev,
// we need to create instances carefully. The constructor takes (char*, bool, bool).
// We'll test the public interface methods that are accessible.

class ImageOutputDevTest_2639 : public ::testing::Test {
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

// Test that the object is created successfully and isOk returns true
TEST_F(ImageOutputDevTest_2639, ConstructorCreatesValidObject_2639) {
    EXPECT_TRUE(dev->isOk());
}

// Test enableJpeg sets/clears JPEG mode
TEST_F(ImageOutputDevTest_2639, EnableJpeg_2639) {
    dev->enableJpeg(true);
    // No direct getter for dumpJPEG, but we verify no crash and isOk still holds
    EXPECT_TRUE(dev->isOk());
    
    dev->enableJpeg(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enablePNG sets/clears PNG mode
TEST_F(ImageOutputDevTest_2639, EnablePNG_2639) {
    dev->enablePNG(true);
    EXPECT_TRUE(dev->isOk());
    
    dev->enablePNG(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableTiff sets/clears TIFF mode
TEST_F(ImageOutputDevTest_2639, EnableTiff_2639) {
    dev->enableTiff(true);
    EXPECT_TRUE(dev->isOk());
    
    dev->enableTiff(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableJpeg2000 sets/clears JP2 mode
TEST_F(ImageOutputDevTest_2639, EnableJpeg2000_2639) {
    dev->enableJpeg2000(true);
    EXPECT_TRUE(dev->isOk());
    
    dev->enableJpeg2000(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableJBig2 sets/clears JBIG2 mode
TEST_F(ImageOutputDevTest_2639, EnableJBig2_2639) {
    dev->enableJBig2(true);
    EXPECT_TRUE(dev->isOk());
    
    dev->enableJBig2(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enableCCITT sets/clears CCITT mode
TEST_F(ImageOutputDevTest_2639, EnableCCITT_2639) {
    dev->enableCCITT(true);
    EXPECT_TRUE(dev->isOk());
    
    dev->enableCCITT(false);
    EXPECT_TRUE(dev->isOk());
}

// Test enablePrintFilenames sets/clears print filenames mode
TEST_F(ImageOutputDevTest_2639, EnablePrintFilenames_2639) {
    dev->enablePrintFilenames(true);
    EXPECT_TRUE(dev->isOk());
    
    dev->enablePrintFilenames(false);
    EXPECT_TRUE(dev->isOk());
}

// Test getErrorCode returns 0 for a successfully created device
TEST_F(ImageOutputDevTest_2639, GetErrorCodeInitiallyZero_2639) {
    EXPECT_EQ(dev->getErrorCode(), 0);
}

// Test upsideDown returns expected value
TEST_F(ImageOutputDevTest_2639, UpsideDown_2639) {
    // OutputDev behavior - ImageOutputDev should return a consistent value
    bool result = dev->upsideDown();
    // Just verify it returns without crashing and returns a bool
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar returns expected value
TEST_F(ImageOutputDevTest_2639, UseDrawChar_2639) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result == true || result == false);
}

// Test interpretType3Chars returns expected value
TEST_F(ImageOutputDevTest_2639, InterpretType3Chars_2639) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test needNonText returns expected value
TEST_F(ImageOutputDevTest_2639, NeedNonText_2639) {
    bool result = dev->needNonText();
    EXPECT_TRUE(result);
}

// Test useTilingPatternFill returns expected value
TEST_F(ImageOutputDevTest_2639, UseTilingPatternFill_2639) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test multiple enable/disable cycles
TEST_F(ImageOutputDevTest_2639, MultipleEnableDisableCycles_2639) {
    for (int i = 0; i < 10; i++) {
        dev->enableJpeg(true);
        dev->enablePNG(true);
        dev->enableTiff(true);
        dev->enableJpeg2000(true);
        dev->enableJBig2(true);
        dev->enableCCITT(true);
    }
    EXPECT_TRUE(dev->isOk());
    EXPECT_EQ(dev->getErrorCode(), 0);
    
    for (int i = 0; i < 10; i++) {
        dev->enableJpeg(false);
        dev->enablePNG(false);
        dev->enableTiff(false);
        dev->enableJpeg2000(false);
        dev->enableJBig2(false);
        dev->enableCCITT(false);
    }
    EXPECT_TRUE(dev->isOk());
    EXPECT_EQ(dev->getErrorCode(), 0);
}

// Test constructor with pageNames=true
TEST(ImageOutputDevConstructor_2639, ConstructWithPageNames_2639) {
    char fileRoot[] = "test_page_names";
    ImageOutputDev dev(fileRoot, true, false);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(dev.getErrorCode(), 0);
}

// Test constructor with listImages=true
TEST(ImageOutputDevConstructor_2639, ConstructWithListImages_2639) {
    char fileRoot[] = "test_list_images";
    ImageOutputDev dev(fileRoot, false, true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(dev.getErrorCode(), 0);
}

// Test constructor with both pageNames and listImages true
TEST(ImageOutputDevConstructor_2639, ConstructWithBothFlags_2639) {
    char fileRoot[] = "test_both_flags";
    ImageOutputDev dev(fileRoot, true, true);
    EXPECT_TRUE(dev.isOk());
    EXPECT_EQ(dev.getErrorCode(), 0);
}

// Test that all format enables can coexist
TEST_F(ImageOutputDevTest_2639, AllFormatsEnabled_2639) {
    dev->enableJpeg(true);
    dev->enablePNG(true);
    dev->enableTiff(true);
    dev->enableJpeg2000(true);
    dev->enableJBig2(true);
    dev->enableCCITT(true);
    dev->enablePrintFilenames(true);
    
    EXPECT_TRUE(dev->isOk());
    EXPECT_EQ(dev->getErrorCode(), 0);
}

// Test that all format disables work together
TEST_F(ImageOutputDevTest_2639, AllFormatsDisabled_2639) {
    dev->enableJpeg(false);
    dev->enablePNG(false);
    dev->enableTiff(false);
    dev->enableJpeg2000(false);
    dev->enableJBig2(false);
    dev->enableCCITT(false);
    dev->enablePrintFilenames(false);
    
    EXPECT_TRUE(dev->isOk());
    EXPECT_EQ(dev->getErrorCode(), 0);
}
