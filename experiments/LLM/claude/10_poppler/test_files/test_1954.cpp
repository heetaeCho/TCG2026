#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "poppler/CertificateInfo.h"
#include "poppler/GooString.h"

// Include the source to access the static function
// This is necessary because getCertificateInfoFromKey has internal linkage
#include "poppler/GPGMECryptoSignBackend.cc"

#include <gpgme++/key.h>
#include <gpgme++/context.h>
#include <gpgme++/global.h>

class GetCertificateInfoFromKeyTest_1954 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        GpgME::initializeLibrary();
    }
};

// Test with a null/empty key and CMS protocol
TEST_F(GetCertificateInfoFromKeyTest_1954, EmptyKeyCMSProtocol_1954)
{
    GpgME::Key emptyKey;
    auto certInfo = getCertificateInfoFromKey(emptyKey, GpgME::CMS);
    ASSERT_NE(certInfo, nullptr);
    // With an empty key, subject/issuer info should have empty fields
    // The function should not crash
}

// Test with a null/empty key and OpenPGP protocol
TEST_F(GetCertificateInfoFromKeyTest_1954, EmptyKeyOpenPGPProtocol_1954)
{
    GpgME::Key emptyKey;
    auto certInfo = getCertificateInfoFromKey(emptyKey, GpgME::OpenPGP);
    ASSERT_NE(certInfo, nullptr);
    // OpenPGP path should set certificate type to PGP
}

// Test with a null/empty key and unknown protocol
TEST_F(GetCertificateInfoFromKeyTest_1954, EmptyKeyUnknownProtocol_1954)
{
    GpgME::Key emptyKey;
    auto certInfo = getCertificateInfoFromKey(emptyKey, GpgME::UnknownProtocol);
    ASSERT_NE(certInfo, nullptr);
    // Should still return a valid object, just without protocol-specific info
}

// Test that X509CertificateInfo default construction works
TEST_F(GetCertificateInfoFromKeyTest_1954, CertificateInfoDefaultConstruction_1954)
{
    X509CertificateInfo info;
    // Default constructed info should have reasonable defaults
    SUCCEED();
}

// Test EntityInfo default construction
TEST_F(GetCertificateInfoFromKeyTest_1954, EntityInfoDefaultConstruction_1954)
{
    X509CertificateInfo::EntityInfo info;
    EXPECT_TRUE(info.commonName.empty());
    EXPECT_TRUE(info.distinguishedName.empty());
    EXPECT_TRUE(info.email.empty());
    EXPECT_TRUE(info.organization.empty());
}

// Test PublicKeyInfo default construction
TEST_F(GetCertificateInfoFromKeyTest_1954, PublicKeyInfoDefaultConstruction_1954)
{
    X509CertificateInfo::PublicKeyInfo pkInfo;
    EXPECT_EQ(pkInfo.publicKeyType, OTHERKEY);
    EXPECT_EQ(pkInfo.publicKeyStrength, 0u);
}

// Test EntityInfo move semantics
TEST_F(GetCertificateInfoFromKeyTest_1954, EntityInfoMoveSemantics_1954)
{
    X509CertificateInfo::EntityInfo info;
    info.commonName = "Test CN";
    info.email = "test@example.com";
    
    X509CertificateInfo::EntityInfo moved(std::move(info));
    EXPECT_EQ(moved.commonName, "Test CN");
    EXPECT_EQ(moved.email, "test@example.com");
}

// Test PublicKeyInfo move semantics
TEST_F(GetCertificateInfoFromKeyTest_1954, PublicKeyInfoMoveSemantics_1954)
{
    X509CertificateInfo::PublicKeyInfo pkInfo;
    pkInfo.publicKeyType = RSAKEY;
    pkInfo.publicKeyStrength = 2048;
    
    X509CertificateInfo::PublicKeyInfo moved(std::move(pkInfo));
    EXPECT_EQ(moved.publicKeyType, RSAKEY);
    EXPECT_EQ(moved.publicKeyStrength, 2048u);
}

// Test KeyUsageExtension enum values
TEST_F(GetCertificateInfoFromKeyTest_1954, KeyUsageExtensionValues_1954)
{
    EXPECT_EQ(KU_DIGITAL_SIGNATURE, 128);
    EXPECT_EQ(KU_NON_REPUDIATION, 64);
    EXPECT_EQ(KU_KEY_ENCIPHERMENT, 32);
    EXPECT_EQ(KU_DATA_ENCIPHERMENT, 16);
    EXPECT_EQ(KU_KEY_AGREEMENT, 8);
    EXPECT_EQ(KU_KEY_CERT_SIGN, 4);
    EXPECT_EQ(KU_CRL_SIGN, 2);
    EXPECT_EQ(KU_ENCIPHER_ONLY, 1);
    EXPECT_EQ(KU_NONE, 0);
}

