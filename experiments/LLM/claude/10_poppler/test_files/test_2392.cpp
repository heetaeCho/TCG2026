#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
struct _PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    // PopplerRectangle signature_rect;
    int left_font_size;
    // PopplerColor border_color;
    int border_width;
    // PopplerColor background_color;
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
void poppler_signing_data_set_document_user_password(PopplerSigningData *signing_data, const gchar *document_user_password);
}

class PopplerSigningDataSetDocumentUserPasswordTest_2392 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override
    {
        signing_data = g_new0(PopplerSigningData, 1);
        signing_data->destination_filename = nullptr;
        signing_data->signature_text = nullptr;
        signing_data->signature_text_left = nullptr;
        signing_data->left_font_size = 0;
        signing_data->border_width = 0;
        signing_data->field_partial_name = nullptr;
        signing_data->reason = nullptr;
        signing_data->location = nullptr;
        signing_data->image_path = nullptr;
        signing_data->password = nullptr;
        signing_data->document_owner_password = nullptr;
        signing_data->document_user_password = nullptr;
    }

    void TearDown() override
    {
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

// Test setting password when document_user_password is initially nullptr
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, SetPasswordFromNull_2392)
{
    ASSERT_EQ(signing_data->document_user_password, nullptr);
    poppler_signing_data_set_document_user_password(signing_data, "mypassword");
    ASSERT_NE(signing_data->document_user_password, nullptr);
    EXPECT_STREQ(signing_data->document_user_password, "mypassword");
}

// Test overwriting an existing password with a new one
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, OverwriteExistingPassword_2392)
{
    poppler_signing_data_set_document_user_password(signing_data, "firstpassword");
    ASSERT_STREQ(signing_data->document_user_password, "firstpassword");

    poppler_signing_data_set_document_user_password(signing_data, "secondpassword");
    EXPECT_STREQ(signing_data->document_user_password, "secondpassword");
}

// Test setting the same string value again (different pointer, same content)
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, SetSameValueDifferentPointer_2392)
{
    poppler_signing_data_set_document_user_password(signing_data, "password123");
    ASSERT_STREQ(signing_data->document_user_password, "password123");

    // Set again with same content but different pointer
    const char *new_password = "password123";
    poppler_signing_data_set_document_user_password(signing_data, new_password);
    EXPECT_STREQ(signing_data->document_user_password, "password123");
}

// Test self-assignment (same pointer) — should be a no-op
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, SelfAssignmentNoOp_2392)
{
    poppler_signing_data_set_document_user_password(signing_data, "selftest");
    ASSERT_STREQ(signing_data->document_user_password, "selftest");

    // Pass the same pointer back — the function should detect and return early
    const gchar *same_ptr = signing_data->document_user_password;
    poppler_signing_data_set_document_user_password(signing_data, same_ptr);
    EXPECT_STREQ(signing_data->document_user_password, "selftest");
    // Verify the pointer hasn't changed (no reallocation)
    EXPECT_EQ(signing_data->document_user_password, same_ptr);
}

// Test with empty string
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, SetEmptyString_2392)
{
    poppler_signing_data_set_document_user_password(signing_data, "");
    ASSERT_NE(signing_data->document_user_password, nullptr);
    EXPECT_STREQ(signing_data->document_user_password, "");
}

// Test with a very long string
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, SetLongString_2392)
{
    std::string long_password(10000, 'A');
    poppler_signing_data_set_document_user_password(signing_data, long_password.c_str());
    ASSERT_NE(signing_data->document_user_password, nullptr);
    EXPECT_STREQ(signing_data->document_user_password, long_password.c_str());
}

// Test with special characters
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, SetSpecialCharacters_2392)
{
    const char *special = "p@$$w0rd!#%^&*()_+{}|:<>?";
    poppler_signing_data_set_document_user_password(signing_data, special);
    ASSERT_NE(signing_data->document_user_password, nullptr);
    EXPECT_STREQ(signing_data->document_user_password, special);
}

// Test with UTF-8 characters
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, SetUTF8String_2392)
{
    const char *utf8_password = "пароль密码パスワード";
    poppler_signing_data_set_document_user_password(signing_data, utf8_password);
    ASSERT_NE(signing_data->document_user_password, nullptr);
    EXPECT_STREQ(signing_data->document_user_password, utf8_password);
}

// Test that the password is a copy (not the same pointer)
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, PasswordIsCopied_2392)
{
    char *original = g_strdup("copyme");
    poppler_signing_data_set_document_user_password(signing_data, original);
    EXPECT_STREQ(signing_data->document_user_password, "copyme");
    // The stored pointer should be different from the original
    EXPECT_NE(signing_data->document_user_password, original);
    g_free(original);
}

// Test that null signing_data doesn't crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, NullSigningDataDoesNotCrash_2392)
{
    // This should trigger g_return_if_fail and return without crashing
    poppler_signing_data_set_document_user_password(nullptr, "password");
    // If we reach here, the function handled null gracefully
    SUCCEED();
}

// Test that null password doesn't crash (g_return_if_fail should handle it)
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, NullPasswordDoesNotCrash_2392)
{
    poppler_signing_data_set_document_user_password(signing_data, "initial");
    // This should trigger g_return_if_fail and return without modifying anything
    poppler_signing_data_set_document_user_password(signing_data, nullptr);
    // The password should remain unchanged
    EXPECT_STREQ(signing_data->document_user_password, "initial");
}

// Test multiple sequential updates
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, MultipleSequentialUpdates_2392)
{
    for (int i = 0; i < 100; i++) {
        std::string password = "pass" + std::to_string(i);
        poppler_signing_data_set_document_user_password(signing_data, password.c_str());
        EXPECT_STREQ(signing_data->document_user_password, password.c_str());
    }
}

// Test that setting password doesn't affect other fields
TEST_F(PopplerSigningDataSetDocumentUserPasswordTest_2392, DoesNotAffectOtherFields_2392)
{
    signing_data->document_owner_password = g_strdup("owner_pass");
    signing_data->password = g_strdup("cert_pass");

    poppler_signing_data_set_document_user_password(signing_data, "user_pass");

    EXPECT_STREQ(signing_data->document_user_password, "user_pass");
    EXPECT_STREQ(signing_data->document_owner_password, "owner_pass");
    EXPECT_STREQ(signing_data->password, "cert_pass");
}
