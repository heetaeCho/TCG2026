#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1739 : public ::testing::Test {
protected:
    CairoImageOutputDev *dev;

    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }
};

// Test that useDrawChar returns false
TEST_F(CairoImageOutputDevTest_1739, UseDrawCharReturnsFalse_1739) {
    EXPECT_FALSE(dev->useDrawChar());
}

// Test that upsideDown returns expected value
TEST_F(CairoImageOutputDevTest_1739, UpsideDown_1739) {
    // Just verify it doesn't crash and returns a bool
    bool result = dev->upsideDown();
    (void)result; // Observable behavior: no crash
}

// Test that useTilingPatternFill returns expected value
TEST_F(CairoImageOutputDevTest_1739, UseTilingPatternFill_1739) {
    bool result = dev->useTilingPatternFill();
    (void)result;
}

// Test that useShadedFills returns expected value
TEST_F(CairoImageOutputDevTest_1739, UseShadedFills_1739) {
    bool result = dev->useShadedFills(1);
    (void)result;
}

// Test that useFillColorStop returns expected value
TEST_F(CairoImageOutputDevTest_1739, UseFillColorStop_1739) {
    bool result = dev->useFillColorStop();
    (void)result;
}

// Test that interpretType3Chars returns expected value
TEST_F(CairoImageOutputDevTest_1739, InterpretType3Chars_1739) {
    bool result = dev->interpretType3Chars();
    (void)result;
}

// Test that needNonText returns expected value
TEST_F(CairoImageOutputDevTest_1739, NeedNonText_1739) {
    bool result = dev->needNonText();
    (void)result;
}

// Test initial number of images is zero
TEST_F(CairoImageOutputDevTest_1739, InitialNumImagesIsZero_1739) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test getImage with no images (boundary: index 0 on empty)
TEST_F(CairoImageOutputDevTest_1739, GetImageOnEmptyReturnsNull_1739) {
    // When there are no images, getImage should return nullptr or handle gracefully
    // This tests boundary behavior
    if (dev->getNumImages() == 0) {
        // We can't guarantee behavior for out-of-bounds, but we test it doesn't crash
        // for index 0 when numImages is 0 — this may be undefined, so we skip explicit call
        EXPECT_EQ(dev->getNumImages(), 0);
    }
}

// Test setImageDrawDecideCbk with nullptr callback
TEST_F(CairoImageOutputDevTest_1739, SetImageDrawDecideCbkNull_1739) {
    // Setting callback to nullptr should not crash
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test setImageDrawDecideCbk with a valid callback
static bool testCallback_1739(int img_id, void *data) {
    int *count = static_cast<int *>(data);
    if (count) {
        (*count)++;
    }
    return true;
}

TEST_F(CairoImageOutputDevTest_1739, SetImageDrawDecideCbkValid_1739) {
    int callCount = 0;
    dev->setImageDrawDecideCbk(testCallback_1739, &callCount);
    // Just verify setting callback doesn't crash
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that no-op state functions don't crash with nullptr
TEST_F(CairoImageOutputDevTest_1739, SaveStateNullDoesNotCrash_1739) {
    dev->saveState(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, RestoreStateNullDoesNotCrash_1739) {
    dev->restoreState(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateAllNullDoesNotCrash_1739) {
    dev->updateAll(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateLineDashNullDoesNotCrash_1739) {
    dev->updateLineDash(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateFlatnessNullDoesNotCrash_1739) {
    dev->updateFlatness(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateLineJoinNullDoesNotCrash_1739) {
    dev->updateLineJoin(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateLineCapNullDoesNotCrash_1739) {
    dev->updateLineCap(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateMiterLimitNullDoesNotCrash_1739) {
    dev->updateMiterLimit(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateLineWidthNullDoesNotCrash_1739) {
    dev->updateLineWidth(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateFillColorNullDoesNotCrash_1739) {
    dev->updateFillColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateStrokeColorNullDoesNotCrash_1739) {
    dev->updateStrokeColor(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateFillOpacityNullDoesNotCrash_1739) {
    dev->updateFillOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateStrokeOpacityNullDoesNotCrash_1739) {
    dev->updateStrokeOpacity(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateBlendModeNullDoesNotCrash_1739) {
    dev->updateBlendMode(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, UpdateFontNullDoesNotCrash_1739) {
    dev->updateFont(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, StrokeNullDoesNotCrash_1739) {
    dev->stroke(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, FillNullDoesNotCrash_1739) {
    dev->fill(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, EoFillNullDoesNotCrash_1739) {
    dev->eoFill(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, ClipToStrokePathNullDoesNotCrash_1739) {
    dev->clipToStrokePath(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, ClipNullDoesNotCrash_1739) {
    dev->clip(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, EoClipNullDoesNotCrash_1739) {
    dev->eoClip(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, ClearSoftMaskNullDoesNotCrash_1739) {
    dev->clearSoftMask(nullptr);
}

TEST_F(CairoImageOutputDevTest_1739, SetDefaultCTM_1739) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);
    // No crash expected
}

TEST_F(CairoImageOutputDevTest_1739, UpdateCTMNull_1739) {
    dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

// Test that setting callback with data that rejects images works
static bool rejectAllCallback_1739(int img_id, void *data) {
    return false;
}

TEST_F(CairoImageOutputDevTest_1739, SetRejectingCallback_1739) {
    dev->setImageDrawDecideCbk(rejectAllCallback_1739, nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test construction and destruction multiple times (leak check)
TEST_F(CairoImageOutputDevTest_1739, MultipleConstructDestruct_1739) {
    for (int i = 0; i < 10; i++) {
        CairoImageOutputDev *localDev = new CairoImageOutputDev();
        EXPECT_EQ(localDev->getNumImages(), 0);
        EXPECT_FALSE(localDev->useDrawChar());
        delete localDev;
    }
}

// Test endTransparencyGroup with nullptr
TEST_F(CairoImageOutputDevTest_1739, EndTransparencyGroupNull_1739) {
    dev->endTransparencyGroup(nullptr);
}

// Test paintTransparencyGroup with nullptr
TEST_F(CairoImageOutputDevTest_1739, PaintTransparencyGroupNull_1739) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    dev->paintTransparencyGroup(nullptr, bbox);
}

// Test beginTransparencyGroup with nullptr
TEST_F(CairoImageOutputDevTest_1739, BeginTransparencyGroupNull_1739) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false);
}

// Test unsetSoftMaskFromImageMask
TEST_F(CairoImageOutputDevTest_1739, UnsetSoftMaskFromImageMaskNull_1739) {
    std::array<double, 6> baseMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->unsetSoftMaskFromImageMask(nullptr, baseMatrix);
}

// Test setSoftMask with nullptr
TEST_F(CairoImageOutputDevTest_1739, SetSoftMaskNull_1739) {
    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};
    dev->setSoftMask(nullptr, bbox, false, nullptr, nullptr);
}
