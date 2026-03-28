#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-form.cc"

#include "./TestProjects/poppler/poppler/CryptoSignBackend.h"



namespace {



using namespace Poppler;

using namespace CryptoSign;



class MockCryptoSignFactory : public Factory {

public:

    MOCK_STATIC_METHOD0(getAvailable, std::vector<Backend::Type>());

    MOCK_STATIC_METHOD1(convertToBackend, std::optional<Backend::Type>(CryptoSignBackend));

    MOCK_STATIC_METHOD1(setPreferredBackend, void(Backend::Type));

    MOCK_STATIC_METHOD0(activeCryptoSignBackend, CryptoSignBackend());

};



TEST_F(PopplerFormTest_1375, SetActiveCryptoSignBackend_Successful_1375) {

    std::vector<Backend::Type> availableBackends = {Backend::Type::Gpg};

    Backend::Type convertedBackend = Backend::Type::Gpg;

    EXPECT_CALL(MockCryptoSignFactory::getAvailable(), Times(1)).WillOnce(testing::Return(availableBackends));

    EXPECT_CALL(MockCryptoSignFactory::convertToBackend(CryptoSignBackend::Gpg), Times(1)).WillOnce(testing::Return(convertedBackend));

    EXPECT_CALL(MockCryptoSignFactory::setPreferredBackend(convertedBackend), Times(1));



    bool result = setActiveCryptoSignBackend(CryptoSignBackend::Gpg);

    EXPECT_TRUE(result);

}



TEST_F(PopplerFormTest_1375, SetActiveCryptoSignBackend_UnavailableBackend_1375) {

    std::vector<Backend::Type> availableBackends = {Backend::Type::Pkcs12};

    EXPECT_CALL(MockCryptoSignFactory::getAvailable(), Times(1)).WillOnce(testing::Return(availableBackends));



    bool result = setActiveCryptoSignBackend(CryptoSignBackend::Gpg);

    EXPECT_FALSE(result);

}



TEST_F(PopplerFormTest_1375, SetActiveCryptoSignBackend_ConversionFailure_1375) {

    std::vector<Backend::Type> availableBackends = {Backend::Type::Gpg};

    EXPECT_CALL(MockCryptoSignFactory::getAvailable(), Times(1)).WillOnce(testing::Return(availableBackends));

    EXPECT_CALL(MockCryptoSignFactory::convertToBackend(CryptoSignBackend::Gpg), Times(1)).WillOnce(testing::Return(std::nullopt));



    bool result = setActiveCryptoSignBackend(CryptoSignBackend::Gpg);

    EXPECT_FALSE(result);

}



TEST_F(PopplerFormTest_1375, SetActiveCryptoSignBackend_BackendMismatch_1375) {

    std::vector<Backend::Type> availableBackends = {Backend::Type::Gpg};

    Backend::Type convertedBackend = Backend::Type::Pkcs12;

    EXPECT_CALL(MockCryptoSignFactory::getAvailable(), Times(1)).WillOnce(testing::Return(availableBackends));

    EXPECT_CALL(MockCryptoSignFactory::convertToBackend(CryptoSignBackend::Gpg), Times(1)).WillOnce(testing::Return(convertedBackend));

    EXPECT_CALL(MockCryptoSignFactory::setPreferredBackend(convertedBackend), Times(1));

    EXPECT_CALL(MockCryptoSignFactory::activeCryptoSignBackend(), Times(1)).WillOnce(testing::Return(CryptoSignBackend::Pkcs12));



    bool result = setActiveCryptoSignBackend(CryptoSignBackend::Gpg);

    EXPECT_FALSE(result);

}



}  // namespace
