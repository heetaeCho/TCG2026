#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "util/arena.h"

namespace leveldb {

class MemTableTest_354 : public ::testing::Test {
 protected:
  void SetUp() override {
    InternalKeyComparator cmp(BytewiseComparator());
    table_ = new MemTable(cmp);
    table_->Ref();
  }

  void TearDown() override {
    table_->Unref();
  }

  MemTable* table_;
};

TEST_F(MemTableTest_354, InitialApproximateMemoryUsage_354) {
  // A freshly created MemTable should have some small memory usage (arena overhead)
  size_t usage = table_->ApproximateMemoryUsage();
  // It should be non-negative; could be 0 or small overhead
  EXPECT_GE(usage, 0u);
}

TEST_F(MemTableTest_354, AddIncreasesMemoryUsage_354) {
  size_t before = table_->ApproximateMemoryUsage();
  table_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  size_t after = table_->ApproximateMemoryUsage();
  EXPECT_GT(after, before);
}

TEST_F(MemTableTest_354, GetExistingKey_354) {
  table_->Add(100, kTypeValue, Slice("testkey"), Slice("testvalue"));
  
  std::string value;
  Status s;
  LookupKey lkey("testkey", 100);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "testvalue");
}

TEST_F(MemTableTest_354, GetNonExistingKey_354) {
  table_->Add(100, kTypeValue, Slice("testkey"), Slice("testvalue"));
  
  std::string value;
  Status s;
  LookupKey lkey("nonexistent", 100);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_FALSE(found);
}

TEST_F(MemTableTest_354, GetDeletedKey_354) {
  table_->Add(100, kTypeValue, Slice("delkey"), Slice("somevalue"));
  table_->Add(200, kTypeDeletion, Slice("delkey"), Slice(""));
  
  std::string value;
  Status s;
  LookupKey lkey("delkey", 200);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
}

TEST_F(MemTableTest_354, GetWithOlderSequenceNumber_354) {
  // Add key at sequence 100
  table_->Add(100, kTypeValue, Slice("key1"), Slice("val1"));
  
  // Lookup with a sequence number older than the insertion
  std::string value;
  Status s;
  LookupKey lkey("key1", 50);
  bool found = table_->Get(lkey, &value, &s);
  
  // The entry at seq 100 should not be visible at seq 50
  EXPECT_FALSE(found);
}

TEST_F(MemTableTest_354, GetLatestVersionOfKey_354) {
  table_->Add(100, kTypeValue, Slice("key1"), Slice("val100"));
  table_->Add(200, kTypeValue, Slice("key1"), Slice("val200"));
  
  std::string value;
  Status s;
  LookupKey lkey("key1", 300);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "val200");
}

TEST_F(MemTableTest_354, GetOlderVersionOfKey_354) {
  table_->Add(100, kTypeValue, Slice("key1"), Slice("val100"));
  table_->Add(200, kTypeValue, Slice("key1"), Slice("val200"));
  
  std::string value;
  Status s;
  LookupKey lkey("key1", 150);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "val100");
}

TEST_F(MemTableTest_354, NewIteratorEmpty_354) {
  Iterator* iter = table_->NewIterator();
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  
  delete iter;
}

TEST_F(MemTableTest_354, NewIteratorNonEmpty_354) {
  table_->Add(100, kTypeValue, Slice("key1"), Slice("val1"));
  table_->Add(200, kTypeValue, Slice("key2"), Slice("val2"));
  table_->Add(300, kTypeValue, Slice("key3"), Slice("val3"));
  
  Iterator* iter = table_->NewIterator();
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(count, 3);
  
  delete iter;
}

TEST_F(MemTableTest_354, MultipleAddsIncreaseMemory_354) {
  size_t usage0 = table_->ApproximateMemoryUsage();
  
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    table_->Add(i + 1, kTypeValue, Slice(key), Slice(val));
  }
  
  size_t usage1 = table_->ApproximateMemoryUsage();
  EXPECT_GT(usage1, usage0);
}

TEST_F(MemTableTest_354, AddEmptyKeyAndValue_354) {
  table_->Add(1, kTypeValue, Slice(""), Slice(""));
  
  std::string value;
  Status s;
  LookupKey lkey("", 1);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "");
}

TEST_F(MemTableTest_354, AddLargeValue_354) {
  std::string large_value(10000, 'x');
  size_t before = table_->ApproximateMemoryUsage();
  table_->Add(1, kTypeValue, Slice("bigkey"), Slice(large_value));
  size_t after = table_->ApproximateMemoryUsage();
  
  EXPECT_GT(after, before);
  
  std::string value;
  Status s;
  LookupKey lkey("bigkey", 1);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, large_value);
}

TEST_F(MemTableTest_354, IteratorSeekToLast_354) {
  table_->Add(100, kTypeValue, Slice("aaa"), Slice("val_a"));
  table_->Add(200, kTypeValue, Slice("bbb"), Slice("val_b"));
  table_->Add(300, kTypeValue, Slice("ccc"), Slice("val_c"));
  
  Iterator* iter = table_->NewIterator();
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToLast();
  EXPECT_TRUE(iter->Valid());
  
  delete iter;
}

TEST_F(MemTableTest_354, IteratorPrevTraversal_354) {
  table_->Add(100, kTypeValue, Slice("a"), Slice("1"));
  table_->Add(200, kTypeValue, Slice("b"), Slice("2"));
  table_->Add(300, kTypeValue, Slice("c"), Slice("3"));
  
  Iterator* iter = table_->NewIterator();
  ASSERT_NE(iter, nullptr);
  
  iter->SeekToLast();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  EXPECT_EQ(count, 3);
  
  delete iter;
}

TEST_F(MemTableTest_354, DeleteThenReinsert_354) {
  table_->Add(100, kTypeValue, Slice("key1"), Slice("original"));
  table_->Add(200, kTypeDeletion, Slice("key1"), Slice(""));
  table_->Add(300, kTypeValue, Slice("key1"), Slice("reinserted"));
  
  std::string value;
  Status s;
  LookupKey lkey("key1", 300);
  bool found = table_->Get(lkey, &value, &s);
  
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "reinserted");
}

TEST_F(MemTableTest_354, RefUnrefDoesNotCrash_354) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mt = new MemTable(cmp);
  mt->Ref();
  mt->Ref();
  mt->Unref();
  mt->Unref();
  // Should not crash; second Unref should delete the object
}

TEST_F(MemTableTest_354, AddMultipleKeysAndGetEach_354) {
  table_->Add(1, kTypeValue, Slice("apple"), Slice("red"));
  table_->Add(2, kTypeValue, Slice("banana"), Slice("yellow"));
  table_->Add(3, kTypeValue, Slice("grape"), Slice("purple"));
  
  {
    std::string value;
    Status s;
    LookupKey lkey("apple", 10);
    EXPECT_TRUE(table_->Get(lkey, &value, &s));
    EXPECT_EQ(value, "red");
  }
  {
    std::string value;
    Status s;
    LookupKey lkey("banana", 10);
    EXPECT_TRUE(table_->Get(lkey, &value, &s));
    EXPECT_EQ(value, "yellow");
  }
  {
    std::string value;
    Status s;
    LookupKey lkey("grape", 10);
    EXPECT_TRUE(table_->Get(lkey, &value, &s));
    EXPECT_EQ(value, "purple");
  }
}

}  // namespace leveldb
