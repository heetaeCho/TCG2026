#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



using namespace testing;



// Mocking the update_font_desc_with_word function to control its behavior in tests.

bool update_font_desc_with_word(PopplerFontDescription &font_desc, const std::string &word);



class PopplerFontNameToDescriptionTest : public Test {

protected:

    void SetUp() override {

        // Initialize font_desc before each test

        font_desc.font_name = nullptr;

        font_desc.size_pt = 0.0;

        font_desc.stretch = POPPLER_STRETCH_NORMAL;

        font_desc.weight = POPPLER_WEIGHT_NORMAL;

        font_desc.style = POPPLER_STYLE_NORMAL;

    }



    void TearDown() override {

        // Free the allocated memory for font_name after each test

        g_free(font_desc.font_name);

    }



    PopplerFontDescription font_desc;

};



// Test normal operation with a typical font name

TEST_F(PopplerFontNameToDescriptionTest, NormalOperation_2043) {

    std::string fontName = "Arial Bold Italic";

    poppler_font_name_to_description(fontName, font_desc);

    EXPECT_STREQ(font_desc.font_name, "Arial");

}



// Test boundary condition with a single word font name

TEST_F(PopplerFontNameToDescriptionTest, SingleWordFontName_2043) {

    std::string fontName = "Helvetica";

    poppler_font_name_to_description(fontName, font_desc);

    EXPECT_STREQ(font_desc.font_name, "Helvetica");

}



// Test boundary condition with an empty string

TEST_F(PopplerFontNameToDescriptionTest, EmptyString_2043) {

    std::string fontName = "";

    poppler_font_name_to_description(fontName, font_desc);

    EXPECT_STREQ(font_desc.font_name, "");

}



// Test exceptional case where update_font_desc_with_word fails on first word

TEST_F(PopplerFontNameToDescriptionTest, UpdateWordFailsFirst_2043) {

    std::string fontName = "Arial Bold Italic";

    ON_CALL(*this, MockUpdateFontDescWithWord(_, _)).WillByDefault(Return(false));

    poppler_font_name_to_description(fontName, font_desc);

    EXPECT_STREQ(font_desc.font_name, "Arial Bold");

}



// Test exceptional case where update_font_desc_with_word fails on second word

TEST_F(PopplerFontNameToDescriptionTest, UpdateWordFailsSecond_2043) {

    std::string fontName = "Arial Bold Italic";

    EXPECT_CALL(*this, MockUpdateFontDescWithWord(_, _)).WillOnce(Return(true)).WillOnce(Return(false));

    poppler_font_name_to_description(fontName, font_desc);

    EXPECT_STREQ(font_desc.font_name, "Arial");

}



// Test with multiple spaces

TEST_F(PopplerFontNameToDescriptionTest, MultipleSpaces_2043) {

    std::string fontName = "Times   New Roman Bold";

    poppler_font_name_to_description(fontName, font_desc);

    EXPECT_STREQ(font_desc.font_name, "Times New Roman");

}



// Mock function to simulate update_font_desc_with_word behavior

bool PopplerFontNameToDescriptionTest::update_font_desc_with_word(PopplerFontDescription &font_desc, const std::string &word) {

    // Default mock implementation that always returns true

    return true;

}
