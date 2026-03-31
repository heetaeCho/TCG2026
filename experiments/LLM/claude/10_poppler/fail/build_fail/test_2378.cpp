#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Include the necessary poppler headers
extern "C" {
#include "poppler-form-field.h"
#include "poppler-page.h"
}

class PopplerSigningDataSetBackgroundColorTest_2378 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
        }
    }
};

// Test normal operation: setting a background color with specific RGB values
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, SetValidBackgroundColor_2378)
{
    PopplerColor color;
    color.red = 255;
    color.green = 128;
    color.blue = 64;

    poppler_signing_data_set_background_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 255);
    EXPECT_EQ(result->green, 128);
    EXPECT_EQ(result->blue, 64);
}

// Test setting background color to black (all zeros)
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, SetBlackBackgroundColor_2378)
{
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_background_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0);
    EXPECT_EQ(result->green, 0);
    EXPECT_EQ(result->blue, 0);
}

// Test setting background color to white (max values)
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, SetWhiteBackgroundColor_2378)
{
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;

    poppler_signing_data_set_background_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 65535);
    EXPECT_EQ(result->green, 65535);
    EXPECT_EQ(result->blue, 65535);
}

// Test overwriting a previously set background color
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, OverwriteBackgroundColor_2378)
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

    const PopplerColor *result = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 400);
    EXPECT_EQ(result->green, 500);
    EXPECT_EQ(result->blue, 600);
}

// Test that passing null signing_data does not crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, NullSigningDataDoesNotCrash_2378)
{
    PopplerColor color;
    color.red = 1;
    color.green = 2;
    color.blue = 3;

    // Should not crash, just return silently due to g_return_if_fail
    poppler_signing_data_set_background_color(nullptr, &color);
}

// Test that passing null color does not crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, NullColorDoesNotCrash_2378)
{
    // Should not crash, just return silently due to g_return_if_fail
    poppler_signing_data_set_background_color(signing_data, nullptr);
}

// Test that passing both null does not crash
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, BothNullDoesNotCrash_2378)
{
    poppler_signing_data_set_background_color(nullptr, nullptr);
}

// Test that the set color is independent of the original color struct (copy semantics)
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, CopySemantics_2378)
{
    PopplerColor color;
    color.red = 10;
    color.green = 20;
    color.blue = 30;

    poppler_signing_data_set_background_color(signing_data, &color);

    // Modify original color after setting
    color.red = 999;
    color.green = 888;
    color.blue = 777;

    // The stored color should not be affected
    const PopplerColor *result = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 10);
    EXPECT_EQ(result->green, 20);
    EXPECT_EQ(result->blue, 30);
}

// Test setting background color with only red channel
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, SetRedOnlyColor_2378)
{
    PopplerColor color;
    color.red = 65535;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_background_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 65535);
    EXPECT_EQ(result->green, 0);
    EXPECT_EQ(result->blue, 0);
}

// Test multiple successive overwrites
TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, MultipleOverwrites_2378)
{
    for (int i = 0; i < 100; i++) {
        PopplerColor color;
        color.red = i;
        color.green = i * 2;
        color.blue = i * 3;
        poppler_signing_data_set_background_color(signing_data, &color);
    }

    const PopplerColor *result = poppler_signing_data_get_background_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 99);
    EXPECT_EQ(result->green, 198);
    EXPECT_EQ(result->blue, 297);
}
