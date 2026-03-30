#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"



using namespace Catch;



class ReporterRegistryTest_1088 : public ::testing::Test {

protected:

    ReporterRegistry registry;

};



TEST_F(ReporterRegistryTest_1088, GetFactories_ReturnsDefaultReporters_1088) {

    const auto& factories = registry.getFactories();

    EXPECT_EQ(factories.size(), 9);

    EXPECT_TRUE(factories.find("Automake") != factories.end());

    EXPECT_TRUE(factories.find("compact") != factories.end());

    EXPECT_TRUE(factories.find("console") != factories.end());

    EXPECT_TRUE(factories.find("JUnit") != factories.end());

    EXPECT_TRUE(factories.find("SonarQube") != factories.end());

    EXPECT_TRUE(factories.find("TAP") != factories.end());

    EXPECT_TRUE(factories.find("TeamCity") != factories.end());

    EXPECT_TRUE(factories.find("XML") != factories.end());

    EXPECT_TRUE(factories.find("JSON") != factories.end());

}



TEST_F(ReporterRegistryTest_1088, GetListeners_ReturnsEmptyVectorInitially_1088) {

    const auto& listeners = registry.getListeners();

    EXPECT_TRUE(listeners.empty());

}



TEST_F(ReporterRegistryTest_1088, RegisterReporter_AddsNewReporter_1088) {

    auto mockFactory = std::make_shared<MockIReporterFactory>();

    registry.registerReporter("MyCustomReporter", mockFactory);



    const auto& factories = registry.getFactories();

    EXPECT_EQ(factories.size(), 10);

    EXPECT_TRUE(factories.find("MyCustomReporter") != factories.end());

}



TEST_F(ReporterRegistryTest_1088, RegisterListener_AddsNewListener_1088) {

    auto mockFactory = Detail::make_unique<MockEventListenerFactory>();

    registry.registerListener(std::move(mockFactory));



    const auto& listeners = registry.getListeners();

    EXPECT_EQ(listeners.size(), 1);

}



TEST_F(ReporterRegistryTest_1088, Create_ReturnsNullptrForUnknownName_1088) {

    ReporterConfig config;

    auto result = registry.create("UnknownReporter", std::move(config));

    EXPECT_EQ(result.get(), nullptr);

}



// Mock classes for IReporterFactory and EventListenerFactory

class MockIReporterFactory : public IReporterFactory {

public:

    MOCK_METHOD(IEventListenerPtr, create, (ReporterConfig &&config), (override));

};



class MockEventListenerFactory : public EventListenerFactory {

public:

    MOCK_METHOD(EventListenerPtr, create, (), (const, override));

};
