#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QByteArray>
#include <QString>
#include <QDateTime>
#include <QTimeZone>

// Include necessary headers
#include "poppler/CertificateInfo.h"
#include "poppler-form.h"
#include "poppler-private.h"

// We need access to the createCertificateInfoPrivate function and CertificateInfoPrivate
// Since createCertificateInfoPrivate is a static function in the Poppler namespace,
// we need to include the source or have it accessible.
// For testing purposes, we'll work with the CertificateInfo public API.

#include "poppler-qt5.h"

namespace {

// Helper to set up a fully populated X509CertificateInfo
std::unique_ptr<X509CertificateInfo> createPopulatedCertInfo() {
    auto ci = std::make_unique<X509CertificateInfo>();
    
    ci->setVersion(3);
    ci->setKeyUsageExtensions(X509CertificateInfo::KU_DIGITAL_SIGNATURE | X509CertificateInfo::KU_NON_REPUDIATION);
    ci->setKeyLocation(KeyLocation::HardwareToken);
    ci->setCertificateType(CertificateType::X509);
    
    GooString serial("12345678");
    ci->setSerialNumber(serial);
    
    X509CertificateInfo::EntityInfo issuer;
    issuer.commonName = "Test Issuer CN";
    issuer.distinguishedName = "CN=Test Issuer CN,O=Test Org";
    issuer.email = "issuer@test.com";
    issuer.organization = "Test Issuer Org";
    ci->setIssuerInfo(std::move(issuer));
    
    X509CertificateInfo::EntityInfo subject;
    subject.commonName = "Test Subject CN";
    subject.distinguishedName = "CN=Test Subject CN,O=Test Subject Org";
    subject.email = "subject@test.com";
    subject.organization = "Test Subject Org";
    ci->setSubjectInfo(std::move(subject));
    
    GooString nick("TestNickName");
    ci->setNickName(nick);
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 1609459200; // 2021-01-01 00:00:00 UTC
    validity.notAfter = 1640995200;  // 2022-01-01 00:00:00 UTC
    ci->setValidity(validity);
    
    X509CertificateInfo::PublicKeyInfo pkInfo;
    GooString pubKey("publicKeyData");
    pkInfo.publicKey = GooString(pubKey);
    pkInfo.publicKeyType = PublicKeyType::RSAKEY;
    pkInfo.publicKeyStrength = 2048;
    ci->setPublicKeyInfo(std::move(pkInfo));
    
    GooString der("certDERdata");
    ci->setCertificateDER(der);
    
    ci->setIsSelfSigned(false);
    
    return ci;
}

} // anonymous namespace

class CreateCertificateInfoPrivateTest_1367 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr creates a null CertificateInfo
TEST_F(CreateCertificateInfoPrivateTest_1367, NullInput_CreatesNullCertInfo_1367) {
    Poppler::CertificateInfo certInfo(nullptr);
    EXPECT_TRUE(certInfo.isNull());
}

// Test that passing a valid X509CertificateInfo creates a non-null CertificateInfo
TEST_F(CreateCertificateInfoPrivateTest_1367, ValidInput_CreatesNonNullCertInfo_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_FALSE(certInfo.isNull());
}

// Test version is correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, VersionIsTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    ci->setVersion(3);
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.version(), 3);
}

// Test serial number is correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, SerialNumberIsTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    GooString serial("ABCDEF");
    ci->setSerialNumber(serial);
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.serialNumber(), QByteArray("ABCDEF", 6));
}

// Test issuer info is correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, IssuerInfoIsTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.issuerInfo().commonName, QString("Test Issuer CN"));
    EXPECT_EQ(certInfo.issuerInfo().distinguishedName, QString("CN=Test Issuer CN,O=Test Org"));
    EXPECT_EQ(certInfo.issuerInfo().emailAddress, QString("issuer@test.com"));
    EXPECT_EQ(certInfo.issuerInfo().organization, QString("Test Issuer Org"));
}

