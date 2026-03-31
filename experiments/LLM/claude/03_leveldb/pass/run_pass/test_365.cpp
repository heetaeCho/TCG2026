#include "gtest/gtest.h"
#include "db/memtable.h"
#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "db/dbformat.h"

namespace leveldb {

class MemTableIteratorTest_365 : public ::testing::Test {
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

  void Add(SequenceNumber seq, ValueType type, const Slice& key,
           const Slice& value) {
    table_->Add(seq, type, key, value);
  }

  Iterator* NewIterator() {
    return table_->NewIterator();
  }

  InternalKeyComparator* cmp_;
  MemTable* table_;
};

// Test that status() always returns OK
TEST_F(MemTableIteratorTest_365, StatusReturnsOK_365) {
  Iterator* iter = NewIterator();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test that iterator on empty table is not valid
TEST_F(MemTableIteratorTest_365, EmptyTableIteratorNotValid_365) {
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToLast on empty table
TEST_F(MemTableIteratorTest_365, EmptyTableSeekToLastNotValid_365) {
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test that after adding one entry, SeekToFirst finds it
TEST_F(MemTableIteratorTest_365, SingleEntrySeekToFirst_365) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // The key is an internal key (user_key + sequence + type)
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test that after adding one entry, SeekToLast finds it
TEST_F(MemTableIteratorTest_365, SingleEntrySeekToLast_365) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test Next() moves past the single entry
TEST_F(MemTableIteratorTest_365, SingleEntryNextInvalidates_365) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test Prev() moves before the single entry
TEST_F(MemTableIteratorTest_365, SingleEntryPrevInvalidates_365) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test multiple entries are iterated in order
TEST_F(MemTableIteratorTest_365, MultipleEntriesForwardIteration_365) {
  Add(1, kTypeValue, "aaa", "val_a");
  Add(2, kTypeValue, "bbb", "val_b");
  Add(3, kTypeValue, "ccc", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(count, 3);
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test backward iteration over multiple entries
TEST_F(MemTableIteratorTest_365, MultipleEntriesBackwardIteration_365) {
  Add(1, kTypeValue, "aaa", "val_a");
  Add(2, kTypeValue, "bbb", "val_b");
  Add(3, kTypeValue, "ccc", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToLast();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  ASSERT_EQ(count, 3);
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test Seek finds the right key
TEST_F(MemTableIteratorTest_365, SeekFindsKey_365) {
  Add(1, kTypeValue, "aaa", "val_a");
  Add(2, kTypeValue, "bbb", "val_b");
  Add(3, kTypeValue, "ccc", "val_c");

  // Build an internal key to seek for "bbb"
  std::string seek_key;
  InternalKey ikey("bbb", 100, kTypeValue);
  
  Iterator* iter = NewIterator();
  iter->Seek(ikey.Encode());
  ASSERT_TRUE(iter->Valid());
  
  // Parse the internal key to verify user key
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(iter->key(), &parsed));
  ASSERT_EQ(parsed.user_key.ToString(), "bbb");
  
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test Seek for a key that doesn't exist (between existing keys)
TEST_F(MemTableIteratorTest_365, SeekBetweenKeys_365) {
  Add(1, kTypeValue, "aaa", "val_a");
  Add(2, kTypeValue, "ccc", "val_c");

  InternalKey ikey("bbb", 100, kTypeValue);
  
  Iterator* iter = NewIterator();
  iter->Seek(ikey.Encode());
  // Should land on "ccc" (next key >= "bbb")
  ASSERT_TRUE(iter->Valid());
  
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(iter->key(), &parsed));
  ASSERT_EQ(parsed.user_key.ToString(), "ccc");
  
  delete iter;
}

// Test Seek past all keys
TEST_F(MemTableIteratorTest_365, SeekPastAllKeys_365) {
  Add(1, kTypeValue, "aaa", "val_a");
  Add(2, kTypeValue, "bbb", "val_b");

  InternalKey ikey("zzz", 100, kTypeValue);
  
  Iterator* iter = NewIterator();
  iter->Seek(ikey.Encode());
  ASSERT_FALSE(iter->Valid());
  
  delete iter;
}

// Test key() and value() return proper data for a single entry
TEST_F(MemTableIteratorTest_365, KeyAndValueCorrectness_365) {
  Add(42, kTypeValue, "testkey", "testvalue");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Verify the user key embedded in the internal key
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(iter->key(), &parsed));
  ASSERT_EQ(parsed.user_key.ToString(), "testkey");
  ASSERT_EQ(parsed.sequence, 42u);
  ASSERT_EQ(parsed.type, kTypeValue);

  // Verify value
  ASSERT_EQ(iter->value().ToString(), "testvalue");

  delete iter;
}

// Test that deletion entries are also iterable
TEST_F(MemTableIteratorTest_365, DeletionEntry_365) {
  Add(1, kTypeDeletion, "delkey", "");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(iter->key(), &parsed));
  ASSERT_EQ(parsed.user_key.ToString(), "delkey");
  ASSERT_EQ(parsed.type, kTypeDeletion);

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test status remains OK throughout iteration
TEST_F(MemTableIteratorTest_365, StatusOKThroughoutIteration_365) {
  Add(1, kTypeValue, "k1", "v1");
  Add(2, kTypeValue, "k2", "v2");

  Iterator* iter = NewIterator();
  
  ASSERT_TRUE(iter->status().ok());
  
  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());
  
  iter->Next();
  ASSERT_TRUE(iter->status().ok());
  
  iter->SeekToLast();
  ASSERT_TRUE(iter->status().ok());
  
  iter->Prev();
  ASSERT_TRUE(iter->status().ok());

  delete iter;
}

// Test multiple entries with same user key but different sequences
TEST_F(MemTableIteratorTest_365, SameKeyDifferentSequences_365) {
  Add(1, kTypeValue, "key", "val1");
  Add(2, kTypeValue, "key", "val2");
  Add(3, kTypeValue, "key", "val3");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    ParsedInternalKey parsed;
    ASSERT_TRUE(ParseInternalKey(iter->key(), &parsed));
    ASSERT_EQ(parsed.user_key.ToString(), "key");
    count++;
    iter->Next();
  }
  // All three entries should be present
  ASSERT_EQ(count, 3);

  delete iter;
}

// Test forward then backward navigation
TEST_F(MemTableIteratorTest_365, ForwardThenBackward_365) {
  Add(1, kTypeValue, "aaa", "v1");
  Add(2, kTypeValue, "bbb", "v2");
  Add(3, kTypeValue, "ccc", "v3");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Move forward to second
  iter->Next();
  ASSERT_TRUE(iter->Valid());

  // Move backward to first
  iter->Prev();
  ASSERT_TRUE(iter->Valid());

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(iter->key(), &parsed));
  ASSERT_EQ(parsed.user_key.ToString(), "aaa");

  delete iter;
}

// Test empty value
TEST_F(MemTableIteratorTest_365, EmptyValue_365) {
  Add(1, kTypeValue, "key", "");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "");

  delete iter;
}

}  // namespace leveldb
