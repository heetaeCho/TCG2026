// Filename: level_file_num_iterator_seek_to_last_test_138.cc
#include <gtest/gtest.h>

#include "db/version_set.h"  // Assumes LevelFileNumIterator is available via this include
#include "db/dbformat.h"     // For InternalKeyComparator
#include "util/comparator.h" // For BytewiseComparator()

namespace leveldb {

class LevelFileNumIteratorTest_138 : public ::testing::Test {
protected:
  // We keep a stable comparator and vectors used by the iterator.
  // We do not rely on FileMetaData contents at all; only on list size.
  InternalKeyComparator icmp_{BytewiseComparator()};
};

// Empty list -> SeekToLast should leave iterator invalid.
TEST_F(LevelFileNumIteratorTest_138, SeekToLast_EmptyList_IsInvalid_138) {
  const std::vector<FileMetaData*> files;  // empty
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToLast();

  EXPECT_FALSE(it.Valid()) << "SeekToLast on empty list must be invalid";
}

// Single element -> SeekToLast makes it valid; one Next() should invalidate.
TEST_F(LevelFileNumIteratorTest_138, SeekToLast_Singleton_NextInvalidates_138) {
  std::vector<FileMetaData*> files(1, nullptr);  // size-only; content unused
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToLast();
  ASSERT_TRUE(it.Valid()) << "SeekToLast on single-element list must be valid";

  it.Next();
  EXPECT_FALSE(it.Valid()) << "Next from last element must become invalid";
}

// Two elements -> SeekToLast valid; Prev stays valid; Next returns to valid last; Next again invalid.
TEST_F(LevelFileNumIteratorTest_138, SeekToLast_TwoElements_PrevThenNext_Works_138) {
  std::vector<FileMetaData*> files(2, nullptr);
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToLast();
  ASSERT_TRUE(it.Valid()) << "SeekToLast must be valid on non-empty list";

  it.Prev();
  ASSERT_TRUE(it.Valid()) << "Prev from last (size>=2) must remain valid";

  it.Next();
  ASSERT_TRUE(it.Valid()) << "Next should return to last element (still valid)";

  it.Next();
  EXPECT_FALSE(it.Valid()) << "Next from last element must become invalid";
}

// Idempotence-ish check: calling SeekToLast multiple times should keep it at a valid position (non-empty)
// and not crash or change validity unexpectedly.
TEST_F(LevelFileNumIteratorTest_138, SeekToLast_CalledTwice_RemainsValidOnNonEmpty_138) {
  std::vector<FileMetaData*> files(3, nullptr);
  Version::LevelFileNumIterator it(icmp_, &files);

  it.SeekToLast();
  ASSERT_TRUE(it.Valid()) << "First SeekToLast must be valid";

  it.SeekToLast();  // Call again
  EXPECT_TRUE(it.Valid()) << "Second SeekToLast should remain valid on non-empty list";
}

}  // namespace leveldb
