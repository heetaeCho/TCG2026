#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form.cc"

#include "CertificateInfo.h"



using namespace Poppler;

using testing::NiceMock;



class MockX509CertificateInfo : public X509CertificateInfo {

public:

    MOCK_CONST_METHOD0(getVersion, int());

    MOCK_CONST_METHOD0(getSerialNumber, const GooString &());

    MOCK_CONST_METHOD0(getNickName, const GooString &());

    MOCK_CONST_METHOD0(getIssuerInfo, const EntityInfo &());

    MOCK_CONST_METHOD0(getValidity, const Validity &());

    MOCK_CONST_METHOD0(getSubjectInfo, const EntityInfo &());

    MOCK_CONST_METHOD0(getPublicKeyInfo, const PublicKeyInfo &());

    MOCK_CONST_METHOD0(getKeyUsageExtensions, unsigned int());

    MOCK_CONST_METHOD0(getCertificateDER, const GooString &());

    MOCK_CONST_METHOD0(isQualified, bool());

    MOCK_CONST_METHOD0(getIsSelfSigned, bool());

    MOCK_CONST_METHOD0(getKeyLocation, KeyLocation());

    MOCK_CONST_METHOD0(getCertificateType, CertificateType());



    EntityInfo mockIssuerInfo;

    EntityInfo mockSubjectInfo;

    PublicKeyInfo mockPublicKeyInfo;

    Validity mockValidity;

    GooString mockSerialNumber;

    GooString mockNickName;

    GooString mockCertDer;

};



class CertificateInfoPrivateTest : public ::testing::Test {

protected:

    NiceMock<MockX509CertificateInfo> mockCertInfo;



    void SetUp() override {

        // Set up common expectations for the mock object

        ON_CALL(mockCertInfo, getVersion()).WillByDefault(testing::Return(3));

        ON_CALL(mockCertInfo, getSerialNumber()).WillByDefault(testing::ReturnRef(mockSerialNumber));

        ON_CALL(mockCertInfo, getNickName()).WillByDefault(testing::ReturnRef(mockNickName));

        ON_CALL(mockCertInfo, getIssuerInfo()).WillByDefault(testing::ReturnRef(mockIssuerInfo));

        ON_CALL(mockCertInfo, getValidity()).WillByDefault(testing::ReturnRef(mockValidity));

        ON_CALL(mockCertInfo, getSubjectInfo()).WillByDefault(testing::ReturnRef(mockSubjectInfo));

        ON_CALL(mockCertInfo, getPublicKeyInfo()).WillByDefault(testing::ReturnRef(mockPublicKeyInfo));

        ON_CALL(mockCertInfo, getKeyUsageExtensions()).WillByDefault(testing::Return(0x10));

        ON_CALL(mockCertInfo, getCertificateDER()).WillByDefault(testing::ReturnRef(mockCertDer));

    }

};



TEST_F(CertificateInfoPrivateTest_1367, CreateWithNullPointer_1367) {

    CertificateInfoPrivate *certPriv = createCertificateInfoPrivate(nullptr);

    EXPECT_TRUE(certPriv->is_null);

    delete certPriv;

}



TEST_F(CertificateInfoPrivateTest_1367, CreateWithValidCert_1367) {

    mockSerialNumber.append("12345");

    mockNickName.append("testNick");



    CertificateInfoPrivate *certPriv = createCertificateInfoPrivate(&mockCertInfo);

    EXPECT_FALSE(certPriv->is_null);

    EXPECT_EQ(certPriv->version, 3);

    EXPECT_EQ(certPriv->ku_extensions, 0x10);

    EXPECT_EQ(certPriv->serial_number, QByteArray("12345", 5));

    EXPECT_EQ(certPriv->nick_name, QString::fromStdString(mockNickName.toStr()));

    delete certPriv;

}



