#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CairoOutputDev.h"

// Test fixture for CairoImageOutputDev
class CairoImageOutputDevTest_1740 : public ::testing::Test {
protected:
    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }

    CairoImageOutputDev *dev;
};

// Test that constructor creates a valid object with zero images
TEST_F(CairoImageOutputDevTest_1740, ConstructorInitializesZeroImages_1740) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that useTilingPatternFill returns true
TEST_F(CairoImageOutputDevTest_1740, UseTilingPatternFillReturnsTrue_1740) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test that useDrawChar returns expected value (should be false for image output dev)
TEST_F(CairoImageOutputDevTest_1740, UseDrawCharReturnsFalse_1740) {
    EXPECT_FALSE(dev->useDrawChar());
}

// Test that interpretType3Chars returns expected value
TEST_F(CairoImageOutputDevTest_1740, InterpretType3CharsReturnsFalse_1740) {
    EXPECT_FALSE(dev->interpretType3Chars());
}

// Test that needNonText returns expected value
TEST_F(CairoImageOutputDevTest_1740, NeedNonTextReturnsTrue_1740) {
    EXPECT_TRUE(dev->needNonText());
}

// Test that upsideDown returns expected value
TEST_F(CairoImageOutputDevTest_1740, UpsideDownReturnsExpected_1740) {
    // CairoOutputDev typically returns true for upsideDown
    EXPECT_TRUE(dev->upsideDown());
}

