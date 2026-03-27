#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/pdfsig.cc"



using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



class MockCryptoSignBackend : public CryptoSign::Factory::Active {

public:

    MOCK_METHOD(std::vector<std::unique_ptr<X509CertificateInfo>>, getAvailableSigningCertificates, (), (override));

};



class MockCryptoSignFactory : public CryptoSign::Factory {

public:

    static std::shared_ptr<CryptoSign::Factory::Active> createActive() {

        return mockBackend;

    }



    static void setMockBackend(std::shared_ptr<MockCryptoSignBackend> backend) {

        mockBackend = backend;

    }



private:

    static std::shared_ptr<MockCryptoSignBackend> mockBackend;

};



std::shared_ptr<MockCryptoSignBackend> MockCryptoSignFactory::mockBackend = nullptr;



class PdfSigTest : public ::testing::Test {

protected:

    void SetUp() override {

        originalCreateActive = CryptoSign::Factory::createActive;

        CryptoSign::Factory::createActive = &MockCryptoSignFactory::createActive;

    }



    void TearDown() override {

        CryptoSign::Factory::createActive = originalCreateActive;

        MockCryptoSignFactory::setMockBackend(nullptr);

        GooString::nssPassword.clear();

    }



    using CreateActiveFunc = std::shared_ptr<CryptoSign::Factory::Active> (*)();

    CreateActiveFunc originalCreateActive;

};



TEST_F(PdfSigTest, GetAvailableSigningCertificates_Success_2684) {

    auto mockBackend = std::make_shared<MockCryptoSignBackend>();

    MockCryptoSignFactory::setMockBackend(mockBackend);



    std::vector<std::unique_ptr<X509CertificateInfo>> expectedCerts;

    expectedCerts.push_back(std::make_unique<X509CertificateInfo>());

    expectedCerts.push_back(std::make_unique<X509CertificateInfo>());



    EXPECT_CALL(*mockBackend, getAvailableSigningCertificates())

        .WillOnce(Return(expectedCerts));



    bool error = false;

    auto certs = getAvailableSigningCertificates(&error);



    ASSERT_FALSE(error);

    ASSERT_EQ(certs.size(), 2u);

}



TEST_F(PdfSigTest, GetAvailableSigningCertificates_NoBackends_2684) {

    auto mockBackend = std::make_shared<MockCryptoSignBackend>();

    MockCryptoSignFactory::setMockBackend(mockBackend);



    EXPECT_CALL(*mockBackend, getAvailableSigningCertificates())

        .Times(0);



    CryptoSign::Factory::createActive = []() -> std::shared_ptr<CryptoSign::Factory::Active> {

        return nullptr;

    };



    bool error = false;

    auto certs = getAvailableSigningCertificates(&error);



    ASSERT_TRUE(error);

    ASSERT_EQ(certs.size(), 0u);

}



TEST_F(PdfSigTest, GetAvailableSigningCertificates_PasswordNeeded_2684) {

    GooString::nssPassword = "wrong_password";



    auto mockBackend = std::make_shared<MockCryptoSignBackend>();

    MockCryptoSignFactory::setMockBackend(mockBackend);



    EXPECT_CALL(*mockBackend, getAvailableSigningCertificates())

        .Times(0);



    bool error = false;

    auto certs = getAvailableSigningCertificates(&error);



    ASSERT_TRUE(error);

    ASSERT_EQ(certs.size(), 0u);

}



TEST_F(PdfSigTest, GetAvailableSigningCertificates_WrongPassword_2684) {

    GooString::nssPassword = "wrong_password";



    auto mockBackend = std::make_shared<MockCryptoSignBackend>();

    MockCryptoSignFactory::setMockBackend(mockBackend);



    EXPECT_CALL(*mockBackend, getAvailableSigningCertificates())

        .Times(0);



    bool error = false;

    auto certs = getAvailableSigningCertificates(&error);



    ASSERT_TRUE(error);

    ASSERT_EQ(certs.size(), 0u);

}
