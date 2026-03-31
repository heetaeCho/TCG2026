#include "gtest/gtest.h"
#include "db/db_impl.h"
#include "db/db_iter.h"
#include "leveldb/comparator.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "util/testutil.h"

#include <string>
#include <vector>

namespace leveldb {

class DBIterTest_369 : public testing::Test {
 protected:
  DB* db_;
  std::string dbname_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "db_iter_test_369";
    options_.create_if_missing = true;
    DestroyDB(dbname_, options_);
    ASSERT_TRUE(DB::Open(options_, dbname_, &db_).ok());
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }

  void Put(const std::string& key, const std::string& value) {
    ASSERT_TRUE(db_->Put(WriteOptions(), key, value).ok());
  }

  void Delete(const std::string& key) {
    ASSERT_TRUE(db_->Delete(WriteOptions(), key).ok());
  }

  std::string Get(const std::string& key) {
    std::string value;
    Status s = db_->Get(ReadOptions(), key, &value);
    if (s.IsNotFound()) return "NOT_FOUND";
    EXPECT_TRUE(s.ok()) << s.ToString();
    return value;
  }
};

// Test that NewDBIterator creates a valid iterator that can iterate over entries
TEST_F(DBIterTest_369, BasicIteration_369) {
  Put("a", "va");
  Put("b", "vb");
  Put("c", "vc");

  Iterator* iter = db_->NewIterator(ReadOptions());
  ASSERT_TRUE(iter != nullptr);

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  EXPECT_EQ("va", iter->value().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());
  EXPECT_EQ("vb", iter->value().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  EXPECT_EQ("vc", iter->value().ToString());

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test iterating over an empty database
TEST_F(DBIterTest_369, EmptyDatabase_369) {
  Iterator* iter = db_->NewIterator(ReadOptions());
  ASSERT_TRUE(iter != nullptr);

  iter->SeekToFirst();
  ASSERT_FALSE(iter->Valid());

  iter->SeekToLast();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test SeekToLast functionality
TEST_F(DBIterTest_369, SeekToLast_369) {
  Put("a", "va");
  Put("b", "vb");
  Put("c", "vc");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  EXPECT_EQ("vc", iter->value().ToString());

  delete iter;
}

// Test Prev functionality
TEST_F(DBIterTest_369, PrevIteration_369) {
  Put("a", "va");
  Put("b", "vb");
  Put("c", "vc");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  iter->Prev();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test Seek to a specific key
TEST_F(DBIterTest_369, SeekToSpecificKey_369) {
  Put("a", "va");
  Put("c", "vc");
  Put("e", "ve");

  Iterator* iter = db_->NewIterator(ReadOptions());

  iter->Seek("c");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());
  EXPECT_EQ("vc", iter->value().ToString());

  delete iter;
}

// Test Seek to a key that doesn't exist (should land on next key)
TEST_F(DBIterTest_369, SeekToNonExistentKey_369) {
  Put("a", "va");
  Put("c", "vc");
  Put("e", "ve");

  Iterator* iter = db_->NewIterator(ReadOptions());

  iter->Seek("b");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  delete iter;
}

// Test Seek past all keys
TEST_F(DBIterTest_369, SeekPastAllKeys_369) {
  Put("a", "va");
  Put("b", "vb");

  Iterator* iter = db_->NewIterator(ReadOptions());

  iter->Seek("z");
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test that deleted keys are not visible
TEST_F(DBIterTest_369, DeletedKeysNotVisible_369) {
  Put("a", "va");
  Put("b", "vb");
  Put("c", "vc");
  Delete("b");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test that overwritten keys show the latest value
TEST_F(DBIterTest_369, OverwrittenKeys_369) {
  Put("a", "v1");
  Put("a", "v2");
  Put("a", "v3");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  EXPECT_EQ("v3", iter->value().ToString());

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test single entry iteration
TEST_F(DBIterTest_369, SingleEntry_369) {
  Put("only", "value");

  Iterator* iter = db_->NewIterator(ReadOptions());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("only", iter->key().ToString());
  EXPECT_EQ("value", iter->value().ToString());

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  // Reset and go backward
  iter->SeekToLast();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("only", iter->key().ToString());

  iter->Prev();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test forward and backward iteration consistency
TEST_F(DBIterTest_369, ForwardAndBackward_369) {
  Put("a", "va");
  Put("b", "vb");
  Put("c", "vc");
  Put("d", "vd");

  Iterator* iter = db_->NewIterator(ReadOptions());

  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  iter->Prev();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("b", iter->key().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("c", iter->key().ToString());

  delete iter;
}

// Test status after valid iteration
TEST_F(DBIterTest_369, StatusOkDuringIteration_369) {
  Put("a", "va");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());

  iter->Next();
  ASSERT_FALSE(iter->Valid());
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test with many keys to ensure iteration handles larger datasets
TEST_F(DBIterTest_369, ManyKeys_369) {
  const int kNumKeys = 100;
  for (int i = 0; i < kNumKeys; i++) {
    char buf[10];
    std::snprintf(buf, sizeof(buf), "key%05d", i);
    Put(buf, std::string(buf) + "_val");
  }

  Iterator* iter = db_->NewIterator(ReadOptions());
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(kNumKeys, count);
  EXPECT_TRUE(iter->status().ok());

  // Count backward
  count = 0;
  for (iter->SeekToLast(); iter->Valid(); iter->Prev()) {
    count++;
  }
  EXPECT_EQ(kNumKeys, count);
  EXPECT_TRUE(iter->status().ok());

  delete iter;
}

// Test snapshot isolation: iterator should not see writes after creation
TEST_F(DBIterTest_369, SnapshotIsolation_369) {
  Put("a", "va");
  Put("b", "vb");

  Iterator* iter = db_->NewIterator(ReadOptions());

  // Write after iterator creation
  Put("c", "vc");
  Put("d", "vd");

  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  // Iterator should see at most the entries present at iterator creation time
  // (snapshot semantics). It should see "a" and "b" but not "c" and "d".
  EXPECT_EQ(2, count);

  delete iter;
}

// Test iterating after delete and re-insert
TEST_F(DBIterTest_369, DeleteAndReInsert_369) {
  Put("a", "v1");
  Delete("a");
  Put("a", "v2");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->SeekToFirst();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());
  EXPECT_EQ("v2", iter->value().ToString());

  iter->Next();
  ASSERT_FALSE(iter->Valid());

  delete iter;
}

// Test Seek with empty string key
TEST_F(DBIterTest_369, SeekEmptyStringKey_369) {
  Put("", "empty_key_value");
  Put("a", "va");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->Seek("");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("", iter->key().ToString());
  EXPECT_EQ("empty_key_value", iter->value().ToString());

  iter->Next();
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("a", iter->key().ToString());

  delete iter;
}

// Test with keys that have common prefixes
TEST_F(DBIterTest_369, CommonPrefixKeys_369) {
  Put("abc", "v1");
  Put("abd", "v2");
  Put("abe", "v3");

  Iterator* iter = db_->NewIterator(ReadOptions());
  iter->Seek("abd");
  ASSERT_TRUE(iter->Valid());
  EXPECT_EQ("abd", iter->key().ToString());
  EXPECT_EQ("v2", iter->value().ToString());

  delete iter;
}

// Test that multiple iterators can coexist
TEST_F(DBIterTest_369, MultipleIterators_369) {
  Put("a", "va");
  Put("b", "vb");
  Put("c", "vc");

  Iterator* iter1 = db_->NewIterator(ReadOptions());
  Iterator* iter2 = db_->NewIterator(ReadOptions());

  iter1->SeekToFirst();
  iter2->SeekToLast();

  ASSERT_TRUE(iter1->Valid());
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ("a", iter1->key().ToString());
  EXPECT_EQ("c", iter2->key().ToString());

  iter1->Next();
  iter2->Prev();
  ASSERT_TRUE(iter1->Valid());
  ASSERT_TRUE(iter2->Valid());
  EXPECT_EQ("b", iter1->key().ToString());
  EXPECT_EQ("b", iter2->key().ToString());

  delete iter1;
  delete iter2;
}

}  // namespace leveldb
