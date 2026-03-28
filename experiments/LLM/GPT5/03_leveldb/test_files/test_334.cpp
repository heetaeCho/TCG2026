// File: db/filename_info_log_test.cc

#include "gtest/gtest.h"
#include "db/filename.h"   // assumes InfoLogFileName is declared here
#include <string>

namespace {

using leveldb::InfoLogFileName;

// Normal operation: typical POSIX path
TEST(InfoLogFileNameTest_334, ReturnsLogPathForPosixDir_334) {
  const std::string dbname = "/tmp/testdb";
  EXPECT_EQ(InfoLogFileName(dbname), "/tmp/testdb/LOG");
}

// Boundary: empty database name
TEST(InfoLogFileNameTest_334, HandlesEmptyDbName_334) {
  const std::string dbname = "";
  EXPECT_EQ(InfoLogFileName(dbname), "/LOG");
}

// Boundary: trailing slash is preserved (no normalization expected)
TEST(InfoLogFileNameTest_334, PreservesTrailingSlash_334) {
  const std::string dbname = "/var/lib/leveldb/";
  EXPECT_EQ(InfoLogFileName(dbname), "/var/lib/leveldb//LOG");
}

// Normal/portability: Windows-style path is not normalized (mixed slashes ok)
TEST(InfoLogFileNameTest_334, DoesNotNormalizeWindowsStylePath_334) {
  const std::string dbname = "C:\\data\\ldb";
  EXPECT_EQ(InfoLogFileName(dbname), "C:\\data\\ldb/LOG");
}

// Normal: unicode and spaces are passed through unchanged
TEST(InfoLogFileNameTest_334, SupportsUnicodeAndSpaces_334) {
  const std::string dbname = "/경로/공 백/db 01";
  EXPECT_EQ(InfoLogFileName(dbname), "/경로/공 백/db 01/LOG");
}

// Boundary: very long path (no truncation or crash; just appends "/LOG")
TEST(InfoLogFileNameTest_334, HandlesVeryLongDbName_334) {
  std::string dbname(4096, 'a');      // long but reasonable for a unit test
  const std::string result = InfoLogFileName(dbname);
  ASSERT_GE(result.size(), dbname.size() + 4);
  EXPECT_EQ(result.substr(0, dbname.size()), dbname);
  EXPECT_EQ(result.substr(dbname.size()), "/LOG");
}

}  // namespace
