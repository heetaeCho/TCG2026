#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on provided information
extern "C" {

typedef struct {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

typedef struct {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

typedef struct _PopplerSigningData {
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
} PopplerSigningData;

void poppler_signing_data_set_field_partial_name(PopplerSigningData *signing_data, const gchar *field_partial_name);

} // extern "C"

class PopplerSigningDataSetFieldPartialNameTest_2380 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override {
        signing_data = g_new0(PopplerSigningData, 1);
        signing_data->field_partial_name = nullptr;
    }

    void TearDown() override {
        if (signing_data) {
            g_free(signing_data->field_partial_name);
            g_free(signing_data->destination_filename);
            g_free(signing_data->signature_text);
            g_free(signing_data->signature_text_left);
            g_free(signing_data->reason);
            g_free(signing_data->location);
            g_free(signing_data->image_path);
            g_free(signing_data->password);
            g_free(signing_data->document_owner_password);
            g_free(signing_data->document_user_password);
            g_free(signing_data);
        }
    }
};

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_NormalString_2380) {
    poppler_signing_data_set_field_partial_name(signing_data, "test_field");
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, "test_field");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_OverwriteExisting_2380) {
    poppler_signing_data_set_field_partial_name(signing_data, "first_value");
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, "first_value");

    poppler_signing_data_set_field_partial_name(signing_data, "second_value");
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, "second_value");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_EmptyString_2380) {
    poppler_signing_data_set_field_partial_name(signing_data, "");
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, "");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_LongString_2380) {
    std::string long_name(1024, 'a');
    poppler_signing_data_set_field_partial_name(signing_data, long_name.c_str());
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, long_name.c_str());
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_StringIsCopied_2380) {
    char buffer[] = "original";
    poppler_signing_data_set_field_partial_name(signing_data, buffer);
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, "original");

    // Modify the original buffer - the stored value should remain unchanged
    buffer[0] = 'X';
    EXPECT_STREQ(signing_data->field_partial_name, "original");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_NullSigningData_2380) {
    // Should not crash - g_return_if_fail should handle null signing_data
    poppler_signing_data_set_field_partial_name(nullptr, "test");
    // If we reach here without crash, the guard worked
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_NullFieldName_2380) {
    // Should not crash - g_return_if_fail should handle null field_partial_name
    poppler_signing_data_set_field_partial_name(signing_data, nullptr);
    // field_partial_name should remain unchanged (null)
    EXPECT_EQ(signing_data->field_partial_name, nullptr);
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_MultipleOverwrites_2380) {
    for (int i = 0; i < 100; i++) {
        std::string name = "field_" + std::to_string(i);
        poppler_signing_data_set_field_partial_name(signing_data, name.c_str());
        ASSERT_NE(signing_data->field_partial_name, nullptr);
        EXPECT_STREQ(signing_data->field_partial_name, name.c_str());
    }
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_SpecialCharacters_2380) {
    poppler_signing_data_set_field_partial_name(signing_data, "field with spaces & special chars!@#$%");
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, "field with spaces & special chars!@#$%");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_UTF8String_2380) {
    const char *utf8_name = "フィールド名";
    poppler_signing_data_set_field_partial_name(signing_data, utf8_name);
    ASSERT_NE(signing_data->field_partial_name, nullptr);
    EXPECT_STREQ(signing_data->field_partial_name, utf8_name);
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetFieldPartialName_SetSameValueTwice_2380) {
    poppler_signing_data_set_field_partial_name(signing_data, "same_value");
    EXPECT_STREQ(signing_data->field_partial_name, "same_value");

    poppler_signing_data_set_field_partial_name(signing_data, "same_value");
    EXPECT_STREQ(signing_data->field_partial_name, "same_value");
}
