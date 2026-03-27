#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/error.hpp"



using namespace Exiv2;

using testing::Eq;



class LogMsgTest_722 : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset any static state if necessary

        LogMsg::setHandler(nullptr);

        LogMsg::setLevel(LogMsg::debug);

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(LogMsgTest_722, DefaultConstructor_SetsLevelCorrectly_722) {

    LogMsg logMsg(LogMsg::info);

    EXPECT_EQ(logMsg.level(), LogMsg::info);

}



TEST_F(LogMsgTest_722, StaticSetAndGetLevel_WorkAsExpected_722) {

    LogMsg::setLevel(LogMsg::warn);

    EXPECT_EQ(LogMsg::level(), LogMsg::warn);

}



TEST_F(LogMsgTest_722, Os_ReturnsValidStream_722) {

    LogMsg logMsg(LogMsg::info);

    std::ostringstream& os = logMsg.os();

    os << "test";

    EXPECT_EQ(os.str(), "test");

}



// Assuming Handler is a function pointer or callable type

using MockHandler = testing::StrictMock<testing::FunctionMocker<void(int, const char*)>>;



TEST_F(LogMsgTest_722, StaticSetAndGetHandler_WorkAsExpected_722) {

    MockHandler mockHandler;

    auto handler = static_cast<LogMsg::Handler>(&mockHandler);

    LogMsg::setHandler(handler);

    EXPECT_EQ(reinterpret_cast<void*>(LogMsg::handler()), reinterpret_cast<void*>(&mockHandler));

}



TEST_F(LogMsgTest_722, DefaultHandler_DoesNotThrowForValidInput_722) {

    EXPECT_NO_THROW(LogMsg::defaultHandler(static_cast<int>(LogMsg::info), "test message"));

}



TEST_F(LogMsgTest_722, CopyConstructor_IsDeleted_722) {

    LogMsg logMsg(LogMsg::info);

    EXPECT_FALSE(std::is_copy_constructible<LogMsg>::value);

}



TEST_F(LogMsgTest_722, AssignmentOperator_IsDeleted_722) {

    LogMsg logMsg(LogMsg::info);

    EXPECT_FALSE(std::is_assignable<LogMsg&, const LogMsg&>::value);

}