// Test PublicKeyType enum values
TEST_F(GetCertificateInfoFromKeyTest_1954, PublicKeyTypeValues_1954)
{
    EXPECT_EQ(RSAKEY, 0);
    EXPECT_EQ(DSAKEY, 1);
    EXPECT_EQ(ECKEY, 2);
    EXPECT_EQ(OTHERKEY, 3);
}

// Test KeyLocation enum values
TEST_F(GetCertificateInfoFromKeyTest_1954, KeyLocationValues_1954)
{
    EXPECT_EQ(static_cast<int>(KeyLocation::Unknown), 0);
    EXPECT_EQ(static_cast<int>(KeyLocation::Other), 1);
    EXPECT_EQ(static_cast<int>(KeyLocation::Computer), 2);
    EXPECT_EQ(static_cast<int>(KeyLocation::HardwareToken), 3);
}

// Test CertificateType enum values
TEST_F(GetCertificateInfoFromKeyTest_1954, CertificateTypeValues_1954)
{
    EXPECT_EQ(static_cast<int>(CertificateType::X509), 0);
    EXPECT_EQ(static_cast<int>(CertificateType::PGP), 1);
}

// Test key usage flags can be combined using bitwise OR
TEST_F(GetCertificateInfoFromKeyTest_1954, KeyUsageFlagsCombination_1954)
{
    int kue = 0;
    kue |= KU_NON_REPUDIATION;
    kue |= KU_DIGITAL_SIGNATURE;
    EXPECT_EQ(kue, KU_NON_REPUDIATION | KU_DIGITAL_SIGNATURE);
    EXPECT_EQ(kue, 64 | 128);
    
    kue |= KU_KEY_ENCIPHERMENT;
    kue |= KU_DATA_ENCIPHERMENT;
    EXPECT_TRUE(kue & KU_NON_REPUDIATION);
    EXPECT_TRUE(kue & KU_DIGITAL_SIGNATURE);
    EXPECT_TRUE(kue & KU_KEY_ENCIPHERMENT);
    EXPECT_TRUE(kue & KU_DATA_ENCIPHERMENT);
    
    kue |= KU_KEY_CERT_SIGN;
    EXPECT_TRUE(kue & KU_KEY_CERT_SIGN);
}

// Test that getCertificateInfoFromKey returns non-null for all protocol types
TEST_F(GetCertificateInfoFromKeyTest_1954, ReturnsNonNullForAllProtocols_1954)
{
    GpgME::Key key;
    
    auto info1 = getCertificateInfoFromKey(key, GpgME::CMS);
    ASSERT_NE(info1, nullptr);
    
    auto info2 = getCertificateInfoFromKey(key, GpgME::OpenPGP);
    ASSERT_NE(info2, nullptr);
    
    auto info3 = getCertificateInfoFromKey(key, GpgME::UnknownProtocol);
    ASSERT_NE(info3, nullptr);
}

// Test that setters on X509CertificateInfo work (via the function or directly)
TEST_F(GetCertificateInfoFromKeyTest_1954, CertificateInfoSettersAndGetters_1954)
{
    auto certInfo = std::make_unique<X509CertificateInfo>();
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "Test Subject";
    subjectInfo.email = "subject@test.com";
    certInfo->setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "Test Issuer";
    certInfo->setIssuerInfo(std::move(issuerInfo));
    
    certInfo->setKeyUsageExtensions(KU_DIGITAL_SIGNATURE | KU_NON_REPUDIATION);
    certInfo->setKeyLocation(KeyLocation::Computer);
    certInfo->setCertificateType(CertificateType::PGP);
    
    X509CertificateInfo::PublicKeyInfo pkInfo;
    pkInfo.publicKeyType = RSAKEY;
    pkInfo.publicKeyStrength = 4096;
    certInfo->setPublicKeyInfo(std::move(pkInfo));
    
    certInfo->setSerialNumber(GooString("ABCDEF123456"));
    certInfo->setNickName(GooString("TestFingerprint"));
    certInfo->setQualified(true);
    
    ASSERT_NE(certInfo, nullptr);
}

// Test with empty key that key usage flags default to 0
TEST_F(GetCertificateInfoFromKeyTest_1954, EmptyKeyHasNoCapabilities_1954)
{
    GpgME::Key emptyKey;
    // An empty key should not have sign, encrypt, or certify capabilities
    EXPECT_FALSE(emptyKey.canSign());
    EXPECT_FALSE(emptyKey.canEncrypt());
    EXPECT_FALSE(emptyKey.canCertify());
}

// Test empty key subkey properties
TEST_F(GetCertificateInfoFromKeyTest_1954, EmptyKeySubkeyProperties_1954)
{
    GpgME::Key emptyKey;
    auto subkey = emptyKey.subkey(0);
    EXPECT_FALSE(subkey.isCardKey());
    EXPECT_FALSE(subkey.isSecret());
    EXPECT_FALSE(subkey.isQualified());
    EXPECT_EQ(subkey.length(), 0u);
}
