#include <gtest/gtest.h>

#include "poppler/PreScanOutputDev.h"

#include <array>



class PreScanOutputDevTest_1657 : public ::testing::Test {

protected:

    PreScanOutputDev* output_dev;



    void SetUp() override {

        output_dev = new PreScanOutputDev(PSLevel::level2);

    }



    void TearDown() override {

        delete output_dev;

    }

};



TEST_F(PreScanOutputDevTest_1657, useTilingPatternFill_ReturnsTrue_1657) {

    EXPECT_TRUE(output_dev->useTilingPatternFill());

}



TEST_F(PreScanOutputDevTest_1657, isMonochrome_DefaultValue_1657) {

    // Assuming default value of mono is false as it's not explicitly set in the constructor.

    EXPECT_FALSE(output_dev->isMonochrome());

}



TEST_F(PreScanOutputDevTest_1657, isGray_DefaultValue_1657) {

    // Assuming default value of gray is false as it's not explicitly set in the constructor.

    EXPECT_FALSE(output_dev->isGray());

}



TEST_F(PreScanOutputDevTest_1657, usesTransparency_DefaultValue_1657) {

    // Assuming default value of transparency is false as it's not explicitly set in the constructor.

    EXPECT_FALSE(output_dev->usesTransparency());

}



TEST_F(PreScanOutputDevTest_1657, isAllGDI_DefaultValue_1657) {

    // Assuming default value of gdi is false as it's not explicitly set in the constructor.

    EXPECT_FALSE(output_dev->isAllGDI());

}



TEST_F(PreScanOutputDevTest_1657, usesPatternImageMask_DefaultValue_1657) {

    // Assuming default value of patternImgMask is false as it's not explicitly set in the constructor.

    EXPECT_FALSE(output_dev->usesPatternImageMask());

}



TEST_F(PreScanOutputDevTest_1657, useShadedFills_DefaultValue_1657) {

    // Testing with a dummy type value 0

    EXPECT_TRUE(output_dev->useShadedFills(0));

}



TEST_F(PreScanOutputDevTest_1657, interpretType3Chars_DefaultValue_1657) {

    EXPECT_FALSE(output_dev->interpretType3Chars());

}



TEST_F(PreScanOutputDevTest_1657, upsideDown_ReturnsFalseByDefault_1657) {

    EXPECT_FALSE(output_dev->upsideDown());

}



TEST_F(PreScanOutputDevTest_1657, useDrawChar_ReturnsFalseByDefault_1657) {

    EXPECT_FALSE(output_dev->useDrawChar());

}
