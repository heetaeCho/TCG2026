#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordTest : public ::testing::Test {

protected:

    GfxState gfxState;

    TextWord textWord;



    TextWordTest() : textWord(&gfxState, 0, 12.0) {}

};



TEST_F(TextWordTest_1192, IsUnderlined_DefaultValue_1192) {

    EXPECT_FALSE(textWord.isUnderlined());

}



// Assuming there is a way to set the underline state, if not, this test would need adjustment

// TEST_F(TextWordTest_1192, IsUnderlined_SetToTrue_ReturnsTrue_1192) {

//     // Assume there's a method to set underline state, e.g., textWord.setUnderlined(true);

//     EXPECT_TRUE(textWord.isUnderlined());

// }



TEST_F(TextWordTest_1192, GetLength_DefaultValue_1192) {

    EXPECT_EQ(0, textWord.getLength());

}



TEST_F(TextWordTest_1192, GetFontInfo_OutOfBounds_ReturnsNull_1192) {

    EXPECT_EQ(nullptr, textWord.getFontInfo(-1));

    EXPECT_EQ(nullptr, textWord.getFontInfo(0)); // Assuming no font info is added initially

}



TEST_F(TextWordTest_1192, GetChar_OutOfBounds_ReturnsNull_1192) {

    EXPECT_EQ(nullptr, textWord.getChar(-1));

    EXPECT_EQ(nullptr, textWord.getChar(0)); // Assuming no characters are added initially

}



TEST_F(TextWordTest_1192, GetFontName_OutOfBounds_ReturnsNull_1192) {

    EXPECT_EQ(nullptr, textWord.getFontName(-1));

    EXPECT_EQ(nullptr, textWord.getFontName(0)); // Assuming no font names are set initially

}



TEST_F(TextWordTest_1192, GetColor_DefaultValues_ReturnsZero_1192) {

    double r, g, b;

    textWord.getColor(&r, &g, &b);

    EXPECT_DOUBLE_EQ(0.0, r);

    EXPECT_DOUBLE_EQ(0.0, g);

    EXPECT_DOUBLE_EQ(0.0, b);

}



TEST_F(TextWordTest_1192, GetBBox_DefaultValues_ReturnsZero_1192) {

    double xMin, yMin, xMax, yMax;

    textWord.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(0.0, xMin);

    EXPECT_DOUBLE_EQ(0.0, yMin);

    EXPECT_DOUBLE_EQ(0.0, xMax);

    EXPECT_DOUBLE_EQ(0.0, yMax);

}



TEST_F(TextWordTest_1192, GetFontSize_DefaultValue_ReturnsInitialFontSize_1192) {

    EXPECT_DOUBLE_EQ(12.0, textWord.getFontSize());

}



TEST_F(TextWordTest_1192, GetRotation_DefaultValue_ReturnsInitialRotation_1192) {

    EXPECT_EQ(0, textWord.getRotation());

}



TEST_F(TextWordTest_1192, GetCharPos_DefaultValue_ReturnsZero_1192) {

    EXPECT_EQ(0, textWord.getCharPos());

}



TEST_F(TextWordTest_1192, GetCharLen_DefaultValue_ReturnsZero_1192) {

    EXPECT_EQ(0, textWord.getCharLen());

}



TEST_F(TextWordTest_1192, GetSpaceAfter_DefaultValue_ReturnsFalse_1192) {

    EXPECT_FALSE(textWord.getSpaceAfter());

}



TEST_F(TextWordTest_1192, HasSpaceAfter_DefaultValue_ReturnsFalse_1192) {

    EXPECT_FALSE(textWord.hasSpaceAfter());

}



TEST_F(TextWordTest_1192, GetLink_DefaultValue_ReturnsNull_1192) {

    EXPECT_EQ(nullptr, textWord.getLink());

}



TEST_F(TextWordTest_1192, GetEdge_OutOfBounds_ReturnsZero_1192) {

    EXPECT_DOUBLE_EQ(0.0, textWord.getEdge(-1));

    EXPECT_DOUBLE_EQ(0.0, textWord.getEdge(0)); // Assuming no edges are set initially

}



TEST_F(TextWordTest_1192, GetBaseline_DefaultValue_ReturnsZero_1192) {

    EXPECT_DOUBLE_EQ(0.0, textWord.getBaseline());

}
