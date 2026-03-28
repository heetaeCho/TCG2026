// filename_descriptor_test_330.cc
#include "gtest/gtest.h"
#include <string>
#include <cstdint>

// Declaration from the provided snippet (treating implementation as black box)
namespace leveldb {
std::string DescriptorFileName(const std::string& dbname, uint64_t number);
}

// Normal operation: minimal positive number should be zero-padded to 6 digits.
TEST(DescriptorFileNameTest_330, ReturnsCorrectPath_MinNumber_330) {
  const std::string db = "/tmp/testdb";
  const std::string got = leveldb::DescriptorFileName(db, 1);
  EXPECT_EQ("/tmp/testdb/MANIFEST-000001", got);
}

// Normal operation: verify zero-padding to width 6 for small numbers.
TEST(DescriptorFileNameTest_330, ZeroPaddingToSixDigits_330) {
  const std::string db = "/var/data";
  const std::string got = leveldb::DescriptorFileName(db, 42);
  EXPECT_EQ("/var/data/MANIFEST-000042", got);
}

// Boundary: exactly six digits should not add extra padding.
TEST(DescriptorFileNameTest_330, ExactlySixDigits_NoExtraPadding_330) {
  const std::string db = "/var/db";
  const std::string got = leveldb::DescriptorFileName(db, 123456);
  EXPECT_EQ("/var/db/MANIFEST-123456", got);
}

// Boundary: more than six digits should not be truncated.
TEST(DescriptorFileNameTest_330, MoreThanSixDigits_NoTruncation_330) {
  const std::string db = "/db";
  const std::string got = leveldb::DescriptorFileName(db, 1000000ULL);
  EXPECT_EQ("/db/MANIFEST-1000000", got);
}

// Normal operation: preserves and concatenates the provided dbname path verbatim.
TEST(DescriptorFileNameTest_330, PreservesDbnamePrefix_330) {
  const std::string db = "/custom/path with spaces";
  const std::string got = leveldb::DescriptorFileName(db, 7);
  EXPECT_EQ("/custom/path with spaces/MANIFEST-000007", got);
}

// Exceptional case (observable via assert): number == 0 should trigger a debug assertion.
// Guarded so it only builds/runs in non-NDEBUG builds.
#ifndef NDEBUG
TEST(DescriptorFileNameTest_330, AssertsOnZeroNumber_330) {
  EXPECT_DEATH({ (void)leveldb::DescriptorFileName("/db", 0); }, "");
}
#endif
