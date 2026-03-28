#include "gtest/gtest.h"
#include <string>
#include <cstdint>

// Forward declare the function from the leveldb namespace
namespace leveldb {
std::string DescriptorFileName(const std::string& dbname, uint64_t number);
}

class DescriptorFileNameTest_330 : public ::testing::Test {
 protected:
};

// Normal operation: basic descriptor file name generation
TEST_F(DescriptorFileNameTest_330, BasicDescriptorFileName_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/testdb", 1);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-000001");
}

// Normal operation: number with multiple digits
TEST_F(DescriptorFileNameTest_330, MultiDigitNumber_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/testdb", 123456);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-123456");
}

// Normal operation: number exceeding 6 digits (padding should not truncate)
TEST_F(DescriptorFileNameTest_330, NumberExceedingSixDigits_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/testdb", 1234567);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-1234567");
}

// Normal operation: small number with zero padding
TEST_F(DescriptorFileNameTest_330, SmallNumberWithPadding_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/testdb", 42);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-000042");
}

// Normal operation: number equal to 1 (minimum valid input)
TEST_F(DescriptorFileNameTest_330, MinimumValidNumber_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/testdb", 1);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-000001");
}

// Normal operation: large number
TEST_F(DescriptorFileNameTest_330, LargeNumber_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/testdb", 999999);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-999999");
}

// Normal operation: very large number (uint64_t range)
TEST_F(DescriptorFileNameTest_330, VeryLargeNumber_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/testdb", 9999999999ULL);
  EXPECT_EQ(result, "/tmp/testdb/MANIFEST-9999999999");
}

// Boundary: empty dbname
TEST_F(DescriptorFileNameTest_330, EmptyDbName_330) {
  std::string result = leveldb::DescriptorFileName("", 1);
  EXPECT_EQ(result, "/MANIFEST-000001");
}

// Normal operation: dbname without trailing slash
TEST_F(DescriptorFileNameTest_330, DbNameWithoutTrailingSlash_330) {
  std::string result = leveldb::DescriptorFileName("/data/mydb", 100);
  EXPECT_EQ(result, "/data/mydb/MANIFEST-000100");
}

// Normal operation: dbname with trailing slash (slash gets doubled)
TEST_F(DescriptorFileNameTest_330, DbNameWithTrailingSlash_330) {
  std::string result = leveldb::DescriptorFileName("/data/mydb/", 100);
  EXPECT_EQ(result, "/data/mydb//MANIFEST-000100");
}

// Normal operation: simple dbname
TEST_F(DescriptorFileNameTest_330, SimpleDbName_330) {
  std::string result = leveldb::DescriptorFileName("db", 5);
  EXPECT_EQ(result, "db/MANIFEST-000005");
}

// Boundary: number exactly 6 digits
TEST_F(DescriptorFileNameTest_330, ExactlySixDigitNumber_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/db", 100000);
  EXPECT_EQ(result, "/tmp/db/MANIFEST-100000");
}

// Normal operation: number with 7 digits
TEST_F(DescriptorFileNameTest_330, SevenDigitNumber_330) {
  std::string result = leveldb::DescriptorFileName("/tmp/db", 1000000);
  EXPECT_EQ(result, "/tmp/db/MANIFEST-1000000");
}

// Normal operation: various padding checks
TEST_F(DescriptorFileNameTest_330, PaddingCheck_330) {
  EXPECT_EQ(leveldb::DescriptorFileName("db", 1), "db/MANIFEST-000001");
  EXPECT_EQ(leveldb::DescriptorFileName("db", 10), "db/MANIFEST-000010");
  EXPECT_EQ(leveldb::DescriptorFileName("db", 100), "db/MANIFEST-000100");
  EXPECT_EQ(leveldb::DescriptorFileName("db", 1000), "db/MANIFEST-001000");
  EXPECT_EQ(leveldb::DescriptorFileName("db", 10000), "db/MANIFEST-010000");
  EXPECT_EQ(leveldb::DescriptorFileName("db", 100000), "db/MANIFEST-100000");
}

// Normal operation: max uint64_t value
TEST_F(DescriptorFileNameTest_330, MaxUint64Number_330) {
  uint64_t maxVal = UINT64_MAX;
  std::string result = leveldb::DescriptorFileName("db", maxVal);
  EXPECT_EQ(result, "db/MANIFEST-18446744073709551615");
}
