// File: db/c_iterate_test_249.cc
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "gtest/gtest.h"

// The C wrapper and struct under test come from db/c.cc
extern "C" {
  struct leveldb_writebatch_t { leveldb::WriteBatch rep; };
  void leveldb_writebatch_iterate(
      const leveldb_writebatch_t* b,
      void* state,
      void (*put)(void*, const char* k, size_t klen, const char* v, size_t vlen),
      void (*deleted)(void*, const char* k, size_t klen));
}

using leveldb::Slice;

struct CallbackEvent {
  enum Type { kPut, kDelete } type;
  std::string key;
  std::string value; // empty for deletes
};

struct CallbackState {
  std::vector<CallbackEvent> events;
  int put_count = 0;
  int delete_count = 0;
};

// Plain C callbacks that record observable behavior into CallbackState.
static void TestPutCB(void* st,
                      const char* k, size_t klen,
                      const char* v, size_t vlen) {
  auto* state = reinterpret_cast<CallbackState*>(st);
  state->events.push_back({CallbackEvent::kPut,
                           std::string(k, klen),
                           std::string(v, vlen)});
  state->put_count++;
}

static void TestDeleteCB(void* st,
                         const char* k, size_t klen) {
  auto* state = reinterpret_cast<CallbackState*>(st);
  state->events.push_back({CallbackEvent::kDelete,
                           std::string(k, klen),
                           std::string()});
  state->delete_count++;
}

class WriteBatchIterateTest_249 : public ::testing::Test {
protected:
  leveldb_writebatch_t batch_;
  CallbackState state_;

  void Iterate() {
    leveldb_writebatch_iterate(&batch_, &state_, &TestPutCB, &TestDeleteCB);
  }
};

// [Normal] Empty batch produces no callbacks
TEST_F(WriteBatchIterateTest_249, EmptyBatch_NoCallbacks_249) {
  // No operations added to batch_.rep
  Iterate();

  EXPECT_TRUE(state_.events.empty());
  EXPECT_EQ(state_.put_count, 0);
  EXPECT_EQ(state_.delete_count, 0);
}

// [Normal] Single Put triggers put callback with exact key/value bytes and lengths
TEST_F(WriteBatchIterateTest_249, SinglePut_CallbackReceivesKeyAndValue_249) {
  batch_.rep.Put(Slice("alpha"), Slice("one"));

  Iterate();

  ASSERT_EQ(state_.put_count, 1);
  ASSERT_EQ(state_.delete_count, 0);
  ASSERT_EQ(state_.events.size(), 1u);
  const auto& ev = state_.events[0];
  EXPECT_EQ(ev.type, CallbackEvent::kPut);
  EXPECT_EQ(ev.key, "alpha");
  EXPECT_EQ(ev.value, "one");
}

// [Normal] Single Delete triggers delete callback with exact key bytes and length
TEST_F(WriteBatchIterateTest_249, SingleDelete_CallbackReceivesKey_249) {
  batch_.rep.Delete(Slice("gone"));

  Iterate();

  ASSERT_EQ(state_.put_count, 0);
  ASSERT_EQ(state_.delete_count, 1);
  ASSERT_EQ(state_.events.size(), 1u);
  const auto& ev = state_.events[0];
  EXPECT_EQ(ev.type, CallbackEvent::kDelete);
  EXPECT_EQ(ev.key, "gone");
  EXPECT_TRUE(ev.value.empty());
}

// [Boundary] Preserves operation order across multiple mixed operations
TEST_F(WriteBatchIterateTest_249, MultipleOps_OrderAndCounts_249) {
  batch_.rep.Put(Slice("k1"), Slice("v1"));
  batch_.rep.Delete(Slice("k2"));
  batch_.rep.Put(Slice("k3"), Slice("v3"));
  batch_.rep.Delete(Slice("k4"));

  Iterate();

  ASSERT_EQ(state_.put_count, 2);
  ASSERT_EQ(state_.delete_count, 2);
  ASSERT_EQ(state_.events.size(), 4u);

  EXPECT_EQ(state_.events[0].type, CallbackEvent::kPut);
  EXPECT_EQ(state_.events[0].key, "k1");
  EXPECT_EQ(state_.events[0].value, "v1");

  EXPECT_EQ(state_.events[1].type, CallbackEvent::kDelete);
  EXPECT_EQ(state_.events[1].key, "k2");

  EXPECT_EQ(state_.events[2].type, CallbackEvent::kPut);
  EXPECT_EQ(state_.events[2].key, "k3");
  EXPECT_EQ(state_.events[2].value, "v3");

  EXPECT_EQ(state_.events[3].type, CallbackEvent::kDelete);
  EXPECT_EQ(state_.events[3].key, "k4");
}

// [Boundary] Empty key/value are forwarded with correct zero lengths (no crashes, exact bytes)
TEST_F(WriteBatchIterateTest_249, HandlesEmptyKeyAndValueLengths_249) {
  // Use explicit length constructor to allow empty slices
  const char* empty = "";
  batch_.rep.Put(Slice(empty, 0), Slice(empty, 0)); // empty key, empty value
  batch_.rep.Delete(Slice(empty, 0));               // empty key delete

  Iterate();

  ASSERT_EQ(state_.events.size(), 2u);
  // First event: put with empty key/value
  EXPECT_EQ(state_.events[0].type, CallbackEvent::kPut);
  EXPECT_TRUE(state_.events[0].key.empty());
  EXPECT_TRUE(state_.events[0].value.empty());
  // Second event: delete with empty key
  EXPECT_EQ(state_.events[1].type, CallbackEvent::kDelete);
  EXPECT_TRUE(state_.events[1].key.empty());
}
