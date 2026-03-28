// windows_logger_test.cc
#include "util/windows_logger.h"

#include <gtest/gtest.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

// Small helper to call Logv with a va_list, without re-implementing internals.
static void CallLogv(WindowsLogger* logger, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  logger->Logv(fmt, ap);
  va_end(ap);
}

static std::string ReadAllFrom(FILE* fp) {
  std::fflush(fp);
  std::fseek(fp, 0, SEEK_SET);
  std::string out;
  char buf[4096];
  size_t n;
  while ((n = std::fread(buf, 1, sizeof(buf), fp)) > 0) {
    out.append(buf, n);
  }
  return out;
}

class WindowsLoggerTest_453 : public ::testing::Test {
 protected:
  void SetUp() override {
#if defined(_WIN32) || defined(_WIN64)
    fp_ = std::tmpfile();  // temporary file; auto-deleted on close
#else
    // The implementation targets Windows; tests still use std::tmpfile for I/O.
    fp_ = std::tmpfile();
#endif
    ASSERT_NE(fp_, nullptr);
    logger_ = std::make_unique<WindowsLogger>(fp_);
  }

  void TearDown() override {
    if (fp_ != nullptr) std::fclose(fp_);
  }

  FILE* fp_{nullptr};
  std::unique_ptr<WindowsLogger> logger_;
};

// Normal operation: writes formatted message and ensures exactly one trailing newline.
TEST_F(WindowsLoggerTest_453, BasicMessageAppendsNewline_453) {
  const char* msg = "hello world";
  CallLogv(logger_.get(), "%s", msg);

  const std::string content = ReadAllFrom(fp_);
  // The output has a timestamp/thread header we don't assert on; we just check observable tail.
  // Must contain our message:
  ASSERT_NE(content.find("hello world"), std::string::npos);
  // Must end with a single newline character:
  ASSERT_FALSE(content.empty());
  EXPECT_EQ(content.back(), '\n');
}

// Respect existing newline: do not append an extra newline when format already ends with '\n'.
TEST_F(WindowsLoggerTest_453, RespectsExistingNewline_453) {
  CallLogv(logger_.get(), "%s", "line-with-nl\n");
  const std::string content = ReadAllFrom(fp_);

  // Contains the message including its newline
  ASSERT_NE(content.find("line-with-nl\n"), std::string::npos);
  // Should not create a double newline sequence right after the message text.
  EXPECT_EQ(content.find("line-with-nl\n\n"), std::string::npos);
  // Still ends with a newline overall.
  ASSERT_FALSE(content.empty());
  EXPECT_EQ(content.back(), '\n');
}

// Formatting behavior: supports printf-style formatting with integers/strings/floats.
TEST_F(WindowsLoggerTest_453, FormatsPrintfStyle_453) {
  CallLogv(logger_.get(), "id=%d status=%s pi=%.2f", 42, "ok", 3.14159);
  const std::string content = ReadAllFrom(fp_);

  // We verify the formatted substring appears as-is.
  ASSERT_NE(content.find("id=42 status=ok pi=3.14"), std::string::npos);
  EXPECT_EQ(content.back(), '\n');
}

// Large message triggers dynamic buffer path but still writes the full message and newline.
TEST_F(WindowsLoggerTest_453, VeryLongMessageHandled_453) {
  // Construct a message substantially larger than the stack buffer (512) plus header.
  const size_t kLen = 4000;  // comfortably large
  std::string big(kLen, 'A');

  CallLogv(logger_.get(), "%s", big.c_str());

  const std::string content = ReadAllFrom(fp_);
  // Contains a lengthy contiguous 'A' block:
  // Check a representative long slice is present to avoid scanning the full string cost.
  std::string probe(1000, 'A');
  ASSERT_NE(content.find(probe), std::string::npos);
  // Ends with exactly one newline:
  ASSERT_FALSE(content.empty());
  EXPECT_EQ(content.back(), '\n');
}

// Multiple calls: writes separate lines, in order, and flushes between calls so reads see both.
TEST_F(WindowsLoggerTest_453, MultipleWritesAreFlushedAndOrdered_453) {
  CallLogv(logger_.get(), "first %d", 1);
  CallLogv(logger_.get(), "second %d", 2);

  const std::string content = ReadAllFrom(fp_);

  // Both messages appear:
  const auto pos1 = content.find("first 1");
  const auto pos2 = content.find("second 2");
  ASSERT_NE(pos1, std::string::npos);
  ASSERT_NE(pos2, std::string::npos);
  // In order:
  EXPECT_LT(pos1, pos2);

  // Two line endings should exist (we can approximate by counting '\n').
  const auto newline_count =
      static_cast<int>(std::count(content.begin(), content.end(), '\n'));
  EXPECT_GE(newline_count, 2);
}

}  // namespace leveldb
