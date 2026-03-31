#include <glib.h>
#include <gtest/gtest.h>

// Include the poppler glib header for the public API
#include "poppler-form-field.h"

class PopplerSigningDataGetBorderColorTest_2375 : public ::testing::Test {
protected:
    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
        }
    }

    PopplerSigningData *signing_data = nullptr;
};

// Test that getting border color from a valid signing data returns non-null
TEST_F(PopplerSigningDataGetBorderColorTest_2375, ReturnsNonNullForValidSigningData_2375)
{
    const PopplerColor *color = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(color, nullptr);
}

// Test that getting border color from null signing data returns null
TEST_F(PopplerSigningDataGetBorderColorTest_2375, ReturnsNullForNullSigningData_2375)
{
    const PopplerColor *color = poppler_signing_data_get_border_color(nullptr);
    EXPECT_EQ(color, nullptr);
}

// Test that setting a border color and then getting it returns the expected values
TEST_F(PopplerSigningDataGetBorderColorTest_2375, ReturnsSetBorderColor_2375)
{
    PopplerColor color;
    color.red = 255;
    color.green = 128;
    color.blue = 64;

    poppler_signing_data_set_border_color(signing_data, &color);

    const PopplerColor *retrieved_color = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 255);
    EXPECT_EQ(retrieved_color->green, 128);
    EXPECT_EQ(retrieved_color->blue, 64);
}

// Test that default border color has some initial values (all zeros or default)
TEST_F(PopplerSigningDataGetBorderColorTest_2375, DefaultBorderColorValues_2375)
{
    const PopplerColor *color = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(color, nullptr);
    // Default color should be initialized - we just verify we can read the values without crashing
    // The actual default values depend on implementation
    EXPECT_GE(color->red, 0);
    EXPECT_GE(color->green, 0);
    EXPECT_GE(color->blue, 0);
}

// Test setting border color with zero values
TEST_F(PopplerSigningDataGetBorderColorTest_2375, SetBorderColorToZero_2375)
{
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_border_color(signing_data, &color);

    const PopplerColor *retrieved_color = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 0);
    EXPECT_EQ(retrieved_color->green, 0);
    EXPECT_EQ(retrieved_color->blue, 0);
}

// Test setting border color with max values
TEST_F(PopplerSigningDataGetBorderColorTest_2375, SetBorderColorToMaxValues_2375)
{
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;

    poppler_signing_data_set_border_color(signing_data, &color);

    const PopplerColor *retrieved_color = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 65535);
    EXPECT_EQ(retrieved_color->green, 65535);
    EXPECT_EQ(retrieved_color->blue, 65535);
}

// Test that setting border color multiple times returns the last set value
TEST_F(PopplerSigningDataGetBorderColorTest_2375, MultipleSetsBorderColor_2375)
{
    PopplerColor color1;
    color1.red = 100;
    color1.green = 200;
    color1.blue = 50;

    poppler_signing_data_set_border_color(signing_data, &color1);

    PopplerColor color2;
    color2.red = 10;
    color2.green = 20;
    color2.blue = 30;

    poppler_signing_data_set_border_color(signing_data, &color2);

    const PopplerColor *retrieved_color = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 10);
    EXPECT_EQ(retrieved_color->green, 20);
    EXPECT_EQ(retrieved_color->blue, 30);
}

// Test that the returned pointer is consistent (same pointer on multiple calls)
TEST_F(PopplerSigningDataGetBorderColorTest_2375, ReturnsSamePointerOnMultipleCalls_2375)
{
    const PopplerColor *color1 = poppler_signing_data_get_border_color(signing_data);
    const PopplerColor *color2 = poppler_signing_data_get_border_color(signing_data);
    EXPECT_EQ(color1, color2);
}

// Test with a copied signing data
TEST_F(PopplerSigningDataGetBorderColorTest_2375, CopiedSigningDataBorderColor_2375)
{
    PopplerColor color;
    color.red = 42;
    color.green = 84;
    color.blue = 168;

    poppler_signing_data_set_border_color(signing_data, &color);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *retrieved_color = poppler_signing_data_get_border_color(copy);
    ASSERT_NE(retrieved_color, nullptr);
    EXPECT_EQ(retrieved_color->red, 42);
    EXPECT_EQ(retrieved_color->green, 84);
    EXPECT_EQ(retrieved_color->blue, 168);

    poppler_signing_data_free(copy);
}
