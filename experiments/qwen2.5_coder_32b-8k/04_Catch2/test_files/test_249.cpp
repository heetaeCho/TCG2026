#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_message.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo &message), (override));

    MOCK_METHOD(void, popScopedMessage, (const MessageInfo &message), (override));

};



class ScopedMessageTest_249 : public ::testing::Test {

protected:

    NiceMock<MockIResultCapture> mockResultCapture;

    std::unique_ptr<IResultCapture> pMockResultCapture;



    void SetUp() override {

        pMockResultCapture.reset(&mockResultCapture);

        setGlobalResultCapture(pMockResultCapture.get());

    }



    void TearDown() override {

        pMockResultCapture.release();

        resetGlobalResultCapture();

    }

};



TEST_F(ScopedMessageTest_249, DestructorCallsPopWhenNoExceptionOrMove_249) {

    MessageInfo messageInfo;

    MockIResultCapture mock;

    EXPECT_CALL(mock, popScopedMessage(messageInfo)).Times(1);

    setGlobalResultCapture(&mock);



    {

        ScopedMessage msg(MessageBuilder().setMessage("Test message"));

    }



    resetGlobalResultCapture();

}



TEST_F(ScopedMessageTest_249, DestructorDoesNotCallPopWhenMoved_249) {

    MessageInfo messageInfo;

    MockIResultCapture mock;

    EXPECT_CALL(mock, popScopedMessage(messageInfo)).Times(0);

    setGlobalResultCapture(&mock);



    ScopedMessage original(MessageBuilder().setMessage("Test message"));

    auto moved = std::move(original);



    resetGlobalResultCapture();

}



TEST_F(ScopedMessageTest_249, DestructorDoesNotCallPopWhenException_249) {

    MessageInfo messageInfo;

    MockIResultCapture mock;

    EXPECT_CALL(mock, popScopedMessage(messageInfo)).Times(0);

    setGlobalResultCapture(&mock);



    try {

        ScopedMessage msg(MessageBuilder().setMessage("Test message"));

        throw std::runtime_error("Exception occurred");

    } catch (...) {}



    resetGlobalResultCapture();

}



TEST_F(ScopedMessageTest_249, MoveConstructorTransfersOwnership_249) {

    MessageInfo messageInfo;

    MockIResultCapture mock;

    EXPECT_CALL(mock, popScopedMessage(messageInfo)).Times(1);

    setGlobalResultCapture(&mock);



    {

        ScopedMessage original(MessageBuilder().setMessage("Test message"));

        auto moved = std::move(original);

    }



    resetGlobalResultCapture();

}



TEST_F(ScopedMessageTest_249, DeletedCopyConstructorPreventsCopying_249) {

    // This test checks that the copy constructor is deleted and cannot be used.

    ScopedMessage original(MessageBuilder().setMessage("Test message"));

    EXPECT_FALSE(std::is_copy_constructible<ScopedMessage>::value);

}
