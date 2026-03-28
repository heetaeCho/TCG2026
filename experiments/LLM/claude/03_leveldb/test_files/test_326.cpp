#include "gtest/gtest.h"
#include "db/filename.h"
#include <string>
#include <cstdint>

namespace leveldb {

// Test normal operation of LogFileName
TEST(FilenameTest_326, LogFileName_Normal_326) {
  std::string result = LogFileName("/tmp/db", 42);
  EXPECT_EQ(result, "/tmp/db/000042.log");
}

TEST(FilenameTest_326, LogFileName_LargeNumber_326) {
  std::string result = LogFileName("/tmp/db", 1234567);
  EXPECT_EQ(result, "/tmp/db/1234567.log");
}

TEST(FilenameTest_326, LogFileName_Zero_326) {
  std::string result = LogFileName("/tmp/db", 0);
  EXPECT_EQ(result, "/tmp/db/000000.log");
}

TEST(FilenameTest_326, LogFileName_EmptyDbname_326) {
  std::string result = LogFileName("", 1);
  EXPECT_EQ(result, "/000001.log");
}

// Test TableFileName
TEST(FilenameTest_326, TableFileName_Normal_326) {
  std::string result = TableFileName("/tmp/db", 100);
  EXPECT_EQ(result, "/tmp/db/000100.ldb");
}

TEST(FilenameTest_326, TableFileName_Zero_326) {
  std::string result = TableFileName("/tmp/db", 0);
  EXPECT_EQ(result, "/tmp/db/000000.ldb");
}

TEST(FilenameTest_326, TableFileName_LargeNumber_326) {
  std::string result = TableFileName("/tmp/db", 9999999);
  EXPECT_EQ(result, "/tmp/db/9999999.ldb");
}

// Test SSTTableFileName (legacy name)
TEST(FilenameTest_326, SSTTableFileName_Normal_326) {
  std::string result = SSTTableFileName("/tmp/db", 100);
  EXPECT_EQ(result, "/tmp/db/000100.sst");
}

// Test DescriptorFileName (MANIFEST)
TEST(FilenameTest_326, DescriptorFileName_Normal_326) {
  std::string result = DescriptorFileName("/tmp/db", 5);
  EXPECT_EQ(result, "/tmp/db/MANIFEST-000005");
}

TEST(FilenameTest_326, DescriptorFileName_Zero_326) {
  std::string result = DescriptorFileName("/tmp/db", 0);
  EXPECT_EQ(result, "/tmp/db/MANIFEST-000000");
}

// Test CurrentFileName
TEST(FilenameTest_326, CurrentFileName_Normal_326) {
  std::string result = CurrentFileName("/tmp/db");
  EXPECT_EQ(result, "/tmp/db/CURRENT");
}

TEST(FilenameTest_326, CurrentFileName_EmptyDbname_326) {
  std::string result = CurrentFileName("");
  EXPECT_EQ(result, "/CURRENT");
}

// Test LockFileName
TEST(FilenameTest_326, LockFileName_Normal_326) {
  std::string result = LockFileName("/tmp/db");
  EXPECT_EQ(result, "/tmp/db/LOCK");
}

// Test TempFileName
TEST(FilenameTest_326, TempFileName_Normal_326) {
  std::string result = TempFileName("/tmp/db", 42);
  EXPECT_EQ(result, "/tmp/db/000042.dbtmp");
}

TEST(FilenameTest_326, TempFileName_Zero_326) {
  std::string result = TempFileName("/tmp/db", 0);
  EXPECT_EQ(result, "/tmp/db/000000.dbtmp");
}

// Test InfoLogFileName
TEST(FilenameTest_326, InfoLogFileName_Normal_326) {
  std::string result = InfoLogFileName("/tmp/db");
  EXPECT_EQ(result, "/tmp/db/LOG");
}

// Test OldInfoLogFileName
TEST(FilenameTest_326, OldInfoLogFileName_Normal_326) {
  std::string result = OldInfoLogFileName("/tmp/db");
  EXPECT_EQ(result, "/tmp/db/LOG.old");
}

// Test ParseFileName
TEST(FilenameTest_326, ParseFileName_LogFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000042.log", &number, &type));
  EXPECT_EQ(number, 42);
  EXPECT_EQ(type, kLogFile);
}

TEST(FilenameTest_326, ParseFileName_TableFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000100.ldb", &number, &type));
  EXPECT_EQ(number, 100);
  EXPECT_EQ(type, kTableFile);
}

TEST(FilenameTest_326, ParseFileName_SSTFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000100.sst", &number, &type));
  EXPECT_EQ(number, 100);
  EXPECT_EQ(type, kTableFile);
}

TEST(FilenameTest_326, ParseFileName_DescriptorFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("MANIFEST-000005", &number, &type));
  EXPECT_EQ(number, 5);
  EXPECT_EQ(type, kDescriptorFile);
}

