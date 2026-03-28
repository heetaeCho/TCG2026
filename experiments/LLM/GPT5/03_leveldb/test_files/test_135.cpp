// File: version_level_file_num_iterator_test_135.cc

#include <gtest/gtest.h>
#include <vector>
#include <memory>

// Adjust includes to match your tree:
#include "db/version_set.h"      // for Version / FileMetaData (or the header that exposes them)
#include "db/dbformat.h"         // for InternalKey, InternalKeyComparator, kTypeValue
#include "util/coding.h"         // if needed by InternalKey
#include "leveldb/comparator.h"  // for BytewiseComparator
#include "leveldb/slice.h"

using leveldb::FileMetaData;
using leveldb::InternalKey;
using leveldb::InternalKeyComparator;
using leveldb::Slice;
using leveldb::Status;
using leveldb::Version;

namespace {

// Helper to create a file meta with [smallest, largest] internal keys.
// We DO NOT test internal content of keys—only use them to allow iterator ops.
static std::unique_ptr<FileMetaData> MakeFileMeta(
    uint64_t number, const std::string& smallest_user_key, const std::string& largest_user_key) {
  auto f = std::make_unique<FileMetaData>();
  f->number = number;
  f->smallest = InternalKey(smallest_user_key, /*seq=*/0, /*type=*/leveldb::kTypeValue);
  f->largest  = InternalKey(largest_user_key,  /*seq=*/0, /*type=*/leveldb::kTypeValue);
  return f;
}

// Fixture builds a comparator and a vector of FileMetaData*.
// We only assert iterator’s observable behavior via its public methods.
class LevelFileNumIteratorTest_135 : public ::testing::Test {
protected:
  InternalKeyComparator icmp_{leveldb::BytewiseComparator()};
  std::vector<FileMetaData*> files_;
  // Own the allocated file metas to clean up after tests.
  std::vector<std::unique_ptr<FileMetaData>> owned_;

  void AddFile(uint64_t number, const std::string& smallest, const std::string& largest) {
    owned_.push_back(MakeFileMeta(number, smallest, largest));
    files_.push_back(owned_.back().get());
  }
};

}  // namespace

// --- Tests ---

// Initial Valid() should be false regardless of file list size because the iterator
// starts at index_ == flist_->size() per the provided code.
TEST_F(LevelFileNumIteratorTest_135, InitialValidIsFalseOnEmpty_135) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  EXPECT_FALSE(it.Valid());
}

TEST_F(LevelFileNumIteratorTest_135, InitialValidIsFalseOnNonEmpty_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  Version::LevelFileNumIterator it(icmp_, &files_);
  EXPECT_FALSE(it.Valid());
}

// SeekToFirst should make a non-empty iterator valid; on empty it remains invalid.
// (We don’t assert which key—only validity as an observable behavior.)
TEST_F(LevelFileNumIteratorTest_135, SeekToFirstValidity_135) {
  // Empty
  {
    Version::LevelFileNumIterator it(icmp_, &files_);
    it.SeekToFirst();
    EXPECT_FALSE(it.Valid());
  }
  // Non-empty
  {
    AddFile(1, "a", "b");
    AddFile(2, "e", "f");
    Version::LevelFileNumIterator it(icmp_, &files_);
    it.SeekToFirst();
    EXPECT_TRUE(it.Valid());
  }
}

// SeekToLast should make a non-empty iterator valid; on empty it remains invalid.
TEST_F(LevelFileNumIteratorTest_135, SeekToLastValidity_135) {
  // Empty
  {
    Version::LevelFileNumIterator it(icmp_, &files_);
    it.SeekToLast();
    EXPECT_FALSE(it.Valid());
  }
  // Non-empty
  {
    AddFile(1, "a", "b");
    AddFile(2, "c", "d");
    Version::LevelFileNumIterator it(icmp_, &files_);
    it.SeekToLast();
    EXPECT_TRUE(it.Valid());
  }
}

// From first element, Prev should make it invalid (moving before first).
TEST_F(LevelFileNumIteratorTest_135, PrevFromFirstMakesInvalid_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  it.Prev();
  EXPECT_FALSE(it.Valid());
}

// From last element, Next should make it invalid (moving past last).
TEST_F(LevelFileNumIteratorTest_135, NextFromLastMakesInvalid_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  it.Next();
  EXPECT_FALSE(it.Valid());
}

// Iterating forward from SeekToFirst should visit exactly N valid positions, then become invalid.
// We only count steps (observable), not inspect keys/values.
TEST_F(LevelFileNumIteratorTest_135, FullForwardIterationCount_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();

  size_t seen = 0;
  while (it.Valid()) {
    // key()/value() existence is observable; we won’t assert their content.
    (void)it.key();
    (void)it.value();
    ++seen;
    it.Next();
  }
  EXPECT_EQ(seen, files_.size());
  EXPECT_FALSE(it.status().IsIOError());  // status() should be ok unless underlying impl says otherwise
}

// Seeking to a target greater than any file’s range should end up invalid.
// This checks only the observable Valid() result after Seek.
TEST_F(LevelFileNumIteratorTest_135, SeekPastLargestBecomesInvalid_135) {
  AddFile(1, "a", "b");   // [a, b]
  AddFile(2, "c", "d");   // [c, d]
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.Seek(Slice("zzz"));  // greater than any user key we inserted
  EXPECT_FALSE(it.Valid());
}

// Seeking into a middle range should make the iterator valid; Next then Prev should preserve validity.
TEST_F(LevelFileNumIteratorTest_135, SeekMiddleThenNextPrevStaysValid_135) {
  AddFile(1, "a", "b");
  AddFile(2, "h", "k");
  AddFile(3, "x", "z");
  Version::LevelFileNumIterator it(icmp_, &files_);

  it.Seek(Slice("i"));  // falls into [h, k]
  EXPECT_TRUE(it.Valid());

  it.Next();
  // Might become invalid if [h,k] was last; in our data it should still be valid or become valid on Prev.
  if (!it.Valid()) {
    // If Next jumped past end, go back to check Prev recovers validity when possible.
    it.Prev();
    EXPECT_TRUE(it.Valid());
  } else {
    // If still valid after Next, Prev should also be valid.
    it.Prev();
    EXPECT_TRUE(it.Valid());
  }
}
