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

const char *poppler_certificate_info_get_subject_organization(const PopplerCertificateInfo *certificate_info);

}

class PopplerCertificateInfoTest_2397 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerCertificateInfoTest_2397, ReturnsSubjectOrganization_2397)
{
    PopplerCertificateInfo info = {};
    info.subject_organization = g_strdup("Test Organization");

    const char *result = poppler_certificate_info_get_subject_organization(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Test Organization");

    g_free(info.subject_organization);
}

TEST_F(PopplerCertificateInfoTest_2397, ReturnsNullWhenSubjectOrganizationIsNull_2397)
{
    PopplerCertificateInfo info = {};
    info.subject_organization = nullptr;

    const char *result = poppler_certificate_info_get_subject_organization(&info);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2397, ReturnsNullWhenCertificateInfoIsNull_2397)
{
    const char *result = poppler_certificate_info_get_subject_organization(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2397, ReturnsEmptyStringWhenSubjectOrganizationIsEmpty_2397)
{
    PopplerCertificateInfo info = {};
    info.subject_organization = g_strdup("");

    const char *result = poppler_certificate_info_get_subject_organization(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(info.subject_organization);
}

TEST_F(PopplerCertificateInfoTest_2397, ReturnsCorrectPointer_2397)
{
    PopplerCertificateInfo info = {};
    info.subject_organization = g_strdup("My Org");

    const char *result = poppler_certificate_info_get_subject_organization(&info);
    EXPECT_EQ(result, info.subject_organization);

    g_free(info.subject_organization);
}

TEST_F(PopplerCertificateInfoTest_2397, DoesNotAffectOtherFields_2397)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = g_strdup("Common Name");
    info.subject_organization = g_strdup("Organization");
    info.subject_email = g_strdup("email@test.com");

    const char *result = poppler_certificate_info_get_subject_organization(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Organization");

    // Verify other fields are untouched
    EXPECT_STREQ(info.subject_common_name, "Common Name");
    EXPECT_STREQ(info.subject_email, "email@test.com");

    g_free(info.subject_common_name);
    g_free(info.subject_organization);
    g_free(info.subject_email);
}

TEST_F(PopplerCertificateInfoTest_2397, HandlesLongOrganizationString_2397)
{
    PopplerCertificateInfo info = {};
    std::string long_org(1000, 'A');
    info.subject_organization = g_strdup(long_org.c_str());

    const char *result = poppler_certificate_info_get_subject_organization(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_org.c_str());

    g_free(info.subject_organization);
}

TEST_F(PopplerCertificateInfoTest_2397, HandlesSpecialCharacters_2397)
{
    PopplerCertificateInfo info = {};
    info.subject_organization = g_strdup("Org with spëcial chars: @#$%^&*()");

    const char *result = poppler_certificate_info_get_subject_organization(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Org with spëcial chars: @#$%^&*()");

    g_free(info.subject_organization);
}

TEST_F(PopplerCertificateInfoTest_2397, ConsistentMultipleCalls_2397)
{
    PopplerCertificateInfo info = {};
    info.subject_organization = g_strdup("Consistent Org");

    const char *result1 = poppler_certificate_info_get_subject_organization(&info);
    const char *result2 = poppler_certificate_info_get_subject_organization(&info);

    EXPECT_EQ(result1, result2);
    EXPECT_STREQ(result1, "Consistent Org");

    g_free(info.subject_organization);
}
