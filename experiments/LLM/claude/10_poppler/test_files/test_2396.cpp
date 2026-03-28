#include <glib.h>
#include <gtest/gtest.h>

// Forward declare the struct and function as they would be exposed through the header
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

const char *poppler_certificate_info_get_subject_common_name(const PopplerCertificateInfo *certificate_info);

} // extern "C"

class PopplerCertificateInfoTest_2396 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerCertificateInfoTest_2396, ReturnsSubjectCommonName_2396)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = g_strdup("John Doe");

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "John Doe");

    g_free(info.subject_common_name);
}

TEST_F(PopplerCertificateInfoTest_2396, ReturnsNullWhenSubjectCommonNameIsNull_2396)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = nullptr;

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2396, ReturnsNullWhenCertificateInfoIsNull_2396)
{
    // g_return_val_if_fail should return nullptr when passed nullptr
    const char *result = poppler_certificate_info_get_subject_common_name(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2396, ReturnsEmptyStringWhenSubjectCommonNameIsEmpty_2396)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = g_strdup("");

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(info.subject_common_name);
}

TEST_F(PopplerCertificateInfoTest_2396, ReturnsCorrectPointer_2396)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = g_strdup("Test CN");

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    // The returned pointer should be the same as the one stored in the struct
    EXPECT_EQ(result, info.subject_common_name);

    g_free(info.subject_common_name);
}

TEST_F(PopplerCertificateInfoTest_2396, ReturnsSubjectCommonNameWithSpecialCharacters_2396)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = g_strdup("CN=Test, O=Org, C=US; <special>&\"chars\"");

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "CN=Test, O=Org, C=US; <special>&\"chars\"");

    g_free(info.subject_common_name);
}

TEST_F(PopplerCertificateInfoTest_2396, ReturnsSubjectCommonNameWithUTF8Characters_2396)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = g_strdup("Ñoño Müller Ñandú");

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Ñoño Müller Ñandú");

    g_free(info.subject_common_name);
}

TEST_F(PopplerCertificateInfoTest_2396, DoesNotReturnOtherFields_2396)
{
    PopplerCertificateInfo info = {};
    info.subject_common_name = g_strdup("Subject CN");
    info.issuer_common_name = g_strdup("Issuer CN");
    info.subject_organization = g_strdup("Subject Org");

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Subject CN");
    EXPECT_STRNE(result, "Issuer CN");
    EXPECT_STRNE(result, "Subject Org");

    g_free(info.subject_common_name);
    g_free(info.issuer_common_name);
    g_free(info.subject_organization);
}

TEST_F(PopplerCertificateInfoTest_2396, ReturnsLongSubjectCommonName_2396)
{
    PopplerCertificateInfo info = {};
    // Create a long string
    std::string long_name(1024, 'A');
    info.subject_common_name = g_strdup(long_name.c_str());

    const char *result = poppler_certificate_info_get_subject_common_name(&info);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_name.c_str());

    g_free(info.subject_common_name);
}
