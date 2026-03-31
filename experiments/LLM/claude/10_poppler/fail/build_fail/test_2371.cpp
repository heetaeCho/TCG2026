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
    int left_font_size;
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
    gdouble font_size;
};

typedef struct _PopplerSigningData PopplerSigningData;

// Declaration of the function under test
extern "C" {
gdouble poppler_signing_data_get_font_size(const PopplerSigningData *signing_data);
}

class PopplerSigningDataGetFontSizeTest_2371 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns the default value of 20.0
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsDefaultWhenNull_2371)
{
    gdouble result = poppler_signing_data_get_font_size(nullptr);
    EXPECT_DOUBLE_EQ(result, 20.0);
}

// Test that a valid signing data with a specific font size returns that size
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsSetFontSize_2371)
{
    PopplerSigningData signing_data = {};
    signing_data.font_size = 12.5;

    gdouble result = poppler_signing_data_get_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 12.5);
}

// Test with font size of 0.0
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsZeroFontSize_2371)
{
    PopplerSigningData signing_data = {};
    signing_data.font_size = 0.0;

    gdouble result = poppler_signing_data_get_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test with a negative font size
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsNegativeFontSize_2371)
{
    PopplerSigningData signing_data = {};
    signing_data.font_size = -5.0;

    gdouble result = poppler_signing_data_get_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, -5.0);
}

// Test with a very large font size
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsLargeFontSize_2371)
{
    PopplerSigningData signing_data = {};
    signing_data.font_size = 99999.99;

    gdouble result = poppler_signing_data_get_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 99999.99);
}

// Test with a very small positive font size
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsVerySmallFontSize_2371)
{
    PopplerSigningData signing_data = {};
    signing_data.font_size = 0.001;

    gdouble result = poppler_signing_data_get_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 0.001);
}

// Test with the default font size value (20.0) explicitly set
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsDefaultFontSizeWhenExplicitlySet_2371)
{
    PopplerSigningData signing_data = {};
    signing_data.font_size = 20.0;

    gdouble result = poppler_signing_data_get_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 20.0);
}

// Test with font size set to 1.0
TEST_F(PopplerSigningDataGetFontSizeTest_2371, ReturnsUnitFontSize_2371)
{
    PopplerSigningData signing_data = {};
    signing_data.font_size = 1.0;

    gdouble result = poppler_signing_data_get_font_size(&signing_data);
    EXPECT_DOUBLE_EQ(result, 1.0);
}
