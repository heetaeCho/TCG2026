#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/qt5/src/poppler-form.cc"

#include "CryptoSign/CryptoSignFactory.h" // Assuming this is where CryptoSign::Factory is defined

#include "X509CertificateInfo.h" // Assuming this is where X509CertificateInfo is defined



using namespace Poppler;

using namespace testing;



class MockCryptoSignBackend : public CryptoSign::Backend {

public:

    MOCK_METHOD(std::vector<std::unique_ptr<X509CertificateInfo>>, getAvailableSigningCertificates, (), (override));

};



TEST_F(PopplerFormTest_1371, GetAvailableSigningCertificates_ReturnsEmptyVectorWhenNoBackend_1371) {

    EXPECT_CALL(CryptoSign::Factory::createActive(), Times(1)).WillOnce(Return(nullptr));



    QVector<CertificateInfo> result = getAvailableSigningCertificates();



    EXPECT_TRUE(result.isEmpty());

}



TEST_F(PopplerFormTest_1371, GetAvailableSigningCertificates_ReturnsNonEmptyVectorWhenBackendHasCertificates_1371) {

    auto mockBackend = std::make_unique<MockCryptoSignBackend>();

    std::vector<std::unique_ptr<X509CertificateInfo>> mockCerts;

    mockCerts.emplace_back(std::make_unique<X509CertificateInfo>());

    EXPECT_CALL(*mockBackend, getAvailableSigningCertificates()).WillOnce(Return(mockCerts));

    EXPECT_CALL(CryptoSign::Factory::createActive(), Times(1)).WillOnce(Return(ByMove(std::move(mockBackend))));



    QVector<CertificateInfo> result = getAvailableSigningCertificates();



    EXPECT_FALSE(result.isEmpty());

}



TEST_F(PopplerFormTest_1371, GetAvailableSigningCertificates_ReturnsCorrectNumberOfCertificates_1371) {

    auto mockBackend = std::make_unique<MockCryptoSignBackend>();

    std::vector<std::unique_ptr<X509CertificateInfo>> mockCerts;

    mockCerts.emplace_back(std::make_unique<X509CertificateInfo>());

    mockCerts.emplace_back(std::make_unique<X509CertificateInfo>());

    EXPECT_CALL(*mockBackend, getAvailableSigningCertificates()).WillOnce(Return(mockCerts));

    EXPECT_CALL(CryptoSign::Factory::createActive(), Times(1)).WillOnce(Return(ByMove(std::move(mockBackend))));



    QVector<CertificateInfo> result = getAvailableSigningCertificates();



    EXPECT_EQ(result.size(), 2);

}
