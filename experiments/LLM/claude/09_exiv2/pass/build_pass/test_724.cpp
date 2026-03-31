#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <exiv2/error.hpp>

namespace {

// Helper to capture handler calls
struct HandlerCapture {
    static int lastLevel;
    static std::string lastMessage;
    static int callCount;

    static void reset() {
        lastLevel = -1;
        lastMessage.clear();
        callCount = 0;
    }

    static void handler(int level, const char* s) {
        lastLevel = level;
        lastMessage = s ? s : "";
        callCount++;
    }
};

int HandlerCapture::lastLevel = -1;
std::string HandlerCapture::lastMessage;
int HandlerCapture::callCount = 0;

// Another handler for testing handler switching
void alternativeHandler(int level, const char* s) {
    // Do nothing
}

class LogMsgTest_724 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset to default state
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
        HandlerCapture::reset();
    }

    void TearDown() override {
        // Restore defaults
        Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    }
};

// Test that default level can be retrieved
TEST_F(LogMsgTest_724, DefaultLevelIsAccessible_724) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);
}

// Test setting level to debug
TEST_F(LogMsgTest_724, SetLevelDebug_724) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);
}

// Test setting level to info
TEST_F(LogMsgTest_724, SetLevelInfo_724) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);
}

// Test setting level to warn
TEST_F(LogMsgTest_724, SetLevelWarn_724) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);
}

// Test setting level to error
TEST_F(LogMsgTest_724, SetLevelError_724) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);
}

// Test setting level to mute
TEST_F(LogMsgTest_724, SetLevelMute_724) {
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::mute);
}

// Test setting a custom handler
TEST_F(LogMsgTest_724, SetCustomHandler_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), HandlerCapture::handler);
}

// Test that handler() returns default handler initially (or after reset)
TEST_F(LogMsgTest_724, HandlerReturnsDefaultAfterReset_724) {
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), Exiv2::LogMsg::defaultHandler);
}

// Test switching handlers
TEST_F(LogMsgTest_724, SwitchHandlers_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), HandlerCapture::handler);

    Exiv2::LogMsg::setHandler(alternativeHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), alternativeHandler);
}

// Test that LogMsg os() returns a valid ostringstream reference
TEST_F(LogMsgTest_724, OsReturnsValidStream_724) {
    Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
    std::ostringstream& os = msg.os();
    os << "test message";
    EXPECT_EQ(os.str(), "test message");
}

// Test that custom handler is called when LogMsg is destroyed with debug level
TEST_F(LogMsgTest_724, CustomHandlerCalledOnDestructionDebug_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "debug message";
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastLevel, Exiv2::LogMsg::debug);
    EXPECT_EQ(HandlerCapture::lastMessage, "debug message");
}

// Test that custom handler is called when LogMsg is destroyed with info level
TEST_F(LogMsgTest_724, CustomHandlerCalledOnDestructionInfo_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "info message";
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastLevel, Exiv2::LogMsg::info);
    EXPECT_EQ(HandlerCapture::lastMessage, "info message");
}

// Test that custom handler is called when LogMsg is destroyed with warn level
TEST_F(LogMsgTest_724, CustomHandlerCalledOnDestructionWarn_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "warn message";
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastLevel, Exiv2::LogMsg::warn);
    EXPECT_EQ(HandlerCapture::lastMessage, "warn message");
}

// Test that custom handler is called when LogMsg is destroyed with error level
TEST_F(LogMsgTest_724, CustomHandlerCalledOnDestructionError_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error message";
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastLevel, Exiv2::LogMsg::error);
    EXPECT_EQ(HandlerCapture::lastMessage, "error message");
}

// Test that messages below the current level are suppressed
TEST_F(LogMsgTest_724, MessageBelowLevelSuppressed_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "should not appear";
    }

    EXPECT_EQ(HandlerCapture::callCount, 0);
}

// Test that info messages are suppressed when level is warn
TEST_F(LogMsgTest_724, InfoSuppressedWhenLevelIsWarn_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "suppressed info";
    }

    EXPECT_EQ(HandlerCapture::callCount, 0);
}

// Test that warn messages pass when level is warn
TEST_F(LogMsgTest_724, WarnPassesWhenLevelIsWarn_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "warn passes";
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastMessage, "warn passes");
}

// Test that error messages pass when level is warn
TEST_F(LogMsgTest_724, ErrorPassesWhenLevelIsWarn_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "error passes";
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastMessage, "error passes");
}

// Test that mute level suppresses all messages
TEST_F(LogMsgTest_724, MuteSuppressesAll_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "should be muted";
    }

    EXPECT_EQ(HandlerCapture::callCount, 0);
}

// Test that mute level suppresses debug messages
TEST_F(LogMsgTest_724, MuteSuppressesDebug_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "muted debug";
    }

    EXPECT_EQ(HandlerCapture::callCount, 0);
}

// Test empty message
TEST_F(LogMsgTest_724, EmptyMessage_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        // Write nothing to os
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastMessage, "");
}

