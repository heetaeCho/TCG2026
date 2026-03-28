#include <gtest/gtest.h>
#include "PreScanOutputDev.h"

// We need to include necessary headers for PSLevel and other dependencies
#include "PSOutputDev.h"
#include "GfxState.h"
#include "GlobalParams.h"

class PreScanOutputDevTest_1664 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test construction with different PS levels
TEST_F(PreScanOutputDevTest_1664, ConstructWithPSLevel1_1664) {
    PreScanOutputDev dev(psLevel1);
    // After construction, default states should be clean
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

TEST_F(PreScanOutputDevTest_1664, ConstructWithPSLevel2_1664) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

TEST_F(PreScanOutputDevTest_1664, ConstructWithPSLevel3_1664) {
    PreScanOutputDev dev(psLevel3);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test upsideDown returns expected value
TEST_F(PreScanOutputDevTest_1664, UpsideDown_1664) {
    PreScanOutputDev dev(psLevel1);
    bool result = dev.upsideDown();
    EXPECT_TRUE(result);
}

// Test useDrawChar returns expected value
TEST_F(PreScanOutputDevTest_1664, UseDrawChar_1664) {
    PreScanOutputDev dev(psLevel1);
    bool result = dev.useDrawChar();
    EXPECT_TRUE(result);
}

// Test useTilingPatternFill returns expected value
TEST_F(PreScanOutputDevTest_1664, UseTilingPatternFill_1664) {
    PreScanOutputDev dev(psLevel1);
    bool result = dev.useTilingPatternFill();
    EXPECT_TRUE(result);
}

// Test useShadedFills returns expected value for various types
TEST_F(PreScanOutputDevTest_1664, UseShadedFillsType1_1664) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.useShadedFills(1));
}

TEST_F(PreScanOutputDevTest_1664, UseShadedFillsType2_1664) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.useShadedFills(2));
}

TEST_F(PreScanOutputDevTest_1664, UseShadedFillsType3_1664) {
    PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.useShadedFills(3));
}

// Test interpretType3Chars returns expected value
TEST_F(PreScanOutputDevTest_1664, InterpretType3Chars_1664) {
    PreScanOutputDev dev(psLevel1);
    bool result = dev.interpretType3Chars();
    EXPECT_TRUE(result);
}

// Test clearStats resets all flags to initial state
TEST_F(PreScanOutputDevTest_1664, ClearStatsResetsFlags_1664) {
    PreScanOutputDev dev(psLevel1);
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test isMonochrome after construction
TEST_F(PreScanOutputDevTest_1664, IsMonochromeInitially_1664) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.isMonochrome());
}

// Test isGray after construction
TEST_F(PreScanOutputDevTest_1664, IsGrayInitially_1664) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.isGray());
}

// Test usesTransparency after construction
TEST_F(PreScanOutputDevTest_1664, UsesTransparencyInitially_1664) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_FALSE(dev.usesTransparency());
}

// Test isAllGDI after construction
TEST_F(PreScanOutputDevTest_1664, IsAllGDIInitially_1664) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_TRUE(dev.isAllGDI());
}

// Test usesPatternImageMask after construction
TEST_F(PreScanOutputDevTest_1664, UsesPatternImageMaskInitially_1664) {
    PreScanOutputDev dev(psLevel2);
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test that clearStats can be called multiple times
TEST_F(PreScanOutputDevTest_1664, ClearStatsMultipleTimes_1664) {
    PreScanOutputDev dev(psLevel1);
    dev.clearStats();
    dev.clearStats();
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test startPage and endPage don't crash with nullptr state
TEST_F(PreScanOutputDevTest_1664, StartPageEndPage_1664) {
    PreScanOutputDev dev(psLevel1);
    dev.startPage(1, nullptr, nullptr);
    dev.endPage();
    // Should not crash, and stats should remain in initial state
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
}

// Test clip and eoClip with nullptr state don't crash
TEST_F(PreScanOutputDevTest_1664, ClipWithNullState_1664) {
    PreScanOutputDev dev(psLevel1);
    dev.clip(nullptr);
    dev.eoClip(nullptr);
    // These are no-ops for PreScanOutputDev typically
    EXPECT_TRUE(dev.isMonochrome());
}

// Test beginStringOp and endStringOp with nullptr state
TEST_F(PreScanOutputDevTest_1664, StringOpWithNullState_1664) {
    PreScanOutputDev dev(psLevel1);
    dev.beginStringOp(nullptr);
    dev.endStringOp(nullptr);
    EXPECT_TRUE(dev.isMonochrome());
}

// Test endType3Char with nullptr state
TEST_F(PreScanOutputDevTest_1664, EndType3CharWithNullState_1664) {
    PreScanOutputDev dev(psLevel1);
    dev.endType3Char(nullptr);
    EXPECT_TRUE(dev.isMonochrome());
}

// Test useShadedFills with type 0
TEST_F(PreScanOutputDevTest_1664, UseShadedFillsType0_1664) {
    PreScanOutputDev dev(psLevel1);
    bool result = dev.useShadedFills(0);
    // Type 0 may or may not be supported; just verify it returns a value
    (void)result;
}

// Test that all query methods are const-correct
TEST_F(PreScanOutputDevTest_1664, ConstCorrectnessOfQueries_1664) {
    const PreScanOutputDev dev(psLevel1);
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}
