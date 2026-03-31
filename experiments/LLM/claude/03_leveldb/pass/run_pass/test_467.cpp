#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/env.h"

#include <cstdarg>
#include <string>

namespace leveldb {

// Mock Logger to observe calls to Logv
class MockLogger : public Logger {
 public:
  MockLogger() = default;
  ~MockLogger() override = default;

  // We capture the format string and use a helper to extract the formatted result
  MOCK_METHOD(void, Logv, (const char* format, std::va_list ap), (override));
};

// Test fixture
class LogTest_467 : public ::testing::Test {
 protected:
  MockLogger mock_logger_;
};

// Test that Log does nothing when info_log is nullptr (no crash, no call)
TEST_F(LogTest_467, NullLoggerDoesNotCrash_467) {
  // Should not crash or call anything
  Log(nullptr, "test message %d", 42);
  // If we get here without crashing, the test passes
}

// Test that Log calls Logv on a valid logger with the correct format string
TEST_F(LogTest_467, ValidLoggerCallsLogv_467) {
  EXPECT_CALL(mock_logger_, Logv(::testing::StrEq("hello %s"), ::testing::_))
      .Times(1);

  Log(&mock_logger_, "hello %s", "world");
}

// Test that Log calls Logv exactly once per invocation
TEST_F(LogTest_467, LogvCalledExactlyOnce_467) {
  EXPECT_CALL(mock_logger_, Logv(::testing::_, ::testing::_)).Times(1);

  Log(&mock_logger_, "single call");
}

// Test multiple calls to Log result in multiple calls to Logv
TEST_F(LogTest_467, MultipleLogCallsResultInMultipleLogvCalls_467) {
  EXPECT_CALL(mock_logger_, Logv(::testing::_, ::testing::_)).Times(3);

  Log(&mock_logger_, "first");
  Log(&mock_logger_, "second %d", 2);
  Log(&mock_logger_, "third %s %d", "msg", 3);
}

// Test that the format string is passed correctly for a simple string
TEST_F(LogTest_467, FormatStringPassedCorrectly_467) {
  EXPECT_CALL(mock_logger_, Logv(::testing::StrEq("no args here"), ::testing::_))
      .Times(1);

  Log(&mock_logger_, "no args here");
}

// Test with empty format string
TEST_F(LogTest_467, EmptyFormatString_467) {
  EXPECT_CALL(mock_logger_, Logv(::testing::StrEq(""), ::testing::_)).Times(1);

  Log(&mock_logger_, "");
}

// Test with various format specifiers to ensure format string is forwarded
TEST_F(LogTest_467, FormatWithMultipleSpecifiers_467) {
  EXPECT_CALL(mock_logger_,
              Logv(::testing::StrEq("%d %s %f %x"), ::testing::_))
      .Times(1);

  Log(&mock_logger_, "%d %s %f %x", 10, "test", 3.14, 0xff);
}

// Test that va_list arguments are properly forwarded by using a custom logger
// that actually formats the string
class FormattingLogger : public Logger {
 public:
  ~FormattingLogger() override = default;
  std::string last_message;

  void Logv(const char* format, std::va_list ap) override {
    char buf[512];
    std::vsnprintf(buf, sizeof(buf), format, ap);
    last_message = buf;
  }
};

TEST_F(LogTest_467, VariadicArgumentsAreForwardedCorrectly_467) {
  FormattingLogger logger;

  Log(&logger, "value=%d name=%s", 42, "test");
  EXPECT_EQ(logger.last_message, "value=42 name=test");
}

TEST_F(LogTest_467, VariadicWithNoExtraArgs_467) {
  FormattingLogger logger;

  Log(&logger, "plain message");
  EXPECT_EQ(logger.last_message, "plain message");
}

TEST_F(LogTest_467, VariadicWithIntegerArg_467) {
  FormattingLogger logger;

  Log(&logger, "count: %d", 100);
  EXPECT_EQ(logger.last_message, "count: 100");
}

TEST_F(LogTest_467, VariadicWithFloatingPointArg_467) {
  FormattingLogger logger;

  Log(&logger, "pi=%.2f", 3.14);
  EXPECT_EQ(logger.last_message, "pi=3.14");
}

// Test interleaving null and non-null logger calls
TEST_F(LogTest_467, InterleavedNullAndValidLogger_467) {
  EXPECT_CALL(mock_logger_, Logv(::testing::_, ::testing::_)).Times(2);

  Log(&mock_logger_, "first call");
  Log(nullptr, "this should be ignored");
  Log(&mock_logger_, "third call");
  Log(nullptr, "also ignored");
}

}  // namespace leveldb
