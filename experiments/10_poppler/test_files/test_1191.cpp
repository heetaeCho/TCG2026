#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordTest_1191 : public ::testing::Test {

protected:

    GfxState gfxState;

    int rotation = 0;

    double fontSize = 12.0;

    TextWord* textWord;



    void SetUp() override {

        textWord = new TextWord(&gfxState, rotation, fontSize);

    }



    void TearDown() override {

        delete textWord;

    }

};



TEST_F(TextWordTest_1191, GetSpaceAfter_ReturnsFalseByDefault_1191) {

    EXPECT_FALSE(textWord->getSpaceAfter());

}



TEST_F(TextWordTest_1191, HasSpaceAfter_ReturnsFalseByDefault_1191) {

    EXPECT_FALSE(textWord->hasSpaceAfter());

}



// Assuming there is a way to set spaceAfter to true, otherwise this test is not possible

// TEST_F(TextWordTest_1191, GetSpaceAfter_ReturnsTrueWhenSet_1191) {

//     // Some function to set spaceAfter to true

//     EXPECT_TRUE(textWord->getSpaceAfter());

// }



TEST_F(TextWordTest_1191, IsUnderlined_ReturnsFalseByDefault_1191) {

    EXPECT_FALSE(textWord->isUnderlined());

}



TEST_F(TextWordTest_1191, GetRotation_ReturnsInitialValue_1191) {

    EXPECT_EQ(rotation, textWord->getRotation());

}



TEST_F(TextWordTest_1191, GetFontSize_ReturnsInitialValue_1191) {

    EXPECT_DOUBLE_EQ(fontSize, textWord->getFontSize());

}



// Assuming there is a way to set next word, otherwise this test is not possible

// TEST_F(TextWordTest_1191, GetNext_ReturnsSetNextWord_1191) {

//     TextWord* nextWord = new TextWord(&gfxState, rotation, fontSize);

//     textWord->setNext(nextWord); // Assuming a setNext method exists

//     EXPECT_EQ(nextWord, textWord->getNext());

//     delete nextWord;

// }



TEST_F(TextWordTest_1191, GetLength_ReturnsZeroInitially_1191) {

    EXPECT_EQ(0, textWord->getLength());

}



TEST_F(TextWordTest_1191, GetLink_ReturnsNullptrByDefault_1191) {

    EXPECT_EQ(nullptr, textWord->getLink());

}
