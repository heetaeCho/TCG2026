// File: read_count_test_147.cc

#include <gtest/gtest.h>

#include <cstdint>
#include <cstdio>      // std::remove
#include <fstream>
#include <limits>
#include <string>
#include <utility>

// Forward declaration of the function under test.
// In your real code, prefer including the proper header instead.
std::pair<int64_t, bool> readCount(const std::string& path);

class ReadCountTest_147 : public ::testing::Test {
 protected:
  // Helper to create a file with given content.
  // Returns the same path for convenience.
  std::string CreateFileWithContent(const std::string& path,
                                    const std::string& content) {
    std::ofstream out(path.c_str());
    out << content;
    // out will be closed when it goes out of scope.
    return path;
  }

  void RemoveFileIfExists(const std::string& path) {
    std::remove(path.c_str());
  }
};

TEST_F(ReadCountTest_147, NonExistingFileReturnsZeroAndFalse_147) {
  // Use a path in a non-existent directory to avoid accidental collisions.
  const std::string path = "no_such_dir_147/non_existing_file_147.txt";

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(0, result.first);
  EXPECT_FALSE(result.second);
}

TEST_F(ReadCountTest_147, ValidIntegerReturnsValueAndTrue_147) {
  const std::string path = "readcount_valid_147.txt";
  CreateFileWithContent(path, "12345");

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(12345, result.first);
  EXPECT_TRUE(result.second);

  RemoveFileIfExists(path);
}

TEST_F(ReadCountTest_147, EmptyFileReturnsZeroAndFalse_147) {
  const std::string path = "readcount_empty_147.txt";
  // Create an empty file.
  CreateFileWithContent(path, "");

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(0, result.first);
  EXPECT_FALSE(result.second);

  RemoveFileIfExists(path);
}

TEST_F(ReadCountTest_147, WhitespaceOnlyFileReturnsZeroAndFalse_147) {
  const std::string path = "readcount_whitespace_147.txt";
  CreateFileWithContent(path, "   \n\t  ");

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(0, result.first);
  EXPECT_FALSE(result.second);

  RemoveFileIfExists(path);
}

TEST_F(ReadCountTest_147, NonNumericContentReturnsZeroAndFalse_147) {
  const std::string path = "readcount_nonnumeric_147.txt";
  CreateFileWithContent(path, "abc def");

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(0, result.first);
  EXPECT_FALSE(result.second);

  RemoveFileIfExists(path);
}

TEST_F(ReadCountTest_147, NumberWithWhitespaceAndExtraTextReturnsNumberAndTrue_147) {
  const std::string path = "readcount_extra_147.txt";
  // Leading whitespace, integer, trailing whitespace and extra text.
  CreateFileWithContent(path, "   42   extra text");

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(42, result.first);
  EXPECT_TRUE(result.second);

  RemoveFileIfExists(path);
}

TEST_F(ReadCountTest_147, NegativeIntegerReturnsValueAndTrue_147) {
  const std::string path = "readcount_negative_147.txt";
  CreateFileWithContent(path, "-77");

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(-77, result.first);
  EXPECT_TRUE(result.second);

  RemoveFileIfExists(path);
}

TEST_F(ReadCountTest_147, MaxInt64ValueReturnsValueAndTrue_147) {
  const std::string path = "readcount_maxint64_147.txt";

  {
    std::ofstream out(path.c_str());
    out << std::numeric_limits<int64_t>::max();
  }

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(std::numeric_limits<int64_t>::max(), result.first);
  EXPECT_TRUE(result.second);

  RemoveFileIfExists(path);
}

TEST_F(ReadCountTest_147, MinInt64ValueReturnsValueAndTrue_147) {
  const std::string path = "readcount_minint64_147.txt";

  {
    std::ofstream out(path.c_str());
    out << std::numeric_limits<int64_t>::min();
  }

  std::pair<int64_t, bool> result = readCount(path);

  EXPECT_EQ(std::numeric_limits<int64_t>::min(), result.first);
  EXPECT_TRUE(result.second);

  RemoveFileIfExists(path);
}
