#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/error.hpp>
#include <sstream>
#include <string>
#include <vector>

// Helper to capture handler calls
static std::vector<std::pair<int, std::string>> g_handlerCalls;

static void testHandler(int level, const char* s) {
    g_handlerCalls.emplace_back(level, s ? s : "");
}

class LogMsgTest_720 : public ::testing::Test {
protected:
    void SetUp() override {
        g_handlerCalls.clear();
        // Reset to default handler and a known level
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }

    void TearDown() override {
        g_handlerCalls.clear();
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    }
};

TEST_F(LogMsgTest_720, DefaultLevel_720) {
    // After setting level to warn, level() should return warn
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);
}

TEST_F(LogMsgTest_720, SetLevelDebug_720) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);
}

TEST_F(LogMsgTest_720, SetLevelInfo_720) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

TEST_F(LogMsgTest_720, SetLevelError_720) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);
}

TEST_F(LogMsgTest_720, SetLevelMute_720) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::mute);
}

TEST_F(LogMsgTest_720, SetCustomHandler_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), testHandler);
}

TEST_F(LogMsgTest_720, SetDefaultHandler_720) {
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), Exiv2::LogMsg::defaultHandler);
}

TEST_F(LogMsgTest_720, HandlerReturnsCurrentHandler_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    auto h = Exiv2::LogMsg::handler();
    EXPECT_NE(h, nullptr);
    EXPECT_EQ(h, testHandler);
}

TEST_F(LogMsgTest_720, CustomHandlerCalledOnDestruction_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "Test message";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].first, static_cast<int>(Exiv2::LogMsg::warn));
    EXPECT_NE(g_handlerCalls[0].second.find("Test message"), std::string::npos);
}

TEST_F(LogMsgTest_720, HandlerNotCalledWhenLevelBelowThreshold_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "Should not appear";
    }

    EXPECT_EQ(g_handlerCalls.size(), 0u);
}

TEST_F(LogMsgTest_720, HandlerCalledWhenLevelAtThreshold_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "Error message";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].first, static_cast<int>(Exiv2::LogMsg::error));
    EXPECT_NE(g_handlerCalls[0].second.find("Error message"), std::string::npos);
}

TEST_F(LogMsgTest_720, HandlerNotCalledWhenMuted_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "Muted message";
    }

    EXPECT_EQ(g_handlerCalls.size(), 0u);
}

TEST_F(LogMsgTest_720, DebugLevelAllowsAllMessages_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "Debug msg";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "Info msg";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "Warn msg";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "Error msg";
    }

    EXPECT_EQ(g_handlerCalls.size(), 4u);
}

TEST_F(LogMsgTest_720, OsReturnsUsableStream_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "Number: " << 42 << " Float: " << 3.14;
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_NE(g_handlerCalls[0].second.find("Number: 42"), std::string::npos);
    EXPECT_NE(g_handlerCalls[0].second.find("Float: 3.14"), std::string::npos);
}

TEST_F(LogMsgTest_720, EmptyMessage_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        // No output to os
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
}

TEST_F(LogMsgTest_720, MultipleSetLevelCalls_720) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

TEST_F(LogMsgTest_720, HandlerLevelParameter_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    g_handlerCalls.clear();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "info test";
    }

    ASSERT_EQ(g_handlerCalls.size(), 1u);
    EXPECT_EQ(g_handlerCalls[0].first, static_cast<int>(Exiv2::LogMsg::info));
}

TEST_F(LogMsgTest_720, SetNullHandler_720) {
    // Setting handler to nullptr - should not crash
    Exiv2::LogMsg::setHandler(nullptr);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "This should not crash";
    }
    // If we get here without crash, the test passes
    SUCCEED();
}

TEST_F(LogMsgTest_720, WarnLevelFiltersDebugAndInfo_720) {
    Exiv2::LogMsg::setHandler(testHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
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

    EXPECT_EQ(g_handlerCalls.size(), 2u);
    if (g_handlerCalls.size() >= 1) {
        EXPECT_EQ(g_handlerCalls[0].first, static_cast<int>(Exiv2::LogMsg::warn));
    }
    if (g_handlerCalls.size() >= 2) {
        EXPECT_EQ(g_handlerCalls[1].first, static_cast<int>(Exiv2::LogMsg::error));
    }
}

TEST_F(LogMsgTest_720, DefaultHandlerIsNotNull_720) {
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_NE(Exiv2::LogMsg::handler(), nullptr);
}
