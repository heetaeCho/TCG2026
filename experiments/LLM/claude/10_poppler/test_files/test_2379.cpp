#include <glib.h>
#include <gtest/gtest.h>

// Include the poppler glib header for the public API
#include "poppler.h"

class PopplerSigningDataBackgroundColorTest_2379 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }
};

// Test that getting background color from a valid signing data returns non-null
TEST_F(PopplerSigningDataBackgroundColorTest_2379, ReturnsNonNullForValidSigningData_2379)
{
    const PopplerColor *color = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(color, nullptr);
}

// Test that passing nullptr returns nullptr (and triggers g_return_val_if_fail)
TEST_F(PopplerSigningDataBackgroundColorTest_2379, ReturnsNullForNullSigningData_2379)
{
    const PopplerColor *color = poppler_signing_data_get_background_color(nullptr);
    EXPECT_EQ(color, nullptr);
}

// Test that setting background color and then getting it returns the correct values
TEST_F(PopplerSigningDataBackgroundColorTest_2379, ReturnsSetBackgroundColor_2379)
{
    PopplerColor color;
    color.red = 255;
    color.green = 128;
    color.blue = 64;

    poppler_signing_data_set_background_color(signing_data, &color);

    const PopplerColor *retrieved = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 255);
    EXPECT_EQ(retrieved->green, 128);
    EXPECT_EQ(retrieved->blue, 64);
}

// Test default background color values on a freshly created signing data
TEST_F(PopplerSigningDataBackgroundColorTest_2379, DefaultBackgroundColorValues_2379)
{
    const PopplerColor *color = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(color, nullptr);
    // Default values should be deterministic (typically initialized to some default)
    // We just verify we can read them without crashing
    EXPECT_GE(color->red, 0);
    EXPECT_GE(color->green, 0);
    EXPECT_GE(color->blue, 0);
}

// Test setting background color with zero values
TEST_F(PopplerSigningDataBackgroundColorTest_2379, SetBackgroundColorToZero_2379)
{
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_background_color(signing_data, &color);

    const PopplerColor *retrieved = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 0);
}

// Test setting background color with max values
TEST_F(PopplerSigningDataBackgroundColorTest_2379, SetBackgroundColorToMaxValues_2379)
{
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;

    poppler_signing_data_set_background_color(signing_data, &color);

    const PopplerColor *retrieved = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 65535);
    EXPECT_EQ(retrieved->green, 65535);
    EXPECT_EQ(retrieved->blue, 65535);
}

// Test that setting background color multiple times returns the last set value
TEST_F(PopplerSigningDataBackgroundColorTest_2379, OverwriteBackgroundColor_2379)
{
    PopplerColor color1;
    color1.red = 100;
    color1.green = 200;
    color1.blue = 300;

    poppler_signing_data_set_background_color(signing_data, &color1);

    PopplerColor color2;
    color2.red = 400;
    color2.green = 500;
    color2.blue = 600;

    poppler_signing_data_set_background_color(signing_data, &color2);

    const PopplerColor *retrieved = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 400);
    EXPECT_EQ(retrieved->green, 500);
    EXPECT_EQ(retrieved->blue, 600);
}

// Test that copied signing data preserves background color
TEST_F(PopplerSigningDataBackgroundColorTest_2379, CopiedSigningDataPreservesBackgroundColor_2379)
{
    PopplerColor color;
    color.red = 111;
    color.green = 222;
    color.blue = 333;

    poppler_signing_data_set_background_color(signing_data, &color);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *retrieved = poppler_signing_data_get_background_color(copy);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 111);
    EXPECT_EQ(retrieved->green, 222);
    EXPECT_EQ(retrieved->blue, 333);

    poppler_signing_data_free(copy);
}

// Test that the returned pointer points to internal storage (same pointer on repeated calls)
TEST_F(PopplerSigningDataBackgroundColorTest_2379, ReturnsSamePointerOnRepeatedCalls_2379)
{
    const PopplerColor *color1 = poppler_signing_data_get_background_color(signing_data);
    const PopplerColor *color2 = poppler_signing_data_get_background_color(signing_data);
    EXPECT_EQ(color1, color2);
}
