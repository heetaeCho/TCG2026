#include <gtest/gtest.h>

#include "PreScanOutputDev.h"



class PreScanOutputDevTest_1655 : public ::testing::Test {

protected:

    PreScanOutputDev* preScanOutputDev;



    void SetUp() override {

        preScanOutputDev = new PreScanOutputDev(PSLevel());

    }



    void TearDown() override {

        delete preScanOutputDev;

    }

};



TEST_F(PreScanOutputDevTest_1655, UpsideDown_ReturnsTrue_1655) {

    EXPECT_TRUE(preScanOutputDev->upsideDown());

}



TEST_F(PreScanOutputDevTest_1655, UseDrawChar_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->useDrawChar());

}



TEST_F(PreScanOutputDevTest_1655, UseTilingPatternFill_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->useTilingPatternFill());

}



TEST_F(PreScanOutputDevTest_1655, UseShadedFills_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->useShadedFills(0));

}



TEST_F(PreScanOutputDevTest_1655, InterpretType3Chars_DefaultBehavior_1655) {

    EXPECT_TRUE(preScanOutputDev->interpretType3Chars());

}



TEST_F(PreScanOutputDevTest_1655, IsMonochrome_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->isMonochrome());

}



TEST_F(PreScanOutputDevTest_1655, IsGray_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->isGray());

}



TEST_F(PreScanOutputDevTest_1655, UsesTransparency_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->usesTransparency());

}



TEST_F(PreScanOutputDevTest_1655, IsAllGDI_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->isAllGDI());

}



TEST_F(PreScanOutputDevTest_1655, UsesPatternImageMask_DefaultBehavior_1655) {

    EXPECT_FALSE(preScanOutputDev->usesPatternImageMask());

}
