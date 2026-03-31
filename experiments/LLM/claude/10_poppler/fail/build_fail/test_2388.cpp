#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and includes needed for the poppler signing data API
extern "C" {
#include "poppler-form-field.h"
}

// If the header doesn't provide these, we declare them externally
// Based on the interface, we need these functions:
// - PopplerSigningData* poppler_signing_data_new(void);
// - void poppler_signing_data_free(PopplerSigningData *signing_data);
// - void poppler_signing_data_set_password(PopplerSigningData *signing_data, const gchar *password);
// - const gchar* poppler_signing_data_get_password(const PopplerSigningData *signing_data);

class PopplerSigningDataPasswordTest_2388 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override
    {
        signing_data = poppler_signing_data_new();
        ASSERT_NE(signing_data, nullptr);
    }

    void TearDown() override
    {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }
};

// Test setting a normal password
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordNormal_2388)
{
    poppler_signing_data_set_password(signing_data, "my_secret_password");
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "my_secret_password");
}

// Test setting password replaces the previous one
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordReplacesOld_2388)
{
    poppler_signing_data_set_password(signing_data, "first_password");
    const gchar *result1 = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "first_password");

    poppler_signing_data_set_password(signing_data, "second_password");
    const gchar *result2 = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "second_password");
}

// Test setting an empty string as password
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordEmptyString_2388)
{
    poppler_signing_data_set_password(signing_data, "");
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test setting password with special characters
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordSpecialCharacters_2388)
{
    const gchar *special_pwd = "p@$$w0rd!#%^&*()_+-={}[]|\\:\";<>?,./~`";
    poppler_signing_data_set_password(signing_data, special_pwd);
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, special_pwd);
}

// Test setting password with UTF-8 characters
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordUTF8_2388)
{
    const gchar *utf8_pwd = "пароль密码パスワード";
    poppler_signing_data_set_password(signing_data, utf8_pwd);
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, utf8_pwd);
}

// Test that the password is a copy (not the same pointer)
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordMakesCopy_2388)
{
    gchar *pwd = g_strdup("temporary_password");
    poppler_signing_data_set_password(signing_data, pwd);

    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "temporary_password");

    // The stored password should be a different pointer (a copy)
    EXPECT_NE(result, pwd);

    g_free(pwd);

    // After freeing the original, the stored copy should still be valid
    result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "temporary_password");
}

// Test setting the same password value twice
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordSameValueTwice_2388)
{
    poppler_signing_data_set_password(signing_data, "same_password");
    poppler_signing_data_set_password(signing_data, "same_password");
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "same_password");
}

// Test setting a very long password
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordVeryLong_2388)
{
    std::string long_pwd(10000, 'A');
    poppler_signing_data_set_password(signing_data, long_pwd.c_str());
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_pwd.c_str());
}

// Test that setting password with null signing_data doesn't crash (g_return_if_fail)
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordNullSigningData_2388)
{
    // This should not crash; g_return_if_fail should handle it gracefully
    poppler_signing_data_set_password(nullptr, "password");
}

// Test that setting password with null password doesn't crash (g_return_if_fail)
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordNullPassword_2388)
{
    // This should not crash; g_return_if_fail should handle it gracefully
    poppler_signing_data_set_password(signing_data, nullptr);
}

// Test setting password multiple times in succession
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordMultipleTimes_2388)
{
    for (int i = 0; i < 100; i++) {
        std::string pwd = "password_" + std::to_string(i);
        poppler_signing_data_set_password(signing_data, pwd.c_str());
        const gchar *result = poppler_signing_data_get_password(signing_data);
        ASSERT_NE(result, nullptr);
        EXPECT_STREQ(result, pwd.c_str());
    }
}

// Test password with embedded null-like content (single char)
TEST_F(PopplerSigningDataPasswordTest_2388, SetPasswordSingleChar_2388)
{
    poppler_signing_data_set_password(signing_data, "x");
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "x");
}
