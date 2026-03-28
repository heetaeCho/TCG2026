// filename_current_test.cc
#include <string>
#include "gtest/gtest.h"

// We only need the declaration to call the already-implemented function.
namespace leveldb {
std::string CurrentFileName(const std::string& dbname);
}

class CurrentFileNameTest_331 : public ::testing::Test {};

// Normal operation: typical DB name
TEST_F(CurrentFileNameTest_331, ReturnsCURRENTPath_ForTypicalDbName_331) {
  const std::string dbname = "/var/data/mydb";
  const std::string result = leveldb::CurrentFileName(dbname);
  EXPECT_EQ("/var/data/mydb/CURRENT", result);
}

// Boundary: empty database name (still returns "/CURRENT")
TEST_F(CurrentFileNameTest_331, HandlesEmptyDbName_331) {
  const std::string dbname = "";
  const std::string result = leveldb::CurrentFileName(dbname);
  EXPECT_EQ("/CURRENT", result);
}

// Boundary: dbname already ends with a slash (observable behavior: double slash)
TEST_F(CurrentFileNameTest_331, PreservesTrailingSlashInInput_331) {
  const std::string dbname = "/var/data/mydb/";
  const std::string result = leveldb::CurrentFileName(dbname);
  EXPECT_EQ("/var/data/mydb//CURRENT", result);
}

// Integrity: input string is not modified by the function
TEST_F(CurrentFileNameTest_331, DoesNotModifyInput_331) {
  std::string dbname = "/tmp/db";
  const std::string original = dbname;
  (void)leveldb::CurrentFileName(dbname);
  EXPECT_EQ(original, dbname);
}

// Unicode / non-ASCII path segment
TEST_F(CurrentFileNameTest_331, SupportsUnicodeDbName_331) {
  const std::string dbname = "/data/데이터베이스";
  const std::string result = leveldb::CurrentFileName(dbname);
  EXPECT_EQ("/data/데이터베이스/CURRENT", result);
}

// Long path name (stress boundary)
TEST_F(CurrentFileNameTest_331, HandlesLongDbName_331) {
  const std::string long_segment(1024, 'a'); // 1KB of 'a'
  const std::string dbname = "/very/long/path/" + long_segment;
  const std::string result = leveldb::CurrentFileName(dbname);
  EXPECT_EQ("/very/long/path/" + long_segment + "/CURRENT", result);
}
