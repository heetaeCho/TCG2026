#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <map>

// Mocks for PopplerFontDescription and necessary enum classes
enum PopplerStyle { STYLE_NORMAL, STYLE_BOLD, STYLE_ITALIC };
enum PopplerWeight { WEIGHT_LIGHT, WEIGHT_REGULAR, WEIGHT_BOLD };
enum PopplerStretch { STRETCH_NORMAL, STRETCH_WIDE, STRETCH_CONDENSED };
enum FontPropType { TYPE_STYLE, TYPE_WEIGHT, TYPE_STRETCH, TYPE_NORMAL };

struct PopplerFontDescription {
    char* font_name;
    double size_pt;
    PopplerStretch stretch;
    PopplerWeight weight;
    PopplerStyle style;
};

using FontProp = std::pair<FontPropType, int>;

// Mock for string_to_fontstyle map
std::map<std::string, FontProp> string_to_fontstyle = {
    {"normal", {TYPE_NORMAL, 0}},
    {"bold", {TYPE_STYLE, STYLE_BOLD}},
    {"light", {TYPE_WEIGHT, WEIGHT_LIGHT}},
    {"wide", {TYPE_STRETCH, STRETCH_WIDE}},
};

bool update_font_desc_with_word(PopplerFontDescription &font_desc, std::string &word) {
    auto a = string_to_fontstyle.find(word);
    if (a != string_to_fontstyle.end()) {
        std::pair<FontPropType, int> elt = a->second;
        switch (elt.first) {
            case TYPE_STYLE:
                font_desc.style = (PopplerStyle)elt.second;
                return true;
            case TYPE_WEIGHT:
                font_desc.weight = (PopplerWeight)elt.second;
                return true;
            case TYPE_STRETCH:
                font_desc.stretch = (PopplerStretch)elt.second;
                return true;
            case TYPE_NORMAL:
                return true;
        }
    }
    return false;
}

// Test Fixture for PopplerFontDescription and update_font_desc_with_word
class PopplerFontDescriptionTest_2042 : public ::testing::Test {
protected:
    PopplerFontDescription font_desc;
    std::string word;

    void SetUp() override {
        font_desc.font_name = "Arial";
        font_desc.size_pt = 12.0;
        font_desc.stretch = STRETCH_NORMAL;
        font_desc.weight = WEIGHT_REGULAR;
        font_desc.style = STYLE_NORMAL;
    }
};

// Normal operation tests
TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_Style_2042) {
    word = "bold";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.style, STYLE_BOLD);
}

TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_Weight_2042) {
    word = "light";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.weight, WEIGHT_LIGHT);
}

TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_Stretch_2042) {
    word = "wide";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.stretch, STRETCH_WIDE);
}

TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_Normal_2042) {
    word = "normal";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.stretch, STRETCH_NORMAL);
    EXPECT_EQ(font_desc.weight, WEIGHT_REGULAR);
    EXPECT_EQ(font_desc.style, STYLE_NORMAL);
}

// Boundary condition tests
TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_EmptyWord_2042) {
    word = "";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_FALSE(result);
}

TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_UnknownWord_2042) {
    word = "extra-bold";  // A word not present in the map
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_FALSE(result);
}

// Exceptional/Error case tests
TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_InvalidEnum_2042) {
    word = "invalid";  // Invalid word that isn't mapped
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_FALSE(result);
}

// Verification of external interactions (Mocking)
TEST_F(PopplerFontDescriptionTest_2042, UpdateFontDesc_VerifyHandler_2042) {
    // In this case, no external handler is involved, but if we had any external dependencies
    // that we could verify, this is where we would do it.
    word = "bold";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
}