// Test multiple LogMsg objects in sequence
TEST_F(LogMsgTest_724, MultipleMessagesInSequence_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "first";
    }
    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastMessage, "first");

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "second";
    }
    EXPECT_EQ(HandlerCapture::callCount, 2);
    EXPECT_EQ(HandlerCapture::lastMessage, "second");
    EXPECT_EQ(HandlerCapture::lastLevel, Exiv2::LogMsg::info);
}

// Test that defaultHandler can be called directly
TEST_F(LogMsgTest_724, DefaultHandlerDirectCallDebug_724) {
    // Capture stderr
    std::streambuf* oldBuf = std::cerr.rdbuf();
    std::ostringstream capturedStderr;
    std::cerr.rdbuf(capturedStderr.rdbuf());

    Exiv2::LogMsg::defaultHandler(Exiv2::LogMsg::debug, "test debug\n");

    std::cerr.rdbuf(oldBuf);

    std::string output = capturedStderr.str();
    EXPECT_NE(output.find("Debug:"), std::string::npos);
    EXPECT_NE(output.find("test debug"), std::string::npos);
}

// Test that defaultHandler can be called directly with info
TEST_F(LogMsgTest_724, DefaultHandlerDirectCallInfo_724) {
    std::streambuf* oldBuf = std::cerr.rdbuf();
    std::ostringstream capturedStderr;
    std::cerr.rdbuf(capturedStderr.rdbuf());

    Exiv2::LogMsg::defaultHandler(Exiv2::LogMsg::info, "test info\n");

    std::cerr.rdbuf(oldBuf);

    std::string output = capturedStderr.str();
    EXPECT_NE(output.find("Info:"), std::string::npos);
    EXPECT_NE(output.find("test info"), std::string::npos);
}

// Test that defaultHandler can be called directly with warn
TEST_F(LogMsgTest_724, DefaultHandlerDirectCallWarn_724) {
    std::streambuf* oldBuf = std::cerr.rdbuf();
    std::ostringstream capturedStderr;
    std::cerr.rdbuf(capturedStderr.rdbuf());

    Exiv2::LogMsg::defaultHandler(Exiv2::LogMsg::warn, "test warn\n");

    std::cerr.rdbuf(oldBuf);

    std::string output = capturedStderr.str();
    EXPECT_NE(output.find("Warning:"), std::string::npos);
    EXPECT_NE(output.find("test warn"), std::string::npos);
}

// Test that defaultHandler can be called directly with error
TEST_F(LogMsgTest_724, DefaultHandlerDirectCallError_724) {
    std::streambuf* oldBuf = std::cerr.rdbuf();
    std::ostringstream capturedStderr;
    std::cerr.rdbuf(capturedStderr.rdbuf());

    Exiv2::LogMsg::defaultHandler(Exiv2::LogMsg::error, "test error\n");

    std::cerr.rdbuf(oldBuf);

    std::string output = capturedStderr.str();
    EXPECT_NE(output.find("Error:"), std::string::npos);
    EXPECT_NE(output.find("test error"), std::string::npos);
}

// Test enum values
TEST_F(LogMsgTest_724, EnumValues_724) {
    EXPECT_EQ(static_cast<int>(Exiv2::LogMsg::debug), 0);
    EXPECT_EQ(static_cast<int>(Exiv2::LogMsg::info), 1);
    EXPECT_EQ(static_cast<int>(Exiv2::LogMsg::warn), 2);
    EXPECT_EQ(static_cast<int>(Exiv2::LogMsg::error), 3);
    EXPECT_EQ(static_cast<int>(Exiv2::LogMsg::mute), 4);
}

// Test level ordering - debug level allows all messages
TEST_F(LogMsgTest_724, DebugLevelAllowsAllMessages_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "d";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "i";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "w";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "e";
    }

    EXPECT_EQ(HandlerCapture::callCount, 4);
}

// Test error level only allows error messages
TEST_F(LogMsgTest_724, ErrorLevelOnlyAllowsError_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "d";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::info);
        msg.os() << "i";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "w";
    }
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::error);
        msg.os() << "e";
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastLevel, Exiv2::LogMsg::error);
    EXPECT_EQ(HandlerCapture::lastMessage, "e");
}

// Test streaming multiple items to os
TEST_F(LogMsgTest_724, StreamMultipleItemsToOs_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    HandlerCapture::reset();

    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
        msg.os() << "count=" << 42 << " flag=" << true;
    }

    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastMessage, "count=42 flag=1");
}

// Test that setting handler back to default works
TEST_F(LogMsgTest_724, SetHandlerBackToDefault_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), HandlerCapture::handler);

    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    EXPECT_EQ(Exiv2::LogMsg::handler(), Exiv2::LogMsg::defaultHandler);
}

// Test changing level between messages
TEST_F(LogMsgTest_724, ChangeLevelBetweenMessages_724) {
    Exiv2::LogMsg::setHandler(HandlerCapture::handler);
    HandlerCapture::reset();

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "suppressed";
    }
    EXPECT_EQ(HandlerCapture::callCount, 0);

    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
    {
        Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
        msg.os() << "not suppressed";
    }
    EXPECT_EQ(HandlerCapture::callCount, 1);
    EXPECT_EQ(HandlerCapture::lastMessage, "not suppressed");
}

} // anonymous namespace
