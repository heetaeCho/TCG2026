#include <gtest/gtest.h>
#include <glib.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler-page.h"
}

// Forward declare the function we're testing
extern "C" {
PopplerTextAttributes *poppler_text_attributes_copy(PopplerTextAttributes *text_attrs);
PopplerTextAttributes *poppler_text_attributes_new(void);
void poppler_text_attributes_free(PopplerTextAttributes *text_attrs);
}

class PopplerTextAttributesCopyTest_2478 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerTextAttributesCopyTest_2478, CopyReturnsDifferentPointer_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Arial");
    orig->font_size = 12.0;
    orig->is_underlined = TRUE;
    orig->color.red = 255;
    orig->color.green = 128;
    orig->color.blue = 64;
    orig->start_index = 0;
    orig->end_index = 10;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, orig);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyPreservesFontName_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Times New Roman");
    orig->font_size = 14.0;
    orig->is_underlined = FALSE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 5;
    orig->end_index = 20;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->font_name, nullptr);
    EXPECT_STREQ(copy->font_name, "Times New Roman");

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyFontNameIsDifferentPointer_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Helvetica");
    orig->font_size = 10.0;
    orig->is_underlined = FALSE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 0;
    orig->end_index = 5;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->font_name, nullptr);
    // The font_name should be a deep copy, not the same pointer
    EXPECT_NE(copy->font_name, orig->font_name);
    EXPECT_STREQ(copy->font_name, orig->font_name);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyPreservesFontSize_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Courier");
    orig->font_size = 24.5;
    orig->is_underlined = FALSE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 0;
    orig->end_index = 100;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->font_size, 24.5);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyPreservesIsUnderlined_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Verdana");
    orig->font_size = 11.0;
    orig->is_underlined = TRUE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 0;
    orig->end_index = 50;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->is_underlined, TRUE);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyPreservesColor_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Georgia");
    orig->font_size = 16.0;
    orig->is_underlined = FALSE;
    orig->color.red = 12345;
    orig->color.green = 54321;
    orig->color.blue = 65535;
    orig->start_index = 3;
    orig->end_index = 7;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->color.red, 12345);
    EXPECT_EQ(copy->color.green, 54321);
    EXPECT_EQ(copy->color.blue, 65535);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyPreservesStartAndEndIndex_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Monospace");
    orig->font_size = 9.0;
    orig->is_underlined = FALSE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 42;
    orig->end_index = 99;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->start_index, 42);
    EXPECT_EQ(copy->end_index, 99);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyPreservesAllFields_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Comic Sans MS");
    orig->font_size = 72.0;
    orig->is_underlined = TRUE;
    orig->color.red = 65535;
    orig->color.green = 0;
    orig->color.blue = 32768;
    orig->start_index = 100;
    orig->end_index = 200;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->font_name, "Comic Sans MS");
    EXPECT_NE(copy->font_name, orig->font_name);
    EXPECT_DOUBLE_EQ(copy->font_size, 72.0);
    EXPECT_EQ(copy->is_underlined, TRUE);
    EXPECT_EQ(copy->color.red, 65535);
    EXPECT_EQ(copy->color.green, 0);
    EXPECT_EQ(copy->color.blue, 32768);
    EXPECT_EQ(copy->start_index, 100);
    EXPECT_EQ(copy->end_index, 200);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyWithEmptyFontName_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("");
    orig->font_size = 0.0;
    orig->is_underlined = FALSE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 0;
    orig->end_index = 0;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->font_name, nullptr);
    EXPECT_STREQ(copy->font_name, "");

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyWithZeroFontSize_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Test");
    orig->font_size = 0.0;
    orig->is_underlined = FALSE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 0;
    orig->end_index = 0;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->font_size, 0.0);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, ModifyingCopyDoesNotAffectOriginal_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("OriginalFont");
    orig->font_size = 18.0;
    orig->is_underlined = TRUE;
    orig->color.red = 100;
    orig->color.green = 200;
    orig->color.blue = 300;
    orig->start_index = 10;
    orig->end_index = 20;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    // Modify the copy
    g_free(copy->font_name);
    copy->font_name = g_strdup("ModifiedFont");
    copy->font_size = 36.0;
    copy->is_underlined = FALSE;
    copy->color.red = 999;
    copy->start_index = 50;
    copy->end_index = 60;

    // Verify original is unchanged
    EXPECT_STREQ(orig->font_name, "OriginalFont");
    EXPECT_DOUBLE_EQ(orig->font_size, 18.0);
    EXPECT_EQ(orig->is_underlined, TRUE);
    EXPECT_EQ(orig->color.red, 100);
    EXPECT_EQ(orig->start_index, 10);
    EXPECT_EQ(orig->end_index, 20);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyWithLongFontName_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    // Create a long font name
    std::string longName(1000, 'A');
    orig->font_name = g_strdup(longName.c_str());
    orig->font_size = 12.0;
    orig->is_underlined = FALSE;
    orig->color.red = 0;
    orig->color.green = 0;
    orig->color.blue = 0;
    orig->start_index = 0;
    orig->end_index = 1;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->font_name, nullptr);
    EXPECT_STREQ(copy->font_name, longName.c_str());
    EXPECT_NE(copy->font_name, orig->font_name);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}

TEST_F(PopplerTextAttributesCopyTest_2478, CopyWithBoundaryColorValues_2478)
{
    PopplerTextAttributes *orig = poppler_text_attributes_new();
    orig->font_name = g_strdup("Test");
    orig->font_size = 12.0;
    orig->is_underlined = FALSE;
    orig->color.red = 65535;
    orig->color.green = 65535;
    orig->color.blue = 65535;
    orig->start_index = 0;
    orig->end_index = 1;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(orig);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->color.red, 65535);
    EXPECT_EQ(copy->color.green, 65535);
    EXPECT_EQ(copy->color.blue, 65535);

    poppler_text_attributes_free(copy);
    poppler_text_attributes_free(orig);
}
