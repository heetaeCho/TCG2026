#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordTest : public ::testing::Test {

protected:

    GfxState gfxState;

    TextFontInfo fontInfo;

    Matrix textMat;



    void SetUp() override {

        // Initialize any necessary objects or state before each test

    }

};



TEST_F(TextWordTest_1189, GetCharPos_ReturnsCorrectPosition_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_EQ(word.getCharPos(), 42);

}



TEST_F(TextWordTest_1189, GetCharPos_ReturnsZeroForEmptyChars_1189) {

    TextWord word(&gfxState, 0, 12.0);

    EXPECT_EQ(word.getCharPos(), 0);

}



TEST_F(TextWordTest_1189, AddChar_IncreasesLength_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_EQ(word.getLength(), 1);

}



TEST_F(TextWordTest_1189, AddCombining_ReturnsTrueForSuccessfulAddition_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_TRUE(word.addCombining(&fontInfo, 12.0, 100.0, 200.0, 5.0, 3.0, 42, 1, 'B', U'B', textMat));

}



TEST_F(TextWordTest_1189, Merge_CombinesTwoWords_1189) {

    TextWord word1(&gfxState, 0, 12.0);

    word1.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);



    TextWord word2(&gfxState, 0, 12.0);

    word2.addChar(&fontInfo, 105.0, 200.0, 5.0, 3.0, 43, 1, 'B', U'B', textMat);



    word1.merge(&word2);

    EXPECT_EQ(word1.getLength(), 2);

}



TEST_F(TextWordTest_1189, GetNext_ReturnsNextWordPointer_1189) {

    TextWord word1(&gfxState, 0, 12.0);

    TextWord word2(&gfxState, 0, 12.0);



    word1.merge(&word2);

    EXPECT_EQ(word1.getNext(), &word2);

}



TEST_F(TextWordTest_1189, GetFontInfo_ReturnsCorrectFontInfo_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_EQ(word.getFontInfo(0), &fontInfo);

}



TEST_F(TextWordTest_1189, GetChar_ReturnsCorrectUnicode_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_EQ(*word.getChar(0), U'A');

}



TEST_F(TextWordTest_1189, GetFontName_ReturnsCorrectFontName_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_EQ(word.getFontName(0)->c_str(), fontInfo.fontName->c_str());

}



TEST_F(TextWordTest_1189, GetColor_ReturnsCorrectRGBValues_1189) {

    TextWord word(&gfxState, 0, 12.0);

    double r, g, b;

    word.getColor(&r, &g, &b);

    EXPECT_DOUBLE_EQ(r, 0.0);

    EXPECT_DOUBLE_EQ(g, 0.0);

    EXPECT_DOUBLE_EQ(b, 0.0);

}



TEST_F(TextWordTest_1189, GetBBox_ReturnsCorrectBoundingBox_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    double xMin, yMin, xMax, yMax;

    word.getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_DOUBLE_EQ(xMin, 95.0);

    EXPECT_DOUBLE_EQ(yMin, 197.0);

    EXPECT_DOUBLE_EQ(xMax, 105.0);

    EXPECT_DOUBLE_EQ(yMax, 203.0);

}



TEST_F(TextWordTest_1189, GetFontSize_ReturnsCorrectFontSize_1189) {

    TextWord word(&gfxState, 0, 12.0);

    EXPECT_DOUBLE_EQ(word.getFontSize(), 12.0);

}



TEST_F(TextWordTest_1189, GetRotation_ReturnsCorrectRotation_1189) {

    TextWord word(&gfxState, 45, 12.0);

    EXPECT_EQ(word.getRotation(), 45);

}



TEST_F(TextWordTest_1189, GetCharLen_ReturnsCorrectLength_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 2, 'A', U'A', textMat);

    EXPECT_EQ(word.getCharLen(), 2);

}



TEST_F(TextWordTest_1189, GetSpaceAfter_ReturnsCorrectSpaceFlag_1189) {

    TextWord word(&gfxState, 0, 12.0);

    // Assuming spaceAfter is set to true in some way (not shown in interface)

    EXPECT_EQ(word.getSpaceAfter(), false); // Since we can't set it directly, assume default

}



TEST_F(TextWordTest_1189, IsUnderlined_ReturnsCorrectUnderlineFlag_1189) {

    TextWord word(&gfxState, 0, 12.0);

    // Assuming underline is set to true in some way (not shown in interface)

    EXPECT_EQ(word.isUnderlined(), false); // Since we can't set it directly, assume default

}



TEST_F(TextWordTest_1189, GetLink_ReturnsCorrectAnnotLink_1189) {

    TextWord word(&gfxState, 0, 12.0);

    EXPECT_EQ(word.getLink(), nullptr); // Assuming no link is set initially

}



TEST_F(TextWordTest_1189, GetEdge_ReturnsCorrectEdgeValue_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_DOUBLE_EQ(word.getEdge(0), 95.0); // Assuming edge calculation is based on x position

}



TEST_F(TextWordTest_1189, GetBaseline_ReturnsCorrectBaselineValue_1189) {

    TextWord word(&gfxState, 0, 12.0);

    EXPECT_DOUBLE_EQ(word.getBaseline(), 0.0); // Assuming baseline is set to 0 initially

}



TEST_F(TextWordTest_1189, HasSpaceAfter_ReturnsCorrectSpaceFlag_1189) {

    TextWord word(&gfxState, 0, 12.0);

    // Assuming spaceAfter is set to true in some way (not shown in interface)

    EXPECT_EQ(word.hasSpaceAfter(), false); // Since we can't set it directly, assume default

}



TEST_F(TextWordTest_1189, NextWord_ReturnsNextWordPointer_1189) {

    TextWord word1(&gfxState, 0, 12.0);

    TextWord word2(&gfxState, 0, 12.0);



    word1.merge(&word2);

    EXPECT_EQ(word1.nextWord(), &word2);

}



TEST_F(TextWordTest_1189, Len_ReturnsCorrectLength_1189) {

    TextWord word(&gfxState, 0, 12.0);

    word.addChar(&fontInfo, 100.0, 200.0, 5.0, 3.0, 42, 1, 'A', U'A', textMat);

    EXPECT_EQ(word.len(), 1);

}
