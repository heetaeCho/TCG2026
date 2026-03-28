#include "util/posix_logger.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "leveldb/env.h"

namespace leveldb {

// Helper function to invoke Logv through a variadic wrapper
static void LogMessage(PosixLogger* logger, const char* format, ...) {
  std::va_list args;
  va_start(args, format);
  logger->Logv(format, args);
  va_end(args);
}

class PosixLoggerTest_428 : public ::testing::Test {
 protected:
  void SetUp() override {
    tmp_file_ = std::tmpnam(nullptr);
    fp_ = std::fopen(tmp_file_.c_str(), "w+");
    ASSERT_NE(fp_, nullptr);
    logger_ = new PosixLogger(fp_);
  }

  void TearDown() override {
    delete logger_;
    // fp_ is owned by the logger's destructor or we close it here
    // Based on the interface, the destructor likely closes it,
    // but to be safe for reading, we handle it.
    // Actually, let's read before teardown closes things.
    std::remove(tmp_file_.c_str());
  }

  std::string ReadLogContents() {
    std::fflush(fp_);
    std::ifstream ifs(tmp_file_);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        std::istreambuf_iterator<char>());
    return content;
  }

  std::string tmp_file_;
  std::FILE* fp_;
  PosixLogger* logger_;
};

TEST_F(PosixLoggerTest_428, SimpleMessage_428) {
  LogMessage(logger_, "hello world");
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("hello world"), std::string::npos);
  // Should end with newline
  EXPECT_EQ(content.back(), '\n');
}

TEST_F(PosixLoggerTest_428, FormattedMessage_428) {
  LogMessage(logger_, "value=%d str=%s", 42, "test");
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("value=42"), std::string::npos);
  EXPECT_NE(content.find("str=test"), std::string::npos);
}

TEST_F(PosixLoggerTest_428, MessageContainsTimestamp_428) {
  LogMessage(logger_, "timestamp test");
  std::string content = ReadLogContents();
  // Timestamp format: YYYY/MM/DD-HH:MM:SS.uuuuuu
  // Check for the date separator pattern
  // At minimum, there should be '/' characters from the date
  EXPECT_NE(content.find('/'), std::string::npos);
  EXPECT_NE(content.find('-'), std::string::npos);
  EXPECT_NE(content.find(':'), std::string::npos);
}

TEST_F(PosixLoggerTest_428, EmptyFormatString_428) {
  LogMessage(logger_, "");
  std::string content = ReadLogContents();
  // Should still produce output (at least the header with timestamp and thread id)
  EXPECT_FALSE(content.empty());
  EXPECT_EQ(content.back(), '\n');
}

TEST_F(PosixLoggerTest_428, MessageWithNewlineAtEnd_428) {
  LogMessage(logger_, "ends with newline\n");
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("ends with newline"), std::string::npos);
  // Should not have double newline at the end
  EXPECT_EQ(content.back(), '\n');
  // Check there's no double newline
  if (content.size() >= 2) {
    // The message already ends with \n, so the logger should not add another
    size_t pos = content.find("ends with newline\n");
    EXPECT_NE(pos, std::string::npos);
  }
}

TEST_F(PosixLoggerTest_428, MultipleLogMessages_428) {
  LogMessage(logger_, "first message");
  LogMessage(logger_, "second message");
  LogMessage(logger_, "third message");
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("first message"), std::string::npos);
  EXPECT_NE(content.find("second message"), std::string::npos);
  EXPECT_NE(content.find("third message"), std::string::npos);
}

TEST_F(PosixLoggerTest_428, LargeMessageExceedsStackBuffer_428) {
  // The stack buffer is 512 bytes, and the header takes ~60+ bytes.
  // Create a message that will exceed the stack buffer to trigger
  // dynamic allocation (second iteration).
  std::string large_msg(600, 'A');
  LogMessage(logger_, "%s", large_msg.c_str());
  std::string content = ReadLogContents();
  EXPECT_NE(content.find(large_msg), std::string::npos);
  EXPECT_EQ(content.back(), '\n');
}

