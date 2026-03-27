// File: leveldb_writebatch_put_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/write_batch.h"  // For leveldb::WriteBatch, Handler, Slice

using ::testing::_;
using ::testing::InSequence;
using ::testing::Matcher;
using ::testing::StrEq;

// Forward declarations for the C API we are testing.
// We only use the public C functions and opaque pointer type.
extern "C" {

// Opaque handle type (pointer-only usage here).
struct leveldb_writebatch_t;

// C API under test:
void leveldb_writebatch_put(leveldb_writebatch_t* b,
                            const char* key, size_t klen,
                            const char* val, size_t vlen);

// Common C helpers expected in the C API (creation & destruction).
// These exist in LevelDB's C wrapper and are used as black-box creators.
leveldb_writebatch_t* leveldb_writebatch_create();
void leveldb_writebatch_destroy(leveldb_writebatch_t* b);

// We also rely on Iterate through the underlying batch, but we won't
// access internals; we'll route through a helper that accepts the C handle.
// If your build exposes only C++ Iterate, we will adapt via a small helper
// fixture method below that unwraps using only Iterate via public API.
// (No private access or assumptions are used.)
}

// ---------- Test Fixture ----------

class WriteBatchCPutTest_247 : public ::testing::Test {
protected:
  leveldb_writebatch_t* wb_ = nullptr;

  void SetUp() override {
    wb_ = leveldb_writebatch_create();
    ASSERT_NE(wb_, nullptr);
  }

  void TearDown() override {
    if (wb_) leveldb_writebatch_destroy(wb_);
  }

  // A concrete Handler to capture calls from Iterate without relying on internals.
  struct RecordingHandler : public leveldb::WriteBatch::Handler {
    std::vector<std::pair<std::string, std::string>> puts;
    std::vector<std::string> deletes;

    void Put(const leveldb::Slice& key, const leveldb::Slice& value) override {
      puts.emplace_back(std::string(key.data(), key.size()),
                        std::string(value.data(), value.size()));
    }
    void Delete(const leveldb::Slice& key) override {
      deletes.emplace_back(std::string(key.data(), key.size()));
    }
  };

  // Helper to iterate the batch and return recorded operations.
  // This uses only the public Iterate(Handler*) API of WriteBatch.
  std::vector<std::pair<std::string, std::string>> IterateAndGetPuts() {
    // We cannot access internals of leveldb_writebatch_t here.
    // Instead, we create a temporary empty WriteBatch, append the C batch into it
    // via public Append if a C helper exists. If only Iterate is available,
    // we need a public way to call Iterate on the underlying batch.
    //
    // Many LevelDB C wrappers expose a function leveldb_writebatch_iterate
    // or similar; if your build does not, we can make a small bridge by
    // creating a minimal adapter Handler at test-time that we pass through
    // a public API exposed for the C batch. To stay strictly within the
    // given interface, we call Iterate by leveraging the public Handler
    // passed into the C wrapper via a provided function. If your environment
    // lacks such a helper, replace the following extern with the actual one.

    extern "C" {
      // Expected helper in the C wrapper; if your headers name it differently,
      // adjust the declaration accordingly for your build.
      void leveldb_writebatch_iterate(leveldb_writebatch_t* b,
                                      void (*put)(void*, const char*, size_t, const char*, size_t),
                                      void (*deleted)(void*, const char*, size_t),
                                      void* state);
    }

    RecordingHandler rec;

    // Thin callbacks that forward to our RecordingHandler without peeking internals.
    auto c_put = [](void* s, const char* k, size_t klen, const char* v, size_t vlen) {
      auto* handler = static_cast<RecordingHandler*>(s);
      handler->Put(leveldb::Slice(k, klen), leveldb::Slice(v, vlen));
    };
    auto c_del = [](void* s, const char* k, size_t klen) {
      auto* handler = static_cast<RecordingHandler*>(s);
      handler->Delete(leveldb::Slice(k, klen));
    };

    leveldb_writebatch_iterate(wb_, c_put, c_del, &rec);
    return rec.puts;
  }
};

// ---------- Tests ----------

// Verifies a single Put is recorded via the public iteration interface.
TEST_F(WriteBatchCPutTest_247, CallsUnderlyingPutOnce_247) {
  const char* k = "key1";
  const char* v = "value1";
  leveldb_writebatch_put(wb_, k, 4, v, 6);  // "key1", "value1"

  auto puts = IterateAndGetPuts();
  ASSERT_EQ(puts.size(), 1u);
  EXPECT_EQ(puts[0].first, "key1");
  EXPECT_EQ(puts[0].second, "value1");
}

// Verifies multiple Put calls are preserved in order when iterated.
TEST_F(WriteBatchCPutTest_247, MultiplePutsPreserveOrder_247) {
  leveldb_writebatch_put(wb_, "a", 1, "1", 1);
  leveldb_writebatch_put(wb_, "b", 1, "2", 1);
  leveldb_writebatch_put(wb_, "c", 1, "3", 1);

  auto puts = IterateAndGetPuts();
  ASSERT_EQ(puts.size(), 3u);
  EXPECT_EQ(puts[0].first, "a"); EXPECT_EQ(puts[0].second, "1");
  EXPECT_EQ(puts[1].first, "b"); EXPECT_EQ(puts[1].second, "2");
  EXPECT_EQ(puts[2].first, "c"); EXPECT_EQ(puts[2].second, "3");
}

// Boundary: empty key and non-empty value should be preserved as empty key.
TEST_F(WriteBatchCPutTest_247, HandlesEmptyKey_247) {
  const char* empty = "";  // non-null pointer even for zero length
  const char* v = "val";
  leveldb_writebatch_put(wb_, empty, 0, v, 3);

  auto puts = IterateAndGetPuts();
  ASSERT_EQ(puts.size(), 1u);
  EXPECT_EQ(puts[0].first, "");     // empty key
  EXPECT_EQ(puts[0].second, "val");
}

// Boundary: non-empty key and empty value should be preserved as empty value.
TEST_F(WriteBatchCPutTest_247, HandlesEmptyValue_247) {
  const char* k = "k";
  const char* empty = "";
  leveldb_writebatch_put(wb_, k, 1, empty, 0);

  auto puts = IterateAndGetPuts();
  ASSERT_EQ(puts.size(), 1u);
  EXPECT_EQ(puts[0].first, "k");
  EXPECT_EQ(puts[0].second, "");    // empty value
}

// Binary data: embedded NULs must be preserved because lengths are explicit.
TEST_F(WriteBatchCPutTest_247, PreservesBinaryDataWithNulls_247) {
  const char key_bytes[]  = {'k', '\0', 'x'};
  const char value_bytes[] = {'v', '\0', 'y', '\0'};

  leveldb_writebatch_put(wb_, key_bytes,   sizeof(key_bytes),   value_bytes, sizeof(value_bytes));

  auto puts = IterateAndGetPuts();
  ASSERT_EQ(puts.size(), 1u);
  EXPECT_EQ(puts[0].first.size(), sizeof(key_bytes));
  EXPECT_EQ(puts[0].second.size(), sizeof(value_bytes));
  EXPECT_EQ(puts[0].first[0], 'k');
  EXPECT_EQ(puts[0].first[1], '\0');
  EXPECT_EQ(puts[0].first[2], 'x');
  EXPECT_EQ(puts[0].second[0], 'v');
  EXPECT_EQ(puts[0].second[1], '\0');
  EXPECT_EQ(puts[0].second[2], 'y');
  EXPECT_EQ(puts[0].second[3], '\0');
}
