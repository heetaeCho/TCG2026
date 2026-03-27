#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CertificateInfo.h"

#include "NSSCryptoSignBackend.h"



using namespace ::testing;



class GetCertificateInfoFromCERTTest_1797 : public Test {

protected:

    CERTCertificate *createMockCert() {

        auto cert = new CERTCertificate();

        // Initialize cert fields with default values or specific test data

        return cert;

    }



    void destroyMockCert(CERTCertificate *cert) {

        delete cert;

    }

};



TEST_F(GetCertificateInfoFromCERTTest_1797, NormalOperation_RsaKey_1797) {

    auto mockCert = createMockCert();

    mockCert->version.data = static_cast<unsigned char*>(PR_Malloc(4));

    mockCert->version.len = 2;

    *reinterpret_cast<int*>(mockCert->version.data) = 0; // version 1



    SECItem serialNumber = {siBuffer, reinterpret_cast<unsigned char*>("123"), 3};

    mockCert->serialNumber = serialNumber;



    SECKEYPublicKey publicKey = {siBuffer, nullptr, rsaKey, {nullptr}, {nullptr}};

    publicKey.u.rsa.modulus.data = reinterpret_cast<unsigned char*>("modulus");

    publicKey.u.rsa.modulus.len = 7;

    EXPECT_CALL(*this, mockExtractPublicKey(mockCert)).WillOnce(Return(&publicKey));



    auto certInfo = getCertificateInfoFromCERT(mockCert);



    EXPECT_EQ(certInfo->getVersion(), 1);

    EXPECT_EQ(certInfo->getSerialNumber()->getCString(), "123");

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKeyType, RSAKEY);

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKey.getCString(), "modulus");



    destroyMockCert(mockCert);

}



TEST_F(GetCertificateInfoFromCERTTest_1797, NormalOperation_DsaKey_1797) {

    auto mockCert = createMockCert();

    mockCert->version.data = static_cast<unsigned char*>(PR_Malloc(4));

    mockCert->version.len = 2;

    *reinterpret_cast<int*>(mockCert->version.data) = 0; // version 1



    SECItem serialNumber = {siBuffer, reinterpret_cast<unsigned char*>("456"), 3};

    mockCert->serialNumber = serialNumber;



    SECKEYPublicKey publicKey = {siBuffer, nullptr, dsaKey, {nullptr}, {nullptr}};

    publicKey.u.dsa.publicValue.data = reinterpret_cast<unsigned char*>("publicvalue");

    publicKey.u.dsa.publicValue.len = 12;

    EXPECT_CALL(*this, mockExtractPublicKey(mockCert)).WillOnce(Return(&publicKey));



    auto certInfo = getCertificateInfoFromCERT(mockCert);



    EXPECT_EQ(certInfo->getVersion(), 1);

    EXPECT_EQ(certInfo->getSerialNumber()->getCString(), "456");

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKeyType, DSAKEY);

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKey.getCString(), "publicvalue");



    destroyMockCert(mockCert);

}



TEST_F(GetCertificateInfoFromCERTTest_1797, NormalOperation_EcKey_1797) {

    auto mockCert = createMockCert();

    mockCert->version.data = static_cast<unsigned char*>(PR_Malloc(4));

    mockCert->version.len = 2;

    *reinterpret_cast<int*>(mockCert->version.data) = 0; // version 1



    SECItem serialNumber = {siBuffer, reinterpret_cast<unsigned char*>("789"), 3};

    mockCert->serialNumber = serialNumber;



    SECKEYPublicKey publicKey = {siBuffer, nullptr, ecKey, {nullptr}, {nullptr}};

    publicKey.u.ec.publicValue.data = reinterpret_cast<unsigned char*>("publicvalue");

    publicKey.u.ec.publicValue.len = 12;

    EXPECT_CALL(*this, mockExtractPublicKey(mockCert)).WillOnce(Return(&publicKey));



    auto certInfo = getCertificateInfoFromCERT(mockCert);



    EXPECT_EQ(certInfo->getVersion(), 1);

    EXPECT_EQ(certInfo->getSerialNumber()->getCString(), "789");

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKeyType, ECKEY);

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKey.getCString(), "publicvalue");



    destroyMockCert(mockCert);

}



