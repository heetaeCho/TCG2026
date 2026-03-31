#include "gtest/gtest.h"
#include "db/memtable.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "db/dbformat.h"
#include "util/coding.h"

namespace leveldb {

class MemTableTest_356 : public ::testing::Test {
 protected:
  void SetUp() override {
    cmp_ = new InternalKeyComparator(BytewiseComparator());
    table_ = new MemTable(*cmp_);
    table_->Ref();
  }

  void TearDown() override {
    table_->Unref();
    delete cmp_;
  }

  InternalKeyComparator* cmp_;
  MemTable* table_;
};

// Test that a newly created MemTable has zero approximate memory usage beyond baseline
TEST_F(MemTableTest_356, EmptyMemTable_356) {
  size_t usage = table_->ApproximateMemoryUsage();
  EXPECT_GE(usage, 0u);
}

// Test adding a single entry and retrieving it
TEST_F(MemTableTest_356, AddAndGet_356) {
  SequenceNumber seq = 1;
  table_->Add(seq, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lkey("key1", seq);
  EXPECT_TRUE(table_->Get(lkey, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

// Test that Get returns false for a non-existent key
TEST_F(MemTableTest_356, GetNonExistentKey_356) {
  SequenceNumber seq = 1;
  table_->Add(seq, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lkey("key2", seq);
  EXPECT_FALSE(table_->Get(lkey, &value, &s));
}

// Test adding a deletion marker and retrieving it
TEST_F(MemTableTest_356, AddDeletion_356) {
  SequenceNumber seq = 2;
  table_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  table_->Add(seq, kTypeDeletion, Slice("key1"), Slice(""));

  std::string value;
  Status s;
  LookupKey lkey("key1", seq);
  bool found = table_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
}

// Test adding multiple entries
TEST_F(MemTableTest_356, MultipleEntries_356) {
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    table_->Add(i + 1, kTypeValue, Slice(key), Slice(val));
  }

  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_val = "value" + std::to_string(i);
    std::string value;
    Status s;
    LookupKey lkey(key, i + 1);
    EXPECT_TRUE(table_->Get(lkey, &value, &s));
    EXPECT_TRUE(s.ok());
    EXPECT_EQ(expected_val, value);
  }
}

// Test with empty key
TEST_F(MemTableTest_356, EmptyKey_356) {
  table_->Add(1, kTypeValue, Slice(""), Slice("emptykey_value"));

  std::string value;
  Status s;
  LookupKey lkey("", 1);
  EXPECT_TRUE(table_->Get(lkey, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("emptykey_value", value);
}

// Test with empty value
TEST_F(MemTableTest_356, EmptyValue_356) {
  table_->Add(1, kTypeValue, Slice("key1"), Slice(""));

  std::string value;
  Status s;
  LookupKey lkey("key1", 1);
  EXPECT_TRUE(table_->Get(lkey, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("", value);
}

// Test with large key and value
TEST_F(MemTableTest_356, LargeKeyValue_356) {
  std::string large_key(1000, 'k');
  std::string large_value(10000, 'v');
  table_->Add(1, kTypeValue, Slice(large_key), Slice(large_value));

  std::string value;
  Status s;
  LookupKey lkey(large_key, 1);
  EXPECT_TRUE(table_->Get(lkey, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(large_value, value);
}

// Test that newer sequence numbers shadow older ones
TEST_F(MemTableTest_356, SequenceNumberShadowing_356) {
  table_->Add(1, kTypeValue, Slice("key1"), Slice("old_value"));
  table_->Add(2, kTypeValue, Slice("key1"), Slice("new_value"));

  std::string value;
  Status s;
  LookupKey lkey("key1", 2);
  EXPECT_TRUE(table_->Get(lkey, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("new_value", value);
}

// Test reading at an older sequence number
TEST_F(MemTableTest_356, ReadAtOlderSequence_356) {
  table_->Add(1, kTypeValue, Slice("key1"), Slice("old_value"));
  table_->Add(2, kTypeValue, Slice("key1"), Slice("new_value"));

  std::string value;
  Status s;
  LookupKey lkey("key1", 1);
  EXPECT_TRUE(table_->Get(lkey, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("old_value", value);
}

// Test iterator over MemTable
TEST_F(MemTableTest_356, Iterator_356) {
  table_->Add(1, kTypeValue, Slice("a"), Slice("va"));
  table_->Add(2, kTypeValue, Slice("b"), Slice("vb"));
  table_->Add(3, kTypeValue, Slice("c"), Slice("vc"));

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(3, count);

  delete iter;
}

// Test iterator SeekToFirst and SeekToLast
TEST_F(MemTableTest_356, IteratorSeek_356) {
  table_->Add(1, kTypeValue, Slice("b"), Slice("vb"));
  table_->Add(2, kTypeValue, Slice("d"), Slice("vd"));
  table_->Add(3, kTypeValue, Slice("f"), Slice("vf"));

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());

  iter->SeekToLast();
  EXPECT_TRUE(iter->Valid());

  delete iter;
}

// Test MemTable memory usage increases after adds
TEST_F(MemTableTest_356, MemoryUsageIncreases_356) {
  size_t initial_usage = table_->ApproximateMemoryUsage();

  table_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  size_t after_one = table_->ApproximateMemoryUsage();
  EXPECT_GT(after_one, initial_usage);

  table_->Add(2, kTypeValue, Slice("key2"), Slice("value2"));
  size_t after_two = table_->ApproximateMemoryUsage();
  EXPECT_GT(after_two, after_one);
}

// Test with binary data in key and value
TEST_F(MemTableTest_356, BinaryData_356) {
  std::string binary_key("\x00\x01\x02\x03", 4);
  std::string binary_value("\xff\xfe\xfd\xfc", 4);
  table_->Add(1, kTypeValue, Slice(binary_key), Slice(binary_value));

  std::string value;
  Status s;
  LookupKey lkey(binary_key, 1);
  EXPECT_TRUE(table_->Get(lkey, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(binary_value, value);
}

// Test empty iterator on empty table
TEST_F(MemTableTest_356, EmptyIterator_356) {
  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test that Get with sequence number 0 doesn't find anything added at seq 1
TEST_F(MemTableTest_356, SequenceNumberZero_356) {
  table_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lkey("key1", 0);
  EXPECT_FALSE(table_->Get(lkey, &value, &s));
}

}  // namespace leveldb
