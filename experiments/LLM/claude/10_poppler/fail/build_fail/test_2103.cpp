#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definitions based on known dependencies
typedef struct {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

typedef struct _PopplerFontDescription PopplerFontDescription;

typedef struct _PopplerAnnotFreeText {
    PopplerFontDescription *font_desc;
    PopplerColor font_color;
} PopplerAnnotFreeText;

// Declaration of the function under test
extern "C" {
PopplerColor *poppler_annot_free_text_get_font_color(PopplerAnnotFreeText *poppler_annot);
}

class PopplerAnnotFreeTextGetFontColorTest_2103 : public ::testing::Test {
protected:
    PopplerAnnotFreeText annot;

    void SetUp() override {
        memset(&annot, 0, sizeof(annot));
    }
};

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, ReturnsNonNullPointer_2103) {
    annot.font_color.red = 100;
    annot.font_color.green = 200;
    annot.font_color.blue = 300;

    PopplerColor *result = poppler_annot_free_text_get_font_color(&annot);
    ASSERT_NE(result, nullptr);
    g_free(result);
}

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, ReturnsCopyOfFontColor_2103) {
    annot.font_color.red = 12345;
    annot.font_color.green = 54321;
    annot.font_color.blue = 65535;

    PopplerColor *result = poppler_annot_free_text_get_font_color(&annot);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 12345);
    EXPECT_EQ(result->green, 54321);
    EXPECT_EQ(result->blue, 65535);
    g_free(result);
}

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, ReturnsIndependentCopy_2103) {
    annot.font_color.red = 100;
    annot.font_color.green = 200;
    annot.font_color.blue = 300;

    PopplerColor *result = poppler_annot_free_text_get_font_color(&annot);
    ASSERT_NE(result, nullptr);

    // Modify the original and verify the returned copy is independent
    annot.font_color.red = 999;
    annot.font_color.green = 888;
    annot.font_color.blue = 777;

    EXPECT_EQ(result->red, 100);
    EXPECT_EQ(result->green, 200);
    EXPECT_EQ(result->blue, 300);
    g_free(result);
}

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, ZeroColorValues_2103) {
    annot.font_color.red = 0;
    annot.font_color.green = 0;
    annot.font_color.blue = 0;

    PopplerColor *result = poppler_annot_free_text_get_font_color(&annot);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0);
    EXPECT_EQ(result->green, 0);
    EXPECT_EQ(result->blue, 0);
    g_free(result);
}

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, MaxColorValues_2103) {
    annot.font_color.red = 65535;
    annot.font_color.green = 65535;
    annot.font_color.blue = 65535;

    PopplerColor *result = poppler_annot_free_text_get_font_color(&annot);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 65535);
    EXPECT_EQ(result->green, 65535);
    EXPECT_EQ(result->blue, 65535);
    g_free(result);
}

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, MixedColorValues_2103) {
    annot.font_color.red = 0;
    annot.font_color.green = 32768;
    annot.font_color.blue = 65535;

    PopplerColor *result = poppler_annot_free_text_get_font_color(&annot);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0);
    EXPECT_EQ(result->green, 32768);
    EXPECT_EQ(result->blue, 65535);
    g_free(result);
}

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, MultipleCallsReturnDifferentPointers_2103) {
    annot.font_color.red = 100;
    annot.font_color.green = 200;
    annot.font_color.blue = 300;

    PopplerColor *result1 = poppler_annot_free_text_get_font_color(&annot);
    PopplerColor *result2 = poppler_annot_free_text_get_font_color(&annot);

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1, result2);

    // Both should have the same values
    EXPECT_EQ(result1->red, result2->red);
    EXPECT_EQ(result1->green, result2->green);
    EXPECT_EQ(result1->blue, result2->blue);

    g_free(result1);
    g_free(result2);
}

TEST_F(PopplerAnnotFreeTextGetFontColorTest_2103, ModifyReturnedColorDoesNotAffectOriginal_2103) {
    annot.font_color.red = 500;
    annot.font_color.green = 600;
    annot.font_color.blue = 700;

    PopplerColor *result = poppler_annot_free_text_get_font_color(&annot);
    ASSERT_NE(result, nullptr);

    // Modify the returned copy
    result->red = 0;
    result->green = 0;
    result->blue = 0;

    // Original should be unchanged
    EXPECT_EQ(annot.font_color.red, 500);
    EXPECT_EQ(annot.font_color.green, 600);
    EXPECT_EQ(annot.font_color.blue, 700);

    g_free(result);
}
