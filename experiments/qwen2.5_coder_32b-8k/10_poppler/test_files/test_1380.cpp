#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form.cc"

#include "NSSCryptoSignBackend.h"



namespace Poppler {

    class NSSSignatureConfigurationMock : public NSSSignatureConfiguration {

    public:

        MOCK_STATIC_METHOD1(setNSSPasswordCallback, void(const std::function<char *(const char *)> &));

    };

}



using namespace testing;



TEST_F(NSSSignatureConfigurationTest_1380, SetNSSPasswordCallback_Success_1380) {

    auto mock = NiceMock<Poppler::NSSSignatureConfigurationMock>();



    EXPECT_CALL(mock, setNSSPasswordCallback(_)).Times(1);



    std::function<char *(const char *)> callback = [](const char*) -> char* { return nullptr; };

    Poppler::setNSSPasswordCallback(callback);

}



TEST_F(NSSSignatureConfigurationTest_1380, SetNSSPasswordCallback_NoNSSSupport_1380) {

    auto mock = NiceMock<Poppler::NSSSignatureConfigurationMock>();



    EXPECT_CALL(mock, setNSSPasswordCallback(_)).Times(0);



    std::function<char *(const char *)> callback = [](const char*) -> char* { return nullptr; };

    Poppler::setNSSPasswordCallback(callback);

}



TEST_F(NSSSignatureConfigurationTest_1380, SetNSSPasswordCallback_NullCallback_1380) {

    auto mock = NiceMock<Poppler::NSSSignatureConfigurationMock>();



    EXPECT_CALL(mock, setNSSPasswordCallback(_)).Times(1);



    std::function<char *(const char *)> callback = nullptr;

    Poppler::setNSSPasswordCallback(callback);

}
