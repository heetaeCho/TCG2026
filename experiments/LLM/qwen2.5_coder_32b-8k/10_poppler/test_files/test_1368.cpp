#include <gtest/gtest.h>

#include "./TestProjects/poppler/qt5/src/poppler-form.cc"



namespace Poppler {

    class SignatureValidationInfo {

    public:

        enum CertificateStatus {

            CertificateTrusted,

            CertificateUntrustedIssuer,

            CertificateUnknownIssuer,

            CertificateRevoked,

            CertificateExpired,

            CertificateGenericError,

            CertificateNotVerified

        };

    };

}



TEST(fromInternalTest_1368, TrustedCertificate_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateTrusted, 

              Poppler::fromInternal(CERTIFICATE_TRUSTED));

}



TEST(fromInternalTest_1368, UntrustedIssuer_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateUntrustedIssuer, 

              Poppler::fromInternal(CERTIFICATE_UNTRUSTED_ISSUER));

}



TEST(fromInternalTest_1368, UnknownIssuer_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateUnknownIssuer, 

              Poppler::fromInternal(CERTIFICATE_UNKNOWN_ISSUER));

}



TEST(fromInternalTest_1368, RevokedCertificate_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateRevoked, 

              Poppler::fromInternal(CERTIFICATE_REVOKED));

}



TEST(fromInternalTest_1368, ExpiredCertificate_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateExpired, 

              Poppler::fromInternal(CERTIFICATE_EXPIRED));

}



TEST(fromInternalTest_1368, GenericError_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateGenericError, 

              Poppler::fromInternal(CERTIFICATE_GENERIC_ERROR));

}



TEST(fromInternalTest_1368, NotVerified_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateNotVerified, 

              Poppler::fromInternal(CERTIFICATE_NOT_VERIFIED));

}



TEST(fromInternalTest_1368, DefaultCase_1368) {

    EXPECT_EQ(Poppler::SignatureValidationInfo::CertificateGenericError, 

              Poppler::fromInternal(static_cast<CertificateValidationStatus>(99)));

}
