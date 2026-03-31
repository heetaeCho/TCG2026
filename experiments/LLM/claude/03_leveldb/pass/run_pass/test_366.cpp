#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "util/logging.h"

namespace leveldb {

class MemTableTest_366 : public ::testing::Test {
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

TEST_F(MemTableTest_366, NewIteratorReturnsNonNull_366) {
  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);
  delete iter;
}

TEST_F(MemTableTest_366, NewIteratorOnEmptyTable_366) {
  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);
  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_366, NewIteratorSeekToLastOnEmptyTable_366) {
  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);
  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_366, AddAndGetSingleEntry_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lk("key1", 1);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value1");
}

TEST_F(MemTableTest_366, GetNonExistentKey_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lk("key2", 1);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_FALSE(found);
}

TEST_F(MemTableTest_366, AddDeletionAndGet_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeDeletion, Slice("key1"), Slice(""));

  std::string value;
  Status s;
  LookupKey lk("key1", 2);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.IsNotFound());
}

TEST_F(MemTableTest_366, GetWithOlderSequenceNumber_366) {
  memtable_->Add(2, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  // Looking up with sequence number 1, which is before the add at seq 2
  LookupKey lk("key1", 1);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_FALSE(found);
}

TEST_F(MemTableTest_366, GetWithNewerSequenceNumber_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lk("key1", 5);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value1");
}

TEST_F(MemTableTest_366, MultipleEntriesIterator_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeValue, Slice("key2"), Slice("value2"));
  memtable_->Add(3, kTypeValue, Slice("key3"), Slice("value3"));

  Iterator* iter = memtable_->NewIterator();
  iter->SeekToFirst();
  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  ASSERT_EQ(count, 3);
  delete iter;
}

TEST_F(MemTableTest_366, IteratorSeekToLast_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeValue, Slice("key2"), Slice("value2"));

  Iterator* iter = memtable_->NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_366, OverwriteValueWithHigherSequence_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeValue, Slice("key1"), Slice("value2"));

  std::string value;
  Status s;
  LookupKey lk("key1", 2);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value2");
}

TEST_F(MemTableTest_366, GetOlderVersionOfOverwrittenKey_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeValue, Slice("key1"), Slice("value2"));

  std::string value;
  Status s;
  LookupKey lk("key1", 1);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value1");
}

TEST_F(MemTableTest_366, ApproximateMemoryUsageInitial_366) {
  size_t initial_usage = memtable_->ApproximateMemoryUsage();
  // An empty memtable should have some small memory usage (arena overhead)
  ASSERT_GT(initial_usage, 0u);
}

TEST_F(MemTableTest_366, ApproximateMemoryUsageGrows_366) {
  size_t initial_usage = memtable_->ApproximateMemoryUsage();
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  size_t after_one = memtable_->ApproximateMemoryUsage();
  ASSERT_GE(after_one, initial_usage);

  memtable_->Add(2, kTypeValue, Slice("key2"), Slice("value2"));
  size_t after_two = memtable_->ApproximateMemoryUsage();
  ASSERT_GE(after_two, after_one);
}

TEST_F(MemTableTest_366, EmptyKeyAndValue_366) {
  memtable_->Add(1, kTypeValue, Slice(""), Slice(""));

  std::string value;
  Status s;
  LookupKey lk("", 1);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "");
}

TEST_F(MemTableTest_366, LargeValue_366) {
  std::string large_value(10000, 'x');
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice(large_value));

  std::string value;
  Status s;
  LookupKey lk("key1", 1);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, large_value);
}

TEST_F(MemTableTest_366, DeleteThenReinsert_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeDeletion, Slice("key1"), Slice(""));
  memtable_->Add(3, kTypeValue, Slice("key1"), Slice("value3"));

  std::string value;
  Status s;
  LookupKey lk("key1", 3);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(value, "value3");
}

TEST_F(MemTableTest_366, DeleteThenReinsertReadAtDeleteSeq_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeDeletion, Slice("key1"), Slice(""));
  memtable_->Add(3, kTypeValue, Slice("key1"), Slice("value3"));

  std::string value;
  Status s;
  LookupKey lk("key1", 2);
  bool found = memtable_->Get(lk, &value, &s);
  ASSERT_TRUE(found);
  ASSERT_TRUE(s.IsNotFound());
}

TEST_F(MemTableTest_366, MultipleKeysGet_366) {
  memtable_->Add(1, kTypeValue, Slice("apple"), Slice("red"));
  memtable_->Add(2, kTypeValue, Slice("banana"), Slice("yellow"));
  memtable_->Add(3, kTypeValue, Slice("cherry"), Slice("dark_red"));

  std::string value;
  Status s;

  {
    LookupKey lk("apple", 3);
    ASSERT_TRUE(memtable_->Get(lk, &value, &s));
    ASSERT_EQ(value, "red");
  }
  {
    LookupKey lk("banana", 3);
    ASSERT_TRUE(memtable_->Get(lk, &value, &s));
    ASSERT_EQ(value, "yellow");
  }
  {
    LookupKey lk("cherry", 3);
    ASSERT_TRUE(memtable_->Get(lk, &value, &s));
    ASSERT_EQ(value, "dark_red");
  }
}

TEST_F(MemTableTest_366, IteratorSeekFindsEntry_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeValue, Slice("key2"), Slice("value2"));
  memtable_->Add(3, kTypeValue, Slice("key3"), Slice("value3"));

  Iterator* iter = memtable_->NewIterator();

  // Internal keys are encoded, so we use SeekToFirst and iterate
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  delete iter;
}

TEST_F(MemTableTest_366, IteratorPrevFromEnd_366) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeValue, Slice("key2"), Slice("value2"));

  Iterator* iter = memtable_->NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  iter->Prev();
  ASSERT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_366, RefUnrefLifecycle_366) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* mt = new MemTable(cmp);
  mt->Ref();
  mt->Add(1, kTypeValue, Slice("k"), Slice("v"));

  std::string value;
  Status s;
  LookupKey lk("k", 1);
  ASSERT_TRUE(mt->Get(lk, &value, &s));
  ASSERT_EQ(value, "v");

  mt->Unref();  // Should destroy the memtable
}

}  // namespace leveldb
