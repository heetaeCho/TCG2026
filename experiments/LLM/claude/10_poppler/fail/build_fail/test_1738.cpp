#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1738 : public ::testing::Test {
protected:
    CairoImageOutputDev *dev;

    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }
};

// Test that upsideDown() returns true
TEST_F(CairoImageOutputDevTest_1738, UpsideDownReturnsTrue_1738) {
    EXPECT_TRUE(dev->upsideDown());
}

// Test that useDrawChar() returns a consistent value (expected false for image output dev)
TEST_F(CairoImageOutputDevTest_1738, UseDrawCharReturnValue_1738) {
    // Just verifying it doesn't crash and returns a boolean
    bool result = dev->useDrawChar();
    // Image output dev typically doesn't use draw char
    EXPECT_FALSE(result);
}

// Test that interpretType3Chars() returns a consistent value
TEST_F(CairoImageOutputDevTest_1738, InterpretType3CharsReturnValue_1738) {
    bool result = dev->interpretType3Chars();
    EXPECT_FALSE(result);
}

// Test that useTilingPatternFill() returns a value
TEST_F(CairoImageOutputDevTest_1738, UseTilingPatternFillReturnValue_1738) {
    bool result = dev->useTilingPatternFill();
    EXPECT_FALSE(result);
}

// Test that useFillColorStop() returns a value
TEST_F(CairoImageOutputDevTest_1738, UseFillColorStopReturnValue_1738) {
    bool result = dev->useFillColorStop();
    EXPECT_FALSE(result);
}

// Test that needNonText() returns a value
TEST_F(CairoImageOutputDevTest_1738, NeedNonTextReturnValue_1738) {
    bool result = dev->needNonText();
    EXPECT_FALSE(result);
}

// Test that getNumImages returns 0 initially
TEST_F(CairoImageOutputDevTest_1738, InitialNumImagesIsZero_1738) {
    EXPECT_EQ(0, dev->getNumImages());
}

// Test that getImage with index 0 on empty dev returns nullptr or handles gracefully
TEST_F(CairoImageOutputDevTest_1738, GetImageOnEmptyDevReturnsNull_1738) {
    // With no images, requesting any image should return nullptr
    CairoImage *img = dev->getImage(0);
    EXPECT_EQ(nullptr, img);
}

// Test getImage with negative index
TEST_F(CairoImageOutputDevTest_1738, GetImageNegativeIndex_1738) {
    CairoImage *img = dev->getImage(-1);
    EXPECT_EQ(nullptr, img);
}

// Test getImage with out-of-range index
TEST_F(CairoImageOutputDevTest_1738, GetImageOutOfRangeIndex_1738) {
    CairoImage *img = dev->getImage(100);
    EXPECT_EQ(nullptr, img);
}

// Test setImageDrawDecideCbk with nullptr callback
TEST_F(CairoImageOutputDevTest_1738, SetImageDrawDecideCbkNull_1738) {
    // Setting callback to nullptr should not crash
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    EXPECT_EQ(0, dev->getNumImages());
}

// Test setImageDrawDecideCbk with a valid callback
static bool testCallback(int img_id, void *data) {
    return true;
}

TEST_F(CairoImageOutputDevTest_1738, SetImageDrawDecideCbkValid_1738) {
    int dummyData = 42;
    dev->setImageDrawDecideCbk(testCallback, &dummyData);
    // Should not crash, no images should be added just from setting callback
    EXPECT_EQ(0, dev->getNumImages());
}

// Test that no-op state methods don't crash with nullptr
TEST_F(CairoImageOutputDevTest_1738, SaveStateNullDoesNotCrash_1738) {
    dev->saveState(nullptr);
    // No crash means success
}

