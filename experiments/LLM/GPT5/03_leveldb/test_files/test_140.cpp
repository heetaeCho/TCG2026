// File: version_level_file_num_iterator_prev_test_140.cc

#include "gtest/gtest.h"
#include "leveldb/comparator.h"
#include "db/dbformat.h"      // leveldb::InternalKeyComparator
#include "db/version_set.h"   // leveldb::Version (and nested LevelFileNumIterator)
#include <vector>

namespace leveldb {

class LevelFileNumIteratorPrevTest_140 : public ::testing::Test {
protected:
  // Helper to create a small vector of FileMetaData* of the requested size.
  // We do not assert on any key/value; tests only observe Valid() transitions.
  static std::vector<FileMetaData*> MakeFiles(size_t n) {
    std::vector<FileMetaData*> v;
    v.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      v.push_back(new FileMetaData());
    }
    return v;
  }

  static void DeleteFiles(std::vector<FileMetaData*>& v) {
    for (auto* f : v) delete f;
    v.clear();
  }

  // Standard comparator used to satisfy constructor requirements.
  InternalKeyComparator icmp_{BytewiseComparator()};
};

// [Boundary] Empty list: iterator starts invalid; Prev on invalid should assert.
TEST_F(LevelFileNumIteratorPrevTest_140, EmptyListStartsInvalid_140) {
  std::vector<FileMetaData*> files; // size 0
  Version::LevelFileNumIterator it(icmp_, &files);

  // No movement; should be invalid on construction for empty list.
  EXPECT_FALSE(it.Valid());
}

#if GTEST_HAS_DEATH_TEST
// [Exceptional] Prev() requires Valid(); calling Prev() when invalid should DCHECK/ASSERT.
TEST_F(LevelFileNumIteratorPrevTest_140, PrevOnInvalidAsserts_140) {
  std::vector<FileMetaData*> files; // size 0 → iterator invalid
  Version::LevelFileNumIterator it(icmp_, &files);

  ASSERT_FALSE(it.Valid());
  EXPECT_DEATH({ it.Prev(); }, "");  // Expect an assertion failure.
}
#endif  // GTEST_HAS_DEATH_TEST

// [Boundary] Single element: SeekToFirst → Prev should make iterator invalid.
TEST_F(LevelFileNumIteratorPrevTest_140, PrevFromFirstOnSingleElementInvalidates_140) {
  auto files = MakeFiles(1);
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());   // At the only element (index 0)

  it.Prev();                 // From index 0 → becomes invalid per contract snippet
  EXPECT_FALSE(it.Valid());

  DeleteFiles(files);
}

// [Normal] Multi-element: SeekToLast then Prev keeps iterator valid (moves to previous).
TEST_F(LevelFileNumIteratorPrevTest_140, PrevFromLastKeepsValidWhenSizeAtLeastTwo_140) {
  auto files = MakeFiles(2);
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToLast();
  ASSERT_TRUE(it.Valid());   // At last (index size-1, which > 0 when size >= 2)

  it.Prev();                 // Should move to index-1 (>= 0) and remain valid
  EXPECT_TRUE(it.Valid());

  DeleteFiles(files);
}

// [Normal] Multi-element: Multiple Prev steps from last remain valid until moving before first.
TEST_F(LevelFileNumIteratorPrevTest_140, PrevTwiceFromLastRemainsValidWhenSizeAtLeastThree_140) {
  auto files = MakeFiles(3);
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToLast();  // index = 2
  ASSERT_TRUE(it.Valid());

  it.Prev();        // index = 1 → valid
  EXPECT_TRUE(it.Valid());

  it.Prev();        // index = 0 → valid (still at first)
  EXPECT_TRUE(it.Valid());

  // One more Prev from first should invalidate (boundary behavior)
  it.Prev();        // index becomes size → invalid
  EXPECT_FALSE(it.Valid());

  DeleteFiles(files);
}

// [Boundary] From first in multi-element: SeekToFirst then Prev invalidates.
TEST_F(LevelFileNumIteratorPrevTest_140, PrevFromFirstInvalidates_140) {
  auto files = MakeFiles(2);
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());  // At first (index 0)

  it.Prev();                // From first → invalid
  EXPECT_FALSE(it.Valid());

  DeleteFiles(files);
}

}  // namespace leveldb
