#include <gtest/gtest.h>
#include <glib.h>

// Include the poppler glib header for the public API
extern "C" {
#include "poppler-form-field.h"
}

class PopplerSigningDataGetSignatureTextLeftTest_2365 : public ::testing::Test {
protected:
    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }

    PopplerSigningData *signing_data = nullptr;
};

// Test that getting signature_text_left from a newly created signing data returns nullptr or empty
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, DefaultValueIsNullOrEmpty_2365)
{
    const gchar *result = poppler_signing_data_get_signature_text_left(signing_data);
    // A newly created signing data should have nullptr for signature_text_left
    EXPECT_EQ(result, nullptr);
}

// Test that passing nullptr returns nullptr (guarded by g_return_val_if_fail)
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, NullSigningDataReturnsNull_2365)
{
    const gchar *result = poppler_signing_data_get_signature_text_left(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that after setting signature_text_left, the getter returns the correct value
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, ReturnsSetValue_2365)
{
    const gchar *test_text = "Left side text";
    poppler_signing_data_set_signature_text_left(signing_data, test_text);
    const gchar *result = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, test_text);
}

// Test setting signature_text_left to an empty string
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, EmptyStringValue_2365)
{
    poppler_signing_data_set_signature_text_left(signing_data, "");
    const gchar *result = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test overwriting signature_text_left with a new value
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, OverwriteValue_2365)
{
    poppler_signing_data_set_signature_text_left(signing_data, "First value");
    const gchar *result1 = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "First value");

    poppler_signing_data_set_signature_text_left(signing_data, "Second value");
    const gchar *result2 = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "Second value");
}

// Test setting signature_text_left to nullptr resets it
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, SetToNullResetsValue_2365)
{
    poppler_signing_data_set_signature_text_left(signing_data, "Some text");
    const gchar *result = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Some text");

    poppler_signing_data_set_signature_text_left(signing_data, nullptr);
    result = poppler_signing_data_get_signature_text_left(signing_data);
    EXPECT_EQ(result, nullptr);
}

// Test with a long string value
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, LongStringValue_2365)
{
    std::string long_text(1024, 'A');
    poppler_signing_data_set_signature_text_left(signing_data, long_text.c_str());
    const gchar *result = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_text.c_str());
}

// Test with UTF-8 characters
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, Utf8StringValue_2365)
{
    const gchar *utf8_text = "Ünïcödé tëxt ñ 你好";
    poppler_signing_data_set_signature_text_left(signing_data, utf8_text);
    const gchar *result = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, utf8_text);
}

// Test that copied signing data preserves signature_text_left
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, CopiedDataPreservesValue_2365)
{
    poppler_signing_data_set_signature_text_left(signing_data, "Copy test");
    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const gchar *result = poppler_signing_data_get_signature_text_left(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Copy test");

    poppler_signing_data_free(copy);
}

// Test with special characters
TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365, SpecialCharacters_2365)
{
    const gchar *special_text = "Line1\nLine2\tTabbed\0Hidden";
    poppler_signing_data_set_signature_text_left(signing_data, special_text);
    const gchar *result = poppler_signing_data_get_signature_text_left(signing_data);
    ASSERT_NE(result, nullptr);
    // Note: C string stops at \0, so only up to "Hidden" won't be included
    EXPECT_STREQ(result, special_text);
}
