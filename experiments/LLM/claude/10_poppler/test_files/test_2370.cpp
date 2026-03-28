#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Forward declarations based on the interface
typedef struct _PopplerSigningData PopplerSigningData;
typedef struct {
    gdouble x1;
    gdouble y1;
    gdouble x2;
    gdouble y2;
} PopplerRectangle;

typedef struct {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

// Based on the known struct definition
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

void poppler_signing_data_set_font_size(PopplerSigningData *signing_data, gdouble font_size);
}

class PopplerSigningDataSetFontSizeTest_2370 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override {
        signing_data = g_new0(PopplerSigningData, 1);
        signing_data->font_size = 0.0;
    }

    void TearDown() override {
        g_free(signing_data);
    }
};

TEST_F(PopplerSigningDataSetFontSizeTest_2370, SetPositiveFontSize_2370) {
    poppler_signing_data_set_font_size(signing_data, 12.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 12.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, SetLargePositiveFontSize_2370) {
    poppler_signing_data_set_font_size(signing_data, 72.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 72.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, SetSmallPositiveFontSize_2370) {
    poppler_signing_data_set_font_size(signing_data, 0.5);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 0.5);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, SetVerySmallPositiveFontSize_2370) {
    poppler_signing_data_set_font_size(signing_data, 0.001);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 0.001);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, ZeroFontSizeIsIgnored_2370) {
    signing_data->font_size = 10.0;
    poppler_signing_data_set_font_size(signing_data, 0.0);
    // Zero should be rejected (font_size <= 0 returns early)
    EXPECT_DOUBLE_EQ(signing_data->font_size, 10.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, NegativeFontSizeIsIgnored_2370) {
    signing_data->font_size = 10.0;
    poppler_signing_data_set_font_size(signing_data, -5.0);
    // Negative should be rejected
    EXPECT_DOUBLE_EQ(signing_data->font_size, 10.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, NegativeLargeFontSizeIsIgnored_2370) {
    signing_data->font_size = 14.0;
    poppler_signing_data_set_font_size(signing_data, -100.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 14.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, NullSigningDataDoesNotCrash_2370) {
    // Should handle null gracefully via g_return_if_fail
    poppler_signing_data_set_font_size(nullptr, 12.0);
    // No crash means pass
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, OverwriteExistingFontSize_2370) {
    poppler_signing_data_set_font_size(signing_data, 10.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 10.0);
    poppler_signing_data_set_font_size(signing_data, 20.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 20.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, SetFractionalFontSize_2370) {
    poppler_signing_data_set_font_size(signing_data, 11.5);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 11.5);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, SetVeryLargeFontSize_2370) {
    poppler_signing_data_set_font_size(signing_data, 1e10);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 1e10);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, BoundaryJustAboveZero_2370) {
    poppler_signing_data_set_font_size(signing_data, DBL_MIN);
    EXPECT_DOUBLE_EQ(signing_data->font_size, DBL_MIN);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, NegativeZeroIsIgnored_2370) {
    signing_data->font_size = 8.0;
    poppler_signing_data_set_font_size(signing_data, -0.0);
    // -0.0 <= 0 is true, so it should be rejected
    EXPECT_DOUBLE_EQ(signing_data->font_size, 8.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, MultipleUpdatesLastWins_2370) {
    poppler_signing_data_set_font_size(signing_data, 5.0);
    poppler_signing_data_set_font_size(signing_data, 15.0);
    poppler_signing_data_set_font_size(signing_data, 25.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 25.0);
}

TEST_F(PopplerSigningDataSetFontSizeTest_2370, InvalidThenValidFontSize_2370) {
    signing_data->font_size = 0.0;
    poppler_signing_data_set_font_size(signing_data, -1.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 0.0);
    poppler_signing_data_set_font_size(signing_data, 16.0);
    EXPECT_DOUBLE_EQ(signing_data->font_size, 16.0);
}
