#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



namespace {



class PopplerFontDescriptionTest : public ::testing::Test {

protected:

    PopplerFontDescription font_desc;

    

    void SetUp() override {

        // Initialize the font description to default values

        font_desc.font_name = nullptr;

        font_desc.size_pt = 0.0;

        font_desc.stretch = POPPLER_STRETCH_NORMAL;

        font_desc.weight = POPPLER_WEIGHT_NORMAL;

        font_desc.style = POPPLER_STYLE_NORMAL;

    }

};



TEST_F(PopplerFontDescriptionTest_2042, UpdateWithValidStyleWord_2042) {

    std::string word = "italic";

    EXPECT_TRUE(update_font_desc_with_word(font_desc, word));

    EXPECT_EQ(font_desc.style, POPPLER_STYLE_ITALIC);

}



TEST_F(PopplerFontDescriptionTest_2042, UpdateWithValidWeightWord_2042) {

    std::string word = "bold";

    EXPECT_TRUE(update_font_desc_with_word(font_desc, word));

    EXPECT_EQ(font_desc.weight, POPPLER_WEIGHT_BOLD);

}



TEST_F(PopplerFontDescriptionTest_2042, UpdateWithValidStretchWord_2042) {

    std::string word = "expanded";

    EXPECT_TRUE(update_font_desc_with_word(font_desc, word));

    EXPECT_EQ(font_desc.stretch, POPPLER_STRETCH_EXPANDED);

}



TEST_F(PopplerFontDescriptionTest_2042, UpdateWithNormalWord_2042) {

    std::string word = "normal";

    EXPECT_TRUE(update_font_desc_with_word(font_desc, word));

}



TEST_F(PopplerFontDescriptionTest_2042, UpdateWithInvalidWord_2042) {

    std::string word = "invalid_style";

    EXPECT_FALSE(update_font_desc_with_word(font_desc, word));

}



} // namespace
