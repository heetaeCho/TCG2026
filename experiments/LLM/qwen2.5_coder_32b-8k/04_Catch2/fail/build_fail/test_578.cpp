#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"



using namespace Catch;

using ::testing::ElementsAre;



class ReporterRegistryTest_578 : public ::testing::Test {

protected:

    ReporterRegistry registry_;

};



TEST_F(ReporterRegistryTest_578, GetListenersInitiallyEmpty_578) {

    EXPECT_TRUE(registry_.getListeners().empty());

}



TEST_F(ReporterRegistryTest_578, RegisterListenerAddsToListeners_578) {

    auto listenerFactory = Detail::make_unique<EventListenerFactory>();

    registry_.registerListener(std::move(listenerFactory));

    EXPECT_EQ(registry_.getListeners().size(), 1);

}



TEST_F(ReporterRegistryTest_578, RegisterMultipleListeners_578) {

    registry_.registerListener(Detail::make_unique<EventListenerFactory>());

    registry_.registerListener(Detail::make_unique<EventListenerFactory>());

    registry_.registerListener(Detail::make_unique<EventListenerFactory>());

    EXPECT_EQ(registry_.getListeners().size(), 3);

}



TEST_F(ReporterRegistryTest_578, GetFactoriesInitiallyEmpty_578) {

    EXPECT_TRUE(registry_.getFactories().empty());

}



TEST_F(ReporterRegistryTest_578, RegisterReporterAddsToFactories_578) {

    auto reporterFactory = Detail::make_unique<ReporterFactory>();

    registry_.registerReporter("reporter1", std::move(reporterFactory));

    EXPECT_EQ(registry_.getFactories().size(), 1);

}



TEST_F(ReporterRegistryTest_578, RegisterMultipleReporters_578) {

    registry_.registerReporter("reporter1", Detail::make_unique<ReporterFactory>());

    registry_.registerReporter("reporter2", Detail::make_unique<ReporterFactory>());

    registry_.registerReporter("reporter3", Detail::make_unique<ReporterFactory>());

    EXPECT_EQ(registry_.getFactories().size(), 3);

}



TEST_F(ReporterRegistryTest_578, RegisterReporterWithSameNameOverwrites_578) {

    auto reporterFactory1 = Detail::make_unique<ReporterFactory>();

    auto reporterFactory2 = Detail::make_unique<ReporterFactory>();

    registry_.registerReporter("reporter1", std::move(reporterFactory1));

    registry_.registerReporter("reporter1", std::move(reporterFactory2));

    EXPECT_EQ(registry_.getFactories().size(), 1);

}



TEST_F(ReporterRegistryTest_578, CreateWithUnknownNameReturnsNull_578) {

    auto listener = registry_.create("unknown", ReporterConfig{});

    EXPECT_FALSE(listener.get());

}
