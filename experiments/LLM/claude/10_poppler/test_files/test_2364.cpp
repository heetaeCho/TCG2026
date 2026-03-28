#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on provided interface
struct PopplerRectangle {
    double x1, y1, x2, y2;
};

struct PopplerColor {
    guint16 red, green, blue;
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
};

typedef struct _PopplerSigningData PopplerSigningData;

// Declare the function under test
extern "C" {
void poppler_signing_data_set_signature_text_left(PopplerSigningData *signing_data, const gchar *signature_text_left);
}

class PopplerSigningDataSetSignatureTextLeftTest_2364 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override {
        signing_data = g_new0(PopplerSigningData, 1);
        signing_data->destination_filename = nullptr;
        signing_data->signature_text = nullptr;
        signing_data->signature_text_left = nullptr;
        signing_data->field_partial_name = nullptr;
        signing_data->reason = nullptr;
        signing_data->location = nullptr;
        signing_data->image_path = nullptr;
        signing_data->password = nullptr;
        signing_data->document_owner_password = nullptr;
        signing_data->document_user_password = nullptr;
    }

    void TearDown() override {
        if (signing_data) {
            g_free(signing_data->destination_filename);
            g_free(signing_data->signature_text);
            g_free(signing_data->signature_text_left);
            g_free(signing_data->field_partial_name);
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

// Test: Setting signature_text_left on a fresh struct with nullptr initial value
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, SetTextLeftFromNull_2364) {
    ASSERT_EQ(signing_data->signature_text_left, nullptr);
    poppler_signing_data_set_signature_text_left(signing_data, "Hello Left");
    ASSERT_NE(signing_data->signature_text_left, nullptr);
    EXPECT_STREQ(signing_data->signature_text_left, "Hello Left");
}

// Test: Overwriting an existing signature_text_left value
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, OverwriteExistingValue_2364) {
    poppler_signing_data_set_signature_text_left(signing_data, "First Value");
    EXPECT_STREQ(signing_data->signature_text_left, "First Value");

    poppler_signing_data_set_signature_text_left(signing_data, "Second Value");
    EXPECT_STREQ(signing_data->signature_text_left, "Second Value");
}

// Test: Setting the same string content again (different pointer)
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, SetSameContentDifferentPointer_2364) {
    poppler_signing_data_set_signature_text_left(signing_data, "Same Content");
    EXPECT_STREQ(signing_data->signature_text_left, "Same Content");

    // Call again with a different pointer but same content
    const char *another_str = "Same Content";
    poppler_signing_data_set_signature_text_left(signing_data, another_str);
    EXPECT_STREQ(signing_data->signature_text_left, "Same Content");
}

// Test: Setting with the same pointer (self-assignment)
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, SelfAssignmentSamePointer_2364) {
    poppler_signing_data_set_signature_text_left(signing_data, "Test String");
    EXPECT_STREQ(signing_data->signature_text_left, "Test String");

    // Self-assignment: pass the same pointer back
    poppler_signing_data_set_signature_text_left(signing_data, signing_data->signature_text_left);
    // Should still be valid and unchanged
    EXPECT_STREQ(signing_data->signature_text_left, "Test String");
}

// Test: Setting an empty string
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, SetEmptyString_2364) {
    poppler_signing_data_set_signature_text_left(signing_data, "");
    ASSERT_NE(signing_data->signature_text_left, nullptr);
    EXPECT_STREQ(signing_data->signature_text_left, "");
}

// Test: Setting a very long string
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, SetVeryLongString_2364) {
    std::string long_str(10000, 'A');
    poppler_signing_data_set_signature_text_left(signing_data, long_str.c_str());
    ASSERT_NE(signing_data->signature_text_left, nullptr);
    EXPECT_STREQ(signing_data->signature_text_left, long_str.c_str());
}

// Test: String with special characters (UTF-8, newlines, etc.)
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, SetStringWithSpecialCharacters_2364) {
    const char *special = "Héllo\nWörld\t日本語";
    poppler_signing_data_set_signature_text_left(signing_data, special);
    ASSERT_NE(signing_data->signature_text_left, nullptr);
    EXPECT_STREQ(signing_data->signature_text_left, special);
}

// Test: The stored string is a copy, not the same pointer
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, ValueIsCopiedNotAliased_2364) {
    char *original = g_strdup("Original");
    poppler_signing_data_set_signature_text_left(signing_data, original);

    // Verify the value is correct
    EXPECT_STREQ(signing_data->signature_text_left, "Original");
    // The pointer should be different (it's a g_strdup copy)
    EXPECT_NE(signing_data->signature_text_left, original);

    g_free(original);
    // The signing_data value should still be valid
    EXPECT_STREQ(signing_data->signature_text_left, "Original");
}

// Test: Multiple successive overwrites
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, MultipleSetsInSequence_2364) {
    poppler_signing_data_set_signature_text_left(signing_data, "One");
    EXPECT_STREQ(signing_data->signature_text_left, "One");

    poppler_signing_data_set_signature_text_left(signing_data, "Two");
    EXPECT_STREQ(signing_data->signature_text_left, "Two");

    poppler_signing_data_set_signature_text_left(signing_data, "Three");
    EXPECT_STREQ(signing_data->signature_text_left, "Three");

    poppler_signing_data_set_signature_text_left(signing_data, "Four");
    EXPECT_STREQ(signing_data->signature_text_left, "Four");
}

// Test: Null signing_data parameter (should return without crashing due to g_return_if_fail)
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, NullSigningDataDoesNotCrash_2364) {
    // g_return_if_fail will log a warning and return, not crash
    poppler_signing_data_set_signature_text_left(nullptr, "text");
    // If we get here, the function handled the null correctly
}

// Test: Null signature_text_left parameter (should return without crashing due to g_return_if_fail)
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, NullTextLeftDoesNotCrash_2364) {
    signing_data->signature_text_left = g_strdup("Existing");
    poppler_signing_data_set_signature_text_left(signing_data, nullptr);
    // The existing value should remain unchanged since g_return_if_fail triggers
    EXPECT_STREQ(signing_data->signature_text_left, "Existing");
}

// Test: Setting does not affect other fields
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, DoesNotAffectOtherFields_2364) {
    signing_data->signature_text = g_strdup("Main Text");
    signing_data->reason = g_strdup("Reason");

    poppler_signing_data_set_signature_text_left(signing_data, "Left Text");

    EXPECT_STREQ(signing_data->signature_text_left, "Left Text");
    EXPECT_STREQ(signing_data->signature_text, "Main Text");
    EXPECT_STREQ(signing_data->reason, "Reason");
}

// Test: String with embedded null-like characters won't truncate (single byte null is end of string in C)
TEST_F(PopplerSigningDataSetSignatureTextLeftTest_2364, SetStringWithNullTerminator_2364) {
    const char *str = "Before";
    poppler_signing_data_set_signature_text_left(signing_data, str);
    EXPECT_STREQ(signing_data->signature_text_left, "Before");
    EXPECT_EQ(strlen(signing_data->signature_text_left), strlen("Before"));
}
