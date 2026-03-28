#include <gtest/gtest.h>

#include "SignatureInfo.h"



// Assuming NSSCMSVerificationStatus is defined in a way that can be used here.

enum NSSCMSVerificationStatus {

    NSSCMSVS_GoodSignature,

    NSSCMSVS_BadSignature,

    NSSCMSVS_DigestMismatch,

    NSSCMSVS_ProcessingError

};



extern SignatureValidationStatus NSS_SigTranslate(NSSCMSVerificationStatus nss_code);



class NSSCryptoSignBackendTest_1802 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(NSSCryptoSignBackendTest_1802, GoodSignatureTranslation_1802) {

    EXPECT_EQ(NSS_SigTranslate(NSSCMSVS_GoodSignature), SIGNATURE_VALID);

}



TEST_F(NSSCryptoSignBackendTest_1802, BadSignatureTranslation_1802) {

    EXPECT_EQ(NSS_SigTranslate(NSSCMSVS_BadSignature), SIGNATURE_INVALID);

}



TEST_F(NSSCryptoSignBackendTest_1802, DigestMismatchTranslation_1802) {

    EXPECT_EQ(NSS_SigTranslate(NSSCMSVS_DigestMismatch), SIGNATURE_DIGEST_MISMATCH);

}



TEST_F(NSSCryptoSignBackendTest_1802, ProcessingErrorTranslation_1802) {

    EXPECT_EQ(NSS_SigTranslate(NSSCMSVS_ProcessingError), SIGNATURE_DECODING_ERROR);

}



TEST_F(NSSCryptoSignBackendTest_1802, DefaultCaseTranslation_1802) {

    EXPECT_EQ(NSS_SigTranslate(static_cast<NSSCMSVerificationStatus>(999)), SIGNATURE_GENERIC_ERROR);

}
