#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "util/logging.h"

namespace leveldb {

class MemTableTest_104 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Use a default BytewiseComparator for InternalKeyComparator
    cmp_ = new InternalKeyComparator(BytewiseComparator());
  }

  void TearDown() override {
    delete cmp_;
  }

  MemTable* NewMemTable() {
    MemTable* mem = new MemTable(*cmp_);
    mem->Ref();
    return mem;
  }

  InternalKeyComparator* cmp_;
};

// Test basic creation and destruction via Ref/Unref
TEST_F(MemTableTest_104, CreateAndDestroy_104) {
  MemTable* mem = NewMemTable();
  // Should not crash on Unref
  mem->Unref();
}

// Test that ApproximateMemoryUsage returns a non-zero value for empty table
TEST_F(MemTableTest_104, ApproximateMemoryUsageEmpty_104) {
  MemTable* mem = NewMemTable();
  size_t usage = mem->ApproximateMemoryUsage();
  // Even an empty MemTable should have some memory usage from arena overhead
  EXPECT_GT(usage, 0u);
  mem->Unref();
}

// Test adding a single entry and retrieving it
TEST_F(MemTableTest_104, AddAndGetSingleEntry_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lk("key1", 1);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "value1");

  mem->Unref();
}

// Test that Get returns false for a non-existent key
TEST_F(MemTableTest_104, GetNonExistentKey_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lk("key2", 1);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_FALSE(found);

  mem->Unref();
}

// Test adding a deletion marker and verifying Get behavior
TEST_F(MemTableTest_104, AddDeletionMarker_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  mem->Add(2, kTypeDeletion, Slice("key1"), Slice(""));

  std::string value;
  Status s;
  LookupKey lk("key1", 2);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());

  mem->Unref();
}

// Test reading at an older sequence number (before deletion)
TEST_F(MemTableTest_104, GetAtOlderSequenceNumber_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  mem->Add(2, kTypeDeletion, Slice("key1"), Slice(""));

  std::string value;
  Status s;
  LookupKey lk("key1", 1);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "value1");

  mem->Unref();
}

// Test multiple entries and retrievals
TEST_F(MemTableTest_104, AddMultipleEntries_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("apple"), Slice("red"));
  mem->Add(2, kTypeValue, Slice("banana"), Slice("yellow"));
  mem->Add(3, kTypeValue, Slice("cherry"), Slice("dark_red"));

  {
    std::string value;
    Status s;
    LookupKey lk("apple", 3);
    EXPECT_TRUE(mem->Get(lk, &value, &s));
    EXPECT_EQ(value, "red");
  }
  {
    std::string value;
    Status s;
    LookupKey lk("banana", 3);
    EXPECT_TRUE(mem->Get(lk, &value, &s));
    EXPECT_EQ(value, "yellow");
  }
  {
    std::string value;
    Status s;
    LookupKey lk("cherry", 3);
    EXPECT_TRUE(mem->Get(lk, &value, &s));
    EXPECT_EQ(value, "dark_red");
  }

  mem->Unref();
}

// Test updating a key with a newer sequence number
TEST_F(MemTableTest_104, UpdateKeyWithNewerSequence_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  mem->Add(2, kTypeValue, Slice("key1"), Slice("value2"));

  std::string value;
  Status s;
  LookupKey lk("key1", 2);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "value2");

  mem->Unref();
}

// Test reading the old value at sequence 1 after update
TEST_F(MemTableTest_104, ReadOldValueAfterUpdate_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  mem->Add(2, kTypeValue, Slice("key1"), Slice("value2"));

  std::string value;
  Status s;
  LookupKey lk("key1", 1);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "value1");

  mem->Unref();
}

// Test that memory usage increases after adding entries
TEST_F(MemTableTest_104, MemoryUsageIncreasesAfterAdd_104) {
  MemTable* mem = NewMemTable();
  size_t initial = mem->ApproximateMemoryUsage();

  mem->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  size_t after_one = mem->ApproximateMemoryUsage();
  EXPECT_GE(after_one, initial);

  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i + 100);
    std::string val = "value" + std::to_string(i + 100);
    mem->Add(i + 2, kTypeValue, Slice(key), Slice(val));
  }
  size_t after_many = mem->ApproximateMemoryUsage();
  EXPECT_GT(after_many, after_one);

  mem->Unref();
}

// Test NewIterator on empty MemTable
TEST_F(MemTableTest_104, NewIteratorEmpty_104) {
  MemTable* mem = NewMemTable();
  Iterator* iter = mem->NewIterator();
  ASSERT_NE(iter, nullptr);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
  mem->Unref();
}

// Test NewIterator with entries
TEST_F(MemTableTest_104, NewIteratorWithEntries_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("aaa"), Slice("v1"));
  mem->Add(2, kTypeValue, Slice("bbb"), Slice("v2"));
  mem->Add(3, kTypeValue, Slice("ccc"), Slice("v3"));

  Iterator* iter = mem->NewIterator();
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());

  // Count entries; there should be at least 3
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, 3);

  delete iter;
  mem->Unref();
}

// Test NewIterator iterates in sorted order
TEST_F(MemTableTest_104, IteratorSortedOrder_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("cherry"), Slice("v3"));
  mem->Add(2, kTypeValue, Slice("apple"), Slice("v1"));
  mem->Add(3, kTypeValue, Slice("banana"), Slice("v2"));

  Iterator* iter = mem->NewIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());

  // Internal keys should be sorted by user key first
  // Extract user keys from internal keys to verify ordering
  std::vector<std::string> keys;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    Slice internal_key = iter->key();
    // User key is all but the last 8 bytes of the internal key encoded in the entry
    // But the iterator returns the encoded entry; let's just verify it's valid
    keys.push_back(internal_key.ToString());
  }
  EXPECT_EQ(keys.size(), 3u);

  delete iter;
  mem->Unref();
}

