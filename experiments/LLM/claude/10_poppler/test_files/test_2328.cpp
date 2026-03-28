#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and type definitions based on the known interface
extern "C" {

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

PopplerCertificateInfo *poppler_signature_info_get_certificate_info(const PopplerSignatureInfo *siginfo);

}

class PopplerSignatureInfoGetCertificateInfoTest_2328 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns NULL
TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, ReturnsNullWhenSigInfoIsNull_2328)
{
    // g_return_val_if_fail should cause it to return NULL when passed nullptr
    // Note: This will generate a GLib warning, which is expected behavior
    PopplerCertificateInfo *result = poppler_signature_info_get_certificate_info(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that it returns the certificate_info field when siginfo is valid and has a certificate
TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, ReturnsCertificateInfoWhenValid_2328)
{
    PopplerCertificateInfo dummy_cert_info;
    PopplerSignatureInfo siginfo = {};
    siginfo.certificate_info = &dummy_cert_info;

    PopplerCertificateInfo *result = poppler_signature_info_get_certificate_info(&siginfo);
    EXPECT_EQ(result, &dummy_cert_info);
}

// Test that it returns NULL when certificate_info is NULL in a valid siginfo
TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, ReturnsNullWhenCertificateInfoIsNull_2328)
{
    PopplerSignatureInfo siginfo = {};
    siginfo.certificate_info = nullptr;

    PopplerCertificateInfo *result = poppler_signature_info_get_certificate_info(&siginfo);
    EXPECT_EQ(result, nullptr);
}

// Test that the returned pointer is exactly the one stored in the struct
TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, ReturnsSamePointerAsStored_2328)
{
    PopplerCertificateInfo dummy_cert_info_1;
    PopplerCertificateInfo dummy_cert_info_2;

    PopplerSignatureInfo siginfo = {};
    siginfo.certificate_info = &dummy_cert_info_1;

    EXPECT_EQ(poppler_signature_info_get_certificate_info(&siginfo), &dummy_cert_info_1);
    EXPECT_NE(poppler_signature_info_get_certificate_info(&siginfo), &dummy_cert_info_2);

    // Change the certificate info and verify it reflects the new value
    siginfo.certificate_info = &dummy_cert_info_2;
    EXPECT_EQ(poppler_signature_info_get_certificate_info(&siginfo), &dummy_cert_info_2);
}

// Test with a fully populated siginfo struct
TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, WorksWithFullyPopulatedSigInfo_2328)
{
    PopplerCertificateInfo dummy_cert;
    int dummy_time = 12345;
    char signer[] = "Test Signer";

    PopplerSignatureInfo siginfo = {};
    siginfo.sig_status = 1;
    siginfo.cert_status = POPPLER_CERTIFICATE_TRUSTED;
    siginfo.signer_name = signer;
    siginfo.local_signing_time = &dummy_time;
    siginfo.certificate_info = &dummy_cert;

    PopplerCertificateInfo *result = poppler_signature_info_get_certificate_info(&siginfo);
    EXPECT_EQ(result, &dummy_cert);
}

// Test const correctness - the function takes const pointer, ensure it works
TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, AcceptsConstSigInfo_2328)
{
    PopplerCertificateInfo dummy_cert;
    PopplerSignatureInfo siginfo = {};
    siginfo.certificate_info = &dummy_cert;

    const PopplerSignatureInfo *const_siginfo = &siginfo;
    PopplerCertificateInfo *result = poppler_signature_info_get_certificate_info(const_siginfo);
    EXPECT_EQ(result, &dummy_cert);
}
