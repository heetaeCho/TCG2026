#include "gtest/gtest.h"
#include "db/memtable.h"
#include "leveldb/db.h"
#include "leveldb/comparator.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/dbformat.h"

namespace leveldb {

class MemTableIteratorTest_358 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a MemTable with the default bytewise comparator
    InternalKeyComparator cmp(BytewiseComparator());
    memtable_ = new MemTable(cmp);
    memtable_->Ref();
  }

  void TearDown() override {
    memtable_->Unref();
  }

  // Helper to add entries to the memtable
  void Add(SequenceNumber seq, ValueType type, const Slice& key,
           const Slice& value) {
    memtable_->Add(seq, type, key, value);
  }

  Iterator* NewIterator() {
    return memtable_->NewIterator();
  }

  MemTable* memtable_;
};

// Test that iterator over empty memtable is not valid
TEST_F(MemTableIteratorTest_358, EmptyMemTableNotValid_358) {
  Iterator* iter = NewIterator();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToFirst on empty memtable
TEST_F(MemTableIteratorTest_358, SeekToFirstEmpty_358) {
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast on empty memtable
TEST_F(MemTableIteratorTest_358, SeekToLastEmpty_358) {
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test status returns OK
TEST_F(MemTableIteratorTest_358, StatusIsOK_358) {
  Iterator* iter = NewIterator();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test Seek on empty memtable
TEST_F(MemTableIteratorTest_358, SeekOnEmptyMemTable_358) {
  Iterator* iter = NewIterator();
  iter->Seek("somekey");
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test adding one entry and iterating
TEST_F(MemTableIteratorTest_358, SingleEntrySeekToFirst_358) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // The key is an internal key encoding, so it should contain "key1"
  ASSERT_TRUE(iter->key().starts_with("key1"));
  delete iter;
}

// Test SeekToLast with single entry
TEST_F(MemTableIteratorTest_358, SingleEntrySeekToLast_358) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("key1"));
  delete iter;
}

// Test Next moves past last entry
TEST_F(MemTableIteratorTest_358, NextPastEnd_358) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Prev moves before first entry
TEST_F(MemTableIteratorTest_358, PrevBeforeBegin_358) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries are in sorted order
TEST_F(MemTableIteratorTest_358, MultipleEntriesSorted_358) {
  Add(1, kTypeValue, "key3", "value3");
  Add(2, kTypeValue, "key1", "value1");
  Add(3, kTypeValue, "key2", "value2");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("key1"));

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("key2"));

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("key3"));

  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Seek finds the correct entry
TEST_F(MemTableIteratorTest_358, SeekFindsEntry_358) {
  Add(1, kTypeValue, "apple", "v1");
  Add(2, kTypeValue, "banana", "v2");
  Add(3, kTypeValue, "cherry", "v3");

  // We need to construct a proper lookup key for Seek
  // The MemTableIterator::Seek expects a key encoded via EncodeKey
  // which is called internally with the slice we pass.
  // We use LookupKey to form the proper internal key format.
  LookupKey lk("banana", 100);
  Iterator* iter = NewIterator();
  iter->Seek(lk.memtable_key());
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("banana"));
  delete iter;
}

// Test SeekToLast then Prev traverses backward
TEST_F(MemTableIteratorTest_358, ReverseIteration_358) {
  Add(1, kTypeValue, "a", "v1");
  Add(2, kTypeValue, "b", "v2");
  Add(3, kTypeValue, "c", "v3");

  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("c"));

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("b"));

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("a"));

  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test value is accessible
TEST_F(MemTableIteratorTest_358, ValueAccessible_358) {
  Add(1, kTypeValue, "mykey", "myvalue");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // value() should return the value portion
  Slice val = iter->value();
  ASSERT_EQ(val.ToString(), "myvalue");
  delete iter;
}

// Test Seek for non-existent key positions at next entry
TEST_F(MemTableIteratorTest_358, SeekNonExistentKey_358) {
  Add(1, kTypeValue, "apple", "v1");
  Add(2, kTypeValue, "cherry", "v3");

  // Seek for "banana" which doesn't exist, should position at "cherry"
  LookupKey lk("banana", 100);
  Iterator* iter = NewIterator();
  iter->Seek(lk.memtable_key());
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->key().starts_with("cherry"));
  delete iter;
}

// Test Seek past all entries
TEST_F(MemTableIteratorTest_358, SeekPastAllEntries_358) {
  Add(1, kTypeValue, "apple", "v1");
  Add(2, kTypeValue, "banana", "v2");

  LookupKey lk("zzz", 100);
  Iterator* iter = NewIterator();
  iter->Seek(lk.memtable_key());
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test status remains ok after operations
TEST_F(MemTableIteratorTest_358, StatusOKAfterOperations_358) {
  Add(1, kTypeValue, "key", "val");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test deletion entries are visible in iterator
TEST_F(MemTableIteratorTest_358, DeletionEntryVisible_358) {
  Add(1, kTypeValue, "key1", "value1");
  Add(2, kTypeDeletion, "key1", "");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // Both entries should be present (iterator sees all entries)
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test with many entries
TEST_F(MemTableIteratorTest_358, ManyEntries_358) {
  const int kNumEntries = 100;
  for (int i = 0; i < kNumEntries; i++) {
    char key[32];
    char val[32];
    snprintf(key, sizeof(key), "key%06d", i);
    snprintf(val, sizeof(val), "val%06d", i);
    Add(i + 1, kTypeValue, key, val);
  }

  Iterator* iter = NewIterator();
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  ASSERT_EQ(count, kNumEntries);
  delete iter;
}

// Test empty key and value
TEST_F(MemTableIteratorTest_358, EmptyKeyAndValue_358) {
  Add(1, kTypeValue, "", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // Value should be empty
  ASSERT_EQ(iter->value().ToString(), "");
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

}  // namespace leveldb
