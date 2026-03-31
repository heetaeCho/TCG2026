#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Include the necessary poppler headers
extern "C" {
#include "poppler-form-field.h"
#include "poppler-page.h"
}

class PopplerSigningDataSetBorderColorTest_2374 : public ::testing::Test {
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

// Test normal operation: setting border color with valid values
TEST_F(PopplerSigningDataSetBorderColorTest_2374, SetBorderColorNormalValues_2374) {
    PopplerColor color;
    color.red = 100;
    color.green = 200;
    color.blue = 50;

    poppler_signing_data_set_border_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 100);
    EXPECT_EQ(result->green, 200);
    EXPECT_EQ(result->blue, 50);
}

// Test setting border color with zero values
TEST_F(PopplerSigningDataSetBorderColorTest_2374, SetBorderColorZeroValues_2374) {
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_border_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0);
    EXPECT_EQ(result->green, 0);
    EXPECT_EQ(result->blue, 0);
}

// Test setting border color with maximum guint16 values
TEST_F(PopplerSigningDataSetBorderColorTest_2374, SetBorderColorMaxValues_2374) {
    PopplerColor color;
    color.red = 65535;
    color.green = 65535;
    color.blue = 65535;

    poppler_signing_data_set_border_color(signing_data, &color);

    const PopplerColor *result = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 65535);
    EXPECT_EQ(result->green, 65535);
    EXPECT_EQ(result->blue, 65535);
}

// Test overwriting a previously set border color
TEST_F(PopplerSigningDataSetBorderColorTest_2374, OverwriteBorderColor_2374) {
    PopplerColor color1;
    color1.red = 10;
    color1.green = 20;
    color1.blue = 30;

    poppler_signing_data_set_border_color(signing_data, &color1);

    PopplerColor color2;
    color2.red = 255;
    color2.green = 128;
    color2.blue = 64;

    poppler_signing_data_set_border_color(signing_data, &color2);

    const PopplerColor *result = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 255);
    EXPECT_EQ(result->green, 128);
    EXPECT_EQ(result->blue, 64);
}

// Test that passing null signing_data does not crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataSetBorderColorTest_2374, NullSigningDataDoesNotCrash_2374) {
    PopplerColor color;
    color.red = 100;
    color.green = 200;
    color.blue = 50;

    // This should not crash; g_return_if_fail handles null gracefully
    poppler_signing_data_set_border_color(nullptr, &color);
}

// Test that passing null border_color does not crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataSetBorderColorTest_2374, NullBorderColorDoesNotCrash_2374) {
    // This should not crash; g_return_if_fail handles null gracefully
    poppler_signing_data_set_border_color(signing_data, nullptr);
}

// Test that the color is copied (modifying original doesn't affect stored color)
TEST_F(PopplerSigningDataSetBorderColorTest_2374, ColorIsCopiedNotReferenced_2374) {
    PopplerColor color;
    color.red = 42;
    color.green = 84;
    color.blue = 126;

    poppler_signing_data_set_border_color(signing_data, &color);

    // Modify original color after setting
    color.red = 999;
    color.green = 888;
    color.blue = 777;

    const PopplerColor *result = poppler_signing_data_get_border_color(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 42);
    EXPECT_EQ(result->green, 84);
    EXPECT_EQ(result->blue, 126);
}

// Test setting border color multiple times with different values
TEST_F(PopplerSigningDataSetBorderColorTest_2374, MultipleSetOperations_2374) {
    for (int i = 0; i < 10; i++) {
        PopplerColor color;
        color.red = i * 100;
        color.green = i * 200;
        color.blue = i * 50;

        poppler_signing_data_set_border_color(signing_data, &color);

        const PopplerColor *result = poppler_signing_data_get_border_color(signing_data);
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->red, i * 100);
        EXPECT_EQ(result->green, i * 200);
        EXPECT_EQ(result->blue, i * 50);
    }
}

// Test with PopplerSigningData created via copy
TEST_F(PopplerSigningDataSetBorderColorTest_2374, CopiedSigningDataPreservesBorderColor_2374) {
    PopplerColor color;
    color.red = 111;
    color.green = 222;
    color.blue = 333;

    poppler_signing_data_set_border_color(signing_data, &color);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *result = poppler_signing_data_get_border_color(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 111);
    EXPECT_EQ(result->green, 222);
    EXPECT_EQ(result->blue, 333);

    poppler_signing_data_free(copy);
}
