#include <glib.h>
#include <gtest/gtest.h>

// Include the poppler glib header for the public API
#include "poppler-form-field.h"

class PopplerSigningDataPasswordTest_2389 : public ::testing::Test {
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

// Test that getting password from a newly created signing data returns nullptr or empty
TEST_F(PopplerSigningDataPasswordTest_2389, GetPasswordFromNewSigningData_2389)
{
    const gchar *password = poppler_signing_data_get_password(signing_data);
    // A newly created signing data should have no password set (nullptr)
    EXPECT_EQ(password, nullptr);
}

// Test that setting and getting a password works correctly
TEST_F(PopplerSigningDataPasswordTest_2389, SetAndGetPassword_2389)
{
    const gchar *test_password = "my_secret_password";
    poppler_signing_data_set_password(signing_data, test_password);

    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, test_password);
}

// Test that passing nullptr signing_data returns nullptr
TEST_F(PopplerSigningDataPasswordTest_2389, GetPasswordFromNullSigningData_2389)
{
    const gchar *result = poppler_signing_data_get_password(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test setting password to an empty string
TEST_F(PopplerSigningDataPasswordTest_2389, SetEmptyPassword_2389)
{
    poppler_signing_data_set_password(signing_data, "");

    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test setting password to nullptr
TEST_F(PopplerSigningDataPasswordTest_2389, SetNullPassword_2389)
{
    // First set a valid password
    poppler_signing_data_set_password(signing_data, "initial_password");
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "initial_password");

    // Now set to nullptr
    poppler_signing_data_set_password(signing_data, nullptr);
    result = poppler_signing_data_get_password(signing_data);
    EXPECT_EQ(result, nullptr);
}

// Test overwriting password with a new value
TEST_F(PopplerSigningDataPasswordTest_2389, OverwritePassword_2389)
{
    poppler_signing_data_set_password(signing_data, "first_password");
    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "first_password");

    poppler_signing_data_set_password(signing_data, "second_password");
    result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "second_password");
}

// Test with a long password string
TEST_F(PopplerSigningDataPasswordTest_2389, LongPassword_2389)
{
    std::string long_password(1024, 'A');
    poppler_signing_data_set_password(signing_data, long_password.c_str());

    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_password.c_str());
}

// Test with special characters in password
TEST_F(PopplerSigningDataPasswordTest_2389, SpecialCharactersPassword_2389)
{
    const gchar *special_password = "p@$$w0rd!#%^&*()_+-={}[]|\\:\";<>?,./~`";
    poppler_signing_data_set_password(signing_data, special_password);

    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, special_password);
}

// Test with UTF-8 characters in password
TEST_F(PopplerSigningDataPasswordTest_2389, Utf8Password_2389)
{
    const gchar *utf8_password = "пароль密码パスワード";
    poppler_signing_data_set_password(signing_data, utf8_password);

    const gchar *result = poppler_signing_data_get_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, utf8_password);
}

// Test that password is independent from a copied signing data
TEST_F(PopplerSigningDataPasswordTest_2389, CopySigningDataPassword_2389)
{
    poppler_signing_data_set_password(signing_data, "original_password");

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const gchar *original_result = poppler_signing_data_get_password(signing_data);
    const gchar *copy_result = poppler_signing_data_get_password(copy);

    ASSERT_NE(original_result, nullptr);
    ASSERT_NE(copy_result, nullptr);
    EXPECT_STREQ(original_result, copy_result);

    // Modify the copy and verify original is unchanged
    poppler_signing_data_set_password(copy, "modified_password");
    original_result = poppler_signing_data_get_password(signing_data);
    copy_result = poppler_signing_data_get_password(copy);

    EXPECT_STREQ(original_result, "original_password");
    EXPECT_STREQ(copy_result, "modified_password");

    poppler_signing_data_free(copy);
}
