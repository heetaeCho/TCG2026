#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "exiv2/error.hpp"

#include <sstream>



using namespace testing;

using namespace Exiv2;



class LogMsgTest : public Test {

protected:

    void SetUp() override {

        // Reset to default state if necessary

        LogMsg::setLevel(LogMsg::Level::debug);

        LogMsg::setHandler(nullptr);

    }

};



TEST_F(LogMsgTest_719, OsReturnsOStringStreamReference_719) {

    LogMsg logMsg(LogMsg::Level::info);

    std::ostringstream& os = logMsg.os();

    EXPECT_TRUE(dynamic_cast<std::ostringstream*>(&os) != nullptr);

}



TEST_F(LogMsgTest_719, SetAndGetLevel_719) {

    LogMsg::setLevel(LogMsg::Level::warn);

    EXPECT_EQ(LogMsg::level(), LogMsg::Level::warn);



    LogMsg::setLevel(LogMsg::Level::error);

    EXPECT_EQ(LogMsg::level(), LogMsg::Level::error);

}



TEST_F(LogMsgTest_719, SetAndGetHandler_719) {

    auto mockHandler = [](int level, const char* s) {};

    LogMsg::setHandler(mockHandler);

    EXPECT_EQ(LogMsg::handler(), mockHandler);



    LogMsg::setHandler(nullptr);

    EXPECT_EQ(LogMsg::handler(), nullptr);

}



TEST_F(LogMsgTest_719, DefaultHandlerDoesNotThrow_719) {

    EXPECT_NO_THROW(LogMsg::defaultHandler(static_cast<int>(LogMsg::Level::info), "test message"));

}



TEST_F(LogMsgTest_719, CopyConstructorIsDeleted_719) {

    LogMsg logMsg(LogMsg::Level::debug);

    EXPECT_FALSE(std::is_copy_constructible<LogMsg>::value);

}



TEST_F(LogMsgTest_719, AssignmentOperatorIsDeleted_719) {

    LogMsg logMsg(LogMsg::Level::debug);

    LogMsg anotherLogMsg(LogMsg::Level::info);

    EXPECT_FALSE(std::is_assignable<LogMsg&, const LogMsg&>::value);

}
