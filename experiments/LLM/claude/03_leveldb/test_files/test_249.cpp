#include "gtest/gtest.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"

#include <string>
#include <vector>
#include <cstring>

// Replicate the C API structs and function as defined in db/c.cc
struct leveldb_writebatch_t {
  leveldb::WriteBatch rep;
};

extern "C" {

void leveldb_writebatch_iterate(
    const leveldb_writebatch_t* b, void* state,
    void (*put)(void*, const char* k, size_t klen, const char* v, size_t vlen),
    void (*deleted)(void*, const char* k, size_t klen)) {
  class H : public leveldb::WriteBatch::Handler {
   public:
    void* state_;
    void (*put_)(void*, const char* k, size_t klen, const char* v, size_t vlen);
    void (*deleted_)(void*, const char* k, size_t klen);
    void Put(const leveldb::Slice& key, const leveldb::Slice& value) override {
      (*put_)(state_, key.data(), key.size(), value.data(), value.size());
    }
    void Delete(const leveldb::Slice& key) override {
      (*deleted_)(state_, key.data(), key.size());
    }
  };
  H handler;
  handler.state_ = state;
  handler.put_ = put;
  handler.deleted_ = deleted;
  b->rep.Iterate(&handler);
}

}  // extern "C"

// Test state to record calls
struct IterateState {
  struct PutRecord {
    std::string key;
    std::string value;
  };
  struct DeleteRecord {
    std::string key;
  };
  std::vector<PutRecord> puts;
  std::vector<DeleteRecord> deletes;
  // Track order of operations: 'P' for put, 'D' for delete
  std::vector<char> order;
};

static void TestPutCallback(void* state, const char* k, size_t klen,
                            const char* v, size_t vlen) {
  auto* s = static_cast<IterateState*>(state);
  s->puts.push_back({std::string(k, klen), std::string(v, vlen)});
  s->order.push_back('P');
}

static void TestDeleteCallback(void* state, const char* k, size_t klen) {
  auto* s = static_cast<IterateState*>(state);
  s->deletes.push_back({std::string(k, klen)});
  s->order.push_back('D');
}

class WriteBatchIterateTest_249 : public ::testing::Test {
 protected:
  leveldb_writebatch_t batch_;
  IterateState state_;

  void SetUp() override {
    batch_.rep.Clear();
    state_ = IterateState();
  }
};

// Test iterating over an empty batch produces no callbacks
TEST_F(WriteBatchIterateTest_249, EmptyBatchNoCallbacks_249) {
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  EXPECT_TRUE(state_.puts.empty());
  EXPECT_TRUE(state_.deletes.empty());
  EXPECT_TRUE(state_.order.empty());
}

// Test iterating with a single Put
TEST_F(WriteBatchIterateTest_249, SinglePut_249) {
  batch_.rep.Put("key1", "value1");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  EXPECT_EQ(state_.puts[0].key, "key1");
  EXPECT_EQ(state_.puts[0].value, "value1");
  EXPECT_TRUE(state_.deletes.empty());
  ASSERT_EQ(state_.order.size(), 1u);
  EXPECT_EQ(state_.order[0], 'P');
}

// Test iterating with a single Delete
TEST_F(WriteBatchIterateTest_249, SingleDelete_249) {
  batch_.rep.Delete("key2");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  EXPECT_TRUE(state_.puts.empty());
  ASSERT_EQ(state_.deletes.size(), 1u);
  EXPECT_EQ(state_.deletes[0].key, "key2");
  ASSERT_EQ(state_.order.size(), 1u);
  EXPECT_EQ(state_.order[0], 'D');
}

// Test iterating with multiple Puts
TEST_F(WriteBatchIterateTest_249, MultiplePuts_249) {
  batch_.rep.Put("a", "1");
  batch_.rep.Put("b", "2");
  batch_.rep.Put("c", "3");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 3u);
  EXPECT_EQ(state_.puts[0].key, "a");
  EXPECT_EQ(state_.puts[0].value, "1");
  EXPECT_EQ(state_.puts[1].key, "b");
  EXPECT_EQ(state_.puts[1].value, "2");
  EXPECT_EQ(state_.puts[2].key, "c");
  EXPECT_EQ(state_.puts[2].value, "3");
  EXPECT_TRUE(state_.deletes.empty());
}

