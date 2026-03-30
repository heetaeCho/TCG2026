// filename_logfile_test_327.cc
#include <gtest/gtest.h>
#include <string>
#include <limits>

namespace leveldb {
// Forward declaration from the production code.
std::string LogFileName(const std::string& dbname, uint64_t number);
}

class FilenameTest_327 : public ::testing::Test {};

// Normal operation: returns a non-empty string that reflects the "log" suffix in some observable way.
TEST(FilenameTest_327, ReturnsStringContainingLogSuffix_327) {
  std::string name = leveldb::LogFileName("testdb", 1);
  EXPECT_FALSE(name.empty());
  // We avoid asserting any specific formatting; we only check that "log" appears somewhere,
  // since LogFileName delegates with the "log" suffix.
  EXPECT_NE(name.find("log"), std::string::npos);
}

// Normal operation: different numbers should reasonably yield different results (observable via return value).
TEST(FilenameTest_327, DifferentNumbersYieldDifferentNames_327) {
  std::string a = leveldb::LogFileName("testdb", 1);
  std::string b = leveldb::LogFileName("testdb", 2);
  EXPECT_NE(a, b);
}

// Boundary condition: empty database name is allowed; still should produce a non-empty result indicating "log".
TEST(FilenameTest_327, EmptyDbNameStillProducesLogFileName_327) {
  std::string name = leveldb::LogFileName("", 7);
  EXPECT_FALSE(name.empty());
  EXPECT_NE(name.find("log"), std::string::npos);
}

// Boundary condition: very large file number should still work and produce a (non-empty) name.
TEST(FilenameTest_327, LargeNumberSupported_327) {
  const uint64_t big = std::numeric_limits<uint64_t>::max();
  std::string name = leveldb::LogFileName("bigdb", big);
  EXPECT_FALSE(name.empty());
  EXPECT_NE(name.find("log"), std::string::npos);
}

// Exceptional case: number == 0 violates the documented assert(number > 0).
TEST(FilenameTest_327, ZeroNumberTriggersAssert_327) {
#ifdef NDEBUG
  GTEST_SKIP() << "Assertions are disabled in release builds; skipping death test.";
#else
  EXPECT_DEATH(
      {
        // Use a lambda scope to avoid any undefined behavior leaking outside.
        (void)leveldb::LogFileName("db", 0);
      },
      "");  // No regex requirement; just assert that it dies.
#endif
}
