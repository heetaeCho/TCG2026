#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TextOutputDev.h"



class TextWordTest : public ::testing::Test {

protected:

    const GfxState* state = nullptr;

    int rotA = 0;

    double fontSize = 12.0;



    std::unique_ptr<TextWord> textWord;



    void SetUp() override {

        textWord = std::make_unique<TextWord>(state, rotA, fontSize);

    }

};



TEST_F(TextWordTest_1187, GetFontSize_ReturnsCorrectValue_1187) {

    EXPECT_EQ(textWord->getFontSize(), fontSize);

}



TEST_F(TextWordTest_1187, GetRotation_ReturnsInitialValue_1187) {

    EXPECT_EQ(textWord->getRotation(), rotA);

}



TEST_F(TextWordTest_1187, GetLength_DefaultValueIsZero_1187) {

    EXPECT_EQ(textWord->getLength(), 0);

}



TEST_F(TextWordTest_1187, HasSpaceAfter_DefaultValueIsFalse_1187) {

    EXPECT_FALSE(textWord->hasSpaceAfter());

}



TEST_F(TextWordTest_1187, IsUnderlined_DefaultValueIsFalse_1187) {

    EXPECT_FALSE(textWord->isUnderlined());

}



TEST_F(TextWordTest_1187, GetLink_DefaultValueIsNullptr_1187) {

    EXPECT_EQ(textWord->getLink(), nullptr);

}



TEST_F(TextWordTest_1187, GetEdge_ReturnsZeroForDefaultIndex_1187) {

    EXPECT_EQ(textWord->getEdge(0), 0.0);

}



TEST_F(TextWordTest_1187, GetBaseline_ReturnsInitialValue_1187) {

    EXPECT_EQ(textWord->getBaseline(), textWord->base);

}