// Test iterating with multiple Deletes
TEST_F(WriteBatchIterateTest_249, MultipleDeletes_249) {
  batch_.rep.Delete("x");
  batch_.rep.Delete("y");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  EXPECT_TRUE(state_.puts.empty());
  ASSERT_EQ(state_.deletes.size(), 2u);
  EXPECT_EQ(state_.deletes[0].key, "x");
  EXPECT_EQ(state_.deletes[1].key, "y");
}

// Test interleaved Puts and Deletes maintain order
TEST_F(WriteBatchIterateTest_249, InterleavedPutsAndDeletes_249) {
  batch_.rep.Put("k1", "v1");
  batch_.rep.Delete("k2");
  batch_.rep.Put("k3", "v3");
  batch_.rep.Delete("k4");
  batch_.rep.Delete("k5");
  batch_.rep.Put("k6", "v6");

  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);

  ASSERT_EQ(state_.puts.size(), 3u);
  ASSERT_EQ(state_.deletes.size(), 3u);
  ASSERT_EQ(state_.order.size(), 6u);

  // Check order
  EXPECT_EQ(state_.order[0], 'P');
  EXPECT_EQ(state_.order[1], 'D');
  EXPECT_EQ(state_.order[2], 'P');
  EXPECT_EQ(state_.order[3], 'D');
  EXPECT_EQ(state_.order[4], 'D');
  EXPECT_EQ(state_.order[5], 'P');

  // Check put contents in order
  EXPECT_EQ(state_.puts[0].key, "k1");
  EXPECT_EQ(state_.puts[0].value, "v1");
  EXPECT_EQ(state_.puts[1].key, "k3");
  EXPECT_EQ(state_.puts[1].value, "v3");
  EXPECT_EQ(state_.puts[2].key, "k6");
  EXPECT_EQ(state_.puts[2].value, "v6");

  // Check delete contents in order
  EXPECT_EQ(state_.deletes[0].key, "k2");
  EXPECT_EQ(state_.deletes[1].key, "k4");
  EXPECT_EQ(state_.deletes[2].key, "k5");
}

// Test empty key and value
TEST_F(WriteBatchIterateTest_249, EmptyKeyAndValue_249) {
  batch_.rep.Put("", "");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  EXPECT_EQ(state_.puts[0].key, "");
  EXPECT_EQ(state_.puts[0].value, "");
}

// Test empty key in Delete
TEST_F(WriteBatchIterateTest_249, EmptyKeyDelete_249) {
  batch_.rep.Delete("");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.deletes.size(), 1u);
  EXPECT_EQ(state_.deletes[0].key, "");
}

// Test key and value with embedded null characters (binary data)
TEST_F(WriteBatchIterateTest_249, BinaryKeyAndValue_249) {
  std::string key("ke\0y", 4);
  std::string value("va\0lue", 6);
  batch_.rep.Put(key, value);
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  EXPECT_EQ(state_.puts[0].key.size(), 4u);
  EXPECT_EQ(state_.puts[0].key, key);
  EXPECT_EQ(state_.puts[0].value.size(), 6u);
  EXPECT_EQ(state_.puts[0].value, value);
}

// Test binary key in Delete
TEST_F(WriteBatchIterateTest_249, BinaryKeyDelete_249) {
  std::string key("de\0l", 4);
  batch_.rep.Delete(key);
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.deletes.size(), 1u);
  EXPECT_EQ(state_.deletes[0].key.size(), 4u);
  EXPECT_EQ(state_.deletes[0].key, key);
}

// Test large key and value
TEST_F(WriteBatchIterateTest_249, LargeKeyAndValue_249) {
  std::string large_key(10000, 'K');
  std::string large_value(100000, 'V');
  batch_.rep.Put(large_key, large_value);
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  EXPECT_EQ(state_.puts[0].key, large_key);
  EXPECT_EQ(state_.puts[0].value, large_value);
}

// Test that after Clear and adding new ops, iterate sees only new ops
TEST_F(WriteBatchIterateTest_249, ClearAndReiterate_249) {
  batch_.rep.Put("old_key", "old_value");
  batch_.rep.Clear();
  batch_.rep.Put("new_key", "new_value");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  EXPECT_EQ(state_.puts[0].key, "new_key");
  EXPECT_EQ(state_.puts[0].value, "new_value");
}

// Test that state pointer is correctly passed through
TEST_F(WriteBatchIterateTest_249, StatePointerPassedCorrectly_249) {
  IterateState another_state;
  batch_.rep.Put("test", "data");
  leveldb_writebatch_iterate(&batch_, &another_state, TestPutCallback,
                             TestDeleteCallback);
  // The original state_ should be untouched
  EXPECT_TRUE(state_.puts.empty());
  // The other state should have the record
  ASSERT_EQ(another_state.puts.size(), 1u);
  EXPECT_EQ(another_state.puts[0].key, "test");
  EXPECT_EQ(another_state.puts[0].value, "data");
}

