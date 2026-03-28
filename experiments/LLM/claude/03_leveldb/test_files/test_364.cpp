#include "gtest/gtest.h"
#include "db/memtable.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "util/coding.h"

namespace leveldb {

class MemTableIteratorTest_364 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a MemTable with the default bytewise comparator
    InternalKeyComparator cmp(BytewiseComparator());
    table_ = new MemTable(cmp);
    table_->Ref();
  }

  void TearDown() override {
    table_->Unref();
  }

  // Helper to add entries to the memtable
  void Add(SequenceNumber seq, ValueType type, const Slice& key,
           const Slice& value) {
    table_->Add(seq, type, key, value);
  }

  Iterator* NewIterator() {
    return table_->NewIterator();
  }

  MemTable* table_;
};

// Test iterator on empty memtable
TEST_F(MemTableIteratorTest_364, EmptyMemTable_Valid_364) {
  Iterator* iter = NewIterator();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_364, EmptyMemTable_SeekToFirst_364) {
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_364, EmptyMemTable_SeekToLast_364) {
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_364, EmptyMemTable_StatusOk_364) {
  Iterator* iter = NewIterator();
  ASSERT_TRUE(iter->status().ok());
  delete iter;
}

// Test with a single entry
TEST_F(MemTableIteratorTest_364, SingleEntry_SeekToFirst_364) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // The value should be "value1"
  Slice val = iter->value();
  ASSERT_EQ(val.ToString(), "value1");
  delete iter;
}

TEST_F(MemTableIteratorTest_364, SingleEntry_SeekToLast_364) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  Slice val = iter->value();
  ASSERT_EQ(val.ToString(), "value1");
  delete iter;
}

TEST_F(MemTableIteratorTest_364, SingleEntry_NextInvalidates_364) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableIteratorTest_364, SingleEntry_PrevInvalidates_364) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test with multiple entries
TEST_F(MemTableIteratorTest_364, MultipleEntries_ForwardIteration_364) {
  Add(3, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(1, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();

  std::vector<std::string> values;
  while (iter->Valid()) {
    values.push_back(iter->value().ToString());
    iter->Next();
  }

  ASSERT_EQ(values.size(), 3u);
  // Values should correspond to keys in sorted order (a, b, c)
  ASSERT_EQ(values[0], "val_a");
  ASSERT_EQ(values[1], "val_b");
  ASSERT_EQ(values[2], "val_c");
  delete iter;
}

TEST_F(MemTableIteratorTest_364, MultipleEntries_ReverseIteration_364) {
  Add(3, kTypeValue, "a", "val_a");
  Add(2, kTypeValue, "b", "val_b");
  Add(1, kTypeValue, "c", "val_c");

  Iterator* iter = NewIterator();
  iter->SeekToLast();

  std::vector<std::string> values;
  while (iter->Valid()) {
    values.push_back(iter->value().ToString());
    iter->Prev();
  }

  ASSERT_EQ(values.size(), 3u);
  // Reverse order: c, b, a
  ASSERT_EQ(values[0], "val_c");
  ASSERT_EQ(values[1], "val_b");
  ASSERT_EQ(values[2], "val_a");
  delete iter;
}

// Test Seek functionality
TEST_F(MemTableIteratorTest_364, Seek_ExistingKey_364) {
  Add(3, kTypeValue, "apple", "val_apple");
  Add(2, kTypeValue, "banana", "val_banana");
  Add(1, kTypeValue, "cherry", "val_cherry");

  // Build a LookupKey-compatible seek target for "banana"
  // MemTable iterator Seek expects an internal key encoding
  Iterator* iter = NewIterator();

  // Construct the memtable lookup key format for seek
  // The memtable uses LookupKey which encodes as:
  // klength (varint32 of internal key length) | user_key | tag (sequence | type)
  std::string seek_key;
  // Internal key = user_key + 8 bytes tag
  size_t internal_key_size = 6 + 8; // "banana" = 6 chars
  PutVarint32(&seek_key, internal_key_size);
  seek_key.append("banana");
  // Pack sequence number and type into tag
  // Use max sequence to find the latest entry
  PutFixed64(&seek_key, (static_cast<uint64_t>(kMaxSequenceNumber) << 8) | kValueTypeForSeek);

  iter->Seek(seek_key);
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "val_banana");
  delete iter;
}

// Test with deletion type entries
TEST_F(MemTableIteratorTest_364, DeletionEntry_Value_364) {
  Add(1, kTypeDeletion, "key1", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // Deletion entries have empty value
  ASSERT_EQ(iter->value().ToString(), "");
  delete iter;
}

// Test that status is always OK
TEST_F(MemTableIteratorTest_364, StatusAlwaysOk_364) {
  Add(1, kTypeValue, "key1", "value1");
  Iterator* iter = NewIterator();

  ASSERT_TRUE(iter->status().ok());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->status().ok());

  iter->Next();
  ASSERT_TRUE(iter->status().ok());

  delete iter;
}

// Test empty value
TEST_F(MemTableIteratorTest_364, EmptyValue_364) {
  Add(1, kTypeValue, "key1", "");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "");
  ASSERT_EQ(iter->value().size(), 0u);
  delete iter;
}

// Test large value
TEST_F(MemTableIteratorTest_364, LargeValue_364) {
  std::string large_value(10000, 'x');
  Add(1, kTypeValue, "key1", large_value);
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), large_value);
  delete iter;
}

// Test key() returns a valid slice
TEST_F(MemTableIteratorTest_364, KeyIsValid_364) {
  Add(1, kTypeValue, "testkey", "testvalue");
  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  // The key should contain "testkey" as part of the internal key
  Slice k = iter->key();
  ASSERT_GT(k.size(), 0u);
  delete iter;
}

// Test multiple entries with same user key but different sequences
TEST_F(MemTableIteratorTest_364, SameKeyDifferentSequences_364) {
  Add(2, kTypeValue, "key1", "newer_value");
  Add(1, kTypeValue, "key1", "older_value");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // With higher sequence number first (internal key ordering)
  std::string first_val = iter->value().ToString();
  ASSERT_EQ(first_val, "newer_value");

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  std::string second_val = iter->value().ToString();
  ASSERT_EQ(second_val, "older_value");

  iter->Next();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

// Test SeekToFirst followed by SeekToLast
TEST_F(MemTableIteratorTest_364, SeekToFirstThenSeekToLast_364) {
  Add(3, kTypeValue, "a", "first");
  Add(2, kTypeValue, "m", "middle");
  Add(1, kTypeValue, "z", "last");

  Iterator* iter = NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "first");

  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  ASSERT_EQ(iter->value().ToString(), "last");

  delete iter;
}

// Test bidirectional navigation
TEST_F(MemTableIteratorTest_364, BidirectionalNavigation_364) {
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

}  // namespace leveldb
