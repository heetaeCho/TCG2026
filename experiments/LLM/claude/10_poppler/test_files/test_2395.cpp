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

const char *poppler_certificate_info_get_id(const PopplerCertificateInfo *certificate_info);

}

class PopplerCertificateInfoTest_2395 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerCertificateInfoTest_2395, GetIdReturnsCorrectId_2395)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("test-certificate-id-123");

    const char *result = poppler_certificate_info_get_id(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "test-certificate-id-123");

    g_free(info.id);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdReturnsNullWhenIdIsNull_2395)
{
    PopplerCertificateInfo info = {};
    info.id = nullptr;

    const char *result = poppler_certificate_info_get_id(&info);

    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdReturnsNullForNullCertificateInfo_2395)
{
    const char *result = poppler_certificate_info_get_id(nullptr);

    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdReturnsEmptyStringWhenIdIsEmpty_2395)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("");

    const char *result = poppler_certificate_info_get_id(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(info.id);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdReturnsPointerToOriginalId_2395)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("original-id");

    const char *result = poppler_certificate_info_get_id(&info);

    // The returned pointer should be the same as the internal id pointer
    EXPECT_EQ(result, info.id);

    g_free(info.id);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdWithLongString_2395)
{
    PopplerCertificateInfo info = {};
    std::string long_id(1024, 'A');
    info.id = g_strdup(long_id.c_str());

    const char *result = poppler_certificate_info_get_id(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_id.c_str());

    g_free(info.id);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdWithSpecialCharacters_2395)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("id-with-special!@#$%^&*()_+=chars");

    const char *result = poppler_certificate_info_get_id(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "id-with-special!@#$%^&*()_+=chars");

    g_free(info.id);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdMultipleCallsReturnSameValue_2395)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("consistent-id");

    const char *result1 = poppler_certificate_info_get_id(&info);
    const char *result2 = poppler_certificate_info_get_id(&info);

    EXPECT_EQ(result1, result2);
    EXPECT_STREQ(result1, "consistent-id");

    g_free(info.id);
}

TEST_F(PopplerCertificateInfoTest_2395, GetIdWithUTF8Characters_2395)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("id-ñ-ü-é-中文");

    const char *result = poppler_certificate_info_get_id(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "id-ñ-ü-é-中文");

    g_free(info.id);
}
