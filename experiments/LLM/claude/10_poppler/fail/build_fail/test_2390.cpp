#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
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

void poppler_signing_data_set_document_owner_password(PopplerSigningData *signing_data, const gchar *document_owner_password);

} // extern "C"

class PopplerSigningDataOwnerPasswordTest_2390 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override {
        signing_data = g_new0(PopplerSigningData, 1);
        signing_data->document_owner_password = nullptr;
    }

    void TearDown() override {
        g_clear_pointer(&signing_data->destination_filename, g_free);
        g_clear_pointer(&signing_data->signature_text, g_free);
        g_clear_pointer(&signing_data->signature_text_left, g_free);
        g_clear_pointer(&signing_data->field_partial_name, g_free);
        g_clear_pointer(&signing_data->reason, g_free);
        g_clear_pointer(&signing_data->location, g_free);
        g_clear_pointer(&signing_data->image_path, g_free);
        g_clear_pointer(&signing_data->password, g_free);
        g_clear_pointer(&signing_data->document_owner_password, g_free);
        g_clear_pointer(&signing_data->document_user_password, g_free);
        g_free(signing_data);
    }
};

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetPasswordNormal_2390) {
    poppler_signing_data_set_document_owner_password(signing_data, "my_owner_pass");
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, "my_owner_pass");
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetPasswordCreatesNewCopy_2390) {
    const char *original = "test_password";
    poppler_signing_data_set_document_owner_password(signing_data, original);
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    // The stored password should be a copy, not the same pointer
    EXPECT_NE(signing_data->document_owner_password, original);
    EXPECT_STREQ(signing_data->document_owner_password, "test_password");
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetPasswordOverwritesPrevious_2390) {
    poppler_signing_data_set_document_owner_password(signing_data, "first_password");
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, "first_password");

    poppler_signing_data_set_document_owner_password(signing_data, "second_password");
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, "second_password");
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetEmptyString_2390) {
    poppler_signing_data_set_document_owner_password(signing_data, "");
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, "");
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetSamePointerDoesNotCrash_2390) {
    poppler_signing_data_set_document_owner_password(signing_data, "initial");
    ASSERT_NE(signing_data->document_owner_password, nullptr);

    // Set the same pointer — the function should detect this and return early
    const gchar *same_ptr = signing_data->document_owner_password;
    poppler_signing_data_set_document_owner_password(signing_data, same_ptr);
    EXPECT_STREQ(signing_data->document_owner_password, "initial");
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, NullSigningDataDoesNotCrash_2390) {
    // Should trigger g_return_if_fail and not crash
    poppler_signing_data_set_document_owner_password(nullptr, "some_password");
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, NullPasswordDoesNotCrash_2390) {
    // Should trigger g_return_if_fail and not crash
    poppler_signing_data_set_document_owner_password(signing_data, nullptr);
    // The original value should remain unchanged (null since SetUp sets it to nullptr)
    EXPECT_EQ(signing_data->document_owner_password, nullptr);
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, NullPasswordDoesNotOverwriteExisting_2390) {
    poppler_signing_data_set_document_owner_password(signing_data, "existing");
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, "existing");

    // Passing null password should be rejected by g_return_if_fail
    poppler_signing_data_set_document_owner_password(signing_data, nullptr);
    // Existing value should remain
    EXPECT_STREQ(signing_data->document_owner_password, "existing");
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetLongPassword_2390) {
    std::string long_password(10000, 'A');
    poppler_signing_data_set_document_owner_password(signing_data, long_password.c_str());
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, long_password.c_str());
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetPasswordWithSpecialCharacters_2390) {
    const char *special = "p@$$w0rd!#%^&*()_+{}|:<>?";
    poppler_signing_data_set_document_owner_password(signing_data, special);
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, special);
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, SetPasswordWithUTF8Characters_2390) {
    const char *utf8_pass = "пароль密码パスワード";
    poppler_signing_data_set_document_owner_password(signing_data, utf8_pass);
    ASSERT_NE(signing_data->document_owner_password, nullptr);
    EXPECT_STREQ(signing_data->document_owner_password, utf8_pass);
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, MultipleOverwrites_2390) {
    for (int i = 0; i < 100; i++) {
        std::string pass = "password_" + std::to_string(i);
        poppler_signing_data_set_document_owner_password(signing_data, pass.c_str());
        ASSERT_NE(signing_data->document_owner_password, nullptr);
        EXPECT_STREQ(signing_data->document_owner_password, pass.c_str());
    }
}

TEST_F(PopplerSigningDataOwnerPasswordTest_2390, BothNullDoesNotCrash_2390) {
    // Both arguments null
    poppler_signing_data_set_document_owner_password(nullptr, nullptr);
}