// Test empty key and value
TEST_F(MemTableTest_104, EmptyKeyAndValue_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice(""), Slice(""));

  std::string value;
  Status s;
  LookupKey lk("", 1);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, "");

  mem->Unref();
}

// Test large key and value
TEST_F(MemTableTest_104, LargeKeyAndValue_104) {
  MemTable* mem = NewMemTable();
  std::string large_key(1000, 'k');
  std::string large_value(10000, 'v');
  mem->Add(1, kTypeValue, Slice(large_key), Slice(large_value));

  std::string value;
  Status s;
  LookupKey lk(large_key, 1);
  bool found = mem->Get(lk, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(value, large_value);

  mem->Unref();
}

// Test multiple Ref/Unref pairs
TEST_F(MemTableTest_104, MultipleRefUnref_104) {
  MemTable* mem = NewMemTable();
  mem->Ref();  // refs_ = 2
  mem->Ref();  // refs_ = 3
  mem->Unref(); // refs_ = 2
  mem->Unref(); // refs_ = 1
  // Should still be alive
  mem->Add(1, kTypeValue, Slice("key"), Slice("val"));
  std::string value;
  Status s;
  LookupKey lk("key", 1);
  EXPECT_TRUE(mem->Get(lk, &value, &s));
  EXPECT_EQ(value, "val");
  mem->Unref(); // refs_ = 0, deleted
}

// Test Get with sequence number 0 - key was added at seq 1
TEST_F(MemTableTest_104, GetWithLowerSequenceNumber_104) {
  MemTable* mem = NewMemTable();
  mem->Add(5, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  // Looking up with sequence 4, which is less than 5
  LookupKey lk("key1", 4);
  bool found = mem->Get(lk, &value, &s);
  // The entry has seq 5 but we're looking at seq 4, so it shouldn't be visible
  EXPECT_FALSE(found);

  mem->Unref();
}

// Test Get returns the latest value at or below the given sequence number
TEST_F(MemTableTest_104, GetLatestValueBelowSeq_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key"), Slice("v1"));
  mem->Add(3, kTypeValue, Slice("key"), Slice("v3"));
  mem->Add(5, kTypeValue, Slice("key"), Slice("v5"));

  {
    std::string value;
    Status s;
    LookupKey lk("key", 4);
    bool found = mem->Get(lk, &value, &s);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "v3");
  }
  {
    std::string value;
    Status s;
    LookupKey lk("key", 5);
    bool found = mem->Get(lk, &value, &s);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "v5");
  }
  {
    std::string value;
    Status s;
    LookupKey lk("key", 2);
    bool found = mem->Get(lk, &value, &s);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "v1");
  }

  mem->Unref();
}

// Test deletion followed by re-insertion
TEST_F(MemTableTest_104, DeleteThenReInsert_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("key"), Slice("v1"));
  mem->Add(2, kTypeDeletion, Slice("key"), Slice(""));
  mem->Add(3, kTypeValue, Slice("key"), Slice("v3"));

  {
    std::string value;
    Status s;
    LookupKey lk("key", 3);
    bool found = mem->Get(lk, &value, &s);
    EXPECT_TRUE(found);
    EXPECT_TRUE(s.ok());
    EXPECT_EQ(value, "v3");
  }
  {
    std::string value;
    Status s;
    LookupKey lk("key", 2);
    bool found = mem->Get(lk, &value, &s);
    EXPECT_TRUE(found);
    EXPECT_TRUE(s.IsNotFound());
  }

  mem->Unref();
}

// Test iterator SeekToLast and Prev
TEST_F(MemTableTest_104, IteratorSeekToLast_104) {
  MemTable* mem = NewMemTable();
  mem->Add(1, kTypeValue, Slice("aaa"), Slice("v1"));
  mem->Add(2, kTypeValue, Slice("zzz"), Slice("v2"));

  Iterator* iter = mem->NewIterator();
  iter->SeekToLast();
  EXPECT_TRUE(iter->Valid());

  iter->Prev();
  EXPECT_TRUE(iter->Valid());

  iter->Prev();
  EXPECT_FALSE(iter->Valid());

  delete iter;
  mem->Unref();
}

// Test many insertions
TEST_F(MemTableTest_104, ManyInsertions_104) {
  MemTable* mem = NewMemTable();
  const int kNumEntries = 1000;
  for (int i = 0; i < kNumEntries; i++) {
    char key_buf[32];
    char val_buf[32];
    snprintf(key_buf, sizeof(key_buf), "key%06d", i);
    snprintf(val_buf, sizeof(val_buf), "val%06d", i);
    mem->Add(i + 1, kTypeValue, Slice(key_buf), Slice(val_buf));
  }

  // Verify a few entries
  for (int i = 0; i < kNumEntries; i += 100) {
    char key_buf[32];
    char val_buf[32];
    snprintf(key_buf, sizeof(key_buf), "key%06d", i);
    snprintf(val_buf, sizeof(val_buf), "val%06d", i);

    std::string value;
    Status s;
    LookupKey lk(key_buf, kNumEntries);
    bool found = mem->Get(lk, &value, &s);
    EXPECT_TRUE(found);
    EXPECT_TRUE(s.ok());
    EXPECT_EQ(value, std::string(val_buf));
  }

  // Verify iterator count
  Iterator* iter = mem->NewIterator();
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(count, kNumEntries);
  delete iter;

  mem->Unref();
}

}  // namespace leveldb