// Test subject info is correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, SubjectInfoIsTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.subjectInfo().commonName, QString("Test Subject CN"));
    EXPECT_EQ(certInfo.subjectInfo().distinguishedName, QString("CN=Test Subject CN,O=Test Subject Org"));
    EXPECT_EQ(certInfo.subjectInfo().emailAddress, QString("subject@test.com"));
    EXPECT_EQ(certInfo.subjectInfo().organization, QString("Test Subject Org"));
}

// Test nick name is correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, NickNameIsTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.nickName(), QString("TestNickName"));
}

// Test validity dates are correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, ValidityDatesAreTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    
    QDateTime expectedStart = QDateTime::fromSecsSinceEpoch(1609459200, QTimeZone::utc());
    QDateTime expectedEnd = QDateTime::fromSecsSinceEpoch(1640995200, QTimeZone::utc());
    
    EXPECT_EQ(certInfo.validityStart(), expectedStart);
    EXPECT_EQ(certInfo.validityEnd(), expectedEnd);
}

// Test public key info is correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, PublicKeyInfoIsTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.publicKey(), QByteArray("publicKeyData", 13));
    EXPECT_EQ(certInfo.publicKeyStrength(), 2048);
}

// Test certificate DER is correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, CertificateDERIsTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.certificateData(), QByteArray("certDERdata", 11));
}

// Test key usage extensions are correctly transferred
TEST_F(CreateCertificateInfoPrivateTest_1367, KeyUsageExtensionsAreTransferred_1367) {
    auto ci = createPopulatedCertInfo();
    ci->setKeyUsageExtensions(X509CertificateInfo::KU_DIGITAL_SIGNATURE);
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_NE(certInfo.keyUsageExtensions(), 0u);
}

// Test with empty strings in certificate info
TEST_F(CreateCertificateInfoPrivateTest_1367, EmptyStringsHandledCorrectly_1367) {
    auto ci = std::make_unique<X509CertificateInfo>();
    
    ci->setVersion(1);
    
    X509CertificateInfo::EntityInfo issuer;
    issuer.commonName = "";
    issuer.distinguishedName = "";
    issuer.email = "";
    issuer.organization = "";
    ci->setIssuerInfo(std::move(issuer));
    
    X509CertificateInfo::EntityInfo subject;
    subject.commonName = "";
    subject.distinguishedName = "";
    subject.email = "";
    subject.organization = "";
    ci->setSubjectInfo(std::move(subject));
    
    GooString emptySerial("");
    ci->setSerialNumber(emptySerial);
    
    GooString emptyNick("");
    ci->setNickName(emptyNick);
    
    GooString emptyDer("");
    ci->setCertificateDER(emptyDer);
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 0;
    validity.notAfter = 0;
    ci->setValidity(validity);
    
    X509CertificateInfo::PublicKeyInfo pkInfo;
    pkInfo.publicKeyStrength = 0;
    ci->setPublicKeyInfo(std::move(pkInfo));
    
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_FALSE(certInfo.isNull());
    EXPECT_EQ(certInfo.issuerInfo().commonName, QString(""));
    EXPECT_EQ(certInfo.subjectInfo().commonName, QString(""));
    EXPECT_EQ(certInfo.serialNumber(), QByteArray("", 0));
    EXPECT_EQ(certInfo.nickName(), QString(""));
}

// Test with zero epoch validity dates
TEST_F(CreateCertificateInfoPrivateTest_1367, ZeroEpochValidityDates_1367) {
    auto ci = std::make_unique<X509CertificateInfo>();
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 0;
    validity.notAfter = 0;
    ci->setValidity(validity);
    
    X509CertificateInfo::EntityInfo issuer;
    ci->setIssuerInfo(std::move(issuer));
    X509CertificateInfo::EntityInfo subject;
    ci->setSubjectInfo(std::move(subject));
    X509CertificateInfo::PublicKeyInfo pkInfo;
    ci->setPublicKeyInfo(std::move(pkInfo));
    
    Poppler::CertificateInfo certInfo(ci.get());
    
    QDateTime epochStart = QDateTime::fromSecsSinceEpoch(0, QTimeZone::utc());
    EXPECT_EQ(certInfo.validityStart(), epochStart);
    EXPECT_EQ(certInfo.validityEnd(), epochStart);
}

