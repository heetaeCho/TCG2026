#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1744 : public ::testing::Test {
protected:
    CairoImageOutputDev *dev;

    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }
};

// Test that needNonText returns true
TEST_F(CairoImageOutputDevTest_1744, NeedNonTextReturnsTrue_1744) {
    EXPECT_TRUE(dev->needNonText());
}

// Test that initially there are no images
TEST_F(CairoImageOutputDevTest_1744, InitialNumImagesIsZero_1744) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test getImage with no images stored - boundary condition
TEST_F(CairoImageOutputDevTest_1744, GetImageWithNoImages_1744) {
    // When no images exist, getImage for any index should return nullptr or handle gracefully
    CairoImage *img = dev->getImage(0);
    EXPECT_EQ(img, nullptr);
}

// Test getImage with negative index - boundary condition
TEST_F(CairoImageOutputDevTest_1744, GetImageNegativeIndex_1744) {
    CairoImage *img = dev->getImage(-1);
    EXPECT_EQ(img, nullptr);
}

// Test upsideDown override
TEST_F(CairoImageOutputDevTest_1744, UpsideDown_1744) {
    // Just verify it doesn't crash and returns a bool
    bool result = dev->upsideDown();
    (void)result; // We just verify it's callable
}

// Test useDrawChar override
TEST_F(CairoImageOutputDevTest_1744, UseDrawChar_1744) {
    bool result = dev->useDrawChar();
    (void)result;
}

// Test useTilingPatternFill override
TEST_F(CairoImageOutputDevTest_1744, UseTilingPatternFill_1744) {
    bool result = dev->useTilingPatternFill();
    (void)result;
}

// Test useFillColorStop override
TEST_F(CairoImageOutputDevTest_1744, UseFillColorStop_1744) {
    bool result = dev->useFillColorStop();
    (void)result;
}

// Test interpretType3Chars override
TEST_F(CairoImageOutputDevTest_1744, InterpretType3Chars_1744) {
    bool result = dev->interpretType3Chars();
    (void)result;
}

// Test setImageDrawDecideCbk with nullptr callback
TEST_F(CairoImageOutputDevTest_1744, SetImageDrawDecideCbkNull_1744) {
    // Setting callback to null should not crash
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test setImageDrawDecideCbk with a valid callback
static bool testDrawDecideCbk(int img_id, void *data) {
    int *counter = static_cast<int*>(data);
    if (counter) {
        (*counter)++;
    }
    return true;
}

TEST_F(CairoImageOutputDevTest_1744, SetImageDrawDecideCbkValid_1744) {
    int counter = 0;
    dev->setImageDrawDecideCbk(testDrawDecideCbk, &counter);
    // Verify no crash; we can't directly test callback invocation without drawing
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that state manipulation functions don't crash with nullptr
TEST_F(CairoImageOutputDevTest_1744, SaveStateNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->saveState(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, RestoreStateNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->restoreState(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateAllNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateAll(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateFillColorNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateFillColor(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateStrokeColorNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateStrokeColor(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateFillOpacityNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateFillOpacity(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateStrokeOpacityNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateStrokeOpacity(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateBlendModeNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateBlendMode(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateFontNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateFont(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, StrokeNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->stroke(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, FillNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->fill(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, EoFillNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->eoFill(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, ClipNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->clip(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, EoClipNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->eoClip(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, ClipToStrokePathNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->clipToStrokePath(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateLineDashNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateLineDash(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateFlatnessNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateFlatness(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateLineJoinNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateLineJoin(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateLineCapNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateLineCap(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateMiterLimitNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateMiterLimit(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, UpdateLineWidthNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateLineWidth(nullptr));
}

TEST_F(CairoImageOutputDevTest_1744, ClearSoftMaskNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->clearSoftMask(nullptr));
}

// Test setDefaultCTM with identity matrix
TEST_F(CairoImageOutputDevTest_1744, SetDefaultCTM_1744) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_NO_FATAL_FAILURE(dev->setDefaultCTM(ctm));
}

// Test updateCTM with nullptr state
TEST_F(CairoImageOutputDevTest_1744, UpdateCTMNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0));
}

// Test useShadedFills for various types
TEST_F(CairoImageOutputDevTest_1744, UseShadedFillsType1_1744) {
    bool result = dev->useShadedFills(1);
    (void)result;
}

TEST_F(CairoImageOutputDevTest_1744, UseShadedFillsType2_1744) {
    bool result = dev->useShadedFills(2);
    (void)result;
}

// Test callback that rejects drawing
static bool rejectDrawCbk(int img_id, void *data) {
    return false;
}

TEST_F(CairoImageOutputDevTest_1744, SetRejectingCallback_1744) {
    dev->setImageDrawDecideCbk(rejectDrawCbk, nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test multiple construction/destruction cycles
TEST(CairoImageOutputDevLifecycle_1744, MultipleInstances_1744) {
    for (int i = 0; i < 5; i++) {
        CairoImageOutputDev *d = new CairoImageOutputDev();
        EXPECT_EQ(d->getNumImages(), 0);
        EXPECT_TRUE(d->needNonText());
        delete d;
    }
}

// Test getImage out of bounds after no images added
TEST_F(CairoImageOutputDevTest_1744, GetImageOutOfBounds_1744) {
    EXPECT_EQ(dev->getImage(100), nullptr);
}

// Test endTransparencyGroup and paintTransparencyGroup with nullptr
TEST_F(CairoImageOutputDevTest_1744, EndTransparencyGroupNullptr_1744) {
    EXPECT_NO_FATAL_FAILURE(dev->endTransparencyGroup(nullptr));
}

// Test unsetSoftMaskFromImageMask with nullptr state
TEST_F(CairoImageOutputDevTest_1744, UnsetSoftMaskFromImageMaskNullptr_1744) {
    std::array<double, 6> baseMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_NO_FATAL_FAILURE(dev->unsetSoftMaskFromImageMask(nullptr, baseMatrix));
}
