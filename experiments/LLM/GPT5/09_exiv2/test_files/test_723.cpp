// File: test_logmsg_723.cpp
// Unit tests for Exiv2::LogMsg (error.cpp / error.hpp)
// TEST_ID: 723

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/error.hpp"

#include <sstream>
#include <string>

namespace {

using ::testing::_;
using ::testing::NotNull;

class HandlerRestoreGuard final {
 public:
  using HandlerType = decltype(Exiv2::LogMsg::handler());

  HandlerRestoreGuard()
      : old_(Exiv2::LogMsg::handler()) {}

  ~HandlerRestoreGuard() { Exiv2::LogMsg::setHandler(old_); }

  HandlerRestoreGuard(const HandlerRestoreGuard&) = delete;
  HandlerRestoreGuard& operator=(const HandlerRestoreGuard&) = delete;

 private:
  HandlerType old_;
};

class LevelRestoreGuard final {
 public:
  using LevelType = decltype(Exiv2::LogMsg::level());

  LevelRestoreGuard()
      : old_(Exiv2::LogMsg::level()) {}

  ~LevelRestoreGuard() { Exiv2::LogMsg::setLevel(old_); }

  LevelRestoreGuard(const LevelRestoreGuard&) = delete;
  LevelRestoreGuard& operator=(const LevelRestoreGuard&) = delete;

 private:
  LevelType old_;
};

class MockHandlerSink {
 public:
  MOCK_METHOD(void, Call, (int level, const char* s));
};

MockHandlerSink* g_sink = nullptr;

// Matches the signature shown for LogMsg::defaultHandler(int level, const char* s).
static void TestHandlerThunk(int level, const char* s) {
  if (g_sink) {
    g_sink->Call(level, s);
  }
}

class LogMsgTest_723 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Keep tests isolated from each other and from global logging settings.
    handler_guard_ = std::make_unique<HandlerRestoreGuard>();
    level_guard_ = std::make_unique<LevelRestoreGuard>();
  }

  void TearDown() override {
    // Guards restore state.
    level_guard_.reset();
    handler_guard_.reset();
  }

 private:
  std::unique_ptr<HandlerRestoreGuard> handler_guard_;
  std::unique_ptr<LevelRestoreGuard> level_guard_;
};

}  // namespace

TEST_F(LogMsgTest_723, StaticHandlerRoundTripsAfterSetHandler_723) {
  const auto old_handler = Exiv2::LogMsg::handler();

  Exiv2::LogMsg::setHandler(&TestHandlerThunk);
  const auto new_handler = Exiv2::LogMsg::handler();

  // Observable behavior: setHandler influences the value returned by handler().
  EXPECT_TRUE(static_cast<bool>(new_handler));
  EXPECT_EQ(new_handler, &TestHandlerThunk);

  // Restore explicitly (also handled by guard).
  Exiv2::LogMsg::setHandler(old_handler);
  EXPECT_EQ(Exiv2::LogMsg::handler(), old_handler);
}

TEST_F(LogMsgTest_723, InstanceHandlerMatchesCurrentGlobalHandler_723) {
  Exiv2::LogMsg::setHandler(&TestHandlerThunk);

  // Construct using an observable Level value without assuming enum members.
  const auto lvl = Exiv2::LogMsg::level();
  Exiv2::LogMsg msg(lvl);

  // Observable behavior from interface: instance handler() returns a Handler.
  EXPECT_EQ(msg.handler(), Exiv2::LogMsg::handler());
  EXPECT_EQ(msg.handler(), &TestHandlerThunk);
}

TEST_F(LogMsgTest_723, OsReturnsStreamReferenceAndCanAccumulateText_723) {
  const auto lvl = Exiv2::LogMsg::level();
  Exiv2::LogMsg msg(lvl);

  std::ostringstream& os1 = msg.os();
  std::ostringstream& os2 = msg.os();

  // Observable: os() returns a reference; repeated calls should refer to the same stream object.
  EXPECT_EQ(&os1, &os2);

  os1 << "hello";
  os2 << " world";

  EXPECT_EQ(msg.os().str(), "hello world");
}

TEST_F(LogMsgTest_723, DefaultHandlerIsCallableAndDoesNotThrow_723) {
  // We don't assert on side-effects (stdout/stderr), only that the interface call is safe.
  EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(0, "test message"));
  EXPECT_NO_THROW(Exiv2::LogMsg::defaultHandler(1, ""));
}

TEST_F(LogMsgTest_723, CustomHandlerIsCallableAndReceivesParameters_723) {
  Exiv2::LogMsg::setHandler(&TestHandlerThunk);

  MockHandlerSink sink;
  g_sink = &sink;

  const auto h = Exiv2::LogMsg::handler();
  ASSERT_TRUE(static_cast<bool>(h));

  EXPECT_CALL(sink, Call(7, NotNull())).Times(1);
  h(7, "payload");

  g_sink = nullptr;
}