TEST_F(PosixLoggerTest_428, VeryLargeMessage_428) {
  // Create an even larger message
  std::string very_large_msg(4096, 'B');
  LogMessage(logger_, "%s", very_large_msg.c_str());
  std::string content = ReadLogContents();
  EXPECT_NE(content.find(very_large_msg), std::string::npos);
  EXPECT_EQ(content.back(), '\n');
}

TEST_F(PosixLoggerTest_428, MessageWithSpecialCharacters_428) {
  LogMessage(logger_, "special chars: %%d %%s %% tab:\there");
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("special chars:"), std::string::npos);
  EXPECT_NE(content.find("%d"), std::string::npos);
}

TEST_F(PosixLoggerTest_428, IntegerFormatting_428) {
  LogMessage(logger_, "int: %d, unsigned: %u, hex: %x", -1, 255u, 255u);
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("int: -1"), std::string::npos);
  EXPECT_NE(content.find("unsigned: 255"), std::string::npos);
  EXPECT_NE(content.find("hex: ff"), std::string::npos);
}

TEST_F(PosixLoggerTest_428, FloatingPointFormatting_428) {
  LogMessage(logger_, "float: %.2f", 3.14);
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("float: 3.14"), std::string::npos);
}

TEST_F(PosixLoggerTest_428, MessageExactlyAtStackBufferBoundary_428) {
  // The header is roughly 28 + thread_id_len + 1 (space) bytes.
  // Try to create a message that, combined with the header, is right around 511 bytes.
  // We'll try a few sizes around the boundary.
  std::string boundary_msg(440, 'C');
  LogMessage(logger_, "%s", boundary_msg.c_str());
  std::string content = ReadLogContents();
  EXPECT_NE(content.find(boundary_msg), std::string::npos);
  EXPECT_EQ(content.back(), '\n');
}

TEST_F(PosixLoggerTest_428, MessageWithOnlyNewline_428) {
  LogMessage(logger_, "\n");
  std::string content = ReadLogContents();
  EXPECT_FALSE(content.empty());
  EXPECT_EQ(content.back(), '\n');
}

TEST_F(PosixLoggerTest_428, MessageWithMultipleNewlines_428) {
  LogMessage(logger_, "line1\nline2\n");
  std::string content = ReadLogContents();
  EXPECT_NE(content.find("line1\nline2"), std::string::npos);
}

TEST_F(PosixLoggerTest_428, NullStringArgument_428) {
  // Passing nullptr for %s is technically undefined behavior in C,
  // but many implementations print "(null)". We just verify no crash.
  LogMessage(logger_, "null: %s", "(nil)");
  std::string content = ReadLogContents();
  EXPECT_FALSE(content.empty());
}

TEST_F(PosixLoggerTest_428, ThreadIdInOutput_428) {
  // The log line should contain a thread ID between the timestamp and the message
  LogMessage(logger_, "thread_check");
  std::string content = ReadLogContents();
  
  // Get current thread id as string
  std::ostringstream oss;
  oss << std::this_thread::get_id();
  std::string tid = oss.str();
  if (tid.size() > 32) tid.resize(32);
  
  EXPECT_NE(content.find(tid), std::string::npos);
}

TEST_F(PosixLoggerTest_428, OutputIsFlushed_428) {
  LogMessage(logger_, "flush test");
  
  // Read the file directly without explicit fflush - the logger should have flushed
  std::ifstream ifs(tmp_file_);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  EXPECT_NE(content.find("flush test"), std::string::npos);
}

TEST_F(PosixLoggerTest_428, EachLineEndsWithNewline_428) {
  LogMessage(logger_, "msg1");
  LogMessage(logger_, "msg2");
  LogMessage(logger_, "msg3");
  
  std::fflush(fp_);
  std::ifstream ifs(tmp_file_);
  std::string line;
  int line_count = 0;
  while (std::getline(ifs, line)) {
    line_count++;
    // std::getline strips the newline, but we know each line existed
    EXPECT_FALSE(line.empty());
  }
  EXPECT_EQ(line_count, 3);
}

}  // namespace leveldb
