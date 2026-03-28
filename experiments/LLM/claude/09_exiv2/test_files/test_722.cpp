#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/error.hpp>
#include <sstream>
#include <string>

// Helper to capture handler calls
static int g_lastHandlerLevel = -1;
static std::string g_lastHandlerMessage;
static int g_handlerCallCount = 0;

static void testHandler(int level, const char* s) {
    g_lastHandlerLevel = level;
    g_lastHandlerMessage = s ? s : "";
    g_handlerCallCount++;
}

static void anotherHandler(int level, const char* s) {
    g_lastHandlerLevel = level * 10;
    g_lastHandlerMessage = std::string("another:") + (s ? s : "");
    g_handlerCallCount++;
}

class LogMsgTest_722 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset to defaults before each test
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
        g_lastHandlerLevel = -1;
        g_lastHandlerMessage.clear();
        g_handlerCallCount = 0;
    }

    void TearDown() override {
        // Restore defaults after each test
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    }
};

// Test that the static level() returns the level set by setLevel()
TEST_F(LogMsgTest_722, SetAndGetLevel_722) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);
}

TEST_F(LogMsgTest_722, SetLevelDebug_722) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);
}

TEST_F(LogMsgTest_722, SetLevelInfo_722) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

TEST_F(LogMsgTest_722, SetLevelError_722) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);
}

TEST_F(LogMsgTest_722, SetLevelMute_722) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::mute);
}

// Test that setHandler and handler work correctly
TEST_F(LogMsgTest_722, SetAndGetHandler_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), testHandler);
}

TEST_F(LogMsgTest_722, DefaultHandlerIsNotNull_722) {
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_NE(Exiv2::LogMsg::handler(), nullptr);
}

TEST_F(LogMsgTest_722, SetCustomHandler_722) {
    Exiv2::LogMsg::setHandler(anotherHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), anotherHandler);
}

// Test that os() returns a valid stream
TEST_F(LogMsgTest_722, OsReturnsValidStream_722) {
    Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
    std::ostringstream& os = msg.os();
    os << "test message";
    // Should not crash, and the stream should contain data
    EXPECT_FALSE(os.str().empty());
}

// Test that the handler is called upon destruction with the message
TEST_F(LogMsgTest_722, HandlerCalledOnDestruction_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "hello world";
    }

    EXPECT_EQ(g_handlerCallCount, 1);
    EXPECT_NE(g_lastHandlerMessage.find("hello world"), std::string::npos);
}

// Test that handler receives correct level
TEST_F(LogMsgTest_722, HandlerReceivesCorrectLevel_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "warning message";
    }

    EXPECT_EQ(g_lastHandlerLevel, static_cast<int>(Exiv2::LogMsg::warn));
}

// Test that messages below current level are suppressed
TEST_F(LogMsgTest_722, MessageBelowLevelSuppressed_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "should be suppressed";
    }

    // The handler should not be called for messages below current level
    EXPECT_EQ(g_handlerCallCount, 0);
}

// Test that messages at or above current level are not suppressed
TEST_F(LogMsgTest_722, MessageAtLevelNotSuppressed_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "warning at threshold";
    }

    EXPECT_EQ(g_handlerCallCount, 1);
}

TEST_F(LogMsgTest_722, MessageAboveLevelNotSuppressed_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error above threshold";
    }

    EXPECT_EQ(g_handlerCallCount, 1);
}

// Test mute level suppresses all messages
TEST_F(LogMsgTest_722, MuteLevelSuppressesAll_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "should be muted";
    }

    EXPECT_EQ(g_handlerCallCount, 0);
}

// Test debug level allows all messages
TEST_F(LogMsgTest_722, DebugLevelAllowsAll_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug message";
    }

    EXPECT_EQ(g_handlerCallCount, 1);
}

// Test that changing handler mid-flight works
TEST_F(LogMsgTest_722, ChangingHandlerWorks_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "first";
    }

    EXPECT_EQ(g_handlerCallCount, 1);
    EXPECT_EQ(g_lastHandlerLevel, static_cast<int>(Exiv2::LogMsg::error));

    Exiv2::LogMsg::setHandler(anotherHandler);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "second";
    }

    EXPECT_EQ(g_handlerCallCount, 1);
    // anotherHandler multiplies level by 10
    EXPECT_EQ(g_lastHandlerLevel, static_cast<int>(Exiv2::LogMsg::error) * 10);
    EXPECT_NE(g_lastHandlerMessage.find("another:"), std::string::npos);
}

// Test multiple writes to os()
TEST_F(LogMsgTest_722, MultipleWritesToOs_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "part1 ";
        msg.os() << "part2 ";
        msg.os() << "part3";
    }

    EXPECT_NE(g_lastHandlerMessage.find("part1"), std::string::npos);
    EXPECT_NE(g_lastHandlerMessage.find("part2"), std::string::npos);
    EXPECT_NE(g_lastHandlerMessage.find("part3"), std::string::npos);
}

// Test empty message
TEST_F(LogMsgTest_722, EmptyMessage_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        // Don't write anything to os()
    }

    EXPECT_EQ(g_handlerCallCount, 1);
}

// Test that defaultHandler can be called directly without crash
TEST_F(LogMsgTest_722, DefaultHandlerDirectCall_722) {
    EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(0, "test direct call"));
}

// Test setting level multiple times
TEST_F(LogMsgTest_722, SetLevelMultipleTimes_722) {
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

// Test info level suppresses debug
TEST_F(LogMsgTest_722, InfoLevelSuppressesDebug_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug should be suppressed";
    }

    EXPECT_EQ(g_handlerCallCount, 0);
}

// Test info level allows info
TEST_F(LogMsgTest_722, InfoLevelAllowsInfo_722) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    g_handlerCallCount = 0;

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "info should pass";
    }

    EXPECT_EQ(g_handlerCallCount, 1);
}
