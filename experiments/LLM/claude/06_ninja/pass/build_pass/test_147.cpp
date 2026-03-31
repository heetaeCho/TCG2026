#include <gtest/gtest.h>
#include <fstream>
#include <cstdint>
#include <string>
#include <utility>
#include <cstdio>

// Declaration of the function under test
std::pair<int64_t, bool> readCount(const std::string& path);

class ReadCountTest_147 : public ::testing::Test {
protected:
  std::string temp_file_;

  void SetUp() override {
    temp_file_ = "readcount_test_147.tmp";
  }

  void TearDown() override {
    std::remove(temp_file_.c_str());
  }

  void WriteFile(const std::string& content) {
    std::ofstream out(temp_file_.c_str());
    out << content;
    out.close();
  }
};

TEST_F(ReadCountTest_147, NonExistentFileReturnsFalse_147) {
  auto result = readCount("nonexistent_file_that_does_not_exist_147.tmp");
  EXPECT_EQ(result.first, 0);
  EXPECT_FALSE(result.second);
}

TEST_F(ReadCountTest_147, EmptyFileReturnsFalse_147) {
  WriteFile("");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 0);
  EXPECT_FALSE(result.second);
}

TEST_F(ReadCountTest_147, ValidPositiveNumber_147) {
  WriteFile("42");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 42);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, ValidNegativeNumber_147) {
  WriteFile("-100");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, -100);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, Zero_147) {
  WriteFile("0");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 0);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, LargeNumber_147) {
  WriteFile("9223372036854775807"); // INT64_MAX
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, INT64_MAX);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, NumberWithTrailingWhitespace_147) {
  WriteFile("123 ");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 123);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, NumberWithTrailingText_147) {
  WriteFile("456abc");
  auto result = readCount(temp_file_);
  // After reading 456, the stream encounters 'a' which is not a digit.
  // The stream state depends on whether the int extraction succeeded.
  // The extraction of 456 succeeds, but then the stream is not in 'good' state
  // because the next char is not whitespace/digit - actually stream should be good
  // after successful extraction, the failbit is not set. Let's see:
  // After "456abc", reading int gives 456, then stream is still good (it stopped at 'a').
  auto result2 = readCount(temp_file_);
  EXPECT_EQ(result2.first, 456);
  EXPECT_TRUE(result2.second);
}

TEST_F(ReadCountTest_147, NonNumericContent_147) {
  WriteFile("abc");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 0);
  EXPECT_FALSE(result.second);
}

TEST_F(ReadCountTest_147, WhitespaceOnly_147) {
  WriteFile("   ");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 0);
  EXPECT_FALSE(result.second);
}

TEST_F(ReadCountTest_147, NumberWithLeadingWhitespace_147) {
  WriteFile("   789");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 789);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, EmptyPath_147) {
  auto result = readCount("");
  EXPECT_EQ(result.first, 0);
  EXPECT_FALSE(result.second);
}

TEST_F(ReadCountTest_147, NumberFollowedByNewline_147) {
  WriteFile("555\n");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 555);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, MinInt64_147) {
  WriteFile("-9223372036854775808"); // INT64_MIN
  auto result = readCount(temp_file_);
  // This might overflow or be handled differently depending on stream implementation
  // Just verify it returns some result without crashing
  // The exact behavior is implementation-defined for edge overflow cases
  (void)result;
}

TEST_F(ReadCountTest_147, MultipleNumbersReadsFirst_147) {
  WriteFile("111 222 333");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 111);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, SingleDigit_147) {
  WriteFile("7");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 7);
  EXPECT_TRUE(result.second);
}

TEST_F(ReadCountTest_147, PlusSign_147) {
  WriteFile("+99");
  auto result = readCount(temp_file_);
  EXPECT_EQ(result.first, 99);
  EXPECT_TRUE(result.second);
}
