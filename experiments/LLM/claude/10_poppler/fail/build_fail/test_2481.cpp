#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

typedef struct _PopplerColor {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

PopplerColor *poppler_color_copy(PopplerColor *color);
}

class PopplerColorCopyTest_2481 : public ::testing::Test {
protected:
    void TearDown() override {}
};

TEST_F(PopplerColorCopyTest_2481, CopyReturnsNonNull_2481)
{
    PopplerColor color;
    color.red = 100;
    color.green = 200;
    color.blue = 300;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyHasCorrectRedValue_2481)
{
    PopplerColor color;
    color.red = 12345;
    color.green = 0;
    color.blue = 0;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->red, 12345);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyHasCorrectGreenValue_2481)
{
    PopplerColor color;
    color.red = 0;
    color.green = 54321;
    color.blue = 0;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->green, 54321);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyHasCorrectBlueValue_2481)
{
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 65535;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->blue, 65535);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyPreservesAllFields_2481)
{
    PopplerColor color;
    color.red = 111;
    color.green = 222;
    color.blue = 333;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->red, 111);
    EXPECT_EQ(copy->green, 222);
    EXPECT_EQ(copy->blue, 333);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyIsDifferentPointer_2481)
{
    PopplerColor color;
    color.red = 10;
    color.green = 20;
    color.blue = 30;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, &color);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyIsIndependentOfOriginal_2481)
{
    PopplerColor color;
    color.red = 500;
    color.green = 600;
    color.blue = 700;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);

    // Modify original after copy
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    // Copy should retain original values
    EXPECT_EQ(copy->red, 500);
    EXPECT_EQ(copy->green, 600);
    EXPECT_EQ(copy->blue, 700);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyWithZeroValues_2481)
{
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->red, 0);
    EXPECT_EQ(copy->green, 0);
    EXPECT_EQ(copy->blue, 0);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, CopyWithMaxValues_2481)
{
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;

    PopplerColor *copy = poppler_color_copy(&color);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->red, 65535);
    EXPECT_EQ(copy->green, 65535);
    EXPECT_EQ(copy->blue, 65535);
    g_free(copy);
}

TEST_F(PopplerColorCopyTest_2481, MultipleCopiesAreIndependent_2481)
{
    PopplerColor color;
    color.red = 100;
    color.green = 200;
    color.blue = 300;

    PopplerColor *copy1 = poppler_color_copy(&color);
    PopplerColor *copy2 = poppler_color_copy(&color);

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);

    EXPECT_EQ(copy1->red, copy2->red);
    EXPECT_EQ(copy1->green, copy2->green);
    EXPECT_EQ(copy1->blue, copy2->blue);

    // Modify copy1, copy2 should be unaffected
    copy1->red = 999;
    EXPECT_EQ(copy2->red, 100);

    g_free(copy1);
    g_free(copy2);
}

TEST_F(PopplerColorCopyTest_2481, CopyOfHeapAllocatedColor_2481)
{
    PopplerColor *color = g_new(PopplerColor, 1);
    color->red = 1000;
    color->green = 2000;
    color->blue = 3000;

    PopplerColor *copy = poppler_color_copy(color);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, color);
    EXPECT_EQ(copy->red, 1000);
    EXPECT_EQ(copy->green, 2000);
    EXPECT_EQ(copy->blue, 3000);

    g_free(color);
    g_free(copy);
}
