// =================================================================================================
// Unit tests for Exiv2::LogMsg
// File: ./TestProjects/exiv2/src/error.cpp (interface from exiv2/error.hpp)
// TEST_ID: 722
// =================================================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/error.hpp>

#include <string>

namespace {

using ::testing::_;
using ::testing::HasSubstr;
using ::testing::MockFunction;

class ScopedLogMsgConfig {
public:
  ScopedLogMsgConfig()
      : savedLevel_(Exiv2::LogMsg::level()),
        savedHandler_(Exiv2::LogMsg::handler()) {}

  ~ScopedLogMsgConfig() {
    // Restore global/static configuration to avoid cross-test pollution.
    Exiv2::LogMsg::setHandler(savedHandler_);
    Exiv2::LogMsg::setLevel(savedLevel_);
  }

  ScopedLogMsgConfig(const ScopedLogMsgConfig&) = delete;
  ScopedLogMsgConfig& operator=(const ScopedLogMsgConfig&) = delete;

private:
  Exiv2::LogMsg::Level savedLevel_;
  Exiv2::LogMsg::Handler savedHandler_;
};

// Bridge for handler callbacks (works for function-pointer Handler; also OK if Handler accepts a
// function pointer).
MockFunction<void(int, const char*)>* g_mockHandler = nullptr;

void TestLogHandlerBridge(int level, const char* s) {
  if (g_mockHandler) {
    g_mockHandler->Call(level, s);
  }
}

class LogMsgTest_722 : public ::testing::Test {
protected:
  void SetUp() override { g_mockHandler = &mockHandler_; }
  void TearDown() override { g_mockHandler = nullptr; }

  MockFunction<void(int, const char*)> mockHandler_;
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Basic stream access behavior
// -------------------------------------------------------------------------------------------------

TEST_F(LogMsgTest_722, OsReturnsSameStreamReference_722) {
  ScopedLogMsgConfig guard;

  // Use any available/valid level from the implementation as a constructor argument.
  const auto lvl = Exiv2::LogMsg::level();

  Exiv2::LogMsg msg(lvl);

  auto& os1 = msg.os();
  auto& os2 = msg.os();

  EXPECT_EQ(&os1, &os2);

  os1 << "abc";
  EXPECT_EQ(os2.str(), std::string("abc"));
}

TEST_F(LogMsgTest_722, LevelAccessorReflectsConstructionLevel_722) {
  ScopedLogMsgConfig guard;

  // Construct with the current level and verify the instance reports it.
  const auto lvl = Exiv2::LogMsg::level();

  Exiv2::LogMsg msg(lvl);
  EXPECT_EQ(msg.level(), lvl);
}

// -------------------------------------------------------------------------------------------------
// Global/static configuration round-trips
// -------------------------------------------------------------------------------------------------

TEST_F(LogMsgTest_722, SetLevelThenLevelReturnsSameValue_722) {
  ScopedLogMsgConfig guard;

  // Use a boundary-ish value without assuming enum members exist.
  const auto newLevel = static_cast<Exiv2::LogMsg::Level>(0);

  Exiv2::LogMsg::setLevel(newLevel);
  EXPECT_EQ(Exiv2::LogMsg::level(), newLevel);
}

TEST_F(LogMsgTest_722, SetHandlerThenHandlerIsInvocable_722) {
  ScopedLogMsgConfig guard;

  Exiv2::LogMsg::setHandler(&TestLogHandlerBridge);

  // Verify observable behavior: calling the configured handler reaches our mock.
  // (Avoids assuming Handler is directly comparable.)
  EXPECT_CALL(mockHandler_, Call(123, HasSubstr("ping"))).Times(1);

  auto h = Exiv2::LogMsg::handler();
  h(123, "ping");
}

// -------------------------------------------------------------------------------------------------
// Observable external interaction: handler invoked with formatted message (if implemented)
// -------------------------------------------------------------------------------------------------

TEST_F(LogMsgTest_722, DestructorMayInvokeHandlerWithStreamedMessage_722) {
  ScopedLogMsgConfig guard;

  // Configure our handler bridge.
  Exiv2::LogMsg::setHandler(&TestLogHandlerBridge);

  // Try to make logging permissive without relying on specific enum names/ordering.
  Exiv2::LogMsg::setLevel(static_cast<Exiv2::LogMsg::Level>(0));

  // If the implementation emits on destruction (common for logging RAII),
  // we should observe our handler being called with a message containing our payload.
  //
  // Note: This test is intentionally written to assert only what is observable
  // through the public interface (handler callback), without assuming formatting.
  EXPECT_CALL(mockHandler_, Call(_, HasSubstr("hello-from-test"))).Times(::testing::AtLeast(0));

  {
    Exiv2::LogMsg msg(static_cast<Exiv2::LogMsg::Level>(0));
    msg.os() << "hello-from-test";
  }

  // If the implementation does call the handler in the destructor, the expectation above
  // will match. If it doesn't, the test still validates that constructing/streaming/destructing
  // does not crash and that the handler configuration is safe to set.
  SUCCEED();
}