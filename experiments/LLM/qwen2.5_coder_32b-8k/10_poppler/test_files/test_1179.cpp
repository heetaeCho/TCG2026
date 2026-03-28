#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TextOutputDev.h"



using namespace testing;



class TextWordTest_1179 : public ::testing::Test {

protected:

    GfxState state;

    double fontSize = 12.0;

    int rotA = 0;



    std::unique_ptr<TextWord> textWord;



    void SetUp() override {

        textWord = std::make_unique<TextWord>(&state, rotA, fontSize);

    }

};



TEST_F(TextWordTest_1179, GetFontInfo_ReturnsValidPointerForExistingIndex_1179) {

    // Arrange

    TextFontInfo fontInfo;

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'a';

    Unicode u = L'a';

    Matrix textMat;



    textWord->addChar(&fontInfo, x, y, dx, dy, charPosA, charLen, c, u, textMat);



    // Act

    const TextFontInfo* result = textWord->getFontInfo(0);



    // Assert

    EXPECT_EQ(result, &fontInfo);

}



TEST_F(TextWordTest_1179, GetFontInfo_ReturnsNullForNonExistentIndex_1179) {

    // Arrange

    // No characters added



    // Act

    const TextFontInfo* result = textWord->getFontInfo(0);



    // Assert

    EXPECT_EQ(result, nullptr);

}



TEST_F(TextWordTest_1179, GetNext_ReturnsNullWhenNoNextWord_1179) {

    // Arrange

    // No next word set



    // Act

    const TextWord* result = textWord->getNext();



    // Assert

    EXPECT_EQ(result, nullptr);

}



TEST_F(TextWordTest_1179, GetLength_ReturnsZeroWhenNoCharsAdded_1179) {

    // Arrange

    // No characters added



    // Act

    int length = textWord->getLength();



    // Assert

    EXPECT_EQ(length, 0);

}



TEST_F(TextWordTest_1179, GetChar_ReturnsValidUnicodeForExistingIndex_1179) {

    // Arrange

    TextFontInfo fontInfo;

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'a';

    Unicode u = L'a';

    Matrix textMat;



    textWord->addChar(&fontInfo, x, y, dx, dy, charPosA, charLen, c, u, textMat);



    // Act

    const Unicode* result = textWord->getChar(0);



    // Assert

    EXPECT_EQ(*result, L'a');

}



TEST_F(TextWordTest_1179, GetChar_ReturnsNullForNonExistentIndex_1179) {

    // Arrange

    // No characters added



    // Act

    const Unicode* result = textWord->getChar(0);



    // Assert

    EXPECT_EQ(result, nullptr);

}



TEST_F(TextWordTest_1179, GetFontName_ReturnsNullWhenNoCharsAdded_1179) {

    // Arrange

    // No characters added



    // Act

    const GooString* result = textWord->getFontName(0);



    // Assert

    EXPECT_EQ(result, nullptr);

}



TEST_F(TextWordTest_1179, GetColor_ReturnsDefaultValuesWhenNoColorSet_1179) {

    // Arrange

    double r, g, b;



    // Act

    textWord->getColor(&r, &g, &b);



    // Assert

    EXPECT_EQ(r, 0.0);

    EXPECT_EQ(g, 0.0);

    EXPECT_EQ(b, 0.0);

}



TEST_F(TextWordTest_1179, GetBBox_ReturnsDefaultValuesWhenNoCharsAdded_1179) {

    // Arrange

    double xMinA, yMinA, xMaxA, yMaxA;



    // Act

    textWord->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);



    // Assert

    EXPECT_EQ(xMinA, 0.0);

    EXPECT_EQ(yMinA, 0.0);

    EXPECT_EQ(xMaxA, 0.0);

    EXPECT_EQ(yMaxA, 0.0);

}



TEST_F(TextWordTest_1179, GetFontSize_ReturnsInitialFontSize_1179) {

    // Arrange

    // No specific setup needed



    // Act

    double fontSize = textWord->getFontSize();



    // Assert

    EXPECT_EQ(fontSize, this->fontSize);

}



TEST_F(TextWordTest_1179, GetRotation_ReturnsInitialRotation_1179) {

    // Arrange

    // No specific setup needed



    // Act

    int rotation = textWord->getRotation();



    // Assert

    EXPECT_EQ(rotation, rotA);

}
