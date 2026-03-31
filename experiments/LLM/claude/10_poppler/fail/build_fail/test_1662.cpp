#include <gtest/gtest.h>
#include "PreScanOutputDev.h"

// We need to know the PSLevel enum. Based on poppler codebase, it's typically defined in PSOutputDev.h or similar.
// Including necessary headers for PSLevel and other dependencies.
#include "PSOutputDev.h"
#include "GfxState.h"

class PreScanOutputDevTest_1662 : public ::testing::Test {
protected:
    void SetUp() override {
        // PSLevel1 is typically the base level
        dev = new PreScanOutputDev(psLevel1);
    }

    void TearDown() override {
        delete dev;
    }

    PreScanOutputDev *dev;
};

// Test that a freshly constructed PreScanOutputDev reports monochrome
TEST_F(PreScanOutputDevTest_1662, InitialStateIsMonochrome_1662) {
    EXPECT_TRUE(dev->isMonochrome());
}

// Test that a freshly constructed PreScanOutputDev reports gray
TEST_F(PreScanOutputDevTest_1662, InitialStateIsGray_1662) {
    EXPECT_TRUE(dev->isGray());
}

// Test that a freshly constructed PreScanOutputDev does not use transparency
TEST_F(PreScanOutputDevTest_1662, InitialStateNoTransparency_1662) {
    EXPECT_FALSE(dev->usesTransparency());
}

// Test that a freshly constructed PreScanOutputDev reports all GDI
TEST_F(PreScanOutputDevTest_1662, InitialStateIsAllGDI_1662) {
    EXPECT_TRUE(dev->isAllGDI());
}

// Test that a freshly constructed PreScanOutputDev does not use pattern image mask
TEST_F(PreScanOutputDevTest_1662, InitialStateNoPatternImageMask_1662) {
    EXPECT_FALSE(dev->usesPatternImageMask());
}

// Test upsideDown returns expected value
TEST_F(PreScanOutputDevTest_1662, UpsideDownReturnValue_1662) {
    // PreScanOutputDev::upsideDown() should return true (typical for poppler output devices)
    EXPECT_TRUE(dev->upsideDown());
}

// Test useDrawChar returns expected value
TEST_F(PreScanOutputDevTest_1662, UseDrawCharReturnValue_1662) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test useTilingPatternFill returns expected value
TEST_F(PreScanOutputDevTest_1662, UseTilingPatternFillReturnValue_1662) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test useShadedFills returns expected value for different types
TEST_F(PreScanOutputDevTest_1662, UseShadedFillsReturnValue_1662) {
    EXPECT_TRUE(dev->useShadedFills(1));
    EXPECT_TRUE(dev->useShadedFills(2));
    EXPECT_TRUE(dev->useShadedFills(3));
}

// Test interpretType3Chars returns expected value
TEST_F(PreScanOutputDevTest_1662, InterpretType3CharsReturnValue_1662) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test clearStats resets state back to initial
TEST_F(PreScanOutputDevTest_1662, ClearStatsResetsState_1662) {
    dev->clearStats();
    EXPECT_TRUE(dev->isMonochrome());
    EXPECT_TRUE(dev->isGray());
    EXPECT_FALSE(dev->usesTransparency());
    EXPECT_TRUE(dev->isAllGDI());
    EXPECT_FALSE(dev->usesPatternImageMask());
}

// Test construction with different PS levels
TEST(PreScanOutputDevConstructionTest_1662, ConstructWithPSLevel2_1662) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
}

TEST(PreScanOutputDevConstructionTest_1662, ConstructWithPSLevel3_1662) {
    PreScanOutputDev dev(psLevel3);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
}

// Test that clearStats can be called multiple times without issue
TEST_F(PreScanOutputDevTest_1662, MultipleClearStatsCallsAreIdempotent_1662) {
    dev->clearStats();
    dev->clearStats();
    dev->clearStats();
    EXPECT_TRUE(dev->isMonochrome());
    EXPECT_TRUE(dev->isGray());
    EXPECT_FALSE(dev->usesTransparency());
    EXPECT_TRUE(dev->isAllGDI());
    EXPECT_FALSE(dev->usesPatternImageMask());
}

// Test beginTransparencyGroup sets transparency flag
TEST_F(PreScanOutputDevTest_1662, BeginTransparencyGroupSetsTransparency_1662) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false);
    EXPECT_TRUE(dev->usesTransparency());
}

// Test that after beginTransparencyGroup and clearStats, transparency is reset
TEST_F(PreScanOutputDevTest_1662, ClearStatsResetsTransparencyAfterBeginTransparencyGroup_1662) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev->beginTransparencyGroup(nullptr, bbox, nullptr, false, false, false);
    EXPECT_TRUE(dev->usesTransparency());
    dev->clearStats();
    EXPECT_FALSE(dev->usesTransparency());
}

// Test setSoftMask sets transparency
TEST_F(PreScanOutputDevTest_1662, SetSoftMaskSetsTransparency_1662) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev->setSoftMask(nullptr, bbox, false, nullptr, nullptr);
    EXPECT_TRUE(dev->usesTransparency());
}

// Test paintTransparencyGroup sets transparency
TEST_F(PreScanOutputDevTest_1662, PaintTransparencyGroupSetsTransparency_1662) {
    std::array<double, 4> bbox = {0, 0, 100, 100};
    dev->paintTransparencyGroup(nullptr, bbox);
    EXPECT_TRUE(dev->usesTransparency());
}
