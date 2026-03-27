#include <gtest/gtest.h>

#include "CairoOutputDev.h"

#include <array>



class CairoImageOutputDevTest_1744 : public ::testing::Test {

protected:

    CairoImageOutputDev* dev;



    void SetUp() override {

        dev = new CairoImageOutputDev();

    }



    void TearDown() override {

        delete dev;

    }

};



TEST_F(CairoImageOutputDevTest_1744, NeedNonText_ReturnsTrue_1744) {

    EXPECT_TRUE(dev->needNonText());

}



TEST_F(CairoImageOutputDevTest_1744, GetNumImages_ReturnsZeroInitially_1744) {

    EXPECT_EQ(0, dev->getNumImages());

}



TEST_F(CairoImageOutputDevTest_1744, UpsideDown_ReturnsFalseByDefault_1744) {

    EXPECT_FALSE(dev->upsideDown());

}



TEST_F(CairoImageOutputDevTest_1744, UseDrawChar_ReturnsTrueByDefault_1744) {

    EXPECT_TRUE(dev->useDrawChar());

}



TEST_F(CairoImageOutputDevTest_1744, UseTilingPatternFill_ReturnsFalseByDefault_1744) {

    EXPECT_FALSE(dev->useTilingPatternFill());

}



TEST_F(CairoImageOutputDevTest_1744, UseShadedFills_ReturnsFalseForAllTypes_1744) {

    for (int type = 0; type < 5; ++type) { // Assuming there are less than 5 types

        EXPECT_FALSE(dev->useShadedFills(type));

    }

}



TEST_F(CairoImageOutputDevTest_1744, UseFillColorStop_ReturnsFalseByDefault_1744) {

    EXPECT_FALSE(dev->useFillColorStop());

}



TEST_F(CairoImageOutputDevTest_1744, InterpretType3Chars_ReturnsTrueByDefault_1744) {

    EXPECT_TRUE(dev->interpretType3Chars());

}
