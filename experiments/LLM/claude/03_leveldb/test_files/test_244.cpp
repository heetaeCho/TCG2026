#include "gtest/gtest.h"
#include "leveldb/c.h"
#include <cstring>
#include <string>
#include <vector>

// Test fixture for WriteBatch C API tests
class WriteBatchTest_244 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that creating a write batch returns a non-null pointer
TEST_F(WriteBatchTest_244, CreateReturnsNonNull_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();
  ASSERT_NE(wb, nullptr);
  leveldb_writebatch_destroy(wb);
}

// Test that destroying a write batch does not crash
TEST_F(WriteBatchTest_244, DestroyDoesNotCrash_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();
  ASSERT_NE(wb, nullptr);
  leveldb_writebatch_destroy(wb);
  // If we reach here, destroy succeeded without crash
}

// Test that a newly created write batch has count 0 (via clear + iterate with no calls)
TEST_F(WriteBatchTest_244, NewBatchIsEmpty_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();
  ASSERT_NE(wb, nullptr);

  // Use a state struct to track iteration callbacks
  struct State {
    int put_count;
    int delete_count;
  };
  State state = {0, 0};

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->put_count++;
      },
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->delete_count++;
      });

  EXPECT_EQ(state.put_count, 0);
  EXPECT_EQ(state.delete_count, 0);

  leveldb_writebatch_destroy(wb);
}

// Test that Put adds an entry observable through iterate
TEST_F(WriteBatchTest_244, PutIsObservableThroughIterate_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  const char* key = "testkey";
  const char* val = "testval";
  leveldb_writebatch_put(wb, key, strlen(key), val, strlen(val));

  struct State {
    std::vector<std::pair<std::string, std::string>> puts;
    int delete_count;
  };
  State state;
  state.delete_count = 0;

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        auto* st = static_cast<State*>(s);
        st->puts.emplace_back(std::string(k, klen), std::string(v, vlen));
      },
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->delete_count++;
      });

  ASSERT_EQ(state.puts.size(), 1u);
  EXPECT_EQ(state.puts[0].first, "testkey");
  EXPECT_EQ(state.puts[0].second, "testval");
  EXPECT_EQ(state.delete_count, 0);

  leveldb_writebatch_destroy(wb);
}

// Test that Delete adds a delete entry observable through iterate
TEST_F(WriteBatchTest_244, DeleteIsObservableThroughIterate_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  const char* key = "delkey";
  leveldb_writebatch_delete(wb, key, strlen(key));

  struct State {
    int put_count;
    std::vector<std::string> deletes;
  };
  State state;
  state.put_count = 0;

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->put_count++;
      },
      [](void* s, const char* k, size_t klen) {
        auto* st = static_cast<State*>(s);
        st->deletes.emplace_back(std::string(k, klen));
      });

  EXPECT_EQ(state.put_count, 0);
  ASSERT_EQ(state.deletes.size(), 1u);
  EXPECT_EQ(state.deletes[0], "delkey");

  leveldb_writebatch_destroy(wb);
}

// Test that multiple puts and deletes are iterated in order
TEST_F(WriteBatchTest_244, MultiplePutsAndDeletesInOrder_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  leveldb_writebatch_put(wb, "k1", 2, "v1", 2);
  leveldb_writebatch_delete(wb, "k2", 2);
  leveldb_writebatch_put(wb, "k3", 2, "v3", 2);

  struct State {
    // Track operations in order: 'P' for put, 'D' for delete
    std::vector<char> ops;
    std::vector<std::string> keys;
    std::vector<std::string> values;  // only for puts
  };
  State state;

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        auto* st = static_cast<State*>(s);
        st->ops.push_back('P');
        st->keys.emplace_back(std::string(k, klen));
        st->values.emplace_back(std::string(v, vlen));
      },
      [](void* s, const char* k, size_t klen) {
        auto* st = static_cast<State*>(s);
        st->ops.push_back('D');
        st->keys.emplace_back(std::string(k, klen));
        st->values.emplace_back("");  // placeholder
      });

  ASSERT_EQ(state.ops.size(), 3u);
  EXPECT_EQ(state.ops[0], 'P');
  EXPECT_EQ(state.keys[0], "k1");
  EXPECT_EQ(state.values[0], "v1");

  EXPECT_EQ(state.ops[1], 'D');
  EXPECT_EQ(state.keys[1], "k2");

  EXPECT_EQ(state.ops[2], 'P');
  EXPECT_EQ(state.keys[2], "k3");
  EXPECT_EQ(state.values[2], "v3");

  leveldb_writebatch_destroy(wb);
}

