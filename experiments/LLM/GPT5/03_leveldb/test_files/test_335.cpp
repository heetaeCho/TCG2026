// db/filename_old_info_log_unittest.cc
#include <gtest/gtest.h>
#include <string>

namespace leveldb {
// Interface under test (provided elsewhere in the codebase).
// We only declare it here to compile tests; linking will resolve the symbol.
std::string OldInfoLogFileName(const std::string& dbname);
}  // namespace leveldb

// Normal operation: typical DB directory path.
TEST(OldInfoLogFileNameTest_335, AppendsSuffixToDbDir_335) {
  const std::string db = "testdb";
  const std::string expected = "testdb/LOG.old";
  EXPECT_EQ(leveldb::OldInfoLogFileName(db), expected);
}

// Boundary: empty dbname should yield just the leading slash plus suffix.
TEST(OldInfoLogFileNameTest_335, EmptyDbName_YieldsLeadingSlash_335) {
  const std::string db;
  const std::string expected = "/LOG.old";
  EXPECT_EQ(leveldb::OldInfoLogFileName(db), expected);
}

// Boundary: trailing slash in input should be preserved (no path normalization).
TEST(OldInfoLogFileNameTest_335, PreservesTrailingSlash_335) {
  const std::string db = "path/with/trailing/";
  const std::string expected = "path/with/trailing//LOG.old";  // double slash is observable behavior
  EXPECT_EQ(leveldb::OldInfoLogFileName(db), expected);
}

// Edge characters: spaces, unicode, and backslashes should be passed through unchanged.
TEST(OldInfoLogFileNameTest_335, SupportsUnicodeAndSpaces_335) {
  const std::string db = u8"데이터 폴더/Project A\\Beta";
  const std::string expected = u8"데이터 폴더/Project A\\Beta/LOG.old";
  EXPECT_EQ(leveldb::OldInfoLogFileName(db), expected);
}

// Observable behavior: function must not mutate the input string.
TEST(OldInfoLogFileNameTest_335, DoesNotAlterInput_335) {
  std::string db = "unchanged_dir";
  const std::string original = db;
  (void)leveldb::OldInfoLogFileName(db);
  EXPECT_EQ(db, original);
}

// Stress/boundary: very long input should be handled without truncation.
TEST(OldInfoLogFileNameTest_335, HandlesVeryLongDbName_335) {
  std::string long_db(10000, 'a');  // 10k 'a's
  const std::string expected = long_db + "/LOG.old";
  const std::string actual = leveldb::OldInfoLogFileName(long_db);
  ASSERT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual, expected);
}
