#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockHandler {

public:

    MOCK_METHOD2(handle, void(int level, const char* s));

};



TEST_F(LogMsgTest_724, DefaultHandlerDebugMessage_724) {

    testing::internal::CaptureStderr();

    LogMsg::defaultHandler(static_cast<int>(LogMsg::debug), "This is a debug message.");

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "Debug: This is a debug message.");

}



TEST_F(LogMsgTest_724, DefaultHandlerInfoMessage_724) {

    testing::internal::CaptureStderr();

    LogMsg::defaultHandler(static_cast<int>(LogMsg::info), "This is an info message.");

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "Info: This is an info message.");

}



TEST_F(LogMsgTest_724, DefaultHandlerWarningMessage_724) {

    testing::internal::CaptureStderr();

    LogMsg::defaultHandler(static_cast<int>(LogMsg::warn), "This is a warning message.");

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "Warning: This is a warning message.");

}



TEST_F(LogMsgTest_724, DefaultHandlerErrorMessage_724) {

    testing::internal::CaptureStderr();

    LogMsg::defaultHandler(static_cast<int>(LogMsg::error), "This is an error message.");

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "Error: This is an error message.");

}



TEST_F(LogMsgTest_724, DefaultHandlerInvalidLevel_724) {

    testing::internal::CaptureStderr();

    LogMsg::defaultHandler(static_cast<int>(LogMsg::mute), "This should not be logged.");

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(output, "");

}



TEST_F(LogMsgTest_724, SetAndGetLevel_724) {

    LogMsg::setLevel(LogMsg::debug);

    EXPECT_EQ(LogMsg::level(), LogMsg::debug);



    LogMsg::setLevel(LogMsg::info);

    EXPECT_EQ(LogMsg::level(), LogMsg::info);



    LogMsg::setLevel(LogMsg::warn);

    EXPECT_EQ(LogMsg::level(), LogMsg::warn);



    LogMsg::setLevel(LogMsg::error);

    EXPECT_EQ(LogMsg::level(), LogMsg::error);



    LogMsg::setLevel(LogMsg::mute);

    EXPECT_EQ(LogMsg::level(), LogMsg::mute);

}



TEST_F(LogMsgTest_724, SetAndGetHandler_724) {

    MockHandler mockHandler;

    auto handler = [](int level, const char* s) {

        static_cast<MockHandler*>(s)->handle(level, "This is a test message.");

    };



    LogMsg::setHandler(reinterpret_cast<LogMsg::Handler>(handler));

    EXPECT_EQ(LogMsg::handler(), reinterpret_cast<LogMsg::Handler>(handler));



    testing::StrictMock<MockHandler> mock;

    EXPECT_CALL(mock, handle(testing::_, "This is a test message.")).Times(1);

    LogMsg::defaultHandler(static_cast<int>(LogMsg::debug), reinterpret_cast<const char*>(&mock));

}



TEST_F(LogMsgTest_724, LogLevelBoundaryConditions_724) {

    LogMsg::setLevel(static_cast<LogMsg::Level>(-1));

    EXPECT_EQ(LogMsg::level(), LogMsg::mute);



    LogMsg::setLevel(static_cast<LogMsg::Level>(5));

    EXPECT_EQ(LogMsg::level(), LogMsg::mute);

}
