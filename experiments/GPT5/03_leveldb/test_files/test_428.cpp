// File: util/posix_logger_test.cc

#include <gtest/gtest.h>
#include <cstdio>
#include <cstdarg>
#include <string>
#include <regex>
#include <vector>
#include <memory>

#include "util/posix_logger.h"

namespace leveldb {

namespace {

// Small helper that calls PosixLogger::Logv with varargs.
void Log(PosixLogger& logger, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  logger.Logv(fmt, ap);
  va_end(ap);
}

class PosixLoggerTest_428 : public ::testing::Test {
 protected:
  void SetUp() override {
    fp_ = std::tmpfile();  // temp file to observe writes
    ASSERT_NE(fp_, nullptr);
    logger_ = std::make_unique<PosixLogger>(fp_);
  }

  void TearDown() override {
    // Ensure logger_ is destroyed (and may close the FILE* internally)
    logger_.reset();
    // tmpfile() will be cleaned up automatically when closed / process exits.
  }

  // Read the entire contents currently in fp_ from the beginning.
  std::string ReadAll() {
    ASSERT_NE(fp_, nullptr);
    std::fflush(fp_);      // Logv already flushes, but make sure.
    std::fseek(fp_, 0, SEEK_SET);
    std::string out;
    char buf[4096];
    size_t n = 0;
    while ((n = std::fread(buf, 1, sizeof(buf), fp_)) > 0) {
      out.append(buf, n);
    }
    return out;
  }

  // Regex that matches the timestamp + thread header prefix.
  // Format: YYYY/MM/DD-HH:MM:SS.MICROS <thread_id> <space>
  // Thread id is streamed; treat it as 1..32 non-space chars.
  static std::regex HeaderRegex() {
    return std::regex(
        R"(^\d{4}/\d{2}/\d{2}-\d{2}:\d{2}:\d{2}\.\d{6} \S{1,32} )");
  }

  std::FILE* fp_{nullptr};
  std::unique_ptr<PosixLogger> logger_;
};

}  // namespace

// Normal operation: formatted message appears with a header and single trailing newline.
TEST_F(PosixLoggerTest_428, LogsFormattedMessageWithHeaderAndNewline_428) {
  Log(*logger_, "%s %d", "value", 42);
  const std::string s = ReadAll();

  // Starts with header pattern.
  EXPECT_TRUE(std::regex_search(s, HeaderRegex()))
      << "Log line did not start with expected header: " << s;

  // Ends with exactly one newline.
  ASSERT_FALSE(s.empty());
  EXPECT_EQ('\n', s.back());

  // Contains the formatted payload and not some other formatting.
  EXPECT_NE(std::string::npos, s.find(" value 42"))
      << "Formatted payload missing: " << s;
}

// Boundary: no newline in format -> logger appends exactly one newline.
TEST_F(PosixLoggerTest_428, AppendsNewlineIfMissing_428) {
  Log(*logger_, "hello");
  const std::string s = ReadAll();

  // Header present
  EXPECT_TRUE(std::regex_search(s, HeaderRegex()));

  // Exactly one newline at the end (no double newline).
  ASSERT_GE(s.size(), size_t{1});
  EXPECT_EQ('\n', s.back());
  EXPECT_EQ(std::string::npos, s.rfind("\n\n")) << s;

  // Payload appears as "hello" before the newline.
  EXPECT_NE(std::string::npos, s.find(" hello"));
}

// Boundary: a newline already present in the formatted message -> logger should not add another newline.
TEST_F(PosixLoggerTest_428, DoesNotDoubleNewlineIfPresent_428) {
  Log(*logger_, "hello\n");
  const std::string s = ReadAll();

  EXPECT_TRUE(std::regex_search(s, HeaderRegex()));
  ASSERT_GE(s.size(), size_t{1});
  EXPECT_EQ('\n', s.back());
  // Ensure there isn't a blank line at the end (no double newline).
  EXPECT_EQ(std::string::npos, s.rfind("\n\n")) << s;

  // Ensure the payload before the last newline is exactly "hello".
  const auto last_nl = s.rfind('\n');
  ASSERT_NE(std::string::npos, last_nl);
  // Grab substring after the header space to the last newline.
  // Just verify "hello" appears; we don't depend on exact offsets.
  EXPECT_NE(std::string::npos, s.find(" hello\n"));
}

// Stress/size boundary: very long message should be fully logged (exercises dynamic buffer path).
TEST_F(PosixLoggerTest_428, HandlesVeryLongMessagesByAllocating_428) {
  // Create a long payload (> 2000 chars) to exceed the stack buffer path.
  std::string long_msg(2000, 'A');
  Log(*logger_, "%s", long_msg.c_str());

  const std::string s = ReadAll();

  EXPECT_TRUE(std::regex_search(s, HeaderRegex()))
      << "Header missing for long message";
  // Payload is present in full.
  EXPECT_NE(std::string::npos, s.find(" " + long_msg))
      << "Long payload not fully present (may indicate truncation)";
  // Exactly one newline at end.
  ASSERT_FALSE(s.empty());
  EXPECT_EQ('\n', s.back());
}

// Interaction/ordering: multiple calls should append sequential lines, each with its own header.
TEST_F(PosixLoggerTest_428, MultipleCallsAppendInOrder_428) {
  Log(*logger_, "first");
  Log(*logger_, "second %d", 7);

  const std::string s = ReadAll();

  // Expect two lines; match two headers.
  std::sregex_iterator it(s.begin(), s.end(), HeaderRegex());
  std::sregex_iterator end;
  std::vector<std::ptrdiff_t> header_positions;
  for (; it != end; ++it) header_positions.push_back(it->position());
  ASSERT_EQ(2u, header_positions.size()) << "Expected two log headers/lines:\n" << s;

  // Order: "first" appears before "second 7".
  const auto pos_first  = s.find(" first");
  const auto pos_second = s.find(" second 7");
  ASSERT_NE(std::string::npos, pos_first);
  ASSERT_NE(std::string::npos, pos_second);
  EXPECT_LT(pos_first, pos_second);
}

}  // namespace leveldb