TEST_F(CertificateInfoPrivateTest_1367, VerifyIssuerInfoCopied_1367) {

    mockIssuerInfo.commonName = "CN=Example Issuer";

    mockIssuerInfo.distinguishedName = "DN=Example DN";

    mockIssuerInfo.email = "issuer@example.com";

    mockIssuerInfo.organization = "Example Org";



    CertificateInfoPrivate *certPriv = createCertificateInfoPrivate(&mockCertInfo);

    EXPECT_EQ(certPriv->issuer_info.common_name, QString::fromStdString(mockIssuerInfo.commonName));

    EXPECT_EQ(certPriv->issuer_info.distinguished_name, QString::fromStdString(mockIssuerInfo.distinguishedName));

    EXPECT_EQ(certPriv->issuer_info.email_address, QString::fromStdString(mockIssuerInfo.email));

    EXPECT_EQ(certPriv->issuer_info.org_name, QString::fromStdString(mockIssuerInfo.organization));

    delete certPriv;

}



TEST_F(CertificateInfoPrivateTest_1367, VerifySubjectInfoCopied_1367) {

    mockSubjectInfo.commonName = "CN=Example Subject";

    mockSubjectInfo.distinguishedName = "DN=Example DN";

    mockSubjectInfo.email = "subject@example.com";

    mockSubjectInfo.organization = "Example Org";



    CertificateInfoPrivate *certPriv = createCertificateInfoPrivate(&mockCertInfo);

    EXPECT_EQ(certPriv->subject_info.common_name, QString::fromStdString(mockSubjectInfo.commonName));

    EXPECT_EQ(certPriv->subject_info.distinguished_name, QString::fromStdString(mockSubjectInfo.distinguishedName));

    EXPECT_EQ(certPriv->subject_info.email_address, QString::fromStdString(mockSubjectInfo.email));

    EXPECT_EQ(certPriv->subject_info.org_name, QString::fromStdString(mockSubjectInfo.organization));

    delete certPriv;

}



TEST_F(CertificateInfoPrivateTest_1367, VerifyPublicKeyInfoCopied_1367) {

    mockPublicKeyInfo.publicKey.append("public_key_data");

    mockPublicKeyInfo.publicKeyType = OTHERKEY;

    mockPublicKeyInfo.publicKeyStrength = 2048;



    CertificateInfoPrivate *certPriv = createCertificateInfoPrivate(&mockCertInfo);

    EXPECT_EQ(certPriv->public_key, QByteArray(mockPublicKeyInfo.publicKey.c_str(), mockPublicKeyInfo.publicKey.size()));

    EXPECT_EQ(certPriv->public_key_type, static_cast<int>(mockPublicKeyInfo.publicKeyType));

    EXPECT_EQ(certPriv->public_key_strength, mockPublicKeyInfo.publicKeyStrength);

    delete certPriv;

}



TEST_F(CertificateInfoPrivateTest_1367, VerifyValidityDatesConverted_1367) {

    mockValidity.notBefore = 1609459200; // Jan 1, 2021

    mockValidity.notAfter = 1640995199;  // Dec 31, 2021



    CertificateInfoPrivate *certPriv = createCertificateInfoPrivate(&mockCertInfo);

    EXPECT_EQ(certPriv->validity_start, QDateTime::fromSecsSinceEpoch(mockValidity.notBefore, QTimeZone::utc()));

    EXPECT_EQ(certPriv->validity_end, QDateTime::fromSecsSinceEpoch(mockValidity.notAfter, QTimeZone::utc()));

    delete certPriv;

}



TEST_F(CertificateInfoPrivateTest_1367, VerifyCertDerCopied_1367) {

    mockCertDer.append("certificate_der_data");



    CertificateInfoPrivate *certPriv = createCertificateInfoPrivate(&mockCertInfo);

    EXPECT_EQ(certPriv->certificate_der, QByteArray(mockCertDer.c_str(), mockCertDer.size()));

    delete certPriv;

}
