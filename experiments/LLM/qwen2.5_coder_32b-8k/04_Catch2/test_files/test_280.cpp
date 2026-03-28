#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_singletons.hpp"



// Mocking the InterfaceT and MutableInterfaceT for testing purposes

struct MockInterface {

    MOCK_CONST_METHOD0(someMethod, int());

};



struct MockMutableInterface {

    MOCK_METHOD0(modifySomething, void());

};



// Test fixture class

class SingletonTest_280 : public ::testing::Test {

protected:

    using TestSingleton = Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>;

};



// Test case for normal operation - getting the const reference

TEST_F(SingletonTest_280, GetReturnsConstReference_280) {

    EXPECT_CALL(*reinterpret_cast<MockInterface*>(TestSingleton::getInternal()), someMethod())

        .Times(1)

        .WillOnce(::testing::Return(42));



    int result = TestSingleton::get().someMethod();

    EXPECT_EQ(result, 42);

}



// Test case for normal operation - getting the mutable reference

TEST_F(SingletonTest_280, GetMutableReturnsMutableReference_280) {

    EXPECT_CALL(*reinterpret_cast<MockMutableInterface*>(TestSingleton::getInternal()), modifySomething())

        .Times(1);



    TestSingleton::getMutable().modifySomething();

}



// Test case for boundary condition - ensuring get() and getMutable() return the same instance

TEST_F(SingletonTest_280, GetAndGetMutableReturnSameInstance_280) {

    EXPECT_EQ(&TestSingleton::get(), reinterpret_cast<const MockInterface*>(&TestSingleton::getMutable()));

}
