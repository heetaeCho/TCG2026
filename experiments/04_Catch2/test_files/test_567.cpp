#include <gtest/gtest.h>

#include "catch_reporter_registrars.hpp"

#include <gmock/gmock.h>



using namespace Catch;



class MockEventListenerFactory : public EventListenerFactory {

public:

    MOCK_METHOD(IEventListenerPtr, create, (IConfig const* config), (const, override));

    MOCK_METHOD(std::string, getDescription, (), (const, override));

};



class ListenerRegistrarTest_567 : public ::testing::Test {

protected:

    MockEventListenerFactory mockFactory;

    std::string listenerName = "MockListener";

    TypedListenerFactory typedFactory{StringRef(listenerName)};

};



TEST_F(ListenerRegistrarTest_567, GetName_ReturnsCorrectName_567) {

    EXPECT_EQ(typedFactory.getName().c_str(), listenerName);

}



TEST_F(ListenerRegistrarTest_567, Create_DelegatesToEventListenerFactoryCreate_567) {

    auto mockConfig = static_cast<IConfig const*>(nullptr);

    EXPECT_CALL(mockFactory, create(mocking::Eq(mockConfig)))

        .Times(1);



    typedFactory.create(mockConfig);

}



TEST_F(ListenerRegistrarTest_567, GetDescription_DelegatesToEventListenerFactoryGetDescription_567) {

    std::string description = "Mock Description";

    EXPECT_CALL(mockFactory, getDescription())

        .WillOnce(::testing::Return(description));



    EXPECT_EQ(typedFactory.getDescription(), description);

}
