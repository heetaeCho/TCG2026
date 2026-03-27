#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TextOutputDev.h"



using namespace testing;



class TextWordTest_1190 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

        state = new GfxState();

        textWord = new TextWord(state, 0, 12.0);

    }



    void TearDown() override {

        delete textWord;

        delete state;

    }



    GfxState* state;

    TextWord* textWord;

};



TEST_F(TextWordTest_1190, GetCharLen_ReturnsZeroForEmptyChars_1190) {

    EXPECT_EQ(textWord->getCharLen(), 0);

}



TEST_F(TextWordTest_1190, GetCharLen_ReturnsCorrectLengthAfterAddingChar_1190) {

    TextFontInfo* font = new TextFontInfo();

    textWord->addChar(font, 0.0, 0.0, 0.5, 0.5, 0, 1, 65, U'A', Matrix());

    EXPECT_EQ(textWord->getCharLen(), 1);

    delete font;

}



TEST_F(TextWordTest_1190, GetCharLen_ReturnsCorrectLengthAfterMultipleAddChars_1190) {

    TextFontInfo* font = new TextFontInfo();

    textWord->addChar(font, 0.0, 0.0, 0.5, 0.5, 0, 1, 65, U'A', Matrix());

    textWord->addChar(font, 0.5, 0.0, 0.5, 0.5, 1, 2, 66, U'B', Matrix());

    EXPECT_EQ(textWord->getCharLen(), 2);

    delete font;

}



TEST_F(TextWordTest_1190, GetCharLen_CorrectAfterAddingCombiningCharacter_1190) {

    TextFontInfo* font = new TextFontInfo();

    textWord->addChar(font, 0.0, 0.0, 0.5, 0.5, 0, 1, 65, U'A', Matrix());

    textWord->addCombining(font, 12.0, 0.5, 0.0, 0.5, 0.5, 1, 1, 769, U'\u0301', Matrix());

    EXPECT_EQ(textWord->getCharLen(), 1);

    delete font;

}



TEST_F(TextWordTest_1190, GetCharLen_ReturnsZeroAfterMergeWithEmptyTextWord_1190) {

    TextWord* word2 = new TextWord(state, 0, 12.0);

    textWord->merge(word2);

    EXPECT_EQ(textWord->getCharLen(), 0);

    delete word2;

}



TEST_F(TextWordTest_1190, GetCharLen_ReturnsCorrectLengthAfterMergeWithNonEmptyTextWord_1190) {

    TextFontInfo* font = new TextFontInfo();

    textWord->addChar(font, 0.0, 0.0, 0.5, 0.5, 0, 1, 65, U'A', Matrix());

    TextWord* word2 = new TextWord(state, 0, 12.0);

    word2->addChar(font, 0.5, 0.0, 0.5, 0.5, 1, 2, 66, U'B', Matrix());

    textWord->merge(word2);

    EXPECT_EQ(textWord->getCharLen(), 3); // Assuming merge combines charPos and charLen appropriately

    delete font;

    delete word2;

}
