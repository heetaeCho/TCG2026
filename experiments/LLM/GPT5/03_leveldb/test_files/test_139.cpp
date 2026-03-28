// File: level_file_num_iterator_next_test_139.cc

#include "gtest/gtest.h"

#include "db/dbformat.h"         // leveldb::InternalKeyComparator, BytewiseComparator()
#include "db/version_set.h"      // leveldb::Version, leveldb::FileMetaData (public types)
#include "leveldb/iterator.h"    // leveldb::Iterator
#include "leveldb/status.h"

#include <memory>
#include <vector>

namespace leveldb {

class LevelFileNumIteratorTest_139 : public ::testing::Test {
protected:
  InternalKeyComparator icmp_{BytewiseComparator()};
  std::vector<FileMetaData*> files_;  // storage for raw pointers owned by unique_ptrs
  std::vector<std::unique_ptr<FileMetaData>> owners_;

  // Helper to append a default-constructed FileMetaData (no assumptions about its fields).
  void AddFile() {
    owners_.emplace_back(new FileMetaData());
    files_.push_back(owners_.back().get());
  }

  // Factory: create the iterator over the current files_ list.
  // NOTE: We treat the iterator purely via its public interface.
  std::unique_ptr<Version::LevelFileNumIterator> MakeIter() {
    return std::unique_ptr<Version::LevelFileNumIterator>(
        new Version::LevelFileNumIterator(icmp_, &files_));
  }
};

// -------------------------------------------------------------
// Normal operation: Next() moves across multiple elements
// -------------------------------------------------------------

TEST_F(LevelFileNumIteratorTest_139, NextAcrossTwoElements_139) {
  AddFile();
  AddFile();
  auto it = MakeIter();

  it->SeekToFirst();
  ASSERT_TRUE(it->Valid()) << "iterator should be valid at the first element";
  EXPECT_TRUE(it->status().ok());

  it->Next();  // move to second element
  EXPECT_TRUE(it->Valid()) << "iterator should be valid at the second element";
  EXPECT_TRUE(it->status().ok());

  it->Next();  // move past the last element
  EXPECT_FALSE(it->Valid()) << "iterator should become invalid past the end";
  EXPECT_TRUE(it->status().ok());
}

// -------------------------------------------------------------
// Boundary: single element -> Next() makes it invalid
// -------------------------------------------------------------

TEST_F(LevelFileNumIteratorTest_139, NextFromSingleElementBecomesInvalid_139) {
  AddFile();
  auto it = MakeIter();

  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  EXPECT_TRUE(it->status().ok());

  it->Next();  // from the only element to "past end"
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

// -------------------------------------------------------------
// Boundary: SeekToLast() then Next() -> becomes invalid
// -------------------------------------------------------------

TEST_F(LevelFileNumIteratorTest_139, NextFromLastBecomesInvalid_139) {
  AddFile();
  AddFile();
  auto it = MakeIter();

  it->SeekToLast();
  ASSERT_TRUE(it->Valid());
  EXPECT_TRUE(it->status().ok());

  it->Next();  // stepping off the end
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

// -------------------------------------------------------------
// Exceptional: Next() requires Valid() (assert). Calling Next()
// while invalid (e.g., before any Seek) should fail in debug.
// -------------------------------------------------------------

#if GTEST_HAS_DEATH_TEST
TEST_F(LevelFileNumIteratorTest_139, NextOnInvalidTriggersAssert_139) {
  // No files added -> iterator starts invalid. Calling Next() should assert.
  auto it = MakeIter();
  ASSERT_FALSE(it->Valid());

  // We don't rely on a specific assert message; match any output.
  EXPECT_DEATH_IF_SUPPORTED(it->Next(), ".*");
}
#endif

// -------------------------------------------------------------
// Sanity: With empty list, SeekToFirst() leaves it invalid and
// Next() (if attempted) would be an error (covered above).
// -------------------------------------------------------------

TEST_F(LevelFileNumIteratorTest_139, EmptyListSeekToFirstStaysInvalid_139) {
  auto it = MakeIter();
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

}  // namespace leveldb
