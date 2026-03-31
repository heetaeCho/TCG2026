#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/error.hpp>
#include <string>
#include <sstream>

// Global variables to capture handler calls
static int g_lastLevel = -1;
static std::string g_lastMessage;
static int g_handlerCallCount = 0;

static void customHandler(int level, const char* s) {
    g_lastLevel = level;
    g_lastMessage = s ? s : "";
    g_handlerCallCount++;
}

static void anotherHandler(int level, const char* s) {
    g_lastLevel = level * 10;  // Distinguish from customHandler
    g_lastMessage = std::string("another:") + (s ? s : "");
    g_handlerCallCount++;
}

class LogMsgTest_721 : public ::testing::Test {
protected:
    void SetUp() override {
        g_lastLevel = -1;
        g_lastMessage.clear();
        g_handlerCallCount = 0;
        // Reset to default handler and level
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }

    void TearDown() override {
        // Reset to default handler and level
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }
};

TEST_F(LogMsgTest_721, DefaultHandlerIsNotNull_721) {
    Exiv2::LogMsg::Handler h = Exiv2::LogMsg::handler();
    EXPECT_NE(h, nullptr);
}

TEST_F(LogMsgTest_721, DefaultHandlerIsDefaultHandler_721) {
    Exiv2::LogMsg::Handler h = Exiv2::LogMsg::handler();
    EXPECT_EQ(h, &Exiv2::LogMsg::defaultHandler);
}

TEST_F(LogMsgTest_721, SetCustomHandler_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::Handler h = Exiv2::LogMsg::handler();
    EXPECT_EQ(h, &customHandler);
}

TEST_F(LogMsgTest_721, SetHandlerToAnotherHandler_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), &customHandler);

    Exiv2::LogMsg::setHandler(anotherHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), &anotherHandler);
}

TEST_F(LogMsgTest_721, SetHandlerBackToDefault_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), &customHandler);

    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), &Exiv2::LogMsg::defaultHandler);
}

TEST_F(LogMsgTest_721, DefaultLevel_721) {
    // Default level is typically warn
    Exiv2::LogMsg::Level lvl = Exiv2::LogMsg::level();
    EXPECT_EQ(lvl, Exiv2::LogMsg::warn);
}

TEST_F(LogMsgTest_721, SetLevelDebug_721) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);
}

TEST_F(LogMsgTest_721, SetLevelInfo_721) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

TEST_F(LogMsgTest_721, SetLevelWarn_721) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);
}

TEST_F(LogMsgTest_721, SetLevelError_721) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);
}

TEST_F(LogMsgTest_721, SetLevelMute_721) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::mute);
}

TEST_F(LogMsgTest_721, OsReturnsStream_721) {
    Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
    std::ostringstream& os = msg.os();
    os << "test message";
    // Verify we can write to the stream without crashing
    EXPECT_FALSE(os.str().empty());
    EXPECT_EQ(os.str(), "test message");
}

TEST_F(LogMsgTest_721, CustomHandlerCalledOnDestruction_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "hello from test";
    }
    // After destruction, the handler should have been called
    EXPECT_EQ(g_handlerCallCount, 1);
    EXPECT_NE(g_lastMessage.find("hello from test"), std::string::npos);
}

TEST_F(LogMsgTest_721, HandlerNotCalledWhenLevelBelowThreshold_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "should not appear";
    }
    // warn < error, so handler should NOT be called
    EXPECT_EQ(g_handlerCallCount, 0);
}

TEST_F(LogMsgTest_721, HandlerCalledWhenLevelMeetsThreshold_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error message";
    }
    // error >= warn, so handler should be called
    EXPECT_EQ(g_handlerCallCount, 1);
    EXPECT_NE(g_lastMessage.find("error message"), std::string::npos);
}

TEST_F(LogMsgTest_721, HandlerCalledWithCorrectLevel_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "test";
    }
    EXPECT_EQ(g_lastLevel, static_cast<int>(Exiv2::LogMsg::error));
}

TEST_F(LogMsgTest_721, MuteLevelSuppressesAllMessages_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "muted message";
    }
    EXPECT_EQ(g_handlerCallCount, 0);
}

TEST_F(LogMsgTest_721, DebugLevelAllowsAllMessages_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug message";
    }
    EXPECT_EQ(g_handlerCallCount, 1);
    EXPECT_NE(g_lastMessage.find("debug message"), std::string::npos);
}

TEST_F(LogMsgTest_721, MultipleMessagesCallHandlerMultipleTimes_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg1(Exiv2::LogMsg::warn);
        msg1.os() << "first";
    }
    EXPECT_EQ(g_handlerCallCount, 1);

    {
        Exiv2::LogMsg msg2(Exiv2::LogMsg::error);
        msg2.os() << "second";
    }
    EXPECT_EQ(g_handlerCallCount, 2);
    EXPECT_NE(g_lastMessage.find("second"), std::string::npos);
}

TEST_F(LogMsgTest_721, EmptyMessage_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        // Don't write anything to the stream
    }
    EXPECT_EQ(g_handlerCallCount, 1);
}

TEST_F(LogMsgTest_721, InfoLevelMessage_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "info message";
    }
    EXPECT_EQ(g_handlerCallCount, 1);
    EXPECT_EQ(g_lastLevel, static_cast<int>(Exiv2::LogMsg::info));
}

TEST_F(LogMsgTest_721, DefaultHandlerDoesNotCrash_721) {
    // Ensure calling defaultHandler directly doesn't crash
    EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(static_cast<int>(Exiv2::LogMsg::warn), "test"));
}

TEST_F(LogMsgTest_721, DefaultHandlerWithNullString_721) {
    // Ensure calling defaultHandler with null doesn't crash (if it handles it)
    // This is a boundary test - behavior may vary
    EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(static_cast<int>(Exiv2::LogMsg::warn), nullptr));
}

TEST_F(LogMsgTest_721, DefaultHandlerWithEmptyString_721) {
    EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(static_cast<int>(Exiv2::LogMsg::warn), ""));
}

TEST_F(LogMsgTest_721, SetLevelPersistsAcrossMultipleCalls_721) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

TEST_F(LogMsgTest_721, HandlerPersistsAcrossMessages_721) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "msg1";
    }

    // Handler should still be customHandler
    EXPECT_EQ(Exiv2::LogMsg::handler(), &customHandler);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "msg2";
    }

    EXPECT_EQ(g_handlerCallCount, 2);
}

TEST_F(LogMsgTest_721, OsStreamAppend_721) {
    Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
    msg.os() << "part1";
    msg.os() << " part2";
    EXPECT_EQ(msg.os().str(), "part1 part2");
}

TEST_F(LogMsgTest_721, SwitchHandlerBetweenMessages_721) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    Exiv2::LogMsg::setHandler(customHandler);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "custom";
    }
    EXPECT_EQ(g_handlerCallCount, 1);
    EXPECT_NE(g_lastMessage.find("custom"), std::string::npos);

    Exiv2::LogMsg::setHandler(anotherHandler);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "another";
    }
    EXPECT_EQ(g_handlerCallCount, 2);
    EXPECT_NE(g_lastMessage.find("another:"), std::string::npos);
}
