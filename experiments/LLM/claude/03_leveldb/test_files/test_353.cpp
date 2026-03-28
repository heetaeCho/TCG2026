#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "db/write_batch_internal.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/write_batch.h"
#include "util/coding.h"

namespace leveldb {

class MemTableTest_353 : public ::testing::Test {
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

  void Add(SequenceNumber seq, ValueType type, const Slice& key,
           const Slice& value) {
    table_->Add(seq, type, key, value);
  }

  bool Get(const Slice& key, SequenceNumber seq, std::string* value,
           Status* s) {
    LookupKey lkey(key, seq);
    return table_->Get(lkey, value, s);
  }

  InternalKeyComparator* cmp_;
  MemTable* table_;
};

TEST_F(MemTableTest_353, EmptyMemTableApproximateMemoryUsage_353) {
  // A newly created MemTable should have some small baseline memory usage.
  size_t usage = table_->ApproximateMemoryUsage();
  EXPECT_GT(usage, 0u);
}

TEST_F(MemTableTest_353, AddAndGetSingleEntry_353) {
  Add(100, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  bool found = Get("key1", 100, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

TEST_F(MemTableTest_353, GetNonExistentKey_353) {
  Add(100, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  bool found = Get("key2", 100, &value, &s);
  EXPECT_FALSE(found);
}

TEST_F(MemTableTest_353, GetWithLowerSequenceNumber_353) {
  // Insert with sequence 100, then query with sequence 50 — should not find it
  Add(100, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  bool found = Get("key1", 50, &value, &s);
  EXPECT_FALSE(found);
}

TEST_F(MemTableTest_353, GetWithHigherSequenceNumber_353) {
  Add(100, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  bool found = Get("key1", 200, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

TEST_F(MemTableTest_353, DeletedKeyReturnsNotFound_353) {
  Add(100, kTypeValue, "key1", "value1");
  Add(200, kTypeDeletion, "key1", "");

  std::string value;
  Status s;
  bool found = Get("key1", 300, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
}

TEST_F(MemTableTest_353, DeletedKeyWithOlderSeqReturnsValue_353) {
  Add(100, kTypeValue, "key1", "value1");
  Add(200, kTypeDeletion, "key1", "");

  std::string value;
  Status s;
  // Query at seq 150 should see the value at seq 100, not the deletion at 200
  bool found = Get("key1", 150, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

TEST_F(MemTableTest_353, MultipleKeysInsertAndGet_353) {
  Add(1, kTypeValue, "aaa", "val_a");
  Add(2, kTypeValue, "bbb", "val_b");
  Add(3, kTypeValue, "ccc", "val_c");

  std::string value;
  Status s;

  EXPECT_TRUE(Get("aaa", 10, &value, &s));
  EXPECT_EQ("val_a", value);

  EXPECT_TRUE(Get("bbb", 10, &value, &s));
  EXPECT_EQ("val_b", value);

  EXPECT_TRUE(Get("ccc", 10, &value, &s));
  EXPECT_EQ("val_c", value);
}

TEST_F(MemTableTest_353, OverwriteKeyWithNewerSequence_353) {
  Add(100, kTypeValue, "key1", "old_value");
  Add(200, kTypeValue, "key1", "new_value");

  std::string value;
  Status s;

  // At seq 300, should see the newer value
  bool found = Get("key1", 300, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("new_value", value);

  // At seq 150, should see the older value
  found = Get("key1", 150, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("old_value", value);
}

TEST_F(MemTableTest_353, MemoryUsageIncreasesWithInserts_353) {
  size_t initial = table_->ApproximateMemoryUsage();

  Add(1, kTypeValue, "key1", "value1");
  size_t after_one = table_->ApproximateMemoryUsage();
  EXPECT_GT(after_one, initial);

  Add(2, kTypeValue, "key2", "value2");
  size_t after_two = table_->ApproximateMemoryUsage();
  EXPECT_GT(after_two, after_one);
}

TEST_F(MemTableTest_353, IteratorOnEmptyTable_353) {
  Iterator* iter = table_->NewIterator();
  ASSERT_NE(iter, nullptr);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

TEST_F(MemTableTest_353, IteratorTraversesAllEntries_353) {
  Add(1, kTypeValue, "c", "vc");
  Add(2, kTypeValue, "a", "va");
  Add(3, kTypeValue, "b", "vb");

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  // Should have 3 entries
  EXPECT_EQ(3, count);
  delete iter;
}

TEST_F(MemTableTest_353, IteratorEntriesAreOrdered_353) {
  Add(1, kTypeValue, "c", "vc");
  Add(2, kTypeValue, "a", "va");
  Add(3, kTypeValue, "b", "vb");

  Iterator* iter = table_->NewIterator();
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());

  // Entries should be ordered by internal key comparator
  // which orders by user key ascending, then by sequence descending
  std::string prev_key = iter->key().ToString();
  iter->Next();
  while (iter->Valid()) {
    std::string curr_key = iter->key().ToString();
    // Internal key comparison: current should be >= previous
    EXPECT_GT(cmp_->Compare(curr_key, prev_key), 0);
    prev_key = curr_key;
    iter->Next();
  }
  delete iter;
}

TEST_F(MemTableTest_353, EmptyKeyAndValue_353) {
  Add(1, kTypeValue, "", "");

  std::string value;
  Status s;
  bool found = Get("", 10, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("", value);
}

TEST_F(MemTableTest_353, LargeValue_353) {
  std::string large_value(10000, 'x');
  Add(1, kTypeValue, "bigkey", large_value);

  std::string value;
  Status s;
  bool found = Get("bigkey", 10, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(large_value, value);
}

TEST_F(MemTableTest_353, ExactSequenceNumberMatch_353) {
  Add(100, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  // Get with the exact sequence number should find it
  bool found = Get("key1", 100, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

TEST_F(MemTableTest_353, GetAtSequenceNumberJustBelow_353) {
  Add(100, kTypeValue, "key1", "value1");

  std::string value;
  Status s;
  // Sequence 99 is less than 100, should not find
  bool found = Get("key1", 99, &value, &s);
  EXPECT_FALSE(found);
}

TEST_F(MemTableTest_353, MultipleVersionsSameKey_353) {
  Add(1, kTypeValue, "key", "v1");
  Add(2, kTypeValue, "key", "v2");
  Add(3, kTypeValue, "key", "v3");
  Add(4, kTypeDeletion, "key", "");
  Add(5, kTypeValue, "key", "v5");

  std::string value;
  Status s;

  EXPECT_TRUE(Get("key", 5, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("v5", value);

  EXPECT_TRUE(Get("key", 4, &value, &s));
  EXPECT_TRUE(s.IsNotFound());

  EXPECT_TRUE(Get("key", 3, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("v3", value);

  EXPECT_TRUE(Get("key", 2, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("v2", value);

  EXPECT_TRUE(Get("key", 1, &value, &s));
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("v1", value);

  EXPECT_FALSE(Get("key", 0, &value, &s));
}

TEST_F(MemTableTest_353, RefUnrefDoesNotCrash_353) {
  // Create a separate MemTable and verify Ref/Unref work
  MemTable* t = new MemTable(*cmp_);
  t->Ref();
  t->Ref();  // second ref
  t->Unref();
  t->Unref();  // should delete
  // No crash expected
}

TEST_F(MemTableTest_353, IteratorSeekToLast_353) {
  Add(1, kTypeValue, "a", "va");
  Add(2, kTypeValue, "z", "vz");

  Iterator* iter = table_->NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  // The last entry by internal key order should be "z" with lower seq or just "z"
  delete iter;
}

TEST_F(MemTableTest_353, IteratorPrevFromEnd_353) {
  Add(1, kTypeValue, "a", "va");
  Add(2, kTypeValue, "b", "vb");
  Add(3, kTypeValue, "c", "vc");

  Iterator* iter = table_->NewIterator();
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());

  int count = 1;
  iter->Prev();
  while (iter->Valid()) {
    count++;
    iter->Prev();
  }
  EXPECT_EQ(3, count);
  delete iter;
}

}  // namespace leveldb