// Test that Clear empties the batch
TEST_F(WriteBatchTest_244, ClearRemovesAllEntries_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  leveldb_writebatch_put(wb, "k1", 2, "v1", 2);
  leveldb_writebatch_delete(wb, "k2", 2);

  leveldb_writebatch_clear(wb);

  struct State {
    int count;
  };
  State state = {0};

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->count++;
      },
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->count++;
      });

  EXPECT_EQ(state.count, 0);

  leveldb_writebatch_destroy(wb);
}

// Test that after clearing, new operations can be added
TEST_F(WriteBatchTest_244, ClearThenAddWorks_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  leveldb_writebatch_put(wb, "k1", 2, "v1", 2);
  leveldb_writebatch_clear(wb);
  leveldb_writebatch_put(wb, "k2", 2, "v2", 2);

  struct State {
    std::vector<std::string> keys;
  };
  State state;

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->keys.emplace_back(std::string(k, klen));
      },
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->keys.emplace_back(std::string(k, klen));
      });

  ASSERT_EQ(state.keys.size(), 1u);
  EXPECT_EQ(state.keys[0], "k2");

  leveldb_writebatch_destroy(wb);
}

// Test that Put with empty key and value works
TEST_F(WriteBatchTest_244, PutEmptyKeyAndValue_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  leveldb_writebatch_put(wb, "", 0, "", 0);

  struct State {
    std::vector<std::pair<std::string, std::string>> puts;
  };
  State state;

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        auto* st = static_cast<State*>(s);
        st->puts.emplace_back(std::string(k, klen), std::string(v, vlen));
      },
      [](void* s, const char* k, size_t klen) {});

  ASSERT_EQ(state.puts.size(), 1u);
  EXPECT_EQ(state.puts[0].first, "");
  EXPECT_EQ(state.puts[0].second, "");

  leveldb_writebatch_destroy(wb);
}

// Test that Delete with empty key works
TEST_F(WriteBatchTest_244, DeleteEmptyKey_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  leveldb_writebatch_delete(wb, "", 0);

  struct State {
    std::vector<std::string> deletes;
  };
  State state;

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {},
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->deletes.emplace_back(std::string(k, klen));
      });

  ASSERT_EQ(state.deletes.size(), 1u);
  EXPECT_EQ(state.deletes[0], "");

  leveldb_writebatch_destroy(wb);
}

// Test that creating multiple write batches independently works
TEST_F(WriteBatchTest_244, MultipleIndependentBatches_244) {
  leveldb_writebatch_t* wb1 = leveldb_writebatch_create();
  leveldb_writebatch_t* wb2 = leveldb_writebatch_create();

  ASSERT_NE(wb1, nullptr);
  ASSERT_NE(wb2, nullptr);
  ASSERT_NE(wb1, wb2);

  leveldb_writebatch_put(wb1, "a", 1, "1", 1);
  leveldb_writebatch_put(wb2, "b", 1, "2", 1);

  struct State {
    std::vector<std::string> keys;
  };

  State state1;
  leveldb_writebatch_iterate(
      wb1, &state1,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->keys.emplace_back(std::string(k, klen));
      },
      [](void* s, const char* k, size_t klen) {});

  State state2;
  leveldb_writebatch_iterate(
      wb2, &state2,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->keys.emplace_back(std::string(k, klen));
      },
      [](void* s, const char* k, size_t klen) {});

  ASSERT_EQ(state1.keys.size(), 1u);
  EXPECT_EQ(state1.keys[0], "a");

  ASSERT_EQ(state2.keys.size(), 1u);
  EXPECT_EQ(state2.keys[0], "b");

  leveldb_writebatch_destroy(wb1);
  leveldb_writebatch_destroy(wb2);
}

