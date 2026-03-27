#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_unique_ptr.hpp"

#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"

#include "catch2/catch_translate_exception.cpp"



using namespace Catch;

using namespace Catch::Detail;



class MockIMutableRegistryHub : public IMutableRegistryHub {

public:

    MOCK_METHOD(void, registerReporter, (const std::string &name, IReporterFactoryPtr factory), (override));

    MOCK_METHOD(void, registerListener, (unique_ptr<EventListenerFactory> factory), (override));

    MOCK_METHOD(void, registerTest, (unique_ptr<TestCaseInfo>&& testInfo, unique_ptr<ITestInvoker>&& invoker), (override));

    MOCK_METHOD(void, registerTranslator, (unique_ptr<IExceptionTranslator>&& translator), (override));

    MOCK_METHOD(void, registerTagAlias, (const std::string &alias, const std::string &tag, const SourceLineInfo &lineInfo), (override));

    MOCK_METHOD(void, registerStartupException, (), (override));

    MOCK_METHOD(IMutableEnumValuesRegistry &, getMutableEnumValuesRegistry, (), (override));

};



class RegisterTranslatorTest_248 : public ::testing::Test {

protected:

    MockIMutableRegistryHub mockRegistryHub;

    unique_ptr<IExceptionTranslator> translator;



    void SetUp() override {

        ON_CALL(mockRegistryHub, registerTranslator(::testing::_))

            .WillByDefault([this](unique_ptr<IExceptionTranslator>&& t) { translator = std::move(t); });

    }

};



TEST_F(RegisterTranslatorTest_248, RegisterTranslator_CallsRegisterTranslatorOnRegistryHub_248) {

    // Arrange

    auto mockTranslator = unique_ptr<IExceptionTranslator>(new IExceptionTranslator());



    // Act

    registerTranslatorImpl(std::move(mockTranslator));



    // Assert

    EXPECT_CALL(mockRegistryHub, registerTranslator(::testing::_)).Times(1);

}



TEST_F(RegisterTranslatorTest_248, RegisterTranslator_TranslatorMovedIntoRegistryHub_248) {

    // Arrange

    auto mockTranslator = unique_ptr<IExceptionTranslator>(new IExceptionTranslator());



    // Act

    registerTranslatorImpl(std::move(mockTranslator));



    // Assert

    EXPECT_EQ(translator.get(), nullptr);

}
