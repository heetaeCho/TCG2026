#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::Return;



class LogMsgTest_720 : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset any static state if necessary

        LogMsg::setLevel(LogMsg::Level::debug);

        LogMsg::setHandler(nullptr);

    }

};



TEST_F(LogMsgTest_720, SetAndGetLogLevel_NormalOperation_720) {

    LogMsg::setLevel(LogMsg::Level::info);

    EXPECT_EQ(LogMsg::level(), LogMsg::Level::info);



    LogMsg::setLevel(LogMsg::Level::warn);

    EXPECT_EQ(LogMsg::level(), LogMsg::Level::warn);

}



TEST_F(LogMsgTest_720, SetAndGetLogLevel_BoundaryConditions_720) {

    LogMsg::setLevel(static_cast<LogMsg::Level>(-1)); // Assuming Level is an enum

    EXPECT_NE(LogMsg::level(), static_cast<LogMsg::Level>(-1));



    LogMsg::setLevel(static_cast<LogMsg::Level>(1000));

    EXPECT_NE(LogMsg::level(), static_cast<LogMsg::Level>(1000));

}



TEST_F(LogMsgTest_720, SetAndGetHandler_NormalOperation_720) {

    auto mockHandler = [](int level, const char* s) {};

    LogMsg::setHandler(mockHandler);

    EXPECT_EQ(LogMsg::handler(), mockHandler);



    LogMsg::setHandler(nullptr);

    EXPECT_EQ(LogMsg::handler(), nullptr);

}



TEST_F(LogMsgTest_720, DefaultHandler_CallWithValidParameters_720) {

    // Since defaultHandler is static and we cannot directly capture its output,

    // we can only test if it accepts valid parameters without crashing.

    LogMsg::defaultHandler(LogMsg::Level::error, "This is an error message");

}



TEST_F(LogMsgTest_720, DefaultHandler_CallWithInvalidParameters_720) {

    // Test with invalid level and null string

    EXPECT_NO_THROW(LogMsg::defaultHandler(static_cast<LogMsg::Level>(-1), nullptr));

}



TEST_F(LogMsgTest_720, LogMsg_ConstructionAndDestruction_720) {

    // Ensure that constructing and destructing a LogMsg object does not cause issues.

    {

        LogMsg logMsg(LogMsg::Level::debug);

    }

}
