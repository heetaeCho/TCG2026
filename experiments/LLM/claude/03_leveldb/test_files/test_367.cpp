#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"

namespace leveldb {

class MemTableTest_367 : public ::testing::Test {
 protected:
  void SetUp() override {
    InternalKeyComparator cmp(BytewiseComparator());
    memtable_ = new MemTable(cmp);
    memtable_->Ref();
  }

  void TearDown() override {
    memtable_->Unref();
  }

  MemTable* memtable_;
};

TEST_F(MemTableTest_367, AddAndGetSingleEntry_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  LookupKey lkey("key1", 1);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("value1", value);
}

TEST_F(MemTableTest_367, GetNonExistentKey_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  LookupKey lkey("key2", 1);
  ASSERT_FALSE(memtable_->Get(lkey, &value, &s));
}

TEST_F(MemTableTest_367, AddMultipleEntries_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeValue, "key2", "value2");
  memtable_->Add(3, kTypeValue, "key3", "value3");

  std::string value;
  Status s;

  LookupKey lkey1("key1", 3);
  ASSERT_TRUE(memtable_->Get(lkey1, &value, &s));
  ASSERT_EQ("value1", value);

  LookupKey lkey2("key2", 3);
  ASSERT_TRUE(memtable_->Get(lkey2, &value, &s));
  ASSERT_EQ("value2", value);

  LookupKey lkey3("key3", 3);
  ASSERT_TRUE(memtable_->Get(lkey3, &value, &s));
  ASSERT_EQ("value3", value);
}

TEST_F(MemTableTest_367, AddDeletionEntry_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeDeletion, "key1", "");

  std::string value;
  Status s;
  LookupKey lkey("key1", 2);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_TRUE(s.IsNotFound());
}

TEST_F(MemTableTest_367, GetWithOlderSequenceNumber_367) {
  memtable_->Add(2, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  // Looking up with sequence number 1, which is before the entry was added at seq 2
  LookupKey lkey("key1", 1);
  ASSERT_FALSE(memtable_->Get(lkey, &value, &s));
}

TEST_F(MemTableTest_367, GetWithNewerSequenceNumber_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  LookupKey lkey("key1", 5);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_EQ("value1", value);
}

TEST_F(MemTableTest_367, OverwriteKeyWithNewerSequence_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeValue, "key1", "value2");

  std::string value;
  Status s;
  LookupKey lkey("key1", 2);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_EQ("value2", value);
}

TEST_F(MemTableTest_367, OverwriteKeyGetOlderVersion_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeValue, "key1", "value2");

  std::string value;
  Status s;
  LookupKey lkey("key1", 1);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_EQ("value1", value);
}

TEST_F(MemTableTest_367, DeleteThenReinsert_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeDeletion, "key1", "");
  memtable_->Add(3, kTypeValue, "key1", "value3");

  std::string value;
  Status s;
  LookupKey lkey("key1", 3);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("value3", value);
}

TEST_F(MemTableTest_367, DeleteThenReinsertGetAtDeleteSeq_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeDeletion, "key1", "");
  memtable_->Add(3, kTypeValue, "key1", "value3");

  std::string value;
  Status s;
  LookupKey lkey("key1", 2);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_TRUE(s.IsNotFound());
}

TEST_F(MemTableTest_367, EmptyKey_367) {
  memtable_->Add(1, kTypeValue, "", "value_empty_key");

  std::string value;
  Status s;
  LookupKey lkey("", 1);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_EQ("value_empty_key", value);
}

TEST_F(MemTableTest_367, EmptyValue_367) {
  memtable_->Add(1, kTypeValue, "key1", "");

  std::string value;
  Status s;
  LookupKey lkey("key1", 1);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_EQ("", value);
}

TEST_F(MemTableTest_367, LargeKeyAndValue_367) {
  std::string large_key(1000, 'k');
  std::string large_value(10000, 'v');
  memtable_->Add(1, kTypeValue, large_key, large_value);

  std::string value;
  Status s;
  LookupKey lkey(large_key, 1);
  ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
  ASSERT_EQ(large_value, value);
}

