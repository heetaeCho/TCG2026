#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and includes needed for the poppler glib API
extern "C" {
#include "poppler-form-field.h"
}

class PopplerSigningDataGetDocumentUserPasswordTest_2393 : public ::testing::Test {
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

// Test that a newly created signing data returns an empty or default user password
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, DefaultUserPasswordIsEmpty_2393) {
    const gchar *password = poppler_signing_data_get_document_user_password(signing_data);
    ASSERT_NE(password, nullptr);
}

// Test that setting a user password and retrieving it returns the same value
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, SetAndGetUserPassword_2393) {
    const gchar *test_password = "my_user_password";
    poppler_signing_data_set_document_user_password(signing_data, test_password);
    
    const gchar *result = poppler_signing_data_get_document_user_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, test_password);
}

// Test that passing nullptr returns a non-null empty string (as per g_return_val_if_fail)
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, NullSigningDataReturnsEmptyString_2393) {
    // g_return_val_if_fail with nullptr should return ""
    const gchar *result = poppler_signing_data_get_document_user_password(nullptr);
    EXPECT_STREQ(result, "");
}

// Test setting an empty string as user password
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, EmptyUserPassword_2393) {
    poppler_signing_data_set_document_user_password(signing_data, "");
    
    const gchar *result = poppler_signing_data_get_document_user_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test setting user password with special characters
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, SpecialCharactersInPassword_2393) {
    const gchar *special_password = "p@$$w0rd!#%^&*()";
    poppler_signing_data_set_document_user_password(signing_data, special_password);
    
    const gchar *result = poppler_signing_data_get_document_user_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, special_password);
}

// Test setting user password with unicode characters
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, UnicodeUserPassword_2393) {
    const gchar *unicode_password = "пароль密码パスワード";
    poppler_signing_data_set_document_user_password(signing_data, unicode_password);
    
    const gchar *result = poppler_signing_data_get_document_user_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, unicode_password);
}

// Test overwriting user password multiple times
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, OverwriteUserPassword_2393) {
    poppler_signing_data_set_document_user_password(signing_data, "first_password");
    const gchar *result1 = poppler_signing_data_get_document_user_password(signing_data);
    EXPECT_STREQ(result1, "first_password");

    poppler_signing_data_set_document_user_password(signing_data, "second_password");
    const gchar *result2 = poppler_signing_data_get_document_user_password(signing_data);
    EXPECT_STREQ(result2, "second_password");

    poppler_signing_data_set_document_user_password(signing_data, "third_password");
    const gchar *result3 = poppler_signing_data_get_document_user_password(signing_data);
    EXPECT_STREQ(result3, "third_password");
}

// Test with a very long password string
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, VeryLongUserPassword_2393) {
    std::string long_password(4096, 'a');
    poppler_signing_data_set_document_user_password(signing_data, long_password.c_str());
    
    const gchar *result = poppler_signing_data_get_document_user_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_password.c_str());
}

// Test that user password is independent from owner password
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, UserPasswordIndependentFromOwnerPassword_2393) {
    poppler_signing_data_set_document_user_password(signing_data, "user_pass");
    poppler_signing_data_set_document_owner_password(signing_data, "owner_pass");
    
    const gchar *user_result = poppler_signing_data_get_document_user_password(signing_data);
    const gchar *owner_result = poppler_signing_data_get_document_owner_password(signing_data);
    
    EXPECT_STREQ(user_result, "user_pass");
    EXPECT_STREQ(owner_result, "owner_pass");
}

// Test with copied signing data
TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, CopyPreservesUserPassword_2393) {
    poppler_signing_data_set_document_user_password(signing_data, "copy_test_password");
    
    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);
    
    const gchar *result = poppler_signing_data_get_document_user_password(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "copy_test_password");
    
    poppler_signing_data_free(copy);
}
