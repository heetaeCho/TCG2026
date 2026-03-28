#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
struct PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    // PopplerRectangle signature_rect; // skipping complex types for simplicity
    double signature_rect[4]; // placeholder
    int left_font_size;
    // PopplerColor border_color;
    double border_color[3]; // placeholder
    int border_width;
    // PopplerColor background_color;
    double background_color[3]; // placeholder
    char *field_partial_name;
    char *reason;
    char *location;
    char *image_path;
    char *password;
    char *document_owner_password;
    char *document_user_password;
};

// Declaration of the function under test
extern "C" {
const gchar *poppler_signing_data_get_field_partial_name(const PopplerSigningData *signing_data);
}

class PopplerSigningDataGetFieldPartialNameTest_2381 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override {
        signing_data = g_new0(PopplerSigningData, 1);
    }

    void TearDown() override {
        if (signing_data) {
            g_free(signing_data->field_partial_name);
            g_free(signing_data);
        }
    }
};

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsFieldPartialName_2381) {
    signing_data->field_partial_name = g_strdup("TestFieldName");
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result, "TestFieldName");
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsEmptyStringWhenFieldIsEmpty_2381) {
    signing_data->field_partial_name = g_strdup("");
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result, "");
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsNullWhenFieldIsNull_2381) {
    signing_data->field_partial_name = nullptr;
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    // When field_partial_name is NULL, the function returns it directly (NULL)
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsEmptyStringWhenSigningDataIsNull_2381) {
    // g_return_val_if_fail returns "" when signing_data is nullptr
    const gchar *result = poppler_signing_data_get_field_partial_name(nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsLongFieldName_2381) {
    std::string long_name(1024, 'A');
    signing_data->field_partial_name = g_strdup(long_name.c_str());
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result, long_name.c_str());
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsFieldNameWithSpecialCharacters_2381) {
    signing_data->field_partial_name = g_strdup("Field@#$%^&*()_+-=[]{}|;':\",./<>?");
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result, "Field@#$%^&*()_+-=[]{}|;':\",./<>?");
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsFieldNameWithUTF8Characters_2381) {
    signing_data->field_partial_name = g_strdup("Feld名前フィールド");
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result, "Feld名前フィールド");
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsSamePointer_2381) {
    signing_data->field_partial_name = g_strdup("pointer_check");
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_EQ(result, signing_data->field_partial_name);
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ConsistentMultipleCalls_2381) {
    signing_data->field_partial_name = g_strdup("consistent");
    const gchar *result1 = poppler_signing_data_get_field_partial_name(signing_data);
    const gchar *result2 = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result1, result2);
    EXPECT_EQ(result1, result2);
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsFieldNameWithSpaces_2381) {
    signing_data->field_partial_name = g_strdup("   field with spaces   ");
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result, "   field with spaces   ");
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381, ReturnsFieldNameWithNewlines_2381) {
    signing_data->field_partial_name = g_strdup("field\nwith\nnewlines");
    const gchar *result = poppler_signing_data_get_field_partial_name(signing_data);
    EXPECT_STREQ(result, "field\nwith\nnewlines");
}
