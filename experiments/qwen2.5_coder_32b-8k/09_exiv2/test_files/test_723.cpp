#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockLogHandler {

public:

    MOCK_METHOD(void, handle, (int level, const char* s), ());

};



TEST_F(LogMsgTest_723, SetAndRetrieveLevel_723) {

    LogMsg::setLevel(LogMsg::Level::debug);

    EXPECT_EQ(LogMsg::level(), LogMsg::Level::debug);



    LogMsg::setLevel(LogMsg::Level::error);

    EXPECT_EQ(LogMsg::level(), LogMsg::Level::error);

}



TEST_F(LogMsgTest_723, SetAndRetrieveHandler_723) {

    MockLogHandler mockHandler;

    auto handler = [](int level, const char* s) { mockHandler.handle(level, s); };



    LogMsg::setHandler(handler);

    EXPECT_EQ(reinterpret_cast<void*>(LogMsg::handler()), reinterpret_cast<void*>(handler));

}



TEST_F(LogMsgTest_723, DefaultHandlerDoesNotThrow_723) {

    EXPECT_NO_THROW(LogMsg::defaultHandler(static_cast<int>(LogMsg::Level::info), "Test message"));

}



TEST_F(LogMsgTest_723, HandlerCalledWithCorrectParameters_723) {

    MockLogHandler mockHandler;

    auto handler = [](int level, const char* s) { mockHandler.handle(level, s); };



    LogMsg::setHandler(handler);

    EXPECT_CALL(mockHandler, handle(static_cast<int>(LogMsg::Level::warning), "Test warning message"));



    LogMsg log(LogMsg::Level::warning);

    log.os() << "Test warning message";

}



TEST_F(LogMsgTest_723, LevelBoundaryConditions_723) {

    LogMsg::setLevel(static_cast<LogMsg::Level>(-1));

    EXPECT_EQ(LogMsg::level(), static_cast<LogMsg::Level>(-1));



    LogMsg::setLevel(static_cast<LogMsg::Level>(100));

    EXPECT_EQ(LogMsg::level(), static_cast<LogMsg::Level>(100));

}



TEST_F(LogMsgTest_723, HandlerNotCalledWhenNoHandlerSet_723) {

    MockLogHandler mockHandler;

    LogMsg::setHandler(nullptr);



    EXPECT_CALL(mockHandler, handle(_, _)).Times(0);



    LogMsg log(LogMsg::Level::info);

    log.os() << "This should not call the handler";

}



TEST_F(LogMsgTest_723, OsReturnsDifferentInstances_723) {

    LogMsg log1(LogMsg::Level::debug);

    LogMsg log2(LogMsg::Level::error);



    EXPECT_NE(&log1.os(), &log2.os());

}
