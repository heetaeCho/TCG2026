#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch;



class ReporterRegistryTest_577 : public ::testing::Test {

protected:

    ReporterRegistry registry;

};



TEST_F(ReporterRegistryTest_577, GetFactories_ReturnsEmptyMap_577) {

    const auto& factories = registry.getFactories();

    EXPECT_TRUE(factories.empty());

}



TEST_F(ReporterRegistryTest_577, RegisterReporter_AddsFactoryToMap_577) {

    IReporterFactoryPtr mockFactory = nullptr; // Assuming IReporterFactoryPtr can be null

    std::string reporterName = "mockReporter";



    registry.registerReporter(reporterName, mockFactory);



    const auto& factories = registry.getFactories();

    EXPECT_EQ(factories.size(), 1);

    EXPECT_TRUE(factories.find(reporterName) != factories.end());

}



TEST_F(ReporterRegistryTest_577, RegisterMultipleReporters_AddsAllToMap_577) {

    IReporterFactoryPtr mockFactory1 = nullptr;

    IReporterFactoryPtr mockFactory2 = nullptr;

    std::string reporterName1 = "mockReporter1";

    std::string reporterName2 = "mockReporter2";



    registry.registerReporter(reporterName1, mockFactory1);

    registry.registerReporter(reporterName2, mockFactory2);



    const auto& factories = registry.getFactories();

    EXPECT_EQ(factories.size(), 2);

    EXPECT_TRUE(factories.find(reporterName1) != factories.end());

    EXPECT_TRUE(factories.find(reporterName2) != factories.end());

}



TEST_F(ReporterRegistryTest_577, RegisterSameReporter_ReplacesExistingFactory_577) {

    IReporterFactoryPtr mockFactory1 = nullptr;

    IReporterFactoryPtr mockFactory2 = nullptr;

    std::string reporterName = "mockReporter";



    registry.registerReporter(reporterName, mockFactory1);

    registry.registerReporter(reporterName, mockFactory2);



    const auto& factories = registry.getFactories();

    EXPECT_EQ(factories.size(), 1);

    EXPECT_TRUE(factories.find(reporterName) != factories.end());

}



TEST_F(ReporterRegistryTest_577, RegisterListener_AddsListenerToVector_577) {

    Detail::unique_ptr<EventListenerFactory> mockListener = nullptr; // Assuming EventListenerFactory can be null



    registry.registerListener(std::move(mockListener));



    const auto& listeners = registry.getListeners();

    EXPECT_EQ(listeners.size(), 1);

}



TEST_F(ReporterRegistryTest_577, RegisterMultipleListeners_AddsAllToListenersVector_577) {

    Detail::unique_ptr<EventListenerFactory> mockListener1 = nullptr;

    Detail::unique_ptr<EventListenerFactory> mockListener2 = nullptr;



    registry.registerListener(std::move(mockListener1));

    registry.registerListener(std::move(mockListener2));



    const auto& listeners = registry.getListeners();

    EXPECT_EQ(listeners.size(), 2);

}
