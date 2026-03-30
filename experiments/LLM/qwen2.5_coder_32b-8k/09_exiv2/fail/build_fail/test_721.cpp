#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Invoke;



class MockLogHandler {

public:

    MOCK_METHOD(void, handle, (int level, const char* s), ());

};



TEST_F(LogMsgTest_721, SetHandler_ShouldStoreHandler_721) {

    MockLogHandler mockHandler;

    Handler handler = [](int level, const char* s) { 

        static_cast<MockLogHandler*>(s)->handle(level, s); 

    };



    LogMsg::setHandler(std::bind(handler, std::placeholders::_1, &mockHandler));



    EXPECT_EQ(LogMsg::handler(), std::bind(handler, std::placeholders::_1, &mockHandler));

}



TEST_F(LogMsgTest_721, SetLevel_ShouldStoreLevel_721) {

    LogMsg::Level level = LogMsg::Level::debug;

    LogMsg::setLevel(level);



    EXPECT_EQ(LogMsg::level(), level);

}



TEST_F(LogMsgTest_721, DefaultHandler_ShouldNotThrowOnValidInput_721) {

    EXPECT_NO_THROW(LogMsg::defaultHandler(static_cast<int>(LogMsg::Level::info), "Test message"));

}



TEST_F(LogMsgTest_721, Handler_CallWithDefaultHandler_ShouldNotThrow_721) {

    LogMsg logMsg(LogMsg::Level::info);

    EXPECT_NO_THROW(logMsg.os() << "This is a test message.");

}



TEST_F(LogMsgTest_721, SetHandler_ShouldInvokeCustomHandler_721) {

    MockLogHandler mockHandler;

    Handler handler = [](int level, const char* s) { 

        static_cast<MockLogHandler*>(s)->handle(level, s); 

    };



    LogMsg::setHandler(std::bind(handler, std::placeholders::_1, &mockHandler));

    EXPECT_CALL(mockHandler, handle(static_cast<int>(LogMsg::Level::info), _));



    LogMsg logMsg(LogMsg::Level::info);

    logMsg.os() << "This is a test message.";

}



TEST_F(LogMsgTest_721, SetHandler_ShouldNotInvokeHandlerIfDefault_721) {

    MockLogHandler mockHandler;

    Handler handler = [](int level, const char* s) { 

        static_cast<MockLogHandler*>(s)->handle(level, s); 

    };



    LogMsg::setHandler(LogMsg::defaultHandler);

    EXPECT_CALL(mockHandler, handle(_, _)).Times(0);



    LogMsg logMsg(LogMsg::Level::info);

    logMsg.os() << "This is a test message.";

}



TEST_F(LogMsgTest_721, SetLevel_ShouldNotThrowOnBoundaryValues_721) {

    EXPECT_NO_THROW(LogMsg::setLevel(static_cast<LogMsg::Level>(-1)));

    EXPECT_NO_THROW(LogMsg::setLevel(static_cast<LogMsg::Level>(100)));

}
