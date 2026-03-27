// File: internal_key_comparator_compare_slice_test_189.cc

#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "leveldb/comparator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::AllOf;
using ::testing::Return;
using ::testing::Truly;

namespace leveldb {

// A strict mock for the user comparator.
// We only care that InternalKeyComparator calls Compare(user_a, user_b)
// with the *user* parts (i.e., without the final 8-byte trailer).
class MockUserComparator : public Comparator {
 public:
  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, FindShortestSeparator,
              (std::string* start, const Slice& limit), (const, override));
  MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (const, override));
};

// Helper: builds a string that looks like an internal key for testing:
// [user_key bytes] + [8-byte trailer (filled with the same byte value)].
// We do NOT rely on any internal encoding helpers; we just ensure 8 bytes exist
// so that the comparator can read a 64-bit value from the end.
static std::string MakeInternalLike(const std::string& user, uint8_t trailer_byte) {
  std::string s = user;
  s.append(8, static_cast<char>(trailer_byte));
  return s;
}

// Matchers to verify that the Slice matches a given std::string exactly.
static auto SliceEquals(const std::string& expect) {
  return Truly([expect](const Slice& s) {
    return s.size() == expect.size() &&
           std::memcmp(s.data(), expect.data(), expect.size()) == 0;
  });
}

class InternalKeyComparatorCompareSliceTest_189 : public ::testing::Test {
 protected:
  MockUserComparator mock_user_;
  InternalKeyComparator ikc_{&mock_user_};
};

// 1) If user keys differ, the result must be exactly the user comparator's result.
TEST_F(InternalKeyComparatorCompareSliceTest_189,
       DifferentUserKeys_UsesUserComparatorResult_189) {
  const std::string user_a = "aaa";
  const std::string user_b = "bbb";

  const std::string a = MakeInternalLike(user_a, /*trailer=*/0x00);
  const std::string b = MakeInternalLike(user_b, /*trailer=*/0xFF);

  // Expect comparator to be called with the user slices only.
  EXPECT_CALL(mock_user_, Compare(SliceEquals(user_a), SliceEquals(user_b)))
      .WillOnce(Return(-7));
  EXPECT_CALL(mock_user_, Name()).Times(0);
  EXPECT_CALL(mock_user_, FindShortestSeparator(_, _)).Times(0);
  EXPECT_CALL(mock_user_, FindShortSuccessor(_)).Times(0);

  // Trailer bytes must not affect the outcome when user comparator != 0.
  EXPECT_EQ(ikc_.Compare(Slice(a), Slice(b)), -7);
}

// 2) If user keys are equal, higher sequence/tag (i.e., larger 8-byte value)
//    must sort *before* (return -1).
TEST_F(InternalKeyComparatorCompareSliceTest_189,
       SameUserKeys_HigherTrailerSortsBefore_189) {
  const std::string user = "key";
  // Build trailers so that the 64-bit value formed by 0x02..02 > 0x01..01.
  const std::string a = MakeInternalLike(user, /*trailer=*/0x02); // larger
  const std::string b = MakeInternalLike(user, /*trailer=*/0x01); // smaller

  // User comparator must return 0 for equal user keys.
  EXPECT_CALL(mock_user_, Compare(SliceEquals(user), SliceEquals(user)))
      .WillOnce(Return(0));

  EXPECT_EQ(ikc_.Compare(Slice(a), Slice(b)), -1) << "Larger trailer must come first";
}

// 3) If user keys are equal, lower sequence/tag (smaller 8-byte value)
//    must sort *after* (return +1).
TEST_F(InternalKeyComparatorCompareSliceTest_189,
       SameUserKeys_LowerTrailerSortsAfter_189) {
  const std::string user = "key";
  const std::string a = MakeInternalLike(user, /*trailer=*/0x01); // smaller
  const std::string b = MakeInternalLike(user, /*trailer=*/0x02); // larger

  EXPECT_CALL(mock_user_, Compare(SliceEquals(user), SliceEquals(user)))
      .WillOnce(Return(0));

  EXPECT_EQ(ikc_.Compare(Slice(a), Slice(b)), +1) << "Smaller trailer must come after";
}

// 4) If both user keys and trailers are equal, comparator must return 0.
TEST_F(InternalKeyComparatorCompareSliceTest_189,
       SameUserKeys_SameTrailer_ReturnsZero_189) {
  const std::string user = "same";
  const std::string a = MakeInternalLike(user, /*trailer=*/0xAB);
  const std::string b = MakeInternalLike(user, /*trailer=*/0xAB);

  EXPECT_CALL(mock_user_, Compare(SliceEquals(user), SliceEquals(user)))
      .WillOnce(Return(0));

  EXPECT_EQ(ikc_.Compare(Slice(a), Slice(b)), 0);
}

// 5) Boundary: empty user keys should still be handled correctly
//    (compare by trailers when user comparator returns 0).
TEST_F(InternalKeyComparatorCompareSliceTest_189,
       EmptyUserKeys_TrailerTiebreaker_189) {
  const std::string user;  // empty
  const std::string a = MakeInternalLike(user, /*trailer=*/0x10); // larger
  const std::string b = MakeInternalLike(user, /*trailer=*/0x0F); // smaller

  EXPECT_CALL(mock_user_, Compare(SliceEquals(user), SliceEquals(user)))
      .WillOnce(Return(0));

  EXPECT_EQ(ikc_.Compare(Slice(a), Slice(b)), -1);
}

}  // namespace leveldb
