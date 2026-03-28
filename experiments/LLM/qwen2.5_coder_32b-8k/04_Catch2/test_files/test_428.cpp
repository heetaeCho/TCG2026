#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_test_registry.hpp"



using namespace Catch;

using namespace ::testing;



// Mock class for testing purposes

class TestClass {

public:

    void testMethod() {}

};



// Test fixture for the tests

class TestRegistryTest_428 : public Test {

protected:

    TestClass testObject;

};



TEST_F(TestRegistryTest_428, MakeTestInvoker_ReturnsUniquePtr_428) {

    auto invoker = makeTestInvoker<&TestClass::testMethod>(&testObject);

    EXPECT_NE(invoker.get(), nullptr);

}



// Assuming there are boundary conditions or error cases to test

// Since the function is simple and does not have parameters other than valid pointers, 

// there might not be many edge cases to cover. However, let's add a null pointer check.



TEST_F(TestRegistryTest_428, MakeTestInvoker_NullMethodPointer_ReturnsNullptr_428) {

    void (TestClass::*nullMethodPtr)() = nullptr;

    auto invoker = makeTestInvoker<TestClass>(nullMethodPtr);

    EXPECT_EQ(invoker.get(), nullptr);

}



// Assuming that passing a null object pointer might be a case to test

TEST_F(TestRegistryTest_428, MakeTestInvoker_NullObjectPointer_ReturnsNullptr_428) {

    TestClass* nullObjectPtr = nullptr;

    auto invoker = makeTestInvoker<&TestClass::testMethod>(nullObjectPtr);

    EXPECT_EQ(invoker.get(), nullptr);

}

```