// Test iterating the same batch twice produces same results
TEST_F(WriteBatchIterateTest_249, IterateTwice_249) {
  batch_.rep.Put("k", "v");
  batch_.rep.Delete("d");

  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  ASSERT_EQ(state_.deletes.size(), 1u);

  IterateState state2;
  leveldb_writebatch_iterate(&batch_, &state2, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state2.puts.size(), 1u);
  ASSERT_EQ(state2.deletes.size(), 1u);
  EXPECT_EQ(state2.puts[0].key, "k");
  EXPECT_EQ(state2.puts[0].value, "v");
  EXPECT_EQ(state2.deletes[0].key, "d");
}

// Test with Append: appending another batch's operations
TEST_F(WriteBatchIterateTest_249, AppendedBatch_249) {
  leveldb_writebatch_t batch2;
  batch2.rep.Put("appended_key", "appended_value");
  batch2.rep.Delete("appended_del");

  batch_.rep.Put("original", "val");
  batch_.rep.Append(batch2.rep);

  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);

  ASSERT_EQ(state_.puts.size(), 2u);
  EXPECT_EQ(state_.puts[0].key, "original");
  EXPECT_EQ(state_.puts[0].value, "val");
  EXPECT_EQ(state_.puts[1].key, "appended_key");
  EXPECT_EQ(state_.puts[1].value, "appended_value");

  ASSERT_EQ(state_.deletes.size(), 1u);
  EXPECT_EQ(state_.deletes[0].key, "appended_del");
}

// Test many operations to verify no data corruption
TEST_F(WriteBatchIterateTest_249, ManyOperations_249) {
  const int kCount = 1000;
  for (int i = 0; i < kCount; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    batch_.rep.Put(key, value);
  }
  for (int i = 0; i < kCount; i++) {
    std::string key = "del" + std::to_string(i);
    batch_.rep.Delete(key);
  }

  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);

  ASSERT_EQ(state_.puts.size(), static_cast<size_t>(kCount));
  ASSERT_EQ(state_.deletes.size(), static_cast<size_t>(kCount));

  for (int i = 0; i < kCount; i++) {
    EXPECT_EQ(state_.puts[i].key, "key" + std::to_string(i));
    EXPECT_EQ(state_.puts[i].value, "value" + std::to_string(i));
    EXPECT_EQ(state_.deletes[i].key, "del" + std::to_string(i));
  }
}

// Test that key/value sizes are correctly reported
TEST_F(WriteBatchIterateTest_249, KeyValueSizesCorrect_249) {
  std::string key(5, 'a');    // "aaaaa"
  std::string value(10, 'b'); // "bbbbbbbbbb"
  batch_.rep.Put(key, value);
  
  // Use a different callback that checks sizes explicitly
  struct SizeCheckState {
    size_t key_len = 0;
    size_t val_len = 0;
    bool called = false;
  };
  SizeCheckState scs;

  auto put_cb = [](void* st, const char* k, size_t klen, const char* v,
                   size_t vlen) {
    auto* s = static_cast<SizeCheckState*>(st);
    s->key_len = klen;
    s->val_len = vlen;
    s->called = true;
  };
  auto del_cb = [](void* st, const char* k, size_t klen) {};

  leveldb_writebatch_iterate(&batch_, &scs, put_cb, del_cb);
  EXPECT_TRUE(scs.called);
  EXPECT_EQ(scs.key_len, 5u);
  EXPECT_EQ(scs.val_len, 10u);
}

// Test Put with empty value but non-empty key
TEST_F(WriteBatchIterateTest_249, NonEmptyKeyEmptyValue_249) {
  batch_.rep.Put("mykey", "");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  EXPECT_EQ(state_.puts[0].key, "mykey");
  EXPECT_EQ(state_.puts[0].value, "");
}

// Test Put with empty key but non-empty value
TEST_F(WriteBatchIterateTest_249, EmptyKeyNonEmptyValue_249) {
  batch_.rep.Put("", "myvalue");
  leveldb_writebatch_iterate(&batch_, &state_, TestPutCallback,
                             TestDeleteCallback);
  ASSERT_EQ(state_.puts.size(), 1u);
  EXPECT_EQ(state_.puts[0].key, "");
  EXPECT_EQ(state_.puts[0].value, "myvalue");
}
