// File: test_logmsg_718.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/error.hpp"

#include <string>

namespace {

using ::testing::_;
using ::testing::Eq;
using ::testing::NotNull;
using ::testing::StrEq;

class MockLogHandler {
public:
  MOCK_METHOD(void, Call, (int level, const char* s), ());
};

// Trampoline to adapt to LogMsg::Handler (commonly a function pointer type).
static MockLogHandler* g_mock_handler = nullptr;

static void HandlerTrampoline(int level, const char* s) {
  if (g_mock_handler) {
    g_mock_handler->Call(level, s);
  }
}

class LogMsgTest_718 : public ::testing::Test {
protected:
  using Level = decltype(Exiv2::LogMsg::level());
  using Handler = decltype(Exiv2::LogMsg::handler());

  void SetUp() override {
    saved_level_ = Exiv2::LogMsg::level();
    saved_handler_ = Exiv2::LogMsg::handler();
    g_mock_handler = nullptr;
    // Default to "no handler" unless a test sets one.
    Exiv2::LogMsg::setHandler(saved_handler_);
    Exiv2::LogMsg::setLevel(saved_level_);
  }

  void TearDown() override {
    g_mock_handler = nullptr;
    Exiv2::LogMsg::setHandler(saved_handler_);
    Exiv2::LogMsg::setLevel(saved_level_);
  }

  static Level L(int v) { return static_cast<Level>(v); }

  Level saved_level_{};
  Handler saved_handler_{};
};

TEST_F(LogMsgTest_718, SetLevelAndLevelGetterRoundTrip_718) {
  Exiv2::LogMsg::setLevel(L(3));
  EXPECT_EQ(Exiv2::LogMsg::level(), L(3));

  Exiv2::LogMsg::setLevel(L(0));
  EXPECT_EQ(Exiv2::LogMsg::level(), L(0));
}

TEST_F(LogMsgTest_718, SetHandlerAndHandlerGetterRoundTrip_718) {
  // Set a handler (trampoline) and verify handler() reflects it.
  Exiv2::LogMsg::setHandler(&HandlerTrampoline);
  EXPECT_THAT(Exiv2::LogMsg::handler(), NotNull());

  // Set back to nullptr (if supported) and observe it via handler().
  Exiv2::LogMsg::setHandler(nullptr);
  EXPECT_EQ(Exiv2::LogMsg::handler(), nullptr);
}

TEST_F(LogMsgTest_718, DestructorDoesNotCallHandlerWhenHandlerIsNull_718) {
  MockLogHandler mock;
  g_mock_handler = &mock;

  Exiv2::LogMsg::setLevel(L(0));
  Exiv2::LogMsg::setHandler(nullptr);

  EXPECT_CALL(mock, Call(_, _)).Times(0);

  {
    Exiv2::LogMsg msg(L(10));
    msg.os() << "hello";
  }
}

TEST_F(LogMsgTest_718, DestructorDoesNotCallHandlerWhenMsgTypeBelowLevel_718) {
  MockLogHandler mock;
  g_mock_handler = &mock;

  Exiv2::LogMsg::setHandler(&HandlerTrampoline);
  Exiv2::LogMsg::setLevel(L(5));

  EXPECT_CALL(mock, Call(_, _)).Times(0);

  {
    Exiv2::LogMsg msg(L(4));  // below current level
    msg.os() << "should not be logged";
  }
}

TEST_F(LogMsgTest_718, DestructorCallsHandlerWhenMsgTypeEqualsLevel_718) {
  MockLogHandler mock;
  g_mock_handler = &mock;

  Exiv2::LogMsg::setHandler(&HandlerTrampoline);
  Exiv2::LogMsg::setLevel(L(2));

  const std::string payload = "exact-level message";
  EXPECT_CALL(mock, Call(Eq(2), StrEq(payload.c_str()))).Times(1);

  {
    Exiv2::LogMsg msg(L(2));
    msg.os() << payload;
  }
}

TEST_F(LogMsgTest_718, DestructorCallsHandlerWhenMsgTypeAboveLevel_718) {
  MockLogHandler mock;
  g_mock_handler = &mock;

  Exiv2::LogMsg::setHandler(&HandlerTrampoline);
  Exiv2::LogMsg::setLevel(L(1));

  const std::string payload = "above-level message";
  EXPECT_CALL(mock, Call(Eq(3), StrEq(payload.c_str()))).Times(1);

  {
    Exiv2::LogMsg msg(L(3));
    msg.os() << payload;
  }
}

TEST_F(LogMsgTest_718, DestructorPassesEmptyStringWhenNoStreamOutput_718) {
  MockLogHandler mock;
  g_mock_handler = &mock;

  Exiv2::LogMsg::setHandler(&HandlerTrampoline);
  Exiv2::LogMsg::setLevel(L(0));

  EXPECT_CALL(mock, Call(Eq(0), StrEq(""))).Times(1);

  {
    Exiv2::LogMsg msg(L(0));
    // No writes to msg.os()
  }
}

TEST_F(LogMsgTest_718, StreamOutputIsConcatenatedInOrder_718) {
  MockLogHandler mock;
  g_mock_handler = &mock;

  Exiv2::LogMsg::setHandler(&HandlerTrampoline);
  Exiv2::LogMsg::setLevel(L(0));

  const std::string expected = std::string("a") + " " + "b" + " " + "123";
  EXPECT_CALL(mock, Call(Eq(0), StrEq(expected.c_str()))).Times(1);

  {
    Exiv2::LogMsg msg(L(0));
    msg.os() << "a";
    msg.os() << " ";
    msg.os() << "b";
    msg.os() << " ";
    msg.os() << 123;
  }
}

TEST_F(LogMsgTest_718, MultipleLogMsgInstancesEachTriggerTheirOwnDestructorCall_718) {
  MockLogHandler mock;
  g_mock_handler = &mock;

  Exiv2::LogMsg::setHandler(&HandlerTrampoline);
  Exiv2::LogMsg::setLevel(L(0));

  EXPECT_CALL(mock, Call(Eq(1), StrEq("first"))).Times(1);
  EXPECT_CALL(mock, Call(Eq(2), StrEq("second"))).Times(1);

  {
    Exiv2::LogMsg a(L(1));
    a.os() << "first";
  }
  {
    Exiv2::LogMsg b(L(2));
    b.os() << "second";
  }
}

}  // namespace