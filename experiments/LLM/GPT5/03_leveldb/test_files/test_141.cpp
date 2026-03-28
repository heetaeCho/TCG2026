// File: version_set_level_file_num_iterator_key_test_141.cc

#include "db/version_set.h"        // Assumes LevelFileNumIterator is available via this or an included header
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "util/testharness.h"      // If your tree uses this; otherwise just gtest
#include "gtest/gtest.h"

namespace leveldb {

class LevelFileNumIteratorTest_141 : public ::testing::Test {
protected:
  InternalKeyComparator icmp_;
  std::vector<FileMetaData*> files_;

  LevelFileNumIteratorTest_141()
      : icmp_(*BytewiseComparator()) {}

  static FileMetaData* MakeFile(uint64_t number,
                                const std::string& smallest_user_key,
                                const std::string& largest_user_key,
                                uint64_t smallest_seq = 100,
                                uint64_t largest_seq  = 200) {
    auto* f = new FileMetaData();
    f->number = number;
    // Construct distinct smallest/largest internal keys so we can assert which one key() returns.
    f->smallest = InternalKey(Slice(smallest_user_key), smallest_seq, kTypeValue);
    f->largest  = InternalKey(Slice(largest_user_key),  largest_seq,  kTypeValue);
    return f;
  }

  void TearDown() override {
    for (auto* f : files_) delete f;
    files_.clear();
  }
};

// Normal operation: key() returns the encoded "largest" internal key of the current file
TEST_F(LevelFileNumIteratorTest_141, KeyReturnsLargestEncode_OnFirst_141) {
  files_.push_back(MakeFile(1, "a", "b"));
  files_.push_back(MakeFile(2, "c", "d"));

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());

  // key() must equal largest.Encode() of the first file
  Slice expected = files_[0]->largest.Encode();
  EXPECT_EQ(it.key().ToString(), expected.ToString());
}

// SeekToLast and key()
TEST_F(LevelFileNumIteratorTest_141, KeyReturnsLargestEncode_OnLast_141) {
  files_.push_back(MakeFile(11, "aa", "ab"));
  files_.push_back(MakeFile(22, "ba", "bb"));
  files_.push_back(MakeFile(33, "ca", "cz"));

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());

  Slice expected = files_.back()->largest.Encode();
  EXPECT_EQ(it.key().ToString(), expected.ToString());
}

// Iteration forward: Next() moves file and key() tracks the new file's largest
TEST_F(LevelFileNumIteratorTest_141, NextUpdatesKeyToNextFilesLargest_141) {
  files_.push_back(MakeFile(5, "k1s", "k1L"));
  files_.push_back(MakeFile(6, "k2s", "k2L"));

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key().ToString(), files_[0]->largest.Encode().ToString());

  it.Next();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key().ToString(), files_[1]->largest.Encode().ToString());
}

// Iteration backward: Prev() and key()
TEST_F(LevelFileNumIteratorTest_141, PrevUpdatesKeyToPrevFilesLargest_141) {
  files_.push_back(MakeFile(10, "m1s", "m1L"));
  files_.push_back(MakeFile(20, "m2s", "m2L"));
  files_.push_back(MakeFile(30, "m3s", "m3L"));

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToLast();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key().ToString(), files_[2]->largest.Encode().ToString());

  it.Prev();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key().ToString(), files_[1]->largest.Encode().ToString());

  it.Prev();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key().ToString(), files_[0]->largest.Encode().ToString());
}

// Boundary: empty list remains invalid; key() should not be called when invalid
TEST_F(LevelFileNumIteratorTest_141, EmptyList_IsInvalid_141) {
  Version::LevelFileNumIterator it(icmp_, &files_);
  EXPECT_FALSE(it.Valid());

  it.SeekToFirst();
  EXPECT_FALSE(it.Valid());

  it.SeekToLast();
  EXPECT_FALSE(it.Valid());

  // Intentionally do NOT call key() here since behavior is undefined when invalid.
}

// Boundary: advancing past the end becomes invalid
TEST_F(LevelFileNumIteratorTest_141, NextPastEnd_BecomesInvalid_141) {
  files_.push_back(MakeFile(1, "s", "L"));

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());
  EXPECT_EQ(it.key().ToString(), files_[0]->largest.Encode().ToString());

  it.Next();  // move past the single element
  EXPECT_FALSE(it.Valid());
}

// Negative control: ensure key() uses 'largest', not 'smallest'
TEST_F(LevelFileNumIteratorTest_141, KeyUsesLargestNotSmallest_141) {
  // Make smallest/largest distinguishable
  files_.push_back(MakeFile(7, "alpha-smallest", "omega-LARGEST"));

  Version::LevelFileNumIterator it(icmp_, &files_);
  it.SeekToFirst();
  ASSERT_TRUE(it.Valid());

  EXPECT_NE(it.key().ToString(), files_[0]->smallest.Encode().ToString());
  EXPECT_EQ(it.key().ToString(), files_[0]->largest.Encode().ToString());
}

}  // namespace leveldb
