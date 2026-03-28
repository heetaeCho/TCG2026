// filename_makefile_test_326.cc
#include <gtest/gtest.h>
#include <limits>
#include <string>

// Include the implementation directly so we can call the internal static function.
// This keeps the class/function under test as a black box and avoids re-implementing logic.
#include "db/filename.cc"

namespace {

using leveldb::MakeFileName;

class FilenameMakeFileNameTest_326 : public ::testing::Test {};

// Normal operation: common suffix and small number
TEST_F(FilenameMakeFileNameTest_326, FormatsLogName_326) {
  const std::string db = "testdb";
  const auto got = MakeFileName(db, /*number=*/1, "log");
  EXPECT_EQ(got, "testdb/000001.log");
}

// Zero padding: verify 6-digit padding for small numbers
TEST_F(FilenameMakeFileNameTest_326, ZeroPaddingSixDigits_1And42_326) {
  EXPECT_EQ(MakeFileName("db", 1, "sst"),  "db/000001.sst");
  EXPECT_EQ(MakeFileName("db", 42, "ldb"), "db/000042.ldb");
}

// Boundary: exactly 6 digits remains as-is (no extra zeros)
TEST_F(FilenameMakeFileNameTest_326, BoundaryExactlySixDigits_326) {
  EXPECT_EQ(MakeFileName("db", 999999, "log"), "db/999999.log");
}

// Boundary: more than 6 digits should still render fully (width is minimum)
TEST_F(FilenameMakeFileNameTest_326, BeyondSixDigits_326) {
  EXPECT_EQ(MakeFileName("db", 1000000, "sst"), "db/1000000.sst");
}

// Empty DB name is allowed — path should start with '/'
TEST_F(FilenameMakeFileNameTest_326, EmptyDbName_326) {
  EXPECT_EQ(MakeFileName("", 123, "sst"), "/000123.sst");
}

// Empty suffix — trailing dot remains present
TEST_F(FilenameMakeFileNameTest_326, EmptySuffix_326) {
  EXPECT_EQ(MakeFileName("path", 7, ""), "path/000007.");
}

// Suffix that already contains a leading dot — function does not sanitize
TEST_F(FilenameMakeFileNameTest_326, SuffixWithLeadingDot_326) {
  EXPECT_EQ(MakeFileName("path", 1, ".meta"), "path/000001..meta");
}

// Large number: ensure it formats completely without truncation
TEST_F(FilenameMakeFileNameTest_326, LargeNumberMaxUint64_326) {
  const uint64_t num = std::numeric_limits<uint64_t>::max();
  const std::string expected = std::string("dir/") + std::to_string(num) + ".log";
  EXPECT_EQ(MakeFileName("dir", num, "log"), expected);
}

}  // namespace
