#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class TextWordTest_1197 : public ::testing::Test {

protected:

    TextWord *word;



    virtual void SetUp() {

        // Assuming GfxState, TextFontInfo, and other necessary objects are mockable or default-constructible

        word = new TextWord(nullptr, 0, 12.0); // Default constructor usage for testing purposes

    }



    virtual void TearDown() {

        delete word;

    }

};



TEST_F(TextWordTest_1197, GetNext_ReturnsNullptrByDefault_1197) {

    EXPECT_EQ(word->nextWord(), nullptr);

}



TEST_F(TextWordTest_1197, GetLength_ReturnsZeroForEmptyWord_1197) {

    EXPECT_EQ(word->getLength(), 0);

}



TEST_F(TextWordTest_1197, HasSpaceAfter_ReturnsFalseByDefault_1197) {

    EXPECT_FALSE(word->hasSpaceAfter());

}



TEST_F(TextWordTest_1197, IsUnderlined_ReturnsFalseByDefault_1197) {

    EXPECT_FALSE(word->isUnderlined());

}



TEST_F(TextWordTest_1197, GetLink_ReturnsNullptrByDefault_1197) {

    EXPECT_EQ(word->getLink(), nullptr);

}



TEST_F(TextWordTest_1197, GetRotation_ReturnsInitialValue_1197) {

    EXPECT_EQ(word->getRotation(), 0);

}



TEST_F(TextWordTest_1197, GetFontSize_ReturnsInitialValue_1197) {

    EXPECT_DOUBLE_EQ(word->getFontSize(), 12.0);

}