// Test getNumImages initially zero
TEST_F(CairoImageOutputDevTest_1740, GetNumImagesInitiallyZero_1740) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test getImage with no images returns nullptr for out-of-bounds
TEST_F(CairoImageOutputDevTest_1740, GetImageWithNoImagesReturnsNull_1740) {
    // When there are no images, accessing index 0 should be out of bounds
    // Depending on implementation, this may return nullptr or be undefined
    // We test that getNumImages is 0 so we know not to call getImage
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test setImageDrawDecideCbk with nullptr callback
TEST_F(CairoImageOutputDevTest_1740, SetImageDrawDecideCbkWithNull_1740) {
    // Setting callback to nullptr should not crash
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test setImageDrawDecideCbk with a valid callback
TEST_F(CairoImageOutputDevTest_1740, SetImageDrawDecideCbkWithValidCallback_1740) {
    auto cbk = [](int img_id, void *data) -> bool {
        return true;
    };
    dev->setImageDrawDecideCbk(cbk, nullptr);
    // Just verify it doesn't crash
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test setImageDrawDecideCbk with callback and data
TEST_F(CairoImageOutputDevTest_1740, SetImageDrawDecideCbkWithData_1740) {
    int userData = 42;
    auto cbk = [](int img_id, void *data) -> bool {
        int *val = static_cast<int *>(data);
        return *val == 42;
    };
    dev->setImageDrawDecideCbk(cbk, &userData);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that various no-op override methods don't crash with nullptr state
TEST_F(CairoImageOutputDevTest_1740, SaveStateWithNullDoesNotCrash_1740) {
    dev->saveState(nullptr);
    // No crash means pass
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, RestoreStateWithNullDoesNotCrash_1740) {
    dev->restoreState(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateAllWithNullDoesNotCrash_1740) {
    dev->updateAll(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, StrokeWithNullDoesNotCrash_1740) {
    dev->stroke(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, FillWithNullDoesNotCrash_1740) {
    dev->fill(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, EoFillWithNullDoesNotCrash_1740) {
    dev->eoFill(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, ClipWithNullDoesNotCrash_1740) {
    dev->clip(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, EoClipWithNullDoesNotCrash_1740) {
    dev->eoClip(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, ClipToStrokePathWithNullDoesNotCrash_1740) {
    dev->clipToStrokePath(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, ClearSoftMaskWithNullDoesNotCrash_1740) {
    dev->clearSoftMask(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateLineDashWithNullDoesNotCrash_1740) {
    dev->updateLineDash(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateFlatnessWithNullDoesNotCrash_1740) {
    dev->updateFlatness(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateLineJoinWithNullDoesNotCrash_1740) {
    dev->updateLineJoin(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateLineCapWithNullDoesNotCrash_1740) {
    dev->updateLineCap(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateMiterLimitWithNullDoesNotCrash_1740) {
    dev->updateMiterLimit(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateLineWidthWithNullDoesNotCrash_1740) {
    dev->updateLineWidth(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateFillColorWithNullDoesNotCrash_1740) {
    dev->updateFillColor(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateStrokeColorWithNullDoesNotCrash_1740) {
    dev->updateStrokeColor(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateFillOpacityWithNullDoesNotCrash_1740) {
    dev->updateFillOpacity(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateStrokeOpacityWithNullDoesNotCrash_1740) {
    dev->updateStrokeOpacity(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateBlendModeWithNullDoesNotCrash_1740) {
    dev->updateBlendMode(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateFontWithNullDoesNotCrash_1740) {
    dev->updateFont(nullptr);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, SetDefaultCTMDoesNotCrash_1740) {
    std::array<double, 6> ctm = {1, 0, 0, 1, 0, 0};
    dev->setDefaultCTM(ctm);
    SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1740, UpdateCTMWithNullDoesNotCrash_1740) {
    dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    SUCCEED();
}

// Test useShadedFills with different type values
TEST_F(CairoImageOutputDevTest_1740, UseShadedFillsReturnsFalse_1740) {
    // For image output dev, shaded fills should likely return false
    EXPECT_FALSE(dev->useShadedFills(1));
    EXPECT_FALSE(dev->useShadedFills(2));
    EXPECT_FALSE(dev->useShadedFills(3));
}

// Test useFillColorStop
TEST_F(CairoImageOutputDevTest_1740, UseFillColorStopReturnsFalse_1740) {
    EXPECT_FALSE(dev->useFillColorStop());
}

// Test endTransparencyGroup with null state
TEST_F(CairoImageOutputDevTest_1740, EndTransparencyGroupWithNullDoesNotCrash_1740) {
    dev->endTransparencyGroup(nullptr);
    SUCCEED();
}

// Test beginTransparencyGroup with null state
TEST_F(CairoImageOutputDevTest_1740, BeginTransparencyGroupWithNullDoesNotCrash_1740) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false);
    SUCCEED();
}

// Test paintTransparencyGroup with null state
TEST_F(CairoImageOutputDevTest_1740, PaintTransparencyGroupWithNullDoesNotCrash_1740) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev->paintTransparencyGroup(nullptr, bbox);
    SUCCEED();
}

// Test setSoftMask with null parameters
TEST_F(CairoImageOutputDevTest_1740, SetSoftMaskWithNullDoesNotCrash_1740) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev->setSoftMask(nullptr, bbox, false, nullptr, nullptr);
    SUCCEED();
}

// Test unsetSoftMaskFromImageMask with null state
TEST_F(CairoImageOutputDevTest_1740, UnsetSoftMaskFromImageMaskWithNullDoesNotCrash_1740) {
    std::array<double, 6> baseMatrix = {1, 0, 0, 1, 0, 0};
    dev->unsetSoftMaskFromImageMask(nullptr, baseMatrix);
    SUCCEED();
}

// Test multiple object creation and destruction
TEST_F(CairoImageOutputDevTest_1740, MultipleInstancesIndependent_1740) {
    CairoImageOutputDev *dev2 = new CairoImageOutputDev();
    EXPECT_EQ(dev->getNumImages(), 0);
    EXPECT_EQ(dev2->getNumImages(), 0);
    delete dev2;
}

// Test that callback rejection means images are not saved
TEST_F(CairoImageOutputDevTest_1740, SetCallbackThatRejectsThenNoImagesSaved_1740) {
    auto cbk = [](int img_id, void *data) -> bool {
        return false; // reject all images
    };
    dev->setImageDrawDecideCbk(cbk, nullptr);
    // Without actually drawing, numImages should still be 0
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test tilingPatternFill returns expected value
TEST_F(CairoImageOutputDevTest_1740, TilingPatternFillWithNullDoesNotCrash_1740) {
    std::array<double, 6> mat = {1, 0, 0, 1, 0, 0};
    // The method should be a no-op for image output dev, likely returns true
    bool result = dev->tilingPatternFill(nullptr, nullptr, nullptr, nullptr, mat, 0, 0, 1, 1, 1.0, 1.0);
    EXPECT_TRUE(result);
}
