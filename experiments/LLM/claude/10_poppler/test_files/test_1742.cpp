#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1742 : public ::testing::Test {
protected:
    CairoImageOutputDev *dev;

    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }
};

// Test that useFillColorStop returns false
TEST_F(CairoImageOutputDevTest_1742, UseFillColorStopReturnsFalse_1742) {
    EXPECT_FALSE(dev->useFillColorStop());
}

// Test that initial number of images is zero
TEST_F(CairoImageOutputDevTest_1742, InitialNumImagesIsZero_1742) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test getImage with no images stored - boundary case
TEST_F(CairoImageOutputDevTest_1742, GetImageWithNoImages_1742) {
    // When there are no images, requesting any index should return nullptr or be invalid
    // Testing boundary: index 0 when numImages is 0
    CairoImage *img = dev->getImage(0);
    EXPECT_EQ(img, nullptr);
}

// Test upsideDown returns expected value
TEST_F(CairoImageOutputDevTest_1742, UpsideDown_1742) {
    // CairoOutputDev typically returns true for upsideDown
    bool result = dev->upsideDown();
    EXPECT_TRUE(result);
}

// Test useDrawChar returns expected value
TEST_F(CairoImageOutputDevTest_1742, UseDrawChar_1742) {
    bool result = dev->useDrawChar();
    // For image output dev, useDrawChar should return false since we don't care about text
    EXPECT_FALSE(result);
}

// Test useTilingPatternFill returns expected value
TEST_F(CairoImageOutputDevTest_1742, UseTilingPatternFill_1742) {
    bool result = dev->useTilingPatternFill();
    EXPECT_FALSE(result);
}

// Test useShadedFills returns expected value
TEST_F(CairoImageOutputDevTest_1742, UseShadedFills_1742) {
    bool result = dev->useShadedFills(1);
    EXPECT_FALSE(result);
}

// Test interpretType3Chars returns expected value
TEST_F(CairoImageOutputDevTest_1742, InterpretType3Chars_1742) {
    bool result = dev->interpretType3Chars();
    EXPECT_FALSE(result);
}

// Test needNonText returns expected value
TEST_F(CairoImageOutputDevTest_1742, NeedNonText_1742) {
    bool result = dev->needNonText();
    EXPECT_TRUE(result);
}

// Test setImageDrawDecideCbk sets callback without crashing
TEST_F(CairoImageOutputDevTest_1742, SetImageDrawDecideCbk_1742) {
    auto cbk = [](int img_id, void *data) -> bool {
        return true;
    };
    // This should not crash
    dev->setImageDrawDecideCbk(cbk, nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test setImageDrawDecideCbk with nullptr callback
TEST_F(CairoImageOutputDevTest_1742, SetImageDrawDecideCbkNull_1742) {
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test that saveState and restoreState don't crash with nullptr
TEST_F(CairoImageOutputDevTest_1742, SaveRestoreStateNullptr_1742) {
    dev->saveState(nullptr);
    dev->restoreState(nullptr);
    // No crash is the success criterion
    SUCCEED();
}

// Test that updateAll with nullptr doesn't crash
TEST_F(CairoImageOutputDevTest_1742, UpdateAllNullptr_1742) {
    dev->updateAll(nullptr);
    SUCCEED();
}

// Test that various update methods don't crash with nullptr
TEST_F(CairoImageOutputDevTest_1742, UpdateMethodsNullptr_1742) {
    dev->updateLineDash(nullptr);
    dev->updateFlatness(nullptr);
    dev->updateLineJoin(nullptr);
    dev->updateLineCap(nullptr);
    dev->updateMiterLimit(nullptr);
    dev->updateLineWidth(nullptr);
    dev->updateFillColor(nullptr);
    dev->updateStrokeColor(nullptr);
    dev->updateFillOpacity(nullptr);
    dev->updateStrokeOpacity(nullptr);
    dev->updateBlendMode(nullptr);
    dev->updateFont(nullptr);
    SUCCEED();
}

// Test that drawing operations don't crash with nullptr state
TEST_F(CairoImageOutputDevTest_1742, StrokeFillNullptr_1742) {
    dev->stroke(nullptr);
    dev->fill(nullptr);
    dev->eoFill(nullptr);
    SUCCEED();
}

// Test that clip operations don't crash with nullptr state
TEST_F(CairoImageOutputDevTest_1742, ClipOperationsNullptr_1742) {
    dev->clip(nullptr);
    dev->eoClip(nullptr);
    dev->clipToStrokePath(nullptr);
    SUCCEED();
}

// Test clearSoftMask with nullptr
TEST_F(CairoImageOutputDevTest_1742, ClearSoftMaskNullptr_1742) {
    dev->clearSoftMask(nullptr);
    SUCCEED();
}

// Test getImage with negative index - boundary
TEST_F(CairoImageOutputDevTest_1742, GetImageNegativeIndex_1742) {
    CairoImage *img = dev->getImage(-1);
    EXPECT_EQ(img, nullptr);
}

// Test that multiple getNumImages calls return consistent results
TEST_F(CairoImageOutputDevTest_1742, GetNumImagesConsistent_1742) {
    int count1 = dev->getNumImages();
    int count2 = dev->getNumImages();
    EXPECT_EQ(count1, count2);
    EXPECT_EQ(count1, 0);
}

// Test callback with user data
TEST_F(CairoImageOutputDevTest_1742, SetCallbackWithUserData_1742) {
    int userData = 42;
    auto cbk = [](int img_id, void *data) -> bool {
        int *val = static_cast<int *>(data);
        return *val == 42;
    };
    dev->setImageDrawDecideCbk(cbk, &userData);
    // Verify no crash and state is consistent
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test useShadedFills with different type values
TEST_F(CairoImageOutputDevTest_1742, UseShadedFillsDifferentTypes_1742) {
    for (int type = 0; type <= 7; ++type) {
        EXPECT_FALSE(dev->useShadedFills(type));
    }
}
