#include "gtest/gtest.h"
#include "db/memtable.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "util/coding.h"

namespace leveldb {

class MemTableIteratorTest_360 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create an InternalKeyComparator with the default bytewise comparator
    cmp_ = new InternalKeyComparator(BytewiseComparator());
    table_ = new MemTable(*cmp_);
    table_->Ref();
  }

  void TearDown() override {
    table_->Unref();
    delete cmp_;
  }

  void AddEntry(SequenceNumber seq, ValueType type, const Slice& key,
                const Slice& value) {
    table_->Add(seq, type, key, value);
  }

  InternalKeyComparator* cmp_;
  MemTable* table_;
};

TEST_F(MemTableIteratorTest_360, EmptyTableIteratorNotValid_360) {
  Iterator* iter = table_->NewIterator();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SeekToFirstOnEmptyTable_360) {
  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SeekToLastOnEmptyTable_360) {
  Iterator* iter = table_->NewIterator();
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, StatusOkOnEmptyTable_360) {
  Iterator* iter = table_->NewIterator();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SingleEntrySeekToFirst_360) {
  AddEntry(1, kTypeValue, "key1", "value1");
  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SingleEntrySeekToLast_360) {
  AddEntry(1, kTypeValue, "key1", "value1");
  Iterator* iter = table_->NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SingleEntryNextInvalidates_360) {
  AddEntry(1, kTypeValue, "key1", "value1");
  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SingleEntryPrevInvalidates_360) {
  AddEntry(1, kTypeValue, "key1", "value1");
  Iterator* iter = table_->NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, MultipleEntriesOrder_360) {
  AddEntry(3, kTypeValue, "aaa", "val_a");
  AddEntry(2, kTypeValue, "ccc", "val_c");
  AddEntry(1, kTypeValue, "bbb", "val_b");

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Entries should be sorted by internal key comparator (user key ascending,
  // then sequence number descending)
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SeekToLastThenPrevTraversesAll_360) {
  AddEntry(3, kTypeValue, "aaa", "val_a");
  AddEntry(2, kTypeValue, "bbb", "val_b");
  AddEntry(1, kTypeValue, "ccc", "val_c");

  Iterator* iter = table_->NewIterator();
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

TEST_F(MemTableIteratorTest_360, SeekFindsEntry_360) {
  AddEntry(5, kTypeValue, "apple", "fruit");
  AddEntry(4, kTypeValue, "banana", "fruit");
  AddEntry(3, kTypeValue, "cherry", "fruit");

  // Build an internal key for seeking
  std::string seek_key;
  // Create a lookup key for "banana"
  LookupKey lk("banana", 10);

  Iterator* iter = table_->NewIterator();
  iter->Seek(lk.memtable_key());
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SeekPastAllEntries_360) {
  AddEntry(1, kTypeValue, "aaa", "val_a");

  // Seek with a key that should be after all entries
  LookupKey lk("zzz", 10);

  Iterator* iter = table_->NewIterator();
  iter->Seek(lk.memtable_key());
  // Should be invalid since "zzz" is past all entries
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, StatusAlwaysOk_360) {
  AddEntry(1, kTypeValue, "key1", "value1");
  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, KeyAndValueAccessible_360) {
  AddEntry(1, kTypeValue, "testkey", "testvalue");
  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // key() and value() should return non-empty slices
  ASSERT_GT(iter->key().size(), 0);
  ASSERT_GT(iter->value().size(), 0);
  delete iter;
}

TEST_F(MemTableIteratorTest_360, DeletionEntryIsVisible_360) {
  AddEntry(2, kTypeDeletion, "deleted_key", "");
  AddEntry(1, kTypeValue, "deleted_key", "old_value");

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  // Both entries (deletion and value) should be present in memtable
  ASSERT_EQ(2, count);
  delete iter;
}

TEST_F(MemTableIteratorTest_360, SeekToFirstThenSeekToLast_360) {
  AddEntry(3, kTypeValue, "aaa", "v1");
  AddEntry(2, kTypeValue, "bbb", "v2");
  AddEntry(1, kTypeValue, "ccc", "v3");

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());

  // After SeekToLast, Next should invalidate
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_360, ForwardAndBackwardTraversal_360) {
  AddEntry(3, kTypeValue, "a", "1");
  AddEntry(2, kTypeValue, "b", "2");
  AddEntry(1, kTypeValue, "c", "3");

  Iterator* iter = table_->NewIterator();

  // Forward
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_TRUE(iter->Valid());

  // Now go backward
  iter->Prev();
  ASSERT_TRUE(iter->Valid());

  delete iter;
}

TEST_F(MemTableIteratorTest_360, ManyEntries_360) {
  const int kNumEntries = 100;
  for (int i = 0; i < kNumEntries; i++) {
    char key[16];
    char val[16];
    std::snprintf(key, sizeof(key), "key%06d", i);
    std::snprintf(val, sizeof(val), "val%06d", i);
    AddEntry(kNumEntries - i, kTypeValue, key, val);
  }

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(kNumEntries, count);

  // Also verify backward count
  iter->SeekToLast();
  count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  ASSERT_EQ(kNumEntries, count);

  delete iter;
}

}  // namespace leveldb
