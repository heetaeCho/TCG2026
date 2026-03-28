#include <glib.h>
#include <gtest/gtest.h>

// Forward declare the struct and function as they would be available from the header
extern "C" {

typedef struct _PopplerCertificateInfo {
    char *id;
    char *subject_common_name;
    char *subject_organization;
    char *subject_email;
    char *issuer_common_name;
    char *issuer_organization;
    char *issuer_email;
    int *issued;
    int *expires;
} PopplerCertificateInfo;

const char *poppler_certificate_info_get_subject_email(const PopplerCertificateInfo *certificate_info);

} // extern "C"

class PopplerCertificateInfoTest_2398 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing a valid certificate_info with a non-null subject_email returns the correct email
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_ValidEmail_2398)
{
    PopplerCertificateInfo info = {};
    info.subject_email = g_strdup("user@example.com");

    const char *result = poppler_certificate_info_get_subject_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "user@example.com");

    g_free(info.subject_email);
}

// Test that passing a valid certificate_info with a null subject_email returns null
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_NullEmail_2398)
{
    PopplerCertificateInfo info = {};
    info.subject_email = nullptr;

    const char *result = poppler_certificate_info_get_subject_email(&info);
    EXPECT_EQ(result, nullptr);
}

// Test that passing a nullptr certificate_info returns nullptr (g_return_val_if_fail guard)
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_NullCertificateInfo_2398)
{
    const char *result = poppler_certificate_info_get_subject_email(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with an empty string subject_email
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_EmptyString_2398)
{
    PopplerCertificateInfo info = {};
    info.subject_email = g_strdup("");

    const char *result = poppler_certificate_info_get_subject_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(info.subject_email);
}

// Test with a subject_email containing special characters
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_SpecialCharacters_2398)
{
    PopplerCertificateInfo info = {};
    info.subject_email = g_strdup("user+tag@sub.example.com");

    const char *result = poppler_certificate_info_get_subject_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "user+tag@sub.example.com");

    g_free(info.subject_email);
}

// Test that the returned pointer is the same as the one stored in the struct (no copy)
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_ReturnsSamePointer_2398)
{
    PopplerCertificateInfo info = {};
    info.subject_email = g_strdup("test@test.org");

    const char *result = poppler_certificate_info_get_subject_email(&info);
    EXPECT_EQ(result, info.subject_email);

    g_free(info.subject_email);
}

// Test with a long email string
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_LongEmail_2398)
{
    PopplerCertificateInfo info = {};
    // Create a long email address
    std::string long_local(200, 'a');
    std::string long_email = long_local + "@example.com";
    info.subject_email = g_strdup(long_email.c_str());

    const char *result = poppler_certificate_info_get_subject_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_email.c_str());

    g_free(info.subject_email);
}

// Test that other fields do not affect subject_email retrieval
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_OtherFieldsPopulated_2398)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("cert-id-123");
    info.subject_common_name = g_strdup("Common Name");
    info.subject_organization = g_strdup("Organization");
    info.subject_email = g_strdup("specific@email.org");
    info.issuer_common_name = g_strdup("Issuer CN");
    info.issuer_organization = g_strdup("Issuer Org");
    info.issuer_email = g_strdup("issuer@email.org");

    const char *result = poppler_certificate_info_get_subject_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "specific@email.org");

    g_free(info.id);
    g_free(info.subject_common_name);
    g_free(info.subject_organization);
    g_free(info.subject_email);
    g_free(info.issuer_common_name);
    g_free(info.issuer_organization);
    g_free(info.issuer_email);
}

// Test with Unicode characters in email
TEST_F(PopplerCertificateInfoTest_2398, GetSubjectEmail_UnicodeCharacters_2398)
{
    PopplerCertificateInfo info = {};
    info.subject_email = g_strdup("tëst@éxample.com");

    const char *result = poppler_certificate_info_get_subject_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "tëst@éxample.com");

    g_free(info.subject_email);
}
