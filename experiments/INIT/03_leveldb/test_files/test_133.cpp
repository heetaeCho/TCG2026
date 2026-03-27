// before_file_test_133.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <set>
#include <string>

#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "db/version_edit.h"
#include "db/dbformat.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Truly;

namespace leveldb {

// Forward-declare the function under test as exposed by the partial code.
// (Treating it as part of the public/visible interface per prompt.)
bool BeforeFile(const Comparator* ucmp, const Slice* user_key, const FileMetaData* f);

// Minimal Google Mock for Comparator: only Compare is used by BeforeFile.
class MockComparator : public Comparator {
 public:
  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));

  // Provide default (unused) implementations to satisfy vtable, without assumptions.
  const char* Name() const override { return "MockComparator"; }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// Small helper for matching Slice equality by content (no internal state access).
static auto SliceEq(const Slice& expected) {
  return Truly([&expected](const Slice& actual) {
    return actual.size() == expected.size() &&
           std::string(actual.data(), actual.size()) ==
               std::string(expected.data(), expected.size());
  });
}

// -------------------- Tests --------------------

TEST(BeforeFileTest_133, ReturnsFalseWhenUserKeyIsNull_133) {
  MockComparator cmp;
  // Comparator must not be called when user_key is null. Be permissive: no EXPECT_CALL.
  FileMetaData meta;                   // Treat as black box; default-constructed is fine.
  const Slice* user_key_ptr = nullptr; // Boundary condition: null user_key.

  const bool result = BeforeFile(&cmp, user_key_ptr, &meta);
  EXPECT_FALSE(result);
}

TEST(BeforeFileTest_133, ReturnsTrueWhenCompareIsNegative_133) {
  MockComparator cmp;

  // Arrange: Make comparator report user_key < smallest.user_key()
  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(-1));

  FileMetaData meta;  // No assumptions about internal members.
  Slice user_key("u"); // Any value; behavior is dictated by mocked Compare.

  const bool result = BeforeFile(&cmp, &user_key, &meta);
  EXPECT_TRUE(result);
}

TEST(BeforeFileTest_133, ReturnsFalseWhenCompareIsZero_133) {
  MockComparator cmp;

  // Arrange: user_key == smallest.user_key()
  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(0));

  FileMetaData meta;
  Slice user_key("u");

  const bool result = BeforeFile(&cmp, &user_key, &meta);
  EXPECT_FALSE(result);
}

TEST(BeforeFileTest_133, ReturnsFalseWhenCompareIsPositive_133) {
  MockComparator cmp;

  // Arrange: user_key > smallest.user_key()
  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(1));

  FileMetaData meta;
  Slice user_key("u");

  const bool result = BeforeFile(&cmp, &user_key, &meta);
  EXPECT_FALSE(result);
}

TEST(BeforeFileTest_133, ComparatorReceivesExpectedArguments_133) {
  MockComparator cmp;

  // We verify the two arguments passed into Compare():
  //   - First is exactly the provided user_key (by value semantics via SliceEq).
  //   - Second is the file's smallest.user_key() (observed through the public API).
  FileMetaData meta;
  const Slice file_smallest_user_key = meta.smallest.user_key(); // Observable via public method.
  const Slice user_key("abc");

  EXPECT_CALL(cmp, Compare(SliceEq(user_key), SliceEq(file_smallest_user_key)))
      .WillOnce(Return(-1)); // Also drives a 'true' result to avoid additional assumptions.

  const bool result = BeforeFile(&cmp, &user_key, &meta);
  EXPECT_TRUE(result);
}

}  // namespace leveldb
