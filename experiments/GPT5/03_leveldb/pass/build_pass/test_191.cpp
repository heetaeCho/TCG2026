// File: dbformat_find_short_successor_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/dbformat.h"   // InternalKeyComparator (public interface)
#include "leveldb/slice.h" // Slice (public interface)
#include "leveldb/comparator.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

class MockComparator : public Comparator {
 public:
  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit), (const, override));
  MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (const, override));
};

class InternalKeyComparatorTest_191 : public ::testing::Test {
 protected:
  std::string MakeInternalLike(const std::string& user_key) {
    // Build an "internal-like" key: user part + 8 trailing bytes.
    // We do not assume or re-implement internal encoding; we just provide
    // a plausible string input that the method can operate on.
    return user_key + std::string(8, '\x00');
  }
};

TEST_F(InternalKeyComparatorTest_191, NoChangeWhenUserComparatorDoesNotShorten_191) {
  StrictMock<MockComparator> user_cmp;
  InternalKeyComparator ikc(&user_cmp);

  // Name is typically queried by infra; provide a safe default.
  ON_CALL(user_cmp, Name()).WillByDefault(Return("mock"));

  std::string key = MakeInternalLike("abc");
  const std::string original = key;

  // User comparator does not change the user-key successor (keeps same length).
  EXPECT_CALL(user_cmp, FindShortSuccessor(_))
      .WillOnce(Invoke([](std::string* s) {
        // leave as-is (no change)
      }));

  // Since no shortening happened, Compare() need not be called. No expectation.

  ikc.FindShortSuccessor(&key);

  // Observable behavior: key remains unchanged.
  EXPECT_EQ(key, original);
}

TEST_F(InternalKeyComparatorTest_191, ChangesWhenShorterAndUserOrderIncreases_191) {
  StrictMock<MockComparator> user_cmp;
  InternalKeyComparator ikc(&user_cmp);
  ON_CALL(user_cmp, Name()).WillByDefault(Return("mock"));

  // Start with user part "abcd"
  std::string key = MakeInternalLike("abcd");
  const std::string original = key;

  // 1) user comparator shortens successor from "abcd" -> "ab" (strictly shorter)
  EXPECT_CALL(user_cmp, FindShortSuccessor(_))
      .WillOnce(Invoke([](std::string* s) {
        // s initially holds a copy of the user key. We shorten it.
        *s = "ab";
      }));

  // 2) user comparator ordering says original user key ("abcd") < shortened ("ab").
  //    We only define semantics necessary for this comparison.
  EXPECT_CALL(user_cmp, Compare(_, _))
      .WillOnce(Invoke([](const Slice& a, const Slice& b) {
        // If a == "abcd" and b == "ab", return < 0 to indicate a < b
        const std::string as(a.data(), a.size());
        const std::string bs(b.data(), b.size());
        if (as == "abcd" && bs == "ab") return -1;
        return 0;
      }));

  ikc.FindShortSuccessor(&key);

  // Observable effects:

  // a) The key should have changed.
  EXPECT_NE(key, original);

  // b) The new key starts with the user comparator's shortened result "ab".
  ASSERT_GE(key.size(), static_cast<size_t>(2));
  EXPECT_EQ(key.compare(0, 2, "ab"), 0);

  // c) The new key size should be prefix ("ab") + 8 trailing bytes.
  EXPECT_EQ(key.size(), std::string("ab").size() + 8);

  // d) According to the InternalKeyComparator's public Compare, original < new.
  EXPECT_LT(ikc.Compare(Slice(original), Slice(key)), 0);
}

TEST_F(InternalKeyComparatorTest_191, NoChangeWhenShorterButNotGreaterInUserOrder_191) {
  StrictMock<MockComparator> user_cmp;
  InternalKeyComparator ikc(&user_cmp);
  ON_CALL(user_cmp, Name()).WillByDefault(Return("mock"));

  std::string key = MakeInternalLike("abcd");
  const std::string original = key;

  // Shorten from "abcd" -> "ab"
  EXPECT_CALL(user_cmp, FindShortSuccessor(_))
      .WillOnce(Invoke([](std::string* s) { *s = "ab"; }));

  // But now define user ordering so that user_key ("abcd") is NOT less than "ab"
  // (e.g., equal or greater). Return >= 0 — here we choose +1.
  EXPECT_CALL(user_cmp, Compare(_, _))
      .WillOnce(Return(+1));

  ikc.FindShortSuccessor(&key);

  // Because user order didn't increase, observable behavior: no change.
  EXPECT_EQ(key, original);
}

TEST_F(InternalKeyComparatorTest_191, EmptyUserKeyBoundary_NoChange_191) {
  StrictMock<MockComparator> user_cmp;
  InternalKeyComparator ikc(&user_cmp);
  ON_CALL(user_cmp, Name()).WillByDefault(Return("mock"));

  // Internal-like key with empty user portion (just 8 trailing bytes).
  std::string key = MakeInternalLike("");
  const std::string original = key;

  // User comparator can't shorten an empty key to a smaller (strictly shorter) key.
  EXPECT_CALL(user_cmp, FindShortSuccessor(_))
      .WillOnce(Invoke([](std::string* s) {
        // leave as-is (still empty)
      }));

  ikc.FindShortSuccessor(&key);

  // Observable behavior: unchanged.
  EXPECT_EQ(key, original);
}

} // namespace leveldb