TEST_F(CairoImageOutputDevTest_1738, RestoreStateNullDoesNotCrash_1738) {
    dev->restoreState(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateAllNullDoesNotCrash_1738) {
    dev->updateAll(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, StrokeNullDoesNotCrash_1738) {
    dev->stroke(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, FillNullDoesNotCrash_1738) {
    dev->fill(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, EoFillNullDoesNotCrash_1738) {
    dev->eoFill(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, ClipNullDoesNotCrash_1738) {
    dev->clip(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, EoClipNullDoesNotCrash_1738) {
    dev->eoClip(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, ClipToStrokePathNullDoesNotCrash_1738) {
    dev->clipToStrokePath(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, ClearSoftMaskNullDoesNotCrash_1738) {
    dev->clearSoftMask(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateFontNullDoesNotCrash_1738) {
    dev->updateFont(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateLineWidthNullDoesNotCrash_1738) {
    dev->updateLineWidth(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateFillColorNullDoesNotCrash_1738) {
    dev->updateFillColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateStrokeColorNullDoesNotCrash_1738) {
    dev->updateStrokeColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateFillOpacityNullDoesNotCrash_1738) {
    dev->updateFillOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateStrokeOpacityNullDoesNotCrash_1738) {
    dev->updateStrokeOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateBlendModeNullDoesNotCrash_1738) {
    dev->updateBlendMode(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateLineDashNullDoesNotCrash_1738) {
    dev->updateLineDash(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateFlatnessNullDoesNotCrash_1738) {
    dev->updateFlatness(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateLineJoinNullDoesNotCrash_1738) {
    dev->updateLineJoin(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateLineCapNullDoesNotCrash_1738) {
    dev->updateLineCap(nullptr);
}

TEST_F(CairoImageOutputDevTest_1738, UpdateMiterLimitNullDoesNotCrash_1738) {
    dev->updateMiterLimit(nullptr);
}

// Test useShadedFills for various type values
TEST_F(CairoImageOutputDevTest_1738, UseShadedFillsReturnValue_1738) {
    EXPECT_FALSE(dev->useShadedFills(1));
    EXPECT_FALSE(dev->useShadedFills(2));
    EXPECT_FALSE(dev->useShadedFills(3));
    EXPECT_FALSE(dev->useShadedFills(0));
}

// Test setDefaultCTM doesn't crash
TEST_F(CairoImageOutputDevTest_1738, SetDefaultCTMDoesNotCrash_1738) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);
}

// Test updateCTM with nullptr state doesn't crash
TEST_F(CairoImageOutputDevTest_1738, UpdateCTMNullDoesNotCrash_1738) {
    dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

// Test endTransparencyGroup with nullptr
TEST_F(CairoImageOutputDevTest_1738, EndTransparencyGroupNullDoesNotCrash_1738) {
    dev->endTransparencyGroup(nullptr);
}

// Test that multiple creations and deletions don't leak
TEST_F(CairoImageOutputDevTest_1738, MultipleCreateDeleteCycles_1738) {
    for (int i = 0; i < 10; i++) {
        CairoImageOutputDev *tempDev = new CairoImageOutputDev();
        EXPECT_EQ(0, tempDev->getNumImages());
        EXPECT_TRUE(tempDev->upsideDown());
        delete tempDev;
    }
}

// Callback that denies all images
static bool denyAllCallback(int img_id, void *data) {
    return false;
}

TEST_F(CairoImageOutputDevTest_1738, SetDenyAllCallback_1738) {
    dev->setImageDrawDecideCbk(denyAllCallback, nullptr);
    EXPECT_EQ(0, dev->getNumImages());
}

// Test callback with data tracking
static bool trackingCallback(int img_id, void *data) {
    if (data) {
        int *count = static_cast<int *>(data);
        (*count)++;
    }
    return true;
}

TEST_F(CairoImageOutputDevTest_1738, SetTrackingCallback_1738) {
    int callCount = 0;
    dev->setImageDrawDecideCbk(trackingCallback, &callCount);
    // Just setting the callback shouldn't invoke it
    EXPECT_EQ(0, callCount);
    EXPECT_EQ(0, dev->getNumImages());
}
