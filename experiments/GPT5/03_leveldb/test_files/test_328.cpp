// filename_table_test_328.cc
#include <gtest/gtest.h>
#include <string>
#include <cstdint>

namespace leveldb {
// Forward declarations from the production code.
std::string TableFileName(const std::string& dbname, uint64_t number);
std::string MakeFileName(const std::string& dbname, uint64_t number, const char* suffix);
}  // namespace leveldb

using leveldb::MakeFileName;
using leveldb::TableFileName;

// Normal operation: result equality against the known interface collaborator (MakeFileName).
TEST(TableFileNameTest_328, MatchesMakeFileNameForTypicalInput_328) {
  const std::string db = "testdb";
  const uint64_t number = 123;
  const std::string expected = MakeFileName(db, number, "ldb");

  EXPECT_EQ(TableFileName(db, number), expected);
}

// Boundary condition: smallest valid number (> 0).
TEST(TableFileNameTest_328, BoundaryNumberOne_328) {
  const std::string db = "mydb";
  const uint64_t number = 1;
  const std::string expected = MakeFileName(db, number, "ldb");

  EXPECT_EQ(TableFileName(db, number), expected);
}

// Path-like db name: ensure behavior is consistent regardless of dbname form.
TEST(TableFileNameTest_328, PathLikeDbName_328) {
  const std::string db = "foo/bar/baz";
  const uint64_t number = 42;
  const std::string expected = MakeFileName(db, number, "ldb");

  EXPECT_EQ(TableFileName(db, number), expected);
}

// Large number: verify handling of big identifiers without assuming formatting details.
TEST(TableFileNameTest_328, LargeNumber_328) {
  const std::string db = "bigdb";
  const uint64_t number = 18446744073709551615ull; // UINT64_MAX
  const std::string expected = MakeFileName(db, number, "ldb");

  EXPECT_EQ(TableFileName(db, number), expected);
}

// Exceptional/error case (observable via assertion in debug builds).
#ifndef NDEBUG
TEST(TableFileNameDeathTest_328, AssertsOnZeroNumber_328) {
  // In debug builds, the function asserts for number == 0.
  EXPECT_DEATH(
      {
        // Use a lambda/body to satisfy EXPECT_DEATH requirements.
        (void)TableFileName("db", 0);
      },
      "");  // No specific regex: just verify that it dies.
}
#endif
