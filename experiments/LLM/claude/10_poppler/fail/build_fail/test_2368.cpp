#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
// We need the poppler glib headers for the types and functions
extern "C" {
#include "poppler-form-field.h"
#include "poppler-page.h"
}

// If the above headers don't work directly, we may need to use the poppler.h umbrella
// extern "C" {
// #include "poppler.h"
// }

class PopplerSigningDataFontColorTest_2368 : public ::testing::Test {
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

// Test that setting font color with valid parameters works correctly
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorBasic_2368) {
    PopplerColor color;
    color.red = 255;
    color.green = 128;
    color.blue = 64;

    poppler_signing_data_set_font_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 255);
    EXPECT_EQ(result->green, 128);
    EXPECT_EQ(result->blue, 64);
}

// Test setting font color to all zeros
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorAllZeros_2368) {
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_font_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0);
    EXPECT_EQ(result->green, 0);
    EXPECT_EQ(result->blue, 0);
}

// Test setting font color to max values
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorMaxValues_2368) {
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;

    poppler_signing_data_set_font_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 65535);
    EXPECT_EQ(result->green, 65535);
    EXPECT_EQ(result->blue, 65535);
}

// Test overwriting font color with a new value
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorOverwrite_2368) {
    PopplerColor color1;
    color1.red = 100;
    color1.green = 200;
    color1.blue = 300;

    poppler_signing_data_set_font_color(signing_data, &color1);

    PopplerColor color2;
    color2.red = 400;
    color2.green = 500;
    color2.blue = 600;

    poppler_signing_data_set_font_color(signing_data, &color2);

    const PopplerColor *result = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 400);
    EXPECT_EQ(result->green, 500);
    EXPECT_EQ(result->blue, 600);
}

// Test that null signing_data doesn't crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorNullSigningData_2368) {
    PopplerColor color;
    color.red = 10;
    color.green = 20;
    color.blue = 30;

    // Should not crash - g_return_if_fail handles null gracefully
    poppler_signing_data_set_font_color(nullptr, &color);
}

// Test that null font_color doesn't crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorNullColor_2368) {
    // Should not crash - g_return_if_fail handles null gracefully
    poppler_signing_data_set_font_color(signing_data, nullptr);
}

// Test that both null parameters don't crash
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorBothNull_2368) {
    // Should not crash - g_return_if_fail handles null gracefully
    poppler_signing_data_set_font_color(nullptr, nullptr);
}

// Test that the original color struct is copied (not referenced)
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorIsCopy_2368) {
    PopplerColor color;
    color.red = 111;
    color.green = 222;
    color.blue = 333;

    poppler_signing_data_set_font_color(signing_data, &color);

    // Modify the original - should not affect the stored value
    color.red = 999;
    color.green = 888;
    color.blue = 777;

    const PopplerColor *result = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 111);
    EXPECT_EQ(result->green, 222);
    EXPECT_EQ(result->blue, 333);
}

// Test setting font color with only red component
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorRedOnly_2368) {
    PopplerColor color;
    color.red = 65535;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_font_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 65535);
    EXPECT_EQ(result->green, 0);
    EXPECT_EQ(result->blue, 0);
}

// Test multiple sequential set operations
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorMultipleTimes_2368) {
    for (int i = 0; i < 10; i++) {
        PopplerColor color;
        color.red = i * 100;
        color.green = i * 200;
        color.blue = i * 300;

        poppler_signing_data_set_font_color(signing_data, &color);

        const PopplerColor *result = poppler_signing_data_get_font_color(signing_data);
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->red, i * 100);
        EXPECT_EQ(result->green, i * 200);
        EXPECT_EQ(result->blue, i * 300);
    }
}

// Test with poppler_signing_data_copy to verify font color is preserved in copy
TEST_F(PopplerSigningDataFontColorTest_2368, SetFontColorPreservedInCopy_2368) {
    PopplerColor color;
    color.red = 1234;
    color.green = 5678;
    color.blue = 9012;

    poppler_signing_data_set_font_color(signing_data, &color);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *result = poppler_signing_data_get_font_color(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 1234);
    EXPECT_EQ(result->green, 5678);
    EXPECT_EQ(result->blue, 9012);

    poppler_signing_data_free(copy);
}
