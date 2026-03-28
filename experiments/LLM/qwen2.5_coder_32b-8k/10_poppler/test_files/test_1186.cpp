#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordTest_1186 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or state before each test

        textWord = new TextWord(nullptr, 0, 12.0);

    }



    void TearDown() override {

        // Clean up after each test

        delete textWord;

    }



    TextWord* textWord;

};



TEST_F(TextWordTest_1186, GetBBox_ReturnsValidRectangle_1186) {

    PDFRectangle bbox = textWord->getBBox();

    EXPECT_LE(bbox.xMin, bbox.xMax);

    EXPECT_LE(bbox.yMin, bbox.yMax);

}



TEST_F(TextWordTest_1186, GetFontInfo_ReturnsNonNullPointerForValidIndex_1186) {

    const TextFontInfo* fontInfo = textWord->getFontInfo(0);

    EXPECT_NE(fontInfo, nullptr);

}



TEST_F(TextWordTest_1186, GetNext_ReturnsNullptrInitially_1186) {

    const TextWord* nextWord = textWord->getNext();

    EXPECT_EQ(nextWord, nullptr);

}



TEST_F(TextWordTest_1186, GetLength_ReturnsZeroInitially_1186) {

    int length = textWord->getLength();

    EXPECT_EQ(length, 0);

}



TEST_F(TextWordTest_1186, GetChar_ReturnsNullptrForInvalidIndex_1186) {

    const Unicode* character = textWord->getChar(-1);

    EXPECT_EQ(character, nullptr);



    character = textWord->getChar(1);

    EXPECT_EQ(character, nullptr);

}



TEST_F(TextWordTest_1186, GetFontName_ReturnsNullptrForInvalidIndex_1186) {

    const GooString* fontName = textWord->getFontName(-1);

    EXPECT_EQ(fontName, nullptr);



    fontName = textWord->getFontName(1);

    EXPECT_EQ(fontName, nullptr);

}



TEST_F(TextWordTest_1186, GetColor_ReturnsValidColors_1186) {

    double r, g, b;

    textWord->getColor(&r, &g, &b);

    EXPECT_GE(r, 0.0);

    EXPECT_LE(r, 1.0);

    EXPECT_GE(g, 0.0);

    EXPECT_LE(g, 1.0);

    EXPECT_GE(b, 0.0);

    EXPECT_LE(b, 1.0);

}



TEST_F(TextWordTest_1186, GetBBox_ReturnsValidCoordinates_1186) {

    double xMin, yMin, xMax, yMax;

    textWord->getBBox(&xMin, &yMin, &xMax, &yMax);

    EXPECT_LE(xMin, xMax);

    EXPECT_LE(yMin, yMax);

}



TEST_F(TextWordTest_1186, GetFontSize_ReturnsPositiveValue_1186) {

    double fontSize = textWord->getFontSize();

    EXPECT_GT(fontSize, 0.0);

}



TEST_F(TextWordTest_1186, GetRotation_ReturnsValidRotation_1186) {

    int rotation = textWord->getRotation();

    EXPECT_GE(rotation, 0);

    EXPECT_LE(rotation, 359);

}



TEST_F(TextWordTest_1186, GetCharPos_ReturnsZeroInitially_1186) {

    int charPos = textWord->getCharPos();

    EXPECT_EQ(charPos, 0);

}



TEST_F(TextWordTest_1186, GetCharLen_ReturnsZeroInitially_1186) {

    int charLen = textWord->getCharLen();

    EXPECT_EQ(charLen, 0);

}



TEST_F(TextWordTest_1186, HasSpaceAfter_ReturnsFalseInitially_1186) {

    bool spaceAfter = textWord->hasSpaceAfter();

    EXPECT_FALSE(spaceAfter);

}



TEST_F(TextWordTest_1186, IsUnderlined_ReturnsFalseInitially_1186) {

    bool underlined = textWord->isUnderlined();

    EXPECT_FALSE(underlined);

}



TEST_F(TextWordTest_1186, GetLink_ReturnsNullptrInitially_1186) {

    const AnnotLink* link = textWord->getLink();

    EXPECT_EQ(link, nullptr);

}



TEST_F(TextWordTest_1186, GetEdge_ReturnsZeroForInvalidIndex_1186) {

    double edge = textWord->getEdge(-1);

    EXPECT_EQ(edge, 0.0);



    edge = textWord->getEdge(1);

    EXPECT_EQ(edge, 0.0);

}



TEST_F(TextWordTest_1186, GetBaseline_ReturnsZeroInitially_1186) {

    double baseline = textWord->getBaseline();

    EXPECT_EQ(baseline, 0.0);

}



TEST_F(TextWordTest_1186, NextWord_ReturnsNullptrInitially_1186) {

    const TextWord* next = textWord->nextWord();

    EXPECT_EQ(next, nullptr);

}



TEST_F(TextWordTest_1186, Len_ReturnsZeroInitially_1186) {

    auto length = textWord->len();

    EXPECT_EQ(length, 0);

}
