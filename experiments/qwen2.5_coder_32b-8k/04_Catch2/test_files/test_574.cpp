#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"

#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"

#include "catch2/reporter/catch_reporter_streaming_base.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockReporterFactory : public IReporterFactory {

public:

    MOCK_METHOD(IEventListenerPtr, create, (ReporterConfig&& config), (override));

    MOCK_METHOD(std::string, getDescription, (), (const, override));

};



TEST_F(ReporterRegistryTest_574, CreateReturnsNullptrForUnknownName_574) {

    ReporterRegistry registry;

    ReporterConfig config(nullptr, nullptr, ColourMode::None, {});

    EXPECT_EQ(registry.create("unknown", std::move(config)), nullptr);

}



TEST_F(ReporterRegistryTest_574, CreateReturnsNonNullptrForRegisteredName_574) {

    ReporterRegistry registry;

    auto mockFactory = std::make_shared<MockReporterFactory>();

    ReporterConfig config(nullptr, nullptr, ColourMode::None, {});

    

    EXPECT_CALL(*mockFactory, create(_)).WillOnce(Return(IEventListenerPtr(new StreamingReporterBase())));

    registry.registerReporter("known", mockFactory);

    

    EXPECT_NE(registry.create("known", std::move(config)), nullptr);

}



TEST_F(ReporterRegistryTest_574, RegisterReporterAddsToFactories_574) {

    ReporterRegistry registry;

    auto mockFactory = std::make_shared<MockReporterFactory>();

    registry.registerReporter("test", mockFactory);

    

    EXPECT_EQ(registry.getFactories().count("test"), 1);

}



TEST_F(ReporterRegistryTest_574, RegisterListenerAddsToListeners_574) {

    ReporterRegistry registry;

    auto listenerFactory = std::make_unique<EventListenerFactory>();

    registry.registerListener(std::move(listenerFactory));

    

    EXPECT_EQ(registry.getListeners().size(), 1);

}



TEST_F(ReporterRegistryTest_574, GetFactoriesReturnsEmptyMapWhenNoReportersRegistered_574) {

    ReporterRegistry registry;

    EXPECT_TRUE(registry.getFactories().empty());

}



TEST_F(ReporterRegistryTest_574, GetListenersReturnsEmptyVectorWhenNoListenersRegistered_574) {

    ReporterRegistry registry;

    EXPECT_TRUE(registry.getListeners().empty());

}
