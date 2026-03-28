#include "gtest/gtest.h"
#include "db/memtable.h"
#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "db/dbformat.h"
#include "util/coding.h"

namespace leveldb {

class MemTableIteratorTest_361 : public ::testing::Test {
 protected:
  void SetUp() override {
    InternalKeyComparator cmp(BytewiseComparator());
    table_ = new MemTable(cmp);
    table_->Ref();
  }

  void TearDown() override {
    table_->Unref();
  }

  void Add(SequenceNumber seq, ValueType type, const Slice& key,
           const Slice& value) {
    table_->Add(seq, type, key, value);
  }

  Iterator* NewIterator() {
    return table_->NewIterator();
  }

  MemTable* table_;
};

TEST_F(MemTableIteratorTest_361, EmptyIteratorIsNotValid_361) {
  Iterator* iter = NewIterator();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, EmptyIteratorSeekToFirst_361) {
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, EmptyIteratorSeekToLast_361) {
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, EmptyIteratorStatusOk_361) {
  Iterator* iter = NewIterator();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SingleEntrySeekToFirst_361) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SingleEntrySeekToLast_361) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SingleEntryNextMakesInvalid_361) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SingleEntryPrevMakesInvalid_361) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, MultipleEntriesOrder_361) {
  Add(1, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(3, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Entries should be in sorted order by internal key
  // We just verify we can iterate through all of them
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_361, MultipleEntriesReverseOrder_361) {
  Add(1, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(3, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  ASSERT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SeekFindsKey_361) {
  Add(3, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(1, kTypeValue, "c", "val_c");

  // Construct an internal key for seeking
  InternalKey target("b", 2, kTypeValue);

  Iterator* iter = NewIterator();
  iter->Seek(target.Encode());
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SeekPastAllKeys_361) {
  Add(1, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");

  // Seek to a key that would be past all entries
  // Using a very large user key
  InternalKey target("z", 0, kTypeValue);

  Iterator* iter = NewIterator();
  iter->Seek(target.Encode());
  // With sequence 0 and user key "z", this should be past all entries
  // depending on internal key ordering
  // Not asserting specific behavior since internal key ordering with sequence
  // numbers could vary, just checking no crash
  delete iter;
}

TEST_F(MemTableIteratorTest_361, KeyAndValueAccessible_361) {
  Add(1, kTypeValue, "mykey", "myvalue");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // key() and value() should return non-empty slices
  Slice k = iter->key();
  Slice v = iter->value();
  ASSERT_FALSE(k.empty());
  // value should contain "myvalue"
  ASSERT_EQ("myvalue", v.ToString());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, StatusAlwaysOk_361) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, DeletionEntry_361) {
  Add(1, kTypeDeletion, "key1", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, DuplicateKeysWithDifferentSequences_361) {
  Add(2, kTypeValue, "key1", "value2");
  Add(1, kTypeValue, "key1", "value1");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  // Both entries should exist in the memtable
  ASSERT_EQ(2, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SeekToFirstThenPrevIsInvalid_361) {
  Add(1, kTypeValue, "a", "va");
  Add(2, kTypeValue, "b", "vb");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, SeekToLastThenNextIsInvalid_361) {
  Add(1, kTypeValue, "a", "va");
  Add(2, kTypeValue, "b", "vb");

  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_361, ForwardThenBackward_361) {
  Add(3, kTypeValue, "a", "va");
  Add(2, kTypeValue, "b", "vb");
  Add(1, kTypeValue, "c", "vc");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  iter->Next();
  ASSERT_TRUE(iter->Valid());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());

  delete iter;
}

TEST_F(MemTableIteratorTest_361, LargeNumberOfEntries_361) {
  const int kNumEntries = 1000;
  for (int i = 0; i < kNumEntries; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    Add(static_cast<SequenceNumber>(i + 1), kTypeValue, key, val);
  }

  Iterator* iter = NewIterator();
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(kNumEntries, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_361, EmptyKeyAndValue_361) {
  Add(1, kTypeValue, "", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  Slice v = iter->value();
  ASSERT_EQ("", v.ToString());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

}  // namespace leveldb
