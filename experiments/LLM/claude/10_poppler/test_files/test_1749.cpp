#include <gtest/gtest.h>
#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1749 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }

    CairoImageOutputDev *dev;
};

// Test that a newly constructed CairoImageOutputDev has zero images
TEST_F(CairoImageOutputDevTest_1749, InitialNumImagesIsZero_1749) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that getImage returns nullptr or doesn't crash for out-of-range index on empty device
TEST_F(CairoImageOutputDevTest_1749, GetImageOnEmptyReturnsNull_1749) {
    CairoImage *img = dev->getImage(0);
    EXPECT_EQ(img, nullptr);
}

// Test negative index for getImage
TEST_F(CairoImageOutputDevTest_1749, GetImageNegativeIndexReturnsNull_1749) {
    CairoImage *img = dev->getImage(-1);
    EXPECT_EQ(img, nullptr);
}

// Test that boolean query methods return expected values
TEST_F(CairoImageOutputDevTest_1749, UpsideDownReturnValue_1749) {
    // Just verify it doesn't crash and returns a bool
    bool result = dev->upsideDown();
    (void)result; // We can't assert a specific value without knowing impl, but it should not crash
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UseDrawCharReturnValue_1749) {
    bool result = dev->useDrawChar();
    (void)result;
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UseTilingPatternFillReturnValue_1749) {
    bool result = dev->useTilingPatternFill();
    (void)result;
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UseFillColorStopReturnValue_1749) {
    bool result = dev->useFillColorStop();
    (void)result;
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, InterpretType3CharsReturnValue_1749) {
    bool result = dev->interpretType3Chars();
    (void)result;
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, NeedNonTextReturnValue_1749) {
    bool result = dev->needNonText();
    (void)result;
    SUCCEED();
}

// Test that setImageDrawDecideCbk can be called with nullptr without crashing
TEST_F(CairoImageOutputDevTest_1749, SetImageDrawDecideCbkNull_1749) {
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    SUCCEED();
}

// Test that setImageDrawDecideCbk can be set with a valid callback
static bool testDrawDecideCbk(int img_id, void *data) {
    int *counter = static_cast<int *>(data);
    if (counter) {
        (*counter)++;
    }
    return true;
}

TEST_F(CairoImageOutputDevTest_1749, SetImageDrawDecideCbkValid_1749) {
    int counter = 0;
    dev->setImageDrawDecideCbk(testDrawDecideCbk, &counter);
    // Just verify it doesn't crash
    SUCCEED();
}

// Test no-op state methods don't crash with nullptr state
TEST_F(CairoImageOutputDevTest_1749, SaveStateNullDoesNotCrash_1749) {
    dev->saveState(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, RestoreStateNullDoesNotCrash_1749) {
    dev->restoreState(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateAllNullDoesNotCrash_1749) {
    dev->updateAll(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, StrokeNullDoesNotCrash_1749) {
    dev->stroke(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, FillNullDoesNotCrash_1749) {
    dev->fill(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, EoFillNullDoesNotCrash_1749) {
    dev->eoFill(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, ClipNullDoesNotCrash_1749) {
    dev->clip(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, EoClipNullDoesNotCrash_1749) {
    dev->eoClip(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, ClipToStrokePathNullDoesNotCrash_1749) {
    dev->clipToStrokePath(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, ClearSoftMaskNullDoesNotCrash_1749) {
    dev->clearSoftMask(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateFillColorNullDoesNotCrash_1749) {
    dev->updateFillColor(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateStrokeColorNullDoesNotCrash_1749) {
    dev->updateStrokeColor(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateFillOpacityNullDoesNotCrash_1749) {
    dev->updateFillOpacity(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateStrokeOpacityNullDoesNotCrash_1749) {
    dev->updateStrokeOpacity(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateBlendModeNullDoesNotCrash_1749) {
    dev->updateBlendMode(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateFontNullDoesNotCrash_1749) {
    dev->updateFont(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateLineDashNullDoesNotCrash_1749) {
    dev->updateLineDash(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateFlatnessNullDoesNotCrash_1749) {
    dev->updateFlatness(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateLineJoinNullDoesNotCrash_1749) {
    dev->updateLineJoin(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateLineCapNullDoesNotCrash_1749) {
    dev->updateLineCap(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateMiterLimitNullDoesNotCrash_1749) {
    dev->updateMiterLimit(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UpdateLineWidthNullDoesNotCrash_1749) {
    dev->updateLineWidth(nullptr);
    SUCCEED();
}

// Test setDefaultCTM with identity-like matrix does not crash
TEST_F(CairoImageOutputDevTest_1749, SetDefaultCTMDoesNotCrash_1749) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);
    SUCCEED();
}

// Test updateCTM with nullptr state does not crash
TEST_F(CairoImageOutputDevTest_1749, UpdateCTMNullDoesNotCrash_1749) {
    dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    SUCCEED();
}

// Test getImage with large out-of-range index
TEST_F(CairoImageOutputDevTest_1749, GetImageLargeIndexReturnsNull_1749) {
    CairoImage *img = dev->getImage(999999);
    EXPECT_EQ(img, nullptr);
}

// Test that useShadedFills with various type values doesn't crash
TEST_F(CairoImageOutputDevTest_1749, UseShadedFillsType1_1749) {
    bool result = dev->useShadedFills(1);
    (void)result;
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UseShadedFillsType2_1749) {
    bool result = dev->useShadedFills(2);
    (void)result;
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, UseShadedFillsType0_1749) {
    bool result = dev->useShadedFills(0);
    (void)result;
    SUCCEED();
}

// Test endTransparencyGroup and paintTransparencyGroup with nullptr
TEST_F(CairoImageOutputDevTest_1749, EndTransparencyGroupNullDoesNotCrash_1749) {
    dev->endTransparencyGroup(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, PaintTransparencyGroupNullDoesNotCrash_1749) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    dev->paintTransparencyGroup(nullptr, bbox);
    SUCCEED();
}

// Test beginTransparencyGroup with nullptr
TEST_F(CairoImageOutputDevTest_1749, BeginTransparencyGroupNullDoesNotCrash_1749) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false);
    SUCCEED();
}

// Verify that a callback that returns false can be set
static bool rejectAllCbk(int img_id, void *data) {
    return false;
}

TEST_F(CairoImageOutputDevTest_1749, SetRejectAllCallback_1749) {
    dev->setImageDrawDecideCbk(rejectAllCbk, nullptr);
    // Verify the device still reports 0 images (no images drawn)
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test multiple constructions/destructions don't leak or crash
TEST_F(CairoImageOutputDevTest_1749, MultipleConstructDestruct_1749) {
    for (int i = 0; i < 10; i++) {
        CairoImageOutputDev *tmpDev = new CairoImageOutputDev();
        EXPECT_EQ(tmpDev->getNumImages(), 0);
        delete tmpDev;
    }
    SUCCEED();
}
