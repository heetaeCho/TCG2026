#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_singletons.hpp"



// Mock interfaces for testing purposes

class MockInterface {

public:

    virtual ~MockInterface() = default;

};



class MockMutableInterface : public MockInterface {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



template <typename SingletonImplT, typename InterfaceT, typename MutableInterfaceT>

class TestSingleton : public Catch::Singleton<SingletonImplT, InterfaceT, MutableInterfaceT> {};



using TestSingletonInstance = TestSingleton<std::remove_reference_t<decltype(*Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>::getInternal())>, MockInterface, MockMutableInterface>;



TEST_F(Catch2SingletonTest_281, GetReturnsConstReference_281) {

    auto& instance = Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>::get();

    EXPECT_EQ(&instance, &Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>::get());

}



TEST_F(Catch2SingletonTest_281, GetMutableReturnsMutableReference_281) {

    auto& mutableInstance = Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>::getMutable();

    EXPECT_EQ(&mutableInstance, &Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>::getMutable());

}



TEST_F(Catch2SingletonTest_281, GetAndGetMutableAreDifferentInstances_281) {

    const auto& instance = Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>::get();

    auto& mutableInstance = Catch::Singleton<MockInterface, MockInterface, MockMutableInterface>::getMutable();

    EXPECT_NE(&instance, &mutableInstance);

}



TEST_F(Catch2SingletonTest_281, GetInternalReturnsNonNullPointer_281) {

    auto* internalPtr = TestSingletonInstance::getInternal();

    EXPECT_NE(nullptr, internalPtr);

}
