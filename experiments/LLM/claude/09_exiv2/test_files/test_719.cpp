#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <exiv2/error.hpp>

// Test fixture for LogMsg tests
class LogMsgTest_719 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset to default handler and level before each test
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
  }

  void TearDown() override {
    // Restore defaults after each test
    Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
  }
};

// Helper: a custom handler that records calls
static int g_lastLevel_719 = -1;
static std::string g_lastMessage_719;
static int g_handlerCallCount_719 = 0;

static void testHandler_719(int level, const char* s) {
  g_lastLevel_719 = level;
  g_lastMessage_719 = s ? s : "";
  g_handlerCallCount_719++;
}

static void resetTestHandler_719() {
  g_lastLevel_719 = -1;
  g_lastMessage_719.clear();
  g_handlerCallCount_719 = 0;
}

// Test that os() returns a valid ostringstream reference that can be written to
TEST_F(LogMsgTest_719, OsReturnsValidStream_719) {
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
  Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
  msg.os() << "Hello World";
  std::string result = msg.os().str();
  EXPECT_EQ(result, "Hello World");
}

// Test that os() can handle multiple writes
TEST_F(LogMsgTest_719, OsHandlesMultipleWrites_719) {
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
  Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
  msg.os() << "Part1" << " " << "Part2";
  std::string result = msg.os().str();
  EXPECT_EQ(result, "Part1 Part2");
}

// Test that os() can handle numeric output
TEST_F(LogMsgTest_719, OsHandlesNumericOutput_719) {
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
  Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
  msg.os() << 42 << " " << 3.14;
  std::string result = msg.os().str();
  EXPECT_FALSE(result.empty());
}

// Test that setLevel and level work correctly
TEST_F(LogMsgTest_719, SetLevelAndGetLevel_719) {
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
  EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::debug);

  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);
  EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::info);

  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
  EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);

  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);
  EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::error);
}

// Test that setHandler and handler work correctly
TEST_F(LogMsgTest_719, SetHandlerAndGetHandler_719) {
  Exiv2::LogMsg::Handler originalHandler = Exiv2::LogMsg::handler();
  EXPECT_NE(originalHandler, nullptr);

  Exiv2::LogMsg::setHandler(testHandler_719);
  EXPECT_EQ(Exiv2::LogMsg::handler(), testHandler_719);

  Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
  EXPECT_EQ(Exiv2::LogMsg::handler(), Exiv2::LogMsg::defaultHandler);
}

// Test that the custom handler is called upon LogMsg destruction when level matches
TEST_F(LogMsgTest_719, CustomHandlerCalledOnDestruction_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
    msg.os() << "Test message";
  }  // destructor called here

  EXPECT_EQ(g_handlerCallCount_719, 1);
  EXPECT_NE(g_lastMessage_719.find("Test message"), std::string::npos);
}

// Test that handler is NOT called when message level is below current level
TEST_F(LogMsgTest_719, HandlerNotCalledWhenBelowLevel_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::error);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
    msg.os() << "Should not appear";
  }

  EXPECT_EQ(g_handlerCallCount_719, 0);
}

// Test that handler IS called when message level equals current level
TEST_F(LogMsgTest_719, HandlerCalledWhenAtLevel_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::info);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::info);
    msg.os() << "Info message";
  }

  EXPECT_EQ(g_handlerCallCount_719, 1);
}

// Test that handler IS called when message level is above current level
TEST_F(LogMsgTest_719, HandlerCalledWhenAboveLevel_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::error);
    msg.os() << "Error message";
  }

  EXPECT_EQ(g_handlerCallCount_719, 1);
}

// Test that the level passed to the handler matches the LogMsg level
TEST_F(LogMsgTest_719, HandlerReceivesCorrectLevel_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::error);
    msg.os() << "Error";
  }

  EXPECT_EQ(g_lastLevel_719, static_cast<int>(Exiv2::LogMsg::error));
}

// Test that the default handler is not null
TEST_F(LogMsgTest_719, DefaultHandlerIsNotNull_719) {
  EXPECT_NE(Exiv2::LogMsg::handler(), nullptr);
}

// Test that default level is typically warn
TEST_F(LogMsgTest_719, DefaultLevelIsWarn_719) {
  // After SetUp restores warn
  EXPECT_EQ(Exiv2::LogMsg::level(), Exiv2::LogMsg::warn);
}

// Test that empty message is handled correctly
TEST_F(LogMsgTest_719, EmptyMessage_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::warn);
    // Write nothing
  }

  EXPECT_EQ(g_handlerCallCount_719, 1);
}

// Test that os() returns the same stream on multiple calls
TEST_F(LogMsgTest_719, OsReturnsSameStream_719) {
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
  Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
  std::ostringstream& ref1 = msg.os();
  std::ostringstream& ref2 = msg.os();
  EXPECT_EQ(&ref1, &ref2);
}

// Test multiple LogMsg instances with custom handler
TEST_F(LogMsgTest_719, MultipleLogMsgInstances_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

  {
    Exiv2::LogMsg msg1(Exiv2::LogMsg::debug);
    msg1.os() << "First";
  }
  {
    Exiv2::LogMsg msg2(Exiv2::LogMsg::info);
    msg2.os() << "Second";
  }
  {
    Exiv2::LogMsg msg3(Exiv2::LogMsg::warn);
    msg3.os() << "Third";
  }

  EXPECT_EQ(g_handlerCallCount_719, 3);
}

// Test setting mute level (above all levels) suppresses all messages
TEST_F(LogMsgTest_719, MuteLevelSuppressesMessages_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::error);
    msg.os() << "Should be muted";
  }

  EXPECT_EQ(g_handlerCallCount_719, 0);
}

// Test debug level allows all messages
TEST_F(LogMsgTest_719, DebugLevelAllowsAll_719) {
  resetTestHandler_719();
  Exiv2::LogMsg::setHandler(testHandler_719);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);

  {
    Exiv2::LogMsg msg(Exiv2::LogMsg::debug);
    msg.os() << "Debug";
  }

  EXPECT_EQ(g_handlerCallCount_719, 1);
}

// Test that defaultHandler can be called directly without crashing
TEST_F(LogMsgTest_719, DefaultHandlerDirectCall_719) {
  EXPECT_NO_FATAL_FAILURE(Exiv2::LogMsg::defaultHandler(0, "test direct call"));
}

// Test setting handler to nullptr (if allowed, or test that it doesn't crash)
TEST_F(LogMsgTest_719, SetNullHandler_719) {
  // Setting a null handler - behavior may vary. Test that setting it doesn't crash.
  // The actual behavior when handler is null during LogMsg destruction depends on implementation.
  Exiv2::LogMsg::setHandler(nullptr);
  Exiv2::LogMsg::Handler h = Exiv2::LogMsg::handler();
  EXPECT_EQ(h, nullptr);

  // Restore to avoid issues in teardown
  Exiv2::LogMsg::setHandler(Exiv2::LogMsg::defaultHandler);
}
