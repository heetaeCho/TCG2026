#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



// Assuming the class under test is named MyClass and has some interface.

class MyClass {

public:

    virtual ~MyClass() = default;

    virtual int doSomething(int param) = 0;

    virtual void registerCallback(std::function<void(int)> callback) = 0;

};



// Mocking external collaborators if needed

class MockCollaborator : public MyClass {

public:

    MOCK_METHOD(int, doSomething, (int param), (override));

    MOCK_METHOD(void, registerCallback, (std::function<void(int)> callback), (override));

};



using namespace ::testing;



TEST_F(MockCollaboratorTest_981, DoSomething_ReturnsExpectedValue_981) {

    MockCollaborator mock;

    EXPECT_CALL(mock, doSomething(42)).WillOnce(Return(84));

    int result = mock.doSomething(42);

    EXPECT_EQ(result, 84);

}



TEST_F(MockCollaboratorTest_981, DoSomething_BoundaryCondition_Zero_981) {

    MockCollaborator mock;

    EXPECT_CALL(mock, doSomething(0)).WillOnce(Return(0));

    int result = mock.doSomething(0);

    EXPECT_EQ(result, 0);

}



TEST_F(MockCollaboratorTest_981, RegisterCallback_IsCalledWithCorrectValue_981) {

    MockCollaborator mock;

    StrictMock<MockFunction<void(int)>> callbackMock;



    EXPECT_CALL(mock, registerCallback(_)).WillOnce(SaveArg<0>(&capturedCallback));

    EXPECT_CALL(callbackMock, Call(42));



    mock.registerCallback(callbackMock.AsStdFunction());

    capturedCallback(42);

}



TEST_F(MockCollaboratorTest_981, RegisterCallback_HandlesMultipleCalls_981) {

    MockCollaborator mock;

    StrictMock<MockFunction<void(int)>> callbackMock;



    EXPECT_CALL(mock, registerCallback(_)).WillOnce(SaveArg<0>(&capturedCallback));

    EXPECT_CALL(callbackMock, Call(42));

    EXPECT_CALL(callbackMock, Call(84));



    mock.registerCallback(callbackMock.AsStdFunction());

    capturedCallback(42);

    capturedCallback(84);

}



TEST_F(MockCollaboratorTest_981, DoSomething_ExceptionalCase_NegativeValue_981) {

    MockCollaborator mock;

    EXPECT_CALL(mock, doSomething(-1)).WillOnce(Return(-1));

    int result = mock.doSomething(-1);

    EXPECT_EQ(result, -1);

}



std::function<void(int)> capturedCallback;


