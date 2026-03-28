// filename_sst_table_unittest.cc
#include <gtest/gtest.h>
#include <regex>
#include <string>

namespace leveldb {
// Forward declaration based on the provided interface snippet.
std::string SSTTableFileName(const std::string& dbname, uint64_t number);
}  // namespace leveldb

// Test suite for SSTTableFileName
class SSTTableFileNameTest_329 : public ::testing::Test {};

// Normal operation: result should end with ".sst".
TEST_F(SSTTableFileNameTest_329, ReturnsSstExtension_329) {
  const std::string db = "path/to/db";
  const uint64_t num = 123;
  const std::string result = leveldb::SSTTableFileName(db, num);

  // Observable property: extension is ".sst"
  ASSERT_GE(result.size(), 4u);
  EXPECT_EQ(result.substr(result.size() - 4), ".sst");
}

// Normal operation: result should include the DB path as a prefix component.
TEST_F(SSTTableFileNameTest_329, IncludesDbPath_329) {
  const std::string db = "path/to/db";
  const uint64_t num = 42;
  const std::string result = leveldb::SSTTableFileName(db, num);

  // Expect returned path starts with "<dbname>/" (path join behavior observable)
  EXPECT_TRUE(result.rfind(db + "/", 0) == 0) << "Got: " << result;
}

// Boundary condition: smallest valid number formats into an .sst file name.
// We do NOT assume exact zero-padding width—only that the numeric
// representation (possibly zero-padded) ends with ".sst".
TEST_F(SSTTableFileNameTest_329, FormatsSmallNumberWithOptionalPadding_329) {
  const std::string db = "mydb";
  const uint64_t num = 1;
  const std::string result = leveldb::SSTTableFileName(db, num);

  // Accept any amount of leading zeros before "1.sst"
  // and require the db prefix.
  std::regex re("^" + db + "/0*1\\.sst$");
  EXPECT_TRUE(std::regex_match(result, re)) << "Got: " << result;
}

// Large number: should appear (without unexpected truncation) before ".sst".
TEST_F(SSTTableFileNameTest_329, FormatsLargeNumber_329) {
  const std::string db = "bigdb";
  const uint64_t num = std::numeric_limits<uint64_t>::max(); // 18446744073709551615
  const std::string result = leveldb::SSTTableFileName(db, num);

  // Expect "<db>/<number>.sst" where <number> is the full decimal of num.
  const std::string expected_suffix = std::to_string(num) + ".sst";
  ASSERT_GE(result.size(), expected_suffix.size());
  EXPECT_EQ(result.substr(result.size() - expected_suffix.size()), expected_suffix);
  EXPECT_TRUE(result.rfind(db + "/", 0) == 0) << "Got: " << result;
}

// Exceptional case (observable via assert): number must be > 0.
// Use a death test to validate the assertion in debug builds.
#ifndef NDEBUG
TEST_F(SSTTableFileNameTest_329, DeathOnZeroNumber_329) {
  // Death tests run the statement in a sub-process and expect abnormal termination.
  EXPECT_DEATH(
      {
        (void)leveldb::SSTTableFileName("anydb", 0);
      },
      "");  // No specific regex on the message; just that it dies.
}
#endif
