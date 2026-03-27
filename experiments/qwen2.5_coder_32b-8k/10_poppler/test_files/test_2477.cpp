#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.cc"

#include "TextOutputDev.h"



using namespace testing;



class PopplerTextAttributesTest_2477 : public ::testing::Test {

protected:

    TextWord* word;

    

    void SetUp() override {

        // Assuming a valid state for TextWord

        double fontSize = 12.0;

        int rotA = 0; 

        const GfxState *state = nullptr; // Placeholder, assuming it's set up elsewhere

        word = new TextWord(state, rotA, fontSize);

        

        // Mocking the color values for simplicity

        word->colorR = 1.0;

        word->colorG = 0.5;

        word->colorB = 0.25;

    }



    void TearDown() override {

        delete word;

    }

};



TEST_F(PopplerTextAttributesTest_2477, FontNameSetCorrectly_2477) {

    // Assuming get_font_name_from_word is a function that returns a valid font name

    const char* expectedFontName = "MockFont";

    EXPECT_CALL(*word, getFontName(0)).WillOnce(Return(new GooString(expectedFontName)));



    PopplerTextAttributes *attrs = poppler_text_attributes_new_from_word(word, 0);

    ASSERT_STREQ(attrs->font_name, expectedFontName);



    g_free(attrs->font_name);

    poppler_text_attributes_free(attrs);

}



TEST_F(PopplerTextAttributesTest_2477, FontSizeSetCorrectly_2477) {

    PopplerTextAttributes *attrs = poppler_text_attributes_new_from_word(word, 0);

    ASSERT_EQ(attrs->font_size, word->getFontSize());



    poppler_text_attributes_free(attrs);

}



TEST_F(PopplerTextAttributesTest_2477, IsUnderlinedSetCorrectly_2477) {

    // Assuming the word is underlined

    EXPECT_CALL(*word, isUnderlined()).WillOnce(Return(true));



    PopplerTextAttributes *attrs = poppler_text_attributes_new_from_word(word, 0);

    ASSERT_TRUE(attrs->is_underlined);



    poppler_text_attributes_free(attrs);

}



TEST_F(PopplerTextAttributesTest_2477, ColorSetCorrectly_2477) {

    PopplerTextAttributes *attrs = poppler_text_attributes_new_from_word(word, 0);

    

    int expectedRed = static_cast<int>(word->colorR * 65535. + 0.5);

    int expectedGreen = static_cast<int>(word->colorG * 65535. + 0.5);

    int expectedBlue = static_cast<int>(word->colorB * 65535. + 0.5);



    ASSERT_EQ(attrs->color.red, expectedRed);

    ASSERT_EQ(attrs->color.green, expectedGreen);

    ASSERT_EQ(attrs->color.blue, expectedBlue);



    poppler_text_attributes_free(attrs);

}



TEST_F(PopplerTextAttributesTest_2477, EdgeCaseFontSizeZero_2477) {

    // Assuming a word with zero font size

    double fontSize = 0.0;

    int rotA = 0; 

    const GfxState *state = nullptr; // Placeholder, assuming it's set up elsewhere

    TextWord* wordWithZeroFontSize = new TextWord(state, rotA, fontSize);



    PopplerTextAttributes *attrs = poppler_text_attributes_new_from_word(wordWithZeroFontSize, 0);

    ASSERT_EQ(attrs->font_size, 0.0);



    delete wordWithZeroFontSize;

    poppler_text_attributes_free(attrs);

}



TEST_F(PopplerTextAttributesTest_2477, EdgeCaseColorValues_2477) {

    // Assuming max and min color values

    word->colorR = 1.0;

    word->colorG = 0.0;

    word->colorB = 0.0;



    PopplerTextAttributes *attrs = poppler_text_attributes_new_from_word(word, 0);



    int expectedRedMax = static_cast<int>(word->colorR * 65535. + 0.5);

    int expectedGreenMin = static_cast<int>(word->colorG * 65535. + 0.5);

    int expectedBlueMin = static_cast<int>(word->colorB * 65535. + 0.5);



    ASSERT_EQ(attrs->color.red, expectedRedMax);

    ASSERT_EQ(attrs->color.green, expectedGreenMin);

    ASSERT_EQ(attrs->color.blue, expectedBlueMin);



    poppler_text_attributes_free(attrs);

}

```


