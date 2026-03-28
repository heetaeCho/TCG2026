// filename_parse_unittest_336.cc
#include "db/filename.h"
#include "gtest/gtest.h"

namespace leveldb {

// Forward-declare the function under test (provided in db/filename.cc).
bool ParseFileName(const std::string& filename, uint64_t* number, FileType* type);

// --- Normal operation cases ---

TEST(ParseFileNameTest_336, ParsesCURRENTAsCurrentFile_336) {
  uint64_t num = 123;  // pre-set to non-zero; we only assert observable outputs
  FileType type = kLogFile;
  ASSERT_TRUE(ParseFileName("CURRENT", &num, &type));
  EXPECT_EQ(0u, num);
  EXPECT_EQ(kCurrentFile, type);
}

TEST(ParseFileNameTest_336, ParsesLOCKAsDBLockFile_336) {
  uint64_t num = 999;
  FileType type = kLogFile;
  ASSERT_TRUE(ParseFileName("LOCK", &num, &type));
  EXPECT_EQ(0u, num);
  EXPECT_EQ(kDBLockFile, type);
}

TEST(ParseFileNameTest_336, ParsesLOGAsInfoLogFile_336) {
  uint64_t num = 42;
  FileType type = kLogFile;
  ASSERT_TRUE(ParseFileName("LOG", &num, &type));
  EXPECT_EQ(0u, num);
  EXPECT_EQ(kInfoLogFile, type);
}

TEST(ParseFileNameTest_336, ParsesLOGOldAsInfoLogFile_336) {
  uint64_t num = 7;
  FileType type = kLogFile;
  ASSERT_TRUE(ParseFileName("LOG.old", &num, &type));
  EXPECT_EQ(0u, num);
  EXPECT_EQ(kInfoLogFile, type);
}

TEST(ParseFileNameTest_336, ParsesManifestWithNumber_336) {
  uint64_t num = 0;
  FileType type = kTempFile;
  ASSERT_TRUE(ParseFileName("MANIFEST-000123", &num, &type));
  EXPECT_EQ(123u, num);           // Observable: decimal number parsed with leading zeros
  EXPECT_EQ(kDescriptorFile, type);
}

TEST(ParseFileNameTest_336, ParsesLogNumberedFile_336) {
  uint64_t num = 0;
  FileType type = kTempFile;
  ASSERT_TRUE(ParseFileName("000123.log", &num, &type));
  EXPECT_EQ(123u, num);
  EXPECT_EQ(kLogFile, type);
}

TEST(ParseFileNameTest_336, ParsesSstTableFile_336) {
  uint64_t num = 0;
  FileType type = kLogFile;
  ASSERT_TRUE(ParseFileName("000007.sst", &num, &type));
  EXPECT_EQ(7u, num);
  EXPECT_EQ(kTableFile, type);
}

TEST(ParseFileNameTest_336, ParsesLdbTableFile_336) {
  uint64_t num = 0;
  FileType type = kLogFile;
  ASSERT_TRUE(ParseFileName("42.ldb", &num, &type));
  EXPECT_EQ(42u, num);
  EXPECT_EQ(kTableFile, type);
}

TEST(ParseFileNameTest_336, ParsesTempFile_336) {
  uint64_t num = 0;
  FileType type = kLogFile;
  ASSERT_TRUE(ParseFileName("000001.dbtmp", &num, &type));
  EXPECT_EQ(1u, num);
  EXPECT_EQ(kTempFile, type);
}

TEST(ParseFileNameTest_336, ParsesZeroLogFileNumber_336) {
  uint64_t num = 999;
  FileType type = kTableFile;
  ASSERT_TRUE(ParseFileName("0.log", &num, &type));
  EXPECT_EQ(0u, num);
  EXPECT_EQ(kLogFile, type);
}

// --- Boundary / malformed / error cases (observable via return=false) ---

TEST(ParseFileNameTest_336, RejectsManifestWithoutNumber_336) {
  uint64_t num = 111;
  FileType type = kLogFile;
  EXPECT_FALSE(ParseFileName("MANIFEST-", &num, &type));
}

TEST(ParseFileNameTest_336, RejectsManifestWithTrailingGarbage_336) {
  uint64_t num = 111;
  FileType type = kLogFile;
  EXPECT_FALSE(ParseFileName("MANIFEST-123a", &num, &type));
}

TEST(ParseFileNameTest_336, RejectsFilenameWithoutSuffix_336) {
  uint64_t num = 111;
  FileType type = kLogFile;
  EXPECT_FALSE(ParseFileName("000123", &num, &type));
}

TEST(ParseFileNameTest_336, RejectsUnknownSuffix_336) {
  uint64_t num = 111;
  FileType type = kLogFile;
  EXPECT_FALSE(ParseFileName("123.xyz", &num, &type));
}

TEST(ParseFileNameTest_336, RejectsNonDecimalPrefixForNumberedFiles_336) {
  uint64_t num = 111;
  FileType type = kLogFile;
  EXPECT_FALSE(ParseFileName("abc.log", &num, &type));
}

}  // namespace leveldb
