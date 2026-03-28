#include <gtest/gtest.h>
#include <glib.h>

// Forward declare the struct and function as they would be exposed in the header
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

const char *poppler_certificate_info_get_issuer_organization(const PopplerCertificateInfo *certificate_info);

}

class PopplerCertificateInfoTest_2400 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerCertificateInfoTest_2400, ReturnsIssuerOrganization_2400)
{
    PopplerCertificateInfo info = {};
    info.issuer_organization = g_strdup("Test Organization");

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Test Organization");

    g_free(info.issuer_organization);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsNullWhenIssuerOrganizationIsNull_2400)
{
    PopplerCertificateInfo info = {};
    info.issuer_organization = nullptr;

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsNullWhenCertificateInfoIsNull_2400)
{
    const char *result = poppler_certificate_info_get_issuer_organization(nullptr);

    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsEmptyStringWhenIssuerOrganizationIsEmpty_2400)
{
    PopplerCertificateInfo info = {};
    info.issuer_organization = g_strdup("");

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(info.issuer_organization);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsCorrectPointerToIssuerOrganization_2400)
{
    PopplerCertificateInfo info = {};
    info.issuer_organization = g_strdup("My Org");

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    // The returned pointer should be the same as the one stored in the struct
    EXPECT_EQ(result, info.issuer_organization);

    g_free(info.issuer_organization);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsIssuerOrganizationWithSpecialCharacters_2400)
{
    PopplerCertificateInfo info = {};
    info.issuer_organization = g_strdup("Org with special chars: @#$%^&*()");

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Org with special chars: @#$%^&*()");

    g_free(info.issuer_organization);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsIssuerOrganizationWithUTF8Characters_2400)
{
    PopplerCertificateInfo info = {};
    info.issuer_organization = g_strdup("Ünïcödé Örganïzatïön");

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Ünïcödé Örganïzatïön");

    g_free(info.issuer_organization);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsIssuerOrganizationIndependentOfOtherFields_2400)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("some-id");
    info.subject_common_name = g_strdup("Subject CN");
    info.subject_organization = g_strdup("Subject Org");
    info.issuer_common_name = g_strdup("Issuer CN");
    info.issuer_organization = g_strdup("The Real Issuer Org");
    info.issuer_email = g_strdup("issuer@example.com");

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "The Real Issuer Org");

    g_free(info.id);
    g_free(info.subject_common_name);
    g_free(info.subject_organization);
    g_free(info.issuer_common_name);
    g_free(info.issuer_organization);
    g_free(info.issuer_email);
}

TEST_F(PopplerCertificateInfoTest_2400, ConsistentReturnOnMultipleCalls_2400)
{
    PopplerCertificateInfo info = {};
    info.issuer_organization = g_strdup("Consistent Org");

    const char *result1 = poppler_certificate_info_get_issuer_organization(&info);
    const char *result2 = poppler_certificate_info_get_issuer_organization(&info);

    EXPECT_EQ(result1, result2);
    EXPECT_STREQ(result1, "Consistent Org");

    g_free(info.issuer_organization);
}

TEST_F(PopplerCertificateInfoTest_2400, ReturnsLongIssuerOrganization_2400)
{
    PopplerCertificateInfo info = {};
    std::string long_org(1000, 'A');
    info.issuer_organization = g_strdup(long_org.c_str());

    const char *result = poppler_certificate_info_get_issuer_organization(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_org.c_str());

    g_free(info.issuer_organization);
}
