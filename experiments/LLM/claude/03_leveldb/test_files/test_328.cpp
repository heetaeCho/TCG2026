#include "gtest/gtest.h"
#include <string>
#include <cstdint>

// Forward declaration based on the interface
namespace leveldb {
std::string TableFileName(const std::string& dbname, uint64_t number);
}

// Include the actual header that declares TableFileName
// Based on typical leveldb structure:
#include "db/filename.h"

namespace leveldb {

// Test normal operation with a typical database name and number
TEST(TableFileNameTest_328, NormalOperation_328) {
  std::string result = TableFileName("/tmp/testdb", 1);
  // Should contain the dbname as prefix
  EXPECT_TRUE(result.find("/tmp/testdb") == 0);
  // Should end with .ldb extension
  EXPECT_TRUE(result.size() >= 4);
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
}

// Test with number = 1 (minimum valid number)
TEST(TableFileNameTest_328, MinimumValidNumber_328) {
  std::string result = TableFileName("db", 1);
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
}

// Test with a large number
TEST(TableFileNameTest_328, LargeNumber_328) {
  std::string result = TableFileName("db", 999999);
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
}

// Test with maximum uint64_t value
TEST(TableFileNameTest_328, MaxUint64Number_328) {
  std::string result = TableFileName("db", UINT64_MAX);
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
}

// Test with empty dbname
TEST(TableFileNameTest_328, EmptyDbName_328) {
  std::string result = TableFileName("", 1);
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
}

// Test that different numbers produce different filenames
TEST(TableFileNameTest_328, DifferentNumbersProduceDifferentNames_328) {
  std::string result1 = TableFileName("db", 1);
  std::string result2 = TableFileName("db", 2);
  EXPECT_NE(result1, result2);
}

// Test that different dbnames produce different filenames
TEST(TableFileNameTest_328, DifferentDbNamesProduceDifferentNames_328) {
  std::string result1 = TableFileName("db1", 1);
  std::string result2 = TableFileName("db2", 1);
  EXPECT_NE(result1, result2);
}

// Test that the result contains a path separator between dbname and the file part
TEST(TableFileNameTest_328, ContainsPathSeparator_328) {
  std::string dbname = "/tmp/testdb";
  std::string result = TableFileName(dbname, 100);
  // The result should have a '/' after the dbname portion
  EXPECT_TRUE(result.size() > dbname.size());
  EXPECT_EQ(result[dbname.size()], '/');
}

// Test with number = 2 to verify consistent format
TEST(TableFileNameTest_328, NumberTwo_328) {
  std::string result = TableFileName("mydb", 2);
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
  EXPECT_TRUE(result.find("mydb") == 0);
}

// Test the format follows the expected pattern: dbname/XXXXXX.ldb
TEST(TableFileNameTest_328, ExpectedFormat_328) {
  std::string result = TableFileName("testdb", 123);
  // Should start with dbname
  EXPECT_EQ(result.substr(0, 6), "testdb");
  // Should end with .ldb
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
  // The number part should be 6 digits (zero-padded) based on leveldb convention
  // Format: dbname/000123.ldb
  EXPECT_EQ(result, "testdb/000123.ldb");
}

// Test with a trailing slash in dbname
TEST(TableFileNameTest_328, DbNameWithTrailingSlash_328) {
  std::string result = TableFileName("/tmp/db/", 5);
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(result.substr(result.size() - 4), ".ldb");
}

// Test same inputs produce same outputs (deterministic)
TEST(TableFileNameTest_328, Deterministic_328) {
  std::string result1 = TableFileName("db", 42);
  std::string result2 = TableFileName("db", 42);
  EXPECT_EQ(result1, result2);
}

}  // namespace leveldb
