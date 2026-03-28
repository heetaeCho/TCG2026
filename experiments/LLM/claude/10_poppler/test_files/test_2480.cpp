#include <gtest/gtest.h>
#include <glib.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler.h"
}

class PopplerColorNewTest_2480 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_color_new returns a non-null pointer
TEST_F(PopplerColorNewTest_2480, ReturnsNonNull_2480)
{
    PopplerColor *color = poppler_color_new();
    ASSERT_NE(color, nullptr);
    g_free(color);
}

// Test that poppler_color_new returns a zero-initialized structure
TEST_F(PopplerColorNewTest_2480, ReturnsZeroInitialized_2480)
{
    PopplerColor *color = poppler_color_new();
    ASSERT_NE(color, nullptr);

    EXPECT_EQ(color->red, 0);
    EXPECT_EQ(color->green, 0);
    EXPECT_EQ(color->blue, 0);

    g_free(color);
}

// Test that multiple calls return distinct allocations
TEST_F(PopplerColorNewTest_2480, MultipleCallsReturnDistinctPointers_2480)
{
    PopplerColor *color1 = poppler_color_new();
    PopplerColor *color2 = poppler_color_new();

    ASSERT_NE(color1, nullptr);
    ASSERT_NE(color2, nullptr);
    EXPECT_NE(color1, color2);

    g_free(color1);
    g_free(color2);
}

// Test that the returned color can be modified without issues
TEST_F(PopplerColorNewTest_2480, CanModifyFields_2480)
{
    PopplerColor *color = poppler_color_new();
    ASSERT_NE(color, nullptr);

    color->red = 65535;
    color->green = 32768;
    color->blue = 0;

    EXPECT_EQ(color->red, 65535);
    EXPECT_EQ(color->green, 32768);
    EXPECT_EQ(color->blue, 0);

    g_free(color);
}

// Test allocation in a loop to ensure repeated calls work correctly
TEST_F(PopplerColorNewTest_2480, RepeatedAllocations_2480)
{
    const int NUM_ALLOCATIONS = 100;
    PopplerColor *colors[NUM_ALLOCATIONS];

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        colors[i] = poppler_color_new();
        ASSERT_NE(colors[i], nullptr);
        EXPECT_EQ(colors[i]->red, 0);
        EXPECT_EQ(colors[i]->green, 0);
        EXPECT_EQ(colors[i]->blue, 0);
    }

    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        g_free(colors[i]);
    }
}

// Test that each newly allocated color is independently zero-initialized
// even after a previous color was modified
TEST_F(PopplerColorNewTest_2480, NewColorIsZeroAfterPreviousModified_2480)
{
    PopplerColor *color1 = poppler_color_new();
    ASSERT_NE(color1, nullptr);

    color1->red = 12345;
    color1->green = 54321;
    color1->blue = 11111;

    PopplerColor *color2 = poppler_color_new();
    ASSERT_NE(color2, nullptr);

    EXPECT_EQ(color2->red, 0);
    EXPECT_EQ(color2->green, 0);
    EXPECT_EQ(color2->blue, 0);

    g_free(color1);
    g_free(color2);
}

// Test that poppler_color_copy and poppler_color_free work with newly created color
TEST_F(PopplerColorNewTest_2480, CopyAndFreeWork_2480)
{
    PopplerColor *color = poppler_color_new();
    ASSERT_NE(color, nullptr);

    color->red = 100;
    color->green = 200;
    color->blue = 300;

    PopplerColor *copy = poppler_color_copy(color);
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->red, 100);
    EXPECT_EQ(copy->green, 200);
    EXPECT_EQ(copy->blue, 300);

    poppler_color_free(color);
    poppler_color_free(copy);
}
