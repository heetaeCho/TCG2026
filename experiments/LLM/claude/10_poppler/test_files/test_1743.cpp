#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1743 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }

    CairoImageOutputDev *dev;
};

// Test that interpretType3Chars returns false
TEST_F(CairoImageOutputDevTest_1743, InterpretType3CharsReturnsFalse_1743) {
    EXPECT_FALSE(dev->interpretType3Chars());
}

// Test that initial number of images is zero
TEST_F(CairoImageOutputDevTest_1743, InitialNumImagesIsZero_1743) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that getImage returns nullptr for invalid index when no images
TEST_F(CairoImageOutputDevTest_1743, GetImageReturnsNullForInvalidIndex_1743) {
    // With no images, any index should be out of bounds
    // Depending on implementation, this may return nullptr or undefined behavior
    // We test index 0 on empty
    CairoImage *img = dev->getImage(0);
    EXPECT_EQ(img, nullptr);
}

// Test upsideDown override behavior
TEST_F(CairoImageOutputDevTest_1743, UpsideDownReturnValue_1743) {
    // CairoImageOutputDev overrides upsideDown; just verify it's callable and returns a bool
    bool result = dev->upsideDown();
    // The base CairoOutputDev typically returns true for upsideDown
    EXPECT_TRUE(result);
}

// Test useDrawChar override behavior
TEST_F(CairoImageOutputDevTest_1743, UseDrawCharReturnValue_1743) {
    bool result = dev->useDrawChar();
    // For an image-only output device, this is expected to return false
    EXPECT_FALSE(result);
}

// Test useTilingPatternFill override behavior
TEST_F(CairoImageOutputDevTest_1743, UseTilingPatternFillReturnValue_1743) {
    bool result = dev->useTilingPatternFill();
    // Image output device likely returns false for tiling pattern fill
    EXPECT_FALSE(result);
}

// Test useShadedFills override behavior
TEST_F(CairoImageOutputDevTest_1743, UseShadedFillsReturnValue_1743) {
    bool result = dev->useShadedFills(1);
    EXPECT_FALSE(result);
}

// Test useFillColorStop override behavior
TEST_F(CairoImageOutputDevTest_1743, UseFillColorStopReturnValue_1743) {
    bool result = dev->useFillColorStop();
    EXPECT_FALSE(result);
}

// Test needNonText override behavior
TEST_F(CairoImageOutputDevTest_1743, NeedNonTextReturnValue_1743) {
    bool result = dev->needNonText();
    // Image output device needs non-text (images)
    EXPECT_TRUE(result);
}

// Test that setImageDrawDecideCbk can be called without crashing
TEST_F(CairoImageOutputDevTest_1743, SetImageDrawDecideCbkNullCallback_1743) {
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    // No crash expected
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test setImageDrawDecideCbk with a valid callback
static bool testDrawDecideCbk(int img_id, void *data) {
    int *counter = static_cast<int *>(data);
    if (counter) {
        (*counter)++;
    }
    return true;
}

TEST_F(CairoImageOutputDevTest_1743, SetImageDrawDecideCbkWithValidCallback_1743) {
    int counter = 0;
    dev->setImageDrawDecideCbk(testDrawDecideCbk, &counter);
    // Just verifying it doesn't crash; actual callback invocation requires drawImage calls
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that no-op state methods don't crash
TEST_F(CairoImageOutputDevTest_1743, SaveStateNoCrash_1743) {
    dev->saveState(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1743, RestoreStateNoCrash_1743) {
    dev->restoreState(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateAllNoCrash_1743) {
    dev->updateAll(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test no-op drawing methods don't crash
TEST_F(CairoImageOutputDevTest_1743, StrokeNoCrash_1743) {
    dev->stroke(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1743, FillNoCrash_1743) {
    dev->fill(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1743, EoFillNoCrash_1743) {
    dev->eoFill(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1743, ClipNoCrash_1743) {
    dev->clip(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1743, EoClipNoCrash_1743) {
    dev->eoClip(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1743, ClipToStrokePathNoCrash_1743) {
    dev->clipToStrokePath(nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test no-op update methods don't crash
TEST_F(CairoImageOutputDevTest_1743, UpdateLineDashNoCrash_1743) {
    dev->updateLineDash(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateFlatnessNoCrash_1743) {
    dev->updateFlatness(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateLineJoinNoCrash_1743) {
    dev->updateLineJoin(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateLineCapNoCrash_1743) {
    dev->updateLineCap(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateMiterLimitNoCrash_1743) {
    dev->updateMiterLimit(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateLineWidthNoCrash_1743) {
    dev->updateLineWidth(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateFillColorNoCrash_1743) {
    dev->updateFillColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateStrokeColorNoCrash_1743) {
    dev->updateStrokeColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateFillOpacityNoCrash_1743) {
    dev->updateFillOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateStrokeOpacityNoCrash_1743) {
    dev->updateStrokeOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateBlendModeNoCrash_1743) {
    dev->updateBlendMode(nullptr);
}

TEST_F(CairoImageOutputDevTest_1743, UpdateFontNoCrash_1743) {
    dev->updateFont(nullptr);
}

// Test clearSoftMask doesn't crash
TEST_F(CairoImageOutputDevTest_1743, ClearSoftMaskNoCrash_1743) {
    dev->clearSoftMask(nullptr);
}

// Test getImage with negative index (boundary)
TEST_F(CairoImageOutputDevTest_1743, GetImageNegativeIndex_1743) {
    CairoImage *img = dev->getImage(-1);
    EXPECT_EQ(img, nullptr);
}

// Test multiple construction/destruction cycles
TEST_F(CairoImageOutputDevTest_1743, MultipleConstructDestruct_1743) {
    CairoImageOutputDev *dev2 = new CairoImageOutputDev();
    EXPECT_EQ(dev2->getNumImages(), 0);
    EXPECT_FALSE(dev2->interpretType3Chars());
    delete dev2;
}

// Test setDefaultCTM doesn't crash
TEST_F(CairoImageOutputDevTest_1743, SetDefaultCTMNoCrash_1743) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);
}

// Test updateCTM doesn't crash
TEST_F(CairoImageOutputDevTest_1743, UpdateCTMNoCrash_1743) {
    dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

// Test callback that rejects images
static bool rejectAllCbk(int img_id, void *data) {
    return false;
}

TEST_F(CairoImageOutputDevTest_1743, SetRejectAllCallback_1743) {
    dev->setImageDrawDecideCbk(rejectAllCbk, nullptr);
    // Callback is set; actual rejection happens during drawImage
    EXPECT_EQ(dev->getNumImages(), 0);
}
