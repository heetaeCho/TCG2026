#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming we have a class named MyClass with some public methods

// Since no specific interface is provided, I'll create a mock interface based on common scenarios



class MyClass {

public:

    virtual ~MyClass() = default;

    virtual int DoSomething(int input) = 0;

    virtual void SetCallback(std::function<void(int)> callback) = 0;

};



class MockMyClass : public MyClass {

public:

    MOCK_METHOD(int, DoSomething, (int input), (override));

    MOCK_METHOD(void, SetCallback, (std::function<void(int)> callback), (override));

};



using namespace testing;



TEST_F(MockMyClassTest_953, DoSomething_ReturnsExpectedValueForPositiveInput_953) {

    MockMyClass mock;

    EXPECT_CALL(mock, DoSomething(10)).WillOnce(Return(20));

    EXPECT_EQ(mock.DoSomething(10), 20);

}



TEST_F(MockMyClassTest_953, DoSomething_ReturnsExpectedValueForZeroInput_953) {

    MockMyClass mock;

    EXPECT_CALL(mock, DoSomething(0)).WillOnce(Return(0));

    EXPECT_EQ(mock.DoSomething(0), 0);

}



TEST_F(MockMyClassTest_953, DoSomething_ReturnsExpectedValueForNegativeInput_953) {

    MockMyClass mock;

    EXPECT_CALL(mock, DoSomething(-10)).WillOnce(Return(-20));

    EXPECT_EQ(mock.DoSomething(-10), -20);

}



TEST_F(MockMyClassTest_953, SetCallback_CallbackIsInvokedWithCorrectValue_953) {

    MockMyClass mock;

    StrictMock<MockFunction<void(int)>> callbackMock;



    EXPECT_CALL(mock, SetCallback(_)).WillOnce(SaveArg<0>(&capturedCallback));

    EXPECT_CALL(callbackMock.AsStdFunction(), Call(42));



    mock.SetCallback(callbackMock.AsStdFunction());

    capturedCallback(42);

}



TEST_F(MockMyClassTest_953, DoSomething_HandlesLargePositiveInputWithoutError_953) {

    MockMyClass mock;

    EXPECT_CALL(mock, DoSomething(std::numeric_limits<int>::max())).WillOnce(Return(0));

    EXPECT_NO_THROW(mock.DoSomething(std::numeric_limits<int>::max()));

}



TEST_F(MockMyClassTest_953, DoSomething_HandlesLargeNegativeInputWithoutError_953) {

    MockMyClass mock;

    EXPECT_CALL(mock, DoSomething(std::numeric_limits<int>::min())).WillOnce(Return(0));

    EXPECT_NO_THROW(mock.DoSomething(std::numeric_limits<int>::min()));

}



std::function<void(int)> capturedCallback;