TEST(FilenameTest_326, ParseFileName_CurrentFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("CURRENT", &number, &type));
  EXPECT_EQ(type, kCurrentFile);
}

TEST(FilenameTest_326, ParseFileName_LockFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("LOCK", &number, &type));
  EXPECT_EQ(type, kDBLockFile);
}

TEST(FilenameTest_326, ParseFileName_InfoLogFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("LOG", &number, &type));
  EXPECT_EQ(type, kInfoLogFile);
}

TEST(FilenameTest_326, ParseFileName_OldInfoLogFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("LOG.old", &number, &type));
  EXPECT_EQ(type, kInfoLogFile);
}

TEST(FilenameTest_326, ParseFileName_TempFile_326) {
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName("000042.dbtmp", &number, &type));
  EXPECT_EQ(number, 42);
  EXPECT_EQ(type, kTempFile);
}

TEST(FilenameTest_326, ParseFileName_InvalidFile_326) {
  uint64_t number;
  FileType type;
  EXPECT_FALSE(ParseFileName("garbage", &number, &type));
}

TEST(FilenameTest_326, ParseFileName_EmptyString_326) {
  uint64_t number;
  FileType type;
  EXPECT_FALSE(ParseFileName("", &number, &type));
}

TEST(FilenameTest_326, ParseFileName_InvalidSuffix_326) {
  uint64_t number;
  FileType type;
  EXPECT_FALSE(ParseFileName("000042.xyz", &number, &type));
}

// Test boundary: exactly 6 digit padding
TEST(FilenameTest_326, LogFileName_ExactlySixDigits_326) {
  std::string result = LogFileName("/db", 999999);
  EXPECT_EQ(result, "/db/999999.log");
}

// Test boundary: number exceeding 6 digits
TEST(FilenameTest_326, LogFileName_SevenDigits_326) {
  std::string result = LogFileName("/db", 1000000);
  EXPECT_EQ(result, "/db/1000000.log");
}

// Test with trailing slash in dbname
TEST(FilenameTest_326, LogFileName_TrailingSlashDbname_326) {
  // The implementation adds a '/' before the number, so trailing slash results in double slash
  std::string result = LogFileName("/tmp/db/", 1);
  EXPECT_EQ(result, "/tmp/db//000001.log");
}

// Test max uint64 value
TEST(FilenameTest_326, LogFileName_MaxUint64_326) {
  std::string result = LogFileName("/db", UINT64_MAX);
  // Just verify it doesn't crash and contains .log
  EXPECT_NE(result.find(".log"), std::string::npos);
}

TEST(FilenameTest_326, TableFileName_MaxUint64_326) {
  std::string result = TableFileName("/db", UINT64_MAX);
  EXPECT_NE(result.find(".ldb"), std::string::npos);
}

// Verify consistency: generating a filename then parsing it
TEST(FilenameTest_326, RoundTrip_LogFile_326) {
  std::string full = LogFileName("/db", 42);
  // Extract just the filename part (after last '/')
  std::string basename = full.substr(full.rfind('/') + 1);
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName(basename, &number, &type));
  EXPECT_EQ(number, 42);
  EXPECT_EQ(type, kLogFile);
}

TEST(FilenameTest_326, RoundTrip_TableFile_326) {
  std::string full = TableFileName("/db", 999);
  std::string basename = full.substr(full.rfind('/') + 1);
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName(basename, &number, &type));
  EXPECT_EQ(number, 999);
  EXPECT_EQ(type, kTableFile);
}

TEST(FilenameTest_326, RoundTrip_DescriptorFile_326) {
  std::string full = DescriptorFileName("/db", 7);
  std::string basename = full.substr(full.rfind('/') + 1);
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName(basename, &number, &type));
  EXPECT_EQ(number, 7);
  EXPECT_EQ(type, kDescriptorFile);
}

TEST(FilenameTest_326, RoundTrip_TempFile_326) {
  std::string full = TempFileName("/db", 123);
  std::string basename = full.substr(full.rfind('/') + 1);
  uint64_t number;
  FileType type;
  ASSERT_TRUE(ParseFileName(basename, &number, &type));
  EXPECT_EQ(number, 123);
  EXPECT_EQ(type, kTempFile);
}

}  // namespace leveldb