TEST_F(GetCertificateInfoFromCERTTest_1797, NormalOperation_OtherKey_1797) {

    auto mockCert = createMockCert();

    mockCert->version.data = static_cast<unsigned char*>(PR_Malloc(4));

    mockCert->version.len = 2;

    *reinterpret_cast<int*>(mockCert->version.data) = 0; // version 1



    SECItem serialNumber = {siBuffer, reinterpret_cast<unsigned char*>("321"), 3};

    mockCert->serialNumber = serialNumber;



    SECKEYPublicKey publicKey = {siBuffer, nullptr, (SECKEYKeyType)99, {nullptr}, {nullptr}};

    EXPECT_CALL(*this, mockExtractPublicKey(mockCert)).WillOnce(Return(&publicKey));



    auto certInfo = getCertificateInfoFromCERT(mockCert);



    EXPECT_EQ(certInfo->getVersion(), 1);

    EXPECT_EQ(certInfo->getSerialNumber()->getCString(), "321");

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKeyType, OTHERKEY);



    destroyMockCert(mockCert);

}



TEST_F(GetCertificateInfoFromCERTTest_1797, PublicKeyNull_1797) {

    auto mockCert = createMockCert();

    mockCert->version.data = static_cast<unsigned char*>(PR_Malloc(4));

    mockCert->version.len = 2;

    *reinterpret_cast<int*>(mockCert->version.data) = 0; // version 1



    SECItem serialNumber = {siBuffer, reinterpret_cast<unsigned char*>("654"), 3};

    mockCert->serialNumber = serialNumber;



    EXPECT_CALL(*this, mockExtractPublicKey(mockCert)).WillOnce(Return(nullptr));



    auto certInfo = getCertificateInfoFromCERT(mockCert);



    EXPECT_EQ(certInfo->getVersion(), 1);

    EXPECT_EQ(certInfo->getSerialNumber()->getCString(), "654");

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKeyType, OTHERKEY);



    destroyMockCert(mockCert);

}



TEST_F(GetCertificateInfoFromCERTTest_1797, BoundaryCondition_VersionMax_1797) {

    auto mockCert = createMockCert();

    mockCert->version.data = static_cast<unsigned char*>(PR_Malloc(4));

    mockCert->version.len = 2;

    *reinterpret_cast<int*>(mockCert->version.data) = std::numeric_limits<int>::max(); // max version



    SECItem serialNumber = {siBuffer, reinterpret_cast<unsigned char*>("987"), 3};

    mockCert->serialNumber = serialNumber;



    SECKEYPublicKey publicKey = {siBuffer, nullptr, rsaKey, {nullptr}, {nullptr}};

    publicKey.u.rsa.modulus.data = reinterpret_cast<unsigned char*>("modulus");

    publicKey.u.rsa.modulus.len = 7;

    EXPECT_CALL(*this, mockExtractPublicKey(mockCert)).WillOnce(Return(&publicKey));



    auto certInfo = getCertificateInfoFromCERT(mockCert);



    EXPECT_EQ(certInfo->getVersion(), std::numeric_limits<int>::max() + 1);

    EXPECT_EQ(certInfo->getSerialNumber()->getCString(), "987");

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKeyType, RSAKEY);

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKey.getCString(), "modulus");



    destroyMockCert(mockCert);

}



TEST_F(GetCertificateInfoFromCERTTest_1797, BoundaryCondition_SerialNumberEmpty_1797) {

    auto mockCert = createMockCert();

    mockCert->version.data = static_cast<unsigned char*>(PR_Malloc(4));

    mockCert->version.len = 2;

    *reinterpret_cast<int*>(mockCert->version.data) = 0; // version 1



    SECItem serialNumber = {siBuffer, nullptr, 0};

    mockCert->serialNumber = serialNumber;



    SECKEYPublicKey publicKey = {siBuffer, nullptr, rsaKey, {nullptr}, {nullptr}};

    publicKey.u.rsa.modulus.data = reinterpret_cast<unsigned char*>("modulus");

    publicKey.u.rsa.modulus.len = 7;

    EXPECT_CALL(*this, mockExtractPublicKey(mockCert)).WillOnce(Return(&publicKey));



    auto certInfo = getCertificateInfoFromCERT(mockCert);



    EXPECT_EQ(certInfo->getVersion(), 1);

    EXPECT_TRUE(certInfo->getSerialNumber()->getCString() == nullptr);

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKeyType, RSAKEY);

    EXPECT_EQ(certInfo->getPublicKeyInfo().publicKey.getCString(), "modulus");



    destroyMockCert(mockCert);

}



SECKEYPublicKey* GetCertificateInfoFromCERTTest_1797::mockExtractPublicKey(CERTCertificate *cert) {

    return CERT_ExtractPublicKey(cert);

}
