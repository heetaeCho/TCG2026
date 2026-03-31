#include <gtest/gtest.h>
#include <poppler.h>

class PopplerSigningDataTest_2369 : public ::testing::Test {
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

// Test that getting font color from a valid signing data returns non-null
TEST_F(PopplerSigningDataTest_2369, GetFontColorReturnsNonNull_2369)
{
    const PopplerColor *color = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(color, nullptr);
}

// Test that getting font color from null returns null (with g_return_val_if_fail)
TEST_F(PopplerSigningDataTest_2369, GetFontColorFromNullReturnsNull_2369)
{
    const PopplerColor *color = poppler_signing_data_get_font_color(nullptr);
    EXPECT_EQ(color, nullptr);
}

// Test that setting font color and then getting it returns the correct values
TEST_F(PopplerSigningDataTest_2369, SetAndGetFontColor_2369)
{
    PopplerColor color;
    color.red = 0xFFFF;
    color.green = 0x0000;
    color.blue = 0x8080;

    poppler_signing_data_set_font_color(signing_data, &color);

    const PopplerColor *retrieved = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0xFFFF);
    EXPECT_EQ(retrieved->green, 0x0000);
    EXPECT_EQ(retrieved->blue, 0x8080);
}

// Test default font color values on a newly created signing data
TEST_F(PopplerSigningDataTest_2369, DefaultFontColorValues_2369)
{
    const PopplerColor *color = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(color, nullptr);
    // Default color should be some defined value (typically red=0, green=0, blue=0 i.e. black)
    // We just verify it's accessible without crash; exact defaults depend on implementation
}

// Test setting font color with zero values
TEST_F(PopplerSigningDataTest_2369, SetFontColorAllZeros_2369)
{
    PopplerColor color;
    color.red = 0;
    color.green = 0;
    color.blue = 0;

    poppler_signing_data_set_font_color(signing_data, &color);

    const PopplerColor *retrieved = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0);
    EXPECT_EQ(retrieved->green, 0);
    EXPECT_EQ(retrieved->blue, 0);
}

// Test setting font color with max values
TEST_F(PopplerSigningDataTest_2369, SetFontColorMaxValues_2369)
{
    PopplerColor color;
    color.red = 0xFFFF;
    color.green = 0xFFFF;
    color.blue = 0xFFFF;

    poppler_signing_data_set_font_color(signing_data, &color);

    const PopplerColor *retrieved = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 0xFFFF);
    EXPECT_EQ(retrieved->green, 0xFFFF);
    EXPECT_EQ(retrieved->blue, 0xFFFF);
}

// Test that setting font color multiple times returns the last set value
TEST_F(PopplerSigningDataTest_2369, SetFontColorMultipleTimes_2369)
{
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

    const PopplerColor *retrieved = poppler_signing_data_get_font_color(signing_data);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 400);
    EXPECT_EQ(retrieved->green, 500);
    EXPECT_EQ(retrieved->blue, 600);
}

// Test with a copied signing data
TEST_F(PopplerSigningDataTest_2369, GetFontColorFromCopiedData_2369)
{
    PopplerColor color;
    color.red = 1234;
    color.green = 5678;
    color.blue = 9012;

    poppler_signing_data_set_font_color(signing_data, &color);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *retrieved = poppler_signing_data_get_font_color(copy);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->red, 1234);
    EXPECT_EQ(retrieved->green, 5678);
    EXPECT_EQ(retrieved->blue, 9012);

    poppler_signing_data_free(copy);
}
