#include "gtest/gtest.h"
#include "db/memtable.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "util/coding.h"

namespace leveldb {

class MemTableIteratorTest_359 : public ::testing::Test {
 protected:
  void SetUp() override {
    InternalKeyComparator cmp(BytewiseComparator());
    memtable_ = new MemTable(cmp);
    memtable_->Ref();
  }

  void TearDown() override {
    memtable_->Unref();
  }

  void AddEntry(SequenceNumber seq, ValueType type, const Slice& key,
                const Slice& value) {
    memtable_->Add(seq, type, key, value);
  }

  Iterator* NewIterator() {
    return memtable_->NewIterator();
  }

  MemTable* memtable_;
};

TEST_F(MemTableIteratorTest_359, EmptyTableIteratorNotValid_359) {
  std::unique_ptr<Iterator> iter(NewIterator());
  ASSERT_FALSE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, SeekToFirstOnEmptyTable_359) {
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, SeekToLastOnEmptyTable_359) {
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, StatusOkOnEmptyTable_359) {
  std::unique_ptr<Iterator> iter(NewIterator());
  ASSERT_TRUE(iter->status().ok());
}

TEST_F(MemTableIteratorTest_359, SeekToFirstSingleEntry_359) {
  AddEntry(1, kTypeValue, "key1", "value1");
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, SeekToLastSingleEntry_359) {
  AddEntry(1, kTypeValue, "key1", "value1");
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, NextInvalidatesAfterLastEntry_359) {
  AddEntry(1, kTypeValue, "key1", "value1");
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, PrevInvalidatesBeforeFirstEntry_359) {
  AddEntry(1, kTypeValue, "key1", "value1");
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, IterateMultipleEntries_359) {
  AddEntry(3, kTypeValue, "a", "val_a");
  AddEntry(2, kTypeValue, "b", "val_b");
  AddEntry(1, kTypeValue, "c", "val_c");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(3, count);
}

TEST_F(MemTableIteratorTest_359, IterateReverseMultipleEntries_359) {
  AddEntry(3, kTypeValue, "a", "val_a");
  AddEntry(2, kTypeValue, "b", "val_b");
  AddEntry(1, kTypeValue, "c", "val_c");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToLast();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  ASSERT_EQ(3, count);
}

TEST_F(MemTableIteratorTest_359, SeekFindsExistingKey_359) {
  AddEntry(1, kTypeValue, "key1", "value1");
  AddEntry(2, kTypeValue, "key2", "value2");
  AddEntry(3, kTypeValue, "key3", "value3");

  std::unique_ptr<Iterator> iter(NewIterator());

  // Build an internal key for seeking
  std::string seek_key;
  // Internal key format: user_key + (sequence << 8 | type)
  // We use a high sequence number so it should find "key2"
  ParsedInternalKey ikey("key2", kMaxSequenceNumber, kValueTypeForSeek);
  AppendInternalKey(&seek_key, ikey);

  iter->Seek(seek_key);
  ASSERT_TRUE(iter->Valid());
}

TEST_F(MemTableIteratorTest_359, SeekPastAllKeys_359) {
  AddEntry(1, kTypeValue, "aaa", "val");

  std::unique_ptr<Iterator> iter(NewIterator());

  std::string seek_key;
  ParsedInternalKey ikey("zzz", kMaxSequenceNumber, kValueTypeForSeek);
  AppendInternalKey(&seek_key, ikey);

  iter->Seek(seek_key);
  // Seeking past all keys may or may not be valid depending on ordering
  // but we just verify no crash and status is ok
  ASSERT_TRUE(iter->status().ok());
}

TEST_F(MemTableIteratorTest_359, StatusAlwaysOk_359) {
  AddEntry(1, kTypeValue, "key1", "value1");
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
}

TEST_F(MemTableIteratorTest_359, KeyAndValueReturnNonEmpty_359) {
  AddEntry(1, kTypeValue, "mykey", "myvalue");
  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  Slice key = iter->key();
  Slice value = iter->value();
  ASSERT_FALSE(key.empty());
  ASSERT_FALSE(value.empty());
}

TEST_F(MemTableIteratorTest_359, DeletionEntriesAreIterable_359) {
  AddEntry(1, kTypeValue, "key1", "value1");
  AddEntry(2, kTypeDeletion, "key1", "");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  // Both the value and deletion entries should be present
  ASSERT_EQ(2, count);
}

TEST_F(MemTableIteratorTest_359, SeekToFirstThenSeekToLast_359) {
  AddEntry(1, kTypeValue, "a", "val_a");
  AddEntry(2, kTypeValue, "z", "val_z");

  std::unique_ptr<Iterator> iter(NewIterator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  Slice first_key = iter->key();

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  Slice last_key = iter->key();

  // First and last should be different entries
  ASSERT_NE(first_key.ToString(), last_key.ToString());
}

TEST_F(MemTableIteratorTest_359, MultipleSeekToFirstCalls_359) {
  AddEntry(1, kTypeValue, "key1", "value1");

  std::unique_ptr<Iterator> iter(NewIterator());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  Slice key1 = iter->key();

  iter->Next();

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  Slice key2 = iter->key();

  ASSERT_EQ(key1.ToString(), key2.ToString());
}

TEST_F(MemTableIteratorTest_359, SameKeyDifferentSequences_359) {
  AddEntry(1, kTypeValue, "key", "value_old");
  AddEntry(2, kTypeValue, "key", "value_new");

  std::unique_ptr<Iterator> iter(NewIterator());
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  // Both versions of the key should be present in the memtable
  ASSERT_EQ(2, count);
}

}  // namespace leveldb
