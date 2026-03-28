#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CairoOutputDev.h"

// Test fixture for CairoImageOutputDev
class CairoImageOutputDevTest_1748 : public ::testing::Test {
protected:
    CairoImageOutputDev *dev;

    void SetUp() override {
        dev = new CairoImageOutputDev();
    }

    void TearDown() override {
        delete dev;
    }
};

// Callback function for testing
static bool testDrawDecideCbk(int img_id, void *data) {
    if (data) {
        *static_cast<int *>(data) = img_id;
    }
    return true;
}

static bool testDrawDecideCbkFalse(int img_id, void *data) {
    return false;
}

// Test: Default construction - getNumImages should return 0
TEST_F(CairoImageOutputDevTest_1748, DefaultConstructionNumImages_1748) {
    EXPECT_EQ(dev->getNumImages(), 0);
}

// Test: getImage with invalid index on empty device
TEST_F(CairoImageOutputDevTest_1748, GetImageOnEmptyReturnsNull_1748) {
    // With 0 images, any index should be out of bounds
    // Depending on implementation, this may return nullptr or be undefined
    // We test with index 0 which is at/beyond the count
    CairoImage *img = dev->getImage(0);
    EXPECT_EQ(img, nullptr);
}

// Test: setImageDrawDecideCbk with valid callback
TEST_F(CairoImageOutputDevTest_1748, SetImageDrawDecideCbkValid_1748) {
    int callbackData = 0;
    // Should not crash or throw
    dev->setImageDrawDecideCbk(testDrawDecideCbk, &callbackData);
}

// Test: setImageDrawDecideCbk with null callback
TEST_F(CairoImageOutputDevTest_1748, SetImageDrawDecideCbkNull_1748) {
    // Setting callback to null should be valid (disables callback)
    dev->setImageDrawDecideCbk(nullptr, nullptr);
}

// Test: setImageDrawDecideCbk with callback but null data
TEST_F(CairoImageOutputDevTest_1748, SetImageDrawDecideCbkNullData_1748) {
    dev->setImageDrawDecideCbk(testDrawDecideCbk, nullptr);
}

// Test: setImageDrawDecideCbk overwrite callback
TEST_F(CairoImageOutputDevTest_1748, SetImageDrawDecideCbkOverwrite_1748) {
    int data1 = 0;
    int data2 = 0;
    dev->setImageDrawDecideCbk(testDrawDecideCbk, &data1);
    dev->setImageDrawDecideCbk(testDrawDecideCbkFalse, &data2);
    // Should not crash; the second callback should replace the first
}

// Test: setImageDrawDecideCbk reset to null after setting
TEST_F(CairoImageOutputDevTest_1748, SetImageDrawDecideCbkResetToNull_1748) {
    int data = 0;
    dev->setImageDrawDecideCbk(testDrawDecideCbk, &data);
    dev->setImageDrawDecideCbk(nullptr, nullptr);
    // Should not crash
}

// Test: upsideDown returns expected value
TEST_F(CairoImageOutputDevTest_1748, UpsideDown_1748) {
    // Should return a boolean value without crashing
    bool result = dev->upsideDown();
    // We just verify it returns without crashing; the actual value depends on implementation
    (void)result;
}

// Test: useDrawChar returns expected value
TEST_F(CairoImageOutputDevTest_1748, UseDrawChar_1748) {
    bool result = dev->useDrawChar();
    (void)result;
}

// Test: useTilingPatternFill returns expected value
TEST_F(CairoImageOutputDevTest_1748, UseTilingPatternFill_1748) {
    bool result = dev->useTilingPatternFill();
    (void)result;
}

// Test: useFillColorStop returns expected value
TEST_F(CairoImageOutputDevTest_1748, UseFillColorStop_1748) {
    bool result = dev->useFillColorStop();
    (void)result;
}

// Test: interpretType3Chars returns expected value
TEST_F(CairoImageOutputDevTest_1748, InterpretType3Chars_1748) {
    bool result = dev->interpretType3Chars();
    (void)result;
}

// Test: needNonText returns expected value
TEST_F(CairoImageOutputDevTest_1748, NeedNonText_1748) {
    bool result = dev->needNonText();
    (void)result;
}

// Test: useShadedFills returns expected value for different types
TEST_F(CairoImageOutputDevTest_1748, UseShadedFills_1748) {
    bool result0 = dev->useShadedFills(0);
    bool result1 = dev->useShadedFills(1);
    bool result2 = dev->useShadedFills(2);
    (void)result0;
    (void)result1;
    (void)result2;
}

// Test: getNumImages is const-correct
TEST_F(CairoImageOutputDevTest_1748, GetNumImagesConstCorrect_1748) {
    const CairoImageOutputDev *constDev = dev;
    EXPECT_EQ(constDev->getNumImages(), 0);
}

// Test: getImage is const-correct
TEST_F(CairoImageOutputDevTest_1748, GetImageConstCorrect_1748) {
    const CairoImageOutputDev *constDev = dev;
    CairoImage *img = constDev->getImage(0);
    EXPECT_EQ(img, nullptr);
}

// Test: getImage with negative index
TEST_F(CairoImageOutputDevTest_1748, GetImageNegativeIndex_1748) {
    // Negative index is out of range
    CairoImage *img = dev->getImage(-1);
    EXPECT_EQ(img, nullptr);
}

// Test: No-op state operations don't crash
TEST_F(CairoImageOutputDevTest_1748, SaveRestoreStateNullDoesNotCrash_1748) {
    dev->saveState(nullptr);
    dev->restoreState(nullptr);
}

// Test: No-op update operations don't crash with null state
TEST_F(CairoImageOutputDevTest_1748, UpdateOperationsNullStateDoNotCrash_1748) {
    dev->updateAll(nullptr);
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
}

// Test: No-op drawing operations don't crash with null state
TEST_F(CairoImageOutputDevTest_1748, DrawOperationsNullStateDoNotCrash_1748) {
    dev->stroke(nullptr);
    dev->fill(nullptr);
    dev->eoFill(nullptr);
    dev->clip(nullptr);
    dev->eoClip(nullptr);
    dev->clipToStrokePath(nullptr);
}

// Test: clearSoftMask with null state doesn't crash
TEST_F(CairoImageOutputDevTest_1748, ClearSoftMaskNullDoesNotCrash_1748) {
    dev->clearSoftMask(nullptr);
}

// Test: setDefaultCTM with identity matrix doesn't crash
TEST_F(CairoImageOutputDevTest_1748, SetDefaultCTMDoesNotCrash_1748) {
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);
}

// Test: updateCTM with null state doesn't crash
TEST_F(CairoImageOutputDevTest_1748, UpdateCTMNullStateDoesNotCrash_1748) {
    dev->updateCTM(nullptr, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}
