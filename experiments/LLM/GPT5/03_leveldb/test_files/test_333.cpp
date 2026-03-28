// File: db/filename_temp_unittest.cc

#include "gtest/gtest.h"
#include <cstdint>
#include <limits>
#include <string>

// Assuming MakeFileName and TempFileName are declared in this header
#include "db/filename.h"

namespace leveldb {

// Normal operation: should exactly match MakeFileName(..., "dbtmp")
TEST(TempFileNameTest_333, ReturnsMakeFileNameEquivalent_333) {
  const std::string db = "/tmp/testdb";
  const uint64_t number = 7;
  const std::string expected = MakeFileName(db, number, "dbtmp");

  EXPECT_EQ(TempFileName(db, number), expected);
}

// Boundary: minimal valid number (1)
TEST(TempFileNameTest_333, MinimalValidNumber_333) {
  const std::string db = "min-db";
  const uint64_t number = 1;
  const std::string expected = MakeFileName(db, number, "dbtmp");

  EXPECT_EQ(TempFileName(db, number), expected);
}

// Boundary: very large number
TEST(TempFileNameTest_333, VeryLargeNumber_333) {
  const std::string db = "big-db";
  const uint64_t number = std::numeric_limits<uint64_t>::max();
  const std::string expected = MakeFileName(db, number, "dbtmp");

  EXPECT_EQ(TempFileName(db, number), expected);
}

// Boundary: empty database name (if allowed by interface)
TEST(TempFileNameTest_333, EmptyDbName_333) {
  const std::string db;  // ""
  const uint64_t number = 123;
  const std::string expected = MakeFileName(db, number, "dbtmp");

  EXPECT_EQ(TempFileName(db, number), expected);
}

// Boundary: db name with spaces, punctuation, unicode path segments
TEST(TempFileNameTest_333, DbNameWithSpecialCharacters_333) {
  const std::string db = "weird path/子-._ db";
  const uint64_t number = 42;
  const std::string expected = MakeFileName(db, number, "dbtmp");

  EXPECT_EQ(TempFileName(db, number), expected);
}

// Exceptional case: asserts on number == 0 (observable via death test in debug)
#ifndef NDEBUG
TEST(TempFileNameTest_333, AssertsOnZeroNumber_333) {
  // We cannot observe internal state; we only verify that passing 0 triggers the assertion.
  EXPECT_DEATH(TempFileName("any-db", 0), "");
}
#endif  // NDEBUG

}  // namespace leveldb
