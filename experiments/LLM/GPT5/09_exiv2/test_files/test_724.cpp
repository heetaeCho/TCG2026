// File: test_error_default_handler_724.cpp
// TEST_ID: 724

#include <gtest/gtest.h>

#include <exiv2/error.hpp>

#include <string>

namespace {

class LogMsgDefaultHandlerTest_724 : public ::testing::Test {
 protected:
  // Call Exiv2::LogMsg::defaultHandler as either a static or (fallback) instance method,
  // without depending on private state or re-implementing behavior.
  template <typename T>
  static auto CallDefaultHandlerImpl(int level, const char* s, int)
      -> decltype(T::defaultHandler(level, s), void()) {
    T::defaultHandler(level, s);
  }

  template <typename T>
  static void CallDefaultHandlerImpl(int level, const char* s, long) {
    // Fallback if defaultHandler is not static in some build configurations.
    T msg(Exiv2::LogMsg::debug);
    msg.defaultHandler(level, s);
  }

  static void CallDefaultHandler(int level, const char* s) {
    CallDefaultHandlerImpl<Exiv2::LogMsg>(level, s, 0);
  }
};

TEST_F(LogMsgDefaultHandlerTest_724, DebugLevelPrintsDebugPrefixAndMessage_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(static_cast<int>(Exiv2::LogMsg::debug), "hello");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "Debug: hello");
}

TEST_F(LogMsgDefaultHandlerTest_724, InfoLevelPrintsInfoPrefixAndMessage_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(static_cast<int>(Exiv2::LogMsg::info), "hello");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "Info: hello");
}

TEST_F(LogMsgDefaultHandlerTest_724, WarnLevelPrintsWarningPrefixAndMessage_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(static_cast<int>(Exiv2::LogMsg::warn), "hello");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "Warning: hello");
}

TEST_F(LogMsgDefaultHandlerTest_724, ErrorLevelPrintsErrorPrefixAndMessage_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(static_cast<int>(Exiv2::LogMsg::error), "hello");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "Error: hello");
}

TEST_F(LogMsgDefaultHandlerTest_724, UnknownLevelPrintsMessageWithoutPrefix_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(999, "hello");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "hello");
}

TEST_F(LogMsgDefaultHandlerTest_724, NegativeLevelPrintsMessageWithoutPrefix_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(-1, "hello");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "hello");
}

TEST_F(LogMsgDefaultHandlerTest_724, EmptyMessageStillPrintsPrefixForKnownLevel_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(static_cast<int>(Exiv2::LogMsg::debug), "");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "Debug: ");
}

TEST_F(LogMsgDefaultHandlerTest_724, MultipleCallsAppendToStderrInOrder_724) {
  testing::internal::CaptureStderr();
  CallDefaultHandler(static_cast<int>(Exiv2::LogMsg::info), "A");
  CallDefaultHandler(static_cast<int>(Exiv2::LogMsg::warn), "B");
  const std::string out = testing::internal::GetCapturedStderr();
  EXPECT_EQ(out, "Info: AWarning: B");
}

}  // namespace