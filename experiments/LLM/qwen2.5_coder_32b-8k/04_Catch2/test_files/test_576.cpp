#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reporter_registry.hpp"



using namespace Catch;

using namespace Catch::Detail;



class MockEventListenerFactory : public EventListenerFactory {

public:

    MOCK_METHOD(IEventListenerPtr, create, (ReporterConfig&& config), (override));

};



class ReporterRegistryTest_576 : public ::testing::Test {

protected:

    ReporterRegistry registry_;

    std::unique_ptr<MockEventListenerFactory> mockFactory1_;

    std::unique_ptr<MockEventListenerFactory> mockFactory2_;



    void SetUp() override {

        mockFactory1_ = std::make_unique<MockEventListenerFactory>();

        mockFactory2_ = std::make_unique<MockEventListenerFactory>();

    }

};



TEST_F(ReporterRegistryTest_576, RegisterListener_AddsToListenersList_576) {

    registry_.registerListener(Catch::Detail::unique_ptr<EventListenerFactory>(mockFactory1_.release()));



    auto listeners = registry_.getListeners();

    EXPECT_EQ(listeners.size(), 1);

}



TEST_F(ReporterRegistryTest_576, RegisterMultipleListeners_AllAreAddedToListenersList_576) {

    registry_.registerListener(Catch::Detail::unique_ptr<EventListenerFactory>(mockFactory1_.release()));

    registry_.registerListener(Catch::Detail::unique_ptr<EventListenerFactory>(mockFactory2_.release()));



    auto listeners = registry_.getListeners();

    EXPECT_EQ(listeners.size(), 2);

}



TEST_F(ReporterRegistryTest_576, RegisterNullptrListener_DoesNotAddToListenersList_576) {

    registry_.registerListener(Catch::Detail::unique_ptr<EventListenerFactory>(nullptr));



    auto listeners = registry_.getListeners();

    EXPECT_EQ(listeners.size(), 0);

}



TEST_F(ReporterRegistryTest_576, GetListeners_ReturnsCorrectListenersList_576) {

    registry_.registerListener(Catch::Detail::unique_ptr<EventListenerFactory>(mockFactory1_.release()));



    auto listeners = registry_.getListeners();

    EXPECT_EQ(listeners.size(), 1);

}



TEST_F(ReporterRegistryTest_576, RegisterListener_AfterGettingListeners_DoesNotAffectPreviousList_576) {

    auto initialListeners = registry_.getListeners();



    registry_.registerListener(Catch::Detail::unique_ptr<EventListenerFactory>(mockFactory1_.release()));



    EXPECT_EQ(initialListeners.size(), 0);

}
