#include <gtest/gtest.h>

#include "./TestProjects/poppler/utils/pdfsig.cc"

#include "./TestProjects/poppler/poppler/SignatureInfo.h"



class CertificateStateTest_2677 : public ::testing::Test {

protected:

    // No additional setup or teardown needed for this function-based test.

};



TEST_F(CertificateStateTest_2677, GetReadableCertState_Trusted_2677) {

    EXPECT_STREQ(getReadableCertState(CERTIFICATE_TRUSTED), "Certificate is Trusted.");

}



TEST_F(CertificateStateTest_2677, GetReadableCertState_UntrustedIssuer_2677) {

    EXPECT_STREQ(getReadableCertState(CERTIFICATE_UNTRUSTED_ISSUER), "Certificate issuer isn't Trusted.");

}



TEST_F(CertificateStateTest_2677, GetReadableCertState_UnknownIssuer_2677) {

    EXPECT_STREQ(getReadableCertState(CERTIFICATE_UNKNOWN_ISSUER), "Certificate issuer is unknown.");

}



TEST_F(CertificateStateTest_2677, GetReadableCertState_Revoked_2677) {

    EXPECT_STREQ(getReadableCertState(CERTIFICATE_REVOKED), "Certificate has been Revoked.");

}



TEST_F(CertificateStateTest_2677, GetReadableCertState_Expired_2677) {

    EXPECT_STREQ(getReadableCertState(CERTIFICATE_EXPIRED), "Certificate has Expired");

}



TEST_F(CertificateStateTest_2677, GetReadableCertState_NotVerified_2677) {

    EXPECT_STREQ(getReadableCertState(CERTIFICATE_NOT_VERIFIED), "Certificate has not yet been verified.");

}



TEST_F(CertificateStateTest_2677, GetReadableCertState_DefaultCase_2677) {

    EXPECT_STREQ(getReadableCertState(static_cast<CertificateValidationStatus>(99)), "Unknown issue with Certificate or corrupted data.");

}