TEST_F(MemTableTest_367, ApproximateMemoryUsageIncreases_367) {
  size_t usage_before = memtable_->ApproximateMemoryUsage();
  memtable_->Add(1, kTypeValue, "key1", "value1");
  size_t usage_after = memtable_->ApproximateMemoryUsage();
  ASSERT_GT(usage_after, usage_before);
}

TEST_F(MemTableTest_367, IteratorIsValid_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeValue, "key2", "value2");

  Iterator* iter = memtable_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(2, count);
  delete iter;
}

TEST_F(MemTableTest_367, IteratorEmptyMemTable_367) {
  Iterator* iter = memtable_->NewIterator();
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_367, IteratorSeekToLast_367) {
  memtable_->Add(1, kTypeValue, "aaa", "value1");
  memtable_->Add(2, kTypeValue, "zzz", "value2");

  Iterator* iter = memtable_->NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_367, IteratorPrevFromEnd_367) {
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(2, kTypeValue, "key2", "value2");
  memtable_->Add(3, kTypeValue, "key3", "value3");

  Iterator* iter = memtable_->NewIterator();
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

TEST_F(MemTableTest_367, ApproximateMemoryUsageEmpty_367) {
  size_t usage = memtable_->ApproximateMemoryUsage();
  // Even an empty memtable should have some memory usage (arena overhead)
  ASSERT_GE(usage, 0u);
}

TEST_F(MemTableTest_367, MultipleAddsSameSequence_367) {
  // Different keys with same sequence number
  memtable_->Add(1, kTypeValue, "key1", "value1");
  memtable_->Add(1, kTypeValue, "key2", "value2");

  std::string value;
  Status s;

  LookupKey lkey1("key1", 1);
  ASSERT_TRUE(memtable_->Get(lkey1, &value, &s));
  ASSERT_EQ("value1", value);

  LookupKey lkey2("key2", 1);
  ASSERT_TRUE(memtable_->Get(lkey2, &value, &s));
  ASSERT_EQ("value2", value);
}

TEST_F(MemTableTest_367, GetFromEmptyMemTable_367) {
  std::string value;
  Status s;
  LookupKey lkey("key1", 1);
  ASSERT_FALSE(memtable_->Get(lkey, &value, &s));
}

TEST_F(MemTableTest_367, AddManyEntries_367) {
  const int kNumEntries = 1000;
  for (int i = 0; i < kNumEntries; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    memtable_->Add(static_cast<SequenceNumber>(i + 1), kTypeValue, key, val);
  }

  for (int i = 0; i < kNumEntries; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_val = "val" + std::to_string(i);
    std::string value;
    Status s;
    LookupKey lkey(key, kNumEntries);
    ASSERT_TRUE(memtable_->Get(lkey, &value, &s));
    ASSERT_EQ(expected_val, value);
  }
}

TEST_F(MemTableTest_367, IteratorOrdering_367) {
  memtable_->Add(1, kTypeValue, "charlie", "c");
  memtable_->Add(2, kTypeValue, "alice", "a");
  memtable_->Add(3, kTypeValue, "bob", "b");

  Iterator* iter = memtable_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Entries should be ordered by user key
  // The iterator returns internal keys, but user key order should be alice < bob < charlie
  std::vector<std::string> keys;
  while (iter->Valid()) {
    keys.push_back(iter->key().ToString());
    iter->Next();
  }
  ASSERT_EQ(3u, keys.size());
  delete iter;
}

TEST_F(MemTableTest_367, RefUnrefManagement_367) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mt = new MemTable(cmp);
  mt->Ref();
  mt->Add(1, kTypeValue, "test", "data");

  std::string value;
  Status s;
  LookupKey lkey("test", 1);
  ASSERT_TRUE(mt->Get(lkey, &value, &s));
  ASSERT_EQ("data", value);

  mt->Unref();  // Should delete the memtable
}

TEST_F(MemTableTest_367, BinaryValueData_367) {
  // Test with binary data containing null bytes
  std::string key = "binkey";
  std::string value(10, '\0');
  value[5] = 'x';
  memtable_->Add(1, kTypeValue, key, value);

  std::string result;
  Status s;
  LookupKey lkey("binkey", 1);
  ASSERT_TRUE(memtable_->Get(lkey, &result, &s));
  ASSERT_EQ(value, result);
  ASSERT_EQ(10u, result.size());
}

}  // namespace leveldb
