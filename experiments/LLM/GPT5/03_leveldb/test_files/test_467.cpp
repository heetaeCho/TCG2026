// File: env_log_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

#include "leveldb/env.h"  // Uses the provided Logger interface
// The function under test is in util/env.cc: leveldb::Log(Logger*, const char*, ...)

using ::testing::_;
using ::testing::StrEq;

namespace {

// A mock for the external collaborator Logger.
// Note: std::va_list is typically a typedef to the platform's va_list type (e.g., __builtin_va_list).
class MockLogger : public leveldb::Logger {
 public:
  MOCK_METHOD(void, Logv, (const char* format, std::va_list ap), (override));
};

class EnvLogTest_467 : public ::testing::Test {
 protected:
  // Helper that calls leveldb::Log with varargs in a type-safe way.
  // We use template + forwarding to keep tests tidy.
  template <typename... Args>
  void CallLog(leveldb::Logger* logger, const char* fmt, Args&&... args) {
    leveldb::Log(logger, fmt, std::forward<Args>(args)...);
  }
};

}  // namespace

// Normal operation: verifies that when a non-null logger is provided,
// Log forwards the format string and varargs to Logger::Logv.
// We validate by formatting inside the mock and checking the final string.
TEST_F(EnvLogTest_467, CallsLoggerWithFormattedArgs_467) {
  MockLogger logger;

  const char* fmt = "x=%d y=%s";
  const int x = 7;
  const char* y = "hi";

  EXPECT_CALL(logger, Logv(StrEq(fmt), _))
      .WillOnce([&](const char* format, std::va_list ap) {
        char buf[128];
        // Format using the provided va_list to ensure args were forwarded correctly.
        int n = std::vsnprintf(buf, sizeof(buf), format, ap);
        ASSERT_GE(n, 0);
        EXPECT_STREQ("x=7 y=hi", buf);
      });

  CallLog(&logger, fmt, x, y);
}

// Boundary: empty format string — should still forward to Logv
// and produce an empty formatted result.
TEST_F(EnvLogTest_467, EmptyFormatString_467) {
  MockLogger logger;

  const char* fmt = "";

  EXPECT_CALL(logger, Logv(StrEq(fmt), _))
      .WillOnce([&](const char* format, std::va_list ap) {
        char buf[8];
        int n = std::vsnprintf(buf, sizeof(buf), format, ap);
        ASSERT_GE(n, 0);
        EXPECT_STREQ("", buf);
      });

  CallLog(&logger, fmt);
}

// Boundary: percent-escape with no additional arguments.
// Ensures varargs forwarding and correct interpretation of "%%".
TEST_F(EnvLogTest_467, PercentEscapeNoArgs_467) {
  MockLogger logger;

  const char* fmt = "100%% done";

  EXPECT_CALL(logger, Logv(StrEq(fmt), _))
      .WillOnce([&](const char* format, std::va_list ap) {
        char buf[64];
        int n = std::vsnprintf(buf, sizeof(buf), format, ap);
        ASSERT_GE(n, 0);
        EXPECT_STREQ("100% done", buf);
      });

  CallLog(&logger, fmt);
}

// Boundary: very long formatted output (e.g., large %s).
// Verifies forwarding works for large inputs (no assumptions about internal buffers).
TEST_F(EnvLogTest_467, LargeFormattedMessage_467) {
  MockLogger logger;

  std::string big(2000, 'a');  // large payload
  const char* fmt = "prefix:%s:suffix";

  EXPECT_CALL(logger, Logv(StrEq(fmt), _))
      .WillOnce([&](const char* format, std::va_list ap) {
        // Use a sufficiently large buffer to capture the full formatted message.
        std::vector<char> buf(4096, '\0');
        int n = std::vsnprintf(buf.data(), buf.size(), format, ap);
        ASSERT_GT(n, 0);
        std::string expected = std::string("prefix:") + big + ":suffix";
        EXPECT_EQ(expected, std::string(buf.data()));
      });

  CallLog(&logger, fmt, big.c_str());
}

// Exceptional/edge observable case: null logger.
// Requirement is only that nothing bad happens (no call, no crash).
// As we have no collaborator, we simply ensure it executes safely.
TEST_F(EnvLogTest_467, NullLoggerNoOp_467) {
  // Should not crash or access through null.
  leveldb::Log(/*info_log=*/nullptr, "ignored %d %s", 42, "text");
  // No EXPECT_* here because there is no observable collaborator interaction.
}

