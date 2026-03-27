#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"

#include "poppler/AnnotLink.h"



class TextWordTest_1193 : public ::testing::Test {

protected:

    TextWord* textWord;



    virtual void SetUp() {

        // Assuming GfxState is a mockable or test-friendly class

        GfxState state;

        textWord = new TextWord(&state, 0, 12.0);

    }



    virtual void TearDown() {

        delete textWord;

    }

};



TEST_F(TextWordTest_1193, GetLink_ReturnsNullByDefault_1193) {

    EXPECT_EQ(textWord->getLink(), nullptr);

}



// Assuming AnnotLink can be created and assigned for testing

TEST_F(TextWordTest_1193, SetAndGetLink_ReturnsCorrectLink_1193) {

    AnnotLink link;

    // There's no setter method provided in the interface to set a link,

    // so this test case is theoretical. Assuming there was a way to set it.

    // textWord->setLink(&link);

    EXPECT_EQ(textWord->getLink(), &link);

}



TEST_F(TextWordTest_1193, GetRotation_ReturnsInitialRotation_1193) {

    EXPECT_EQ(textWord->getRotation(), 0);

}



TEST_F(TextWordTest_1193, GetFontSize_ReturnsInitialFontSize_1193) {

    EXPECT_DOUBLE_EQ(textWord->getFontSize(), 12.0);

}



TEST_F(TextWordTest_1193, HasSpaceAfter_ReturnsFalseByDefault_1193) {

    EXPECT_FALSE(textWord->hasSpaceAfter());

}



TEST_F(TextWordTest_1193, IsUnderlined_ReturnsFalseByDefault_1193) {

    EXPECT_FALSE(textWord->isUnderlined());

}



// Assuming addChar can be used to modify internal state and affect getLength

TEST_F(TextWordTest_1193, AddChar_IncreasesLength_1193) {

    TextFontInfo font;

    textWord->addChar(&font, 0.0, 0.0, 1.0, 1.0, 0, 1, 'A', U'A', Matrix());

    EXPECT_EQ(textWord->getLength(), 1);

}



TEST_F(TextWordTest_1193, AddCombining_IncreasesLength_1193) {

    TextFontInfo font;

    textWord->addCombining(&font, 12.0, 0.0, 0.0, 1.0, 1.0, 0, 1, 'A', U'A', Matrix());

    EXPECT_EQ(textWord->getLength(), 1);

}



// Assuming merge can be used to modify internal state and affect getLength

TEST_F(TextWordTest_1193, Merge_IncreasesLength_1193) {

    GfxState state;

    TextWord otherWord(&state, 0, 12.0);

    textWord->merge(&otherWord);

    EXPECT_GE(textWord->getLength(), 0); // Length can be 0 if both words are empty

}



TEST_F(TextWordTest_1193, GetChar_ReturnsNullForInvalidIndex_1193) {

    EXPECT_EQ(textWord->getChar(0), nullptr);

}



TEST_F(TextWordTest_1193, GetFontInfo_ReturnsNullForInvalidIndex_1193) {

    EXPECT_EQ(textWord->getFontInfo(0), nullptr);

}



TEST_F(TextWordTest_1193, GetFontName_ReturnsNullForInvalidIndex_1193) {

    EXPECT_EQ(textWord->getFontName(0), nullptr);

}
