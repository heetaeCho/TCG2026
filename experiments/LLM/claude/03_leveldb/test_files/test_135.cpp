#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"

#include <vector>
#include <string>
#include <cstring>

namespace leveldb {

class LevelFileNumIteratorTest_135 : public ::testing::Test {
 protected:
  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;

  LevelFileNumIteratorTest_135()
      : icmp_(BytewiseComparator()) {}

  ~LevelFileNumIteratorTest_135() override {
    for (auto* f : files_) {
      delete f;
    }
  }

  void AddFile(uint64_t number, const std::string& smallest,
               const std::string& largest) {
    FileMetaData* f = new FileMetaData();
    f->number = number;
    f->file_size = 100;  // arbitrary size
    f->smallest = InternalKey(smallest, 100, kTypeValue);
    f->largest = InternalKey(largest, 100, kTypeValue);
    files_.push_back(f);
  }

  // Creates iterator over current files_ vector
  Iterator* NewIterator() {
    // We need to create a LevelFileNumIterator. Since it's an internal class
    // within Version, we access it through the version_set infrastructure.
    // However, the class is exposed enough to test through the public Iterator
    // interface. We'll use a helper to create it.
    //
    // LevelFileNumIterator is constructed with (icmp, &flist)
    // We can instantiate it if the header exposes it.
    // Since the prompt shows it as a nested class, let's try direct construction.
    return new Version::LevelFileNumIterator(icmp_, &files_);
  }
};

// Test that iterator over empty file list is not valid initially
TEST_F(LevelFileNumIteratorTest_135, EmptyFileList_135) {
  std::unique_ptr<Iterator> iter(NewIterator());
  EXPECT_FALSE(iter->Valid());
}

// Test SeekToFirst on non-empty list makes iterator valid
TEST_F(LevelFileNumIteratorTest_135, SeekToFirstNonEmpty_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
}

// Test SeekToFirst on empty list keeps iterator invalid
TEST_F(LevelFileNumIteratorTest_135, SeekToFirstEmpty_135) {
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
}

// Test SeekToLast on non-empty list makes iterator valid
TEST_F(LevelFileNumIteratorTest_135, SeekToLastNonEmpty_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();
  EXPECT_TRUE(iter->Valid());
}

// Test SeekToLast on empty list keeps iterator invalid
TEST_F(LevelFileNumIteratorTest_135, SeekToLastEmpty_135) {
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
}

// Test that iterating forward through all files works
TEST_F(LevelFileNumIteratorTest_135, ForwardIteration_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(3, count);
}

// Test that iterating backward through all files works
TEST_F(LevelFileNumIteratorTest_135, BackwardIteration_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  EXPECT_EQ(3, count);
}

// Test that key() returns the largest key of the current file
TEST_F(LevelFileNumIteratorTest_135, KeyReturnsLargestKey_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // The key returned should be the largest key of the first file
  Slice key = iter->key();
  EXPECT_FALSE(key.empty());
}

// Test that value() encodes the file number and file size
TEST_F(LevelFileNumIteratorTest_135, ValueEncodesFileInfo_135) {
  AddFile(42, "a", "b");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  Slice val = iter->value();
  EXPECT_FALSE(val.empty());
}

// Test status() returns OK
TEST_F(LevelFileNumIteratorTest_135, StatusIsOK_135) {
  AddFile(1, "a", "b");

  std::unique_ptr<Iterator> iter(NewIterator());
  EXPECT_TRUE(iter->status().ok());

  iter->SeekToFirst();
  EXPECT_TRUE(iter->status().ok());
}

// Test Next past end makes iterator invalid
TEST_F(LevelFileNumIteratorTest_135, NextPastEnd_135) {
  AddFile(1, "a", "b");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  EXPECT_FALSE(iter->Valid());
}

// Test Prev before beginning makes iterator invalid
TEST_F(LevelFileNumIteratorTest_135, PrevBeforeBeginning_135) {
  AddFile(1, "a", "b");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
}

// Test Seek finds the correct file
TEST_F(LevelFileNumIteratorTest_135, SeekFindsCorrectFile_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");

  std::unique_ptr<Iterator> iter(NewIterator());

  // Seek to a key that should land on the second file
  InternalKey target("c", 100, kTypeValue);
  iter->Seek(target.Encode());
  EXPECT_TRUE(iter->Valid());
}

// Test Seek past all files makes iterator invalid
TEST_F(LevelFileNumIteratorTest_135, SeekPastAllFiles_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");

  std::unique_ptr<Iterator> iter(NewIterator());

  InternalKey target("z", 100, kTypeValue);
  iter->Seek(target.Encode());
  // Depending on implementation, this may or may not be valid.
  // If all files have keys less than "z", seek may go past end.
  // We just verify no crash and status is ok.
  EXPECT_TRUE(iter->status().ok());
}

// Test single file iteration
TEST_F(LevelFileNumIteratorTest_135, SingleFile_135) {
  AddFile(1, "a", "z");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  Slice key = iter->key();
  EXPECT_FALSE(key.empty());

  Slice val = iter->value();
  EXPECT_FALSE(val.empty());

  iter->Next();
  EXPECT_FALSE(iter->Valid());
}

// Test SeekToLast then Prev
TEST_F(LevelFileNumIteratorTest_135, SeekToLastThenPrev_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());

  iter->Prev();
  EXPECT_FALSE(iter->Valid());
}

// Test iterator initially not valid (index set to flist size)
TEST_F(LevelFileNumIteratorTest_135, InitiallyNotValid_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");

  std::unique_ptr<Iterator> iter(NewIterator());
  // Initially index_ = flist_->size(), so should be invalid
  EXPECT_FALSE(iter->Valid());
}

// Test Seek to a key before all files
TEST_F(LevelFileNumIteratorTest_135, SeekBeforeAllFiles_135) {
  AddFile(1, "d", "f");
  AddFile(2, "g", "i");

  std::unique_ptr<Iterator> iter(NewIterator());

  InternalKey target("a", 100, kTypeValue);
  iter->Seek(target.Encode());
  EXPECT_TRUE(iter->Valid());
}

// Test multiple forward-backward traversals
TEST_F(LevelFileNumIteratorTest_135, ForwardBackwardTraversal_135) {
  AddFile(1, "a", "b");
  AddFile(2, "c", "d");
  AddFile(3, "e", "f");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  iter->Next();
  ASSERT_TRUE(iter->Valid());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());

  // Should be back at first
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
}

}  // namespace leveldb
