// File: find_smallest_boundary_file_test_175.cc
#include <gtest/gtest.h>
#include <vector>
#include <memory>

#include "leveldb/comparator.h"
#include "db/dbformat.h"
#include "db/version_edit.h"

// Forward declaration of the function under test (implemented in version_set.cc)
namespace leveldb {
FileMetaData* FindSmallestBoundaryFile(
    const InternalKeyComparator& icmp,
    const std::vector<FileMetaData*>& level_files,
    const InternalKey& largest_key);
}

// --------- Test Fixture ---------
class FindSmallestBoundaryFileTest_175 : public ::testing::Test {
protected:
  const leveldb::Comparator* user_cmp_ = leveldb::BytewiseComparator();
  leveldb::InternalKeyComparator icmp_{user_cmp_};

  // Helper to make an InternalKey with a given user-key and sequence.
  // We use kTypeValue consistently; tests rely only on observable ordering.
  leveldb::InternalKey IKey(const std::string& user, leveldb::SequenceNumber seq) {
    return leveldb::InternalKey(leveldb::Slice(user), seq, leveldb::kTypeValue);
  }

  // Helper to create a FileMetaData whose `smallest` = ikey
  std::unique_ptr<leveldb::FileMetaData> MakeFile(const leveldb::InternalKey& smallest) {
    auto f = std::make_unique<leveldb::FileMetaData>();
    f->smallest = smallest;
    return f;
  }
};

// ---------- Tests ----------

// Empty input -> nullptr
TEST_F(FindSmallestBoundaryFileTest_175, ReturnsNullptrOnEmptyInput_175) {
  std::vector<leveldb::FileMetaData*> files;
  leveldb::InternalKey largest = IKey("a", /*seq=*/200);

  auto* found = leveldb::FindSmallestBoundaryFile(icmp_, files, largest);
  EXPECT_EQ(found, nullptr);
}

// No user-key match -> nullptr
TEST_F(FindSmallestBoundaryFileTest_175, ReturnsNullptrWhenNoUserKeyMatches_175) {
  auto f1 = MakeFile(IKey("b", 100)); // different user key than "a"
  std::vector<leveldb::FileMetaData*> files = { f1.get() };

  leveldb::InternalKey largest = IKey("a", 200);

  auto* found = leveldb::FindSmallestBoundaryFile(icmp_, files, largest);
  EXPECT_EQ(found, nullptr);
}

// Found candidate must have same user key AND strictly greater internal key
// For same user key, LevelDB internal-key ordering is by seq DESC; so
// f.smallest > largest_key when f.seq < largest.seq.
TEST_F(FindSmallestBoundaryFileTest_175, FindsBoundaryWhenSameUserKeyAndStrictlyGreater_175) {
  // largest user key "a", seq 200
  leveldb::InternalKey largest = IKey("a", 200);

  // Candidate with same user key "a" and seq 100 -> strictly greater than largest
  auto f_ok = MakeFile(IKey("a", 100));

  // A non-candidate with different user key
  auto f_other = MakeFile(IKey("b", 500));

  std::vector<leveldb::FileMetaData*> files = { f_other.get(), f_ok.get() };

  auto* found = leveldb::FindSmallestBoundaryFile(icmp_, files, largest);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, f_ok.get());
}

// Must be strictly greater; equal (not >) should NOT match
TEST_F(FindSmallestBoundaryFileTest_175, DoesNotMatchWhenEqualInternalKey_175) {
  // Equal internal key to largest -> not strictly greater
  leveldb::InternalKey largest = IKey("a", 200);
  auto f_equal = MakeFile(IKey("a", 200));  // equal

  std::vector<leveldb::FileMetaData*> files = { f_equal.get() };

  auto* found = leveldb::FindSmallestBoundaryFile(icmp_, files, largest);
  EXPECT_EQ(found, nullptr);
}

// Multiple valid candidates: pick the one with the smallest `smallest` key (closest above)
// For same user key "a": 150 and 120 are both > 200? No. Recall: higher seq sorts smaller.
// So to be > largest(200), candidate seq must be < 200; among candidates, the one with
// the larger seq (but still < 200) is actually "smaller" in internal-key ordering,
// so the chosen "smallest boundary" should be the one with the highest seq below 200.
// This test asserts the function picks that one.
TEST_F(FindSmallestBoundaryFileTest_175, PicksSmallestAmongMultipleCandidates_175) {
  leveldb::InternalKey largest = IKey("a", 200);

  // All same user key "a"; all seq < 200, so each is a boundary candidate.
  // Among 150, 120, and 50: by internal-key ordering (seq DESC), 150 < 120 < 50.
  // "Smallest" boundary (closest just above 'largest') is the one with seq 150.
  auto f1 = MakeFile(IKey("a", 150)); // should be selected
  auto f2 = MakeFile(IKey("a", 120));
  auto f3 = MakeFile(IKey("a", 50));
  auto f_other_user = MakeFile(IKey("b", 10)); // ignored

  std::vector<leveldb::FileMetaData*> files = { f3.get(), f_other_user.get(), f2.get(), f1.get() };

  auto* found = leveldb::FindSmallestBoundaryFile(icmp_, files, largest);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, f1.get());
}

// Candidate with same user key but NOT greater (seq > largest.seq -> smaller in internal order)
// should not be returned.
TEST_F(FindSmallestBoundaryFileTest_175, SameUserKeyButNotStrictlyGreater_175) {
  leveldb::InternalKey largest = IKey("a", 100);

  // seq 300 with same user key "a": in internal order, higher seq is "smaller", so not > largest
  auto f_not_greater = MakeFile(IKey("a", 300));
  std::vector<leveldb::FileMetaData*> files = { f_not_greater.get() };

  auto* found = leveldb::FindSmallestBoundaryFile(icmp_, files, largest);
  EXPECT_EQ(found, nullptr);
}
