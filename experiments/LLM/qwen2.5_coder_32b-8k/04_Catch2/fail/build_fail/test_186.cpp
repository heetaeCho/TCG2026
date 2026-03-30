#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming a hypothetical class name `ExampleClass` for demonstration purposes.

// Replace `ExampleClass` with the actual class name as per your codebase.



class ExampleClass {

public:

    virtual ~ExampleClass() = default;

    virtual void someFunction() = 0;

    virtual int someValueReturningFunction() = 0;

};



using namespace testing;



TEST_F(ExampleTest_186, someFunctionDoesNotThrowException_186) {

    // Arrange

    auto mockObj = std::make_unique<StrictMock<MockExampleClass>>();



    // Act & Assert

    EXPECT_NO_THROW(mockObj->someFunction());

}



TEST_F(ExampleTest_186, someValueReturningFunctionReturnsExpectedValue_186) {

    // Arrange

    auto mockObj = std::make_unique<NiceMock<MockExampleClass>>();

    const int expectedValue = 42;

    EXPECT_CALL(*mockObj, someValueReturningFunction()).WillOnce(Return(expectedValue));



    // Act

    int result = mockObj->someValueReturningFunction();



    // Assert

    EXPECT_EQ(result, expectedValue);

}



TEST_F(ExampleTest_186, someFunctionCallsHandlerCorrectly_186) {

    // Arrange

    auto mockObj = std::make_unique<StrictMock<MockExampleClass>>();

    auto handler = std::make_shared<StrictMock<MockHandler>>();

    EXPECT_CALL(*mockObj, someFunction()).WillOnce(Invoke([handler]() { handler->handle(); }));

    EXPECT_CALL(*handler, handle());



    // Act

    mockObj->someFunction();

}



// Mock class declarations for the above tests.

class MockExampleClass : public ExampleClass {

public:

    MOCK_METHOD(void, someFunction, (), (override));

    MOCK_METHOD(int, someValueReturningFunction, (), (override));

};



class MockHandler {

public:

    MOCK_METHOD(void, handle, ());

};

```


