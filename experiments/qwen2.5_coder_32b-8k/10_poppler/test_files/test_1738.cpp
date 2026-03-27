#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/CairoOutputDev.h"



using namespace testing;



class CairoImageOutputDevTest : public Test {

protected:

    CairoImageOutputDev* outputDev;



    void SetUp() override {

        outputDev = new CairoImageOutputDev();

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(CairoImageOutputDevTest_1738, UpsideDown_ReturnsTrue_1738) {

    EXPECT_TRUE(outputDev->upsideDown());

}



TEST_F(CairoImageOutputDevTest_1738, UseDrawChar_DefaultBehavior_1738) {

    EXPECT_FALSE(outputDev->useDrawChar());

}



TEST_F(CairoImageOutputDevTest_1738, UseTilingPatternFill_DefaultBehavior_1738) {

    EXPECT_FALSE(outputDev->useTilingPatternFill());

}



TEST_F(CairoImageOutputDevTest_1738, UseShadedFills_DefaultBehavior_1738) {

    EXPECT_FALSE(outputDev->useShadedFills(0));

}



TEST_F(CairoImageOutputDevTest_1738, UseFillColorStop_DefaultBehavior_1738) {

    EXPECT_FALSE(outputDev->useFillColorStop());

}



TEST_F(CairoImageOutputDevTest_1738, InterpretType3Chars_DefaultBehavior_1738) {

    EXPECT_TRUE(outputDev->interpretType3Chars());

}



TEST_F(CairoImageOutputDevTest_1738, NeedNonText_DefaultBehavior_1738) {

    EXPECT_FALSE(outputDev->needNonText());

}



TEST_F(CairoImageOutputDevTest_1738, GetNumImages_InitiallyZero_1738) {

    EXPECT_EQ(0, outputDev->getNumImages());

}
