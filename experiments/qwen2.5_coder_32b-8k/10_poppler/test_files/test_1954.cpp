#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include "GPGMECryptoSignBackend.cc"

#include "CertificateInfo.h"



using namespace GpgME;

using namespace testing;



class X509CertificateInfoTest : public Test {

protected:

    Key key;

    Protocol protocol = CMS;

};



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_CMSProtocol_ReturnsValidCertificateInfo_1954) {

    // Arrange

    ON_CALL(key, issuerName()).WillByDefault(Return("CN=Issuer"));

    ON_CALL(key, userID(0)).WillByDefault(Return(UserID("uid0", "user@domain.com")));

    ON_CALL(key, subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));

    ON_CALL(key.subkey(0), length()).WillByDefault(Return(2048));

    ON_CALL(key.subkey(0), isCardKey()).WillByDefault(Return(false));

    ON_CALL(key, primaryFingerprint()).WillByDefault(Return("fingerprint"));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->subjectInfo.email, "user@domain.com");

    EXPECT_EQ(certificateInfo->publicKeyInfo.publicKeyType, RSAKEY);

    EXPECT_EQ(certificateInfo->publicKeyInfo.publicKeyStrength, 2048);

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_OpenPGPProtocol_ReturnsValidCertificateInfo_1954) {

    // Arrange

    ON_CALL(key, userID(0)).WillByDefault(Return(UserID("uid0", "user@domain.com")));

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));

    ON_CALL(key.subkey(0), length()).WillByDefault(Return(2048));

    ON_CALL(key, primaryFingerprint()).WillByDefault(Return("fingerprint"));

    protocol = OpenPGP;



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->subjectInfo.email, "user@domain.com");

    EXPECT_EQ(certificateInfo->certificateType, CertificateType::PGP);

    EXPECT_EQ(certificateInfo->publicKeyInfo.publicKeyType, RSAKEY);

    EXPECT_EQ(certificateInfo->publicKeyInfo.publicKeyStrength, 2048);

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_SubkeyIsCardKey_SetKeyLocationToHardwareToken_1954) {

    // Arrange

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));

    ON_CALL(key.subkey(0), isCardKey()).WillByDefault(Return(true));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->keyLocation, KeyLocation::HardwareToken);

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_SubkeyIsSecret_SetKeyLocationToComputer_1954) {

    // Arrange

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));

    ON_CALL(key.subkey(0), isCardKey()).WillByDefault(Return(false));

    ON_CALL(key.subkey(0), isSecret()).WillByDefault(Return(true));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->keyLocation, KeyLocation::Computer);

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_SubkeyIsQualified_SetQualifiedTrue_1954) {

    // Arrange

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));

    ON_CALL(key.subkey(0), isQualified()).WillByDefault(Return(true));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_TRUE(certificateInfo->qualified);

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_CanSignAndEncrypt_SetKeyUsageExtensionsCorrectly_1954) {

    // Arrange

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));

    EXPECT_CALL(key, canSign()).WillOnce(Return(true));

    EXPECT_CALL(key, canEncrypt()).WillOnce(Return(true));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->keyUsageExtensions, KU_NON_REPUDIATION | KU_DIGITAL_SIGNATURE | KU_KEY_ENCIPHERMENT | KU_DATA_ENCIPHERMENT);

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_CanCertify_SetKeyUsageExtensionsCorrectly_1954) {

    // Arrange

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));

    EXPECT_CALL(key, canSign()).WillOnce(Return(false));

    EXPECT_CALL(key, canEncrypt()).WillOnce(Return(false));

    EXPECT_CALL(key, canCertify()).WillOnce(Return(true));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->keyUsageExtensions, KU_KEY_CERT_SIGN);

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_NoEmailInFirstUserID_TakesEmailFromSecondUserID_1954) {

    // Arrange

    ON_CALL(key, issuerName()).WillByDefault(Return("CN=Issuer"));

    ON_CALL(key, userID(0)).WillByDefault(Return(UserID("uid0", "")));

    ON_CALL(key, userID(1)).WillByDefault(Return(UserID("uid1", "user@domain.com")));

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->subjectInfo.email, "user@domain.com");

}



TEST_F(X509CertificateInfoTest_1954, GetCertificateInfoFromKey_NoEmailInUserIDs_SetEmptyEmail_1954) {

    // Arrange

    ON_CALL(key, issuerName()).WillByDefault(Return("CN=Issuer"));

    ON_CALL(key, userID(0)).WillByDefault(Return(UserID("uid0", "")));

    ON_CALL(key, userID(1)).WillByDefault(Return(UserID("uid1", "")));

    ON_CALL(key.subkey(0)).WillByDefault(Return(Subkey(GpgME::Subkey::AlgoRSA)));



    // Act

    auto certificateInfo = getCertificateInfoFromKey(key, protocol);



    // Assert

    EXPECT_EQ(certificateInfo->subjectInfo.email, "");

}
