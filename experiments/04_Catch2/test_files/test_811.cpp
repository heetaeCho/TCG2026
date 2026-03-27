#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_registrars.hpp"

#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"



using namespace Catch;

using namespace Catch::Detail;



class MockIMutableRegistryHub : public IMutableRegistryHub {

public:

    MOCK_METHOD(void, registerListener, (unique_ptr<EventListenerFactory> factory), (override));

};



class RegisterListenerImplTest_811 : public ::testing::Test {

protected:

    std::shared_ptr<MockIMutableRegistryHub> mockRegistryHub;

    

    void SetUp() override {

        mockRegistryHub = std::make_shared<testing::NiceMock<MockIMutableRegistryHub>>();

        setMutableRegistryHub(mockRegistryHub);

    }

};



TEST_F(RegisterListenerImplTest_811, RegisterValidListener_811) {

    auto listenerFactory = unique_ptr<EventListenerFactory>(new EventListenerFactory());

    

    EXPECT_CALL(*mockRegistryHub, registerListener(::testing::_)).Times(1);

    

    registerListenerImpl(std::move(listenerFactory));

}



TEST_F(RegisterListenerImplTest_811, RegisterNullptrListener_811) {

    auto listenerFactory = unique_ptr<EventListenerFactory>(nullptr);

    

    EXPECT_CALL(*mockRegistryHub, registerListener(::testing::_)).Times(1);

    

    registerListenerImpl(std::move(listenerFactory));

}
