#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_test_registry.hpp"
#include "catch2/interfaces/catch_interfaces_testcase.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// A simple test class to use with makeTestInvoker
class SimpleTestClass {
public:
    void testMethod() {
        // Simple test method that does nothing exceptional
        executed = true;
    }

    void anotherMethod() {
        anotherExecuted = true;
    }

    static bool executed;
    static bool anotherExecuted;
};

bool SimpleTestClass::executed = false;
bool SimpleTestClass::anotherExecuted = false;

// A test class with multiple methods
class MultiMethodClass {
public:
    void methodA() { methodACalled = true; }
    void methodB() { methodBCalled = true; }

    static bool methodACalled;
    static bool methodBCalled;
};

bool MultiMethodClass::methodACalled = false;
bool MultiMethodClass::methodBCalled = false;

// Test fixture
class MakeTestInvokerTest_428 : public ::testing::Test {
protected:
    void SetUp() override {
        SimpleTestClass::executed = false;
        SimpleTestClass::anotherExecuted = false;
        MultiMethodClass::methodACalled = false;
        MultiMethodClass::methodBCalled = false;
    }
};

// Test that makeTestInvoker returns a non-null unique_ptr
TEST_F(MakeTestInvokerTest_428, ReturnsNonNullPointer_428) {
    auto invoker = Catch::makeTestInvoker(&SimpleTestClass::testMethod);
    EXPECT_NE(invoker.get(), nullptr);
}

// Test that makeTestInvoker works with different methods of the same class
TEST_F(MakeTestInvokerTest_428, WorksWithDifferentMethodsSameClass_428) {
    auto invoker1 = Catch::makeTestInvoker(&SimpleTestClass::testMethod);
    auto invoker2 = Catch::makeTestInvoker(&SimpleTestClass::anotherMethod);
    EXPECT_NE(invoker1.get(), nullptr);
    EXPECT_NE(invoker2.get(), nullptr);
}

// Test that makeTestInvoker works with different classes
TEST_F(MakeTestInvokerTest_428, WorksWithDifferentClasses_428) {
    auto invoker1 = Catch::makeTestInvoker(&SimpleTestClass::testMethod);
    auto invoker2 = Catch::makeTestInvoker(&MultiMethodClass::methodA);
    EXPECT_NE(invoker1.get(), nullptr);
    EXPECT_NE(invoker2.get(), nullptr);
}

// Test that the returned object is a valid ITestInvoker
TEST_F(MakeTestInvokerTest_428, ReturnsValidITestInvoker_428) {
    auto invoker = Catch::makeTestInvoker(&SimpleTestClass::testMethod);
    // The invoker should implement ITestInvoker interface
    Catch::ITestInvoker* rawPtr = invoker.get();
    EXPECT_NE(rawPtr, nullptr);
}

// Test that creating multiple invokers for the same method works independently
TEST_F(MakeTestInvokerTest_428, MultipleInvokersForSameMethod_428) {
    auto invoker1 = Catch::makeTestInvoker(&SimpleTestClass::testMethod);
    auto invoker2 = Catch::makeTestInvoker(&SimpleTestClass::testMethod);
    EXPECT_NE(invoker1.get(), nullptr);
    EXPECT_NE(invoker2.get(), nullptr);
    // They should be distinct objects
    EXPECT_NE(invoker1.get(), invoker2.get());
}

// Test invoker with MultiMethodClass methodA
TEST_F(MakeTestInvokerTest_428, WorksWithMultiMethodClassMethodA_428) {
    auto invoker = Catch::makeTestInvoker(&MultiMethodClass::methodA);
    EXPECT_NE(invoker.get(), nullptr);
}

// Test invoker with MultiMethodClass methodB
TEST_F(MakeTestInvokerTest_428, WorksWithMultiMethodClassMethodB_428) {
    auto invoker = Catch::makeTestInvoker(&MultiMethodClass::methodB);
    EXPECT_NE(invoker.get(), nullptr);
}

// Test that the returned unique_ptr properly manages ownership (move semantics)
TEST_F(MakeTestInvokerTest_428, UniquePtrOwnershipTransfer_428) {
    auto invoker = Catch::makeTestInvoker(&SimpleTestClass::testMethod);
    ASSERT_NE(invoker.get(), nullptr);

    Catch::ITestInvoker* rawBefore = invoker.get();
    auto movedInvoker = std::move(invoker);
    EXPECT_EQ(invoker.get(), nullptr);
    EXPECT_EQ(movedInvoker.get(), rawBefore);
}

// An empty class with a test method
class EmptyTestClass {
public:
    void run() {}
};

TEST_F(MakeTestInvokerTest_428, WorksWithMinimalClass_428) {
    auto invoker = Catch::makeTestInvoker(&EmptyTestClass::run);
    EXPECT_NE(invoker.get(), nullptr);
}

// Test with a class that has a virtual method
class VirtualMethodClass {
public:
    virtual void testVirtual() { virtualCalled = true; }
    virtual ~VirtualMethodClass() = default;
    static bool virtualCalled;
};

bool VirtualMethodClass::virtualCalled = false;

TEST_F(MakeTestInvokerTest_428, WorksWithVirtualMethod_428) {
    auto invoker = Catch::makeTestInvoker(&VirtualMethodClass::testVirtual);
    EXPECT_NE(invoker.get(), nullptr);
}

// Test with a derived class
class DerivedTestClass : public VirtualMethodClass {
public:
    void testVirtual() override { derivedCalled = true; }
    static bool derivedCalled;
};

bool DerivedTestClass::derivedCalled = false;

TEST_F(MakeTestInvokerTest_428, WorksWithDerivedClassMethod_428) {
    auto invoker = Catch::makeTestInvoker(&DerivedTestClass::testVirtual);
    EXPECT_NE(invoker.get(), nullptr);
}