// Test appending one batch to another
TEST_F(WriteBatchTest_244, AppendBatch_244) {
  leveldb_writebatch_t* wb1 = leveldb_writebatch_create();
  leveldb_writebatch_t* wb2 = leveldb_writebatch_create();

  leveldb_writebatch_put(wb1, "k1", 2, "v1", 2);
  leveldb_writebatch_put(wb2, "k2", 2, "v2", 2);

  leveldb_writebatch_append(wb1, wb2);

  struct State {
    std::vector<std::string> keys;
  };
  State state;

  leveldb_writebatch_iterate(
      wb1, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->keys.emplace_back(std::string(k, klen));
      },
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->keys.emplace_back(std::string(k, klen));
      });

  ASSERT_EQ(state.keys.size(), 2u);
  EXPECT_EQ(state.keys[0], "k1");
  EXPECT_EQ(state.keys[1], "k2");

  leveldb_writebatch_destroy(wb1);
  leveldb_writebatch_destroy(wb2);
}

// Test that Put with large key and value works
TEST_F(WriteBatchTest_244, PutLargeKeyValue_244) {
  leveldb_writebatch_t* wb = leveldb_writebatch_create();

  std::string large_key(10000, 'K');
  std::string large_val(100000, 'V');
  leveldb_writebatch_put(wb, large_key.data(), large_key.size(),
                         large_val.data(), large_val.size());

  struct State {
    std::string key;
    std::string val;
    int count;
  };
  State state;
  state.count = 0;

  leveldb_writebatch_iterate(
      wb, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        auto* st = static_cast<State*>(s);
        st->key = std::string(k, klen);
        st->val = std::string(v, vlen);
        st->count++;
      },
      [](void* s, const char* k, size_t klen) {});

  EXPECT_EQ(state.count, 1);
  EXPECT_EQ(state.key.size(), 10000u);
  EXPECT_EQ(state.val.size(), 100000u);
  EXPECT_EQ(state.key, std::string(10000, 'K'));
  EXPECT_EQ(state.val, std::string(100000, 'V'));

  leveldb_writebatch_destroy(wb);
}

// Test creating and immediately destroying (no operations)
TEST_F(WriteBatchTest_244, CreateAndDestroyImmediately_244) {
  for (int i = 0; i < 100; i++) {
    leveldb_writebatch_t* wb = leveldb_writebatch_create();
    ASSERT_NE(wb, nullptr);
    leveldb_writebatch_destroy(wb);
  }
}

// Test that appending an empty batch to a non-empty batch doesn't change it
TEST_F(WriteBatchTest_244, AppendEmptyBatchNoEffect_244) {
  leveldb_writebatch_t* wb1 = leveldb_writebatch_create();
  leveldb_writebatch_t* wb2 = leveldb_writebatch_create();

  leveldb_writebatch_put(wb1, "k1", 2, "v1", 2);
  // wb2 is empty

  leveldb_writebatch_append(wb1, wb2);

  struct State {
    int count;
  };
  State state = {0};

  leveldb_writebatch_iterate(
      wb1, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        static_cast<State*>(s)->count++;
      },
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->count++;
      });

  EXPECT_EQ(state.count, 1);

  leveldb_writebatch_destroy(wb1);
  leveldb_writebatch_destroy(wb2);
}

// Test that the source batch is not modified after being appended
TEST_F(WriteBatchTest_244, AppendDoesNotModifySource_244) {
  leveldb_writebatch_t* wb1 = leveldb_writebatch_create();
  leveldb_writebatch_t* wb2 = leveldb_writebatch_create();

  leveldb_writebatch_put(wb2, "k2", 2, "v2", 2);
  leveldb_writebatch_append(wb1, wb2);

  // Check wb2 still has its original content
  struct State {
    int count;
    std::string key;
  };
  State state = {0, ""};

  leveldb_writebatch_iterate(
      wb2, &state,
      [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
        auto* st = static_cast<State*>(s);
        st->count++;
        st->key = std::string(k, klen);
      },
      [](void* s, const char* k, size_t klen) {
        static_cast<State*>(s)->count++;
      });

  EXPECT_EQ(state.count, 1);
  EXPECT_EQ(state.key, "k2");

  leveldb_writebatch_destroy(wb1);
  leveldb_writebatch_destroy(wb2);
}
