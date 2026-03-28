#include "gtest/gtest.h"
#include "db/filename.h"
#include <string>
#include <cstdint>

namespace leveldb {

// Forward declaration - ParseFileName is declared in db/filename.h
bool ParseFileName(const std::string& filename, uint64_t* number, FileType* type);

class ParseFileNameTest_336 : public ::testing::Test {
 protected:
  uint64_t number_;
  FileType type_;
};

// Test CURRENT file
TEST_F(ParseFileNameTest_336, ParseCurrentFile_336) {
  ASSERT_TRUE(ParseFileName("CURRENT", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kCurrentFile, type_);
}

// Test LOCK file
TEST_F(ParseFileNameTest_336, ParseLockFile_336) {
  ASSERT_TRUE(ParseFileName("LOCK", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kDBLockFile, type_);
}

// Test LOG file
TEST_F(ParseFileNameTest_336, ParseLogInfoFile_336) {
  ASSERT_TRUE(ParseFileName("LOG", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kInfoLogFile, type_);
}

// Test LOG.old file
TEST_F(ParseFileNameTest_336, ParseLogOldInfoFile_336) {
  ASSERT_TRUE(ParseFileName("LOG.old", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kInfoLogFile, type_);
}

// Test MANIFEST file with valid number
TEST_F(ParseFileNameTest_336, ParseManifestFile_336) {
  ASSERT_TRUE(ParseFileName("MANIFEST-000002", &number_, &type_));
  EXPECT_EQ(2, number_);
  EXPECT_EQ(kDescriptorFile, type_);
}

// Test MANIFEST file with number 1
TEST_F(ParseFileNameTest_336, ParseManifestFileNumber1_336) {
  ASSERT_TRUE(ParseFileName("MANIFEST-1", &number_, &type_));
  EXPECT_EQ(1, number_);
  EXPECT_EQ(kDescriptorFile, type_);
}

// Test MANIFEST file with large number
TEST_F(ParseFileNameTest_336, ParseManifestFileLargeNumber_336) {
  ASSERT_TRUE(ParseFileName("MANIFEST-999999", &number_, &type_));
  EXPECT_EQ(999999, number_);
  EXPECT_EQ(kDescriptorFile, type_);
}

// Test MANIFEST file with no number (should fail)
TEST_F(ParseFileNameTest_336, ParseManifestFileNoNumber_336) {
  ASSERT_FALSE(ParseFileName("MANIFEST-", &number_, &type_));
}

// Test MANIFEST file with trailing characters (should fail)
TEST_F(ParseFileNameTest_336, ParseManifestFileTrailingChars_336) {
  ASSERT_FALSE(ParseFileName("MANIFEST-2abc", &number_, &type_));
}

// Test MANIFEST file with non-numeric content (should fail)
TEST_F(ParseFileNameTest_336, ParseManifestFileNonNumeric_336) {
  ASSERT_FALSE(ParseFileName("MANIFEST-abc", &number_, &type_));
}

// Test .log file (WAL log file)
TEST_F(ParseFileNameTest_336, ParseLogFile_336) {
  ASSERT_TRUE(ParseFileName("000100.log", &number_, &type_));
  EXPECT_EQ(100, number_);
  EXPECT_EQ(kLogFile, type_);
}

// Test .log file with simple number
TEST_F(ParseFileNameTest_336, ParseLogFileSimple_336) {
  ASSERT_TRUE(ParseFileName("5.log", &number_, &type_));
  EXPECT_EQ(5, number_);
  EXPECT_EQ(kLogFile, type_);
}

// Test .sst file (table file)
TEST_F(ParseFileNameTest_336, ParseSstFile_336) {
  ASSERT_TRUE(ParseFileName("000100.sst", &number_, &type_));
  EXPECT_EQ(100, number_);
  EXPECT_EQ(kTableFile, type_);
}

// Test .ldb file (table file)
TEST_F(ParseFileNameTest_336, ParseLdbFile_336) {
  ASSERT_TRUE(ParseFileName("000100.ldb", &number_, &type_));
  EXPECT_EQ(100, number_);
  EXPECT_EQ(kTableFile, type_);
}

// Test .dbtmp file (temp file)
TEST_F(ParseFileNameTest_336, ParseTempFile_336) {
  ASSERT_TRUE(ParseFileName("000100.dbtmp", &number_, &type_));
  EXPECT_EQ(100, number_);
  EXPECT_EQ(kTempFile, type_);
}

// Test empty filename (should fail)
TEST_F(ParseFileNameTest_336, ParseEmptyFilename_336) {
  ASSERT_FALSE(ParseFileName("", &number_, &type_));
}

// Test unknown extension (should fail)
TEST_F(ParseFileNameTest_336, ParseUnknownExtension_336) {
  ASSERT_FALSE(ParseFileName("000100.txt", &number_, &type_));
}

// Test no extension after number (should fail)
TEST_F(ParseFileNameTest_336, ParseNoExtension_336) {
  ASSERT_FALSE(ParseFileName("000100", &number_, &type_));
}

// Test random string (should fail)
TEST_F(ParseFileNameTest_336, ParseRandomString_336) {
  ASSERT_FALSE(ParseFileName("foobar", &number_, &type_));
}

// Test number 0 with .log extension
TEST_F(ParseFileNameTest_336, ParseZeroLogFile_336) {
  ASSERT_TRUE(ParseFileName("0.log", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kLogFile, type_);
}

// Test number 0 with .sst extension
TEST_F(ParseFileNameTest_336, ParseZeroSstFile_336) {
  ASSERT_TRUE(ParseFileName("0.sst", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kTableFile, type_);
}

// Test number 0 with .ldb extension
TEST_F(ParseFileNameTest_336, ParseZeroLdbFile_336) {
  ASSERT_TRUE(ParseFileName("0.ldb", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kTableFile, type_);
}

// Test number 0 with .dbtmp extension
TEST_F(ParseFileNameTest_336, ParseZeroTempFile_336) {
  ASSERT_TRUE(ParseFileName("0.dbtmp", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kTempFile, type_);
}

// Test only a dot (should fail)
TEST_F(ParseFileNameTest_336, ParseOnlyDot_336) {
  ASSERT_FALSE(ParseFileName(".", &number_, &type_));
}

// Test only a number with dot but no extension name (should fail)
TEST_F(ParseFileNameTest_336, ParseNumberWithDotOnly_336) {
  ASSERT_FALSE(ParseFileName("123.", &number_, &type_));
}

// Test MANIFEST without dash (should fail - doesn't start with number)
TEST_F(ParseFileNameTest_336, ParseManifestNoDash_336) {
  ASSERT_FALSE(ParseFileName("MANIFEST", &number_, &type_));
}

// Test case sensitivity - lowercase current should fail
TEST_F(ParseFileNameTest_336, ParseLowercaseCurrent_336) {
  ASSERT_FALSE(ParseFileName("current", &number_, &type_));
}

// Test case sensitivity - lowercase lock should fail
TEST_F(ParseFileNameTest_336, ParseLowercaseLock_336) {
  ASSERT_FALSE(ParseFileName("lock", &number_, &type_));
}

// Test case sensitivity - lowercase log should fail
TEST_F(ParseFileNameTest_336, ParseLowercaseLog_336) {
  ASSERT_FALSE(ParseFileName("log", &number_, &type_));
}

// Test large file number
TEST_F(ParseFileNameTest_336, ParseLargeNumberLogFile_336) {
  ASSERT_TRUE(ParseFileName("18446744073709551615.log", &number_, &type_));
  EXPECT_EQ(18446744073709551615ULL, number_);
  EXPECT_EQ(kLogFile, type_);
}

// Test MANIFEST-0
TEST_F(ParseFileNameTest_336, ParseManifestZero_336) {
  ASSERT_TRUE(ParseFileName("MANIFEST-0", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kDescriptorFile, type_);
}

// Test double extension (should fail)
TEST_F(ParseFileNameTest_336, ParseDoubleExtension_336) {
  ASSERT_FALSE(ParseFileName("123.log.sst", &number_, &type_));
}

// Test leading zeros in numbered files
TEST_F(ParseFileNameTest_336, ParseLeadingZerosLogFile_336) {
  ASSERT_TRUE(ParseFileName("000000.log", &number_, &type_));
  EXPECT_EQ(0, number_);
  EXPECT_EQ(kLogFile, type_);
}

// Test CURRENT with trailing characters should fail
TEST_F(ParseFileNameTest_336, ParseCurrentWithTrailing_336) {
  ASSERT_FALSE(ParseFileName("CURRENT2", &number_, &type_));
}

// Test LOG with unexpected suffix should fail
TEST_F(ParseFileNameTest_336, ParseLogWithUnexpectedSuffix_336) {
  ASSERT_FALSE(ParseFileName("LOG.new", &number_, &type_));
}

// Test LOCK with trailing should fail
TEST_F(ParseFileNameTest_336, ParseLockWithTrailing_336) {
  ASSERT_FALSE(ParseFileName("LOCK2", &number_, &type_));
}

// Test space in filename (should fail)
TEST_F(ParseFileNameTest_336, ParseSpaceInFilename_336) {
  ASSERT_FALSE(ParseFileName("100 .log", &number_, &type_));
}

}  // namespace leveldb
