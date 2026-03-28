#include "gtest/gtest.h"
#include "leveldb/c.h"

#include <cstring>
#include <string>
#include <vector>

// We need to test the C API function leveldb_writebatch_clear
// through the public C interface provided by leveldb.

class WriteBatchClearTest_246 : public ::testing::Test {
 protected:
  void SetUp() override {
    batch_ = leveldb_writebatch_create();
    ASSERT_NE(batch_, nullptr);
  }

  void TearDown() override {
    if (batch_) {
      leveldb_writebatch_destroy(batch_);
    }
  }

  leveldb_writebatch_t* batch_;
};

// Helper state for iterate callback
struct IterateState {
  std::vector<std::pair<std::string, std::string>> puts;
  std::vector<std::string> deletes;
};

static void CheckPut(void* state, const char* key, size_t klen,
                     const char* val, size_t vlen) {
  auto* s = static_cast<IterateState*>(state);
  s->puts.emplace_back(std::string(key, klen), std::string(val, vlen));
}

static void CheckDelete(void* state, const char* key, size_t klen) {
  auto* s = static_cast<IterateState*>(state);
  s->deletes.emplace_back(std::string(key, klen));
}

// Test: Clearing an empty batch should succeed without issues
TEST_F(WriteBatchClearTest_246, ClearEmptyBatch_246) {
  leveldb_writebatch_clear(batch_);
  // After clearing an already empty batch, count should be 0
  int count = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count, 0);
}

// Test: Clearing a batch with Put operations removes all operations
TEST_F(WriteBatchClearTest_246, ClearAfterPut_246) {
  leveldb_writebatch_put(batch_, "key1", 4, "val1", 4);
  leveldb_writebatch_put(batch_, "key2", 4, "val2", 4);

  int count_before = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_before, 2);

  leveldb_writebatch_clear(batch_);

  int count_after = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_after, 0);
}

// Test: Clearing a batch with Delete operations removes all operations
TEST_F(WriteBatchClearTest_246, ClearAfterDelete_246) {
  leveldb_writebatch_delete(batch_, "key1", 4);
  leveldb_writebatch_delete(batch_, "key2", 4);

  int count_before = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_before, 2);

  leveldb_writebatch_clear(batch_);

  int count_after = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_after, 0);
}

// Test: Clearing a batch with mixed Put and Delete operations
TEST_F(WriteBatchClearTest_246, ClearAfterMixedOperations_246) {
  leveldb_writebatch_put(batch_, "key1", 4, "val1", 4);
  leveldb_writebatch_delete(batch_, "key2", 4);
  leveldb_writebatch_put(batch_, "key3", 4, "val3", 4);

  int count_before = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_before, 3);

  leveldb_writebatch_clear(batch_);

  int count_after = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_after, 0);
}

// Test: After clearing, iterating should yield no operations
TEST_F(WriteBatchClearTest_246, ClearThenIterateYieldsNothing_246) {
  leveldb_writebatch_put(batch_, "key1", 4, "val1", 4);
  leveldb_writebatch_delete(batch_, "key2", 4);

  leveldb_writebatch_clear(batch_);

  IterateState state;
  leveldb_writebatch_iterate(batch_, &state, CheckPut, CheckDelete);

  EXPECT_TRUE(state.puts.empty());
  EXPECT_TRUE(state.deletes.empty());
}

// Test: After clearing, new operations can be added successfully
TEST_F(WriteBatchClearTest_246, ClearThenAddNewOperations_246) {
  leveldb_writebatch_put(batch_, "key1", 4, "val1", 4);
  leveldb_writebatch_put(batch_, "key2", 4, "val2", 4);

  leveldb_writebatch_clear(batch_);

  leveldb_writebatch_put(batch_, "key3", 4, "val3", 4);

  int count = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count, 1);

  IterateState state;
  leveldb_writebatch_iterate(batch_, &state, CheckPut, CheckDelete);

  ASSERT_EQ(state.puts.size(), 1u);
  EXPECT_EQ(state.puts[0].first, "key3");
  EXPECT_EQ(state.puts[0].second, "val3");
}

// Test: Multiple clears in succession should be safe
TEST_F(WriteBatchClearTest_246, MultipleClearsInSuccession_246) {
  leveldb_writebatch_put(batch_, "key1", 4, "val1", 4);

  leveldb_writebatch_clear(batch_);
  leveldb_writebatch_clear(batch_);
  leveldb_writebatch_clear(batch_);

  int count = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count, 0);
}

// Test: Clear after appending another batch
TEST_F(WriteBatchClearTest_246, ClearAfterAppend_246) {
  leveldb_writebatch_t* other = leveldb_writebatch_create();
  leveldb_writebatch_put(other, "k1", 2, "v1", 2);
  leveldb_writebatch_put(other, "k2", 2, "v2", 2);

  leveldb_writebatch_append(batch_, other);

  int count_before = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_before, 2);

  leveldb_writebatch_clear(batch_);

  int count_after = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_after, 0);

  leveldb_writebatch_destroy(other);
}

// Test: Clearing a batch with large number of operations
TEST_F(WriteBatchClearTest_246, ClearLargeBatch_246) {
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    leveldb_writebatch_put(batch_, key.c_str(), key.size(),
                           val.c_str(), val.size());
  }

  int count_before = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_before, 1000);

  leveldb_writebatch_clear(batch_);

  int count_after = leveldb_writebatch_count(batch_);
  EXPECT_EQ(count_after, 0);
}

// Test: ApproximateSize should decrease after clear
TEST_F(WriteBatchClearTest_246, ApproximateSizeDecreasesAfterClear_246) {
  leveldb_writebatch_put(batch_, "key1", 4, "value1", 6);
  leveldb_writebatch_put(batch_, "key2", 4, "value2", 6);
  leveldb_writebatch_put(batch_, "key3", 4, "value3", 6);

  size_t size_before = leveldb_writebatch_approximate_size(batch_);
  EXPECT_GT(size_before, 0u);

  leveldb_writebatch_clear(batch_);

  size_t size_after = leveldb_writebatch_approximate_size(batch_);
  EXPECT_LT(size_after, size_before);
}

// Test: Clear then add and verify operations via iterate
TEST_F(WriteBatchClearTest_246, ClearAndRebuildVerifyViaIterate_246) {
  leveldb_writebatch_put(batch_, "old_key", 7, "old_val", 7);
  leveldb_writebatch_delete(batch_, "del_key", 7);

  leveldb_writebatch_clear(batch_);

  leveldb_writebatch_put(batch_, "new_key", 7, "new_val", 7);
  leveldb_writebatch_delete(batch_, "rm_key", 6);

  IterateState state;
  leveldb_writebatch_iterate(batch_, &state, CheckPut, CheckDelete);

  ASSERT_EQ(state.puts.size(), 1u);
  EXPECT_EQ(state.puts[0].first, "new_key");
  EXPECT_EQ(state.puts[0].second, "new_val");

  ASSERT_EQ(state.deletes.size(), 1u);
  EXPECT_EQ(state.deletes[0], "rm_key");
}
