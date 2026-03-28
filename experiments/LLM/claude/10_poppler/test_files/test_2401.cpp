#include <glib.h>
#include <gtest/gtest.h>

// Forward declare the struct and function as they appear in the interface
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

const char *poppler_certificate_info_get_issuer_email(const PopplerCertificateInfo *certificate_info);

}

class PopplerCertificateInfoTest_2401 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a valid issuer_email string is returned correctly
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_ValidEmail_2401)
{
    PopplerCertificateInfo info = {};
    info.issuer_email = g_strdup("test@example.com");

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "test@example.com");

    g_free(info.issuer_email);
}

// Test that nullptr is returned when issuer_email is nullptr
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_NullEmail_2401)
{
    PopplerCertificateInfo info = {};
    info.issuer_email = nullptr;

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    EXPECT_EQ(result, nullptr);
}

// Test that passing nullptr as certificate_info returns nullptr
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_NullCertificateInfo_2401)
{
    const char *result = poppler_certificate_info_get_issuer_email(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with an empty string as issuer_email
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_EmptyString_2401)
{
    PopplerCertificateInfo info = {};
    info.issuer_email = g_strdup("");

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(info.issuer_email);
}

// Test with a long email string
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_LongEmail_2401)
{
    PopplerCertificateInfo info = {};
    std::string long_email(500, 'a');
    long_email += "@example.com";
    info.issuer_email = g_strdup(long_email.c_str());

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_email.c_str());

    g_free(info.issuer_email);
}

// Test that the returned pointer points to the same memory as the struct member
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_ReturnsSamePointer_2401)
{
    PopplerCertificateInfo info = {};
    info.issuer_email = g_strdup("issuer@domain.org");

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    EXPECT_EQ(result, info.issuer_email);

    g_free(info.issuer_email);
}

// Test with special characters in the email
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_SpecialCharacters_2401)
{
    PopplerCertificateInfo info = {};
    info.issuer_email = g_strdup("user+tag@sub.domain.co.uk");

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "user+tag@sub.domain.co.uk");

    g_free(info.issuer_email);
}

// Test with unicode characters in the email
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_UnicodeCharacters_2401)
{
    PopplerCertificateInfo info = {};
    info.issuer_email = g_strdup("user@例え.jp");

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "user@例え.jp");

    g_free(info.issuer_email);
}

// Test that other fields don't affect issuer_email retrieval
TEST_F(PopplerCertificateInfoTest_2401, GetIssuerEmail_OtherFieldsPopulated_2401)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("id123");
    info.subject_common_name = g_strdup("Subject CN");
    info.subject_organization = g_strdup("Subject Org");
    info.subject_email = g_strdup("subject@example.com");
    info.issuer_common_name = g_strdup("Issuer CN");
    info.issuer_organization = g_strdup("Issuer Org");
    info.issuer_email = g_strdup("issuer@example.com");
    info.issued = nullptr;
    info.expires = nullptr;

    const char *result = poppler_certificate_info_get_issuer_email(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "issuer@example.com");

    g_free(info.id);
    g_free(info.subject_common_name);
    g_free(info.subject_organization);
    g_free(info.subject_email);
    g_free(info.issuer_common_name);
    g_free(info.issuer_organization);
    g_free(info.issuer_email);
}
