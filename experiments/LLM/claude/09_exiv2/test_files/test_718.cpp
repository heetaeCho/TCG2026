#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/error.hpp>
#include <string>
#include <vector>

// Global storage for capturing handler calls
struct HandlerCallInfo {
    int level;
    std::string message;
};

static std::vector<HandlerCallInfo> g_handlerCalls;

static void testHandler(int level, const char* s) {
    g_handlerCalls.push_back({level, s ? s : ""});
}

static void anotherHandler(int level, const char* s) {
    g_handlerCalls.push_back({level + 1000, s ? s : ""});
}

class LogMsgTest_718 : public ::testing::Test {
protected:
    void SetUp() override {
        g_handlerCalls.clear();
        // Reset to default state
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }

    void TearDown() override {
        g_handlerCalls.clear();
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }
};

// Test that default level is retrievable
TEST_F(LogMsgTest_718, DefaultLevelIsWarn_718) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);
}

// Test setting level to debug
TEST_F(LogMsgTest_718, SetLevelDebug_718) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);
}

// Test setting level to info
TEST_F(LogMsgTest_718, SetLevelInfo_718) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

// Test setting level to error
TEST_F(LogMsgTest_718, SetLevelError_718) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);
}

// Test setting level to mute
TEST_F(LogMsgTest_718, SetLevelMute_718) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::mute);
}

// Test setting a custom handler
TEST_F(LogMsgTest_718, SetCustomHandler_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), testHandler);
}

// Test getting the default handler
TEST_F(LogMsgTest_718, DefaultHandlerIsSet_718) {
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), Exiv2::LogMsg::defaultHandler);
}

// Test that handler is called when msgType >= level on destruction
TEST_F(LogMsgTest_718, HandlerCalledWhenMsgTypeAboveLevel_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "test message";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].message, "test message");
}

// Test that handler is called when msgType == level
TEST_F(LogMsgTest_718, HandlerCalledWhenMsgTypeEqualsLevel_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "exact level";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].message, "exact level");
}

// Test that handler is NOT called when msgType < level
TEST_F(LogMsgTest_718, HandlerNotCalledWhenMsgTypeBelowLevel_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "should not appear";
    }

    EXPECT_EQ(g_handlerCalls.size(), 0u);
}

// Test that debug messages are suppressed when level is warn
TEST_F(LogMsgTest_718, DebugMessagesSuppressedAtWarnLevel_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug msg";
    }

    EXPECT_EQ(g_handlerCalls.size(), 0u);
}

// Test that info messages are suppressed when level is warn
TEST_F(LogMsgTest_718, InfoMessagesSuppressedAtWarnLevel_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "info msg";
    }

    EXPECT_EQ(g_handlerCalls.size(), 0u);
}

// Test that error messages pass when level is warn
TEST_F(LogMsgTest_718, ErrorMessagesPassAtWarnLevel_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error msg";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].message, "error msg");
}

// Test level value is passed correctly to handler
TEST_F(LogMsgTest_718, HandlerReceivesCorrectLevel_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "level test";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].level, static_cast<int>(Exiv2::LogMsg::error));
}

// Test that the os() method returns a usable stream
TEST_F(LogMsgTest_718, OsStreamIsWritable_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "hello " << 42 << " world";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].message, "hello 42 world");
}

// Test empty message
TEST_F(LogMsgTest_718, EmptyMessage_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        // Don't write anything to os
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].message, "");
}

// Test switching handler
TEST_F(LogMsgTest_718, SwitchingHandler_718) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    Exiv2::LogMsg::setHandler(testHandler);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "first handler";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].message, "first handler");

    Exiv2::LogMsg::setHandler(anotherHandler);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "second handler";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    // anotherHandler adds 1000 to the level
    EXPECT_EQ(g_handlerCalls[0].level, static_cast<int>(Exiv2::LogMsg::warn) + 1000);
    EXPECT_EQ(g_handlerCalls[0].message, "second handler");
}

// Test that mute level suppresses all messages
TEST_F(LogMsgTest_718, MuteLevelSuppressesAll_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "should be muted";
    }

    EXPECT_EQ(g_handlerCalls.size(), 0u);
}

// Test that debug level allows all messages
TEST_F(LogMsgTest_718, DebugLevelAllowsAllMessages_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "info";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "warn";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error";
    }

    EXPECT_EQ(g_handlerCalls.size(), 4u);
}

// Test multiple writes to the same os stream
TEST_F(LogMsgTest_718, MultipleWritesToStream_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "part1";
        msg.os() << " part2";
        msg.os() << " part3";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].message, "part1 part2 part3");
}

// Test that setting handler to nullptr prevents handler call
TEST_F(LogMsgTest_718, NullHandlerPreventsCall_718) {
    Exiv2::LogMsg::setHandler(nullptr);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "no handler";
    }

    // With null handler, no crash should occur and no calls recorded
    EXPECT_EQ(g_handlerCalls.size(), 0u);
}

// Test defaultHandler doesn't crash (smoke test)
TEST_F(LogMsgTest_718, DefaultHandlerDoesNotCrash_718) {
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    // This should not crash - defaultHandler writes to stderr
    EXPECT_NO_THROW({
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "default handler test";
    });
}

// Test level() returns last set level
TEST_F(LogMsgTest_718, LevelReturnsLastSet_718) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::mute);
}

// Test handler() returns last set handler
TEST_F(LogMsgTest_718, HandlerReturnsLastSet_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), testHandler);

    Exiv2::LogMsg::setHandler(anotherHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), anotherHandler);

    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), Exiv2::LogMsg::defaultHandler);
}

// Test that debug level message type is passed to handler correctly
TEST_F(LogMsgTest_718, DebugLevelPassedToHandler_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "dbg";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].level, static_cast<int>(Exiv2::LogMsg::debug));
}

// Test info level message type is passed to handler correctly
TEST_F(LogMsgTest_718, InfoLevelPassedToHandler_718) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "inf";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].level, static_cast<int>(Exiv2::LogMsg::info));
}
