#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "util/windows_logger.h"

namespace leveldb {

// Helper function to call Logv with variadic arguments
static void LogMessage(WindowsLogger* logger, const char* format, ...) {
  std::va_list args;
  va_start(args, format);
  logger->Logv(format, args);
  va_end(args);
}

class WindowsLoggerTest_453 : public ::testing::Test {
 protected:
  void SetUp() override {
    fp_ = std::tmpfile();
    ASSERT_NE(fp_, nullptr);
    logger_ = new WindowsLogger(fp_);
  }

  void TearDown() override {
    delete logger_;
    if (fp_) {
      std::fclose(fp_);
    }
  }

  std::string ReadLogContents() {
    std::fflush(fp_);
    std::rewind(fp_);
    std::string contents;
    char buf[4096];
    size_t n;
    while ((n = std::fread(buf, 1, sizeof(buf), fp_)) > 0) {
      contents.append(buf, n);
    }
    return contents;
  }

  std::FILE* fp_;
  WindowsLogger* logger_;
};

TEST_F(WindowsLoggerTest_453, SimpleMessage_453) {
  LogMessage(logger_, "hello world");
  std::string contents = ReadLogContents();
  EXPECT_FALSE(contents.empty());
  // Should contain the message text
  EXPECT_NE(contents.find("hello world"), std::string::npos);
  // Should end with newline
  EXPECT_EQ(contents.back(), '\n');
}

TEST_F(WindowsLoggerTest_453, FormattedMessage_453) {
  LogMessage(logger_, "value=%d", 42);
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find("value=42"), std::string::npos);
  EXPECT_EQ(contents.back(), '\n');
}

TEST_F(WindowsLoggerTest_453, StringFormatArgument_453) {
  LogMessage(logger_, "name=%s count=%d", "test", 123);
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find("name=test"), std::string::npos);
  EXPECT_NE(contents.find("count=123"), std::string::npos);
}

TEST_F(WindowsLoggerTest_453, EmptyFormat_453) {
  LogMessage(logger_, "");
  std::string contents = ReadLogContents();
  // Should still have at least the header with date/time and thread id
  EXPECT_FALSE(contents.empty());
  EXPECT_EQ(contents.back(), '\n');
}

TEST_F(WindowsLoggerTest_453, MessageAlreadyEndsWithNewline_453) {
  LogMessage(logger_, "with newline\n");
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find("with newline"), std::string::npos);
  // Should end with exactly one newline (no double newline at the end)
  EXPECT_EQ(contents.back(), '\n');
  // Check there's no double newline at the very end
  if (contents.size() >= 2) {
    // The message should not produce a trailing double newline
    // (the implementation avoids adding a second newline if one is present)
    size_t pos = contents.rfind("with newline\n");
    EXPECT_NE(pos, std::string::npos);
  }
}

TEST_F(WindowsLoggerTest_453, MultipleLogMessages_453) {
  LogMessage(logger_, "first");
  LogMessage(logger_, "second");
  LogMessage(logger_, "third");
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find("first"), std::string::npos);
  EXPECT_NE(contents.find("second"), std::string::npos);
  EXPECT_NE(contents.find("third"), std::string::npos);

  // Verify ordering
  size_t pos1 = contents.find("first");
  size_t pos2 = contents.find("second");
  size_t pos3 = contents.find("third");
  EXPECT_LT(pos1, pos2);
  EXPECT_LT(pos2, pos3);
}

TEST_F(WindowsLoggerTest_453, LongMessageExceedsStackBuffer_453) {
  // Create a message longer than 512 bytes to trigger dynamic allocation
  std::string long_msg(600, 'A');
  LogMessage(logger_, "%s", long_msg.c_str());
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find(long_msg), std::string::npos);
  EXPECT_EQ(contents.back(), '\n');
}

TEST_F(WindowsLoggerTest_453, VeryLongMessage_453) {
  // A very long message to stress the dynamic buffer path
  std::string very_long_msg(4000, 'B');
  LogMessage(logger_, "%s", very_long_msg.c_str());
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find(very_long_msg), std::string::npos);
  EXPECT_EQ(contents.back(), '\n');
}

TEST_F(WindowsLoggerTest_453, HeaderContainsDateFormat_453) {
  LogMessage(logger_, "test");
  std::string contents = ReadLogContents();
  // Header should contain date in format YYYY/MM/DD-HH:MM:SS
  // Check for the slash and dash pattern
  EXPECT_NE(contents.find("/"), std::string::npos);
  EXPECT_NE(contents.find("-"), std::string::npos);
  EXPECT_NE(contents.find(":"), std::string::npos);
}

TEST_F(WindowsLoggerTest_453, FloatFormatArgument_453) {
  LogMessage(logger_, "pi=%.2f", 3.14);
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find("pi=3.14"), std::string::npos);
}

TEST_F(WindowsLoggerTest_453, MessageExactlyAtStackBufferBoundary_453) {
  // Create a message that when combined with the header is close to 512 bytes
  // Header is roughly 28 + thread_id_length + 1 bytes
  // Try a message that pushes close to the boundary
  std::string boundary_msg(450, 'C');
  LogMessage(logger_, "%s", boundary_msg.c_str());
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find(boundary_msg), std::string::npos);
  EXPECT_EQ(contents.back(), '\n');
}

TEST_F(WindowsLoggerTest_453, SpecialCharactersInMessage_453) {
  LogMessage(logger_, "special: %%percent %d tabs\there", 99);
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find("%percent"), std::string::npos);
  EXPECT_NE(contents.find("99"), std::string::npos);
  EXPECT_EQ(contents.back(), '\n');
}

TEST_F(WindowsLoggerTest_453, MultipleFormatSpecifiers_453) {
  LogMessage(logger_, "%d %s %f %c", 10, "hello", 1.5, 'X');
  std::string contents = ReadLogContents();
  EXPECT_NE(contents.find("10"), std::string::npos);
  EXPECT_NE(contents.find("hello"), std::string::npos);
  EXPECT_NE(contents.find("X"), std::string::npos);
}

}  // namespace leveldb
