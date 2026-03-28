#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CairoOutputDev.h"

// Test fixture for CairoImageOutputDev
class CairoImageOutputDevTest_2447 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
    }

    CairoImageOutputDev *dev;
};

// Test that a newly constructed CairoImageOutputDev has zero images
TEST_F(CairoImageOutputDevTest_2447, InitialNumImagesIsZero_2447) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test getImage with no images returns nullptr or handles gracefully
TEST_F(CairoImageOutputDevTest_2447, GetImageWithNoImages_2447) {
    // With 0 images, accessing index 0 should be out of bounds
    // We test that getNumImages is 0 to confirm no images exist
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that upsideDown returns expected value
TEST_F(CairoImageOutputDevTest_2447, UpsideDown_2447) {
    // CairoImageOutputDev overrides this - just verify it returns a bool
    bool result = dev->upsideDown();
    // The result is implementation-defined, but we verify it doesn't crash
    (void)result;
}

// Test that useDrawChar returns expected value
TEST_F(CairoImageOutputDevTest_2447, UseDrawChar_2447) {
    bool result = dev->useDrawChar();
    (void)result;
}

// Test that useTilingPatternFill returns expected value
TEST_F(CairoImageOutputDevTest_2447, UseTilingPatternFill_2447) {
    bool result = dev->useTilingPatternFill();
    (void)result;
}

// Test that interpretType3Chars returns expected value
TEST_F(CairoImageOutputDevTest_2447, InterpretType3Chars_2447) {
    bool result = dev->interpretType3Chars();
    (void)result;
}

// Test that needNonText returns expected value
TEST_F(CairoImageOutputDevTest_2447, NeedNonText_2447) {
    bool result = dev->needNonText();
    (void)result;
}

// Test setImageDrawDecideCbk with a valid callback
static bool testCallback(int img_id, void *data) {
    int *counter = static_cast<int *>(data);
    (*counter)++;
    return true;
}

TEST_F(CairoImageOutputDevTest_2447, SetImageDrawDecideCbkValid_2447) {
    int counter = 0;
    // Setting callback should not crash
    dev->setImageDrawDecideCbk(testCallback, &counter);
    // We can't directly verify the callback is set without triggering image drawing,
    // but we verify no crash occurs
    SUCCEED();
}

// Test setImageDrawDecideCbk with nullptr callback
TEST_F(CairoImageOutputDevTest_2447, SetImageDrawDecideCbkNull_2447) {
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    SUCCEED();
}

// Test setImageDrawDecideCbk with callback that returns false
static bool rejectCallback(int img_id, void *data) {
    return false;
}

TEST_F(CairoImageOutputDevTest_2447, SetImageDrawDecideCbkReject_2447) {
    dev->setImageDrawDecideCbk(rejectCallback, nullptr);
    // Verify no crash and num images is still 0
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that useShadedFills returns a value for various types
TEST_F(CairoImageOutputDevTest_2447, UseShadedFills_2447) {
    for (int type = 1; type <= 7; ++type) {
        bool result = dev->useShadedFills(type);
        (void)result;
    }
    SUCCEED();
}

// Test that useFillColorStop returns expected value
TEST_F(CairoImageOutputDevTest_2447, UseFillColorStop_2447) {
    bool result = dev->useFillColorStop();
    (void)result;
}

// Test multiple setImageDrawDecideCbk calls (overwrite callback)
TEST_F(CairoImageOutputDevTest_2447, SetCallbackMultipleTimes_2447) {
    int counter1 = 0;
    int counter2 = 0;
    dev->setImageDrawDecideCbk(testCallback, &counter1);
    dev->setImageDrawDecideCbk(testCallback, &counter2);
    // Should not crash, second callback should replace first
    SUCCEED();
}

// Test construction and destruction cycle
TEST_F(CairoImageOutputDevTest_2447, ConstructDestructCycle_2447) {
    CairoImageOutputDev *localDev = new CairoImageOutputDev();
    EXPECT_EQ(localDev->getNumImages(), 0);
    delete localDev;
    SUCCEED();
}

// Test getImage with valid index after confirming count (boundary)
TEST_F(CairoImageOutputDevTest_2447, GetImageBoundaryIndex_2447) {
    int numImages = dev->getNumImages();
    EXPECT_EQ(numImages, 0);
    // If numImages > 0, getImage(0) should return non-null
    // If numImages == 0, we just verify count is correct
    if (numImages > 0) {
        CairoImage *img = dev->getImage(0);
        EXPECT_NE(img, nullptr);
    }
}

// Test saveState and restoreState with nullptr (no-op overrides)
TEST_F(CairoImageOutputDevTest_2447, SaveRestoreStateNullptr_2447) {
    dev->saveState(nullptr);
    dev->restoreState(nullptr);
    // These should be no-ops for image output dev
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test updateAll with nullptr
TEST_F(CairoImageOutputDevTest_2447, UpdateAllNullptr_2447) {
    dev->updateAll(nullptr);
    SUCCEED();
}

// Test clearSoftMask with nullptr
TEST_F(CairoImageOutputDevTest_2447, ClearSoftMaskNullptr_2447) {
    dev->clearSoftMask(nullptr);
    SUCCEED();
}