// Test with version set to default/negative
TEST_F(CreateCertificateInfoPrivateTest_1367, DefaultVersionValue_1367) {
    auto ci = std::make_unique<X509CertificateInfo>();
    // Default version is -1 according to the header
    
    X509CertificateInfo::EntityInfo issuer;
    ci->setIssuerInfo(std::move(issuer));
    X509CertificateInfo::EntityInfo subject;
    ci->setSubjectInfo(std::move(subject));
    X509CertificateInfo::PublicKeyInfo pkInfo;
    ci->setPublicKeyInfo(std::move(pkInfo));
    X509CertificateInfo::Validity validity;
    validity.notBefore = 0;
    validity.notAfter = 0;
    ci->setValidity(validity);
    
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.version(), -1);
}

// Test binary data in serial number
TEST_F(CreateCertificateInfoPrivateTest_1367, BinarySerialNumber_1367) {
    auto ci = createPopulatedCertInfo();
    
    // Set serial number with embedded null bytes
    char binarySerial[] = {'\x01', '\x00', '\x02', '\x03'};
    GooString serial(binarySerial, 4);
    ci->setSerialNumber(serial);
    
    Poppler::CertificateInfo certInfo(ci.get());
    QByteArray expectedSerial(binarySerial, 4);
    EXPECT_EQ(certInfo.serialNumber(), expectedSerial);
    EXPECT_EQ(certInfo.serialNumber().size(), 4);
}

// Test binary data in certificate DER
TEST_F(CreateCertificateInfoPrivateTest_1367, BinaryCertificateDER_1367) {
    auto ci = createPopulatedCertInfo();
    
    char binaryDer[] = {'\x30', '\x82', '\x00', '\x01', '\x00'};
    GooString der(binaryDer, 5);
    ci->setCertificateDER(der);
    
    Poppler::CertificateInfo certInfo(ci.get());
    QByteArray expectedDer(binaryDer, 5);
    EXPECT_EQ(certInfo.certificateData(), expectedDer);
    EXPECT_EQ(certInfo.certificateData().size(), 5);
}

// Test public key strength boundary value
TEST_F(CreateCertificateInfoPrivateTest_1367, LargePublicKeyStrength_1367) {
    auto ci = createPopulatedCertInfo();
    
    X509CertificateInfo::PublicKeyInfo pkInfo;
    pkInfo.publicKeyStrength = 4096;
    ci->setPublicKeyInfo(std::move(pkInfo));
    
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.publicKeyStrength(), 4096);
}

// Test that key usage extensions with no flags set
TEST_F(CreateCertificateInfoPrivateTest_1367, NoKeyUsageExtensions_1367) {
    auto ci = createPopulatedCertInfo();
    ci->setKeyUsageExtensions(X509CertificateInfo::KU_NONE);
    
    Poppler::CertificateInfo certInfo(ci.get());
    EXPECT_EQ(certInfo.keyUsageExtensions(), 0u);
}

// Test copy semantics of CertificateInfo (if available)
TEST_F(CreateCertificateInfoPrivateTest_1367, CertificateInfoCopy_1367) {
    auto ci = createPopulatedCertInfo();
    Poppler::CertificateInfo certInfo(ci.get());
    
    Poppler::CertificateInfo copy(certInfo);
    EXPECT_FALSE(copy.isNull());
    EXPECT_EQ(copy.nickName(), certInfo.nickName());
    EXPECT_EQ(copy.version(), certInfo.version());
}

// Test large validity timestamps
TEST_F(CreateCertificateInfoPrivateTest_1367, LargeValidityTimestamps_1367) {
    auto ci = createPopulatedCertInfo();
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 2147483647; // Max 32-bit signed
    validity.notAfter = 2147483647;
    ci->setValidity(validity);
    
    Poppler::CertificateInfo certInfo(ci.get());
    
    QDateTime expectedTime = QDateTime::fromSecsSinceEpoch(2147483647, QTimeZone::utc());
    EXPECT_EQ(certInfo.validityStart(), expectedTime);
    EXPECT_EQ(certInfo.validityEnd(), expectedTime);
}
