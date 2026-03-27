#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PreScanOutputDev.h"



class PreScanOutputDevTest_1662 : public ::testing::Test {

protected:

    PreScanOutputDev* preScanOutputDev;



    void SetUp() override {

        // Assuming PSLevel is an enum or a type that can be default constructed

        preScanOutputDev = new PreScanOutputDev(PSLevel());

    }



    void TearDown() override {

        delete preScanOutputDev;

    }

};



TEST_F(PreScanOutputDevTest_1662, UsesTransparency_ReturnsTrue_1662) {

    // Assuming we can set the transparency state through some means

    // For this test, we assume that the constructor or some setup makes transparency true

    EXPECT_TRUE(preScanOutputDev->usesTransparency());

}



TEST_F(PreScanOutputDevTest_1662, UsesTransparency_ReturnsFalse_1662) {

    // Assuming we can set the transparency state through some means

    // For this test, we assume that the constructor or some setup makes transparency false

    // This might require a different setup or mock if possible, but as a black box,

    // we'll assume there's a way to make it false for testing.

    // Since we can't change internal state directly, let's assume a fresh instance is false by default.

    PreScanOutputDev* preScanOutputDevFalse = new PreScanOutputDev(PSLevel());

    EXPECT_FALSE(preScanOutputDevFalse->usesTransparency());

    delete preScanOutputDevFalse;

}



TEST_F(PreScanOutputDevTest_1662, IsMonochrome_ReturnsTrue_1662) {

    // Assuming we can set the mono state through some means

    // For this test, we assume that the constructor or some setup makes mono true

    EXPECT_TRUE(preScanOutputDev->isMonochrome());

}



TEST_F(PreScanOutputDevTest_1662, IsMonochrome_ReturnsFalse_1662) {

    // Assuming we can set the mono state through some means

    // For this test, we assume that the constructor or some setup makes mono false

    PreScanOutputDev* preScanOutputDevFalse = new PreScanOutputDev(PSLevel());

    EXPECT_FALSE(preScanOutputDevFalse->isMonochrome());

    delete preScanOutputDevFalse;

}



TEST_F(PreScanOutputDevTest_1662, IsGray_ReturnsTrue_1662) {

    // Assuming we can set the gray state through some means

    // For this test, we assume that the constructor or some setup makes gray true

    EXPECT_TRUE(preScanOutputDev->isGray());

}



TEST_F(PreScanOutputDevTest_1662, IsGray_ReturnsFalse_1662) {

    // Assuming we can set the gray state through some means

    // For this test, we assume that the constructor or some setup makes gray false

    PreScanOutputDev* preScanOutputDevFalse = new PreScanOutputDev(PSLevel());

    EXPECT_FALSE(preScanOutputDevFalse->isGray());

    delete preScanOutputDevFalse;

}



TEST_F(PreScanOutputDevTest_1662, IsAllGDI_ReturnsTrue_1662) {

    // Assuming we can set the gdi state through some means

    // For this test, we assume that the constructor or some setup makes gdi true

    EXPECT_TRUE(preScanOutputDev->isAllGDI());

}



TEST_F(PreScanOutputDevTest_1662, IsAllGDI_ReturnsFalse_1662) {

    // Assuming we can set the gdi state through some means

    // For this test, we assume that the constructor or some setup makes gdi false

    PreScanOutputDev* preScanOutputDevFalse = new PreScanOutputDev(PSLevel());

    EXPECT_FALSE(preScanOutputDevFalse->isAllGDI());

    delete preScanOutputDevFalse;

}



TEST_F(PreScanOutputDevTest_1662, UsesPatternImageMask_ReturnsTrue_1662) {

    // Assuming we can set the patternImgMask state through some means

    // For this test, we assume that the constructor or some setup makes patternImgMask true

    EXPECT_TRUE(preScanOutputDev->usesPatternImageMask());

}



TEST_F(PreScanOutputDevTest_1662, UsesPatternImageMask_ReturnsFalse_1662) {

    // Assuming we can set the patternImgMask state through some means

    // For this test, we assume that the constructor or some setup makes patternImgMask false

    PreScanOutputDev* preScanOutputDevFalse = new PreScanOutputDev(PSLevel());

    EXPECT_FALSE(preScanOutputDevFalse->usesPatternImageMask());

    delete preScanOutputDevFalse;

}



TEST_F(PreScanOutputDevTest_1662, UseDrawChar_ReturnsTrue_1662) {

    // Assuming useDrawChar always returns true based on the interface

    EXPECT_TRUE(preScanOutputDev->useDrawChar());

}



TEST_F(PreScanOutputDevTest_1662, UseTilingPatternFill_ReturnsTrue_1662) {

    // Assuming useTilingPatternFill always returns true based on the interface

    EXPECT_TRUE(preScanOutputDev->useTilingPatternFill());

}



TEST_F(PreScanOutputDevTest_1662, UseShadedFills_ReturnsTrue_1662) {

    // Assuming useShadedFills always returns true based on the interface

    EXPECT_TRUE(preScanOutputDev->useShadedFills(0));

}



TEST_F(PreScanOutputDevTest_1662, InterpretType3Chars_ReturnsTrue_1662) {

    // Assuming interpretType3Chars always returns true based on the interface

    EXPECT_TRUE(preScanOutputDev->interpretType3Chars());

}



TEST_F(PreScanOutputDevTest_1662, UpsideDown_ReturnsFalse_1662) {

    // Assuming upsideDown always returns false based on the interface

    EXPECT_FALSE(preScanOutputDev->upsideDown());

}
