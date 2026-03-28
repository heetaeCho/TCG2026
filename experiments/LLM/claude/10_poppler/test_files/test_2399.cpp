#include <gtest/gtest.h>
#include <glib.h>

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

const char *poppler_certificate_info_get_issuer_common_name(const PopplerCertificateInfo *certificate_info);

} // extern "C"

class PopplerCertificateInfoTest_2399 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing a valid certificate_info with a non-null issuer_common_name returns it correctly
TEST_F(PopplerCertificateInfoTest_2399, ReturnsIssuerCommonName_2399)
{
    PopplerCertificateInfo info = {};
    info.issuer_common_name = g_strdup("Test Issuer CN");

    const char *result = poppler_certificate_info_get_issuer_common_name(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Test Issuer CN");

    g_free(info.issuer_common_name);
}

// Test that passing a nullptr certificate_info returns nullptr
TEST_F(PopplerCertificateInfoTest_2399, ReturnsNullForNullInput_2399)
{
    const char *result = poppler_certificate_info_get_issuer_common_name(nullptr);

    EXPECT_EQ(result, nullptr);
}

// Test that when issuer_common_name is nullptr, the function returns nullptr
TEST_F(PopplerCertificateInfoTest_2399, ReturnsNullWhenIssuerCommonNameIsNull_2399)
{
    PopplerCertificateInfo info = {};
    info.issuer_common_name = nullptr;

    const char *result = poppler_certificate_info_get_issuer_common_name(&info);

    EXPECT_EQ(result, nullptr);
}

// Test that an empty string issuer_common_name is returned correctly
TEST_F(PopplerCertificateInfoTest_2399, ReturnsEmptyStringWhenIssuerCommonNameIsEmpty_2399)
{
    PopplerCertificateInfo info = {};
    info.issuer_common_name = g_strdup("");

    const char *result = poppler_certificate_info_get_issuer_common_name(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(info.issuer_common_name);
}

// Test that the returned pointer points to the same memory as the struct member
TEST_F(PopplerCertificateInfoTest_2399, ReturnsSamePointerAsStructMember_2399)
{
    PopplerCertificateInfo info = {};
    info.issuer_common_name = g_strdup("Pointer Test");

    const char *result = poppler_certificate_info_get_issuer_common_name(&info);

    EXPECT_EQ(result, info.issuer_common_name);

    g_free(info.issuer_common_name);
}

// Test with a long issuer common name string
TEST_F(PopplerCertificateInfoTest_2399, ReturnsLongIssuerCommonName_2399)
{
    PopplerCertificateInfo info = {};
    std::string long_name(1024, 'A');
    info.issuer_common_name = g_strdup(long_name.c_str());

    const char *result = poppler_certificate_info_get_issuer_common_name(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_name.c_str());

    g_free(info.issuer_common_name);
}

// Test with special characters in the issuer common name
TEST_F(PopplerCertificateInfoTest_2399, ReturnsIssuerCommonNameWithSpecialChars_2399)
{
    PopplerCertificateInfo info = {};
    info.issuer_common_name = g_strdup("Issuer CN with spëcial çhàrs & symbols <>/\\");

    const char *result = poppler_certificate_info_get_issuer_common_name(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Issuer CN with spëcial çhàrs & symbols <>/\\");

    g_free(info.issuer_common_name);
}

// Test that other fields don't affect the issuer_common_name retrieval
TEST_F(PopplerCertificateInfoTest_2399, OtherFieldsDoNotAffectResult_2399)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("some-id");
    info.subject_common_name = g_strdup("Subject CN");
    info.subject_organization = g_strdup("Subject Org");
    info.subject_email = g_strdup("subject@example.com");
    info.issuer_common_name = g_strdup("Expected Issuer CN");
    info.issuer_organization = g_strdup("Issuer Org");
    info.issuer_email = g_strdup("issuer@example.com");
    info.issued = nullptr;
    info.expires = nullptr;

    const char *result = poppler_certificate_info_get_issuer_common_name(&info);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Expected Issuer CN");

    g_free(info.id);
    g_free(info.subject_common_name);
    g_free(info.subject_organization);
    g_free(info.subject_email);
    g_free(info.issuer_common_name);
    g_free(info.issuer_organization);
    g_free(info.issuer_email);
}
