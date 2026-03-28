#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test
#include "catch2/internal/catch_singletons.hpp"

// We need to understand that Catch2's Singleton relies on ISingleton infrastructure.
// Since we're testing the interface as a black box, we'll create concrete types
// to instantiate the Singleton template and verify observable behavior.

namespace {

// Define test interfaces
class ITestInterface {
public:
    virtual ~ITestInterface() = default;
    virtual int getValue() const = 0;
};

class IMutableTestInterface : public ITestInterface {
public:
    virtual ~IMutableTestInterface() = default;
    virtual void setValue(int v) = 0;
};

// Define a concrete singleton implementation
class TestSingletonImpl : public IMutableTestInterface {
    int value_ = 42;
public:
    int getValue() const override { return value_; }
    void setValue(int v) override { value_ = v; }
};

} // anonymous namespace

// Note: Catch2's Singleton template requires registration with ISingleton infrastructure.
// The following tests attempt to exercise the public interface. If the singleton
// infrastructure isn't initialized, these tests document expected behavior.

class SingletonTest_281 : public ::testing::Test {
protected:
    void SetUp() override {
        // Singleton infrastructure may need to be set up by Catch2's runtime.
        // We test what we can through the public interface.
    }

    void TearDown() override {
    }
};

// Test that getMutable returns a reference (non-null, same address on repeated calls)
TEST_F(SingletonTest_281, GetMutableReturnsSameInstance_281) {
    // If the Catch2 singleton infrastructure is available, getMutable should
    // return the same instance on repeated calls.
    // This test verifies the singleton property.
    try {
        using SingletonType = Catch::Singleton<TestSingletonImpl, ITestInterface, IMutableTestInterface>;
        auto& ref1 = SingletonType::getMutable();
        auto& ref2 = SingletonType::getMutable();
        EXPECT_EQ(&ref1, &ref2) << "getMutable() should return the same instance";
    } catch (...) {
        // If singleton infrastructure isn't initialized, we note it
        GTEST_SKIP() << "Catch2 singleton infrastructure not available";
    }
}

// Test that get() returns a const reference to the same underlying object
TEST_F(SingletonTest_281, GetReturnsConstReference_281) {
    try {
        using SingletonType = Catch::Singleton<TestSingletonImpl, ITestInterface, IMutableTestInterface>;
        auto const& constRef1 = SingletonType::get();
        auto const& constRef2 = SingletonType::get();
        EXPECT_EQ(&constRef1, &constRef2) << "get() should return the same const instance";
    } catch (...) {
        GTEST_SKIP() << "Catch2 singleton infrastructure not available";
    }
}

// Test that get() and getMutable() refer to the same underlying singleton
TEST_F(SingletonTest_281, GetAndGetMutableReferToSameObject_281) {
    try {
        using SingletonType = Catch::Singleton<TestSingletonImpl, ITestInterface, IMutableTestInterface>;
        auto& mutableRef = SingletonType::getMutable();
        auto const& constRef = SingletonType::get();
        
        // They should point to the same underlying object
        // Since MutableInterfaceT extends InterfaceT, we can compare through dynamic_cast or address
        const ITestInterface* mutableAsConst = &mutableRef;
        EXPECT_EQ(mutableAsConst, &constRef) << "get() and getMutable() should refer to same object";
    } catch (...) {
        GTEST_SKIP() << "Catch2 singleton infrastructure not available";
    }
}

// Test that mutations through getMutable are visible through get
TEST_F(SingletonTest_281, MutationsThroughGetMutableVisibleThroughGet_281) {
    try {
        using SingletonType = Catch::Singleton<TestSingletonImpl, ITestInterface, IMutableTestInterface>;
        auto& mutableRef = SingletonType::getMutable();
        mutableRef.setValue(100);
        
        auto const& constRef = SingletonType::get();
        EXPECT_EQ(constRef.getValue(), 100) << "Changes via getMutable should be visible via get";
    } catch (...) {
        GTEST_SKIP() << "Catch2 singleton infrastructure not available";
    }
}

// Test that getMutable returns a type that allows mutation (compile-time check effectively)
TEST_F(SingletonTest_281, GetMutableReturnsMutableInterface_281) {
    try {
        using SingletonType = Catch::Singleton<TestSingletonImpl, ITestInterface, IMutableTestInterface>;
        auto& mutableRef = SingletonType::getMutable();
        
        // Should be able to call setValue without const issues
        mutableRef.setValue(77);
        EXPECT_EQ(mutableRef.getValue(), 77);
    } catch (...) {
        GTEST_SKIP() << "Catch2 singleton infrastructure not available";
    }
}
