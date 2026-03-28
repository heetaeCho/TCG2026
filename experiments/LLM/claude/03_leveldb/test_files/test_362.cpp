#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/memtable.h"
#include "leveldb/status.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "util/coding.h"

namespace leveldb {

class MemTableTest_362 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create an InternalKeyComparator using the default bytewise comparator
    cmp_ = new InternalKeyComparator(BytewiseComparator());
    memtable_ = new MemTable(*cmp_);
    memtable_->Ref();
  }

  void TearDown() override {
    memtable_->Unref();
    delete cmp_;
  }

  void Add(SequenceNumber seq, ValueType type, const Slice& key,
           const Slice& value) {
    memtable_->Add(seq, type, key, value);
  }

  Iterator* NewIterator() {
    return memtable_->NewIterator();
  }

  InternalKeyComparator* cmp_;
  MemTable* memtable_;
};

TEST_F(MemTableTest_362, EmptyIteratorIsNotValid_362) {
  Iterator* iter = NewIterator();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, EmptyIteratorSeekToFirstNotValid_362) {
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, EmptyIteratorSeekToLastNotValid_362) {
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, StatusIsOkOnEmptyIterator_362) {
  Iterator* iter = NewIterator();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableTest_362, SingleEntrySeekToFirst_362) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, SingleEntrySeekToLast_362) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, SingleEntryNextMakesInvalid_362) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, SingleEntryPrevMakesInvalid_362) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, MultipleEntriesForwardIteration_362) {
  Add(1, kTypeValue, "key1", "value1");
  Add(2, kTypeValue, "key2", "value2");
  Add(3, kTypeValue, "key3", "value3");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableTest_362, MultipleEntriesReverseIteration_362) {
  Add(1, kTypeValue, "key1", "value1");
  Add(2, kTypeValue, "key2", "value2");
  Add(3, kTypeValue, "key3", "value3");

  Iterator* iter = NewIterator();
  iter->SeekToLast();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  ASSERT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableTest_362, SeekFindsKey_362) {
  Add(1, kTypeValue, "key1", "value1");
  Add(2, kTypeValue, "key2", "value2");
  Add(3, kTypeValue, "key3", "value3");

  // Construct an internal key to seek
  InternalKey ikey("key2", 2, kTypeValue);
  
  Iterator* iter = NewIterator();
  iter->Seek(ikey.Encode());
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, SeekPastAllKeys_362) {
  Add(1, kTypeValue, "aaa", "value1");
  Add(2, kTypeValue, "bbb", "value2");

  // Seek to a key that is past all entries (high sequence number, high key)
  InternalKey ikey("zzz", kMaxSequenceNumber, kValueTypeForSeek);
  
  Iterator* iter = NewIterator();
  iter->Seek(ikey.Encode());
  // Seeking past all keys - depends on internal ordering; at minimum status ok
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

TEST_F(MemTableTest_362, IteratorKeyAndValueAreAccessible_362) {
  Add(1, kTypeValue, "testkey", "testvalue");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  
  // The key should be an internal key encoding of "testkey"
  Slice k = iter->key();
  ASSERT_GT(k.size(), 0u);
  
  Slice v = iter->value();
  ASSERT_EQ(v.ToString(), "testvalue");
  delete iter;
}

TEST_F(MemTableTest_362, DeletionEntryIteratable_362) {
  Add(1, kTypeDeletion, "key1", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, PrevFromMiddle_362) {
  Add(1, kTypeValue, "key1", "value1");
  Add(2, kTypeValue, "key2", "value2");
  Add(3, kTypeValue, "key3", "value3");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  // Now go back
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_362, ForwardThenBackward_362) {
  Add(1, kTypeValue, "a", "va");
  Add(2, kTypeValue, "b", "vb");
  Add(3, kTypeValue, "c", "vc");

  Iterator* iter = NewIterator();
  
  // Go forward to end
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  
  // Now go backward from end
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  
  delete iter;
}

TEST_F(MemTableTest_362, StatusAlwaysOk_362) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  
  ASSERT_TRUE(iter->status().ok());
  
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  
  delete iter;
}

TEST_F(MemTableTest_362, DuplicateKeysWithDifferentSequences_362) {
  Add(1, kTypeValue, "key1", "value_old");
  Add(2, kTypeValue, "key1", "value_new");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  // Both entries should be present in the memtable
  ASSERT_EQ(2, count);
  delete iter;
}

TEST_F(MemTableTest_362, MemTableApproximateMemoryUsage_362) {
  // Empty memtable should have some base memory usage
  size_t initial_usage = memtable_->ApproximateMemoryUsage();
  
  Add(1, kTypeValue, "key1", "value1");
  
  size_t after_add_usage = memtable_->ApproximateMemoryUsage();
  ASSERT_GT(after_add_usage, initial_usage);
}

TEST_F(MemTableTest_362, MemTableGetExistingKey_362) {
  Add(1, kTypeValue, "key1", "value1");
  
  std::string value;
  Status s;
  LookupKey lkey("key1", 1);
  bool found = memtable_->Get(lkey, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("value1", value);
}

TEST_F(MemTableTest_362, MemTableGetNonExistentKey_362) {
  Add(1, kTypeValue, "key1", "value1");
  
  std::string value;
  Status s;
  LookupKey lkey("key2", 1);
  bool found = memtable_->Get(lkey, &value, &s);
  ASSERT_FALSE(found);
}

TEST_F(MemTableTest_362, MemTableGetDeletedKey_362) {
  Add(1, kTypeValue, "key1", "value1");
  Add(2, kTypeDeletion, "key1", "");
  
  std::string value;
  Status s;
  LookupKey lkey("key1", 2);
  bool found = memtable_->Get(lkey, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.IsNotFound());
}

TEST_F(MemTableTest_362, MemTableGetWithOlderSequence_362) {
  Add(2, kTypeValue, "key1", "value1");
  
  std::string value;
  Status s;
  // Look up with a sequence number older than the entry
  LookupKey lkey("key1", 1);
  bool found = memtable_->Get(lkey, &value, &s);
  ASSERT_FALSE(found);
}

TEST_F(MemTableTest_362, MemTableGetLatestValue_362) {
  Add(1, kTypeValue, "key1", "value_old");
  Add(2, kTypeValue, "key1", "value_new");
  
  std::string value;
  Status s;
  LookupKey lkey("key1", 3);
  bool found = memtable_->Get(lkey, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("value_new", value);
}

}  // namespace leveldb
