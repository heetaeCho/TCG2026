#include <glib.h>
#include <gtest/gtest.h>

// Include the poppler-glib header for the public API
extern "C" {
#include "poppler.h"
}

class PopplerSigningDataGetSignatureTextTest_2363 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsNullWhenSigningDataIsNull_2363)
{
    // When passing nullptr, should return nullptr (via g_return_val_if_fail)
    const gchar *result = poppler_signing_data_get_signature_text(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsSignatureTextWhenSet_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    const char *expected_text = "Test Signature";
    poppler_signing_data_set_signature_text(signing_data, expected_text);

    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, expected_text);

    poppler_signing_data_free(signing_data);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsNullWhenSignatureTextNotSet_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    EXPECT_EQ(result, nullptr);

    poppler_signing_data_free(signing_data);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsEmptyStringWhenSetToEmpty_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    poppler_signing_data_set_signature_text(signing_data, "");

    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    poppler_signing_data_free(signing_data);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsUpdatedTextAfterMultipleSets_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    poppler_signing_data_set_signature_text(signing_data, "First Signature");
    const gchar *result1 = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "First Signature");

    poppler_signing_data_set_signature_text(signing_data, "Second Signature");
    const gchar *result2 = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "Second Signature");

    poppler_signing_data_free(signing_data);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsLongSignatureText_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    // Create a long string
    std::string long_text(1000, 'A');
    poppler_signing_data_set_signature_text(signing_data, long_text.c_str());

    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_text.c_str());

    poppler_signing_data_free(signing_data);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsUTF8SignatureText_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    const char *utf8_text = "Ünïcödé Sîgnâtürè Tëxt 日本語";
    poppler_signing_data_set_signature_text(signing_data, utf8_text);

    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, utf8_text);

    poppler_signing_data_free(signing_data);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsNullAfterSettingToNull_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    poppler_signing_data_set_signature_text(signing_data, "Some text");
    const gchar *result1 = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "Some text");

    // Setting to nullptr should clear it
    poppler_signing_data_set_signature_text(signing_data, nullptr);
    const gchar *result2 = poppler_signing_data_get_signature_text(signing_data);
    EXPECT_EQ(result2, nullptr);

    poppler_signing_data_free(signing_data);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, CopiedSigningDataPreservesSignatureText_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    poppler_signing_data_set_signature_text(signing_data, "Copy Test");

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const gchar *result = poppler_signing_data_get_signature_text(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Copy Test");

    poppler_signing_data_free(signing_data);
    poppler_signing_data_free(copy);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, SignatureTextWithSpecialCharacters_2363)
{
    PopplerSigningData *signing_data = poppler_signing_data_new();
    ASSERT_NE(signing_data, nullptr);

    const char *special_text = "Line1\nLine2\tTabbed\0Hidden";
    poppler_signing_data_set_signature_text(signing_data, special_text);

    const gchar *result = poppler_signing_data_get_signature_text(signing_data);
    ASSERT_NE(result, nullptr);
    // Note: C string will stop at \0, so only "Line1\nLine2\tTabbed" is expected
    EXPECT_STREQ(result, "Line1\nLine2\tTabbed");

    poppler_signing_data_free(signing_data);
}
