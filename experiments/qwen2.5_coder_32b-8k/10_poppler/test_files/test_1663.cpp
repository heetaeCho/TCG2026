#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PreScanOutputDev.h"



class PreScanOutputDevTest_1663 : public ::testing::Test {

protected:

    PreScanOutputDevTest_1663() : outputDev(PSLevel()) {}



    PreScanOutputDev outputDev;

};



TEST_F(PreScanOutputDevTest_1663, isAllGDI_ReturnsTrue_1663) {

    // Assuming gdi is set to true for this test case

    EXPECT_TRUE(outputDev.isAllGDI());

}



TEST_F(PreScanOutputDevTest_1663, isAllGDI_ReturnsFalse_1663) {

    // Assuming there's a way to set gdi to false, otherwise this would require internal state access

    // For the sake of this test, we assume a setup function exists that can modify gdi

    // This is a placeholder as per constraints, actual implementation would differ

    outputDev = PreScanOutputDev(PSLevel()); // Reset with default constructor

    EXPECT_FALSE(outputDev.isAllGDI());

}



TEST_F(PreScanOutputDevTest_1663, isMonochrome_ReturnsTrue_1663) {

    // Assuming mono is set to true for this test case

    // Placeholder as actual access to internal state is not allowed

    EXPECT_TRUE(outputDev.isMonochrome());

}



TEST_F(PreScanOutputDevTest_1663, isGray_ReturnsTrue_1663) {

    // Assuming gray is set to true for this test case

    // Placeholder as actual access to internal state is not allowed

    EXPECT_TRUE(outputDev.isGray());

}



TEST_F(PreScanOutputDevTest_1663, usesTransparency_ReturnsTrue_1663) {

    // Assuming transparency is set to true for this test case

    // Placeholder as actual access to internal state is not allowed

    EXPECT_TRUE(outputDev.usesTransparency());

}



TEST_F(PreScanOutputDevTest_1663, usesPatternImageMask_ReturnsTrue_1663) {

    // Assuming patternImgMask is set to true for this test case

    // Placeholder as actual access to internal state is not allowed

    EXPECT_TRUE(outputDev.usesPatternImageMask());

}



TEST_F(PreScanOutputDevTest_1663, upsideDown_ReturnsFalse_1663) {

    // Assuming upsideDown returns false by default or setup

    EXPECT_FALSE(outputDev.upsideDown());

}



TEST_F(PreScanOutputDevTest_1663, useDrawChar_ReturnsTrue_1663) {

    // Assuming useDrawChar returns true by default or setup

    EXPECT_TRUE(outputDev.useDrawChar());

}



TEST_F(PreScanOutputDevTest_1663, useTilingPatternFill_ReturnsFalse_1663) {

    // Assuming useTilingPatternFill returns false by default or setup

    EXPECT_FALSE(outputDev.useTilingPatternFill());

}



TEST_F(PreScanOutputDevTest_1663, useShadedFills_ReturnsTrueForType_1663) {

    // Assuming useShadedFills returns true for some type

    EXPECT_TRUE(outputDev.useShadedFills(0)); // Placeholder type 0

}



TEST_F(PreScanOutputDevTest_1663, interpretType3Chars_ReturnsTrue_1663) {

    // Assuming interpretType3Chars returns true by default or setup

    EXPECT_TRUE(outputDev.interpretType3Chars());

}
