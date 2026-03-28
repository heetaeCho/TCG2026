#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/CairoOutputDev.h"



class CairoImageOutputDevTest : public ::testing::Test {

protected:

    CairoImageOutputDev* output_dev;



    void SetUp() override {

        output_dev = new CairoImageOutputDev();

    }



    void TearDown() override {

        delete output_dev;

    }

};



TEST_F(CairoImageOutputDevTest_1740, UseTilingPatternFill_ReturnsTrue_1740) {

    EXPECT_TRUE(output_dev->useTilingPatternFill());

}



TEST_F(CairoImageOutputDevTest_1740, GetNumImages_InitialValueIsZero_1740) {

    EXPECT_EQ(0, output_dev->getNumImages());

}



TEST_F(CairoImageOutputDevTest_1740, GetImage_OutOfBounds_ReturnsNull_1740) {

    EXPECT_EQ(nullptr, output_dev->getImage(-1));

    EXPECT_EQ(nullptr, output_dev->getImage(0));

}



// Assuming there's a way to add images to test getImage, otherwise this is skipped.

// TEST_F(CairoImageOutputDevTest_1740, GetImage_ValidIndex_ReturnsNonNull_1740) {

//     // Add an image to the output device

//     // EXPECT_NE(nullptr, output_dev->getImage(0));

// }



TEST_F(CairoImageOutputDevTest_1740, UseDrawChar_DefaultValueIsFalse_1740) {

    EXPECT_FALSE(output_dev->useDrawChar());

}



TEST_F(CairoImageOutputDevTest_1740, UseShadedFills_DefaultValueIsFalse_1740) {

    EXPECT_FALSE(output_dev->useShadedFills(0));

}



TEST_F(CairoImageOutputDevTest_1740, UseFillColorStop_DefaultValueIsFalse_1740) {

    EXPECT_FALSE(output_dev->useFillColorStop());

}



TEST_F(CairoImageOutputDevTest_1740, InterpretType3Chars_DefaultValueIsTrue_1740) {

    EXPECT_TRUE(output_dev->interpretType3Chars());

}



TEST_F(CairoImageOutputDevTest_1740, NeedNonText_DefaultValueIsFalse_1740) {

    EXPECT_FALSE(output_dev->needNonText());

}
