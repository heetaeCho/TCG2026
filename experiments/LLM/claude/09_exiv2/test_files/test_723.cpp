#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/error.hpp>
#include <sstream>
#include <string>

// Store captured log messages for verification
static int g_lastLevel = -1;
static std::string g_lastMessage;

static void customHandler(int level, const char* s) {
    g_lastLevel = level;
    g_lastMessage = s ? s : "";
}

static int g_callCount = 0;
static void countingHandler(int level, const char* s) {
    g_callCount++;
    g_lastLevel = level;
    g_lastMessage = s ? s : "";
}

class LogMsgTest_723 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset to defaults before each test
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
        g_lastLevel = -1;
        g_lastMessage.clear();
        g_callCount = 0;
    }

    void TearDown() override {
        // Restore defaults after each test
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }
};

// Test that handler() returns the default handler initially
TEST_F(LogMsgTest_723, DefaultHandlerIsSet_723) {
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    Exiv2::LogMsg::Handler h = Exiv2::LogMsg::handler();
    ASSERT_NE(h, nullptr);
    EXPECT_EQ(h, Exiv2::LogMsg::defaultHandler);
}

// Test that setHandler changes the handler
TEST_F(LogMsgTest_723, SetHandlerChangesHandler_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), customHandler);
}

// Test that setting handler back to default works
TEST_F(LogMsgTest_723, SetHandlerBackToDefault_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), customHandler);
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), Exiv2::LogMsg::defaultHandler);
}

// Test that default level is warn
TEST_F(LogMsgTest_723, DefaultLevelIsWarn_723) {
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);
}

// Test setLevel and level
TEST_F(LogMsgTest_723, SetLevelChangesLevel_723) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);
}

TEST_F(LogMsgTest_723, SetLevelToError_723) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);
}

TEST_F(LogMsgTest_723, SetLevelToInfo_723) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

TEST_F(LogMsgTest_723, SetLevelToMute_723) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::mute);
}

// Test that os() returns a valid ostringstream reference
TEST_F(LogMsgTest_723, OsReturnsValidStream_723) {
    Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
    std::ostringstream& os = msg.os();
    os << "test message";
    EXPECT_EQ(os.str(), "test message");
}

// Test that custom handler is called when LogMsg is destroyed
TEST_F(LogMsgTest_723, CustomHandlerCalledOnDestruction_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "hello world";
    }
    // After destruction, handler should have been called
    EXPECT_NE(g_lastLevel, -1);
    EXPECT_FALSE(g_lastMessage.empty());
}

// Test that handler is NOT called when message level is below current log level
TEST_F(LogMsgTest_723, HandlerNotCalledBelowLevel_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug message";
    }
    // Handler should not be called since debug < error
    EXPECT_EQ(g_lastLevel, -1);
    EXPECT_TRUE(g_lastMessage.empty());
}

// Test that handler is called when message level equals current log level
TEST_F(LogMsgTest_723, HandlerCalledAtExactLevel_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error message";
    }
    EXPECT_NE(g_lastLevel, -1);
}

// Test that handler is called when message level is above current log level
TEST_F(LogMsgTest_723, HandlerCalledAboveLevel_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error message";
    }
    EXPECT_NE(g_lastLevel, -1);
}

// Test that message content is passed to handler
TEST_F(LogMsgTest_723, HandlerReceivesMessageContent_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "specific content 12345";
    }
    EXPECT_NE(g_lastMessage.find("specific content 12345"), std::string::npos);
}

// Test that mute level suppresses all messages
TEST_F(LogMsgTest_723, MuteLevelSuppressesAll_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "should not appear";
    }
    // With mute, no message should be sent to handler
    EXPECT_EQ(g_lastLevel, -1);
}

// Test multiple messages with counting handler
TEST_F(LogMsgTest_723, MultipleMessagesCallHandler_723) {
    Exiv2::LogMsg::setHandler(countingHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "first";
    }
    EXPECT_EQ(g_callCount, 1);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "second";
    }
    EXPECT_EQ(g_callCount, 2);
}

// Test that os() can be used with stream operators
TEST_F(LogMsgTest_723, OsSupportsStreamOperators_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "number: " << 42 << " float: " << 3.14;
    }
    EXPECT_NE(g_lastMessage.find("42"), std::string::npos);
    EXPECT_NE(g_lastMessage.find("3.14"), std::string::npos);
}

// Test defaultHandler can be called directly without crash
TEST_F(LogMsgTest_723, DefaultHandlerCanBeCalledDirectly_723) {
    EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(0, "test"));
}

// Test defaultHandler with nullptr string doesn't crash
TEST_F(LogMsgTest_723, DefaultHandlerWithNullString_723) {
    EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(0, nullptr));
}

// Test that LogMsg is non-copyable (compile-time check would be needed;
// we verify the interface declares delete)
// This is implicitly tested by the fact that copy constructor and
// assignment operator are deleted in the header.

// Test empty message
TEST_F(LogMsgTest_723, EmptyMessage_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        // Don't write anything to os
    }
    // Handler should still be called, possibly with empty or minimal content
    EXPECT_NE(g_lastLevel, -1);
}

// Test handler receives correct level
TEST_F(LogMsgTest_723, HandlerReceivesCorrectLevel_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "test";
    }
    // The level passed to handler should correspond to LogMsg::error
    EXPECT_EQ(g_lastLevel, static_cast<int>(Exiv2::LogMsg::error));
}

// Test info level message with handler
TEST_F(LogMsgTest_723, InfoLevelMessage_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "info message";
    }
    EXPECT_EQ(g_lastLevel, static_cast<int>(Exiv2::LogMsg::info));
}

// Test debug level message with handler
TEST_F(LogMsgTest_723, DebugLevelMessage_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug message";
    }
    EXPECT_EQ(g_lastLevel, static_cast<int>(Exiv2::LogMsg::debug));
}

// Test switching handlers between messages
TEST_F(LogMsgTest_723, SwitchHandlersBetweenMessages_723) {
    Exiv2::LogMsg::setHandler(customHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "first handler";
    }
    EXPECT_EQ(Exiv2::LogMsg::handler(), customHandler);
    
    Exiv2::LogMsg::setHandler(countingHandler);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "second handler";
    }
    EXPECT_EQ(g_callCount, 1);
    EXPECT_EQ(Exiv2::LogMsg::handler(), countingHandler);
}
