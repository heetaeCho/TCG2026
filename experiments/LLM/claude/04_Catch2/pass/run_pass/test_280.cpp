#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_singletons.hpp"

// We need to define concrete types to instantiate the Singleton template for testing purposes.

namespace {

// Define a const interface
class IMyInterface {
public:
    virtual ~IMyInterface() = default;
    virtual int getValue() const = 0;
};

// Define a mutable interface
class IMutableInterface {
public:
    virtual ~IMutableInterface() = default;
    virtual void setValue(int v) = 0;
};

// Define a concrete implementation that derives from both interfaces
class MySingletonImpl : public IMyInterface, public IMutableInterface {
public:
    MySingletonImpl() : value_(42) {}
    int getValue() const override { return value_; }
    void setValue(int v) override { value_ = v; }
private:
    int value_;
};

// Create the Singleton type alias for our test
using MySingleton = Catch::Singleton<MySingletonImpl, IMyInterface, IMutableInterface>;

} // anonymous namespace

// Test that get() returns a valid const reference
TEST(SingletonTest_280, GetReturnsConstReference_280) {
    const IMyInterface& instance = MySingleton::get();
    // Just verify we can call a method on the returned reference without crashing
    int val = instance.getValue();
    // The default value should be 42 as set in the constructor
    EXPECT_EQ(val, 42);
}

// Test that get() returns the same instance on multiple calls
TEST(SingletonTest_280, GetReturnsSameInstanceOnMultipleCalls_280) {
    const IMyInterface& instance1 = MySingleton::get();
    const IMyInterface& instance2 = MySingleton::get();
    // Both references should point to the same object
    EXPECT_EQ(&instance1, &instance2);
}

// Test that getMutable() returns a valid mutable reference
TEST(SingletonTest_280, GetMutableReturnsMutableReference_280) {
    IMutableInterface& mutableInstance = MySingleton::getMutable();
    // Should be able to call setValue without crashing
    mutableInstance.setValue(100);

    // Verify through the const interface that the value was changed
    const IMyInterface& constInstance = MySingleton::get();
    EXPECT_EQ(constInstance.getValue(), 100);

    // Reset to original value for other tests
    mutableInstance.setValue(42);
}

// Test that getMutable() returns the same instance on multiple calls
TEST(SingletonTest_280, GetMutableReturnsSameInstanceOnMultipleCalls_280) {
    IMutableInterface& instance1 = MySingleton::getMutable();
    IMutableInterface& instance2 = MySingleton::getMutable();
    EXPECT_EQ(&instance1, &instance2);
}

// Test that get() and getMutable() refer to the same underlying singleton object
TEST(SingletonTest_280, GetAndGetMutableReferToSameObject_280) {
    IMutableInterface& mutableRef = MySingleton::getMutable();
    mutableRef.setValue(999);

    const IMyInterface& constRef = MySingleton::get();
    EXPECT_EQ(constRef.getValue(), 999);

    // Reset
    mutableRef.setValue(42);
}

// Test that mutations through getMutable() are visible through get()
TEST(SingletonTest_280, MutationsThroughGetMutableVisibleThroughGet_280) {
    IMutableInterface& mutable1 = MySingleton::getMutable();
    const IMyInterface& const1 = MySingleton::get();

    mutable1.setValue(77);
    EXPECT_EQ(const1.getValue(), 77);

    mutable1.setValue(0);
    EXPECT_EQ(const1.getValue(), 0);

    // Reset
    mutable1.setValue(42);
}

// Test boundary: setting extreme values through mutable interface
TEST(SingletonTest_280, BoundaryValues_280) {
    IMutableInterface& mutableRef = MySingleton::getMutable();
    const IMyInterface& constRef = MySingleton::get();

    mutableRef.setValue(std::numeric_limits<int>::max());
    EXPECT_EQ(constRef.getValue(), std::numeric_limits<int>::max());

    mutableRef.setValue(std::numeric_limits<int>::min());
    EXPECT_EQ(constRef.getValue(), std::numeric_limits<int>::min());

    mutableRef.setValue(0);
    EXPECT_EQ(constRef.getValue(), 0);

    // Reset
    mutableRef.setValue(42);
}
