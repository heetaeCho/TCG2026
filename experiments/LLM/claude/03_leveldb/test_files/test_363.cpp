#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/memtable.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "util/coding.h"

namespace leveldb {

class MemTableIteratorTest_363 : public ::testing::Test {
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

TEST_F(MemTableIteratorTest_363, EmptyTableIsNotValid_363) {
  Iterator* iter = NewIterator();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SeekToFirstOnEmptyTable_363) {
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SeekToLastOnEmptyTable_363) {
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, StatusIsOkOnEmptyTable_363) {
  Iterator* iter = NewIterator();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SingleEntrySeekToFirst_363) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SingleEntrySeekToLast_363) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SingleEntryKeyIsRetrievable_363) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // The key in the memtable is an internal key (user_key + sequence + type)
  Slice k = iter->key();
  ASSERT_TRUE(k.size() > 4);  // At minimum user key + 8 bytes for seq+type
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SingleEntryValueIsRetrievable_363) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  Slice v = iter->value();
  ASSERT_EQ(v.ToString(), "value1");
  delete iter;
}

TEST_F(MemTableIteratorTest_363, NextMakesInvalidAfterSingleEntry_363) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, PrevMakesInvalidAfterSingleEntry_363) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, MultipleEntriesForwardIteration_363) {
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
  ASSERT_EQ(count, 3);
  delete iter;
}

TEST_F(MemTableIteratorTest_363, MultipleEntriesReverseIteration_363) {
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
  ASSERT_EQ(count, 3);
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SeekFindsExactKey_363) {
  Add(3, kTypeValue, "apple", "val_a");
  Add(2, kTypeValue, "banana", "val_b");
  Add(1, kTypeValue, "cherry", "val_c");

  // Build a lookup key for "banana"
  LookupKey lk("banana", 100);
  Slice memtable_key = lk.memtable_key();

  Iterator* iter = NewIterator();
  iter->Seek(memtable_key);
  ASSERT_TRUE(iter->Valid());
  // The value for banana should be "val_b"
  ASSERT_EQ(iter->value().ToString(), "val_b");
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SeekPastAllKeys_363) {
  Add(3, kTypeValue, "apple", "val_a");
  Add(2, kTypeValue, "banana", "val_b");

  // Seek for a key that is after all existing keys
  LookupKey lk("zzz", 100);
  Slice memtable_key = lk.memtable_key();

  Iterator* iter = NewIterator();
  iter->Seek(memtable_key);
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, SeekBeforeAllKeys_363) {
  Add(3, kTypeValue, "banana", "val_b");
  Add(2, kTypeValue, "cherry", "val_c");

  // Seek for a key that is before all existing keys
  LookupKey lk("aaa", 100);
  Slice memtable_key = lk.memtable_key();

  Iterator* iter = NewIterator();
  iter->Seek(memtable_key);
  ASSERT_TRUE(iter->Valid());
  // Should land on the first key "banana"
  ASSERT_EQ(iter->value().ToString(), "val_b");
  delete iter;
}

TEST_F(MemTableIteratorTest_363, StatusIsAlwaysOk_363) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, DeletionEntryIsVisible_363) {
  Add(2, kTypeDeletion, "key1", "");
  Add(1, kTypeValue, "key1", "value1");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Should see 2 entries (deletion + value, both for key1 with different sequences)
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(count, 2);
  delete iter;
}

TEST_F(MemTableIteratorTest_363, MultipleVersionsOfSameKey_363) {
  Add(3, kTypeValue, "key1", "v3");
  Add(2, kTypeValue, "key1", "v2");
  Add(1, kTypeValue, "key1", "v1");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Should have all 3 versions
  // First should be highest sequence number
  ASSERT_EQ(iter->value().ToString(), "v3");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "v2");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "v1");

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

TEST_F(MemTableIteratorTest_363, ForwardThenBackward_363) {
  Add(3, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(1, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "val_a");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "val_b");

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "val_a");

  delete iter;
}

TEST_F(MemTableIteratorTest_363, EmptyKeyAndValue_363) {
  Add(1, kTypeValue, "", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "");
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_363, LargeValue_363) {
  std::string large_val(10000, 'x');
  Add(1, kTypeValue, "bigkey", large_val);
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), large_val);
  delete iter;
}

}  // namespace leveldb
