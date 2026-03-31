#include <string>
#include <cstdint>
#include "gtest/gtest.h"
#include "db/filename.h"

namespace leveldb {

// Test normal operation with a typical number
TEST(TempFileNameTest_333, NormalNumber_333) {
  std::string result = TempFileName("/tmp/testdb", 1);
  // Should contain the dbname prefix
  EXPECT_NE(result.find("/tmp/testdb/"), std::string::npos);
  // Should end with .dbtmp
  EXPECT_GE(result.size(), 6u);
  EXPECT_EQ(result.substr(result.size() - 6), ".dbtmp");
}

// Test with number = 1 (minimum valid number)
TEST(TempFileNameTest_333, MinimumValidNumber_333) {
  std::string result = TempFileName("db", 1);
  EXPECT_NE(result.find("db/"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 6), ".dbtmp");
}

// Test with a large number
TEST(TempFileNameTest_333, LargeNumber_333) {
  std::string result = TempFileName("db", 999999);
  EXPECT_NE(result.find("db/"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 6), ".dbtmp");
  // The number 999999 should appear in the filename in some form
  EXPECT_NE(result.find("999999"), std::string::npos);
}

// Test with maximum uint64_t value
TEST(TempFileNameTest_333, MaxUint64Number_333) {
  std::string result = TempFileName("db", UINT64_MAX);
  EXPECT_EQ(result.substr(result.size() - 6), ".dbtmp");
}

// Test with empty dbname
TEST(TempFileNameTest_333, EmptyDbName_333) {
  std::string result = TempFileName("", 1);
  EXPECT_EQ(result.substr(result.size() - 6), ".dbtmp");
}

// Test that different numbers produce different filenames
TEST(TempFileNameTest_333, DifferentNumbersDifferentFiles_333) {
  std::string result1 = TempFileName("db", 1);
  std::string result2 = TempFileName("db", 2);
  EXPECT_NE(result1, result2);
}

// Test that different dbnames produce different filenames
TEST(TempFileNameTest_333, DifferentDbNamesDifferentFiles_333) {
  std::string result1 = TempFileName("db1", 1);
  std::string result2 = TempFileName("db2", 1);
  EXPECT_NE(result1, result2);
}

// Test with dbname containing path separators
TEST(TempFileNameTest_333, DbNameWithPathSeparators_333) {
  std::string result = TempFileName("/a/b/c/db", 42);
  EXPECT_NE(result.find("/a/b/c/db/"), std::string::npos);
  EXPECT_EQ(result.substr(result.size() - 6), ".dbtmp");
}

// Test consistency - same inputs should produce same output
TEST(TempFileNameTest_333, Consistency_333) {
  std::string result1 = TempFileName("testdb", 100);
  std::string result2 = TempFileName("testdb", 100);
  EXPECT_EQ(result1, result2);
}

// Test that the filename format follows expected pattern (number is zero-padded to 6 digits)
TEST(TempFileNameTest_333, NumberFormatInFilename_333) {
  std::string result = TempFileName("db", 42);
  // MakeFileName typically formats as "dbname/NNNNNN.suffix"
  // For number 42, expect "000042" somewhere in the name
  EXPECT_NE(result.find("000042"), std::string::npos);
}

// Test with number that has more than 6 digits
TEST(TempFileNameTest_333, NumberMoreThanSixDigits_333) {
  std::string result = TempFileName("db", 1234567);
  EXPECT_EQ(result.substr(result.size() - 6), ".dbtmp");
  EXPECT_NE(result.find("1234567"), std::string::npos);
}

}  // namespace leveldb
