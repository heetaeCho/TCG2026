// File: level_file_num_iterator_test_136.cc

#include "gtest/gtest.h"

#include "db/dbformat.h"          // InternalKeyComparator
#include "leveldb/comparator.h"   // BytewiseComparator
#include <vector>

namespace leveldb {

// Forward declarations that match the provided interface snippets.
struct FileMetaData;
class Iterator;

class Version {
 public:
  class LevelFileNumIterator : public Iterator {
   public:
    LevelFileNumIterator(const InternalKeyComparator& icmp,
                         const std::vector<FileMetaData*>* flist);
    bool Valid() const override;
    void Seek(const Slice& target) override;
    void SeekToFirst() override;
    void SeekToLast() override;
    void Next() override;
    void Prev() override;
    Slice key() const override;
    Slice value() const override;
    Status status() const override;
  };
};

}  // namespace leveldb

namespace {

using leveldb::BytewiseComparator;
using leveldb::FileMetaData;
using leveldb::InternalKeyComparator;
using leveldb::Slice;
using leveldb::Status;
using leveldb::Version;

class LevelFileNumIteratorTest_136 : public ::testing::Test {
 protected:
  LevelFileNumIteratorTest_136()
      : icmp_(BytewiseComparator()), files_() {}

  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;
};

// --- Normal/Boundary behavior on empty file list ---

TEST_F(LevelFileNumIteratorTest_136, ConstructedOnEmptyList_IsInitiallyInvalid_136) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());  // status should be OK if no prior errors
}

TEST_F(LevelFileNumIteratorTest_136, SeekOnEmptyList_RemainsInvalid_136) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.Seek(Slice("any_target"));
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

TEST_F(LevelFileNumIteratorTest_136, SeekToFirstOnEmptyList_RemainsInvalid_136) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

TEST_F(LevelFileNumIteratorTest_136, SeekToLastOnEmptyList_RemainsInvalid_136) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToLast();
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

TEST_F(LevelFileNumIteratorTest_136, NextOnEmptyList_DoesNotBecomeValid_136) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.Next();  // should be a no-op in terms of validity on empty list
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

TEST_F(LevelFileNumIteratorTest_136, PrevOnEmptyList_DoesNotBecomeValid_136) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  it.Prev();  // should be a no-op in terms of validity on empty list
  EXPECT_FALSE(it.Valid());
  EXPECT_TRUE(it.status().ok());
}

// Note: We intentionally do NOT call key() / value() when !Valid(),
// since their behavior is unspecified in that state based on the given interface.

}  // namespace
