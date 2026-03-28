#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TextOutputDev.h"



using namespace ::testing;



class TextWordTest : public ::testing::Test {

protected:

    GfxState* state;

    TextFontInfo* fontA;

    Matrix textMatA;

    PDFRectangle selection;

    TextSelectionVisitor visitor;



    void SetUp() override {

        state = new GfxState();

        fontA = new TextFontInfo();

    }



    void TearDown() override {

        delete state;

        delete fontA;

    }

};



TEST_F(TextWordTest_1182, ConstructorInitializesMembers_1182) {

    TextWord textWord(state, 0, 12.0);

}



TEST_F(TextWordTest_1182, AddCharIncreasesLength_1182) {

    TextWord textWord(state, 0, 12.0);

    int initialLength = textWord.getLength();

    textWord.addChar(fontA, 0, 0, 1, 1, 0, 1, 'a', U'a', textMatA);

    EXPECT_EQ(textWord.getLength(), initialLength + 1);

}



TEST_F(TextWordTest_1182, GetCharReturnsCorrectUnicode_1182) {

    TextWord textWord(state, 0, 12.0);

    textWord.addChar(fontA, 0, 0, 1, 1, 0, 1, 'a', U'a', textMatA);

    EXPECT_EQ(*textWord.getChar(0), U'a');

}



TEST_F(TextWordTest_1182, GetLengthReturnsCorrectValueAfterAddingChars_1182) {

    TextWord textWord(state, 0, 12.0);

    textWord.addChar(fontA, 0, 0, 1, 1, 0, 1, 'a', U'a', textMatA);

    textWord.addChar(fontA, 1, 1, 2, 2, 1, 1, 'b', U'b', textMatA);

    EXPECT_EQ(textWord.getLength(), 2);

}



TEST_F(TextWordTest_1182, GetFontInfoReturnsCorrectPointer_1182) {

    TextWord textWord(state, 0, 12.0);

    textWord.addChar(fontA, 0, 0, 1, 1, 0, 1, 'a', U'a', textMatA);

    EXPECT_EQ(textWord.getFontInfo(0), fontA);

}



TEST_F(TextWordTest_1182, GetFontNameReturnsValidPointer_1182) {

    TextWord textWord(state, 0, 12.0);

    textWord.addChar(fontA, 0, 0, 1, 1, 0, 1, 'a', U'a', textMatA);

    EXPECT_NE(textWord.getFontName(0), nullptr);

}



TEST_F(TextWordTest_1182, GetColorSetsRGBValues_1182) {

    TextWord textWord(state, 0, 12.0);

    double r, g, b;

    textWord.getColor(&r, &g, &b);

    EXPECT_TRUE(r >= 0 && r <= 1);

    EXPECT_TRUE(g >= 0 && g <= 1);

    EXPECT_TRUE(b >= 0 && b <= 1);

}



TEST_F(TextWordTest_1182, GetBBoxSetsCoordinates_1182) {

    TextWord textWord(state, 0, 12.0);

    double xMinA, yMinA, xMaxA, yMaxA;

    textWord.getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_TRUE(xMinA <= xMaxA);

    EXPECT_TRUE(yMinA <= yMaxA);

}



TEST_F(TextWordTest_1182, GetRotationReturnsInitialValue_1182) {

    TextWord textWord(state, 45, 12.0);

    EXPECT_EQ(textWord.getRotation(), 45);

}



TEST_F(TextWordTest_1182, GetCharPosReturnsCorrectValueAfterAddingChars_1182) {

    TextWord textWord(state, 0, 12.0);

    textWord.addChar(fontA, 0, 0, 1, 1, 5, 1, 'a', U'a', textMatA);

    EXPECT_EQ(textWord.getCharPos(), 5);

}



TEST_F(TextWordTest_1182, GetEdgeReturnsCorrectValueAfterAddingChars_1182) {

    TextWord textWord(state, 0, 12.0);

    textWord.addChar(fontA, 0, 0, 1, 1, 5, 1, 'a', U'a', textMatA);

    EXPECT_EQ(textWord.getEdge(0), 1);

}



TEST_F(TextWordTest_1182, GetBaselineReturnsCorrectValue_1182) {

    TextWord textWord(state, 0, 12.0);

    double baseline = textWord.getBaseline();

    EXPECT_TRUE(baseline >= 0); // Assuming baseline is non-negative

}



TEST_F(TextWordTest_1182, HasSpaceAfterReturnsFalseByDefault_1182) {

    TextWord textWord(state, 0, 12.0);

    EXPECT_FALSE(textWord.hasSpaceAfter());

}



TEST_F(TextWordTest_1182, IsUnderlinedReturnsFalseByDefault_1182) {

    TextWord textWord(state, 0, 12.0);

    EXPECT_FALSE(textWord.isUnderlined());

}



TEST_F(TextWordTest_1182, GetLinkReturnsNullptrByDefault_1182) {

    TextWord textWord(state, 0, 12.0);

    EXPECT_EQ(textWord.getLink(), nullptr);

}
