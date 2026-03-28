#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_exception_translator_registry.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"



namespace Catch {

    class MockIExceptionTranslator : public IExceptionTranslator {

    public:

        MOCK_METHOD(bool, translate, (std::string& message), (override));

    };

}



using namespace Catch;

using ::testing::_;



class ExceptionTranslatorRegistryTest_686 : public ::testing::Test {

protected:

    ExceptionTranslatorRegistry registry;

};



TEST_F(ExceptionTranslatorRegistryTest_686, RegisterTranslator_AddsTranslator_686) {

    Detail::unique_ptr<MockIExceptionTranslator> translator(new MockIExceptionTranslator());

    EXPECT_NO_THROW(registry.registerTranslator(CATCH_MOVE(translator)));

}



TEST_F(ExceptionTranslatorRegistryTest_686, TranslateActiveException_NoTranslators_ReturnsEmptyString_686) {

    std::string result = registry.translateActiveException();

    EXPECT_EQ(result, "");

}



TEST_F(ExceptionTranslatorRegistryTest_686, TranslateActiveException_WithTranslator_TranslatesException_686) {

    MockIExceptionTranslator* mockTranslator = new MockIExceptionTranslator;

    std::string translatedMessage = "Translated Exception";

    EXPECT_CALL(*mockTranslator, translate(_)).WillOnce(::testing::SetArgReferee<0>(translatedMessage));



    Detail::unique_ptr<MockIExceptionTranslator> translator(mockTranslator);

    registry.registerTranslator(CATCH_MOVE(translator));



    std::string result = registry.translateActiveException();

    EXPECT_EQ(result, translatedMessage);

}
