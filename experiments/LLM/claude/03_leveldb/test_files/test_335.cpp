#include "gtest/gtest.h"
#include <string>

// Forward declare the function we're testing
namespace leveldb {
std::string OldInfoLogFileName(const std::string& dbname);
}

// Also include relevant headers that may declare additional filename utilities
#include "db/filename.h"

namespace leveldb {

// Test normal operation with a typical database name
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForTypicalDbName_335) {
  std::string result = OldInfoLogFileName("/tmp/testdb");
  EXPECT_EQ(result, "/tmp/testdb/LOG.old");
}

// Test with empty database name
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForEmptyDbName_335) {
  std::string result = OldInfoLogFileName("");
  EXPECT_EQ(result, "/LOG.old");
}

// Test with root path
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForRootPath_335) {
  std::string result = OldInfoLogFileName("/");
  EXPECT_EQ(result, "//LOG.old");
}

// Test with a simple directory name (no leading slash)
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForRelativePath_335) {
  std::string result = OldInfoLogFileName("mydb");
  EXPECT_EQ(result, "mydb/LOG.old");
}

// Test with a path that has a trailing slash
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForTrailingSlash_335) {
  std::string result = OldInfoLogFileName("/tmp/testdb/");
  EXPECT_EQ(result, "/tmp/testdb//LOG.old");
}

// Test with a deeply nested path
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForDeeplyNestedPath_335) {
  std::string result = OldInfoLogFileName("/a/b/c/d/e/f");
  EXPECT_EQ(result, "/a/b/c/d/e/f/LOG.old");
}

// Test with a path containing dots
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForPathWithDots_335) {
  std::string result = OldInfoLogFileName("/tmp/test.db");
  EXPECT_EQ(result, "/tmp/test.db/LOG.old");
}

// Test with a path containing spaces
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForPathWithSpaces_335) {
  std::string result = OldInfoLogFileName("/tmp/my database");
  EXPECT_EQ(result, "/tmp/my database/LOG.old");
}

// Test with a single character database name
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForSingleCharDbName_335) {
  std::string result = OldInfoLogFileName("x");
  EXPECT_EQ(result, "x/LOG.old");
}

// Test with current directory notation
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForCurrentDir_335) {
  std::string result = OldInfoLogFileName(".");
  EXPECT_EQ(result, "./LOG.old");
}

// Test with parent directory notation
TEST(OldInfoLogFileNameTest_335, ReturnsCorrectPathForParentDir_335) {
  std::string result = OldInfoLogFileName("..");
  EXPECT_EQ(result, "../LOG.old");
}

// Additional filename utility tests if the header exposes more functions

// Test MakeFileName / TableFileName if available
TEST(FileNameTest_335, TableFileName_335) {
  std::string result = TableFileName("/tmp/testdb", 123);
  EXPECT_EQ(result, "/tmp/testdb/000123.ldb");
}

TEST(FileNameTest_335, SSTTableFileName_335) {
  std::string result = SSTTableFileName("/tmp/testdb", 123);
  EXPECT_EQ(result, "/tmp/testdb/000123.sst");
}

TEST(FileNameTest_335, LogFileName_335) {
  std::string result = LogFileName("/tmp/testdb", 42);
  EXPECT_EQ(result, "/tmp/testdb/000042.log");
}

TEST(FileNameTest_335, DescriptorFileName_335) {
  std::string result = DescriptorFileName("/tmp/testdb", 100);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-000100");
}

TEST(FileNameTest_335, CurrentFileName_335) {
  std::string result = CurrentFileName("/tmp/testdb");
  EXPECT_EQ(result, "/tmp/testdb/CURRENT");
}

TEST(FileNameTest_335, LockFileName_335) {
  std::string result = LockFileName("/tmp/testdb");
  EXPECT_EQ(result, "/tmp/testdb/LOCK");
}

TEST(FileNameTest_335, TempFileName_335) {
  std::string result = TempFileName("/tmp/testdb", 999);
  EXPECT_EQ(result, "/tmp/testdb/000999.dbtmp");
}

TEST(FileNameTest_335, InfoLogFileName_335) {
  std::string result = InfoLogFileName("/tmp/testdb");
  EXPECT_EQ(result, "/tmp/testdb/LOG");
}

// Test ParseFileName
TEST(ParseFileNameTest_335, ParseLogFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000042.log", &number, &type));
  EXPECT_EQ(number, 42u);
  EXPECT_EQ(type, kLogFile);
}

TEST(ParseFileNameTest_335, ParseTableFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000123.ldb", &number, &type));
  EXPECT_EQ(number, 123u);
  EXPECT_EQ(type, kTableFile);
}

TEST(ParseFileNameTest_335, ParseSSTFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000123.sst", &number, &type));
  EXPECT_EQ(number, 123u);
  EXPECT_EQ(type, kTableFile);
}

TEST(ParseFileNameTest_335, ParseDescriptorFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("MANIFEST-000100", &number, &type));
  EXPECT_EQ(number, 100u);
  EXPECT_EQ(type, kDescriptorFile);
}

TEST(ParseFileNameTest_335, ParseCurrentFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("CURRENT", &number, &type));
  EXPECT_EQ(type, kCurrentFile);
}

TEST(ParseFileNameTest_335, ParseLockFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("LOCK", &number, &type));
  EXPECT_EQ(type, kDBLockFile);
}

TEST(ParseFileNameTest_335, ParseInfoLogFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("LOG", &number, &type));
  EXPECT_EQ(type, kInfoLogFile);
}

TEST(ParseFileNameTest_335, ParseOldInfoLogFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("LOG.old", &number, &type));
  EXPECT_EQ(type, kInfoLogFile);
}

TEST(ParseFileNameTest_335, ParseTempFile_335) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000999.dbtmp", &number, &type));
  EXPECT_EQ(number, 999u);
  EXPECT_EQ(type, kTempFile);
}

TEST(ParseFileNameTest_335, InvalidFileName_335) {
  uint64_t number;
  FileType type;
  EXPECT_FALSE(ParseFileName("garbage", &number, &type));
}

TEST(ParseFileNameTest_335, EmptyFileName_335) {
  uint64_t number;
  FileType type;
  EXPECT_FALSE(ParseFileName("", &number, &type));
}

// Boundary: file number 0
TEST(FileNameTest_335, TableFileNameWithZero_335) {
  std::string result = TableFileName("/db", 0);
  EXPECT_EQ(result, "/db/000000.ldb");
}

TEST(FileNameTest_335, LogFileNameWithZero_335) {
  std::string result = LogFileName("/db", 0);
  EXPECT_EQ(result, "/db/000000.log");
}

// Large file number
TEST(FileNameTest_335, TableFileNameWithLargeNumber_335) {
  std::string result = TableFileName("/db", 9999999);
  EXPECT_EQ(result, "/db/9999999.ldb");
}

}  // namespace leveldb
