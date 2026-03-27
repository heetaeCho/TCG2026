#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the class to be tested is named `MyClass` and has a public interface as follows:

// class MyClass {

// public:

//     void someFunction();

//     int anotherFunction();

//     void functionWithCallback(const std::function<void()>& callback);

// };



class MyClassMock : public MyClass {

public:

    MOCK_METHOD(void, someFunction, (), (override));

    MOCK_METHOD(int, anotherFunction, (), (override));

    MOCK_METHOD(void, functionWithCallback, (const std::function<void()>&), (override));

};



using namespace testing;



class MyClassTest_958 : public ::testing::Test {

protected:

    MyClassMock myClassMock;

};



TEST_F(MyClassTest_958, SomeFunctionNormalOperation_958) {

    EXPECT_CALL(myClassMock, someFunction()).Times(1);

    myClassMock.someFunction();

}



TEST_F(MyClassTest_958, AnotherFunctionReturnsZero_958) {

    EXPECT_CALL(myClassMock, anotherFunction()).WillOnce(Return(0));

    EXPECT_EQ(myClassMock.anotherFunction(), 0);

}



TEST_F(MyClassTest_958, FunctionWithCallbackInvokesCallback_958) {

    ::testing::StrictMock<MockFunction<void()>> callbackMock;

    EXPECT_CALL(callbackMock, Call()).Times(1);



    myClassMock.functionWithCallback(callbackMock.AsStdFunction());

}



// Assuming boundary conditions and exceptional cases are relevant:

TEST_F(MyClassTest_958, AnotherFunctionReturnsMaxInt_958) {

    EXPECT_CALL(myClassMock, anotherFunction()).WillOnce(Return(std::numeric_limits<int>::max()));

    EXPECT_EQ(myClassMock.anotherFunction(), std::numeric_limits<int>::max());

}



TEST_F(MyClassTest_958, AnotherFunctionReturnsMinInt_958) {

    EXPECT_CALL(myClassMock, anotherFunction()).WillOnce(Return(std::numeric_limits<int>::min()));

    EXPECT_EQ(myClassMock.anotherFunction(), std::numeric_limits<int>::min());

}
