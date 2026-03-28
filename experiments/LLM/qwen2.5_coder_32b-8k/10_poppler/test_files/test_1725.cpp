#include <gtest/gtest.h>

#include "CairoOutputDev.h"



class CairoOutputDevTest : public ::testing::Test {

protected:

    CairoOutputDev* cairoOutputDev;



    void SetUp() override {

        cairoOutputDev = new CairoOutputDev();

    }



    void TearDown() override {

        delete cairoOutputDev;

    }

};



TEST_F(CairoOutputDevTest_1725, UseShadedFills_NormalOperation_1725) {

    EXPECT_TRUE(cairoOutputDev->useShadedFills(0));

    EXPECT_TRUE(cairoOutputDev->useShadedFills(7));

}



TEST_F(CairoOutputDevTest_1725, UseShadedFills_BoundaryConditions_1725) {

    EXPECT_TRUE(cairoOutputDev->useShadedFills(-1));

    EXPECT_FALSE(cairoOutputDev->useShadedFills(8));

}



// No observable exceptional or error cases for useShadedFills based on the provided interface.



TEST_F(CairoOutputDevTest_1725, UseDrawChar_NormalOperation_1725) {

    EXPECT_TRUE(cairoOutputDev->useDrawChar());

}



TEST_F(CairoOutputDevTest_1725, UseTilingPatternFill_NormalOperation_1725) {

    EXPECT_FALSE(cairoOutputDev->useTilingPatternFill());

}



TEST_F(CairoOutputDevTest_1725, UseFillColorStop_NormalOperation_1725) {

    EXPECT_TRUE(cairoOutputDev->useFillColorStop());

}



TEST_F(CairoOutputDevTest_1725, InterpretType3Chars_NormalOperation_1725) {

    EXPECT_TRUE(cairoOutputDev->interpretType3Chars());

}



TEST_F(CairoOutputDevTest_1725, NeedClipToCropBox_NormalOperation_1725) {

    EXPECT_FALSE(cairoOutputDev->needClipToCropBox());

}



TEST_F(CairoOutputDevTest_1725, SupportJPXtransparency_NormalOperation_1725) {

    EXPECT_TRUE(cairoOutputDev->supportJPXtransparency());

}
