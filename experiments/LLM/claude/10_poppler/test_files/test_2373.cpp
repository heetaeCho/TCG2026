#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
struct PopplerColor {
    guint16 red;
    guint16 green;
    guint16 blue;
};

struct PopplerRectangle {
    gdouble x1;
    gdouble y1;
    gdouble x2;
    gdouble y2;
};

struct _PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    PopplerRectangle signature_rect;
    gdouble left_font_size;
    PopplerColor border_color;
    int border_width;
    PopplerColor background_color;
    char *field_partial_name;
    char *reason;
    char *location;
    char *image_path;
    char *password;
    char *document_owner_password;
    char *document_user_password;
};

typedef struct _PopplerSigningData PopplerSigningData;

// Declaration of the function under test
extern "C" {
gdouble poppler_signing_data_get_left_font_size(const PopplerSigningData *signing_data);
}

class PopplerSigningDataGetLeftFontSizeTest_2373 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns the default value of 12.0
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsDefaultWhenNull_2373)
{
    gdouble result = poppler_signing_data_get_left_font_size(nullptr);
    EXPECT_DOUBLE_EQ(result, 12.0);
}

// Test that a valid signing_data with a specific font size returns that size
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsSetFontSize_2373)
{
    PopplerSigningData signing_data = {};
    signing_data.left_font_size = 24.0;
    gdouble result = poppler_signing_data_get_left_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 24.0);
}

// Test with zero font size
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsZeroFontSize_2373)
{
    PopplerSigningData signing_data = {};
    signing_data.left_font_size = 0.0;
    gdouble result = poppler_signing_data_get_left_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test with negative font size
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsNegativeFontSize_2373)
{
    PopplerSigningData signing_data = {};
    signing_data.left_font_size = -5.0;
    gdouble result = poppler_signing_data_get_left_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, -5.0);
}

// Test with very large font size
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsLargeFontSize_2373)
{
    PopplerSigningData signing_data = {};
    signing_data.left_font_size = 99999.99;
    gdouble result = poppler_signing_data_get_left_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 99999.99);
}

// Test with very small positive font size
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsVerySmallFontSize_2373)
{
    PopplerSigningData signing_data = {};
    signing_data.left_font_size = 0.001;
    gdouble result = poppler_signing_data_get_left_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 0.001);
}

// Test with the default-like value of 12.0 explicitly set
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsDefaultValueWhenExplicitlySet_2373)
{
    PopplerSigningData signing_data = {};
    signing_data.left_font_size = 12.0;
    gdouble result = poppler_signing_data_get_left_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 12.0);
}

// Test with fractional font size
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsFractionalFontSize_2373)
{
    PopplerSigningData signing_data = {};
    signing_data.left_font_size = 10.5;
    gdouble result = poppler_signing_data_get_left_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 10.5);
}
