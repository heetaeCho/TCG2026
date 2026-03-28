#include <gtest/gtest.h>
#include "PreScanOutputDev.h"

// We need to know what PSLevel values are available
// Based on poppler codebase, PSLevel is typically an enum
// Common values include psLevel1, psLevel1Sep, psLevel2, psLevel2Sep, psLevel3, psLevel3Sep

class PreScanOutputDevTest_1660 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a PreScanOutputDev with a default PS level
        dev = new PreScanOutputDev(psLevel2);
    }

    void TearDown() override {
        delete dev;
    }

    PreScanOutputDev *dev;
};

// Test that after construction and clearStats, isMonochrome returns true
// (initial state should be monochrome since nothing has been scanned yet)
TEST_F(PreScanOutputDevTest_1660, InitialIsMonochrome_1660) {
    dev->clearStats();
    EXPECT_TRUE(dev->isMonochrome());
}

// Test that after construction and clearStats, isGray returns true
TEST_F(PreScanOutputDevTest_1660, InitialIsGray_1660) {
    dev->clearStats();
    EXPECT_TRUE(dev->isGray());
}

// Test that after construction and clearStats, usesTransparency returns false
TEST_F(PreScanOutputDevTest_1660, InitialUsesTransparency_1660) {
    dev->clearStats();
    EXPECT_FALSE(dev->usesTransparency());
}

// Test that after construction and clearStats, isAllGDI returns true
TEST_F(PreScanOutputDevTest_1660, InitialIsAllGDI_1660) {
    dev->clearStats();
    EXPECT_TRUE(dev->isAllGDI());
}

// Test that after construction and clearStats, usesPatternImageMask returns false
TEST_F(PreScanOutputDevTest_1660, InitialUsesPatternImageMask_1660) {
    dev->clearStats();
    EXPECT_FALSE(dev->usesPatternImageMask());
}

// Test upsideDown returns expected value (typically true for OutputDev subclasses)
TEST_F(PreScanOutputDevTest_1660, UpsideDown_1660) {
    bool result = dev->upsideDown();
    EXPECT_TRUE(result);
}

// Test useDrawChar returns expected value
TEST_F(PreScanOutputDevTest_1660, UseDrawChar_1660) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result);
}

// Test useTilingPatternFill returns expected value
TEST_F(PreScanOutputDevTest_1660, UseTilingPatternFill_1660) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);
}

// Test useShadedFills returns expected value for different types
TEST_F(PreScanOutputDevTest_1660, UseShadedFillsType1_1660) {
    bool result = dev->useShadedFills(1);
    EXPECT_TRUE(result);
}

TEST_F(PreScanOutputDevTest_1660, UseShadedFillsType2_1660) {
    bool result = dev->useShadedFills(2);
    EXPECT_TRUE(result);
}

TEST_F(PreScanOutputDevTest_1660, UseShadedFillsType3_1660) {
    bool result = dev->useShadedFills(3);
    EXPECT_TRUE(result);
}

// Test interpretType3Chars returns expected value
TEST_F(PreScanOutputDevTest_1660, InterpretType3Chars_1660) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result);
}

// Test clearStats resets all flags to initial state
TEST_F(PreScanOutputDevTest_1660, ClearStatsResetsMonochrome_1660) {
    dev->clearStats();
    EXPECT_TRUE(dev->isMonochrome());
}

TEST_F(PreScanOutputDevTest_1660, ClearStatsResetsGray_1660) {
    dev->clearStats();
    EXPECT_TRUE(dev->isGray());
}

TEST_F(PreScanOutputDevTest_1660, ClearStatsResetsTransparency_1660) {
    dev->clearStats();
    EXPECT_FALSE(dev->usesTransparency());
}

TEST_F(PreScanOutputDevTest_1660, ClearStatsResetsGDI_1660) {
    dev->clearStats();
    EXPECT_TRUE(dev->isAllGDI());
}

TEST_F(PreScanOutputDevTest_1660, ClearStatsResetsPatternImageMask_1660) {
    dev->clearStats();
    EXPECT_FALSE(dev->usesPatternImageMask());
}

// Test with different PSLevel constructor arguments
TEST(PreScanOutputDevConstructor_1660, ConstructWithLevel1_1660) {
    PreScanOutputDev dev(psLevel1);
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

TEST(PreScanOutputDevConstructor_1660, ConstructWithLevel3_1660) {
    PreScanOutputDev dev(psLevel3);
    dev.clearStats();
    EXPECT_TRUE(dev.isMonochrome());
    EXPECT_TRUE(dev.isGray());
    EXPECT_FALSE(dev.usesTransparency());
    EXPECT_TRUE(dev.isAllGDI());
    EXPECT_FALSE(dev.usesPatternImageMask());
}

// Test that monochrome implies gray
TEST_F(PreScanOutputDevTest_1660, MonochromeImpliesGray_1660) {
    dev->clearStats();
    if (dev->isMonochrome()) {
        EXPECT_TRUE(dev->isGray());
    }
}

// Test multiple clearStats calls
TEST_F(PreScanOutputDevTest_1660, MultipleClearStats_1660) {
    dev->clearStats();
    dev->clearStats();
    dev->clearStats();
    EXPECT_TRUE(dev->isMonochrome());
    EXPECT_TRUE(dev->isGray());
    EXPECT_FALSE(dev->usesTransparency());
    EXPECT_TRUE(dev->isAllGDI());
    EXPECT_FALSE(dev->usesPatternImageMask());
}
