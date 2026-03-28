#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CryptoSignBackend.h"

#include <optional>

#include <vector>

#include <memory>



using namespace CryptoSign;



namespace {



class FactoryTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset preferred backend to ensure clean state for each test

        setenv("POPPLER_SIGNATURE_BACKEND", "", 1);

        Factory::setPreferredBackend(Backend::Type{});

    }

};



TEST_F(FactoryTest_1961, GetActive_NoPreferredBackendOrEnvironment_DefaultsToCompiledDefault_1961) {

    auto active = Factory::getActive();

    ASSERT_TRUE(active.has_value());

}



TEST_F(FactoryTest_1961, GetActive_PreferredBackendSet_ReturnsPreferredBackend_1961) {

    Backend::Type preferredBackend{1};

    Factory::setPreferredBackend(preferredBackend);

    auto active = Factory::getActive();

    ASSERT_TRUE(active.has_value());

    EXPECT_EQ(*active, preferredBackend);

}



TEST_F(FactoryTest_1961, GetActive_EnvironmentVariableSet_ReturnsEnvironmentBackend_1961) {

    Backend::Type envBackend{2};

    setenv("POPPLER_SIGNATURE_BACKEND", "backend_type_2", 1);

    EXPECT_CALL(*this, typeFromStringMock("backend_type_2")).WillOnce(::testing::Return(envBackend));

    auto active = Factory::getActive();

    ASSERT_TRUE(active.has_value());

    EXPECT_EQ(*active, envBackend);

}



TEST_F(FactoryTest_1961, GetActive_InvalidEnvironmentVariable_DefaultsToCompiledDefault_1961) {

    setenv("POPPLER_SIGNATURE_BACKEND", "invalid_backend_type", 1);

    EXPECT_CALL(*this, typeFromStringMock("invalid_backend_type")).WillOnce(::testing::Return(std::nullopt));

    auto active = Factory::getActive();

    ASSERT_TRUE(active.has_value());

}



TEST_F(FactoryTest_1961, GetActive_ValidEnvironmentVariable_ReturnsExpectedBackend_1961) {

    Backend::Type envBackend{3};

    setenv("POPPLER_SIGNATURE_BACKEND", "backend_type_3", 1);

    EXPECT_CALL(*this, typeFromStringMock("backend_type_3")).WillOnce(::testing::Return(envBackend));

    auto active = Factory::getActive();

    ASSERT_TRUE(active.has_value());

    EXPECT_EQ(*active, envBackend);

}



// Mocking the typeFromString function

class MockFactory : public Factory {

public:

    MOCK_METHOD(std::optional<Backend::Type>, typeFromString, (std::string_view string), (override));

};



TEST_F(FactoryTest_1961, GetActive_TypeFromStringFails_ReturnsCompiledDefault_1961) {

    Backend::Type compiledDefault{4};

    setenv("POPPLER_SIGNATURE_BACKEND", "invalid_backend_type", 1);

    MockFactory mockFactory;

    EXPECT_CALL(mockFactory, typeFromString("invalid_backend_type")).WillOnce(::testing::Return(std::nullopt));

    auto active = Factory::getActive();

    ASSERT_TRUE(active.has_value());

}



} // namespace
