#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// Replicate the C wrapper struct as defined in db/c.cc
struct leveldb_writebatch_t {
  leveldb::WriteBatch rep;
};

// Forward declare the C function under test
extern "C" {
void leveldb_writebatch_delete(leveldb_writebatch_t* b, const char* key,
                               size_t klen);
}

// If the C function isn't linked as extern "C", we can define it inline
// matching the implementation:
// void leveldb_writebatch_delete(leveldb_writebatch_t* b, const char* key,
//                                size_t klen) {
//   b->rep.Delete(leveldb::Slice(key, klen));
// }

// Mock handler to observe what operations are in the WriteBatch
class MockHandler : public leveldb::WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const leveldb::Slice& key, const leveldb::Slice& value), (override));
  MOCK_METHOD(void, Delete, (const leveldb::Slice& key), (override));
};

class WriteBatchDeleteTest_248 : public ::testing::Test {
 protected:
  void SetUp() override {
    batch_ = new leveldb_writebatch_t();
  }

  void TearDown() override {
    delete batch_;
  }

  leveldb_writebatch_t* batch_;
};

// Test that calling leveldb_writebatch_delete adds a delete operation
TEST_F(WriteBatchDeleteTest_248, SingleDelete_248) {
  const char* key = "testkey";
  size_t klen = strlen(key);

  leveldb_writebatch_delete(batch_, key, klen);

  MockHandler handler;
  EXPECT_CALL(handler, Delete(leveldb::Slice("testkey", 7))).Times(1);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test that calling leveldb_writebatch_delete with an empty key works
TEST_F(WriteBatchDeleteTest_248, EmptyKey_248) {
  const char* key = "";
  size_t klen = 0;

  leveldb_writebatch_delete(batch_, key, klen);

  MockHandler handler;
  EXPECT_CALL(handler, Delete(leveldb::Slice("", 0))).Times(1);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test that multiple deletes are recorded in order
TEST_F(WriteBatchDeleteTest_248, MultipleDeletes_248) {
  const char* key1 = "key1";
  const char* key2 = "key2";
  const char* key3 = "key3";

  leveldb_writebatch_delete(batch_, key1, strlen(key1));
  leveldb_writebatch_delete(batch_, key2, strlen(key2));
  leveldb_writebatch_delete(batch_, key3, strlen(key3));

  MockHandler handler;
  {
    ::testing::InSequence seq;
    EXPECT_CALL(handler, Delete(leveldb::Slice("key1", 4))).Times(1);
    EXPECT_CALL(handler, Delete(leveldb::Slice("key2", 4))).Times(1);
    EXPECT_CALL(handler, Delete(leveldb::Slice("key3", 4))).Times(1);
  }
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test delete with binary key containing null bytes
TEST_F(WriteBatchDeleteTest_248, BinaryKeyWithNullBytes_248) {
  const char key[] = "ke\0y";
  size_t klen = 4;  // includes the null byte in the middle

  leveldb_writebatch_delete(batch_, key, klen);

  MockHandler handler;
  EXPECT_CALL(handler, Delete(leveldb::Slice(key, 4))).Times(1);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test that delete increases the approximate size of the batch
TEST_F(WriteBatchDeleteTest_248, DeleteIncreasesApproximateSize_248) {
  size_t initial_size = batch_->rep.ApproximateSize();

  const char* key = "somekey";
  leveldb_writebatch_delete(batch_, key, strlen(key));

  size_t after_size = batch_->rep.ApproximateSize();
  EXPECT_GT(after_size, initial_size);
}

// Test that partial key length is respected
TEST_F(WriteBatchDeleteTest_248, PartialKeyLength_248) {
  const char* key = "longtestkey";
  size_t klen = 4;  // Only use "long"

  leveldb_writebatch_delete(batch_, key, klen);

  MockHandler handler;
  EXPECT_CALL(handler, Delete(leveldb::Slice("long", 4))).Times(1);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test that Clear after delete removes the delete operation
TEST_F(WriteBatchDeleteTest_248, ClearAfterDelete_248) {
  const char* key = "testkey";
  leveldb_writebatch_delete(batch_, key, strlen(key));

  batch_->rep.Clear();

  MockHandler handler;
  EXPECT_CALL(handler, Delete(::testing::_)).Times(0);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test delete with a very long key
TEST_F(WriteBatchDeleteTest_248, LongKey_248) {
  std::string long_key(10000, 'x');

  leveldb_writebatch_delete(batch_, long_key.data(), long_key.size());

  MockHandler handler;
  EXPECT_CALL(handler, Delete(leveldb::Slice(long_key))).Times(1);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test that delete with single character key works
TEST_F(WriteBatchDeleteTest_248, SingleCharKey_248) {
  const char* key = "a";
  leveldb_writebatch_delete(batch_, key, 1);

  MockHandler handler;
  EXPECT_CALL(handler, Delete(leveldb::Slice("a", 1))).Times(1);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// Test that deleting the same key multiple times records all operations
TEST_F(WriteBatchDeleteTest_248, DuplicateKeyDeletes_248) {
  const char* key = "samekey";
  leveldb_writebatch_delete(batch_, key, strlen(key));
  leveldb_writebatch_delete(batch_, key, strlen(key));

  MockHandler handler;
  EXPECT_CALL(handler, Delete(leveldb::Slice("samekey", 7))).Times(2);
  EXPECT_CALL(handler, Put(::testing::_, ::testing::_)).Times(0);

  leveldb::Status s = batch_->rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}
