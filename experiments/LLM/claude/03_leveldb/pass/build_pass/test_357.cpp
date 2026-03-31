#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "util/arena.h"

namespace leveldb {

class MemTableIteratorTest_357 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a MemTable with a BytewiseComparator-based InternalKeyComparator
    cmp_ = new InternalKeyComparator(BytewiseComparator());
    table_ = new MemTable(*cmp_);
    table_->Ref();
  }

  void TearDown() override {
    table_->Unref();
    delete cmp_;
  }

  void Add(SequenceNumber seq, ValueType type, const Slice& key,
           const Slice& value) {
    table_->Add(seq, type, key, value);
  }

  Iterator* NewIterator() { return table_->NewIterator(); }

  InternalKeyComparator* cmp_;
  MemTable* table_;
};

TEST_F(MemTableIteratorTest_357, EmptyTableIteratorNotValid_357) {
  Iterator* iter = NewIterator();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SeekToFirstOnEmptyTable_357) {
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SeekToLastOnEmptyTable_357) {
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, StatusIsOkOnEmptyTable_357) {
  Iterator* iter = NewIterator();
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SingleEntrySeekToFirst_357) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SingleEntrySeekToLast_357) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  EXPECT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SingleEntryNextMakesInvalid_357) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SingleEntryPrevMakesInvalid_357) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  EXPECT_TRUE(iter->Valid());
  iter->Prev();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, MultipleEntriesForwardIteration_357) {
  Add(3, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(1, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_357, MultipleEntriesReverseIteration_357) {
  Add(3, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(1, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToLast();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  EXPECT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SeekFindsExistingKey_357) {
  Add(3, kTypeValue, "apple", "val_apple");
  Add(2, kTypeValue, "banana", "val_banana");
  Add(1, kTypeValue, "cherry", "val_cherry");

  // Construct a proper internal key for seeking
  std::string target;
  InternalKey ikey("banana", 2, kTypeValue);
  target = ikey.Encode().ToString();

  Iterator* iter = NewIterator();
  iter->Seek(target);
  EXPECT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SeekForNonExistingKeyLandsOnNext_357) {
  Add(3, kTypeValue, "apple", "val_apple");
  Add(1, kTypeValue, "cherry", "val_cherry");

  // Seek for "banana" which doesn't exist, should land on "cherry" or beyond "apple"
  InternalKey ikey("banana", kMaxSequenceNumber, kValueTypeForSeek);
  std::string target = ikey.Encode().ToString();

  Iterator* iter = NewIterator();
  iter->Seek(target);
  // It should be valid since "cherry" comes after "banana"
  EXPECT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, SeekPastAllKeysIsInvalid_357) {
  Add(1, kTypeValue, "apple", "val_apple");

  InternalKey ikey("zzz", kMaxSequenceNumber, kValueTypeForSeek);
  std::string target = ikey.Encode().ToString();

  Iterator* iter = NewIterator();
  iter->Seek(target);
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, StatusAlwaysOk_357) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->status().ok());
  iter->Next();
  EXPECT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, KeyAndValueAreReadable_357) {
  Add(1, kTypeValue, "mykey", "myvalue");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  // key() returns an internal key encoding, so its size should be > "mykey".size()
  Slice k = iter->key();
  EXPECT_GT(k.size(), 5u);  // "mykey" is 5 bytes, internal key adds 8 bytes
  Slice v = iter->value();
  EXPECT_EQ("myvalue", v.ToString());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, DeletionEntryIsIterable_357) {
  Add(1, kTypeDeletion, "deleted_key", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  Slice v = iter->value();
  EXPECT_EQ("", v.ToString());
  iter->Next();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, MultipleVersionsOfSameKey_357) {
  // Add multiple versions of the same user key with different sequence numbers
  Add(3, kTypeValue, "key", "value3");
  Add(2, kTypeValue, "key", "value2");
  Add(1, kTypeValue, "key", "value1");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  // All three entries should be present in the memtable
  EXPECT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_357, ForwardThenReverse_357) {
  Add(3, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(1, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  iter->Next();
  EXPECT_TRUE(iter->Valid());
  // Now go back
  iter->Prev();
  EXPECT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_357, LargeNumberOfEntries_357) {
  const int kNumEntries = 1000;
  for (int i = 0; i < kNumEntries; i++) {
    char key[100];
    char val[100];
    std::snprintf(key, sizeof(key), "key%06d", i);
    std::snprintf(val, sizeof(val), "val%06d", i);
    Add(kNumEntries - i, kTypeValue, key, val);
  }

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(kNumEntries, count);
  delete iter;
}

}  // namespace leveldb
