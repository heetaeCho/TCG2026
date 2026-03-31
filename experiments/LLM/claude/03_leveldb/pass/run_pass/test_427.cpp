#include <cstdio>
#include <cstring>
#include <string>
#include <cstdarg>

#include "gtest/gtest.h"
#include "leveldb/env.h"
#include "util/posix_logger.h"

namespace leveldb {

class PosixLoggerTest_427 : public ::testing::Test {
 protected:
  std::string tmp_file_path_;
  std::FILE* fp_ = nullptr;
  PosixLogger* logger_ = nullptr;

  void SetUp() override {
    tmp_file_path_ = std::tmpnam(nullptr);
    fp_ = std::fopen(tmp_file_path_.c_str(), "w+");
    ASSERT_NE(fp_, nullptr);
    logger_ = new PosixLogger(fp_);
  }

  void TearDown() override {
    delete logger_;
    logger_ = nullptr;
    fp_ = nullptr;  // closed by ~PosixLogger
    std::remove(tmp_file_path_.c_str());
  }

  std::string ReadLogFile() {
    // Flush before reading
    std::FILE* read_fp = std::fopen(tmp_file_path_.c_str(), "r");
    if (!read_fp) return "";
    std::string content;
    char buf[1024];
    while (std::fgets(buf, sizeof(buf), read_fp)) {
      content += buf;
    }
    std::fclose(read_fp);
    return content;
  }

  // Helper to invoke Logv through Logger::Log (variadic wrapper)
  void LogMessage(Logger* logger, const char* format, ...) {
    std::va_list args;
    va_start(args, format);
    logger->Logv(format, args);
    va_end(args);
  }
};

TEST_F(PosixLoggerTest_427, BasicLogMessage_427) {
  LogMessage(logger_, "hello %s", "world");
  std::string content = ReadLogFile();
  EXPECT_NE(content.find("hello world"), std::string::npos);
}

TEST_F(PosixLoggerTest_427, LogMultipleMessages_427) {
  LogMessage(logger_, "message %d", 1);
  LogMessage(logger_, "message %d", 2);
  LogMessage(logger_, "message %d", 3);
  std::string content = ReadLogFile();
  EXPECT_NE(content.find("message 1"), std::string::npos);
  EXPECT_NE(content.find("message 2"), std::string::npos);
  EXPECT_NE(content.find("message 3"), std::string::npos);
}

TEST_F(PosixLoggerTest_427, LogEmptyString_427) {
  LogMessage(logger_, "");
  std::string content = ReadLogFile();
  // Should not crash; content may contain timestamp/header but empty message body
  // Just verifying it doesn't crash
  SUCCEED();
}

TEST_F(PosixLoggerTest_427, LogIntegerFormatting_427) {
  LogMessage(logger_, "count=%d", 42);
  std::string content = ReadLogFile();
  EXPECT_NE(content.find("count=42"), std::string::npos);
}

TEST_F(PosixLoggerTest_427, LogFloatFormatting_427) {
  LogMessage(logger_, "value=%.2f", 3.14);
  std::string content = ReadLogFile();
  EXPECT_NE(content.find("value=3.14"), std::string::npos);
}

TEST_F(PosixLoggerTest_427, LogLongMessage_427) {
  // Test with a message longer than typical buffer sizes
  std::string long_msg(10000, 'A');
  LogMessage(logger_, "%s", long_msg.c_str());
  std::string content = ReadLogFile();
  // At least some portion of the long message should appear
  EXPECT_NE(content.find("AAAA"), std::string::npos);
}

TEST_F(PosixLoggerTest_427, LogContainsNewline_427) {
  LogMessage(logger_, "test line");
  std::string content = ReadLogFile();
  // Log entries typically end with a newline
  EXPECT_NE(content.find('\n'), std::string::npos);
}

TEST_F(PosixLoggerTest_427, LogContainsTimestampInfo_427) {
  LogMessage(logger_, "timestamped message");
  std::string content = ReadLogFile();
  // PosixLogger typically prepends date/time information
  // The content should be longer than just the message itself
  EXPECT_GT(content.size(), strlen("timestamped message"));
}

TEST_F(PosixLoggerTest_427, LogSpecialCharacters_427) {
  LogMessage(logger_, "special: %%percent %s", "tab\there");
  std::string content = ReadLogFile();
  EXPECT_NE(content.find("%percent"), std::string::npos);
}

TEST_F(PosixLoggerTest_427, DestructorClosesFile_427) {
  // Create a separate logger and destroy it, then verify file is closed
  std::string path = std::tmpnam(nullptr);
  std::FILE* fp = std::fopen(path.c_str(), "w");
  ASSERT_NE(fp, nullptr);
  {
    PosixLogger temp_logger(fp);
    // Logger goes out of scope here, should close fp
  }
  // After destruction, the file should have been closed.
  // We can verify indirectly that no crash occurs and file exists.
  std::FILE* verify = std::fopen(path.c_str(), "r");
  EXPECT_NE(verify, nullptr);
  if (verify) std::fclose(verify);
  std::remove(path.c_str());
}

TEST_F(PosixLoggerTest_427, LogNoFormatArgs_427) {
  LogMessage(logger_, "no format args here");
  std::string content = ReadLogFile();
  EXPECT_NE(content.find("no format args here"), std::string::npos);
}

TEST_F(PosixLoggerTest_427, LogMultipleFormats_427) {
  LogMessage(logger_, "%s %d %f %c", "test", 123, 4.56, 'X');
  std::string content = ReadLogFile();
  EXPECT_NE(content.find("test"), std::string::npos);
  EXPECT_NE(content.find("123"), std::string::npos);
}

}  // namespace leveldb
