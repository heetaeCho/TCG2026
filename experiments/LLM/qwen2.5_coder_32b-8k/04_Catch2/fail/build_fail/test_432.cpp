#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_test_registry.hpp"



// Mock class to simulate the behavior of the test fixture class C.

class MockTestFixture {

public:

    MOCK_METHOD(void, testAsMethod, (), (const));

};



TEST_F(MockTestFixture_432, MakeTestInvokerFixture_CreatesUniquePtr_432) {

    // Arrange

    auto mockTestFixture = std::make_unique<MockTestFixture>();

    

    // Act

    Catch::Detail::unique_ptr<Catch::ITestInvoker> invoker = 

        Catch::makeTestInvokerFixture(&MockTestFixture::testAsMethod);



    // Assert

    EXPECT_NE(invoker.get(), nullptr);

}



TEST_F(MockTestFixture_432, MakeTestInvokerFixture_CallsTestAsMethod_432) {

    // Arrange

    auto mockTestFixture = std::make_unique<MockTestFixture>();

    EXPECT_CALL(*mockTestFixture, testAsMethod()).Times(1);



    Catch::Detail::unique_ptr<Catch::ITestInvoker> invoker = 

        Catch::makeTestInvokerFixture(&MockTestFixture::testAsMethod);



    // Act

    invoker->invoke();



    // Assert is handled by the mock expectation.

}

```


