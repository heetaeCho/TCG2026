#include "gtest/gtest.h"
#include <string>
#include <cstdint>

// Forward declaration of the function under test
namespace leveldb {
std::string LogFileName(const std::string& dbname, uint64_t number);
}

// Test normal operation with a simple database name and number
TEST(LogFileNameTest_327, BasicFunctionality_327) {
  std::string result = leveldb::LogFileName("/tmp/testdb", 1);
  // The result should contain the dbname as a prefix
  EXPECT_NE(result.find("/tmp/testdb"), std::string::npos);
  // The result should end with ".log"
  EXPECT_GE(result.size(), 4u);
  EXPECT_EQ(result.substr(result.size() - 4), ".log");
}

// Test with a larger number
TEST(LogFileNameTest_327, LargerNumber_327) {
  std::string result = leveldb::LogFileName("/tmp/testdb", 123456);
  EXPECT_NE(result.find("/tmp/testdb"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 4), ".log");
  // Should contain the number somewhere in the filename
  EXPECT_NE(result.find("123456"), std::string::npos);
}

// Test with number = 1 (smallest valid number since assert(number > 0))
TEST(LogFileNameTest_327, SmallestValidNumber_327) {
  std::string result = leveldb::LogFileName("db", 1);
  EXPECT_NE(result.find("db"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 4), ".log");
}

// Test with a very large number
TEST(LogFileNameTest_327, VeryLargeNumber_327) {
  uint64_t largeNum = 999999;
  std::string result = leveldb::LogFileName("/data/leveldb", largeNum);
  EXPECT_NE(result.find("/data/leveldb"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 4), ".log");
}

// Test with empty dbname
TEST(LogFileNameTest_327, EmptyDbName_327) {
  std::string result = leveldb::LogFileName("", 1);
  EXPECT_EQ(result.substr(result.size() - 4), ".log");
}

// Test that different numbers produce different filenames
TEST(LogFileNameTest_327, DifferentNumbersDifferentNames_327) {
  std::string result1 = leveldb::LogFileName("/tmp/db", 1);
  std::string result2 = leveldb::LogFileName("/tmp/db", 2);
  EXPECT_NE(result1, result2);
}

// Test that different dbnames produce different filenames
TEST(LogFileNameTest_327, DifferentDbNamesDifferentNames_327) {
  std::string result1 = leveldb::LogFileName("/tmp/db1", 1);
  std::string result2 = leveldb::LogFileName("/tmp/db2", 1);
  EXPECT_NE(result1, result2);
}

// Test with dbname containing trailing slash
TEST(LogFileNameTest_327, DbNameWithTrailingSlash_327) {
  std::string result = leveldb::LogFileName("/tmp/testdb/", 42);
  EXPECT_EQ(result.substr(result.size() - 4), ".log");
}

// Test the format follows MakeFileName pattern: dbname/NNNNNN.log
TEST(LogFileNameTest_327, FormatContainsSlashSeparator_327) {
  std::string result = leveldb::LogFileName("mydb", 5);
  // Should have a '/' separating dbname from the number part
  EXPECT_NE(result.find("mydb/"), std::string::npos);
}

// Test that the number is zero-padded to 6 digits (common leveldb convention)
TEST(LogFileNameTest_327, NumberZeroPadded_327) {
  std::string result = leveldb::LogFileName("db", 1);
  // Expected format: db/000001.log
  EXPECT_EQ(result, "db/000001.log");
}

// Test zero-padding with a 6-digit number
TEST(LogFileNameTest_327, SixDigitNumber_327) {
  std::string result = leveldb::LogFileName("db", 123456);
  EXPECT_EQ(result, "db/123456.log");
}

// Test with max uint64_t value (boundary)
TEST(LogFileNameTest_327, MaxUint64Number_327) {
  uint64_t maxVal = UINT64_MAX;
  std::string result = leveldb::LogFileName("db", maxVal);
  EXPECT_EQ(result.substr(result.size() - 4), ".log");
  EXPECT_NE(result.find("db/"), std::string::npos);
}
