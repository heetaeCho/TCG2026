#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_registry.hpp"



using namespace Catch;



class TestClass {

public:

    void testMethod() {}

};



// Mocking an external collaborator if needed (not required in this case)

// class MockCollaborator {

// public:

//     MOCK_METHOD(void, someMethod, (), ());

// };



class TestInvokerAsMethodTest_427 : public ::testing::Test {

protected:

    void SetUp() override {

        testClass = new TestClass();

        invoker = new TestInvokerAsMethod<TestClass>(&TestClass::testMethod);

    }



    void TearDown() override {

        delete invoker;

        delete testClass;

    }



    TestClass* testClass;

    TestInvokerAsMethod<TestClass>* invoker;

};



TEST_F(TestInvokerAsMethodTest_427, InvokeCallsTestMethod_427) {

    EXPECT_NO_THROW(invoker->invoke());

}



// No boundary conditions or exceptional cases are observable through the public interface in this specific case.

```


