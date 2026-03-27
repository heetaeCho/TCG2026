#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordTest : public ::testing::Test {

protected:

    GfxState* state;

    TextFontInfo* fontA;



    void SetUp() override {

        state = new GfxState();

        fontA = new TextFontInfo();

    }



    void TearDown() override {

        delete state;

        delete fontA;

    }

};



TEST_F(TextWordTest_1195, GetBaseline_ReturnsCorrectValue_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_DOUBLE_EQ(0.0, textWord.getBaseline());

}



TEST_F(TextWordTest_1195, GetRotation_ReturnsCorrectValue_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 45;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_EQ(45, textWord.getRotation());

}



TEST_F(TextWordTest_1195, GetLength_ReturnsZeroForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_EQ(0, textWord.getLength());

}



TEST_F(TextWordTest_1195, AddChar_IncreasesLengthByOne_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'a';

    Unicode u = 'a';

    Matrix textMatA;



    // Act

    textWord.addChar(fontA, x, y, dx, dy, charPosA, charLen, c, u, textMatA);



    // Assert

    EXPECT_EQ(1, textWord.getLength());

}



TEST_F(TextWordTest_1195, AddCombining_IncreasesLengthByOne_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'a';

    Unicode u = 'a';

    Matrix textMatA;



    // Act

    bool result = textWord.addCombining(fontA, fontSize, x, y, dx, dy, charPosA, charLen, c, u, textMatA);



    // Assert

    if (result) {

        EXPECT_EQ(1, textWord.getLength());

    } else {

        EXPECT_EQ(0, textWord.getLength()); // Depending on the implementation of addCombining

    }

}



TEST_F(TextWordTest_1195, GetChar_ReturnsCorrectUnicode_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'a';

    Unicode u = 'a';

    Matrix textMatA;

    textWord.addChar(fontA, x, y, dx, dy, charPosA, charLen, c, u, textMatA);



    // Act

    const Unicode* result = textWord.getChar(0);



    // Assert

    EXPECT_EQ(u, *result);

}



TEST_F(TextWordTest_1195, GetChar_OutOfBounds_ReturnsNullptr_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act

    const Unicode* result = textWord.getChar(0);



    // Assert

    EXPECT_EQ(nullptr, result);

}



TEST_F(TextWordTest_1195, GetFontName_ReturnsNullptrForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act

    const GooString* result = textWord.getFontName(0);



    // Assert

    EXPECT_EQ(nullptr, result);

}



TEST_F(TextWordTest_1195, GetFontInfo_ReturnsNullptrForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act

    const TextFontInfo* result = textWord.getFontInfo(0);



    // Assert

    EXPECT_EQ(nullptr, result);

}



TEST_F(TextWordTest_1195, GetColor_ReturnsDefaultValuesForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);

    double r, g, b;



    // Act

    textWord.getColor(&r, &g, &b);



    // Assert

    EXPECT_DOUBLE_EQ(0.0, r);

    EXPECT_DOUBLE_EQ(0.0, g);

    EXPECT_DOUBLE_EQ(0.0, b);

}



TEST_F(TextWordTest_1195, GetBBox_ReturnsDefaultValuesForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);

    double xMinA, yMinA, xMaxA, yMaxA;



    // Act

    textWord.getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);



    // Assert

    EXPECT_DOUBLE_EQ(0.0, xMinA);

    EXPECT_DOUBLE_EQ(0.0, yMinA);

    EXPECT_DOUBLE_EQ(0.0, xMaxA);

    EXPECT_DOUBLE_EQ(0.0, yMaxA);

}



TEST_F(TextWordTest_1195, GetCharBBox_ReturnsDefaultValuesForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);

    double xMinA, yMinA, xMaxA, yMaxA;



    // Act

    textWord.getCharBBox(0, &xMinA, &yMinA, &xMaxA, &yMaxA);



    // Assert

    EXPECT_DOUBLE_EQ(0.0, xMinA);

    EXPECT_DOUBLE_EQ(0.0, yMinA);

    EXPECT_DOUBLE_EQ(0.0, xMaxA);

    EXPECT_DOUBLE_EQ(0.0, yMaxA);

}



TEST_F(TextWordTest_1195, HasSpaceAfter_ReturnsFalseForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_FALSE(textWord.hasSpaceAfter());

}



TEST_F(TextWordTest_1195, IsUnderlined_ReturnsFalseForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_FALSE(textWord.isUnderlined());

}



TEST_F(TextWordTest_1195, GetLink_ReturnsNullptrForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act

    const AnnotLink* result = textWord.getLink();



    // Assert

    EXPECT_EQ(nullptr, result);

}



TEST_F(TextWordTest_1195, GetEdge_ReturnsZeroForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_DOUBLE_EQ(0.0, textWord.getEdge(0));

}



TEST_F(TextWordTest_1195, GetNext_ReturnsNullptrForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act

    const TextWord* result = textWord.getNext();



    // Assert

    EXPECT_EQ(nullptr, result);

}



TEST_F(TextWordTest_1195, GetNextWord_ReturnsNullptrForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act

    const TextWord* result = textWord.nextWord();



    // Assert

    EXPECT_EQ(nullptr, result);

}



TEST_F(TextWordTest_1195, GetFontSize_ReturnsConstructorValue_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_DOUBLE_EQ(fontSize, textWord.getFontSize());

}



TEST_F(TextWordTest_1195, GetCharPos_ReturnsZeroForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_EQ(0, textWord.getCharPos());

}



TEST_F(TextWordTest_1195, GetCharLen_ReturnsZeroForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_EQ(0, textWord.getCharLen());

}



TEST_F(TextWordTest_1195, GetSpaceAfter_ReturnsFalseForNewInstance_1195) {

    // Arrange

    double fontSize = 12.0;

    int rotA = 0;

    TextWord textWord(state, rotA, fontSize);



    // Act & Assert

    EXPECT_FALSE(textWord.getSpaceAfter());

}
