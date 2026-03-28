// ExtractUserKey_test_48.cc
#include <gtest/gtest.h>
#include <string>
#include "db/dbformat.h"
#include "leveldb/slice.h"

using leveldb::Slice;
using leveldb::ExtractUserKey;

class ExtractUserKeyTest_48 : public ::testing::Test {};

// Normal operation: returns the prefix excluding the last 8 bytes trailer
TEST_F(ExtractUserKeyTest_48, ReturnsPrefixWithoutTrailer_48) {
  const std::string user = "hello-world";
  const std::string trailer(8, '\xAB');  // arbitrary trailer
  const std::string internal = user + trailer;

  Slice internal_key(internal);           // constructed from std::string
  Slice user_key = ExtractUserKey(internal_key);

  EXPECT_EQ(user.size(), user_key.size());
  EXPECT_EQ(user, user_key.ToString());
  // Observable pointer behavior: returned slice starts at same data pointer
  EXPECT_EQ(internal_key.data(), user_key.data());
}

// Boundary: exactly 8 bytes => empty user key
TEST_F(ExtractUserKeyTest_48, ExactlyEightBytesReturnsEmpty_48) {
  const std::string internal(8, '\x00');  // exactly 8 bytes
  Slice internal_key(internal);
  Slice user_key = ExtractUserKey(internal_key);

  EXPECT_TRUE(user_key.empty());
  EXPECT_EQ(static_cast<size_t>(0), user_key.size());
}

// Binary safety: handles embedded NULs and arbitrary bytes
TEST_F(ExtractUserKeyTest_48, HandlesBinaryDataWithNulls_48) {
  const char raw_user[] = {'\x00','\x01','A','\x00','Z'}; // 5 bytes
  const std::string trailer(8, '\xFF');
  std::string internal(raw_user, raw_user + sizeof(raw_user));
  internal += trailer;

  Slice internal_key(internal.data(), internal.size());
  Slice user_key = ExtractUserKey(internal_key);

  ASSERT_EQ(sizeof(raw_user), user_key.size());
  std::string recovered(user_key.data(), user_key.size());
  EXPECT_EQ(std::string(raw_user, sizeof(raw_user)), recovered);
}

// Pointer stability (non-empty): no copy; same base address
TEST_F(ExtractUserKeyTest_48, DoesNotCopyMemorySharesBasePointer_48) {
  const std::string user = "abc";
  const std::string trailer(8, 'x');
  const std::string internal = user + trailer;

  Slice internal_key(internal);
  Slice user_key = ExtractUserKey(internal_key);

  EXPECT_EQ(internal_key.data(), user_key.data());
  EXPECT_EQ(user, user_key.ToString());
}

// Error case (observable via assert): size < 8 should terminate in debug builds
TEST_F(ExtractUserKeyTest_48, DiesIfSizeLessThanEight_48) {
#if defined(NDEBUG)
  GTEST_SKIP() << "Assertions are disabled in release (NDEBUG) builds.";
#else
  const std::string internal(7, 'y');  // less than 8
  Slice internal_key(internal);
  EXPECT_DEATH({ (void)ExtractUserKey(internal_key); }, "");
#endif
}
