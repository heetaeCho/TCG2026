#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definition based on known dependencies
typedef enum {
    POPPLER_SIGNATURE_VALID,
    POPPLER_SIGNATURE_INVALID,
    POPPLER_SIGNATURE_DIGEST_MISMATCH,
    POPPLER_SIGNATURE_DECODING_ERROR,
    POPPLER_SIGNATURE_GENERIC_ERROR,
    POPPLER_SIGNATURE_NOT_FOUND,
    POPPLER_SIGNATURE_NOT_VERIFIED
} PopplerSignatureStatus;

typedef enum {
    POPPLER_CERTIFICATE_TRUSTED,
    POPPLER_CERTIFICATE_UNTRUSTED_ISSUER,
    POPPLER_CERTIFICATE_UNKNOWN_ISSUER,
    POPPLER_CERTIFICATE_REVOKED,
    POPPLER_CERTIFICATE_EXPIRED,
    POPPLER_CERTIFICATE_GENERIC_ERROR,
    POPPLER_CERTIFICATE_NOT_VERIFIED
} PopplerCertificateStatus;

typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

typedef struct _PopplerSignatureInfo {
    int sig_status;
    PopplerCertificateStatus cert_status;
    char *signer_name;
    int *local_signing_time;
    PopplerCertificateInfo *certificate_info;
} PopplerSignatureInfo;

// Declaration of the function under test
extern "C" {
const gchar *poppler_signature_info_get_signer_name(const PopplerSignatureInfo *siginfo);
}

class PopplerSignatureInfoGetSignerNameTest_2330 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsNullWhenSigInfoIsNull_2330)
{
    // When passed a null pointer, the function should return NULL
    const gchar *result = poppler_signature_info_get_signer_name(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsSignerNameWhenValid_2330)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.signer_name = g_strdup("John Doe");

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "John Doe");

    g_free(siginfo.signer_name);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsNullWhenSignerNameIsNull_2330)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.signer_name = nullptr;

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsEmptyStringWhenSignerNameIsEmpty_2330)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.signer_name = g_strdup("");

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(siginfo.signer_name);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsSignerNameWithSpecialCharacters_2330)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.signer_name = g_strdup("José García-López");

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "José García-López");

    g_free(siginfo.signer_name);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsSignerNameWithUnicodeCharacters_2330)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.signer_name = g_strdup("田中太郎");

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "田中太郎");

    g_free(siginfo.signer_name);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsSignerNameWithLongString_2330)
{
    PopplerSignatureInfo siginfo = {};
    // Create a long signer name
    std::string long_name(1024, 'A');
    siginfo.signer_name = g_strdup(long_name.c_str());

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_name.c_str());

    g_free(siginfo.signer_name);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsSamePointerAsSignerName_2330)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.signer_name = g_strdup("Test Signer");

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    // The function should return the same pointer, not a copy
    EXPECT_EQ(result, siginfo.signer_name);

    g_free(siginfo.signer_name);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsSignerNameWithWhitespace_2330)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.signer_name = g_strdup("   spaces and\ttabs\nnewlines   ");

    const gchar *result = poppler_signature_info_get_signer_name(&siginfo);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "   spaces and\ttabs\nnewlines   ");

    g_free(siginfo.signer_name);
}
