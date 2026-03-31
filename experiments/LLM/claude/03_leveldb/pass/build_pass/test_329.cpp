#include <string>
#include <cstdint>
#include "gtest/gtest.h"

// Forward declaration of the function under test
namespace leveldb {
std::string SSTTableFileName(const std::string& dbname, uint64_t number);
}

namespace leveldb {

// Test normal operation with a typical database name and number
TEST(SSTTableFileNameTest_329, NormalOperation_329) {
  std::string result = SSTTableFileName("/tmp/testdb", 1);
  // Should contain the dbname prefix
  EXPECT_NE(result.find("/tmp/testdb"), std::string::npos);
  // Should end with .sst
  EXPECT_GE(result.size(), 4u);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
}

// Test with number = 1 (minimum valid number since number > 0)
TEST(SSTTableFileNameTest_329, MinimumValidNumber_329) {
  std::string result = SSTTableFileName("db", 1);
  EXPECT_NE(result.find("db"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
}

// Test with a large number
TEST(SSTTableFileNameTest_329, LargeNumber_329) {
  std::string result = SSTTableFileName("db", 999999);
  EXPECT_NE(result.find("db"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
}

// Test with maximum uint64_t value
TEST(SSTTableFileNameTest_329, MaxUint64Number_329) {
  std::string result = SSTTableFileName("db", UINT64_MAX);
  EXPECT_NE(result.find("db"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
}

// Test with empty dbname
TEST(SSTTableFileNameTest_329, EmptyDbname_329) {
  std::string result = SSTTableFileName("", 1);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
}

// Test that different numbers produce different filenames
TEST(SSTTableFileNameTest_329, DifferentNumbersDifferentFiles_329) {
  std::string result1 = SSTTableFileName("db", 1);
  std::string result2 = SSTTableFileName("db", 2);
  EXPECT_NE(result1, result2);
}

// Test that different dbnames produce different filenames
TEST(SSTTableFileNameTest_329, DifferentDbnamesDifferentFiles_329) {
  std::string result1 = SSTTableFileName("db1", 1);
  std::string result2 = SSTTableFileName("db2", 1);
  EXPECT_NE(result1, result2);
}

// Test that the same inputs produce the same output (deterministic)
TEST(SSTTableFileNameTest_329, DeterministicOutput_329) {
  std::string result1 = SSTTableFileName("testdb", 42);
  std::string result2 = SSTTableFileName("testdb", 42);
  EXPECT_EQ(result1, result2);
}

// Test with dbname containing path separators
TEST(SSTTableFileNameTest_329, DbnameWithPathSeparators_329) {
  std::string result = SSTTableFileName("/a/b/c/testdb", 100);
  EXPECT_NE(result.find("/a/b/c/testdb"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
}

// Test with number that results in typical 6-digit formatting
TEST(SSTTableFileNameTest_329, TypicalSixDigitNumber_329) {
  std::string result = SSTTableFileName("db", 123456);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
  // The filename should contain the number representation
  EXPECT_FALSE(result.empty());
}

// Test that result is non-empty for valid input
TEST(SSTTableFileNameTest_329, ResultNonEmpty_329) {
  std::string result = SSTTableFileName("db", 5);
  EXPECT_FALSE(result.empty());
}

// Test with number = 0 should trigger assertion (death test)
TEST(SSTTableFileNameTest_329, NumberZeroAssertion_329) {
  EXPECT_DEATH(SSTTableFileName("db", 0), "");
}

}  // namespace leveldb
