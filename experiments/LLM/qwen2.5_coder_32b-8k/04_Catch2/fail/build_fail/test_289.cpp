#include <gtest/gtest.h>

#include "catch2/catch_registry_hub.hpp"

#include "catch2/interfaces/catch_interfaces_exception.hpp"



using namespace Catch;



class MockExceptionTranslatorRegistry : public IExceptionTranslatorRegistry {

public:

    MOCK_CONST_METHOD0(translateActiveException, std::string());

};



class MockRegistryHub : public IRegistryHub {

public:

    MOCK_CONST_METHOD0(getExceptionTranslatorRegistry, const IExceptionTranslatorRegistry&());

};



class TranslateActiveExceptionTest_289 : public ::testing::Test {

protected:

    void SetUp() override {

        registry_hub = std::make_unique<MockRegistryHub>();

        exception_translator_registry = std::make_unique<MockExceptionTranslatorRegistry>();



        ON_CALL(*registry_hub, getExceptionTranslatorRegistry())

            .WillByDefault(testing::ReturnRef(*exception_translator_registry));

    }



    std::unique_ptr<MockRegistryHub> registry_hub;

    std::unique_ptr<MockExceptionTranslatorRegistry> exception_translator_registry;

};



TEST_F(TranslateActiveExceptionTest_289, NormalOperation_TranslatesException_289) {

    EXPECT_CALL(*exception_translator_registry, translateActiveException())

        .WillOnce(testing::Return("Translated Exception"));



    auto result = Catch::translateActiveException();



    EXPECT_EQ(result, "Translated Exception");

}



TEST_F(TranslateActiveExceptionTest_289, NoException_ReturnsEmptyString_289) {

    EXPECT_CALL(*exception_translator_registry, translateActiveException())

        .WillOnce(testing::Return(""));



    auto result = Catch::translateActiveException();



    EXPECT_EQ(result, "");

}



TEST_F(TranslateActiveExceptionTest_289, MultipleCalls_AllTranslated_289) {

    EXPECT_CALL(*exception_translator_registry, translateActiveException())

        .Times(3)

        .WillRepeatedly(testing::Return("Translated Exception"));



    for (int i = 0; i < 3; ++i) {

        auto result = Catch::translateActiveException();

        EXPECT_EQ(result, "Translated Exception");

    }

}
