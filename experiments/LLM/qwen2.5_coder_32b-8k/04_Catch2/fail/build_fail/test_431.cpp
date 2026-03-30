#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_test_registry.hpp"



using namespace Catch;



class MockFixture {

public:

    MOCK_METHOD(void, testMethod, (), (const));

};



class TestInvokerFixtureTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockFixture = std::make_unique<MockFixture>();

        invokerFixture = std::make_unique<TestInvokerFixture<MockFixture>>(&MockFixture::testMethod);

    }



    std::unique_ptr<MockFixture> mockFixture;

    std::unique_ptr<TestInvokerFixture<MockFixture>> invokerFixture;

};



TEST_F(TestInvokerFixtureTest, InvokeCallsTestMethod_431) {

    EXPECT_CALL(*mockFixture, testMethod()).Times(1);

    invokerFixture->invoke();

}



// Boundary conditions and exceptional cases are not directly applicable here

// as the provided interface does not suggest any parameters or error handling.

```


