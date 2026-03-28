#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

// Test that destroying a valid writebatch does not crash
TEST(LevelDBWriteBatchDestroyTest_245, DestroyValidWriteBatch_245) {
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  ASSERT_NE(batch, nullptr);
  // Should not crash or leak
  leveldb_writebatch_destroy(batch);
}

// Test that destroying a writebatch after putting data does not crash
TEST(LevelDBWriteBatchDestroyTest_245, DestroyAfterPut_245) {
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  ASSERT_NE(batch, nullptr);
  leveldb_writebatch_put(batch, "key", 3, "value", 5);
  leveldb_writebatch_destroy(batch);
}

// Test that destroying a writebatch after delete operation does not crash
TEST(LevelDBWriteBatchDestroyTest_245, DestroyAfterDelete_245) {
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  ASSERT_NE(batch, nullptr);
  leveldb_writebatch_delete(batch, "key", 3);
  leveldb_writebatch_destroy(batch);
}

// Test that destroying a writebatch after clear does not crash
TEST(LevelDBWriteBatchDestroyTest_245, DestroyAfterClear_245) {
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  ASSERT_NE(batch, nullptr);
  leveldb_writebatch_put(batch, "key", 3, "value", 5);
  leveldb_writebatch_clear(batch);
  leveldb_writebatch_destroy(batch);
}

// Test that destroying a writebatch with multiple operations does not crash
TEST(LevelDBWriteBatchDestroyTest_245, DestroyAfterMultipleOperations_245) {
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  ASSERT_NE(batch, nullptr);
  leveldb_writebatch_put(batch, "key1", 4, "value1", 6);
  leveldb_writebatch_put(batch, "key2", 4, "value2", 6);
  leveldb_writebatch_delete(batch, "key1", 4);
  leveldb_writebatch_put(batch, "key3", 4, "value3", 6);
  leveldb_writebatch_destroy(batch);
}

// Test that creating and immediately destroying is safe (empty batch)
TEST(LevelDBWriteBatchDestroyTest_245, CreateAndImmediatelyDestroy_245) {
  leveldb_writebatch_t* batch = leveldb_writebatch_create();
  ASSERT_NE(batch, nullptr);
  // Immediate destroy with no operations
  leveldb_writebatch_destroy(batch);
}

// Test destroying a writebatch after appending another batch
TEST(LevelDBWriteBatchDestroyTest_245, DestroyAfterAppend_245) {
  leveldb_writebatch_t* batch1 = leveldb_writebatch_create();
  leveldb_writebatch_t* batch2 = leveldb_writebatch_create();
  ASSERT_NE(batch1, nullptr);
  ASSERT_NE(batch2, nullptr);

  leveldb_writebatch_put(batch1, "key1", 4, "val1", 4);
  leveldb_writebatch_put(batch2, "key2", 4, "val2", 4);
  leveldb_writebatch_append(batch1, batch2);

  leveldb_writebatch_destroy(batch2);
  leveldb_writebatch_destroy(batch1);
}

// Test that destroying multiple independently created batches works
TEST(LevelDBWriteBatchDestroyTest_245, DestroyMultipleBatches_245) {
  const int kNumBatches = 10;
  leveldb_writebatch_t* batches[kNumBatches];

  for (int i = 0; i < kNumBatches; i++) {
    batches[i] = leveldb_writebatch_create();
    ASSERT_NE(batches[i], nullptr);
    leveldb_writebatch_put(batches[i], "key", 3, "val", 3);
  }

  for (int i = 0; i < kNumBatches; i++) {
    leveldb_writebatch_destroy(batches[i]);
  }
}
