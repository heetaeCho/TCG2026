#include <gtest/gtest.h>
#include <glib.h>

// Include the poppler glib header for the public API
#include "poppler-form-field.h"

class PopplerSigningDataSetSignatureTextTest_2362 : public ::testing::Test {
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

// Test setting a normal signature text
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, SetNormalSignatureText_2362) {
    const gchar *text = "John Doe";
    poppler_signing_data_set_signature_text(signing_data, text);
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "John Doe");
}

// Test setting signature text overwrites previous value
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, OverwritePreviousSignatureText_2362) {
    poppler_signing_data_set_signature_text(signing_data, "First Text");
    poppler_signing_data_set_signature_text(signing_data, "Second Text");
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Second Text");
}

// Test setting an empty string as signature text
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, SetEmptyStringSignatureText_2362) {
    poppler_signing_data_set_signature_text(signing_data, "");
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test that the signature text is a copy (not the same pointer)
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, SignatureTextIsCopied_2362) {
    gchar *text = g_strdup("Copied Text");
    poppler_signing_data_set_signature_text(signing_data, text);
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Copied Text");
    // The stored text should be a different pointer (a copy)
    EXPECT_NE(result, text);
    g_free(text);
}

// Test setting signature text with special characters
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, SetSpecialCharactersSignatureText_2362) {
    const gchar *text = "Ünïcödé Tëxt 日本語 🔏";
    poppler_signing_data_set_signature_text(signing_data, text);
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, text);
}

// Test setting a very long signature text
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, SetLongSignatureText_2362) {
    std::string long_text(10000, 'A');
    poppler_signing_data_set_signature_text(signing_data, long_text.c_str());
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_text.c_str());
}

// Test that passing null signing_data does not crash (g_return_if_fail handles it)
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, NullSigningDataDoesNotCrash_2362) {
    // This should trigger g_return_if_fail and simply return without crash
    poppler_signing_data_set_signature_text(nullptr, "Some text");
    // If we reach here, the function handled null gracefully
    SUCCEED();
}

// Test that passing null signature_text does not crash (g_return_if_fail handles it)
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, NullSignatureTextDoesNotCrash_2362) {
    poppler_signing_data_set_signature_text(signing_data, "Initial");
    // This should trigger g_return_if_fail and simply return without crash
    poppler_signing_data_set_signature_text(signing_data, nullptr);
    // The previous value should remain unchanged
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Initial");
}

// Test setting the same value multiple times
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, SetSameValueMultipleTimes_2362) {
    poppler_signing_data_set_signature_text(signing_data, "Repeated");
    poppler_signing_data_set_signature_text(signing_data, "Repeated");
    poppler_signing_data_set_signature_text(signing_data, "Repeated");
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Repeated");
}

// Test setting signature text with newlines
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, SetSignatureTextWithNewlines_2362) {
    const gchar *text = "Line1\nLine2\nLine3";
    poppler_signing_data_set_signature_text(signing_data, text);
    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, text);
}

// Test using a copied signing data preserves signature text independently
TEST_F(PopplerSigningDataSetSignatureTextTest_2362, CopyPreservesSignatureText_2362) {
    poppler_signing_data_set_signature_text(signing_data, "Original");
    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const gchar *copy_result = poppler_signing_data_get_signature_text(copy);
    ASSERT_NE(copy_result, nullptr);
    EXPECT_STREQ(copy_result, "Original");

    // Modify the original, copy should be unaffected
    poppler_signing_data_set_signature_text(signing_data, "Modified");
    const gchar *original_result = poppler_signing_data_get_signature_text(signing_data);
    copy_result = poppler_signing_data_get_signature_text(copy);
    EXPECT_STREQ(original_result, "Modified");
    EXPECT_STREQ(copy_result, "Original");

    poppler_signing_data_free(copy);
}
