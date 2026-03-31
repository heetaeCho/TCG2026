#include <gtest/gtest.h>

// Include necessary headers
extern "C" {
#include <glib.h>
}

// Define the struct based on known/inferred dependencies
typedef enum {
    POPPLER_CERTIFICATE_TRUSTED = 0,
    POPPLER_CERTIFICATE_UNTRUSTED_ISSUER = 1,
    POPPLER_CERTIFICATE_UNKNOWN_ISSUER = 2,
    POPPLER_CERTIFICATE_REVOKED = 3,
    POPPLER_CERTIFICATE_EXPIRED = 4,
    POPPLER_CERTIFICATE_GENERIC_ERROR = 5,
    POPPLER_CERTIFICATE_NOT_VERIFIED = 6
} PopplerCertificateStatus;

typedef struct {
    int sig_status;
    PopplerCertificateStatus cert_status;
    char *signer_name;
    int *local_signing_time;
    void *certificate_info;
} PopplerSignatureInfo;

// Declaration of the function under test
extern "C" PopplerCertificateStatus poppler_signature_info_get_certificate_status(const PopplerSignatureInfo *siginfo);

class PopplerSignatureInfoTest_2329 : public ::testing::Test {
protected:
    PopplerSignatureInfo siginfo;

    void SetUp() override {
        memset(&siginfo, 0, sizeof(siginfo));
    }
};

TEST_F(PopplerSignatureInfoTest_2329, NullInputReturnsGenericError_2329) {
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(nullptr);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_GENERIC_ERROR);
}

TEST_F(PopplerSignatureInfoTest_2329, ReturnsTrustedStatus_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_TRUSTED;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_TRUSTED);
}

TEST_F(PopplerSignatureInfoTest_2329, ReturnsUntrustedIssuerStatus_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_UNTRUSTED_ISSUER;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_UNTRUSTED_ISSUER);
}

TEST_F(PopplerSignatureInfoTest_2329, ReturnsUnknownIssuerStatus_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_UNKNOWN_ISSUER;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_UNKNOWN_ISSUER);
}

TEST_F(PopplerSignatureInfoTest_2329, ReturnsRevokedStatus_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_REVOKED;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_REVOKED);
}

TEST_F(PopplerSignatureInfoTest_2329, ReturnsExpiredStatus_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_EXPIRED;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_EXPIRED);
}

TEST_F(PopplerSignatureInfoTest_2329, ReturnsGenericErrorStatus_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_GENERIC_ERROR;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_GENERIC_ERROR);
}

TEST_F(PopplerSignatureInfoTest_2329, ReturnsNotVerifiedStatus_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_NOT_VERIFIED;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_NOT_VERIFIED);
}

TEST_F(PopplerSignatureInfoTest_2329, FirstEnumValueBoundary_2329) {
    siginfo.cert_status = static_cast<PopplerCertificateStatus>(0);
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_TRUSTED);
}

TEST_F(PopplerSignatureInfoTest_2329, LastEnumValueBoundary_2329) {
    siginfo.cert_status = static_cast<PopplerCertificateStatus>(6);
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_NOT_VERIFIED);
}

TEST_F(PopplerSignatureInfoTest_2329, CertStatusIndependentOfOtherFields_2329) {
    siginfo.sig_status = 42;
    siginfo.cert_status = POPPLER_CERTIFICATE_REVOKED;
    siginfo.signer_name = nullptr;
    siginfo.local_signing_time = nullptr;
    siginfo.certificate_info = nullptr;
    PopplerCertificateStatus result = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result, POPPLER_CERTIFICATE_REVOKED);
}

TEST_F(PopplerSignatureInfoTest_2329, MultipleCallsReturnSameResult_2329) {
    siginfo.cert_status = POPPLER_CERTIFICATE_EXPIRED;
    PopplerCertificateStatus result1 = poppler_signature_info_get_certificate_status(&siginfo);
    PopplerCertificateStatus result2 = poppler_signature_info_get_certificate_status(&siginfo);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, POPPLER_CERTIFICATE_EXPIRED);
}
