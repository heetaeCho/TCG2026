#include <gtest/gtest.h>

#include "poppler-form-field.h"



// Mock structure for PopplerSignatureInfo

struct MockPopplerSignatureInfo : public _PopplerSignatureInfo {

    MockPopplerSignatureInfo(PopplerCertificateStatus status) {

        cert_status = status;

    }

};



class SignatureInfoTest_2329 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary data or state before each test

    }



    void TearDown() override {

        // Clean up any resources after each test

    }

};



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_Trusted_2329) {

    MockPopplerSignatureInfo siginfo(POPPLER_CERTIFICATE_TRUSTED);

    EXPECT_EQ(poppler_signature_info_get_certificate_status(&siginfo), POPPLER_CERTIFICATE_TRUSTED);

}



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_UntrustedIssuer_2329) {

    MockPopplerSignatureInfo siginfo(POPPLER_CERTIFICATE_UNTRUSTED_ISSUER);

    EXPECT_EQ(poppler_signature_info_get_certificate_status(&siginfo), POPPLER_CERTIFICATE_UNTRUSTED_ISSUER);

}



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_UnknownIssuer_2329) {

    MockPopplerSignatureInfo siginfo(POPPLER_CERTIFICATE_UNKNOWN_ISSUER);

    EXPECT_EQ(poppler_signature_info_get_certificate_status(&siginfo), POPPLER_CERTIFICATE_UNKNOWN_ISSUER);

}



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_Revoked_2329) {

    MockPopplerSignatureInfo siginfo(POPPLER_CERTIFICATE_REVOKED);

    EXPECT_EQ(poppler_signature_info_get_certificate_status(&siginfo), POPPLER_CERTIFICATE_REVOKED);

}



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_Expired_2329) {

    MockPopplerSignatureInfo siginfo(POPPLER_CERTIFICATE_EXPIRED);

    EXPECT_EQ(poppler_signature_info_get_certificate_status(&siginfo), POPPLER_CERTIFICATE_EXPIRED);

}



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_GenericError_2329) {

    MockPopplerSignatureInfo siginfo(POPPLER_CERTIFICATE_GENERIC_ERROR);

    EXPECT_EQ(poppler_signature_info_get_certificate_status(&siginfo), POPPLER_CERTIFICATE_GENERIC_ERROR);

}



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_NotVerified_2329) {

    MockPopplerSignatureInfo siginfo(POPPLER_CERTIFICATE_NOT_VERIFIED);

    EXPECT_EQ(poppler_signature_info_get_certificate_status(&siginfo), POPPLER_CERTIFICATE_NOT_VERIFIED);

}



TEST_F(SignatureInfoTest_2329, GetCertificateStatus_NullPointer_2329) {

    EXPECT_EQ(poppler_signature_info_get_certificate_status(nullptr), POPPLER_CERTIFICATE_GENERIC_ERROR);

}
