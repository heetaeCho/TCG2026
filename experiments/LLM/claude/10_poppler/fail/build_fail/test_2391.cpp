#include <glib.h>
#include <gtest/gtest.h>

// Include the header that declares PopplerSigningData and related functions
extern "C" {
#include "poppler-form-field.h"
}

// If the header doesn't expose the struct internals, we rely on the public API
// We need the creation/destruction and setter/getter functions from the public API

class PopplerSigningDataGetDocumentOwnerPasswordTest_2391 : public ::testing::Test {
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

// Test that a newly created PopplerSigningData returns nullptr for document_owner_password
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, DefaultValueIsNull_2391) {
    const gchar *result = poppler_signing_data_get_document_owner_password(signing_data);
    EXPECT_EQ(result, nullptr);
}

// Test that after setting the document owner password, the getter returns the correct value
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, ReturnsSetPassword_2391) {
    poppler_signing_data_set_document_owner_password(signing_data, "owner_pass_123");
    const gchar *result = poppler_signing_data_get_document_owner_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "owner_pass_123");
}

// Test that passing nullptr as signing_data returns nullptr (g_return_val_if_fail guard)
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, NullSigningDataReturnsNull_2391) {
    const gchar *result = poppler_signing_data_get_document_owner_password(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test setting an empty string as the document owner password
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, EmptyStringPassword_2391) {
    poppler_signing_data_set_document_owner_password(signing_data, "");
    const gchar *result = poppler_signing_data_get_document_owner_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test overwriting the document owner password with a new value
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, OverwritePassword_2391) {
    poppler_signing_data_set_document_owner_password(signing_data, "first_password");
    const gchar *result1 = poppler_signing_data_get_document_owner_password(signing_data);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "first_password");

    poppler_signing_data_set_document_owner_password(signing_data, "second_password");
    const gchar *result2 = poppler_signing_data_get_document_owner_password(signing_data);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "second_password");
}

// Test setting the document owner password to nullptr after previously setting it
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, SetToNullAfterValue_2391) {
    poppler_signing_data_set_document_owner_password(signing_data, "some_password");
    const gchar *result1 = poppler_signing_data_get_document_owner_password(signing_data);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "some_password");

    poppler_signing_data_set_document_owner_password(signing_data, nullptr);
    const gchar *result2 = poppler_signing_data_get_document_owner_password(signing_data);
    EXPECT_EQ(result2, nullptr);
}

// Test with a long password string
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, LongPassword_2391) {
    std::string long_password(1024, 'A');
    poppler_signing_data_set_document_owner_password(signing_data, long_password.c_str());
    const gchar *result = poppler_signing_data_get_document_owner_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_password.c_str());
}

// Test with special characters in the password
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, SpecialCharactersPassword_2391) {
    const gchar *special_pass = "p@$$w0rd!#%^&*()_+-=[]{}|;':\",./<>?";
    poppler_signing_data_set_document_owner_password(signing_data, special_pass);
    const gchar *result = poppler_signing_data_get_document_owner_password(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, special_pass);
}

// Test with a copied signing data to verify the password is properly copied
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, CopiedSigningDataRetainsPassword_2391) {
    poppler_signing_data_set_document_owner_password(signing_data, "copy_test_password");
    
    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);
    
    const gchar *result = poppler_signing_data_get_document_owner_password(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "copy_test_password");
    
    poppler_signing_data_free(copy);
}

// Test that getting the password multiple times returns consistent results
TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391, ConsistentMultipleGets_2391) {
    poppler_signing_data_set_document_owner_password(signing_data, "consistent_pass");
    
    const gchar *result1 = poppler_signing_data_get_document_owner_password(signing_data);
    const gchar *result2 = poppler_signing_data_get_document_owner_password(signing_data);
    const gchar *result3 = poppler_signing_data_get_document_owner_password(signing_data);
    
    EXPECT_STREQ(result1, "consistent_pass");
    EXPECT_STREQ(result2, "consistent_pass");
    EXPECT_STREQ(result3, "consistent_pass");
    // The pointer should be the same since it returns internal storage
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}
