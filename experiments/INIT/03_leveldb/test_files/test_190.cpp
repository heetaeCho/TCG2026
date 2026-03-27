// File: dbformat_find_shortest_separator_test_190.cc
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::AllOf;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Property;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace leveldb {

class MockComparator : public Comparator {
 public:
  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit), (const, override));
  MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (const, override));
};

// Helper: build a minimal “internal key”-shaped string without relying on any
// private helpers. We simply append 8 bytes so that if the implementation
// expects an internal-key layout (user key + 8-byte tag), ExtractUserKey can
// safely read the user part. The exact tag contents are irrelevant here.
static std::string MakeInternalKey(const std::string& user_key) {
  return user_key + std::string(8, '\0');
}

// --- Tests ---

// No change when user comparator doesn't shorten `tmp`
// Expectation: start remains byte-for-byte identical.
TEST(InternalKeyComparator_FindShortestSeparator_190, NoChangeWhenTmpNotShorter_190) {
  MockComparator user_cmp;

  // Default behavior to avoid surprises
  ON_CALL(user_cmp, Name).WillByDefault(Return("mock"));
  ON_CALL(user_cmp, Compare).WillByDefault(Return(0));
  // Do NOT modify tmp; leaves it identical to user_start.
  EXPECT_CALL(
      user_cmp,
      FindShortestSeparator(
          _, AllOf(Property(&Slice::ToString, ::testing::Eq("abz")))))
      .WillOnce(Invoke([](std::string* tmp, const Slice& /*limit*/) {
        // leave *tmp as-is
      }));

  InternalKeyComparator ikc(&user_cmp);

  std::string start = MakeInternalKey("abc");
  const std::string original_start = start;
  Slice limit(MakeInternalKey("abz"));

  ikc.FindShortestSeparator(&start, limit);

  EXPECT_EQ(start, original_start) << "start must not change when tmp is not shorter";
}

// No change when tmp is shorter but NOT considered greater by user comparator
// (i.e., user comparator Compare(user_start, tmp) >= 0).
TEST(InternalKeyComparator_FindShortestSeparator_190, NoChangeWhenTmpNotGreater_190) {
  MockComparator user_cmp;

  ON_CALL(user_cmp, Name).WillByDefault(Return("mock"));
  // The only comparison that matters here: user_start ("abc") vs tmp ("ab")
  EXPECT_CALL(user_cmp, Compare(
      AllOf(Property(&Slice::ToString, ::testing::Eq("abc"))),
      AllOf(Property(&Slice::ToString, ::testing::Eq("ab")))))
      .WillOnce(Return(1));  // NOT less than 0 => condition fails

  // Shorten tmp from "abc" -> "ab"
  EXPECT_CALL(user_cmp,
              FindShortestSeparator(
                  _, AllOf(Property(&Slice::ToString, ::testing::Eq("abz")))))
      .WillOnce(Invoke([](std::string* tmp, const Slice& /*limit*/) {
        *tmp = "ab";
      }));

  InternalKeyComparator ikc(&user_cmp);

  std::string start = MakeInternalKey("abc");
  const std::string original_start = start;
  Slice limit(MakeInternalKey("abz"));

  ikc.FindShortestSeparator(&start, limit);

  // Because Compare(user_start, tmp) >= 0, start must remain unchanged.
  EXPECT_EQ(start, original_start);
}

// Update occurs when tmp is shorter AND user comparator considers tmp greater
// than user_start (Compare(user_start, tmp) < 0). We verify that:
// - start is swapped (updated).
// - the updated start begins with the new tmp ("ab") and has an 8-byte trailer.
TEST(InternalKeyComparator_FindShortestSeparator_190, UpdatesWhenShorterAndGreater_190) {
  MockComparator user_cmp;

  ON_CALL(user_cmp, Name).WillByDefault(Return("mock"));

  // user comparator shortens "abc" -> "ab"
  EXPECT_CALL(user_cmp,
              FindShortestSeparator(
                  _, AllOf(Property(&Slice::ToString, ::testing::Eq("abz")))))
      .WillOnce(Invoke([](std::string* tmp, const Slice& /*limit*/) {
        *tmp = "ab";
      }));

  // The crucial gate: user_start ("abc") vs tmp ("ab") must be < 0 to permit update.
  EXPECT_CALL(user_cmp, Compare(
      AllOf(Property(&Slice::ToString, ::testing::Eq("abc"))),
      AllOf(Property(&Slice::ToString, ::testing::Eq("ab")))))
      .WillOnce(Return(-1));

  InternalKeyComparator ikc(&user_cmp);

  std::string start = MakeInternalKey("abc");
  Slice limit(MakeInternalKey("abz"));

  ikc.FindShortestSeparator(&start, limit);

  // After update, start should be tmp ("ab") + 8-byte trailer.
  ASSERT_GE(start.size(), static_cast<size_t>(2)) << "start must be at least 'ab' + tag";
  EXPECT_EQ(start.substr(0, 2), "ab");
  EXPECT_EQ(start.size(), static_cast<size_t>(2 + 8))
      << "updated internal key should be user-part ('ab') plus 8-byte tag";
}

// Delegation: Ensure the user comparator is called with user-only slices,
// even when limit is empty (edge/boundary behavior).
TEST(InternalKeyComparator_FindShortestSeparator_190, DelegatesWithEmptyLimit_190) {
  MockComparator user_cmp;

  ON_CALL(user_cmp, Name).WillByDefault(Return("mock"));
  // When limit is empty, still expect a call; implementation passes user_limit.
  EXPECT_CALL(
      user_cmp,
      FindShortestSeparator(
          _, AllOf(Property(&Slice::size, ::testing::Eq(static_cast<size_t>(0))))))
      .WillOnce(Invoke([](std::string* tmp, const Slice& /*limit*/) {
        // leave tmp unchanged
      }));

  InternalKeyComparator ikc(&user_cmp);

  std::string start = MakeInternalKey("key");
  Slice empty_limit;  // default-constructed: empty

  const std::string original_start = start;
  ikc.FindShortestSeparator(&start, empty_limit);

  // No change expected because tmp wasn't shortened.
  EXPECT_EQ(start, original_start);
}

}  // namespace leveldb
