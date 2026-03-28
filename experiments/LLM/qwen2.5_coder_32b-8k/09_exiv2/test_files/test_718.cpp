#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Invoke;

using ::testing::MockFunction;



class MockHandler {

public:

    MOCK_METHOD(void, Call, (int level, const char* s), ());

};



class LogMsgTest : public ::testing::Test {

protected:

    static void SetUpTestSuite() {

        LogMsg::setLevel(LogMsg::Level::debug);

        LogMsg::setHandler(nullptr);

    }



    MockHandler mock_handler;

};



TEST_F(LogMsgTest_SetHandler_718, SetAndCallHandlerWithMessage_718) {

    // Arrange

    int expected_level = static_cast<int>(LogMsg::Level::info);

    std::string message = "Test message";

    LogMsg::setHandler([&mock_handler](int level, const char* s) { mock_handler.Call(level, s); });



    EXPECT_CALL(mock_handler, Call(expected_level, StrEq(message.c_str())));



    // Act

    {

        LogMsg log_msg(LogMsg::Level::info);

        log_msg.os() << message;

    }



    // Assert is handled by EXPECT_CALL

}



TEST_F(LogMsgTest_SetHandler_718, SetNullHandler_NoCall_718) {

    // Arrange

    std::string message = "This should not be called";

    LogMsg::setHandler(nullptr);



    // Act & Assert: No call to handler expected

    {

        LogMsg log_msg(LogMsg::Level::info);

        log_msg.os() << message;

    }

}



TEST_F(LogMsgTest_SetLevel_718, SetLevelBelowMessage_NoCall_718) {

    // Arrange

    std::string message = "This should not be called";

    LogMsg::setLevel(LogMsg::Level::warn);

    EXPECT_CALL(mock_handler, Call(_, _)).Times(0);



    LogMsg::setHandler([&mock_handler](int level, const char* s) { mock_handler.Call(level, s); });



    // Act & Assert: No call to handler expected

    {

        LogMsg log_msg(LogMsg::Level::info);

        log_msg.os() << message;

    }

}



TEST_F(LogMsgTest_SetLevel_718, SetLevelAboveMessage_CallHandler_718) {

    // Arrange

    int expected_level = static_cast<int>(LogMsg::Level::error);

    std::string message = "This should be called";

    LogMsg::setLevel(LogMsg::Level::info);

    EXPECT_CALL(mock_handler, Call(expected_level, StrEq(message.c_str())));



    LogMsg::setHandler([&mock_handler](int level, const char* s) { mock_handler.Call(level, s); });



    // Act

    {

        LogMsg log_msg(LogMsg::Level::error);

        log_msg.os() << message;

    }



    // Assert is handled by EXPECT_CALL

}



TEST_F(LogMsgTest_DefaultHandler_718, DefaultHandler_CallNoException_718) {

    // Arrange: Use the default handler and ensure no exception occurs

    LogMsg::setLevel(LogMsg::Level::debug);

    LogMsg::setHandler(nullptr); // Reset to default



    std::string message = "Test with default handler";



    // Act & Assert: No exception expected, default handler should not throw

    {

        LogMsg log_msg(LogMsg::Level::info);

        log_msg.os() << message;

    }

}
