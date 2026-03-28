#include <gtest/gtest.h>
#include <glib.h>

// Include the necessary headers
extern "C" {
#include "poppler-annot.h"
}

// Forward declare the function under test if not in header
extern "C" PopplerFontDescription *poppler_font_description_copy(PopplerFontDescription *font_desc);

class PopplerFontDescriptionCopyTest_2126 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled per test
    }
};

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyReturnsDifferentPointer_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("Arial");
    original->size_pt = 12.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_NE(copy, original);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyPreservesFontName_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("Times New Roman");
    original->size_pt = 14.5;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_BOLD;
    original->style = POPPLER_STYLE_ITALIC;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    ASSERT_NE(copy->font_name, nullptr);
    EXPECT_STREQ(copy->font_name, "Times New Roman");
    // Ensure it's a deep copy (different pointer)
    EXPECT_NE(copy->font_name, original->font_name);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyPreservesSizePt_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("Courier");
    original->size_pt = 99.99;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_DOUBLE_EQ(copy->size_pt, 99.99);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyPreservesStretch_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("Helvetica");
    original->size_pt = 10.0;
    original->stretch = POPPLER_STRETCH_CONDENSED;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_EQ(copy->stretch, POPPLER_STRETCH_CONDENSED);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyPreservesWeight_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("Verdana");
    original->size_pt = 8.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_BOLD;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_EQ(copy->weight, POPPLER_WEIGHT_BOLD);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyPreservesStyle_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("Georgia");
    original->size_pt = 16.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_ITALIC;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_EQ(copy->style, POPPLER_STYLE_ITALIC);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyWithEmptyFontName_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("");
    original->size_pt = 0.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    ASSERT_NE(copy->font_name, nullptr);
    EXPECT_STREQ(copy->font_name, "");
    EXPECT_NE(copy->font_name, original->font_name);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyWithZeroSize_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("Mono");
    original->size_pt = 0.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_DOUBLE_EQ(copy->size_pt, 0.0);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyWithNegativeSize_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("TestFont");
    original->size_pt = -5.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_DOUBLE_EQ(copy->size_pt, -5.0);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyWithLongFontName_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    // Create a long font name
    std::string long_name(1000, 'A');
    original->font_name = g_strdup(long_name.c_str());
    original->size_pt = 12.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    ASSERT_NE(copy->font_name, nullptr);
    EXPECT_STREQ(copy->font_name, long_name.c_str());
    EXPECT_NE(copy->font_name, original->font_name);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyAllFieldsAtOnce_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("ComplexFont-BoldItalic");
    original->size_pt = 24.75;
    original->stretch = POPPLER_STRETCH_EXPANDED;
    original->weight = POPPLER_WEIGHT_BOLD;
    original->style = POPPLER_STYLE_OBLIQUE;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_NE(copy, original);
    EXPECT_NE(copy->font_name, original->font_name);
    EXPECT_STREQ(copy->font_name, "ComplexFont-BoldItalic");
    EXPECT_DOUBLE_EQ(copy->size_pt, 24.75);
    EXPECT_EQ(copy->stretch, POPPLER_STRETCH_EXPANDED);
    EXPECT_EQ(copy->weight, POPPLER_WEIGHT_BOLD);
    EXPECT_EQ(copy->style, POPPLER_STYLE_OBLIQUE);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, ModifyingCopyDoesNotAffectOriginal_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("OriginalFont");
    original->size_pt = 12.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    // Modify the copy
    g_free(copy->font_name);
    copy->font_name = g_strdup("ModifiedFont");
    copy->size_pt = 999.0;

    // Original should be unchanged
    EXPECT_STREQ(original->font_name, "OriginalFont");
    EXPECT_DOUBLE_EQ(original->size_pt, 12.0);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyWithVeryLargeSize_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("BigFont");
    original->size_pt = 1e308;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    EXPECT_DOUBLE_EQ(copy->size_pt, 1e308);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}

TEST_F(PopplerFontDescriptionCopyTest_2126, CopyWithUnicodeFontName_2126)
{
    PopplerFontDescription *original = g_new(PopplerFontDescription, 1);
    original->font_name = g_strdup("字体名称-テスト");
    original->size_pt = 11.0;
    original->stretch = POPPLER_STRETCH_NORMAL;
    original->weight = POPPLER_WEIGHT_NORMAL;
    original->style = POPPLER_STYLE_NORMAL;

    PopplerFontDescription *copy = poppler_font_description_copy(original);

    ASSERT_NE(copy->font_name, nullptr);
    EXPECT_STREQ(copy->font_name, "字体名称-テスト");
    EXPECT_NE(copy->font_name, original->font_name);

    g_free(copy->font_name);
    g_free(copy);
    g_free(original->font_name);
    g_free(original);
}
