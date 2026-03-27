#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib.h>



// Mocking the X509CertificateInfo class and CryptoSign::Factory for testing purposes.

class X509CertificateInfo {

public:

    virtual ~X509CertificateInfo() = default;

};



class MockX509CertificateInfo : public X509CertificateInfo {

public:

    MOCK_METHOD(void, dummyMethod, (), (const));

};



namespace CryptoSign {

    class Backend {

    public:

        virtual ~Backend() = default;

        virtual std::vector<std::unique_ptr<X509CertificateInfo>> getAvailableSigningCertificates() const = 0;

    };



    class Factory {

    public:

        static Backend* createActive();

    };

}



class MockCryptoSignBackend : public CryptoSign::Backend {

public:

    MOCK_METHOD(std::vector<std::unique_ptr<X509CertificateInfo>>, getAvailableSigningCertificates, (), (const));

};



// Global mock backend pointer

MockCryptoSignBackend* g_mockBackend = nullptr;



namespace CryptoSign {

    Backend* Factory::createActive() {

        return g_mockBackend;

    }

}



extern "C" GList *poppler_get_available_signing_certificates(void);



class PopplerFormFieldTest_2407 : public ::testing::Test {

protected:

    void SetUp() override {

        g_mockBackend = new MockCryptoSignBackend();

    }



    void TearDown() override {

        delete g_mockBackend;

        g_mockBackend = nullptr;



        // Free any remaining GList elements

        if (result_list) {

            g_list_free_full(result_list, [](gpointer data) { g_free(data); });

            result_list = nullptr;

        }

    }



    MockCryptoSignBackend* getMockBackend() {

        return g_mockBackend;

    }



    GList* getResultList() const {

        return result_list;

    }



    void callFunctionUnderTest() {

        result_list = poppler_get_available_signing_certificates();

    }



private:

    GList* result_list = nullptr;

};



TEST_F(PopplerFormFieldTest_2407, NoCertificatesAvailable_2407) {

    EXPECT_CALL(*getMockBackend(), getAvailableSigningCertificates()).WillOnce(::testing::Return(std::vector<std::unique_ptr<X509CertificateInfo>>{}));



    callFunctionUnderTest();

    

    ASSERT_EQ(getResultList(), nullptr);

}



TEST_F(PopplerFormFieldTest_2407, SingleCertificateAvailable_2407) {

    auto mockCert = std::make_unique<MockX509CertificateInfo>();

    EXPECT_CALL(*getMockBackend(), getAvailableSigningCertificates()).WillOnce(::testing::Return(std::vector<std::unique_ptr<X509CertificateInfo>>{std::move(mockCert)}));



    callFunctionUnderTest();



    ASSERT_NE(getResultList(), nullptr);

    EXPECT_EQ(g_list_length(getResultList()), 1);



    g_list_free_full(getResultList(), [](gpointer data) { g_free(data); });

}



TEST_F(PopplerFormFieldTest_2407, MultipleCertificatesAvailable_2407) {

    auto mockCert1 = std::make_unique<MockX509CertificateInfo>();

    auto mockCert2 = std::make_unique<MockX509CertificateInfo>();



    EXPECT_CALL(*getMockBackend(), getAvailableSigningCertificates()).WillOnce(::testing::Return(std::vector<std::unique_ptr<X509CertificateInfo>>{std::move(mockCert1), std::move(mockCert2)}));



    callFunctionUnderTest();



    ASSERT_NE(getResultList(), nullptr);

    EXPECT_EQ(g_list_length(getResultList()), 2);



    g_list_free_full(getResultList(), [](gpointer data) { g_free(data); });

}



TEST_F(PopplerFormFieldTest_2407, BackendCreationFails_2407) {

    g_mockBackend = nullptr; // Simulate backend creation failure



    callFunctionUnderTest();



    ASSERT_EQ(getResultList(), nullptr);

}
